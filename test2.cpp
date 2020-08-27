#include <iostream>
#include<stdlib.h>

int **B;
int m,n;
//Dynamic Allocation of 2D Array
using namespace std;
//data structured
    typedef int ElementType;
//
//    typedef struct LOfNodes{ //list of nodes (nodes of tree)
//    struct MTreeNode * child;
//    struct LOfNodes * next;
//}   LOfNodes;

    typedef struct MTreeNode  //m-ary tree
{   ElementType Data;
    MTreeNode *Children;
    }MTreeNode;

 MTreeNode* constructMTreeNode(ElementType data)
{
    MTreeNode *D;
    D=(MTreeNode*)malloc(sizeof(MTreeNode));
    if (D==NULL)
    {
        cout<<"Error\n";
        return 0;
    }
    D->Data=data;
    D->Children==NULL;
    return D;
}

void  BuildTree(MTreeNode *node)
{  int Count=0;
   for(int i=0;i<m;i++)
    {
       if(B[(node->Data)-1][i]==1){
        Count++;
       }
    }
    node->Children = (MTreeNode*)malloc(Count*sizeof(MTreeNode));
    for(int i=0;i<Count;i++)
    {
        int j;
        for(j=0;j<m;j++)
        {
            if(B[node->Data-1][j]==1)
                break;
        }
    B[(node->Data)-1][j]=0;
    B[j][(node->Data)-1]=0;
    MTreeNode* node2;
    node2= constructMTreeNode(j+1);
    BuildTree(node2);
    node->Children[i]=*node2;
    }


   /* for(int i=0;i<n;i++){
        cout<<A[i]<<endl;
        free(A); } */
}


int main(void)
{
    int i,j;
    int Cycles=0;
    cout<<"Enter number of rows:";
    cin>>n;
    cout<<"Enter number of columns:";
    cin>>m;
if (n!=m)
{
    cout<<"invalid size";
    return 0;
}
else
{
    B=(int **)malloc(n*sizeof(int*));
    if(B==NULL)
    {
        cout<<"Out of memory";
        return 1;
    }
    for (i=0;i<n;i++)
    {
        B[i]=(int *)malloc(m*sizeof(int));
        if(B[i]==NULL)
        {
            cout<<"Out of memory";
            return 1;
        }
    }
}
//============================================================================
    B[0][0]=0;
    B[0][1]=0;
    B[0][2]=0;
    B[0][3]=1;
    B[0][4]=0;
    B[0][5]=0;
    B[1][0]=0;
    B[1][1]=0;
    B[1][2]=0;
    B[1][3]=1;
    B[1][4]=0;
    B[1][5]=0;
    B[2][0]=0;
    B[2][1]=0;
    B[2][2]=0;
    B[2][3]=1;
    B[2][4]=0;
    B[2][5]=0;
    B[3][0]=1;
    B[3][1]=1;
    B[3][2]=1;
    B[3][3]=0;
    B[3][4]=1;
    B[3][5]=0;
    B[4][0]=0;
    B[4][1]=0;
    B[4][2]=0;
    B[4][3]=1;
    B[4][4]=0;
    B[4][5]=1;
    B[5][0]=0;
    B[5][1]=0;
    B[5][2]=0;
    B[5][3]=0;
    B[5][4]=1;
    B[5][5]=0;
/*     for(i=0;i<n;i++)
 *     {
 *         for(j=0;j<m;j++)
 *         {
 *             cin>>B[i][j];
 *         }
 *     }
 */
//================================================== check
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(B[i][j]!=B[j][i])
            {
                cout<<"invalid matrix";
                return 0;
            }
            if(B[i][j]==1)
            {
                Cycles++;
            }
        }
        if(B[i][i]!=0)
        {
            cout<<"invalid matrix";
            return 0;
        }
    }
    if(Cycles!=((n-1)*2)) //check cycles
    {
        cout<<"invalid matrix";
        return 0;
    }
    //======================================================== display
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            cout<<B[i][j]<<"\t";
        }
        cout<<endl;
    }
    //============================================================
    MTreeNode *P;
    P = constructMTreeNode(4);
    BuildTree(P);
    for(int i=0;i<4;i++)
    {
        cout<<P->Children[3].Children[0].Data;
    }





    //===============================A============================= free
    for(i=0;i<n;i++)
        free(B[i]);

    free(B);

    return 0;
    }


