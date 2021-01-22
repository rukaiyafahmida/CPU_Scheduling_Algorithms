/*This code is for Shortest-Job-First algorithm code. It is designing to consider the arrival time of the processes as well. It is Non Preemptive.*/

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

bool byCpuTime(Processes a, Processes b)
{
    //will return true for lower time
    return a.cpuTime < b.cpuTime;

}

bool byStartTime(Processes a, Processes b)
{
    //will return true for lower time
    return a.startTime < b.startTime;

}

int main()
{
    int p,total=0;

    cout<<"Number of processes:";
    cin>>p;

    Processes a[p];

    //input
    for(int i=0; i<p; i++)
    {
        cin>> a[i].processNumber;
        cin>> a[i].arrivalTime;
        cin>> a[i].cpuTime;
        total+=a[i].cpuTime;
    }

    sort(a,a+p,byArrivalTime);
    //working for the first arrived task
    t+=a[0].cpuTime;
    a[0].endTime=t;
    sort(a,a+p,byCpuTime);
    total-=t;
    while(total!=0)
    {
        Processes b[p]; //declaring new process queue
        int k=0;

        //getting the arrived processes with in t in sorted by cputime
        for(int i=0; i<p; i++)
        {
            if(a[i].arrivalTime<=t && a[i].endTime==0)
            {
                b[k]=a[i];
                k++;
                sort(b,b+k,byCpuTime);
            }
        }
        //modifying the process in the original queue
            for(int j=0; j<p; j++)
            {
                if(b[0].processNumber == a[j].processNumber)
                {
                    a[j].startTime=t;
                    t+=a[j].cpuTime;
                    a[j].endTime=t;
                    total-=a[j].cpuTime;
                }
            }
    }

    sort(a,a+p,byStartTime);

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
