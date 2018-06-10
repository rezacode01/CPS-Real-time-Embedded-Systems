/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program  online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;

const int b = 2;
const int s = 5;
const double percentile = 0.6;

bool is_valid(int x)
{
    if(x>=0 && x <=2)
        return true;
    return false;
}

int move_coordination(int x, int coordination)
{
    if(coordination==0)
        x += 0;
    else if(coordination ==1)
        x += 1;
    else if(coordination ==2)
        x -=1;
    return x;
}

void change_coordination(int& coordination){
    coordination = ((coordination+1)%2) +1;
}

int main()
{
    //winsorisation    
    long dbs[b][s] = {{-25, -75, -29, -28, -24}, {-44,-47,-76,-43, -45}};
    double interval_dbs[b];
    long batch[s];
    
    for (int i = 0; i < b; i++)
    { 
        //initialization
        for(int j = 0; j < s; j++)
            batch[j] = dbs[i][j];
        //sotring
        for(int j =0; j < s; j++)
            for(int k = 0; k < s-1; k++)
                if(batch[k]>batch[k+1])
                {
                    long temp = batch[k];
                    batch[k] = batch[k+1];
                    batch[k+1] = temp;
                }
        //winsorisation
        int index_low = (int) (((1.0-percentile)/2.0)*s);
        int index_high = (int) ((1-((1.0-percentile)/2.0))*s)-1;
        if(i==0)
            cout << "low form " << index_low << " to " << index_high << endl;
        for(int j = 0; j < index_low; j++)
            batch[j] = batch[index_low];
        for(int j = index_high+1; j < s; j++)
            batch[j] = batch[index_high];
        interval_dbs[i] = 0;
        for(int j = 0; j < s; j++)
            interval_dbs[i] += double(batch[j]);
        interval_dbs[i] /= double(s);
        cout << "batch number " << i << " has average " << interval_dbs[i]<< endl;
    }
    
    
    
    
    int coordination = 0;
    int x = 1;
    for(int i =0; i < 100; i++)
    {
          //cerr << x << " " << coordination << endl;
        if(!is_valid(move_coordination(x,coordination))
           || interval_dbs[x]>=interval_dbs[move_coordination(x,coordination)])
           {
                change_coordination(coordination);
           }
        else
            x = move_coordination(x, coordination);
      
    }
    cout << "best signal at " << x << endl;
    return 0;
}
