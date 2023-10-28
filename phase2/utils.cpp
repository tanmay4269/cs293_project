#include "bits/stdc++.h"
#include "stock_entries.cpp"
using namespace std;

typedef map<string, StockEntries> buffer_dict;

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
    // word.pop_back();
    split_result.push_back(word);

    return split_result;
}
