#include <iostream>
#include<stdlib.h>
using namespace std;
int **R;
int r;
int CHECKALL(int**R);
typedef int data;

typedef struct TREENODE{
    int data;
    TREENODE*brother;
    TREENODE*child;
    }nodE;

TREENODE* construct(int data){
TREENODE *f;
f=(TREENODE*)malloc(sizeof(TREENODE));
f->data=data;
f->child=NULL;
f->brother=NULL;
return f;}

void show_node(TREENODE* T)
{
    cout<<T->data;
}

void inorder(TREENODE* T)
{
    if (T != NULL)
    {
        inorder(T->child);
        show_node(T);
        inorder(T->brother);
    }
}


void BUILDTREE(TREENODE *node)
{
    for(int i=0;i<r;i++)
    {
        if(R[(node->data)-1][i]==1)
        {
            TREENODE *NEWNODE = construct(i+1);
            if(node->child==NULL)
            {
                node->child= NEWNODE;
                R[(node->data)-1][i]=0;
                R[i][(node->data)-1]=0;
                BUILDTREE(NEWNODE); 
            }
            else
            {
                TREENODE *p=node->child;
                while(p->brother!=NULL)
                {
                    p=p->brother;
                }
                p->brother=NEWNODE;
                R[(node->data)-1][i]=0;
                R[i][(node->data)-1]=0;
                BUILDTREE(NEWNODE);
            }
        }
    }
}
int main()
{
cout<<"Enter the size of the adj matrix:";
cin>>r;
R=(int **)malloc(r*sizeof(int*));
if(R==NULL)
{
cout<<"Out of memory";
return 1;
}
for (int i=0;i<r;i++)
{
R[i]=(int *)malloc(r*sizeof(int));
if(R[i]==NULL)
{
cout<<"Out of memory";
return 1;
}
}
cout<<"insert the values of the adjacency matrix"<<endl;
    R[0][0]=0;
    R[0][1]=0;
    R[0][2]=0;
    R[0][3]=1;
    R[0][4]=0;
    R[0][5]=0;
    R[1][0]=0;
    R[1][1]=0;
    R[1][2]=0;
    R[1][3]=1;
    R[1][4]=0;
    R[1][5]=0;
    R[2][0]=0;
    R[2][1]=0;
    R[2][2]=0;
    R[2][3]=1;
    R[2][4]=0;
    R[2][5]=0;
    R[3][0]=1;
    R[3][1]=1;
    R[3][2]=1;
    R[3][3]=0;
    R[3][4]=1;
    R[3][5]=0;
    R[4][0]=0;
    R[4][1]=0;
    R[4][2]=0;
    R[4][3]=1;
    R[4][4]=0;
    R[4][5]=1;
    R[5][0]=0;
    R[5][1]=0;
    R[5][2]=0;
    R[5][3]=0;
    R[5][4]=1;
    R[5][5]=0;
for(int i=0;i<r;i++)
{  for (int j=0;j<r;j++)
{

cout<<R[i][j]<<"\t";
}
        cout<<endl;
}
int check=CHECKALL(R);
if(check==0)
{
    return 0;
}
//===================================================
TREENODE *p = construct(4);
BUILDTREE(p);
cout<<"Tree inorder:";
inorder(p);
//===================================================
return 0;
}
int CHECKALL(int**R)
{
    int x=0;
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<r;j++)
        {
            if(R[i][j]==1)
            {
                x++;
            }
            else if (R[i][j]!=0)
            {

                return 0;
            }
            if(R[i][j]!=R[j][i])
            {
                return 0;
            }
        }
        if(R[i][i]!=0)
        return 0;
    }
    if((x/2)!=(r-1))
    {
        cout<<"invalid";
        return 0;
    }
    cout<<"valid";
    return 1;
}
