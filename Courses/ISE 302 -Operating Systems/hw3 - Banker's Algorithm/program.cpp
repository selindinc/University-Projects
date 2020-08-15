// Development environment: Lubuntu 18.04.1 LTS
// To compile: g++ -pthread -std=c++11 program.cpp -o hw3
// To run: ./hw3 new_request_process_id new_request_resource 
// Example: ./hw3 2 2

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

vector<int> IsSafe(vector<int> NowWorking, vector<int> MaxCapacity, int TotRes);

int main(int argc, char const **argv)
{
    ifstream fpointer(argv[1]);

    if (!fpointer.is_open())
    {
        cout << "ERROR: File is not Open" << '\n';
    }

    int new_request_process_id = atoi(argv[2]);
    int new_request_resource = atoi(argv[3]);
    string totResource; // number of total resources
    vector<int> NowWorking; //resources which are allocated to processors
    vector<int> MaxCapacity; // number of max resources which a processor can handle
 
    getline(fpointer, totResource, '\n');
    int TotRes = stoi(totResource);

    while (fpointer.good())
    {

        int s = 0;

        string PNowRes;
        getline(fpointer, PNowRes, ' ');
        int pNowRes = stoi(PNowRes);
        NowWorking.push_back(pNowRes);

        string PMaxRes;
        getline(fpointer, PMaxRes, '\n');
        int pMaxRes = stoi(PMaxRes);
        MaxCapacity.push_back(pMaxRes);

        s++;
    }

    vector<int> order2 = IsSafe(NowWorking, MaxCapacity, TotRes); //copy of order vector
    if (order2[0] == -1) // deadlock 
    {
        cout << "Not Safe" << endl;
        cout << "No order" << endl;
        cout << "The new request CANNOT be granted." << endl;
    }
    else //no deadlock 
    {
        cout << "Safe" << endl;
        cout << "A correct process execution order is: ";
        for (int o=0; o<order2.size();o++)
        {

            cout <<  order2[o] <<"->";
            
        }
        cout<<endl;
        NowWorking[new_request_process_id] += new_request_resource; 
        vector<int> order3 = IsSafe(NowWorking, MaxCapacity, TotRes); //copy of the order vector

        if (order3[0] == -1) //can be granted or not
        {
            cout << "The new request CANNOT be granted." << endl;
        }
        else
        {
            cout << "The new request CAN be granted." << endl;
        }
    }

    return 0;
}

vector<int> IsSafe(vector<int> NowWorking, vector<int> MaxCapacity, int TotRes) //check if the situation is safe
{

    vector<int> need; //number of needed resources for each processor
    int size = NowWorking.size();
    int a = 0;

    for (int s = 0; s < size; s++)//calculating number of needed resources for each processor
    {

        a = MaxCapacity[s] - NowWorking[s];
        need.push_back(a);
    }
    int count = 0;
    for (int c : NowWorking) //number of resources that allocated at start
    {
        count += c;
    }
    int Free = TotRes - count; // number of free resources

    int n = 0;

    vector<int> order; //order vector
    while (size > n)
    {
        if (need[n] != -1)
        {
            if (need[n] <= Free) 
            {
                Free = NowWorking[n] + Free;
                
                order.push_back(n);
                need[n] = -1;
                n = -1;
            }
        }
        n++;
    }


    if (Free == TotRes)
    {
        return order;
    }
    else
    {

        order.push_back(-1);
        return order;
    }
}