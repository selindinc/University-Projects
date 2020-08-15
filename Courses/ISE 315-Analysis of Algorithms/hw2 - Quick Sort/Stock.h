#ifndef STOCK_H
#define STOCK_H
#include <string>
#include <iostream>

using namespace std;

class Stock{
    public:
        Stock();
        Stock(string timestamp,int instrument_token,double last_price,string rest);
        Stock(const Stock &s2);
       
        
        string getTimestamp();
        int getInstToken();
        double getLastPrice();
        string getRest();


    private:
        string timestamp;
        double last_price;
        int instrument_token;
        string rest;
};
#endif