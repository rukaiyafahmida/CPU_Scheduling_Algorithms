#include <stdio.h>
#include <iostream>
#include <queue>
#include <algorithm>
#include<stdlib.h>
#include<string.h>

using namespace std;

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


int notChecked[100];
int main()
{
    memset(notChecked, 1, sizeof(notChecked)); //notChecked=1 if the process is untouched
    int p,quantum,total_time,gIndex=0;
    cout<<"Number of processes: ";
    cin>>p;
    cout<<"Quantum: ";
    cin>>quantum;

    Processes a[p];
    Processes b[p*p]; //printing array

    //input
    for(int i=0; i<p ; i++)
    {
        cin>> a[i].processNumber;
        cin>> a[i].arrivalTime;
        cin>> a[i].cpuTime;
    }

    sort(a, a + p, byArrivalTime);


    queue<int> q;
    q.push(0);         //index of the sorted queue
    notChecked[0] = 0;
    total_time = a[0].arrivalTime;

    while (!q.empty())
    {
        int process_no = q.front(); //index of the first sorted processes
        q.pop();                   //making the next process come in front
        int time_taken = min(quantum, a[process_no].cpuTime); //time given to the process

        //populating the printing array
        b[gIndex].processNumber= a[process_no].processNumber;
        b[gIndex].startTime=total_time;
        a[process_no].cpuTime -= min(quantum, a[process_no].cpuTime);
        total_time += time_taken;
        b[gIndex].endTime=total_time;
        gIndex++;


        for (int i = 0; i < p; i++)
        {
            if (a[i].arrivalTime <= total_time && notChecked[i]) //checking if there is any untouched process within the total_time
            {
                q.push(i);          //pushing that onto the queue and making it checked
                notChecked[i] = 0;
            }
        }
        if (a[process_no].cpuTime > 0)
        {
            q.push(process_no);    //then checking for processes whose burst>0 and pushing it
        }
        else{
            a[process_no].endTime= total_time;
        }
        if(q.empty())
        {
            for (int i = 0; i < p; ++i)    //checking if there will be any process in the further future and pushing it
            {
                if (notChecked[i])
                {
                    q.push(i);
                    notChecked[i] = 0;
                    total_time = a[i].arrivalTime;
                    break;
                }
            }
        }
    }


    //printing the result
    cout << endl<< "Gantt Chart" << endl;
    cout<<"|";
    for(int i=0; i<gIndex; i++)
    {
        cout<<"--P"<<b[i].processNumber<<"---|";
    }
    cout<<endl;

    cout<<b[0].startTime;
    for(int i=0; i<gIndex; i++)
    {
        cout<<"\t"<<b[i].endTime;
    }


    return 0;

}
