#include <iostream>
#include "MatchingEngine.h"

using namespace std;

int main() {
  cout << "Starting matching engine" << endl;
  MatchingEngine* engine = new MatchingEngine();

  Order* order1 = new Order("GEZ9",1,true,9950,"0001","TEST1","FIRM1");
  Order* order2 = new Order("GEZ9",1,false,9951,"0002","TEST2","FIRM2");
  Order* order3 = new Order("GEZ9",1,true,9948,"0003","TEST1","FIRM1");
  Order* order4 = new Order("GEZ9",1,true,9949,"0004","TEST1","FIRM1");
  Order* order5 = new Order("GEZ9",2,true,9950,"0005","TEST1","FIRM1");
  Order* order6 = new Order("GEH0",2,false,9925,"0006","TEST2","FIRM2");
  Order* order7 = new Order("GEZ9",5,false,9951,"0007","TEST2","FIRM2");
  Order* order8 = new Order("GEZ9",1,false,9953,"0008","TEST2","FIRM2");
  Order* order9 = new Order("GEZ9",1,false,9952,"0009","TEST2","FIRM2");
  Order* order10 = new Order("GEZ9",1,false,9950,"0010","TEST2","FIRM2");
  Order* order11 = new Order("GEZ9",2,false,9947,"0011","TEST2","FIRM2");
  engine->addOrder(order1);
  engine->addOrder(order2);
  engine->addOrder(order3);
  engine->addOrder(order4);
  engine->addOrder(order5);
  engine->addOrder(order6);
  engine->addOrder(order7);
  engine->addOrder(order8);
  engine->addOrder(order9);
  engine->printOrders();

  engine->cancelOrder(order8);
  engine->cancelOrder(order6);
  engine->cancelOrder(order5);
  engine->printOrders();


  engine->addOrder(order10);
  engine->addOrder(order11);
  engine->printOrders();
  engine->printTrades();

  if(engine)
    delete engine;
  cout << "Stopping matching engine" << endl;
  return 0;
}
