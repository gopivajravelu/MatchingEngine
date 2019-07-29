#include <iostream>
#include "OrderBook.h"

OrderBook::OrderBook(bool isBuy) :
  m_isBuy(isBuy)
{
}

OrderBook::~OrderBook()
{
  list<Order*>::iterator it     = m_orderBook.begin();
  list<Order*>::iterator it_end = m_orderBook.end();
  while(it != it_end)
  {
    if(*it)
      delete *it;
    ++it;
  }
  m_orderBook.clear();
};

void OrderBook::printOrderBook()
{
  list<Order*>::iterator it     = m_orderBook.begin();
  list<Order*>::iterator it_end = m_orderBook.end();
  while(it != it_end)
  {
    cout << "Side: " << (*it)->getSide() << " Qty: " << (*it)->getQty() << " Price: " << (*it)->getPrice() << endl;
    ++it;
  }
}

void OrderBook::addOrder(Order* newOrder)
{
  list<Order*>::iterator it     = m_orderBook.begin();
  list<Order*>::iterator it_end = m_orderBook.end();
  if(m_isBuy)
  {
    while(it != it_end)
    {
      if((*it)->getPrice() < newOrder->getPrice())
      {
        m_orderBook.insert(it,newOrder);
        return;
      }
      ++it;
    }
  }
  else
  {
    while(it != it_end)
    {
      if((*it)->getPrice() > newOrder->getPrice())
      {
        m_orderBook.insert(it,newOrder);
        return;
      }
      ++it;
    }
  }
  m_orderBook.push_back(newOrder);
}
