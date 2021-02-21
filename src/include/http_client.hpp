
#ifndef __HTTP_CLIENT_H_
#define __HTTP_CLIENT_H_

#include <string>

namespace rsato {

class HttpResponse;
class HttpClient {
   public:
    HttpClient();
    ~HttpClient();
    virtual HttpResponse HttpRequest(const std::string &url, const int timeout_ms);
    static std::string UrlEncode(const std::string &arg_str);
};

class HttpResponse {
   private:
    const bool is_valid_;
    const std::string response_;
    const std::string error_;
    const std::int64_t latency_usec_;

   public:
    HttpResponse(bool is_valid, std::string response, std::string error, std::int64_t latency_usec)
        : is_valid_(is_valid), response_(response), error_(error), latency_usec_(latency_usec){};
    bool IsValid() { return this->is_valid_; }
    std::string GetResponse() { return this->response_; }
    std::string GetErrorMessage() { return this->error_; }
    std::int64_t GetLatency() { return this->latency_usec_; }
    std::int64_t GetLatencyAsMilliSec() { return this->latency_usec_ / 1000; }
};

}  // namespace rsato
#endif
