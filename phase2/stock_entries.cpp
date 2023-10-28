#include "bits/stdc++.h"
using namespace std;

struct stock_entry {
    string broker_name;
    int price;
    int quantity;
    int time_of_entry;
    int life_remaining;
};

class Node {
public:
    stock_entry data;
    Node* next_node = nullptr;

    Node();
    Node(stock_entry value) : data(value) {};
};

/* TODO:
- [ ] inserting new entries
- [ ] updating life_remaining

*/
class StockEntries {
public:
    Node* root = nullptr;
    int size = 0;

    void insert(stock_entry& value) {
        Node* new_entry = new Node(value);

        if (root == nullptr || value.price > root->data.price || (value.price == root->data.price && value.time_of_entry < root->data.time_of_entry) || (value.price == root->data.price && value.time_of_entry == root->data.time_of_entry && value.broker_name < root->data.broker_name)) {
            new_entry->next_node = root;
            root = new_entry;
            size++;
            return;
        }

        Node* curr_node = root;
        Node* prev_node = nullptr;

        while (curr_node != nullptr) {
            if (value.price > curr_node->data.price || (value.price == curr_node->data.price && value.time_of_entry < curr_node->data.time_of_entry) || (value.price == curr_node->data.price && value.time_of_entry == curr_node->data.time_of_entry && value.broker_name < curr_node->data.broker_name)) {
                new_entry->next_node = curr_node;
                prev_node->next_node = new_entry;
                size++;
                return;
            }
            prev_node = curr_node;
            curr_node = curr_node->next_node;
        }

        prev_node->next_node = new_entry;
        size++;
    }

};
