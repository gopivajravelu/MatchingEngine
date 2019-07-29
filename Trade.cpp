#include <iostream>
#include "Trade.h"

Trade::Trade(const string& securityDesc, int qty, double price,
             const string& buySideSession, const string& sellSideSession,
             const string& execId) :
  m_securityDesc(securityDesc)
, m_qty(qty)
, m_price(price)
, m_buySideSession(buySideSession)
, m_sellSideSession(sellSideSession)
, m_execId(execId)
{
}

Trade::~Trade()
{
};

void Trade::printTrade()
{
  cout << "SecurityDesc: " << m_securityDesc << " Qty: " << m_qty << " Price: " << m_price << endl;
}
