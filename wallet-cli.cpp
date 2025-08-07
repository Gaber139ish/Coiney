#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>  // You’ll need jsoncpp or similar library

// Replace with your RPC credentials and URL
const std::string rpcUser = "user";
const std::string rpcPassword = "password";
const std::string rpcUrl = "http://127.0.0.1:9332/"; // default Litecoin port; adjust for Coiney

// Helper to capture CURL response
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Make JSON-RPC call
Json::Value rpc_call(const std::string& method, const Json::Value& params)
{
    CURL* curl = curl_easy_init();
    Json::Value result;
    if(curl) {
        Json::StreamWriterBuilder writer;
        Json::Value rpc_request;
        rpc_request["jsonrpc"] = "1.0";
        rpc_request["id"] = "wallet-cli";
        rpc_request["method"] = method;
        rpc_request["params"] = params;

        std::string requestStr = Json::writeString(writer, rpc_request);
        std::string readBuffer;

        curl_easy_setopt(curl, CURLOPT_URL, rpcUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)requestStr.size());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestStr.c_str());
        curl_easy_setopt(curl, CURLOPT_USERPWD, (rpcUser + ":" + rpcPassword).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            exit(1);
        }
        curl_easy_cleanup(curl);

        Json::CharReaderBuilder readerBuilder;
        std::string errs;
        std::istringstream s(readBuffer);
        if (!Json::parseFromStream(readerBuilder, s, &result, &errs)) {
            std::cerr << "JSON parse error: " << errs << std::endl;
            exit(1);
        }
    }
    return result;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: wallet-cli <command> [args]\n";
        std::cout << "Commands:\n";
        std::cout << "  getbalance <address>\n";
        std::cout << "  sendtoaddress <address> <amount>\n";
        return 1;
    }

    std::string cmd = argv[1];

    if (cmd == "getbalance") {
        if (argc < 3) {
            std::cerr << "Usage: wallet-cli getbalance <address>\n";
            return 1;
        }
        std::string address = argv[2];
        Json::Value params;
        params.append(address);
        Json::Value res = rpc_call("getreceivedbyaddress", params);
        std::cout << "Balance for " << address << ": " << res.asString() << " COY\n";
    }
    else if (cmd == "sendtoaddress") {
        if (argc < 4) {
            std::cerr << "Usage: wallet-cli sendtoaddress <address> <amount>\n";
            return 1;
        }
        std::string address = argv[2];
        double amount = atof(argv[3]);
        Json::Value params;
        params.append(address);
        params.append(amount);
        Json::Value res = rpc_call("sendtoaddress", params);
        std::cout << "Transaction sent! TXID: " << res.asString() << "\n";
    }
    else {
        std::cerr << "Unknown command: " << cmd << "\n";
        return 1;
    }

    return 0;
}
