//Assignment 1----Memory Allocation

#include<stdio.h>
#include<stdlib.h>
//#include<string.h>
//#include<stddef.h>
#define SIZE 1000000    //1000000 bytes(1mb)(size of memory)
#define START 0
unsigned char memory_array[SIZE]; //our memory
//static char *pointer=memory_array;
//static char *pointer=&memory_array[0];
//char *myfree(void *pointer);
//void mergefreeblock();
//void splitblock(struct header *fitslot,int blocksize);

/* ##malloc -memory allocation is not contiguous
  ##small block at the begining--header(Pointer and size)--  All blocks are multiple of the header size */
/*header structure  */
struct header
{
   int blocksize;
  struct header *next;/*points to the next block in chain,record of the size of the block and then free space itself*/
  int freeblock;
};
struct header *freeblock_ptr=(void*)memory_array;

void splitblock(struct header *fitslot,int blocksize)
 {
    struct header *newblock=(void*)((void*)fitslot+blocksize+sizeof(struct header));
    newblock->blocksize=(fitslot->blocksize)-blocksize-sizeof(struct header);
    newblock->freeblock=1;
    newblock->next=fitslot->next;
    fitslot->blocksize=blocksize;
    fitslot->freeblock=0;
    fitslot->next=newblock;
 }



//Allocation---( assign and split )
/*return pointer to n characters*/
//char *myalloc(size_t n)  
void *mymalloc(int n)   
 {
   struct header *current,*previous;
   void *allocation;
   if(!(freeblock_ptr->blocksize))
    {
      freeblock_ptr->blocksize=SIZE-sizeof(struct header);
      freeblock_ptr->freeblock=1;/*if block is free-->set 1*/
      freeblock_ptr->next=NULL;
    }
  current=freeblock_ptr;
/* If the request is granted --> block of memory is reserved
   address of reserved block--> placed  into  pointer variable
   request successful-> return pointer to the memory block
   if not enough memory available->mymalloc reurns null*/
  while((((current->blocksize)<n)||((current->freeblock)==0))&&(current->next!=NULL))
  {
    previous=current;
    current=current->next;
    
 }
 if((current->blocksize)==n)
   {
     current->freeblock=0;
     allocation=(void*)(++current);
     return allocation;
  }
 else if((current->blocksize)>(n+sizeof(struct header)))
  {
    splitblock(current,n);
    allocation=(void*)(++current);
     return allocation;
  }
 }



	



//Deallocation---( free and merge)
/*
void afree(char *free) // free storage pointed to by free
{
if (free >= memory_array && free < memory_array + SIZE)
  pointer = free;
}
*/
/*  check if the next slot is free or the previous slot is free 
    combining two free slots
      */
char *myfree(void *pointer)
   {
    // if(((void*)memory_array<=pointer)&&(pointer<=(void*)(memory_array+SIZE)))
   //{
     struct header *current=pointer;
     --current;
      current->freeblock=1;
     // mergefreeblock();
   
  //  }
}

void mergefreeblock()
 {
   struct header *current,*previous;
   current=freeblock_ptr;
   while((current->next)!=NULL)
   {
     if((current->freeblock)&&(current->next->freeblock))
     {
       current->blocksize+=(current->next->blocksize)+sizeof(struct header);
      // current=current->next;
       current->next=current->next->next;
       continue;
     }
     previous=current;
     current=current->next;
    }
  }

