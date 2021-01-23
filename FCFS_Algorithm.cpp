#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;
int t=0; //time passing

struct Processes
{
    int processNumber;
    int arrivalTime;
    int cpuTime;
    int startTime=0;
    int endTime=0;
};

bool byArrivalTime(Processes a, Processes b)
{
    //will return true for lower time
    return a.arrivalTime < b.arrivalTime;

}

int main()
{
    int p;

    cout<<"Number of processes:";
    cin>>p;

    Processes a[p];

    //input
    for(int i=0; i<p; i++)
    {
        cin>> a[i].processNumber;
        cin>> a[i].arrivalTime;
        cin>> a[i].cpuTime;
    }

    sort(a,a+p,byArrivalTime);
    //working for the first arrived task
    t+=a[0].cpuTime;
    a[0].endTime=t;

   //modifying the process in the  queue
            for(int j=1; j<p; j++)
            {
                {
                    a[j].startTime=t;
                    t+=a[j].cpuTime;
                    a[j].endTime=t;
                }
            }

    //printing the result
    cout<<"|";
    for(int i=0; i<p; i++)
    {
        cout<<"------P"<<a[i].processNumber<<"-------|";
    }
    cout<<endl;

    cout<<a[0].startTime;
    for(int i=0; i<p; i++)
    {
        cout<<"\t\t"<<a[i].endTime;
    }

    return 0;
}
