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
    int priority;
};

bool byArrivalTime(Processes a, Processes b)
{
    //will return true for lower time
    return a.arrivalTime < b.arrivalTime;

}

bool byPriority(Processes a, Processes b)
{
    //will return true for greater priority
    if(a.priority != b.priority)
    return a.priority < b.priority;
    else
    return a.arrivalTime < b.arrivalTime;

}

bool byStartTime(Processes a, Processes b)
{
    //will return true for lower time
    return a.startTime < b.startTime;

}

bool byProcessNumber(Processes a, Processes b)
{
    //will return true for lower time
    return a.processNumber < b.processNumber;

}

int main()
{
    int p,total=0;

    double waitTime=0,turnaroundTime=0;

    cout<<"Number of processes:";
    cin>>p;

    Processes a[p];

    //input
    for(int i=0; i<p; i++)
    {
        cin>> a[i].processNumber;
        cin>> a[i].arrivalTime;
        cin>> a[i].cpuTime;
        cin>> a[i].priority;
        total+=a[i].cpuTime;
    }

    sort(a,a+p,byArrivalTime);
    //working for the first arrived task
    t+=a[0].cpuTime;
    a[0].endTime=t;
    sort(a,a+p,byPriority);

    total-=t;
    while(total!=0)
    {
        Processes b[p]; //declaring new process queue
        int k=0;

        //getting the arrived processes with in t in sorted by priority
        for(int i=0; i<p; i++)
        {
            if(a[i].arrivalTime<=t && a[i].endTime==0)
            {
                b[k]=a[i];
                k++;
                sort(b,b+k,byPriority);
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
    cout<<endl;
    sort(a,a+p,byProcessNumber);
    cout<<endl;
    for(int i=0;i<p;i++)
    {
        double temp1= a[i].startTime - a[i].arrivalTime;
        waitTime+=temp1;
        double temp2=temp1+ a[i].cpuTime;
        turnaroundTime+=temp2;
        cout<<"P"<<a[i].processNumber<<" Waiting Time:"<< temp1 <<"   Turnaround Time:"<< temp2 <<endl;
    }
    cout<<"Average Waiting Time: "<< waitTime/p <<endl;
    cout<<"Average Turnaround Time: "<<  turnaroundTime/p <<endl;
    return 0;
}
