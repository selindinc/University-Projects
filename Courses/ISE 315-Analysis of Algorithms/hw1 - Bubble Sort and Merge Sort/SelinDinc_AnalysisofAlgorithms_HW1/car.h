#ifndef CAR_H
#define CAR_H
#include <string>
#include <iostream>

using namespace std;

class Car{
    public:
        Car();
        Car(int price,int mileage,int id, int year, string city,string state,string vin,string make,string model);
        Car(const Car &c2);
       
        
        int getID();
        int getMileage();
        int getPrice();
        int getYear();
        string getCity();
        string getState();
        string getVin();
        string getMake();
        string getModel();



    private:
        int price;
        int mileage;
        int id;
        int year;
        string city;
        string state;
        string vin;
        string make;
        string model;


};
#endif