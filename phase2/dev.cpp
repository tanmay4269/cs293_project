#include "utils.cpp"

int main() {
  StockEntries stock1;

  stock_entry entry1 = {
    "z",
    100,
    100,
    100,
    100
  };

  stock_entry entry2 = {
    "y",
    99,
    100,
    100,
    100
  };
  
  stock_entry entry3 = {
    "x",
    98,
    100,
    100,
    100
  };

  stock_entry entry4 = {
    "w",
    97,
    100,
    100,
    100
  };

  stock1.insert(entry1);
  stock1.insert(entry2);
  stock1.insert(entry3);
  stock1.insert(entry4);

  cout << stock1.root->data.broker_name << endl;
  cout << stock1.root->next_node->data.broker_name << endl;
  cout << stock1.root->next_node->next_node->data.broker_name << endl;
  cout << stock1.root->next_node->next_node->next_node->data.broker_name << endl;

}