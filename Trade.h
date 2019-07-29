#ifndef TRADE_H
#define TRADE_H

#include <string>

using namespace std;

class Trade
{
public:
  Trade(const string& securityDesc, int qty, double price,
        const string& buySideSession, const string& sellSideSession,
        const string& execId);
  ~Trade();

  void printTrade();

private:
  string    m_securityDesc;
  int       m_qty;
  double    m_price;
  string    m_buySideSession;
  string    m_sellSideSession;
  string    m_execId;
};

#endif
