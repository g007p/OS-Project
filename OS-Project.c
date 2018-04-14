#include <iostream>
using namespace std;

struct process{
    int p_id;
    int bTime;
    int tt_time;
    int tTime=0;
};

struct line{
    int prio_st;
    int prio_end;
    int tTime=0;
    int len = 0;
    process *p;
    bool exc = false;
};

bool fun1(line q[]){
    bool a=false;
    int Flag=0;
        for(int i=0;i<3;i++){
                Flag=0;
            for(int j=0;j<q[i].len;j++){
                if(q[i].p[j].bTime != 0){
                    a=true;
                }
                else{
                    Flag+=1;
                }
            }
            if(Flag==q[i].len){

                q[i].exc = true;
            }
        }
        return a;
}



void bucket(line q){
   
    for(int i=1;i<q.len;i++){
        for(int j=0;j<q.len-1;j++){
            if(q.p[j].p_id<q.p[j+1].p_id){
                process temp = q.p[j+1];
                q.p[j+1] = q.p[j];
                q.p[j] = temp;
            }
        }
    }
}


void timing(line q[]){
    bool a = fun1(q);
    for(int i=0;i<3;i++){
        if(q[i].exc==false){
            for(int j=0;j<q[i].len;j++){
                if(q[i].p[j].bTime!=0){
                    q[i].p[j].tTime+=1;
                }
            }
            q[i].tTime+=1;
        }
    }
}

main(){

 
    line q[3];
    q[0].prio_st = 7;
    q[0].prio_end = 9;
    q[1].prio_st = 4;
    q[1].prio_end = 6;
    q[2].prio_st = 1;
    q[2].prio_end = 3;

    int num,checkPrio,bTime_of_process;
    
    cout<<"Enter the number of processes\n";
    cin>>num;
    process p1[num];

    for(int i=0;i<num;i++){
        cout<<"Enter the p_id of the process\n";
        cin>>checkPrio;
        cout<<"Enter the burst time of the process\n";
        cin>>bTime_of_process;
        p1[i].p_id = checkPrio;
        p1[i].bTime = bTime_of_process;
        p1[i].tt_time = bTime_of_process;
        for(int j=0;j<3;j++){
        if(q[j].prio_st<=checkPrio && checkPrio<=q[j].prio_end){
            q[j].len++;
        }
        }
    }

    for(int i =0;i<3;i++){
        int len = q[i].len;
        q[i].p = new process[len];
    }


    int a=0;
    int b=0;
    int c=0;

    for(int i =0;i<3;i++){
        for(int j=0;j<num;j++){
            if((q[i].prio_st<=p1[j].p_id) && (p1[j].p_id<=q[i].prio_end)){
                if(i==0){
                    q[i].p[a++] = p1[j];

                    }
                else if(i==1){
                    q[i].p[b++] = p1[j];
                    }
                else{
                    q[i].p[c++] = p1[j];
                    }
            }
        }
    }

    a--;b--;c--;
    for(int i=0;i<3;i++){
        cout<<"Queue "<<i+1<<" : \t";
        for(int j=0;j<q[i].len;j++){
            cout<<q[i].p[j].p_id<<"->";
        }
        cout<<"NULL\n";
    }


  
    int timer = 10;
    int l =-1;
    while(fun1(q)){
        if(timer == 10){
            l+=1;
            if(l>=3){
                l=l%3;
            }
            timer = 0;
        }

        if(q[l].exc == true){
                cout<<"Queue "<<l+1<<" completed\n";
            l+=1;
            if(l>=3){
                l=l%3;
            }
            continue;
        }

        
        if(l==0){
            cout<<"Queue "<<l+1<<" in hand\n";
            
            int rr_timer = 4;
            for(int i=0;i<q[l].len;i++){
                if(q[l].p[i].bTime==0){
                        continue;
                }
                while(rr_timer>0 && q[l].p[i].bTime!=0 && timer!=10){
                    cout<<"Executing queue 1 and "<<i+1<<" process for a unit time. Process has prio of "<<q[l].p[i].p_id<<"\n";
                    q[l].p[i].bTime--;
                    timing(q);
                    rr_timer--;
                    timer++;
                    cout<<l<<"\t"<<timer<<endl;
                }
                if(timer == 10){
                    break;
                }
                if(q[l].p[i].bTime==0){
                    continue;
                }
                if(rr_timer <= 0){
                    rr_timer = 4;
                    if(i == (q[i].len-1)){
                        i=-1;
                    }
                    continue;
                }

            }
        }


        else if(l==1){
            cout<<"Queue "<<l+1<<" in hand\n";
            bucket(q[l]);
        
            for(int i=0;i<q[l].len;i++){
                if(q[l].p[i].bTime==0){
                        continue;
                }
                while(q[l].p[i].bTime!=0 && timer!=10){
                    cout<<"Executing queue 2 and "<<i+1<<" process for a unit time. Process has prio of "<<q[l].p[i].p_id<<"\n";
                    q[l].p[i].bTime--;
                    timing(q);
                    timer++;
                    cout<<l<<"\t"<<timer<<endl;
                }
                if(timer == 10){
                    break;
                }
                if(q[l].p[i].bTime==0){
                        continue;
                }

            }
        }
        else{
            cout<<"Queue "<<l+1<<" in hand\n";
            //FCFS
            for(int i=0;i<q[l].len;i++){
                if(q[l].p[i].bTime==0){
                        continue;
                }
                while(q[l].p[i].bTime!=0 && timer!=10){
                    cout<<"Executing queue 3 and "<<i+1<<" process for a unit time. Process has priority of "<<q[l].p[i].p_id<<"\n";
                    q[l].p[i].bTime--;
                    timing(q);

                    timer++;
                }
                if(timer == 10){
                    break;
                }
                if(q[l].p[i].bTime==0){
                        continue;
                }

            }

        }
        cout<<"Queue broke"<<l+1<<"\n";
    }

    for(int i=0;i<3;i++){
            cout<<"\nTime taken for queue "<<i+1<<" to execute: "<<q[i].tTime<<"\n";
        for(int j=0;j<q[i].len;j++){
            cout<<"Process "<<j+1<<" of queue "<<i+1<<" took "<<q[i].p[j].tTime<<"\n";
        }
    }

    int sum_tt=0;
    int sum_wt=0;

    cout<<"\n\nProcess | Turn Around Time | Waiting Time\n";
    for(int i=0;i<3;i++){
            cout<<"Queue "<<i+1<<"\n";
        for(int j=0;j<q[i].len;j++){
            cout<<"Process P"<<j+1<<"\t"<<q[i].p[j].tTime<<"\t\t    "<<q[i].p[j].tTime-q[i].p[j].tt_time<<"\n";
            sum_tt+=q[i].p[j].tTime;
            sum_wt+=q[i].p[j].tTime-q[i].p[j].tt_time;
        }
    }

    cout<<"\n The average turnaround time is : "<<sum_tt/num<<endl;
    cout<<"\n The average waiting time is : "<<sum_wt/num<<endl;

}
