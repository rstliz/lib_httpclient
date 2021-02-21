#include "http_client.hpp"

#include <gtest/gtest.h>

TEST(HttpClientTest_HttpRequest, ValidResponse) {
    rsato::HttpClient http_client;
    rsato::HttpResponse response = http_client.HttpRequest("https://www.google.com/", 1000);

    EXPECT_FALSE(response.GetResponse().empty());
    EXPECT_TRUE(response.IsValid());
    EXPECT_STREQ("No error", response.GetErrorMessage().c_str());
}

TEST(HttpClientTest_HttpRequest, InValidResponse) {
    rsato::HttpClient http_client;
    rsato::HttpResponse response = http_client.HttpRequest("https://foo.rsato.jp/", 1000);

    EXPECT_TRUE(response.GetResponse().empty());
    EXPECT_FALSE(response.IsValid());
    EXPECT_FALSE(response.GetErrorMessage().empty());
}