#ifndef FUNCTION_H
#define FUNCTION_H

typedef struct 
{
    char Stack[100];
    int topIndex;
}stack_T;

typedef struct DoubleNode{
  double data;
  struct DoubleNode* next;
}DoubleNode;

struct queue
{
    int count;
    DoubleNode *front;
    DoubleNode *rear;
};
typedef struct queue queue;

typedef struct Node{
  char data[100];
  struct Node* next;
  int priority;
}Node;

void initialize(queue *q);
int isempty(queue *q);
void dequeue(queue *q);
void enqueue(queue *q, double value);
void display(queue* q,int set);
void InfixSelect();
void reverse(char *s);
char popStack(stack_T* stack);
void pushStack(char inp, stack_T* stack);
stack_T* StackInfixToPostfix(char expression[],char mode[]);
void StackInfixToOther(char* Mode);

void removeEnter(char *str);
int setting(int start);
void printans(double answer,int set);

void EnterCutter(char* arr);
void loopFreeNode(Node* headNode);
int priority(char Operator);
Node* push(Node* topStack,Node* source);
Node* addNode(Node* tailNode,char *val);
const char* pop(Node** topStack);
DoubleNode* pushDouble(DoubleNode* topStack, double data);
double popDouble(DoubleNode** topStack);
int CheckEquationValid(char* buffer,queue* q);
Node* EquationToNode(char* buffer,queue* q);
Node* NodeInfixtoPostfix(Node* headNodeInfix);
int CalculateFromPostfix(Node* headStack,double* StoringAnswer);
void CalculateFunction(int digit,queue* q);
void welcome();
void slime();
void trucksan();
void thank();




































#endif