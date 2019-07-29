#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <list>
#include "Order.h"

using namespace std;

class OrderBook
{
public:
  OrderBook(bool isBuy);
  ~OrderBook();

  void printOrderBook();

  void addOrder(Order* newOrder);

private:
  bool            m_isBuy;
  list<Order*>    m_orderBook;
};

#endif
