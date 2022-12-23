#include <iostream>
#include <string>

// Include the necessary libraries for making HTTP requests and parsing JSON
#include <curl/curl.h>
#include <nlohmann/json.hpp>

// Replace these constants with your own API key and base URL
const std::string API_KEY = "YOUR_API_KEY";
const std::string API_BASE_URL = "https://api.plancke.io/";

// This function makes a GET request to the Plancke.io API and returns the response as a string
std::string makeApiRequest(const std::string& endpoint, const std::string& queryString) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        // Set the URL and query string
        std::string url = API_BASE_URL + endpoint + "?" + queryString;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the API key as a header
        struct curl_slist* headers = NULL;
        std::string apiKeyHeader = "Authorization: Bearer " + API_KEY;
        headers = curl_slist_append(headers, apiKeyHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the callback function for storing the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char* ptr, size_t size, size_t nmemb, std::string* data) -> size_t {
            data->append(ptr, size * nmemb);
            return size * nmemb;
        });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Make the request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return response;
}

// This function retrieves the statistics for a given player and game mode from the Plancke.io API
void getPlayerStats(const std::string& playerName, const std::string& gameMode) {
    // Build the query string for the API request
    std::string queryString = "player=" + playerName + "&mode=" + gameMode;

    // Make the API request and store the response
    std::string response = makeApiRequest("player/stats", queryString);

    // Parse the JSON response
    auto json = nlohmann::json::parse(response);

    // Extract the desired statistics from the JSON data
    // Replace "kdr", "fkdr", and "w/l" with the actual keys for the statistics you want to retrieve
    double kdr = json["stats"]["kdr"];
    double fkdr = json["stats"]["fkdr"];
    double wl = json["stats"]["w/l"];

    // Print the retrieved statistics to the console
    std::cout << playerName << " " << gameMode << " stats:" << std::endl;
    std::cout << "KDR: " << kdr << std::endl;
    std::cout << "FKDR: " << fkdr << std::endl;
    std::cout << "W/L: " << wl << std::endl;
}
