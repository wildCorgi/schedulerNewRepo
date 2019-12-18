#include "headers.h"
typedef struct treeNode  
{ 
    int  PID; 
    int memSize;
    int start,end;
    struct treeNode *left; 
    struct treeNode *right; 
}; 
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
    return treeNode;
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
            return 1;
        }
        else
        {
            struct treeNode* left = newLeftNode(&currSegment);
            struct treeNode* right = newRightNode(&currSegment);
            if(allocate(left,memSize,process)==0)
                return allocate(right,memSize,process);
            else
            {
                return 1;
            }
        }
    }
}

