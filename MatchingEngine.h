#ifndef MATCHING_ENGINE_H
#define MATCHING_ENGINE_H

#include <map>
#include "OrderBook.h"

using namespace std;

class MatchingEngine
{
public:
  MatchingEngine();
  ~MatchingEngine();

  void printOrders();

  void addOrder(Order* order);
  void cancelOrder(Order* order);

private:
  map<string,OrderBook*>      m_buyOrderBookMap;
  map<string,OrderBook*>      m_sellOrderBookMap;
};

#endif
