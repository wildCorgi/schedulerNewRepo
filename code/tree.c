#include "headers.h"
typedef struct treeNode  
{ 
    int  PID; 
    int memSize;
    int branched;
    int start,end;
    struct treeNode *left; 
    struct treeNode *right; 
}treeNode; 
// struct treeNode* newNode(int PID,int memSize,int start,int end) 
// { 
//   // Allocate memory for new node  
//   struct treeNode* treeNode = (struct treeNode*)malloc(sizeof(struct treeNode)); 
  
//   // Assign data to this node 
//   treeNode->PID = PID; 
//   treeNode->memSize = memSize;
//   treeNode->start = start;
//   treeNode->end = end;
//   // Initialize left and right children as NULL 
//   treeNode->left = NULL; 
//   treeNode->right = NULL; 
//   return(treeNode); 
// } 
struct treeNode* newLeftNode(struct treeNode* currSegment)
{
    struct treeNode* treeNode = (struct treeNode*)malloc(sizeof(struct treeNode));
    treeNode->PID=-1;
    treeNode->memSize=currSegment->memSize/2;
    treeNode->start=currSegment->start;
    treeNode->end=currSegment->end/2;
    treeNode->left=NULL;
    treeNode->right=NULL;
    currSegment->left= treeNode;
    treeNode->branched=0;
    currSegment->branched=1;
    return treeNode;
}

struct treeNode* newRightNode(struct treeNode* currSegment)
{
    struct treeNode* treeNode = (struct treeNode*)malloc(sizeof(struct treeNode));
    treeNode->PID=-1;
    treeNode->memSize=currSegment->memSize/2;
    treeNode->start=((currSegment->end)/2)+1;
    treeNode->end=currSegment->end;
    treeNode->left=NULL;
    treeNode->right=NULL;
    currSegment->right= treeNode;
    treeNode->branched=0;
    currSegment->branched=1;
    return treeNode;
}
int merge(struct treeNode* tree)
{
    if(tree == NULL)
    {
            return 0;
    }
    else
    {
        if(tree->branched==1)
        {
            if(merge(tree->left)==-1 && merge(tree->right) == -1)
            {
                tree->branched=0;
                //delete left and right they are empty
                free(tree->left);
                free(tree->right);
                return-1;
            }
            else
            {
                return tree->PID;
            }
            
        }
        else
        {
            if(tree->PID!=-1)
            {
                 return 0;
            }
            else
            {
                return -1;
            }
            
        }

    }
}
int allocate(struct treeNode* currSegment,int memSize, PCB* process)
{
    if(currSegment->PID!=-1)
    {
        return 0;
    }    
    if(process->memSize==0)
    {
        return 1;
    }

    if(currSegment->memSize>=process->memSize)
    {
        if((currSegment->memSize/2)<process->memSize)
        {
            currSegment->PID=process->processID;
            process->mStart=currSegment->start;
            process->mEnd=currSegment->end;
            return 1;
        }
        else
        {
            currSegment->branched=1;
            struct treeNode* left = newLeftNode(currSegment);
            struct treeNode* right = newRightNode(currSegment);
            if(allocate(left,memSize,process)==0)
                return allocate(right,memSize,process);
            else
            {
                return 1;
            }
        }
    }
}
void dealoc(struct treeNode * tree,int *pid)
{
        if(tree == NULL)
        {
                return;
        }
        if(tree->PID == *pid)
        {
                tree->PID = -1;
                *pid= -1998;
                return ;
        }
        dealoc(tree->left,pid);
        dealoc(tree->right,pid);
}

bool doTheMath(struct treeNode * tree,int *pid)
{
    dealoc(tree,(pid));
    merge(tree);
    return *(pid) != -1998;
}
