#include <iostream>
#include<stdlib.h>

using namespace std;


int **Mx;
int Size;

typedef int elementType;

typedef struct BTN
{
    elementType data;
    struct BTN* left;
    struct BTN* right;
}BTN;
typedef struct BTN* bTree;

typedef struct node
{
    struct ntn* child;
    struct node* next;
}node;

typedef struct ntn
{
    elementType data;
    ntn
}ntn;
typedef struct ntn *nTree;


int *arr;

bool check()
{
    int ones=0;
    for(int i=0;i<Size;i++)
    {
        for(int j=0;j<Size;j++)
        {
            if(Mx[i][j]!=Mx[j][i])
            {
                return false;
            }
            if(Mx[i][j]==1)
            {
                ones++;
            }
        }
        if(Mx[i][i]!=0)
        {
            return false;
        }
    }
    if(ones!=((Size-1)*2))
    {
        return false;
    }
    return true;
}
bool initialize()
{
    cout<<"Enter the size of the square matrix: ";
    cin>>Size;
    Mx =(int **)malloc(Size*sizeof(int*));
    if(Mx==NULL)
    {
        cout<<"Out of memory";
        return 0;
    }
    for (int i=0;i<Size;i++)
    {
        Mx[i]=(int *)malloc(Size*sizeof(int));
        if(Mx[i]==NULL)
        {
            cout<<"Out of memory";
            return 0;
        }
    }
    for(int i=0;i<Size;i++)
    {
        for(int j=0;j<Size;j++)
        {
            cout<<"Enter Cell ("<<i+1<<","<<j+1<<"): ";
            cin>>Mx[i][j];
        }
    }
    if(check())
    {
        cout<<"Valid!"<<endl;
        return true;
    }
    else
    {
        cout<<"Invalid!"<<endl;
        return false;
    }
    return true;
}
void display()
{
    cout<<endl;
    for(int i=0;i<Size;i++)
    {
        for(int j=0;j<Size;j++)
        {
            cout<<Mx[i][j]<<" ";
        }
        cout<<endl;
    }
}
void insert(node **children, ntn *child)
{
    node *new_node = (node*)malloc(sizeof(node));
    new_node->child  = child;
    new_node->next=NULL;
    node *Last = *children;
    if(*children==NULL)
    {
        *children=new_node;
        return;
    }
    while(Last->next!=NULL)
    {
        Last=Last->next;
    }
    Last->next=new_node;
    return;
}
ntn* constructNTN(elementType data)
{
    ntn *P;
    P=(ntn*)malloc(sizeof(ntn));
    if (P==NULL)
    {
        cout<<"Error\n";
        return 0;
    }
    P->data=data;
    P->children = NULL;
    return P;
}
void constructNT(ntn *mtree, int node)
{
    for(int i=0;i<Size;i++)
    {
        if(Mx[node-1][i]==1)
        {
            ntn *tmp = constructNTN(i+1);
            Mx[node-1][i]=0;
            Mx[i][node-1]=0;
            insert(&(mtree->children), tmp);
            constructNT(tmp,i+1);
        }
    }
}
void storeBSTN(BTN* root)
{
    if (root==NULL)
        return;
    static int i=0;
    storeBSTN(root->left);
    arr[i]= root->data;
    i++;
    storeBSTN(root->right);
}
BTN* constructBTN(elementType data)
{
    BTN *P;
    P =(BTN*)malloc(sizeof(BTN));
    if(P==NULL)
    {
        cout<<"Error\n";
        return 0;
    }
    P->data=data;
    P->left=NULL;
    P->right=NULL;
    return P;
}
BTN* BT(node *LNode)
{
    BTN *tmp;
    tmp = constructBTN(LNode->child->data);
    if(LNode->child->children!=NULL)
    {
        tmp->left = BT(LNode->child->children);
    }
    if(LNode->next!=NULL)
    {
        tmp->right = BT(LNode->next);
    }
    return tmp;
}
BTN* buildAVL(int start, int end)
{
    if (start > end)
        return NULL;
    int mid = (start + end)/2;
    BTN *root = constructBTN(arr[mid]);
    BTN *c1 = buildAVL(start, mid-1);
    BTN *c2 = buildAVL(mid+1, end);
    if(c1!=NULL)
    {
        if(c1->data>root->data)
        {
            root->right=c1;
            root->left=c2;
        }
    }
    if(c2!=NULL)
    {
        if(c2->data>root->data && c2!=NULL)
        {
            root->right=c2;
            root->left=c1;
        }
    }
    return root;
}
void show_node(bTree T)
{
    cout<<T->data;
}
void preorder(bTree T)
{
    if (T != NULL)
    {
        show_node(T);
        preorder(T->left);
        preorder(T->right);
    }
}
void postorder(bTree T)
{
    if (T != NULL)
    {
        postorder(T->left);
        postorder(T->right);
        show_node(T);
    }
}
void inorder(bTree T)
{
    if (T != NULL)
    {
        inorder(T->left);
        show_node(T);
        inorder(T->right);
    }
}
int main(void)
{
    TestCase();
    // if(!initialize())
    // {
    //     return 0;
    // }
    cout<<"Adjacency Matrix: "<<endl;
    display();
    int treeRoot;
    cout<<"Enter the Root of the Tree: ";
    cin>>treeRoot;
    nTree maintree = constructNTN(treeRoot);
    constructNT(maintree, treeRoot);
    bTree BiTree = constructBTN(treeRoot);
    BiTree->left = BT(maintree->children);
    cout<<"Binary Tree in inorder traverse: ";
    inorder(BiTree);
    arr=(int*)malloc(Size*sizeof(int));
    storeBSTN(BiTree);
    bTree AVL = buildAVL(0, Size-1);
    cout<<endl<<"AVL in inorder traverse: ";
    inorder(AVL);
    cout<<endl<<"AVL in postorder traverse: ";
    postorder(AVL);
    cout<<endl<<"AVL in preorder traverse: ";
    preorder(AVL);
    return 0;
}
