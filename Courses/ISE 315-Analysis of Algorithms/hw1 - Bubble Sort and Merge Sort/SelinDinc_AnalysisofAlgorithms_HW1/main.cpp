#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include "car.h"
#include "stdlib.h"
#include <ctime>
using namespace std;

void BubbleSort(vector<Car>& cars,char feature);
vector<Car> Merge(vector<Car> left,vector<Car> right,char feature);
vector<Car> MergeSort(vector<Car> cars, char feature);
void writeToFile(vector<Car> cars,string headline);

main(int argc, char const **argv)
{
    ifstream fpointer("tc20171021.csv");

    if(!fpointer.is_open()){ cout << "ERROR: File is not Open" << '\n';}
    
    int N=atoi(argv[6]);
    char algo=*argv[2];
    char feature=*argv[4]; 
    vector<Car> cars;
    string price;
    string mileage;
    string id;
    string year;
    string city;
    string state;
    string vin;
    string make;
    string model;
    string headline;
   
    
    getline(fpointer,headline,'\n');
    

    while(fpointer.good() && N>0 ){

        
        getline(fpointer,id,',');
        int aId = atoi(id.c_str());
        getline(fpointer,price,',');
        int aPrice = atoi(price.c_str());
        getline(fpointer,year,',');
        int aYear = atoi(year.c_str());
        getline(fpointer,mileage,',');
        int aMile = atoi(mileage.c_str());
        getline(fpointer,city,',');
        getline(fpointer,state,',');
        getline(fpointer,vin,',');
        getline(fpointer,make,',');
        getline(fpointer,model,'\n');
        N--;
        Car c = Car(aId,aMile,aPrice,aYear,city, state, vin, make, model);//create objects
        cars.push_back(c);
    
    }
    clock_t ticks;
     
    if(algo=='b'){
        
        ticks=clock();
        BubbleSort(cars,feature);
        ticks=clock()-ticks;
        float seconds=(float)ticks/CLOCKS_PER_SEC;
        cout<<"time for bubble sort:"<<" "<<seconds<<endl;
        writeToFile(cars,headline);
       
    }

    if(algo=='m'){
        ticks=clock();
        vector<Car> tempE=MergeSort(cars,feature);
        ticks=clock()-ticks;
        float seconds=(float)ticks/CLOCKS_PER_SEC;
        cout<<"time for merge sort:"<<" "<<seconds<<endl;
        writeToFile(tempE,headline);
    }
    
    return 0;
}
void BubbleSort(vector<Car> &cars,char feature){
    int i,j;
    for(i=0;i<cars.size()-1;i++){
        for(j=0;j<cars.size()-i-1;j++){
            if(feature=='p'){
                if((cars[j].getPrice())>(cars[j+1].getPrice())){
                    Car temp1=Car(cars[j]);
                    Car temp2=Car(cars[j+1]);
                    cars[j+1]=temp1;
                    cars[j]=temp2;
                }
            }
            if(feature=='m'){
                if((cars[j].getMileage())>(cars[j+1].getMileage())){
                    Car temp1=Car(cars[j]);
                    Car temp2=Car(cars[j+1]);
                    cars[j+1]=temp1;
                    cars[j]=temp2;
                } 
            }
            
        }
    }

}

vector<Car> MergeSort(vector<Car> cars,char feature){
    int sizeV=cars.size();
    if(sizeV<2){  return cars; }
    int m=sizeV/2;
    vector<Car> left;
    vector<Car> right;
    
    for(int i=0;i<m;i++){
       left.push_back(cars[i]);

    }
    for(int i=m;i<=sizeV-1;i++){
        right.push_back(cars[i]);
        
    }
    vector<Car>tempL=MergeSort(left,feature);
    vector<Car>tempR=MergeSort(right,feature);
    
    
    vector<Car> tempC=Merge(tempL,tempR,feature);
    return tempC;


}

vector<Car> Merge(vector<Car> left,vector<Car> right,char feature){
    int sizeL=left.size();
    int sizeR=right.size();
    int i=0;
    int j=0;
    vector<Car> tempD;

    while(i<sizeL && j<sizeR){
        if(feature=='p'){
            if(left[i].getPrice()<=right[j].getPrice()){
                tempD.push_back(left[i]);
                i++;
            }
            else{
                tempD.push_back(right[j]);
                j++;
            }

        }
         if(feature=='m'){
            if(left[i].getMileage()<=right[j].getMileage()){
                tempD.push_back(left[i]);
                i++;
            }
            else{
                tempD.push_back(right[j]);
                j++;
            }
        }
        

    }
    while(i<sizeL){
        if(feature=='p'){
                tempD.push_back(left[i]);
                i++;
        }
            
        if(feature=='m'){
                tempD.push_back(left[i]);
                i++;
        }

    }
    while(j<sizeR){
        if(feature=='p'){
                tempD.push_back(right[j]);
                j++;
        }
        if(feature=='m'){
                tempD.push_back(right[j]);
                j++;
        }

    }
    return tempD;

}
void writeToFile(vector<Car> cars,string headline){

    ofstream fp;
    fp.open("sorted.csv");
    fp<<headline<<"\n";
    int vsize=cars.size();
    int i=0;
    while(vsize>0){
        fp<<cars[i].getID()<<",";
        fp<<cars[i].getPrice()<<",";
        fp<<cars[i].getYear()<<",";
        fp<<cars[i].getMileage()<<",";
        fp<<cars[i].getCity()<<",";
        fp<<cars[i].getState()<<",";
        fp<<cars[i].getVin()<<",";
        fp<<cars[i].getMake()<<",";
        fp<<cars[i].getModel()<<"\n";
        i++;
        vsize--;
    }   
}








