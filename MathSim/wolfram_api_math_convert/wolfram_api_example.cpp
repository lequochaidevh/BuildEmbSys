#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

// Callback function to handle data returned from the API
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

int main() {
    CURL* curl;
    CURLcode res;

    // Your API Key and the query to send to Wolfram Alpha
    std::string apiKey = "API_KEY";  // Replace with your actual API key
    std::string query = "simplify sin(a) * cos(b) + cos(a) * sin(b)";
    
    // Initialize cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        // URL encode the query
        char* encoded_query = curl_easy_escape(curl, query.c_str(), query.length());

        // Construct the full URL with the encoded query parameters
        std::string url = "http://api.wolframalpha.com/v2/query?input=" + std::string(encoded_query) + "&format=plaintext&output=JSON&appid=" + apiKey;

        std::string response_string;

        // Set the URL and the callback function to handle the response
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        // Send the request
        res = curl_easy_perform(curl);

        // Check the result of the request
        if(res != CURLE_OK) {
            std::cerr << "cURL Error: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Uncomment the line below to print the full response
            // std::cout << "Response: " << response_string << std::endl;

            // Parse the JSON response
            try {
                auto json_data = nlohmann::json::parse(response_string);

                // Check if the query was successful
                if (json_data["queryresult"]["success"] == true) {
                    // Extract and print line 1 from the "Input interpretation" pod
                    std::string input_plaintext = json_data["queryresult"]["pods"][0]["subpods"][0]["plaintext"];
                    std::cout << input_plaintext << std::endl;  // Line 1

                    // Extract and print line 2 from the "Result" pod
                    std::string result_plaintext = json_data["queryresult"]["pods"][1]["subpods"][0]["plaintext"];
                    std::cout << result_plaintext << std::endl;  // Line 2
                } else {
                    std::cerr << "Error: No results or query failed." << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
            }
        }

        // Clean up
        curl_easy_cleanup(curl);
        curl_free(encoded_query);
    }

    curl_global_cleanup();
    return 0;
}
