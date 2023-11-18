// functions for making curl requests and processing them

#pragma once

#include <string>

namespace workerd {
  // make an http GET request to url
  // response is written to readBuffer
  void curlGet(std::string url, std::string& readBuffer);

  // make an http POST request to url
  // specific for consistency check headers
  void curlPost(std::string url, std::string key, int version_number);

  // make and http POST request to url using the json
  // return the response json in a string
  std::string curlPostJson(std::string url, std::string json);
}
