#include <stdio.h>
#include <stdlib.h>
#define MAX 10 

typedef int date; 
typedef enum {FALSE, TRUE} Bool;

typedef struct stackType{
    date year[MAX]; 
    int top; 
}StackType, *Stack;

typedef struct node{
    date year; 
    struct node* next; 
}NodeQueue, *NodePtr;

typedef struct{
    NodePtr front; 
    NodePtr rear;
}Queue;

void init(Queue *Q);
void EnQueue(Queue *Q, date new);
void DeQueue(Queue *Q);
void displayQueue(Queue *Q);

void initialize(Stack *S);
Bool isEmpty(Stack S);
Bool isFull(Stack S);
date top(Stack S);
void push(Stack *S, date elem);
void pop(Stack *S);
void displayStack(Stack S);

Stack SortStack(Queue *Q);

// sort the queue using stack method 

int main(){

    Queue Q; 
    init(&Q);
    Stack S; 
    initialize(&S);

    //data stored in the queue 
    EnQueue(&Q, 1999);
    EnQueue(&Q, 1993);
    EnQueue(&Q, 1998);
    EnQueue(&Q, 1973);
    EnQueue(&Q, 1982);
    EnQueue(&Q, 2006);
    EnQueue(&Q, 2023);
    EnQueue(&Q, 2022);
    EnQueue(&Q, 2019);
    EnQueue(&Q, 2012);
    //printf("%d\n", Q.front->next->year);
    displayQueue(&Q);

    printf("===========\n");
    S = SortStack(&Q);
    displayStack(S);
}

void init(Queue *Q){

    Q->front = NULL;
    Q->rear = NULL;

    // queue is empty, so there is no front and no rear
}

void EnQueue(Queue *Q, date new){

    NodePtr newElem = malloc(sizeof(struct node));
    newElem->year = new; 
    newElem->next = NULL; 
    
    if(Q->front == NULL){ //if queue is empty, the new is first AND last
        Q->rear = newElem;
        Q->front = newElem;
    }
    else{ //if queue has ppl, connect last node to the new node
        Q->rear->next = newElem;
        Q->rear = newElem;  
    }

} 

void DeQueue(Queue *Q){

    if(Q->front != NULL){
        //to free
        NodePtr temp = Q->front;
        Q->front = Q->front->next; 

        if(Q->front == NULL){
            Q->rear = NULL; 
        }

        free(temp);
    }
    
    
}

void displayQueue(Queue *Q){
    
    Queue temp;
    int i = 1; 

    init(&temp);

    while(Q->front != NULL){

        printf("%d : %d \n", i , Q->front->year);
        EnQueue(&temp, Q->front->year);
        
        DeQueue(Q);
   

        i++; 

    }

    *Q = temp; 
    
}

void initialize(Stack *S){

    (*S) = (struct stackType*)malloc(sizeof(struct stackType));
    (*S)->top = MAX; 

}

Bool isFull(Stack S){

    return(S->top == 0) ? TRUE:FALSE;

}

Bool isEmpty(Stack S){

    return(S->top == MAX) ? TRUE:FALSE;
    
}

date top(Stack S){

    return(isEmpty(S) == FALSE) ? S->year[S->top] : '!' ; 

}

void push(Stack *S, date elem){

    if(isFull(*S) == FALSE){
        (*S)->top--;
        (*S)->year[(*S)->top] = elem;     
    }
    
}

void pop(Stack *S){

    if(isEmpty(*S) == FALSE){
        (*S)->top++;
    }

}

void displayStack(Stack S){

    Stack temp; 
    initialize(&temp);

    while(isEmpty(S) == FALSE){
        printf("%d \n", S->year[S->top]);
        push(&temp, S->year[S->top]);
        pop(&S);
    }

    //moving

    while(isEmpty(temp) == FALSE){
        push(&S, temp->year[temp->top]);
        pop(&temp);
    }

}

Stack SortStack(Queue *Q){

    Stack Stack1, Stack2; 

    initialize(&Stack1);
    initialize(&Stack2);

    push(&Stack1, Q->front->year);
    DeQueue(Q);

    while(Q->front != NULL){
        while(Stack1->year[Stack1->top] > Q->front->year){
            push(&Stack2, Stack1->year[Stack1->top]);
            pop(&Stack1);
            //printf("stack1 to stack 2\t %d\n", Stack1->year[Stack1->top]);
        }

        push(&Stack1, Q->front->year);
        DeQueue(Q);
        //printf("dekwey\n");

        while(isEmpty(Stack2) == FALSE){
            push(&Stack1, Stack2->year[Stack2->top]);
            pop(&Stack2);
            //printf("stack2 to stack1\t %d\n", Stack1->year[Stack1->top]);
        }

    }

    return Stack1;

    //Stack1 == return 
    //Stack2 == temp storage

    //1. move queue items to stack in order
    // queue first in first out 
    // stack first in last out

    // first queue to top of stack1
    // compare first of queue to stack1 top
        // if 1stqueue is less push to stack2
        // else(greater) push to stack 1 
}
