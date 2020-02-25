#include<bits/stdc++.h>

using namespace std;

struct proc{
        int id;
        int arrival;
        int burst;
        int queue;
        int start;
        int left;
        int end;
};

void sortqueue(vector<proc> &rq){
        for(int i=0;i<rq.size();i++){
                for(int j=i+1;j<rq.size();j++){
                        if(rq[i].arrival<rq[j].arrival){
                                proc p=rq[j];
                                rq[j]=rq[i];
                                rq[i]=p;
                        }
                }
        }
}


void displayinitial(vector<proc> fore, vector<proc> back){
        cout<<"Foreground: \n";
        cout<<"\nID\tArrival\tBurst\n";
        for(int i=0;i<fore.size();i++){
                cout<<fore[i].id<<"\t"<<fore[i].arrival<<"\t"<<fore[i].burst<<endl;
        }
        cout<<"Background: \n";
        cout<<"\nID\tArrival\tBurst\n";
        for(int i=0;i<back.size();i++){
                cout<<back[i].id<<"\t"<<back[i].arrival<<"\t"<<back[i].burst<<endl;
        }
}

void getproc(int n, vector<proc> &fore, vector<proc> &back){
        cout<<"Enter process details as [ Queue Arrival Burst ]\n";
        int queue,arrival,burst;
        for(int i=0;i<n;i++){
                proc p;
                p.id=i;
                cin>>queue>>arrival>>burst;
                p.queue=queue;
                p.arrival=arrival;
                p.burst=burst;
                p.start=-1;
                p.end=-1;
                p.left=p.burst;
                if(p.queue==0)
                        fore.push_back(p);
                else
                        back.push_back(p);
        }
        displayinitial(fore,back);
        sortqueue(fore);
        sortqueue(back);
}

void schedule(vector<proc> &fore, vector<proc> &back, vector<proc> &order){
        int time=0;
        int fs=fore.size();
        int bs=back.size();
        while(fs!=0 || bs!=0){
                if(fs!=0 && fore[fs-1].arrival <= time){
                        fore[fs-1].start=time;
                        fore[fs-1].end=time+fore[fs-1].burst;
                        time+=fore[fs-1].burst;
                        order.push_back(fore[fs-1]);
                        fore.pop_back();
                        fs--;
                }
                else if(bs!=0 && back[bs-1].arrival <=time){
                        if(back[bs-1].start==-1) back[bs-1].start=time;
                        back[bs-1].left--;
                        time++;
                        if(back[bs-1].left==0){
                                back[bs-1].end=time;
                                order.push_back(back[bs-1]);
                                back.pop_back();
                                bs--;
                        }
                }
                else time++;
        }
}

void displayfinal(vector<proc> order){
        cout<<"\nID\tQueue\tStart\tEnd\n";
        for(int i=0;i<order.size();i++){
                if(order[i].queue==0)
                        cout<<order[i].id<<"\tF\t"<<order[i].start<<"\t"<<order[i].end<<endl;
                else
                        cout<<order[i].id<<"\tB\t"<<order[i].start<<"\t"<<order[i].end<<endl;
        }
}

void avgtimes(vector<proc> order){
        int twt=0,ttt=0;
        for(int i=0;i<order.size();i++){
                int tt=order[i].end-order[i].arrival;
                int wt=tt-order[i].burst;
                twt+=wt;
                ttt+=tt;
        }
        float avtt=(float)ttt/order.size();
        float avwt=(float)twt/order.size();
        cout<<"\nAverage waiting time: "<<avwt<<"\nAverage turnaround time: "<<avtt<<endl;
}

int main(){
        int n;
        vector<proc> fore,back,order;
        cout<<"Enter number of processes: ";
        cin>>n;
        getproc(n,fore,back);
        schedule(fore,back,order);
        displayfinal(order);
        avgtimes(order);
        return 0;
}
