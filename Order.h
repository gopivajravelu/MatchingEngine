#ifndef ORDER_H
#define ORDER_H

#include <string>

using namespace std;

class Order
{
public:
  Order(const string& securityDesc, int qty, bool isBuy,
        int price, const string& orderNumber,
        const string& trader, const string& sessionName);
  ~Order();

  inline const string& getSecurityDesc() const { return m_securityDesc; };
  inline int getQty() const { return m_qty; };
  inline bool getSide() const { return m_isBuy; };
  inline int getPrice() const { return m_price; };

private:
  string    m_securityDesc;
  int       m_qty;
  bool      m_isBuy;
  int       m_price;
  string    m_orderNumber;
  string    m_trader;
  string    m_sessionName;
};

#endif