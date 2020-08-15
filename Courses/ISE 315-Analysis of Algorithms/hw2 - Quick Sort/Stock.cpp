#include "Stock.h"
#include <string>
#include <iostream>
using namespace std;

Stock :: Stock(){

    last_price=0.0;
    instrument_token=0;
    timestamp="";
    rest="";

}
Stock :: Stock(string timestamp,int instrument_token,double last_price,string rest){
    this->timestamp=timestamp;
    this->instrument_token=instrument_token;
    this->last_price=last_price;
    this->rest=rest;

}
Stock :: Stock(const Stock &s2){
    timestamp=s2.timestamp;
    instrument_token=s2.instrument_token;
    last_price=s2.last_price;
    rest=s2.rest;

}
   
string Stock :: getTimestamp(){ return timestamp; }
int Stock :: getInstToken(){ return instrument_token; }
double Stock :: getLastPrice(){ return last_price; }
string Stock :: getRest(){ return rest; }