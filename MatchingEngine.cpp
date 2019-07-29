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

  vector<Trade*>::iterator tradeIt     = m_trades.begin();
  vector<Trade*>::iterator tradeIt_end = m_trades.end();
  while(tradeIt != tradeIt_end)
  {
    if(*tradeIt)
      delete *tradeIt;
    ++tradeIt;
  }
};

void MatchingEngine::printOrders()
{
  cout << "Print orders" << endl;
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

void MatchingEngine::printTrades()
{
  cout << "Print trades" << endl;
  vector<Trade*>::iterator tradeIt     = m_trades.begin();
  vector<Trade*>::iterator tradeIt_end = m_trades.end();
  while(tradeIt != tradeIt_end)
  {
    (*tradeIt)->printTrade();
    ++tradeIt;
  }
}

void MatchingEngine::addOrder(Order* order)
{
  checkForTrade(order);

  if(order->getQty() > 0)
  {
    map<string,OrderBook*>& sideMap = order->getSide() ? m_buyOrderBookMap : m_sellOrderBookMap;

    map<string,OrderBook*>::iterator it = sideMap.find(order->getSecurityDesc());
    if(it == sideMap.end())
    {
      OrderBook* book = new OrderBook(order->getSide());
      sideMap[order->getSecurityDesc()] = book;
      book->addOrder(order);
    }
    else
      it->second->addOrder(order);
  }
}

void MatchingEngine::cancelOrder(Order* order)
{
  map<string,OrderBook*>& sideMap = order->getSide() ? m_buyOrderBookMap : m_sellOrderBookMap;
  map<string,OrderBook*>::iterator it = sideMap.find(order->getSecurityDesc());
  if(it != sideMap.end())
    it->second->cancelOrder(order);
}

bool MatchingEngine::checkForTrade(Order* order)
{
  map<string,OrderBook*>& oppositeSideMap = order->getSide() ? m_sellOrderBookMap : m_buyOrderBookMap;
  map<string,OrderBook*>::iterator it = oppositeSideMap.find(order->getSecurityDesc());
  if(it != oppositeSideMap.end())
  {
    if(!order->getSide())
    {
      while(order->getQty() > 0 &&
            it->second->getTopOfBook()->getPrice() >= order->getPrice())
      {
        Order* firstBuy = it->second->getTopOfBook();
        if(firstBuy->getQty() <= order->getQty())
        {
          Trade* trade = new Trade(order->getSecurityDesc(),firstBuy->getQty(),
              order->getPrice(),firstBuy->getSessionName(),
              order->getSessionName(),"ExecId:ToDo");
          m_trades.push_back(trade);
          order->setQty(order->getQty()-firstBuy->getQty());
          firstBuy->setQty(0);
          it->second->cancelOrder(firstBuy);
        }
        else
        {
          Trade* trade = new Trade(order->getSecurityDesc(),order->getQty(),
              order->getPrice(),firstBuy->getSessionName(),
              order->getSessionName(),"ExecId:ToDo");
          m_trades.push_back(trade);
          firstBuy->setQty(firstBuy->getQty()-order->getQty());
          order->setQty(0);
        }
      }
    }
    else
    {
      while(order->getQty() > 0 &&
            it->second->getTopOfBook()->getPrice() <= order->getPrice())
      {
        Order* firstSell = it->second->getTopOfBook();
        if(firstSell->getQty() <= order->getQty())
        {
          Trade* trade = new Trade(order->getSecurityDesc(),firstSell->getQty(),
              order->getPrice(),order->getSessionName(),
              firstSell->getSessionName(),"ExecId:ToDo");
          m_trades.push_back(trade);
          order->setQty(order->getQty()-firstSell->getQty());
          firstSell->setQty(0);
          it->second->cancelOrder(firstSell);
        }
        else
        {
          Trade* trade = new Trade(order->getSecurityDesc(),order->getQty(),
              order->getPrice(),order->getSessionName(),
              firstSell->getSessionName(),"ExecId:ToDo");
          m_trades.push_back(trade);
          firstSell->setQty(firstSell->getQty()-order->getQty());
          order->setQty(0);
        }
      }
    }
  }
  return false;
}
