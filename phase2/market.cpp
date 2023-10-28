#include "market.h"
#include "market_manager.cpp"

market::market(int argc, char** argv) 
{

}

void market::start()
{
  ifstream inputFile("output.txt");

  string line;
  int curr_timestamp = 0;
  // (stock) -> (broker, price, # stocks, life_remaining)
  buffer_dict sell_buffer; 
  buffer_dict buy_buffer;

  while (getline(inputFile, line)) {
    if(line == "TL") // start of the file
      continue;
    if(line == "!@") // end of relevent data
      break;

    // breaks each line into individual words
    vector<string> words = split_sentence(line, ' ');

    int timestamp = stoi(words[0]);
    if(curr_timestamp != timestamp) {
      // check matches by calling market_manager(~buffers~)
      curr_timestamp = timestamp;
    }

    string stock_name = words[3];

    stock_entry value = {
      words[1],                 // broker_name
      stoi(words[4].substr(1)), // price
      stoi(words[5].substr(1)), // quantity
      timestamp,                // time_of_entry
      stoi(words[6])            // life_remaining
    };

    // inserting into buffers
    if(words[2] == "SELL")
      sell_buffer[stock_name].insert(value);
    else if(words[2] == "BUY")
      buy_buffer[stock_name].insert(value);
  }

  // shit be workin innit
  cout << "----- Sellers -----\n";
  for(auto& entries : sell_buffer) {
    Node* curr = entries.second.root;
    cout << entries.first << ": ";
    while(curr) {
      cout << curr->data.broker_name << " " << curr->data.price << " --- ";
      curr = curr->next_node;
    }
    cout << endl;
  }

  cout << "----- Buyers -----\n";
  for(auto& entries : buy_buffer) {
    Node* curr = entries.second.root;    
    cout << entries.first << ": ";
    while(curr) {
      cout << entries.first << " " << curr->data.broker_name << " " << curr->data.price << " --- ";
      curr = curr->next_node;
    }
    cout << endl;
  }

  inputFile.close();
}
