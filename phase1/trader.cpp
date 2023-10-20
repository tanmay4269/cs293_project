// #include "receiver.h"
#include "iostream"
#include "string"
#include "vector"
#include "map"
using namespace std;

vector<string> split_sentence(string str, char delem) {
    vector<string> split_result;

    string word = "";
    for (auto x : str)  {
        if (x == delem) {
            split_result.push_back(word);
            word = "";
        }
        else {
            word = word + x;
        }
    }

    return split_result;
}

bool accept_trade(int* old_price, int curr_price, string direction) {
    if((direction == "b" && *old_price < curr_price) || (direction == "s" && *old_price > curr_price)) {
        *old_price = curr_price;
        return true;
    }

    return false;
}

int main() {

    // Receiver rcv;
    // sleep(5);
    // string message = rcv.readIML();

    string message = "ASML 650 s#ASML 645 b#AAPL 430 b#$";
    message.pop_back();
    vector<string> orders = split_sentence(message, '#');

    map<string, int> price_buffers;

    vector<string> responces;

    for(string order : orders) {
        vector<string> words = split_sentence(order, ' ');
        string stock = words[0];
        int price = stoi(words[1]);
        string direction = words[0];

        if(price_buffers.find(stock) == price_buffers.end()) {
            price_buffers[stock] = price;
        } else {
            if(accept_trade(&price_buffers[stock], price, direction)) {
                string dir = (direction == "s") ? "b" : "s";
                string responce = stock + " " + to_string(price) + " " + dir;
                responces.push_back(responce);
            } else {
                responces.push_back("No trade");
            }
        }
    }

    message = "";
    for(auto responce : responces) {
        message += responce + "\n";
    }

    cout << message;


    return 0;
}
