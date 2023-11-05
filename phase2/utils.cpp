#include "vector"
#include "string"
#include "custom_hash_map.cpp"
#include "stock_entries.cpp"
using namespace std;

typedef CustomHashMap<string, StockEntries> buffer_dict;

// works perfectly
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

int min(int a, int b) {
  if(a > b) {
    return b;
  } else {
    return a;
  }
}

int max(int a, int b) {
  if(a > b) {
    return a;
  } else {
    return b;
  }
}

void print_buffers(buffer_dict& sell_buffer, buffer_dict& buy_buffer) {
  cout << "\t--- Sellers ---" << endl;

  for(auto& bucket : sell_buffer.table) {
    for(auto& entry : bucket) {
      Node* curr_node = entry.value.root;
      
      cout << "\t\t" << entry.key;
      while(curr_node) {
        cout << " --- {" << curr_node->data.broker_name << " $" << curr_node->data.price << " #" << curr_node->data.quantity << " " << 
        curr_node->data.time_of_entry << "}";
        curr_node = curr_node->next_node;
      }
      cout << endl;
    }
  }


  cout << "\t--- Buyers ---" << endl;
  
  for(auto& bucket : buy_buffer.table) {
    for(auto& entry : bucket) {
      Node* curr_node = entry.value.root;
      
      cout << "\t\t" << entry.key;
      while(curr_node) {
        cout << " --- {" << curr_node->data.broker_name << " $" << curr_node->data.price << " #" << curr_node->data.quantity << " " << 
        curr_node->data.time_of_entry << "}";
        curr_node = curr_node->next_node;
      }
      cout << endl;
    }
  }

}

void print_exchanges(vector<successful_exchange>& exchanges) {
  for(auto& exchange : exchanges) {
    cout << exchange.buyer_name << " purchased " << 
    exchange.num_shares << " shares of " << exchange.stock_name << " from " << 
    exchange.seller_name << " for $" << exchange.price_per_share << "/share\n";
  }
  cout << endl;
}

// EOD calculations
void eod(vector<successful_exchange>& exchanges) {
  int total_sum = 0;
  int num_trades = 0;
  int num_shares = 0;

  for(auto& exchange : exchanges) {
    total_sum += exchange.num_shares * exchange.price_per_share;
    num_shares += exchange.num_shares;
    num_trades++;
  }

  cout << "---End of Day---\n";
  cout << "Total Amount of Money Transferred: " << total_sum << endl;
  cout << "Number of Completed Trades: " << num_trades << endl;
  cout << "Number of Shares Traded: " << num_shares << endl;
}

void broker_wise_data(vector<successful_exchange>& exchanges) {
  CustomHashMap<string, vector<int>> brokers_buy;
  CustomHashMap<string, vector<int>> brokers_sell;

  for(auto& exchange : exchanges) {
    if(brokers_buy[exchange.buyer_name].empty()) {
      brokers_buy[exchange.buyer_name].push_back(exchange.num_shares);
      brokers_buy[exchange.buyer_name].push_back(exchange.num_shares * exchange.price_per_share);
      brokers_buy[exchange.buyer_name].push_back(0);
    } 
    else {
      brokers_buy[exchange.buyer_name][0] += exchange.num_shares;
      brokers_buy[exchange.buyer_name][1] += exchange.num_shares * exchange.price_per_share;
    }

    if(brokers_sell[exchange.seller_name].empty()) {
      brokers_sell[exchange.seller_name].push_back(exchange.num_shares);
      brokers_sell[exchange.seller_name].push_back(exchange.num_shares * exchange.price_per_share);
      brokers_sell[exchange.seller_name].push_back(0);
    } 
    else {
      brokers_sell[exchange.seller_name][0] += exchange.num_shares;
      brokers_sell[exchange.seller_name][1] += exchange.num_shares * exchange.price_per_share;
    }
  }

  for(auto& bucket : brokers_buy.table) {
    for(auto& pair : bucket) {
      int seller_qtty = 0;
      int seller_price = 0;

      if(!brokers_sell[pair.key].empty()) {
        seller_qtty = brokers_sell[pair.key][0];
        seller_price = brokers_sell[pair.key][1];
        brokers_sell[pair.key][2] = 1;
      }
    
      int net = -1 * pair.value[1] + seller_price;
      cout << pair.key << " bought " << pair.value[0] << 
      " and sold " << seller_qtty <<
      " for a net transfer of $" << net << endl;

      pair.value[2] = 1;
    }
  }

  for(auto& bucket : brokers_sell.table) {
    for(auto& pair : bucket) {
      if(pair.value.empty() != 0 || pair.value[2] == 1) {
        continue;
      }

      int seller_qtty = 0;
      int seller_price = 0;

      if(!brokers_buy[pair.key].empty()) {
        seller_qtty = brokers_buy[pair.key][0];
        seller_price = brokers_buy[pair.key][1];
      }
    
      int net = pair.value[1] - seller_price;
      cout << pair.key << " bought " << seller_qtty << 
      " and sold " << pair.value[0] <<
      " for a net transfer of $" << net << endl;
    }
  }
}