#include <iostream>
#include "MatchingEngine.h"

MatchingEngine::MatchingEngine()
{
}

MatchingEngine::~MatchingEngine()
{
  map<string,OrderBook*>::iterator buyIt     = m_buyOrderBookMap.begin();
  map<string,OrderBook*>::iterator buyIt_end = m_buyOrderBookMap.end();
  while(buyIt != buyIt_end)
  {
    if(buyIt->second)
      delete buyIt->second;
    ++buyIt;
  }
  m_buyOrderBookMap.clear();

  map<string,OrderBook*>::iterator sellIt     = m_sellOrderBookMap.begin();
  map<string,OrderBook*>::iterator sellIt_end = m_sellOrderBookMap.end();
  while(sellIt != sellIt_end)
  {
    if(sellIt->second)
      delete sellIt->second;
    ++sellIt;
  }
  m_sellOrderBookMap.clear();
};

void MatchingEngine::printOrders()
{
  map<string,OrderBook*>::iterator buyIt     = m_buyOrderBookMap.begin();
  map<string,OrderBook*>::iterator buyIt_end = m_buyOrderBookMap.end();
  while(buyIt != buyIt_end)
  {
    cout << "SecurityDesc: " << buyIt->first << endl;
    buyIt->second->printOrderBook();
    ++buyIt;
  }
  map<string,OrderBook*>::iterator sellIt     = m_sellOrderBookMap.begin();
  map<string,OrderBook*>::iterator sellIt_end = m_sellOrderBookMap.end();
  while(sellIt != sellIt_end)
  {
    cout << "SecurityDesc: " << sellIt->first << endl;
    sellIt->second->printOrderBook();
    ++sellIt;
  }
}

void MatchingEngine::addOrder(Order* newOrder)
{
  map<string,OrderBook*>& sideMap = newOrder->getSide() ? m_buyOrderBookMap : m_sellOrderBookMap;

  map<string,OrderBook*>::iterator it = sideMap.find(newOrder->getSecurityDesc());
  if(it == sideMap.end())
  {
    OrderBook* book = new OrderBook(newOrder->getSide());
    sideMap[newOrder->getSecurityDesc()] = book;
    book->addOrder(newOrder);
  }
  else
    it->second->addOrder(newOrder);
}
