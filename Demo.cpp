#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<malloc.h>

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


typedef struct LTreeNode{ //m-ary tree
ElementType Data;
LTreeNode *Children;
int Childrensize;
}LTreeNode;

typedef struct NOOOODE  {
ElementType data;
struct NOOOODE* left;
struct NOOOODE* right; }NOOOODE;

typedef struct NOOOODE* BinaryTREE;



LTreeNode* constructMTreeNode(ElementType data);
void BuildTree(LTreeNode *Node);
//binary tree
NOOOODE* NewNode(ElementType data);
NOOOODE* BuildBinaryTree(LTreeNode* Node);
void INORDERtraverse(BinaryTREE TTT);


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
//=================================================== insert
    for(i=0;i<n;i++)
    {
        cout<<"Enter Values of row "<<i+1<<" : ";
        for(j=0;j<m;j++)
        {
            cin>>B[i][j];
        }
    }
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
    //============================================================ Trees
    LTreeNode *P;
    int w;
    cout<<"Enter the node to be the root node ";
    cin>>w;
    P = constructMTreeNode(w);
    BuildTree(P);
    LTreeNode k = P->Children[3];

    NOOOODE *K = BuildBinaryTree(P);

    cout<<"Binary Tree in Inorder Traverse: ";
    INORDERtraverse(K);
    //============================================================ free
    for(i=0;i<n;i++)
        free(B[i]);

    free(B);

    return 0;
    }
//==============================================
LTreeNode* constructMTreeNode(ElementType data)
{
      LTreeNode *D;
      D=(LTreeNode*)malloc(sizeof(LTreeNode));
      if (D==NULL)
      {
        cout<<"Error\n";
          return 0;
      }
      D->Data=data;
      D->Children=NULL;
      D->Childrensize=0;
      return D;
}
//==============================================
void BuildTree(LTreeNode *Node)
{     
    int Count=0;
    for(int i=0;i<m;i++)
    {
        if(B[(Node->Data)-1][i]==1){
            Count++;
        }
    }
    Node->Childrensize=Count;
    if(Count!=0)
    {
        Node->Children = (LTreeNode*)malloc(Count*sizeof(LTreeNode));
        for(int i=0;i<Count;i++)
        {
            int j=0;
            for(j=0;j<m;j++)
            {
                if(B[Node->Data-1][j]==1)
                    break;
            }
            LTreeNode* node2;
            node2= constructMTreeNode(j+1);
            B[(Node->Data)-1][j]=0;
            B[j][(Node->Data)-1]=0;
            BuildTree(node2);
            Node->Children[i] = *node2;
            
        }
    }
}

NOOOODE * NewNode(ElementType data)
{
    NOOOODE *D;
    D=(NOOOODE*)malloc(sizeof(NOOOODE));
    if(D==NULL)
    {
        cout<<"Error\n";
        return 0;
    }
    D->data=data;
    D->left = NULL;
    D->right = NULL;
    return D;
}

//=============================================
NOOOODE* BuildBinaryTree(LTreeNode* Node)
{
    NOOOODE* Bnode = NewNode(Node->Data);
    if(Node->Childrensize!=0)
    {
        NOOOODE* Bnode2 = BuildBinaryTree(&(Node->Children[0]));
        Bnode->left=Bnode2;
        NOOOODE* p= Bnode2;
        for(int i=1;i<Node->Childrensize;i++)
        {
            NOOOODE* Bnode3 = BuildBinaryTree(&(Node->Children[i]));
            p->right=Bnode3;
            p=p->right;
        }
    }
    return Bnode;
}


void show_node(NOOOODE* T)
{
    cout<<T->data;
}

void INORDERtraverse(BinaryTREE TTT)
{
    if (TTT != NULL)
    {
        INORDERtraverse(TTT->left);
        show_node(TTT);
        INORDERtraverse(TTT->right);
    }
}