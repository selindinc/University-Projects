#include "car.h"
#include <string>
#include <iostream>
using namespace std;

Car :: Car(){

    id=0;
    mileage=0;
    price=0;
    year=0;
    city="";
    state="";
    vin="";
    make="";
    model="";
}
Car :: Car(int id,int mileage,int price, int year, string city,string state,string vin,string make,string model){
    this->id=id;
    this->mileage=mileage;
    this->price=price;
    this->year=year;
    this->city=city;
    this->state=state;
    this->vin=vin;
    this->make=make;
    this->model=model;

}
Car :: Car(const Car &c2){
    id=c2.id;
    mileage=c2.mileage;
    price=c2.price;
    year=c2.year;
    city=c2.city;
    state=c2.state;
    vin=c2.vin;
    make=c2.make;
    model=c2.model;

}
/*Car :: operator=(const Car& c){

    if(id=c.id){return 0;}
    mileage=c.mileage;
    price=c.price;
    year=c.year;
    city=c.city;
    state=c.state;
    vin=c.vin;
    make=c.make;
    model=c.model;

}*/

        
int Car :: getID(){ return id; }
int Car :: getMileage(){ return mileage; }
int Car :: getPrice(){ return price; }
int Car :: getYear(){ return year; }
string Car :: getCity(){ return city; }
string Car :: getState(){return state; }
string Car :: getVin(){ return vin; }
string Car :: getMake(){ return make; }
string Car :: getModel(){ return model; }