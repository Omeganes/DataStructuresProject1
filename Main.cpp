#include <iostream>
#include <stdlib.h>

using namespace std;

//====================================================================
#pragma region Variable support


typedef int EType;

//Binary Tree
typedef struct BiTreeNode
{
    EType data;
    struct BiTreeNode* left;
    struct BiTreeNode* right;
}BiTreeNode;
typedef struct BiTreeNode* BTree;

//List
typedef struct ListNode
{
    struct NTreeNode* child;
    struct ListNode* next;
}ListNode;

// M-ary Tree
typedef struct NTreeNode
{
    EType data;
    ListNode *children;
}NTreeNode;
typedef struct NTreeNode *NTree;

/**
 * Global Variables
 * */
// Adjacecny Matrix
int **AdjMx;
// Matrix Size
int MxSize;
// Array of inorder traverse
int *BiTreeNodesArray;

#pragma endregion
//====================================================================
#pragma region Prototypes

// General
/**
 * Checks if the number is repeated
 * */
bool checkAdjacency();
/**
 * Initiates the Adjacency Matrix
 * */
bool initiateMatrix();
/**
 * Displays the Adjacency Matrix
 * */
void ShowAdjMx();
/**
 * Test Case of the project
 * */
void TestCase();

// Linked List
/**
 * Inserts a n-arry tree node to the rear of a list
 * */
void ListAppend(ListNode **children, NTreeNode *child);

// M-ary tree
/**
 * Converts Adjacency Matrix into N-ary Tree using Recursion
 * */
void nrryTree(NTreeNode *NTreeNode, int node);
/**
 * Constructs a m-ary tree node
 * */
NTreeNode* constructNTreeNode(EType data);
/**
 * Free the N-ary Tree
 * */
void DestroyNTree(ListNode *L);

// Binary Tree
/**
 * Insert the Binary tree into the array in Inorder traverse
 * */
void storeBSTNodes(BiTreeNode* root);
/**
 * Converts M-ary Tree to Binary Tree
 * */
BiTreeNode* BinaryTree(ListNode *LNode);
/**
 * Constructs a Binary Tree Node 
 * @param Data
 * */
BiTreeNode* constructBiTreeNode(EType data);
/**
 * Shows the preorder of the Tree
 * */
void preorder(BTree T);
/**
 * Display the Tree in Postorder
 * */
void postorder(BTree T);
/**
 * Display the Tree Inorder
 * */
void inorder(BTree T);
/**
 * Shows the content of a node
 * */
void show_node(BTree T);
/**
 * Build an Balanced Search Tree using an array of inordered traversed tree
 * @param StartIndex
 * @param EndIndex
 * */
BiTreeNode* BuildAVL(int start, int end);
/**
 * Frees binary tree
 * */
void DestroyBiTree(BTree T);
#pragma endregion
//====================================================================
int main(void)
{
    TestCase();
    // if(!initiateMatrix())
    // {
    //     // Terminate the program if the adjacency is invalid
    //     return 0;
    // }
    cout<<"Adjacency Matrix: "<<endl;
    ShowAdjMx();
    // Variable support fot the root of the tree
    int treeRoot;
    cout<<"Enter the Root of the Tree: ";
    cin>>treeRoot;
    // Construct M-arry Tree
    NTree maintree = constructNTreeNode(treeRoot);
    nrryTree(maintree, treeRoot);
    // Construct Binary Tree
    BTree BiTree = constructBiTreeNode(treeRoot);
    BiTree->left = BinaryTree(maintree->children);
    cout<<"Binary Tree in inorder traverse: ";
    inorder(BiTree);
    // A dynamically allocated array to save the inorder traverse of the tree "declared globally"
    BiTreeNodesArray=(int*)malloc(MxSize*sizeof(int));
    storeBSTNodes(BiTree);
    // Create AVL Tree
    BTree AVL = BuildAVL(0, MxSize-1);
    // Show Traverse of the AVL Trr
    cout<<endl<<"AVL in inorder traverse: ";
    inorder(AVL);
    cout<<endl<<"AVL in postorder traverse: ";
    postorder(AVL);
    cout<<endl<<"AVL in preorder traverse: ";
    preorder(AVL);
    // Free memory
    DestroyNTree(maintree->children);
    free(maintree);
    DestroyBiTree(BiTree);
    DestroyBiTree(AVL);
    free(AdjMx);
    free(BiTreeNodesArray);
    return 0;
}
//====================================================================
#pragma region General Functions

bool initiateMatrix()
{
    cout<<"Enter the size of the square matrix: ";
	cin>>MxSize;
    AdjMx =(int **)malloc(MxSize*sizeof(int*));
    if(AdjMx==NULL)
    {
        cout<<"Out of memory";
        return 0;
    }
    for (int i=0;i<MxSize;i++)
    {
        AdjMx[i]=(int *)malloc(MxSize*sizeof(int));
        if(AdjMx[i]==NULL)
        {
            cout<<"Out of memory";
            return 0;
        }
    }
    for(int i=0;i<MxSize;i++)
    {  
        for(int j=0;j<MxSize;j++)
        {
            cout<<"Enter Cell ("<<i+1<<","<<j+1<<"): ";
            cin>>AdjMx[i][j];
        }
    }
    if(checkAdjacency())
    {
        cout<<"Valid Adjacency Matrix!"<<endl;
        return true;
    }
    else
    {
        cout<<"Invalid Adjacency Matrix!"<<endl;
        return false;
    }
    return true;
}

bool checkAdjacency()
{
	int checkCycles=0;
    for(int i=0;i<MxSize;i++)
    {
        for(int j=0;j<MxSize;j++)
        {
            if(AdjMx[i][j]!=AdjMx[j][i])
            {
                return false;
            }
			if(AdjMx[i][j]==1)
			{
				checkCycles++;
			}
        }
		if(AdjMx[i][i]!=0 && AdjMx[i][i]!=1)
        {
            return false;
        }
    }
	if(checkCycles!=((MxSize-1)*2))
	{
		return false;
	}
    return true;
}

void ShowAdjMx()
{
    cout<<endl;
    for(int i=0;i<MxSize;i++)
    {
        for(int j=0;j<MxSize;j++)
        {
            cout<<AdjMx[i][j]<<" ";
        }
        cout<<endl;
    }
}

void TestCase()
{
    cout<<"Enter the size of the square matrix: ";
    MxSize=6;
    AdjMx =(int **)malloc(MxSize*sizeof(int*));
    if(AdjMx==NULL)
    {
        cout<<"Out of memory";
    }
    for (int i=0;i<MxSize;i++)
    {
        AdjMx[i]=(int *)malloc(MxSize*sizeof(int));
        if(AdjMx[i]==NULL)
        {
            cout<<"Out of memory";
        }
    }
    AdjMx[0][0]=0;
    AdjMx[0][1]=0;
    AdjMx[0][2]=0;
    AdjMx[0][3]=1;
    AdjMx[0][4]=0;
    AdjMx[0][5]=0;
    AdjMx[1][0]=0;
    AdjMx[1][1]=0;
    AdjMx[1][2]=0;
    AdjMx[1][3]=1;
    AdjMx[1][4]=0;
    AdjMx[1][5]=0;
    AdjMx[2][0]=0;
    AdjMx[2][1]=0;
    AdjMx[2][2]=0;
    AdjMx[2][3]=1;
    AdjMx[2][4]=0;
    AdjMx[2][5]=0;
    AdjMx[3][0]=1;
    AdjMx[3][1]=1;
    AdjMx[3][2]=1;
    AdjMx[3][3]=0;
    AdjMx[3][4]=1;
    AdjMx[3][5]=0;
    AdjMx[4][0]=0;
    AdjMx[4][1]=0;
    AdjMx[4][2]=0;
    AdjMx[4][3]=1;
    AdjMx[4][4]=0;
    AdjMx[4][5]=1;
    AdjMx[5][0]=0;
    AdjMx[5][1]=0;
    AdjMx[5][2]=0;
    AdjMx[5][3]=0;
    AdjMx[5][4]=1;
    AdjMx[5][5]=0;
    if(checkAdjacency())
    {
        cout<<"Valid Adjacency Matrix!"<<endl;
    }
    else
    {
        cout<<"Invalid Adjacency Matrix!"<<endl;
    } 
}

#pragma endregion
//====================================================================
#pragma region M-ary Tree Functions

void nrryTree(NTreeNode *mtree, int node)
{
    for(int i=0;i<MxSize;i++)
    {
        if(AdjMx[node-1][i]==1)
        {
            NTreeNode *tmp = constructNTreeNode(i+1);
            AdjMx[node-1][i]=0;
            AdjMx[i][node-1]=0;
            ListAppend(&(mtree->children), tmp);
            nrryTree(tmp,i+1);
        }
    }
}

NTreeNode* constructNTreeNode(EType data)
{
    NTreeNode *P;
    P=(NTreeNode*)malloc(sizeof(NTreeNode));
    if (P==NULL)
    {
        cout<<"Error\n";
        return 0;
    }
    P->data=data;
    P->children = NULL;
    return P;
}

void DestroyNTree(ListNode *L)
{
    if (L != NULL)
    {
        DestroyNTree(L->child->children);
        DestroyNTree(L->next);
        free(L);
    }
}

#pragma endregion
//====================================================================
#pragma region Linked-list Functions

void ListAppend(ListNode **children, NTreeNode *child)
{
	ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->child  = child;
	new_node->next=NULL;
	ListNode *Last = *children;	
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

#pragma endregion
//====================================================================
#pragma region Binary Tree Functions

void storeBSTNodes(BiTreeNode* root) 
{ 
    // Base case 
    if (root==NULL) 
        return; 
    static int i=0;
    // Store nodes in Inorder (which is sorted 
    // order for BST) 
    storeBSTNodes(root->left);
    BiTreeNodesArray[i]= root->data;
    i++;
    storeBSTNodes(root->right);    
} 

BiTreeNode* BinaryTree(ListNode *LNode)
{
    BiTreeNode *tmp;
    tmp = constructBiTreeNode(LNode->child->data);
    if(LNode->child->children!=NULL)
    {
        tmp->left = BinaryTree(LNode->child->children);
    }
    if(LNode->next!=NULL)
    {
        tmp->right = BinaryTree(LNode->next);
    }
    return tmp;
}

BiTreeNode* constructBiTreeNode(EType data)
{
    BiTreeNode *P;
    P =(BiTreeNode*)malloc(sizeof(BiTreeNode));
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

BiTreeNode* BuildAVL(int start, int end)
{ 
    // base case 
    if (start > end) 
        return NULL;
        /* Get the middle element and make it root */
    int mid = (start + end)/2; 
    BiTreeNode *root = constructBiTreeNode(BiTreeNodesArray[mid]);
    BiTreeNode *child1 = BuildAVL(start, mid-1);
    BiTreeNode *child2 = BuildAVL(mid+1, end);
    if(child1!=NULL)
    {
        if(child1->data>root->data)
        {
            root->right=child1;
            root->left=child2;
        }
    }
    if(child2!=NULL)
    {
        if(child2->data>root->data && child2!=NULL)
        {
            root->right=child2;
            root->left=child1;
        }
    }    
    return root;
} 

void preorder(BTree T)
{
    if (T != NULL)
    {
        show_node(T);
        preorder(T->left);
        preorder(T->right);
    }
}

void postorder(BTree T)
{
    if (T != NULL)
    {
        postorder(T->left);
        postorder(T->right);
        show_node(T);
    }
}

void inorder(BTree T)
{
    if (T != NULL)
    {
        inorder(T->left);
        show_node(T);
        inorder(T->right);
    }
}

void DestroyBiTree(BTree T)
{
    if (T != NULL)
    {
        DestroyBiTree(T->left);
        DestroyBiTree(T->right);
        free(T);
    }
}

void show_node(BTree T)
{
    cout<<T->data;
}
#pragma endregion
//====================================================================