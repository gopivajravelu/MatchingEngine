#include "Order.h"

Order::Order(const string& securityDesc, int qty, bool isBuy,
             int price, const string& orderNumber,
             const string& trader, const string& sessionName) :
  m_securityDesc(securityDesc)
, m_qty(qty)
, m_isBuy(isBuy)
, m_price(price)
, m_orderNumber(orderNumber)
, m_trader(trader)
, m_sessionName(sessionName)
{
}

Order::~Order()
{
};
