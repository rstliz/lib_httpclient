
#include "http_client.hpp"

#include <curl/curl.h>

#include <stdexcept>
#include <string>

/*
 ライブラリ利用者にcurlへのリンクを意識させたくないので、curl依存処理はcppに分割
*/
namespace rsato {

HttpClient::HttpClient() {
    //スレッドセーフではないのでアプリケーション起動時に1度呼ぶべき。
    if (CURLE_OK != curl_global_init(CURL_GLOBAL_ALL)) {
        throw std::runtime_error("Failed curl_global_init().");
    }
}

HttpClient::~HttpClient() {
    //アプリケーション終了時に一度だけ呼ぶべき
    curl_global_cleanup();
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, std::string *stream) {
    int data_size = size * nmemb;
    stream->append(ptr, data_size);
    return data_size;
}

HttpResponse HttpClient::HttpRequest(const std::string &url, const int timeout_ms) {
    std::string chunk;

    CURL *curl = curl_easy_init();
    if (!curl) {
        HttpResponse response(false, "", "Failed curl_easy_init().", -1);
        return response;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout_ms);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    curl_off_t curltime;
    curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &curltime);

    HttpResponse response((res == CURLE_OK), chunk, std::string(curl_easy_strerror(res)), (std::int64_t)curltime);
    return response;
}

std::string HttpClient::UrlEncode(const std::string &arg_str) {
    CURL *curl              = curl_easy_init();
    char *encoded           = curl_easy_escape(curl, arg_str.c_str(), arg_str.size());  // RFC3986
    std::string encoded_str = encoded;
    curl_free(encoded);
    curl_easy_cleanup(curl);
    return encoded_str;
}

}  // namespace rsato