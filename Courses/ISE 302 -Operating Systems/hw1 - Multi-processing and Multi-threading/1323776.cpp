// Development environment: Lubuntu 18.04.1 LTS
// To compile: g++ -pthread -std=c++11 Homework1.cpp -o Homework1
// To run: ./program interval_min interval_max np nt
// Example: ./program 20 139 2 2

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
using namespace std;

void findPrime(vector<int>& nums);


main(int argc, char const **argv)
{
    
    int interval_min = atoi(argv[1]);
    int interval_max = atoi(argv[2]);
    int np = atoi(argv[3]);
    int nt = atoi(argv[4]);

    vector<vector<int>> nums;//degistir
    
    vector<thread> threads;
    vector<int> vec;

    pid_t PID = 0;
    int status;

    int numOfDivide=np*nt;
    int intervalSize=interval_max-interval_min+1;
    int threadIntervalSize= intervalSize/numOfDivide;
    int remain = intervalSize%numOfDivide;
    int k=1;
    cout<<"Master: Started."<<endl;
    for(int s=0;s<=intervalSize;s+=threadIntervalSize){
        int e = interval_min+threadIntervalSize-1;
        if(k==numOfDivide){
            for(int i=s;i<s+threadIntervalSize+remain;i++){
                vec.push_back(i+interval_min);
            }
        }
        else{   
            for(int i=s;i<s+threadIntervalSize;i++){
                vec.push_back(i+interval_min);
            }
        }
        nums.push_back(vec);
        
        vec.clear();
        
        k++;
    }
    for(int i=0; i<np;i++){
        PID=fork();
        if(PID==-1){
            cout<<"Error!"<<endl;
            return -1;
        }
        else if(PID==0){
            vector<int> a = nums.at(i*nt);
            cout<<"Slave "<<i+1<<": Started. Interval "<< a.at(0)<<"-";
            a=nums.at(i*nt+1);
            cout<< a.at(a.size()-1) <<endl;

            for(int j=0;j<nt;j++){
                a=nums.at(i*nt+j);
                cout<<"Thread "<<i+1<<"."<<j+1<<": searching in "<< a.at(0)<<"-"<<a.at(a.size()-1)<<endl;
                threads.push_back(thread(findPrime,ref(nums.at(i*nt+j))));
                threads.at(j).join();
            }
            cout<<"Slave "<<i+1<<":Done. Prime numbers are: ";
            vector<int> v;
            for(int x=i*nt; x<i*nt+2;x++){
                v = nums.at(x);
                for(int y=0;y<v.size();y++){
                    if (v.at(y)!= -1 && v.at(y)!=0)
                    cout<<v.at(y)<<",";
                }
            }
            cout<<endl;
            exit(0);
        }
        else {
            wait(&status);
            wait(&status);
        }
    }
    cout<<"Master: Done."<<endl;
    return 0;
}

void findPrime(vector<int>& nums){
    int vecSize = nums.size();

    for(int j=0; j<vecSize;j++){
        for(int i=2; i<=nums[j]/2;i++){
            if(nums[j]%i==0){
                nums[j]=-1;
                break;
            }
        }
    }
    return ;
}