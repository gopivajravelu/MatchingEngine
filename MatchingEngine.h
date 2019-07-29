#ifndef MATCHING_ENGINE_H
#define MATCHING_ENGINE_H

#include <map>
#include <vector>
#include "OrderBook.h"
#include "Trade.h"

using namespace std;

class MatchingEngine
{
public:
  MatchingEngine();
  ~MatchingEngine();

  void printOrders();
  void printTrades();

  void addOrder(Order* order);
  void cancelOrder(Order* order);
  bool checkForTrade(Order* order);

private:
  map<string,OrderBook*>      m_buyOrderBookMap;
  map<string,OrderBook*>      m_sellOrderBookMap;
  vector<Trade*>              m_trades;
};

#endif
