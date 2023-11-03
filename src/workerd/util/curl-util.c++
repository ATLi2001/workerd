#include "curl-util.h"

#include <kj/debug.h>
#include <curl/curl.h>

namespace workerd {

  // write callback function for curl
  static size_t write_cb(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
  }

  void curlGet(std::string url, std::string& readBuffer) {
    CURL *curl;

    curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
      curl_easy_perform(curl);
      curl_easy_cleanup(curl);
    }
    KJ_ASSERT(readBuffer.size() > 0, "curl easy did not work");
  }

  void curlPost(std::string url, std::string key, int version_number) {
    CURL *curl;

    curl = curl_easy_init();
    if(curl) {
      // POST request but no data
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0L);
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
      // set headers
      struct curl_slist *list = NULL;
      std::string key_header("key: ");
      std::string version_number_header("versionNumber: ");
      list = curl_slist_append(list, key_header.append(key).c_str());
      list = curl_slist_append(list, version_number_header.append(std::to_string(version_number)).c_str());
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
      // do curl
      curl_easy_perform(curl);
      // cleanup
      curl_easy_cleanup(curl);
      curl_slist_free_all(list);
    }
  }
}
