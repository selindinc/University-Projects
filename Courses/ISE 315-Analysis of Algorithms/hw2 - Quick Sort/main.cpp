#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include "Stock.h"
#include "stdlib.h"
#include <ctime>
#include <algorithm>
using namespace std;

void QuickSort(vector<Stock> &data,int low, int high,char feature);

int partition(vector<Stock> &data,int low,int high,char feature);

void writeToFile(vector<Stock> &data,string headline);

main(int argc, char const **argv)
{
    ifstream fpointer("log_inf.csv");

    if(!fpointer.is_open()){ cout << "ERROR: File is not Open" << '\n';}
    
    int N=atoi(argv[4]);
    char feature=*argv[2]; 
    vector<Stock> data;
    string timestamp;
    string instrument_token;
    string last_price;
    string headline;
    string rest;

    getline(fpointer,headline,'\n');
    

    while(fpointer.good() && N>0 ){

        
        getline(fpointer,timestamp,',');
        getline(fpointer,instrument_token,',');
        int aInstrumentToken = atoi(instrument_token.c_str());
        getline(fpointer,last_price,',');
        int aLastPrice = atof(last_price.c_str());
        getline(fpointer,rest,'\n');

        N--;
        Stock s = Stock(timestamp,aInstrumentToken,aLastPrice,rest);//create objects
        data.push_back(s);
    
    }
    clock_t ticks;
    random_shuffle(data.begin(),data.end());
    ticks=clock();
    QuickSort(data,0,data.size()-1,feature);
    ticks=clock()-ticks;
    float seconds=(float)ticks/CLOCKS_PER_SEC;
    cout<<"Time for QuickSort:"<<" "<<seconds<<endl;
    writeToFile(data,headline); 

    
    return 0;
}

void QuickSort(vector<Stock> &data,int low, int high,char feature){
    if(low<high){
        int pi=partition(data,low,high,feature);
        QuickSort(data,low,pi-1,feature);
        QuickSort(data,pi+1,high,feature);
    }
}
int partition(vector<Stock> &data,int low,int high,char feature){
    Stock pivot = data.at(high); 
    int i=(low-1);//index of smaller element

    if(feature=='t'){
        for(int s=low;s<=high-1;s++){
            if(data[s].getTimestamp().compare(pivot.getTimestamp())<0){
                i++;
                Stock temp1= Stock(data.at(i));
                Stock temp2 = Stock(data.at(s));
                data.at(s)=temp1;
                data.at(i)=temp2;
            }
        }
        Stock tempa=Stock(data.at(i+1));
        Stock tempb=Stock(data.at(high));
        data.at(high)=tempa;
        data.at(i+1)=tempb;
        return i+1;
    }
    if(feature='p'){
        for(int s=low;s<=high-1;s++){
            if(data[s].getLastPrice()<=pivot.getLastPrice()){
                i++;
                Stock temp1= Stock(data.at(i));
                Stock temp2 = Stock(data.at(s));
                data.at(s)=temp1;
                data.at(i)=temp2;
            }
        }
        Stock tempa=Stock(data.at(i+1));
        Stock tempb=Stock(data.at(high));
        data.at(high)=tempa;
        data.at(i+1)=tempb;
        return i+1;
    }
}
void writeToFile(vector<Stock> &data,string headline){

    ofstream fp;
    fp.open("sorted.csv");
    fp<<headline<<"\n";
    int vsize=data.size();
    int i=0;
    while(vsize>0){
        fp<<data[i].getTimestamp()<<",";
        fp<<data[i].getInstToken()<<",";
        fp<<data[i].getLastPrice()<<",";
        fp<<data[i].getRest()<<"\n";
        i++;
        vsize--;
    }   
}
