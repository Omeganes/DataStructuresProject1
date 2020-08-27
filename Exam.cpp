#include <iostream>
#include <stdlib.h>

using namespace std;

//====================================================================
int main(void)
{
    int **A;
    int *B;
    A =(int **)malloc(5*sizeof(int*));
    B =(int *)malloc(5*sizeof(int));
    if(A==NULL)
    {
        cout<<"Out of memory";
        return 0;
    }
    for (int i=0;i<5;i++)
    {
        A[i]=(int *)malloc(4*sizeof(int));
        if(A[i]==NULL)
        {
            cout<<"Out of memory";
            return 0;
        }
    }
    for(int i=0;i<5;i++)
    {  
        for(int j=0;j<4;j++)
        {
            cout<<"Enter Cell ("<<i+1<<","<<j+1<<"): ";
            cin>>A[i][j];
        }
    }
    for(int i=0;i<5;i++)
    {
        for(int j =0;j<4;j++)
        {
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }


    return 0;
}
//====================================================================
