#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "function.h"


void removeEnter(char *str) {
  if (str[strlen(str) - 1] == '\n') {
    str[strlen(str) - 1] = '\0';
  }
}


int setting(int start)
{
  char set;
  int returnValue = start;
  char intbuff[50];

  printf("\e[0;94m");
  printf("\n================================================================\n\n");
  printf("\e[0m");
  while(set !='7')
  {
  printf("Current Setting : %d Max Decimal points\n",returnValue);
  printf("Enter Decimal point (0-6) (7 to leave) : ");
  fgets(intbuff, 50, stdin);
  removeEnter(intbuff);
  set=intbuff[0];
    if(isprint(intbuff[1])!=0)
    {
        printf("\e[0;31m");
        printf("\n-----------------------------Error!-----------------------------\n\n");
        printf("\e[0m");
        continue;
    }
  
  switch(set)
      {
        case '0':
            returnValue =  0;
            break;
        case '1':
            returnValue = 1;
            break;
        case '2':
            returnValue =  2;
            break;
        case '3':
            returnValue =  3;
            break;
        case '4':
            returnValue =  4;
            break;
        case '5':
            returnValue =  5;
            break;
        case '6':
            returnValue =  6;
            break;
        case '7':
            break;
        default:
            printf("e[0;31m");
            printf("\n-----------------------------Error!-----------------------------\n");
            printf("e[0;0m");
            break;
      }
    if(set!='7')
    {
      printf("\e[0;94m");
      printf("\n================================================================\n\n");
      printf("\e[0m");
    }
  }
  return returnValue;
}

//แสดงคำตอบอันเดียว
void printans(double answer,int set)
{
  //printf("Check");
  double printAns = 0;
  switch(set)
      {
        case 0:
            printAns = floor(answer);
            //printf("%.0lf\n",answer);
            break;
        case 1:
            printAns = floor(answer*10)/10;
            //printf("%.1lf\n",answer);
            break;
        case 2:
            printAns = floor(answer*100)/100;
            //printf("%.2lf\n",answer);
            break;
        case 3:
            printAns = floor(answer*1000)/1000;
            //printf("%.3lf\n",answer);
            break;
        case 4:
            printAns = floor(answer*10000)/10000;
            //printf("%.4lf\n",answer);
            break;
        case 5:
            printAns = floor(answer*100000)/100000;
            //printf("%.5lf\n",answer);
            break;
        case 6:
            //printf("%.6lf\n",answer);
            printAns = floor(answer*100000)/100000;
            //printf("%.6lf\n",answer);
            break;
        //case 7:
            //printf("%g\n",answer);
            //break;
      }
    //ถ้าเป็นทศนิยม6จุดหรือมากกว่า ให้ใช้ .6lf เลย
    //ถ้าไม่ ใช้ %g เหมือนเดิม
    if(set == 6 && (printAns != answer))
    {
      printf("%.6lf\n",answer);
    }
    else
    {
      printf("%g\n",printAns);
    }
    
}


void initialize(queue *q)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

int isempty(queue *q)
{
    return (q->rear == NULL);
}

void dequeue(queue *q)
{
    DoubleNode *tmp;
    int n = q->front->data;
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free(tmp);
}

void enqueue(queue *q, double value)
{
    
    if (q->count == 5)
    {
        dequeue(q);
    }
    DoubleNode *tmp;
        tmp = malloc(sizeof(DoubleNode));
        tmp->data = value;
        tmp->next = NULL;
        //ถ้ามีอยู่แล้ว ต่อหลัง
        if(!isempty(q))
        {
            q->rear->next = tmp;
            q->rear = tmp;
        }
        //ถ้าไม่มี เป็นหัวเป็นท้าย
        else
        {
            q->front = q->rear = tmp;
        }
        q->count++;
}


void display(queue* q,int set)
{
  printf("\e[0;94m");
  printf("\n================================================================\n\n");
  printf("\e[0m");
  
  int count = q->count;
    if(q->front == NULL)
    {
        printf("Nothing in History\n");
    }
    else
    {
        DoubleNode* loopNode = q->front;
        while(loopNode != NULL)
        {
          printf("%d Answer before : ",count); 
          printans(loopNode->data, set);
          count--;
          loopNode = loopNode->next;
        }
        
    }
}

int priority(char Operator)
{
    if (Operator == '^')
    {
        return 3;
    }
    else if (Operator == '*' || Operator == '/' || Operator == '%')
    {
        return 2;
    }
    else if(Operator == '+' || Operator == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

//////////////////เริ่มส่วนแปลง Infix เป็นอื่นๆ/////////////////
//ด้วยเหตุผลบางประการ strrev คอมไพล์ไม่รอด 
//เลยต้องทำฟังก์ชั่นไว้ reverse สตริง
void reverse(char *s)
{
    int length, c;
    char *begin, *end, temp;
 
    length = strlen(s);
    begin  = s;
    end    = s;
    //หาที่อยู่ end
    for (c = 0; c < length - 1; c++)
    {
        end++;
    }
    //สลับ
    for (c = 0; c < length/2; c++)
    {        
        temp   = *end;
        *end   = *begin;
        *begin = temp;
 
        begin++;
        end--;
    }
}

//ถ้ามีของใน Stack ให้เอาของออกมา พร้อมลบ Index ตัวบนสุด
char popStack(stack_T* stack)
{
    if(stack->topIndex == -1)
        return -1;
    else
        return stack->Stack[(stack->topIndex)--];
}

//เพิ่ม Index ตัวบนสุดแล้วใส่ของที่ป้อนมาลง Stack
void pushStack(char inp, stack_T* stack)
{
    (stack->topIndex)++; 
    stack->Stack[stack->topIndex] = inp;
}

//คืนเป็น Pointer ไป (กันวุ่นวาย)
stack_T* StackInfixToPostfix(char expression[],char mode[])
{
    //เป็น Stack ไว้ดอง
    stack_T StackForPostfix;
    //อันนี้ไว้คำตอบ (ส่งกลับ)
    stack_T* Converted = calloc(1,sizeof(stack_T));

    //Index ตอนไม่มีของจะเป็น -1 ไปก่อน
    StackForPostfix.topIndex = -1;
    Converted->topIndex = -1;

    int ScanIndex = 0,Priority = 0;
    char* pointer;
    

    //ใส่วงเล็บปิด&เปิดไปก่อน
    pushStack('(',&StackForPostfix);

    expression[strlen(expression)] = ')'; 
    expression[strlen(expression)] = '\0'; 
    
    //กำหนดตัวแรกที่จะวน + ตัวแปรไว้สำหรับ pop
    char item = expression[0],PopItem;
    
    while (item != '\0')
    {
        
        //ถ้าเป็น ( ให้เอาใส่ Stack
        if (item == '(')
        {
            pushStack(item,&StackForPostfix);
        }
        //ถ้าเป็นตัวอักษร ช่างมันแล้วใส่ลงคำตอบ
        else if (isalpha(item) != 0)
        {
           pushStack(item,Converted);
        }
        //ถ้าเจอ ) ให้ดึงใส่คำตอบไปเรื่อยๆจนกว่าจะเจอ (
        else if (item == ')')
        {
            
            while ((PopItem = popStack(&StackForPostfix)) != '(')
            {
                pushStack(PopItem,Converted);
            }  

        }
        //ถ้าเจอตัว priority ต่ำกว่า ให้ดึงตัวสูงกว่าไปปริ้นเลย
        //แต่ว่ากรณีของ Postfix จะนับตัวที่เท่ากันด้วย
        //เลยต้องแยกกรณี Prefix กับ Postfix ผ่าน mode
        else if(priority(item) == 1 || priority(item) == 2)
        {
            //ถ้าเป็น Prefix
            if (strcmp("Prefix",mode) == 0)
            {
                //เช็คค่า priority ตัวก่อน
                while (priority(StackForPostfix.Stack[StackForPostfix.topIndex])
                 > priority(item) && StackForPostfix.topIndex != -1)
                {
                    PopItem  = popStack(&StackForPostfix);
                    pushStack(PopItem,Converted);
                } 
                pushStack(item,&StackForPostfix);
            }
            //ถ้าเป็น Postfix
            else
            {
                 //เช็คค่า priority ตัวก่อน
                while (priority(StackForPostfix.Stack[StackForPostfix.topIndex])
                 >= priority(item) && StackForPostfix.topIndex != -1)
                {
                    PopItem  = popStack(&StackForPostfix);
                    pushStack(PopItem,Converted);
                } 
                pushStack(item,&StackForPostfix);
            }
           
        }
        //else ไม่ต้องใส่ เอาไว้ข้ามกรณี Invalid เลย
        
        //เก็บค่า Priority ไว้ให้ตัวใหม่ตรวจ + วนขึ้นตัวใหม่
        //Priority = priority(item);
        ScanIndex++;
        item = expression[ScanIndex];
    
    }

    return Converted;
}

void StackInfixToOther(char* Mode)
{
  //รับข้อมูลเข้า
    char buffer[100],prefix[100];
    stack_T* postfix;
    stack_T* ConvertedPrefix;
  
    printf("Please Enter Infix : ");
    fgets(buffer, 100, stdin);
    EnterCutter(buffer);
    strcpy(prefix,buffer);
    postfix = StackInfixToPostfix(buffer,"Postfix");

  if(strcmp("Prefix", Mode) == 0)
  {
    ////////////////////ลอง Infix to prefix/////////////////////
    
    //Reverse String ก่อน
    reverse(prefix);

    //สลับ ( กับ ) 
    for (int i = 0; i < strlen(prefix); i++)
    {
        if (prefix[i] == '(')
        {
            prefix[i] = ')';
        }
        
        else if (prefix[i] == ')')
        {
            prefix[i] = '(';
        }
        
    }

    //ทำ Postfix
    ConvertedPrefix = StackInfixToPostfix(prefix,"Prefix");

    //reverse postfix เป็น Prefix
    reverse(ConvertedPrefix->Stack);
    printf("The answer is : %s\n",ConvertedPrefix->Stack);
    return;
  }

    
    printf("The answer is : %s\n",postfix->Stack);

  
}

void InfixSelect()
{
  char intbuff[50];
  char set;
  printf("\e[0;94m");
printf("\n================================================================\n\n");
  printf("\e[0m");;

  while(set !='3')
  {
    printf("1.Infix to Postfix\n");
    printf("2.Infix to Prefix\n");
    printf("3.Exit\n");
    printf("Please select the options (1/2/3) : ");
    fgets(intbuff, 50, stdin);
    removeEnter(intbuff);
    set=intbuff[0];
    if(isprint(intbuff[1])!=0)
    {
        printf("\e[0;31m");
        printf("\n-----------------------------Error!-----------------------------\n\n");
        printf("\e[0m");
        continue;
    }
  switch(set)
      {
        case '1':
            StackInfixToOther("Postfix");
            break;
        case '2':
            StackInfixToOther("Prefix");
            break;
        case '3':
            break;
        default:
            printf("e[0;31m");
            printf("\n-----------------------------Error!-----------------------------\n");
            printf("e[0;0m");
            break;
      }
    if(set!='3')
    {
      printf("\e[0;94m");
      printf("\n================================================================\n\n");
      printf("\e[0m");
    }
  }
  
}
//////////////////จบส่วนแปลง Infix เป็นอื่นๆ/////////////////

/////////////////////เริ่มส่วนไว้ใช้คิดเลขทั่วไป////////////////
void EnterCutter(char* arr)
{
    if (arr[strlen(arr)-1] == '\n')
    {
        arr[strlen(arr)-1] = '\0';
    }
    
}

void loopFreeNode(Node* headNode)
{
  Node* loopNode = headNode;
  Node* prevNode = loopNode;
  while (loopNode != NULL)
    {
      prevNode = loopNode;
      loopNode = loopNode->next;
      free(prevNode);
      
    }
}



Node* push(Node* topStack,Node* source) 
{ 
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->data,source->data);
    newNode->priority = source->priority;
  
    newNode->next = topStack;

    //return ให้เป็น Top ใหม่
    return newNode;
}

Node* addNode(Node* tailNode,char *val) 
{ 
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->data,val);
    newNode->next = NULL;
   if (tailNode != NULL)
    {
      tailNode->next = newNode;
    }
    //ใส่ priority
    newNode->priority = priority(val[0]);
  /*
    if (strcmp("sqrt(", val) == 0 || strcmp("root(", val) == 0)
    {
      newNode->priority = 3;
    }
  */

    //return ท้ายใหม่
    return newNode;
}

//อาจลองตัด const
const char* pop(Node** topStack) 
{ 
    Node* prevTopStack = (*topStack);
    //printf("Pop Check %s \n",(*topStack)->data);
    
    (*topStack) = (*topStack)->next;
    char* ReString = (char *)malloc(sizeof(char)*100);
    strcpy(ReString, prevTopStack->data);
    free(prevTopStack);
    //printf("Pop Check : %s\n",ReString);
    return ReString;
}

DoubleNode* pushDouble(DoubleNode* topStack, double data)
{
  DoubleNode* newNode =  (DoubleNode *)malloc(sizeof(DoubleNode));
  newNode->data = data;
  newNode->next = topStack;
  return newNode;
}

double popDouble(DoubleNode** topStack)
{
    DoubleNode* prevTopStack = (*topStack);
    if((*topStack) == NULL)
    {
      return 0;
    }
    (*topStack) = (*topStack)->next;
    double value = prevTopStack->data;
    free(prevTopStack);
    return  value;
}

int CheckEquationValid(char* buffer,queue* q)
{
  /////////////////////ส่วน 1 ดักตรวจ//////////////////////   
  //ดักตัวอักษรแปลกๆ
  int index = 0;
  int open = 0;
  int close = 0;
  int CorrectFlag = 1;
  char CheckHistory[10];
  int Numhistory;
  
  while(buffer[index] != '\0')
  {
    //ถ้าเป็น + - * / ^ ไม่เป็นไร (มี priority)
    if(priority(buffer[index]) != 0)
    {
      //ต้องมี ) หรือ เลขอยู่ด้านหน้า ยกเว้น - ที่ไม่มีของข้างหน้าได้
      if (buffer[index] != '-')
      {
        if (!(index-1 >= 0 && (buffer[index-1] == ')' || 
          isdigit(buffer[index-1]))) )
        {
          //ฟ้อง
          CorrectFlag = 0;
          break;
        }
      }
      
      //ต้องมีตัวเลขหรือ ( อยู่ข้างหลัง sqrt หรือ root 
      if(index+1 <= strlen(buffer) && 
        (buffer[index+1] == '(' || isdigit(buffer[index+1]) ||
        buffer[index+1] == 's' || buffer[index+1] == 'r' ||
        buffer[index+1] == 'a' ))
      {
        index++;
        continue;
      }
      else
      {
        //ฟ้อง
        CorrectFlag = 0;
        break;
      }
    }
    //เป็น ans ให้ตวรจว่าเป็น ans ที่มีอยู่หรือไม่
    else if (buffer[index] == 'a')
    {
      //check 4 ตัวว่ามีต่อมั้ย ถ้า index ยังน้อยกว่า index มากสุด
      if (index+3 <= strlen(buffer))
      {
        //ถ้ามีตัวข้างฟลัง ให้เป็นได้แค่ operator กับ )  เท่านั้น
        if(buffer[index+1] == 'n' && buffer[index+2] == 's' &&
          isdigit(buffer[index+3]) && buffer[index+3]!=0)
        {
          //ถ้ามีตัวหลัง แล้วตัวหลังไม่ใช่ operator และ ) ให้ตีว่าไม่ได้
          if(index+4 <= strlen(buffer) && 
            (priority(buffer[index+4]) == 0) && buffer[index+4] != ')')
          {
            //ฟ้อง
          CorrectFlag = 0;
          break;
          }
          //ดูคิวด้วยว่าคิวสูงสุดคือเท่าไหร่
          //ท้ายคิวคือเลข 1 
          CheckHistory[0] = buffer[index+3];
          CheckHistory[1] = '\0';
          Numhistory = atoi(CheckHistory);
          if(Numhistory > q->count)
          {
            //ฟ้อง
            CorrectFlag = 0;
            break;
          }
          
          //บวกไป 3 ตัว
          index = index+3;
          continue;
        }
        else
        {
          //ฟ้อง
          CorrectFlag = 0;
          break;
        }
      }
      else
      {
        //ฟ้อง
        CorrectFlag = 0;
        break;
      }
    
    } 
    //ถ้าเป็น sqrt หรือ root ไม่เป็นไร โดดข้ามด้วย
    //วงเล็บเปิดต้องต่อ sqrt หรือ root เสมอ
    else if (buffer[index] == 's')
    {
      //check 4 ตัวว่ามีต่อมั้ย ถ้า index ยังน้อยกว่า index มากสุด
      if (index+5 <= strlen(buffer))
      {
        //ถ้ามีตัวข้างหน้า ให้เป็นได้แค่ operator กับ (  เท่านั้น
        if(buffer[index+1] == 'q' && buffer[index+2] == 'r' &&
          buffer[index+3] == 't' && buffer[index+4] == '(' &&    
          (buffer[index+5] == '-' || buffer[index+5] == '(' || 
          isdigit(buffer[index+5])))
        {
          //บวกไป 5 ตัว
          open++;
          index = index+5;
          continue;
        }
        else
        {
          //ฟ้อง
          CorrectFlag = 0;
          break;
        }
      }
      else
      {
        //ฟ้อง
        CorrectFlag = 0;
        break;
      }
    }
    else if (buffer[index] == 'r')
    {
      //check 5 ตัวว่ามีต่อมั้ย ถ้า index ยังน้อยกว่า index มากสุด
      if (index+5 <= strlen(buffer))
      {
        if(buffer[index+1] == 'o' && buffer[index+2] == 'o' &&
          buffer[index+3] == 't' && buffer[index+4] == '(' &&    
          (buffer[index+5] == '-' || buffer[index+1] == '(' || 
          isdigit(buffer[index+5])))
        {
          //บวกไป 5 ตัว
          open++;
          index = index+5;
          continue;
        }
        else
        {
          //ฟ้อง
          CorrectFlag = 0;
          break;
        }
      }
      else
      {
        //ฟ้อง
        CorrectFlag = 0;
        break;
      }
    }
    //ถ้าเป็น ans หน้ามีวงเล็บเปิดกับ
      
    //ถ้าเป็น ( ) หรือเลขไม่เป็นไร แต่วงเล็บเปิดต้องมีวงเล็บปิดเสมอ
    else if (buffer[index] == '(')
    {
      //วงเล็บเปิดต่อได้แค่ตัวเลข - กับ (
      if (index+1 <= strlen(buffer) && (buffer[index+1] == '-' ||
        buffer[index+1] == '(' || isdigit(buffer[index+1])))
      {
          open++;
          index++;
          continue; 
      }
      else
      {
          //ฟ้อง
          CorrectFlag = 0;
          break;
      }
      
    }
    else if (buffer[index] == ')')
    {
      close++;
      index++;
      continue;
    }   
    //ถ้าเป็น . ต้องมีเลขอยู่ข้างหน้าหลังประกบ ที่เหลือเป็น
    else if (buffer[index] == '.')
    {
      if (index-1 >= 0 && index+1 <= strlen(buffer))
      {
        if(isdigit(buffer[index-1]) && isdigit(buffer[index+1]))
        {
          index++;
          continue;
        }
        else
        {
          //ฟ้อง
          CorrectFlag = 0;
          break;
        }
      }
      else
      {
        //ฟ้อง
        CorrectFlag = 0;
        break;
      }
    } 
    //ตัวเลขไม่เป็นไร
    else if (isdigit(buffer[index]))
    {
      index++;
      continue;
    }
    //นอกเหนือกรณีนี้ Invalid Equation
    else
    {
      //ฟ้อง
      CorrectFlag = 0;
      break;
    }
    //index++;
  }

  if (open != close)
  {
    CorrectFlag = 0;
  }
  //test
  /*
  if (CorrectFlag == 1)
  {
    printf("Valid");
  }
  else
  {
    printf("Invalid");
  }
  */
  return CorrectFlag;
}

Node* EquationToNode(char* buffer,queue* q)
{
  /////////////////ส่วน 2 ยัดเป็น Linked Node////////////////

  /*
  1. แปลง ( ) + - * / เป็นก้อนเดียว
  2. แปลงเลขให้ติดกัน โดยถ้าตัวต่อไปไม่ใช่เลขให้หยุดเก็บไว้เท่านั้น
   1) ทำ array ขึ้นมาไว้สำรองเล่นๆ
   2) ดูดเฉพาะตัวเลขที่ใช้ไปเก็บ
   3) clear array ทุกรอบ + รีตัวแปรเป็น　0
  3. sqrt( เก็บเป็นก้อนนึง เจอ ) ให้ pop มั้ง
  */
int i = 0;
int iBefore = 0; 
Node* headNode = NULL;
Node* tailNode = NULL;
DoubleNode* loopQueue = NULL;
char NumberString[100];
char ansString[100];
char CheckHistory[10];
int Numhistory;
int temp;
  
while (buffer[i] != '\0')
  {
    int count = 0;
    iBefore = i;
    //clear
    strcpy(NumberString, "");
    /*
    if (i == 0)
    {
      headNode = tailNode;
    }
    */
    
    //ถ้าหน้า - เป็นเลข แสดงว่าเป็นตัวดำเนินการ
    //แต่ถ้าหน้า - ไม่ใช่เลข แสดงว่าต้องต่อเป็นสตริงเลข
    if(buffer[i] == '-')
    {
      //ต่อแบบดำเนินการ ข้างหน้า - เป็นเลข
      if(i-1 >= 0 && isdigit(buffer[i-1]))
      {
        //ใส่เข้าไป
      NumberString[0] = buffer[i];
      NumberString[1] = '\0';
      //printf("Check\n");
      tailNode = addNode(tailNode,NumberString);
      
      i++;
      }
      //ถ้าเป็น unary -sqrt() 
      //ถ้าข้างหน้ามีตัวอักษรอยู่ ต้องเป็น ( เท่านั้น
      //ถ้าเป็นเลข โดนดักไปแล้ว
      else if (i+1<=strlen(buffer) &&
        (buffer[i+1] == 's' || buffer[i+1] == 'r'))
      {
        strncpy(NumberString, (buffer+i), 6);
        NumberString[6] = '\0';
        //printf("NumberString : %s\n",NumberString);
        tailNode = addNode(tailNode,NumberString);
        i = i+6;
      }
      //ต่อเป็นสตริงเลข
      else
      {
        //ลูปเก็บตัวเลข
        NumberString[0] = '-';
        count++;
        i++;
        if(i+1<=strlen(buffer) &&
        (buffer[i+1] == 'a'))
          
        {
          //ถ้าเป็น ansx ให้ซัมม่อนเลข6ตัวมาจาก history ได้เลย
          CheckHistory[0] = buffer[i+4];
          CheckHistory[1] = '\0';
          Numhistory = atoi(CheckHistory);
          //หา queue ที่ต้องการ
          //หัวคิวมากสุด ท้ายคิวน้อยสุด
          temp = q->count;
          loopQueue = q->front;
          while(temp > Numhistory)
          {
            loopQueue = loopQueue->next;
            temp--;
          }
          sprintf(ansString, "%f" , loopQueue->data);
          
          while(ansString[count-1] != '\0')
          {
            NumberString[count] = ansString[count-1];
            count++;
          }
          i=i+4;
        }
        else
        {
          while(isdigit(buffer[i])!=0 || buffer[i] == '.')
          {
          NumberString[count] = buffer[i];
          count++;
          i++;
          }
        }
        
        
        
      NumberString[count] = '\0';

      tailNode = addNode(tailNode,NumberString);
      }
    }
    else if (buffer[i] == 'a')
    {
          
          //ถ้าเป็น ansx ให้ซัมม่อนเลข6ตัวมาจาก history ได้เลย
          CheckHistory[0] = buffer[i+3];
          CheckHistory[1] = '\0';
          Numhistory = atoi(CheckHistory);
          //หา queue ที่ต้องการ
          //หัวคิวมากสุด ท้ายคิวน้อยสุด
          temp = q->count;
          //printf("Check\n");
          loopQueue = q->front;
          while(temp > Numhistory)
          {
            loopQueue = loopQueue->next;
            temp--;
          }
          sprintf(ansString, "%f" , loopQueue->data);
          strcpy(NumberString, ansString);
          tailNode = addNode(tailNode,NumberString);
          i = i+4;        
    }
    
    //แปลง ( ) +  * / เป็นก้อนเดียว
    else if (buffer[i] == '(' || buffer[i] == ')' ||
      priority(buffer[i]) != 0 )
    {
      
      //ใส่เข้าไป
      NumberString[0] = buffer[i];
      NumberString[1] = '\0';
      //printf("Check\n");
      tailNode = addNode(tailNode,NumberString);
      
      i++;

    }
    else if (buffer[i] == 's' || buffer[i] == 'r')
    {
      strncpy(NumberString, (buffer+i), 5);
      NumberString[5] = '\0';
      tailNode = addNode(tailNode,NumberString);
      i = i+5;
      
    }
      
    else if (isdigit(buffer[i]))
    {
      //ลูปเก็บตัวเลข
      while(isdigit(buffer[i])!=0 || buffer[i] == '.')
        {
          NumberString[count] = buffer[i];
          count++;
          i++;
        }
      NumberString[count] = '\0';

      tailNode = addNode(tailNode,NumberString);
    }
    else
    {
      i++;
    }
    
    if (iBefore == 0)
    {
        headNode = tailNode;
    }
    
  }
  

  return headNode;
  
}

Node* NodeInfixtoPostfix(Node* headNodeInfix)
{
    ////////////ส่วนที่ 3 Infix to Postfix/////////////////
  
    //เป็น Stack ไว้ดอง
    Node* topStack = NULL;
    //อันนี้ไว้คำตอบ (ส่งกลับ)
    Node* headStack = NULL;
    Node* tailStack = NULL;

    //Dummy Node
    Node* DummyNode = (Node *)malloc(sizeof(Node));
    //char Dummy[100];

    //Index ตอนไม่มีของจะเป็น -1 ไปก่อน
    //StackForPostfix.topIndex = -1;
    //Converted->topIndex = -1;

    char* pointer;


    //ใส่วงเล็บปิด&เปิดไปก่อน
    strcpy(DummyNode->data, "(");
    topStack = push(topStack,DummyNode);

    //หาท้าย Node
    Node* tailNode = headNodeInfix;
    Node* loopNode = headNodeInfix;
    while(loopNode != NULL)
    {
      tailNode = loopNode;
      loopNode = loopNode->next;
    }

    //strcpy(Dummy, ")");
    tailNode = addNode(tailNode, ")");
    //expression[strlen(expression)] = ')'; 
    //expression[strlen(expression)] = '\0'; 
    
    //กำหนดตัวแรกที่จะวน + ตัวแปรไว้สำหรับ pop
    loopNode = headNodeInfix;
    char PopItem[100];
    //char item = expression[0],PopItem;

    
  
    while (loopNode != NULL)
    {
        //printf("Check Node data : %s\n",loopNode->data);
        //ถ้าเป็น ( ให้เอาใส่ Stack (รวม root sqrt ด้วยมั้ง)
        if (strcmp(loopNode->data, "(") == 0 ||
            strcmp(loopNode->data, "sqrt(") == 0 ||
            strcmp(loopNode->data, "root(") == 0 ||
            strcmp(loopNode->data, "-root(") == 0 ||
            strcmp(loopNode->data, "-sqrt(") == 0)
        {
            //printf("Check %s \n",loopNode->data);
            topStack = push(topStack,loopNode);
            //printf("TopStack now : %s\n", topStack->data);
        }
      
        //ถ้าเจอ ) ให้ดึงใส่คำตอบไปเรื่อยๆจนกว่าจะเจอ ( หรือ sqrt( หรือ root(
        else if (strcmp(loopNode->data, ")") == 0)
        {
            
            //เริ่มตัวแรก
            strcpy(PopItem, pop(&topStack));
            while (strcmp(PopItem,"(") != 0 && 
                strcmp(PopItem, "sqrt(") != 0 &&
                strcmp(PopItem, "root(") != 0 &&
                strcmp(PopItem, "-sqrt(") != 0 &&
                strcmp(PopItem, "-root(") != 0)
            {
              
                tailStack  = addNode(tailStack,PopItem);
                //ไม่มีหัว ให้เอาตัวที่ได้ตัวแรกเป็นหัว
                if (headStack == NULL)
                {
                  headStack = tailStack;
                }
                //printf("Else if loop Check\n");
                //Pop สำหรับตัวต่อๆไป
                strcpy(PopItem, pop(&topStack));
              
            }  
            //ถ้าเป็น sqrt หรือ root เอาไปต่อหลัง Node คำตอบด้วย
            if(strcmp(PopItem, "sqrt(") == 0 ||
                strcmp(PopItem, "root(") == 0 ||
              strcmp(PopItem, "-root(") == 0 ||
              strcmp(PopItem, "-sqrt(") == 0)
            {
              tailStack = addNode(tailStack,PopItem);
            }
            
        }
        //ถ้าเจอตัว priority ต่ำกว่า ให้ดึงตัวสูงกว่าไปปริ้นเลย
        //แต่ว่ากรณีของ Postfix จะนับตัวที่เท่ากันด้วย
        //ไม่รวมวงเล็บนะ
        else if(loopNode->priority != 0)
        {

                 //เช็คค่า priority ตัวก่อน
                while (topStack != NULL && (topStack->priority
                 >= loopNode->priority))
                {
                    //แก้บัค ถ้าเจอตัว priority ต่ำกว่าแต่ไม่ใช่ ( ถึงจะ Pop
                    //printf("TopStack %s Priority %d\n", topStack->data,                     topStack->priority);
                    //printf("loopNode %s Priority %d\n", loopNode->data,                     loopNode->priority);
                    if(strcmp(topStack->data, "(") != 0 &&
                      strcmp(topStack->data, "sqrt(") != 0 &&
                      strcmp(topStack->data, "root(") != 0 &&
                      strcmp(topStack->data, "-sqrt(") != 0 &&
                      strcmp(topStack->data, "-root(") != 0)
                    {
                      strcpy(PopItem, pop(&topStack));
                    }
                    else
                    {
                      break;
                    }
                    tailStack = addNode(tailStack, PopItem);
                    //PopItem  = pop(&StackForPostfix);
                    //push(PopItem,Converted);
                } 
                //ใส่ Stack
                topStack = push(topStack,loopNode);
            
           
        }
        //else ถ้าเป็นตัวเลข ช่างมันแล้วใส่ลงคำตอบ
        else
        {
          tailStack = addNode(tailStack, loopNode->data);
        }
        
        //ขึ้นตัวใหม่
        loopNode = loopNode->next;

        //ไม่มีหัว ให้เอาตัวที่ได้ตัวแรกเป็นหัว
        if (headStack == NULL)
        {
          headStack = tailStack;
        }
    }
  free(DummyNode);
  //printf("finish!\n");
  return headStack;
}

int CalculateFromPostfix(Node* headStack,double* StoringAnswer)
{
  ////////////////////ส่วนที่ 4 คิดเลข//////////////////////
    Node* loopCheck = headStack;
    DoubleNode* DoubleStack = NULL;
    /*
      CorrectFlag 
      0 = ไม่ได้เพราะหาร 0
      1 = สำเร็จ
      2 = ไม่ได้ เพราะจะหารเอาเศษกับเลขทศนิยม
      -1 = ไมได้ เพราะว่าในรูทติดลบ
      3 = ไม่ได้ เพราะ 0^0
    */
    int CorrectFlag = 1; 
    
    while (loopCheck != NULL)
    {
      double val1 = 0,val2 = 0,result = 0;
      int temp1 = 0,temp2 = 0,tempResult = 0;
      //ถ้าเจอ operator ให้ Pop เลขที่จะใช้แล้วเอาลง 
      if (strcmp(loopCheck->data, "+") == 0)
      {
        //val1 + val2
        val2 = popDouble(&DoubleStack);
        val1 = popDouble(&DoubleStack);

        //บวก
        result = (val1)+(val2);
      }
      else if(strcmp(loopCheck->data, "-") == 0)
      {
        //val1 - val2
        val2 = popDouble(&DoubleStack);
        val1 = popDouble(&DoubleStack);

        //ลบ
        result = (val1)-(val2);
      }
      else if(strcmp(loopCheck->data, "*") == 0)
      {
        //val1 * val2
        val2 = popDouble(&DoubleStack);
        val1 = popDouble(&DoubleStack);

        //คูณ
        result = (val1)*(val2);
      }
      else if(strcmp(loopCheck->data, "/") == 0)
      {
        //val1 / val2
        val2 = popDouble(&DoubleStack);
        val1 = popDouble(&DoubleStack);
        //ดักหาร 0
        if (val2 == 0)
        {
          CorrectFlag = 0;
          break;
        }
        //หาร
        result = (val1)/(val2);
      }
      else if(strcmp(loopCheck->data, "%") == 0)
      {
        //val1 % val2
        val2 = popDouble(&DoubleStack);
        val1 = popDouble(&DoubleStack);
        //หารเอาเศษ ต้องเป็นเลขจำนวนเต็มเท่านั้น 
        if(val1 != floor(val1) || val2 != floor(val2))
        {
          CorrectFlag = 2;
          break;
        }
        //ดักหาร 0
        if (val2 == 0)
        {
          CorrectFlag = 0;
          break;
        }
        //หารเอาเศษ
        temp1 = (int)val1;
        temp2 = (int)val2;
        tempResult = (temp1)%(temp2);
        result = (double) tempResult;
      }
      else if(strcmp(loopCheck->data, "^") == 0)
      {
        //val1 ^ val2
        val2 = popDouble(&DoubleStack);
        val1 = popDouble(&DoubleStack);

        if (val1 == 0 && val2 == 0)
        {
          CorrectFlag = 3;
          break;
        }
        
        //กำลัง
        result = pow(val1, val2);
      }
      else if(strcmp(loopCheck->data, "sqrt(") == 0 ||
        strcmp(loopCheck->data, "root(") == 0)
      {
        //sqrt(val1) 
        val1 = popDouble(&DoubleStack);
        //ดูว่าใน root น้อยกว่า 0 มั้ย
        if (val1<0)
        {
          CorrectFlag = -1;
          break;
        }
        //หาร
        result = sqrt(val1);
      }
      else if (strcmp(loopCheck->data, "-sqrt(") == 0 ||
        strcmp(loopCheck->data, "-root(") == 0)
      {
        //-sqrt(val1) 
        val1 = popDouble(&DoubleStack);
        //ดูว่าใน root น้อยกว่า 0 มั้ย
        if (val1<0)
        {
          CorrectFlag = -1;
          break;
        }
        //หาร
        result = (sqrt(val1) * (-1));
      }
      //ถ้าเจอเลข ให้เอาลง Stack
      else
      {
        //แปลงสตริงเป็น double
        result = strtod(loopCheck->data, NULL);
        
      }
      
      //ใส่ Stack
      DoubleStack = pushDouble(DoubleStack, result);
      loopCheck = loopCheck->next;
    }
  
  if (CorrectFlag == 1)
  {
    (*StoringAnswer) = popDouble(&DoubleStack);
  }

  //free ของใน Stack ถ้ามันยังเหลือ
  DoubleNode* loopFree = DoubleStack;
  DoubleNode* prevNode = loopFree;
  while(loopFree != NULL)
  {
    prevNode = loopFree;
    loopFree = loopFree->next;
    free(prevNode);
    
  }
  
  return CorrectFlag;
}

//ต้องใส่ฟังก์ชั่นเก็บประวัติในนี้ด้วย
void CalculateFunction(int digit, queue* q)
{
  /*
    สิ่งที่ต้องทำ (ค่อยแก้ตรง autosave)
    1.รับสตริง ดักตัวอักษรแปลกๆ (✓) 
    2.แปลงสตริงเป็นก้อน Node แล้วทำเป็น linked Stack (✓) 
    3.แปลง Linked Stack จาก Infix เป็น Postfix (✓)
    4.ค่อยคิดวิธีการคำนวณที่หลัง (✓)
      - เปลี่ยนมาใช้ double แล้ว
      - strtod เอาตอนถอดมาเป็นตัวเลข
      - Stack คิดเอา
  ----ดักพวกหาร 0 รูทติดลบ
  */
  char buffer[200];
  printf("\e[0;94m");
  printf("\n================================================================\n\n");
  printf("\e[0m");;
  printf("Please Enter the Equation : ");
  fgets(buffer,200,stdin);
  EnterCutter(buffer);
  
  int CorrectFlag = CheckEquationValid(buffer,q);
  if(CorrectFlag != 1)
  {
    printf("\e[0;31m");
    printf("Error : Invalid Equation\n");
    printf("\e[0;0m");
  }
  else
  {
    
    Node* headNodeInfix = NULL;
    
    headNodeInfix = EquationToNode(buffer,q);
    //printf("Check\n");
    /*
    Node* CheckPostfix = headNodeInfix;
    while(CheckPostfix != NULL)
      {
        printf("%s ",CheckPostfix->data);
        CheckPostfix = CheckPostfix->next;
      }
    printf("\n");
    */
    //มีปัญหาตรงนี้
    Node* headStack = NodeInfixtoPostfix(headNodeInfix);
    double StoringAnswer = 0;
    
    double answer = 0;
    /*
    Node* CheckPostfix = headStack;
    while(CheckPostfix != NULL)
      {
        printf("%s ",CheckPostfix->data);
        CheckPostfix = CheckPostfix->next;
      }
    printf("\n");
    */
    CorrectFlag = CalculateFromPostfix(headStack, &StoringAnswer);

    //printf("Calculate Check\n");
    
    //check Status
    if (CorrectFlag == -1)
    {
      printf("\e[0;31m");
      printf("Error : sqrt with value less than 0\n");
      printf("\e[0;0m");
    }
    else if (CorrectFlag == 0)
    {
      printf("\e[0;31m");
      printf("Error : Divide by 0\n");
      printf("\e[0;0m");
    }
    else if (CorrectFlag == 2)
    {
      printf("\e[0;31m");
      printf("Error : Modulo with non-integer value\n");
      printf("\e[0;0m");
    }
    else if (CorrectFlag == 3)
    {
      printf("\e[0;31m");
      printf("Error : 0 Powered by 0\n");
      printf("\e[0;0m");
    }
    else
    {
      /* เอาเข้าคิวประวัติด้วย*/
      enqueue(q, StoringAnswer);
      //ตัวสุดท้ายใน Stack คือคำตอบ
      printf("The Answer is : ");
      printans(StoringAnswer, digit);
    }
      
      //printf("The answer is : %.6lf",StoringAnswer);
    

    loopFreeNode(headNodeInfix);
    loopFreeNode(headStack);

  }  
}
/////////////////////จบส่วนไว้ใช้คิดเลขทั่วไป///////////////////

void welcome()
{
printf("\e[34;47m");
printf("████████████████████████████████████████████████████████████████\n");
printf("█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█\n");
printf("█░░░░░░\e[0;104m╔╗╔╗╔╗╔═══╗╔╗\e[34;47m░░░\e[0;104m╔═══╗╔═══╗╔═╗╔═╗╔═══╗\e[34;47m░░\e[0;104m╔════╗╔═══╗\e[34;47m░░░░░░█\n");
printf("█░░░░░░\e[0;104m║║║║║║║╔══╝║║\e[34;47m░░░\e[0;104m║╔═╗║║╔═╗║║║╚╝║║║╔══╝\e[34;47m░░\e[0;104m║╔╗╔╗║║╔═╗║\e[34;47m░░░░░░█\n");
printf("█░░░░░░\e[0;104m║║║║║║║╚══╗║║\e[34;47m░░░\e[0;104m║║\e[34;47m░\e[0;104m╚╝║║\e[34;47m░\e[0;104m║║║╔╗╔╗║║╚══╗\e[34;47m░░\e[0;104m╚╝║║╚╝║║\e[34;47m░\e[0;104m║║\e[34;47m░░░░░░█\n");
printf("█░░░░░░\e[0;104m║╚╝╚╝║║╔══╝║║\e[34;47m░\e[0;104m╔╗║║\e[34;47m░\e[0;104m╔╗║║\e[34;47m░\e[0;104m║║║║║║║║║╔══╝\e[34;47m░░░░\e[0;104m║║\e[34;47m░░\e[0;104m║║\e[34;47m░\e[0;104m║║\e[34;47m░░░░░░█\n");
printf("█░░░░░░\e[0;104m╚╗╔╗╔╝║╚══╗║╚═╝║║╚═╝║║╚═╝║║║║║║║║╚══╗\e[34;47m░░░░\e[0;104m║║\e[34;47m░░\e[0;104m║╚═╝║\e[34;47m░░░░░░█\n");
printf("█░░░░░░░\e[0;104m╚╝╚╝\e[34;47m░\e[0;104m╚═══╝╚═══╝╚═══╝╚═══╝╚╝╚╝╚╝╚═══╝\e[34;47m░░░░\e[0;104m╚╝\e[34;47m░░\e[0;104m╚═══╝\e[34;47m░░░░░░█\n");
printf("█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█\n");
printf("█░░░░░░░░\e[0;104m╔═══╗╔═══╗╔══╗\e[34;47m░\e[0;104m╔═══╗╔═══╗╔═╗\e[34;47m░\e[0;104m╔╗\e[34;47m░░░\e[0;104m╔═══╗╔═══╗\e[34;47m░░░░░░░░░░█\n");
printf("█░░░░░░░░\e[0;104m║╔═╗║║╔══╝║╔╗║\e[34;47m░\e[0;104m║╔═╗║║╔═╗║║║╚╗║║\e[34;47m░░░\e[0;104m║╔═╗║║╔═╗║\e[34;47m░░░░░░░░░░█\n");
printf("█░░░░░░░░\e[0;104m║╚═╝║║╚══╗║╚╝╚╗║║\e[34;47m░\e[0;104m║║║╚═╝║║╔╗╚╝║\e[34;47m░░░\e[0;104m║║\e[34;47m░\e[0;104m║║║╚══╗\e[34;47m░░░░░░░░░░█\n");
printf("█░░░░░░░░\e[0;104m║╔╗╔╝║╔══╝║╔═╗║║║\e[34;47m░\e[0;104m║║║╔╗╔╝║║╚╗║║\e[34;47m░░░\e[0;104m║╚═╝║╚══╗║\e[34;47m░░░░░░░░░░█\n");
printf("█░░░░░░░░\e[0;104m║║║╚╗║╚══╗║╚═╝║║╚═╝║║║║╚╗║║\e[34;47m░\e[0;104m║║║\e[34;47m░░░\e[0;104m║╔═╗║║╚═╝║\e[34;47m░░░░░░░░░░█\n");
printf("█░░░░░░░░\e[0;104m╚╝╚═╝╚═══╝╚═══╝╚═══╝╚╝╚═╝╚╝\e[34;47m░\e[0;104m╚═╝\e[34;47m░░░\e[0;104m╚╝\e[34;47m░\e[0;104m╚╝╚═══╝\e[34;47m░░░░░░░░░░█\n");
printf("█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█\n");
printf("█░\e[0;104m╔═══╗\e[34;47m░░\e[0;104m╔═══╗╔═══╗╔╗\e[34;47m░░░\e[0;104m╔═══╗╔╗\e[34;47m░\e[0;104m╔╗╔╗\e[34;47m░░░\e[0;104m╔═══╗╔════╗╔═══╗╔═══╗╔╗\e[34;47m░█\n");
printf("█░\e[0;104m║╔═╗║\e[34;47m░░\e[0;104m║╔═╗║║╔═╗║║║\e[34;47m░░░\e[0;104m║╔═╗║║║\e[34;47m░\e[0;104m║║║║\e[34;47m░░░\e[0;104m║╔═╗║║╔╗╔╗║║╔═╗║║╔═╗║║║\e[34;47m░█\n");
printf("█░\e[0;104m║║\e[34;47m░\e[0;104m║║\e[34;47m░░\e[0;104m║║\e[34;47m░\e[0;104m╚╝║║\e[34;47m░\e[0;104m║║║║\e[34;47m░░░\e[0;104m║║\e[34;47m░\e[0;104m╚╝║║\e[34;47m░\e[0;104m║║║║\e[34;47m░░░\e[0;104m║║\e[34;47m░\e[0;104m║║╚╝║║╚╝║║\e[34;47m░\e[0;104m║║║╚═╝║║║\e[34;47m░█\n");
printf("█░\e[0;104m║╚═╝║\e[34;47m░░\e[0;104m║║\e[34;47m░\e[0;104m╔╗║╚═╝║║║\e[34;47m░\e[0;104m╔╗║║\e[34;47m░\e[0;104m╔╗║║\e[34;47m░\e[0;104m║║║║\e[34;47m░\e[0;104m╔╗║╚═╝║\e[34;47m░░\e[0;104m║║\e[34;47m░░\e[0;104m║║\e[34;47m░\e[0;104m║║║╔╗╔╝╚╝\e[34;47m░█\n");
printf("█░\e[0;104m║╔═╗║\e[34;47m░░\e[0;104m║╚═╝║║╔═╗║║╚═╝║║╚═╝║║╚═╝║║╚═╝║║╔═╗║\e[34;47m░░\e[0;104m║║\e[34;47m░░\e[0;104m║╚═╝║║║║╚╗╔╗\e[34;47m░█\n");
printf("█░\e[0;104m╚╝\e[34;47m░\e[0;104m╚╝\e[34;47m░░\e[0;104m╚═══╝╚╝\e[34;47m░\e[0;104m╚╝╚═══╝╚═══╝╚═══╝╚═══╝╚╝\e[34;47m░\e[0;104m╚╝\e[34;47m░░\e[0;104m╚╝\e[34;47m░░\e[0;104m╚═══╝╚╝╚═╝╚╝\e[34;47m░█\n");
printf("█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█\n");
printf("████████████████████████████████████████████████████████████████");
printf("\e[0m");
printf("\n");
}


void slime(){
printf("\e[34;47m████████████████████████████████████████████████████████████████\e[m\n");
printf("\e[34;47m█\e[48;5;15m                                                              \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m                    \e[38;5;15;48;5;15m▄\e[38;5;195;48;5;15m▄▄▄\e[38;5;189;48;5;195m▄▄▄▄▄▄▄▄▄▄▄\e[38;5;189;48;5;255m▄\e[38;5;189;48;5;195m▄▄▄\e[38;5;195;48;5;15m▄▄▄\e[38;5;15;48;5;15m▄\e[48;5;15m                   \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m               \e[38;5;15;48;5;15m▄\e[38;5;255;48;5;15m▄\e[38;5;195;48;5;15m▄\e[38;5;189;48;5;15m▄\e[38;5;189;48;5;254m▄\e[48;5;189m                      \e[38;5;189;48;5;189m▄\e[38;5;189;48;5;195m▄\e[38;5;195;48;5;15m▄▄\e[48;5;15m                \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m             \e[38;5;195;48;5;15m▄\e[38;5;189;48;5;15m▄\e[38;5;195;48;5;195m▄\e[38;5;255;48;5;189m▄\e[38;5;15;48;5;189m▄\e[38;5;15;48;5;15m▄▄▄\e[38;5;15;48;5;254m▄\e[38;5;195;48;5;189m▄\e[48;5;189m                      \e[38;5;189;48;5;189m▄▄\e[38;5;189;48;5;255m▄\e[38;5;195;48;5;15m▄\e[38;5;15;48;5;15m▄\e[48;5;15m            \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m          \e[38;5;15;48;5;15m▄\e[38;5;195;48;5;15m▄\e[38;5;189;48;5;195m▄\e[38;5;15;48;5;189m▄\e[38;5;15;48;5;195m▄\e[38;5;15;48;5;15m▄\e[48;5;15m     \e[38;5;15;48;5;15m▄\e[38;5;189;48;5;195m▄\e[48;5;189m                         \e[38;5;189;48;5;189m▄\e[38;5;189;48;5;195m▄\e[38;5;189;48;5;255m▄\e[38;5;255;48;5;15m▄\e[48;5;15m          \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m         \e[38;5;195;48;5;15m▄\e[38;5;189;48;5;195m▄\e[38;5;15;48;5;189m▄\e[38;5;15;48;5;255m▄\e[48;5;15m       \e[38;5;15;48;5;15m▄\e[38;5;189;48;5;255m▄\e[38;5;189;48;5;189m▄\e[48;5;189m                            \e[38;5;189;48;5;195m▄▄\e[38;5;15;48;5;15m▄\e[48;5;15m        \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m       \e[38;5;195;48;5;15m▄\e[38;5;189;48;5;195m▄\e[38;5;195;48;5;189m▄\e[38;5;15;48;5;255m▄\e[48;5;15m       \e[38;5;15;48;5;15m▄\e[38;5;195;48;5;15m▄\e[38;5;189;48;5;195m▄\e[48;5;189m  \e[38;5;189;48;5;189m▄\e[38;5;152;48;5;189m▄\e[38;5;146;48;5;189m▄\e[38;5;110;48;5;153m▄▄\e[38;5;110;48;5;110m▄▄▄▄▄▄\e[38;5;110;48;5;153m▄▄▄\e[38;5;146;48;5;189m▄\e[38;5;152;48;5;189m▄\e[38;5;153;48;5;189m▄\e[38;5;189;48;5;189m▄\e[48;5;189m            \e[38;5;189;48;5;189m▄\e[38;5;195;48;5;255m▄\e[38;5;15;48;5;15m▄\e[48;5;15m      \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m     \e[38;5;15;48;5;15m▄\e[38;5;195;48;5;255m▄\e[38;5;189;48;5;189m▄\e[48;5;189m \e[38;5;15;48;5;255m▄\e[48;5;15m      \e[38;5;255;48;5;15m▄\e[38;5;195;48;5;15m▄\e[38;5;189;48;5;255m▄\e[38;5;189;48;5;189m▄\e[38;5;153;48;5;189m▄▄\e[38;5;110;48;5;152m▄\e[48;5;110m                 \e[38;5;110;48;5;110m▄\e[38;5;110;48;5;153m▄\e[38;5;153;48;5;189m▄\e[38;5;189;48;5;189m▄\e[48;5;189m          \e[38;5;189;48;5;189m▄\e[38;5;189;48;5;195m▄\e[38;5;195;48;5;15m▄\e[48;5;15m     \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m    \e[38;5;195;48;5;15m▄\e[38;5;189;48;5;195m▄\e[48;5;189m   \e[38;5;195;48;5;255m▄\e[38;5;255;48;5;15m▄▄▄\e[38;5;195;48;5;15m▄\e[38;5;189;48;5;15m▄\e[38;5;189;48;5;195m▄\e[38;5;189;48;5;189m▄▄\e[38;5;153;48;5;189m▄\e[38;5;110;48;5;153m▄\e[38;5;110;48;5;110m▄\e[48;5;110m          \e[38;5;152;48;5;110m▄\e[38;5;189;48;5;153m▄\e[38;5;189;48;5;189m▄\e[38;5;153;48;5;152m▄\e[48;5;110m        \e[38;5;110;48;5;146m▄\e[38;5;153;48;5;189m▄\e[48;5;189m           \e[38;5;189;48;5;195m▄\e[38;5;195;48;5;15m▄\e[48;5;15m    \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m  \e[38;5;15;48;5;15m▄\e[38;5;195;48;5;15m▄\e[38;5;189;48;5;195m▄\e[48;5;189m     \e[38;5;189;48;5;189m▄▄▄\e[48;5;189m   \e[38;5;189;48;5;189m▄\e[38;5;110;48;5;153m▄\e[38;5;110;48;5;110m▄\e[48;5;110m            \e[38;5;110;48;5;152m▄\e[38;5;110;48;5;189m▄\e[38;5;110;48;5;255m▄\e[38;5;110;48;5;110m▄\e[48;5;110m         \e[38;5;153;48;5;153m▄\e[48;5;189m            \e[38;5;189;48;5;189m▄\e[38;5;195;48;5;15m▄\e[38;5;15;48;5;15m▄\e[48;5;15m  \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m  \e[38;5;195;48;5;15m▄\e[38;5;189;48;5;195m▄\e[48;5;189m \e[38;5;189;48;5;189m▄\e[38;5;15;48;5;189m▄▄\e[38;5;195;48;5;189m▄\e[48;5;189m       \e[38;5;189;48;5;189m▄\e[38;5;110;48;5;110m▄\e[48;5;110m                         \e[38;5;110;48;5;110m▄\e[38;5;152;48;5;153m▄\e[48;5;189m             \e[38;5;189;48;5;189m▄\e[38;5;195;48;5;195m▄\e[48;5;15m  \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m  \e[38;5;189;48;5;195m▄\e[48;5;189m  \e[38;5;195;48;5;255m▄\e[48;5;15m \e[38;5;15;48;5;15m▄\e[38;5;195;48;5;195m▄\e[48;5;189m       \e[38;5;189;48;5;189m▄\e[38;5;189;48;5;153m▄▄\e[38;5;153;48;5;110m▄\e[38;5;110;48;5;110m▄\e[48;5;110m                      \e[38;5;153;48;5;110m▄\e[38;5;189;48;5;189m▄\e[48;5;189m              \e[38;5;189;48;5;189m▄\e[38;5;15;48;5;15m▄\e[48;5;15m \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m \e[38;5;195;48;5;195m▄\e[48;5;189m   \e[38;5;189;48;5;189m▄\e[38;5;189;48;5;195m▄\e[38;5;189;48;5;189m▄\e[48;5;189m         \e[38;5;189;48;5;189m▄\e[38;5;153;48;5;189m▄\e[38;5;110;48;5;146m▄\e[48;5;110m                      \e[38;5;110;48;5;110m▄\e[38;5;110;48;5;153m▄▄\e[38;5;146;48;5;189m▄\e[38;5;153;48;5;189m▄▄▄\e[38;5;152;48;5;189m▄\e[38;5;189;48;5;189m▄\e[48;5;189m  \e[38;5;152;48;5;189m▄\e[38;5;66;48;5;189m▄\e[38;5;254;48;5;189m▄\e[48;5;189m    \e[38;5;189;48;5;189m▄\e[48;5;15m \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[38;5;15;48;5;15m▄\e[38;5;189;48;5;189m▄\e[48;5;189m            \e[38;5;189;48;5;189m▄▄\e[38;5;153;48;5;189m▄\e[38;5;146;48;5;153m▄\e[48;5;110m                                 \e[38;5;110;48;5;152m▄\e[38;5;240;48;5;189m▄\e[38;5;246;48;5;236m▄\e[38;5;189;48;5;103m▄\e[38;5;189;48;5;189m▄\e[48;5;189m     \e[38;5;15;48;5;15m▄\e[34;47m█\e[m\n");
printf("\e[34;47m█\e[38;5;15;48;5;15m▄\e[38;5;189;48;5;189m▄\e[48;5;189m        \e[38;5;189;48;5;189m▄\e[38;5;153;48;5;189m▄▄\e[38;5;110;48;5;189m▄\e[38;5;110;48;5;146m▄\e[38;5;110;48;5;110m▄\e[48;5;110m                                  \e[38;5;109;48;5;110m▄\e[38;5;66;48;5;67m▄\e[38;5;110;48;5;67m▄\e[38;5;110;48;5;152m▄\e[48;5;189m      \e[38;5;195;48;5;189m▄\e[48;5;15m \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m \e[38;5;189;48;5;189m▄\e[48;5;189m      \e[38;5;189;48;5;189m▄\e[38;5;110;48;5;189m▄\e[38;5;110;48;5;153m▄\e[38;5;110;48;5;110m▄\e[48;5;110m       \e[38;5;110;48;5;110m▄\e[38;5;59;48;5;110m▄\e[38;5;237;48;5;110m▄\e[38;5;66;48;5;110m▄\e[38;5;110;48;5;110m▄▄\e[48;5;110m                       \e[38;5;110;48;5;110m▄\e[38;5;66;48;5;67m▄\e[38;5;110;48;5;67m▄\e[38;5;110;48;5;110m▄\e[48;5;110m \e[38;5;146;48;5;110m▄\e[48;5;189m     \e[38;5;195;48;5;189m▄\e[38;5;15;48;5;15m▄\e[48;5;15m \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m \e[38;5;15;48;5;15m▄\e[38;5;189;48;5;189m▄\e[48;5;189m   \e[38;5;189;48;5;189m▄\e[38;5;153;48;5;153m▄\e[38;5;110;48;5;110m▄\e[48;5;110m           \e[38;5;110;48;5;110m▄▄\e[38;5;110;48;5;60m▄▄\e[38;5;110;48;5;239m▄\e[38;5;110;48;5;66m▄\e[38;5;238;48;5;110m▄▄\e[38;5;110;48;5;110m▄▄\e[48;5;110m              \e[38;5;110;48;5;110m▄▄\e[38;5;103;48;5;110m▄\e[38;5;67;48;5;67m▄\e[38;5;110;48;5;66m▄\e[38;5;110;48;5;110m▄\e[48;5;110m  \e[38;5;153;48;5;110m▄\e[38;5;189;48;5;189m▄\e[48;5;189m    \e[38;5;195;48;5;189m▄\e[38;5;15;48;5;195m▄\e[48;5;15m  \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m  \e[38;5;195;48;5;195m▄\e[38;5;195;48;5;189m▄\e[48;5;189m  \e[38;5;189;48;5;189m▄\e[38;5;153;48;5;146m▄\e[38;5;110;48;5;110m▄\e[48;5;110m                  \e[38;5;110;48;5;110m▄\e[38;5;110;48;5;240m▄\e[38;5;110;48;5;60m▄\e[38;5;67;48;5;67m▄\e[38;5;67;48;5;110m▄\e[38;5;66;48;5;110m▄\e[38;5;67;48;5;110m▄\e[48;5;110m \e[38;5;110;48;5;110m▄\e[38;5;67;48;5;110m▄▄\e[48;5;110m     \e[38;5;110;48;5;110m▄\e[38;5;110;48;5;67m▄\e[38;5;110;48;5;103m▄\e[38;5;110;48;5;60m▄\e[38;5;110;48;5;110m▄\e[48;5;110m   \e[38;5;153;48;5;110m▄\e[38;5;189;48;5;153m▄\e[48;5;189m   \e[38;5;195;48;5;189m▄\e[38;5;15;48;5;195m▄\e[38;5;15;48;5;15m▄\e[48;5;15m   \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m  \e[38;5;15;48;5;15m▄\e[38;5;15;48;5;195m▄\e[38;5;195;48;5;189m▄\e[38;5;189;48;5;189m▄\e[48;5;189m \e[38;5;189;48;5;189m▄▄\e[38;5;153;48;5;110m▄▄\e[38;5;110;48;5;110m▄\e[48;5;110m                     \e[38;5;110;48;5;110m▄\e[38;5;110;48;5;67m▄\e[38;5;110;48;5;110m▄▄▄▄\e[48;5;110m     \e[38;5;110;48;5;110m▄▄\e[48;5;110m  \e[38;5;110;48;5;110m▄\e[38;5;152;48;5;110m▄\e[38;5;189;48;5;152m▄\e[48;5;189m  \e[38;5;189;48;5;189m▄\e[38;5;195;48;5;189m▄\e[38;5;15;48;5;195m▄\e[38;5;15;48;5;15m▄\e[48;5;15m     \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m    \e[38;5;15;48;5;15m▄\e[38;5;15;48;5;195m▄\e[38;5;195;48;5;189m▄\e[38;5;189;48;5;189m▄\e[48;5;189m \e[38;5;189;48;5;189m▄▄▄\e[38;5;189;48;5;153m▄\e[38;5;189;48;5;110m▄\e[38;5;152;48;5;110m▄\e[38;5;110;48;5;110m▄\e[48;5;110m                  \e[38;5;110;48;5;110m▄\e[38;5;110;48;5;240m▄\e[38;5;110;48;5;238m▄\e[38;5;110;48;5;103m▄\e[48;5;110m       \e[38;5;110;48;5;110m▄▄\e[38;5;153;48;5;110m▄\e[38;5;189;48;5;153m▄\e[38;5;189;48;5;189m▄\e[48;5;189m \e[38;5;189;48;5;189m▄\e[38;5;195;48;5;189m▄\e[38;5;15;48;5;189m▄\e[38;5;15;48;5;15m▄\e[48;5;15m       \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m      \e[38;5;15;48;5;15m▄\e[38;5;15;48;5;195m▄\e[38;5;15;48;5;189m▄\e[38;5;195;48;5;189m▄▄\e[38;5;189;48;5;189m▄\e[48;5;189m  \e[38;5;189;48;5;189m▄\e[38;5;189;48;5;153m▄▄\e[38;5;189;48;5;152m▄\e[38;5;189;48;5;110m▄\e[38;5;153;48;5;110m▄\e[38;5;146;48;5;110m▄\e[38;5;110;48;5;110m▄▄\e[48;5;110m              \e[38;5;110;48;5;110m▄▄▄▄▄\e[38;5;153;48;5;110m▄\e[38;5;189;48;5;110m▄\e[38;5;189;48;5;153m▄▄\e[38;5;189;48;5;189m▄\e[48;5;189m \e[38;5;189;48;5;189m▄\e[38;5;255;48;5;189m▄\e[38;5;15;48;5;195m▄▄\e[48;5;15m          \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m            \e[38;5;15;48;5;255m▄\e[38;5;15;48;5;195m▄\e[38;5;15;48;5;189m▄▄\e[38;5;195;48;5;189m▄\e[38;5;189;48;5;189m▄\e[48;5;189m    \e[38;5;189;48;5;189m▄\e[38;5;189;48;5;153m▄▄▄▄▄▄\e[38;5;189;48;5;110m▄▄▄▄▄\e[38;5;189;48;5;153m▄▄▄▄▄▄\e[38;5;189;48;5;189m▄▄\e[48;5;189m  \e[38;5;189;48;5;189m▄\e[38;5;195;48;5;189m▄\e[38;5;15;48;5;189m▄\e[38;5;15;48;5;195m▄▄\e[38;5;15;48;5;15m▄\e[48;5;15m            \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m                  \e[38;5;15;48;5;15m▄\e[38;5;15;48;5;195m▄▄▄▄\e[38;5;195;48;5;189m▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\e[38;5;255;48;5;195m▄\e[38;5;15;48;5;195m▄▄▄\e[38;5;15;48;5;15m▄\e[48;5;15m                  \e[34;47m█\e[m\n");
printf("\e[34;47m█\e[48;5;15m                                                              \e[34;47m█\e[m\n");
}

void trucksan(){
  printf ("\e[38;2;254;254;254;48;2;255;255;255m▄\e[48;2;255;255;255m \e[48;2;251;251;251m \e[38;2;205;205;205;48;2;208;208;208m▄\e[38;2;205;204;205;48;2;236;234;235m▄\e[38;2;248;248;248;48;2;228;226;227m▄\e[38;2;253;253;253;48;2;236;235;235m▄\e[38;2;253;253;253;48;2;241;241;241m▄\e[38;2;249;248;249;48;2;224;223;224m▄\e[38;2;217;216;217;48;2;191;190;191m▄\e[38;2;232;232;232;48;2;248;248;248m▄\e[48;2;254;254;254m \e[38;2;254;254;254;48;2;255;255;255m▄\e[48;2;255;255;255m \e[48;2;254;254;254m \e[38;2;253;253;253;48;2;254;254;254m▄▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;253;253;253;48;2;254;254;254m▄▄▄▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;253;253;253;48;2;254;254;254m▄▄▄\e[38;2;252;252;252;48;2;254;254;254m▄▄\e[38;2;251;251;251;48;2;254;254;254m▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;246;246;246;48;2;253;253;253m▄\e[38;2;234;233;233;48;2;241;240;241m▄\e[38;2;231;229;231;48;2;221;219;220m▄\e[38;2;212;210;212;48;2;214;212;213m▄\e[38;2;181;180;182;48;2;215;214;215m▄\e[38;2;139;138;139;48;2;200;198;199m▄\e[38;2;128;128;128;48;2;180;179;180m▄\e[38;2;144;144;145;48;2;180;180;179m▄\e[38;2;161;161;163;48;2;195;195;195m▄\e[38;2;161;161;163;48;2;197;197;198m▄\e[38;2;177;177;178;48;2;201;201;202m▄\e[38;2;195;193;196;48;2;237;235;236m▄\e[38;2;219;218;219;48;2;252;251;252m▄\e[38;2;251;251;251;48;2;254;254;254m▄\e[38;2;253;252;253;48;2;254;254;254m▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;253;252;252;48;2;254;254;254m▄\e[38;2;253;253;253;48;2;254;254;254m▄▄▄▄\e[38;2;253;252;252;48;2;254;254;254m▄\e[38;2;253;253;253;48;2;254;254;254m▄▄▄▄▄▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;253;253;253;48;2;254;254;254m▄▄\e[48;2;254;254;254m \e[48;2;255;255;255m  \e[48;2;254;254;254m \e[38;2;250;250;250;48;2;251;251;251m▄\e[38;2;188;186;187;48;2;207;205;206m▄\e[38;2;234;233;234;48;2;203;202;202m▄\e[38;2;253;253;253;48;2;236;236;236m▄\e[38;2;253;253;253;48;2;239;239;239m▄\e[38;2;244;244;244;48;2;219;217;218m▄\e[38;2;172;172;172;48;2;190;189;190m▄\e[38;2;196;196;196;48;2;201;201;200m▄\e[48;2;251;251;251m \e[48;2;254;254;254m \e[38;2;252;252;252;48;2;250;250;250m▄\e[38;2;251;251;251;48;2;238;238;238m▄\e[38;2;248;248;248;48;2;227;227;227m▄\e[m\n");
printf("\e[38;2;251;251;251;48;2;253;253;253m▄\e[38;2;253;253;253;48;2;255;255;255m▄\e[38;2;250;249;249;48;2;251;251;251m▄\e[38;2;184;183;183;48;2;192;191;192m▄\e[38;2;136;135;135;48;2;174;173;173m▄\e[48;2;253;253;253m \e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;251;251;252;48;2;254;254;254m▄\e[38;2;246;246;246;48;2;252;252;252m▄\e[38;2;225;224;224;48;2;236;235;235m▄\e[38;2;171;169;170;48;2;211;210;211m▄\e[38;2;223;221;222;48;2;247;246;246m▄\e[48;2;252;252;252m \e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;249;249;249;48;2;253;253;253m▄\e[38;2;149;148;149;48;2;219;219;219m▄\e[38;2;175;176;176;48;2;212;212;212m▄\e[38;2;208;208;208;48;2;207;207;207m▄\e[38;2;130;130;129;48;2;205;205;205m▄\e[38;2;97;97;96;48;2;202;202;202m▄\e[38;2;98;98;98;48;2;199;199;199m▄\e[38;2;103;103;103;48;2;202;202;202m▄\e[38;2;109;109;109;48;2;208;208;208m▄\e[38;2;142;142;142;48;2;210;210;210m▄\e[38;2;169;169;169;48;2;215;215;215m▄\e[38;2;201;201;201;48;2;223;223;223m▄\e[38;2;240;239;240;48;2;235;235;235m▄\e[38;2;249;248;248;48;2;244;243;244m▄\e[38;2;172;172;172;48;2;248;247;247m▄\e[38;2;95;95;95;48;2;210;210;210m▄\e[38;2;106;106;106;48;2;159;159;159m▄\e[38;2;131;131;131;48;2;155;155;155m▄\e[38;2;133;132;132;48;2;184;183;184m▄\e[38;2;123;121;122;48;2;225;224;225m▄\e[38;2;178;177;177;48;2;230;228;229m▄\e[38;2;219;219;219;48;2;182;182;183m▄\e[38;2;161;161;161;48;2;118;118;118m▄\e[38;2;102;102;102;48;2;43;43;43m▄\e[38;2;56;57;56;48;2;20;20;19m▄\e[38;2;15;15;15;48;2;25;25;25m▄\e[38;2;12;12;12;48;2;67;67;67m▄\e[38;2;56;56;56;48;2;141;141;141m▄\e[38;2;161;161;161;48;2;176;176;177m▄\e[38;2;113;112;113;48;2;159;158;159m▄\e[38;2;126;126;126;48;2;199;198;199m▄\e[38;2;122;122;121;48;2;217;216;216m▄\e[38;2;118;119;118;48;2;219;219;219m▄\e[38;2;114;115;115;48;2;216;216;216m▄\e[38;2;114;115;114;48;2;213;213;213m▄\e[38;2;112;113;113;48;2;210;210;210m▄\e[38;2;110;110;111;48;2;206;206;207m▄\e[38;2;108;109;109;48;2;202;202;203m▄\e[38;2;104;104;104;48;2;211;211;211m▄\e[38;2;115;115;116;48;2;219;218;218m▄\e[38;2;116;116;116;48;2;219;219;219m▄\e[38;2;117;117;117;48;2;220;220;220m▄\e[38;2;116;116;116;48;2;219;219;219m▄\e[38;2;115;115;116;48;2;218;218;218m▄\e[38;2;118;118;118;48;2;219;219;219m▄\e[38;2;153;153;153;48;2;219;219;219m▄\e[38;2;204;203;204;48;2;221;219;220m▄\e[38;2;160;159;160;48;2;214;214;214m▄\e[38;2;172;172;172;48;2;233;233;233m▄\e[38;2;247;247;247;48;2;252;252;252m▄\e[38;2;254;254;254;48;2;255;255;255m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;241;241;241;48;2;253;253;253m▄\e[38;2;178;176;177;48;2;226;224;225m▄\e[38;2;231;231;231;48;2;216;215;215m▄\e[38;2;252;252;252;48;2;251;251;251m▄\e[38;2;251;251;251;48;2;254;254;254m▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;246;246;246;48;2;249;249;249m▄\e[38;2;174;174;174;48;2;198;198;198m▄\e[38;2;191;191;191;48;2;204;204;204m▄\e[38;2;252;252;252;48;2;251;251;251m▄\e[38;2;255;255;255;48;2;254;254;254m▄▄▄▄\e[m\n");
printf("\e[38;2;244;244;244;48;2;245;245;245m▄\e[38;2;194;194;194;48;2;250;250;250m▄\e[38;2;141;141;141;48;2;233;232;233m▄\e[38;2;120;120;120;48;2;162;161;161m▄\e[38;2;144;142;144;48;2;105;105;105m▄\e[38;2;127;126;126;48;2;194;194;193m▄\e[38;2;115;115;116;48;2;201;201;201m▄\e[38;2;233;231;232;48;2;244;242;244m▄\e[38;2;201;199;200;48;2;154;154;154m▄\e[38;2;140;140;140;48;2;165;165;164m▄\e[38;2;230;230;230;48;2;207;205;205m▄\e[38;2;196;194;196;48;2;193;192;193m▄\e[38;2;200;200;200;48;2;241;241;241m▄\e[38;2;249;249;249;48;2;253;253;253m▄\e[38;2;251;251;251;48;2;252;251;251m▄\e[38;2;179;178;178;48;2;132;131;130m▄\e[38;2;177;175;176;48;2;184;183;184m▄\e[38;2;243;243;243;48;2;236;235;236m▄\e[38;2;125;125;125;48;2;87;86;86m▄\e[38;2;36;36;36;48;2;11;11;9m▄\e[38;2;33;33;33;48;2;11;11;11m▄\e[38;2;33;33;33;48;2;10;10;10m▄\e[38;2;51;51;51;48;2;23;23;23m▄\e[38;2;102;102;102;48;2;83;83;83m▄\e[38;2;143;143;143;48;2;138;138;138m▄\e[38;2;181;181;181;48;2;186;186;186m▄\e[38;2;229;228;229;48;2;235;234;235m▄\e[38;2;138;137;137;48;2;209;207;208m▄\e[38;2;131;131;129;48;2;106;106;106m▄\e[38;2;127;127;127;48;2;117;117;116m▄\e[48;2;128;128;128m \e[38;2;134;134;133;48;2;137;137;137m▄\e[38;2;126;126;127;48;2;129;129;130m▄\e[38;2;107;107;107;48;2;121;120;121m▄\e[38;2;104;104;103;48;2;104;104;104m▄\e[38;2;61;61;61;48;2;158;158;158m▄\e[38;2;209;209;209;48;2;221;221;221m▄\e[38;2;164;164;164;48;2;192;190;190m▄\e[38;2;117;118;118;48;2;174;172;174m▄\e[38;2;52;52;51;48;2;148;148;150m▄\e[38;2;47;47;46;48;2;143;143;144m▄\e[38;2;94;94;93;48;2;151;151;151m▄\e[38;2;140;140;140;48;2;184;184;185m▄\e[38;2;37;37;36;48;2;31;31;31m▄\e[38;2;23;23;22;48;2;10;10;8m▄\e[38;2;23;23;22;48;2;10;10;9m▄\e[38;2;25;25;24;48;2;11;11;10m▄\e[38;2;24;24;25;48;2;10;10;10m▄\e[38;2;23;24;24;48;2;10;10;10m▄\e[38;2;25;25;25;48;2;10;10;10m▄\e[38;2;25;25;25;48;2;11;11;11m▄\e[38;2;25;25;25;48;2;10;10;10m▄\e[38;2;26;26;26;48;2;9;9;9m▄\e[38;2;25;25;24;48;2;10;10;9m▄\e[38;2;24;24;23;48;2;10;10;9m▄\e[38;2;27;28;26;48;2;10;10;9m▄\e[38;2;29;29;29;48;2;11;11;9m▄\e[38;2;29;29;28;48;2;11;11;10m▄\e[38;2;36;36;35;48;2;10;10;9m▄\e[38;2;205;205;204;48;2;152;152;152m▄\e[38;2;208;207;208;48;2;222;222;222m▄\e[38;2;186;186;186;48;2;161;160;161m▄\e[38;2;221;221;221;48;2;192;191;191m▄\e[38;2;254;254;254;48;2;252;252;252m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;225;224;224;48;2;249;248;249m▄\e[38;2;166;166;166;48;2;205;204;204m▄\e[38;2;207;208;208;48;2;191;192;191m▄\e[38;2;155;155;155;48;2;146;146;146m▄\e[38;2;102;102;102;48;2;220;220;220m▄\e[38;2;141;141;142;48;2;190;190;190m▄\e[38;2;125;126;124;48;2;202;202;201m▄\e[38;2;232;231;231;48;2;234;233;233m▄\e[38;2;164;162;163;48;2;125;124;125m▄\e[38;2;200;199;200;48;2;195;194;194m▄\e[38;2;249;249;249;48;2;251;251;251m▄\e[48;2;254;254;254m \e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;251;251;251;48;2;254;254;254m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[m\n");
printf("\e[38;2;36;36;36;48;2;94;94;94m▄\e[38;2;187;187;187;48;2;89;89;89m▄\e[38;2;239;239;239;48;2;169;169;169m▄\e[38;2;212;212;212;48;2;177;177;177m▄\e[38;2;252;251;251;48;2;196;195;197m▄\e[38;2;250;250;250;48;2;185;184;185m▄\e[38;2;249;249;249;48;2;193;193;194m▄\e[38;2;242;242;242;48;2;189;188;190m▄\e[38;2;232;231;232;48;2;129;128;130m▄\e[38;2;210;209;211;48;2;123;123;123m▄\e[38;2;190;190;190;48;2;217;217;217m▄\e[38;2;173;173;173;48;2;144;144;145m▄\e[38;2;159;158;161;48;2;119;118;118m▄\e[38;2;177;176;177;48;2;226;226;226m▄\e[38;2;250;249;249;48;2;251;251;251m▄\e[38;2;252;252;252;48;2;218;217;218m▄\e[38;2;188;186;187;48;2;170;168;169m▄\e[38;2;216;216;216;48;2;180;180;180m▄\e[38;2;229;229;229;48;2;157;157;157m▄\e[38;2;86;86;86;48;2;140;140;140m▄\e[38;2;8;8;8;48;2;146;146;146m▄\e[38;2;11;11;11;48;2;161;161;161m▄\e[38;2;69;69;69;48;2;175;175;175m▄\e[38;2;122;122;122;48;2;194;194;194m▄\e[38;2;183;183;183;48;2;214;214;214m▄\e[38;2;217;217;217;48;2;227;226;227m▄\e[38;2;150;150;150;48;2;202;201;202m▄\e[38;2;90;90;90;48;2;112;113;113m▄\e[38;2;144;144;144;48;2;125;125;124m▄\e[38;2;116;116;116;48;2;110;109;110m▄\e[38;2;99;99;98;48;2;125;125;125m▄\e[38;2;107;107;107;48;2;126;126;126m▄\e[38;2;88;88;87;48;2;116;116;115m▄\e[38;2;48;48;49;48;2;84;84;84m▄\e[38;2;66;66;67;48;2;78;78;77m▄\e[38;2;47;47;47;48;2;66;66;65m▄\e[38;2;226;226;226;48;2;215;215;215m▄\e[38;2;190;190;192;48;2;173;173;173m▄\e[38;2;153;153;154;48;2;88;88;88m▄\e[38;2;154;154;154;48;2;23;23;23m▄\e[38;2;68;68;68;48;2;52;52;52m▄\e[38;2;11;11;11;48;2;123;123;124m▄\e[38;2;11;11;11;48;2;148;148;148m▄\e[38;2;9;9;9;48;2;170;170;171m▄\e[38;2;10;10;10;48;2;169;169;169m▄\e[38;2;10;10;10;48;2;164;164;163m▄\e[38;2;8;8;8;48;2;161;161;161m▄\e[38;2;10;10;10;48;2;160;159;161m▄\e[38;2;9;9;9;48;2;150;150;151m▄\e[38;2;8;8;8;48;2;143;143;144m▄\e[38;2;8;8;8;48;2;142;142;142m▄\e[38;2;10;10;10;48;2;139;139;139m▄\e[38;2;10;10;10;48;2;134;134;135m▄\e[38;2;9;9;9;48;2;127;127;128m▄\e[38;2;10;10;10;48;2;120;120;120m▄\e[38;2;10;10;10;48;2;116;116;115m▄\e[38;2;10;10;10;48;2;114;114;114m▄\e[38;2;12;11;11;48;2;106;106;105m▄\e[38;2;138;136;137;48;2;107;107;108m▄\e[38;2;171;169;170;48;2;152;152;151m▄\e[38;2;209;207;208;48;2;186;186;186m▄\e[38;2;225;225;225;48;2;202;200;201m▄\e[38;2;253;253;253;48;2;242;241;241m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;219;219;219;48;2;247;247;247m▄\e[38;2;129;129;129;48;2;172;171;172m▄\e[38;2;164;164;164;48;2;115;115;116m▄\e[38;2;207;207;207;48;2;214;213;213m▄\e[38;2;235;235;235;48;2;165;165;166m▄\e[38;2;249;249;249;48;2;124;124;125m▄\e[38;2;250;250;250;48;2;174;174;175m▄\e[38;2;252;252;252;48;2;170;170;171m▄\e[38;2;252;252;252;48;2;208;207;208m▄\e[38;2;242;242;242;48;2;204;204;204m▄\e[38;2;219;219;219;48;2;210;210;210m▄\e[38;2;249;249;249;48;2;248;248;248m▄\e[38;2;255;255;255;48;2;254;254;254m▄\e[38;2;254;254;254;48;2;251;251;251m▄\e[38;2;252;252;252;48;2;244;244;244m▄\e[38;2;252;252;252;48;2;232;232;232m▄\e[m\n");
printf("\e[38;2;221;220;220;48;2;151;151;149m▄\e[38;2;247;246;247;48;2;239;239;239m▄\e[38;2;246;246;246;48;2;243;243;243m▄\e[38;2;217;217;217;48;2;215;215;215m▄\e[38;2;255;255;255;48;2;254;254;254m▄\e[48;2;255;255;255m \e[38;2;255;255;255;48;2;254;254;254m▄▄▄\e[38;2;255;255;255;48;2;254;254;253m▄\e[38;2;255;255;255;48;2;254;254;254m▄\e[38;2;255;255;255;48;2;253;253;253m▄\e[38;2;253;253;253;48;2;251;251;251m▄\e[38;2;231;230;230;48;2;222;222;222m▄\e[38;2;218;217;217;48;2;226;226;226m▄\e[38;2;249;249;249;48;2;252;252;252m▄\e[38;2;246;245;246;48;2;223;221;222m▄\e[38;2;213;212;213;48;2;218;218;218m▄\e[38;2;219;218;219;48;2;240;240;240m▄\e[38;2;191;191;192;48;2;194;194;194m▄\e[38;2;105;106;106;48;2;16;16;16m▄\e[38;2;110;110;110;48;2;18;18;17m▄\e[38;2;120;120;120;48;2;37;37;37m▄\e[38;2;163;162;162;48;2;121;121;121m▄\e[38;2;187;187;186;48;2;175;175;175m▄\e[38;2;218;218;217;48;2;216;216;216m▄\e[38;2;248;248;248;48;2;178;178;178m▄\e[38;2;139;139;139;48;2;94;94;94m▄\e[38;2;112;112;112;48;2;131;131;131m▄\e[38;2;127;127;126;48;2;103;103;102m▄\e[38;2;132;132;132;48;2;103;103;102m▄\e[38;2;86;86;86;48;2;109;109;109m▄\e[38;2;195;194;195;48;2;111;111;111m▄\e[38;2;164;163;164;48;2;166;166;167m▄\e[38;2;180;180;180;48;2;144;144;144m▄\e[38;2;248;248;248;48;2;172;172;172m▄\e[38;2;233;232;233;48;2;236;235;236m▄\e[38;2;199;198;199;48;2;171;170;171m▄\e[38;2;179;179;179;48;2;120;120;121m▄\e[38;2;144;144;144;48;2;35;35;35m▄\e[38;2;124;124;124;48;2;15;15;15m▄\e[38;2;121;121;122;48;2;15;15;15m▄\e[38;2;119;119;120;48;2;16;16;16m▄\e[38;2;118;118;119;48;2;16;16;16m▄\e[38;2;119;119;120;48;2;17;17;17m▄\e[38;2;119;119;120;48;2;18;18;18m▄\e[38;2;118;118;119;48;2;16;16;16m▄\e[38;2;118;118;118;48;2;15;15;15m▄\e[38;2;117;117;117;48;2;16;16;16m▄\e[38;2;117;117;117;48;2;16;15;16m▄\e[38;2;116;116;116;48;2;15;15;15m▄\e[38;2;117;116;116;48;2;15;15;15m▄\e[38;2;116;114;113;48;2;15;14;15m▄\e[38;2;116;115;116;48;2;15;15;15m▄\e[38;2;115;115;116;48;2;15;15;15m▄\e[38;2;115;114;114;48;2;15;15;15m▄\e[38;2;115;114;115;48;2;16;16;16m▄\e[38;2;147;147;147;48;2;63;62;62m▄\e[38;2;218;218;218;48;2;206;205;205m▄\e[38;2;230;229;230;48;2;208;206;207m▄\e[38;2;208;207;208;48;2;226;224;225m▄\e[38;2;252;252;252;48;2;233;233;233m▄\e[48;2;253;253;253m \e[38;2;213;212;212;48;2;248;248;248m▄\e[38;2;227;226;227;48;2;199;199;199m▄\e[38;2;253;253;253;48;2;251;251;251m▄\e[38;2;255;255;255;48;2;253;253;253m▄\e[38;2;255;255;255;48;2;254;254;254m▄\e[48;2;255;255;255m \e[38;2;255;255;255;48;2;254;254;254m▄▄▄\e[48;2;254;254;254m \e[38;2;242;242;242;48;2;243;243;243m▄\e[38;2;217;217;217;48;2;218;218;218m▄\e[48;2;248;248;248m \e[48;2;255;255;255m    \e[m\n");
printf("\e[38;2;228;228;228;48;2;229;228;228m▄\e[38;2;243;243;243;48;2;247;247;247m▄\e[38;2;248;248;248;48;2;247;247;247m▄\e[38;2;217;217;217;48;2;221;221;221m▄\e[38;2;249;249;249;48;2;254;254;254m▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;254;254;254;48;2;255;255;255m▄▄▄▄\e[48;2;255;255;255m  \e[48;2;254;254;254m \e[38;2;254;254;254;48;2;248;248;248m▄\e[38;2;200;199;200;48;2;203;202;203m▄\e[38;2;236;236;236;48;2;244;243;244m▄\e[38;2;254;254;254;48;2;253;253;253m▄\e[38;2;253;253;253;48;2;232;231;232m▄\e[38;2;253;253;253;48;2;191;190;191m▄\e[38;2;253;253;253;48;2;163;163;165m▄\e[38;2;254;254;254;48;2;174;174;174m▄\e[38;2;253;253;253;48;2;185;185;185m▄\e[38;2;253;253;253;48;2;188;188;188m▄\e[38;2;253;253;253;48;2;196;194;195m▄\e[38;2;253;253;253;48;2;206;206;207m▄\e[38;2;253;253;253;48;2;222;222;221m▄\e[38;2;251;251;251;48;2;238;238;238m▄\e[38;2;209;208;208;48;2;153;152;153m▄\e[38;2;89;89;89;48;2;88;89;89m▄\e[38;2;117;116;117;48;2;106;106;106m▄\e[38;2;211;210;212;48;2;193;193;194m▄\e[38;2;178;178;178;48;2;192;192;192m▄\e[38;2;224;224;225;48;2;227;227;228m▄\e[38;2;199;198;200;48;2;216;214;216m▄\e[38;2;224;223;223;48;2;205;204;205m▄\e[38;2;253;253;253;48;2;244;244;244m▄\e[38;2;253;253;253;48;2;233;231;232m▄\e[38;2;253;253;253;48;2;215;215;215m▄\e[38;2;254;254;254;48;2;207;207;207m▄\e[38;2;253;253;253;48;2;196;196;196m▄\e[38;2;253;253;253;48;2;187;187;188m▄\e[38;2;253;253;253;48;2;182;182;183m▄\e[38;2;253;253;253;48;2;175;175;175m▄\e[38;2;253;253;253;48;2;178;178;178m▄\e[38;2;253;253;253;48;2;179;179;179m▄\e[38;2;253;253;253;48;2;176;176;177m▄\e[38;2;253;253;253;48;2;176;176;176m▄\e[38;2;253;253;253;48;2;177;177;177m▄\e[38;2;253;253;253;48;2;176;176;176m▄\e[38;2;253;253;253;48;2;174;174;174m▄\e[38;2;253;253;253;48;2;173;173;173m▄\e[38;2;253;253;253;48;2;174;174;173m▄\e[38;2;253;253;253;48;2;174;174;175m▄\e[38;2;253;253;253;48;2;170;170;170m▄\e[38;2;253;253;253;48;2;172;172;173m▄\e[38;2;253;253;253;48;2;172;170;172m▄\e[38;2;253;253;253;48;2;172;171;172m▄\e[38;2;253;253;253;48;2;167;167;168m▄\e[38;2;253;253;253;48;2;176;176;177m▄\e[38;2;253;253;253;48;2;202;202;202m▄\e[38;2;254;254;254;48;2;241;241;241m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;218;218;218;48;2;252;252;252m▄\e[38;2;222;222;222;48;2;188;188;188m▄\e[38;2;254;254;254;48;2;252;252;252m▄\e[48;2;254;254;254m \e[38;2;254;254;254;48;2;255;255;255m▄▄▄▄▄▄\e[38;2;251;251;251;48;2;254;254;254m▄\e[38;2;227;226;226;48;2;241;241;241m▄\e[38;2;211;211;211;48;2;215;215;215m▄\e[48;2;248;248;248m \e[48;2;254;254;254m \e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;250;250;250;48;2;254;254;254m▄\e[38;2;253;253;253;48;2;255;255;255m▄\e[m\n");
printf("\e[38;2;154;152;153;48;2;207;205;206m▄\e[38;2;247;247;247;48;2;239;239;239m▄\e[38;2;250;250;250;48;2;251;250;250m▄\e[38;2;140;140;140;48;2;153;151;152m▄\e[38;2;83;84;84;48;2;183;182;183m▄\e[38;2;122;121;122;48;2;212;212;212m▄\e[38;2;140;140;140;48;2;245;245;245m▄\e[38;2;131;131;131;48;2;253;253;253m▄\e[38;2;143;143;143;48;2;253;253;253m▄\e[38;2;163;163;163;48;2;254;254;254m▄\e[38;2;178;178;178;48;2;254;254;254m▄\e[38;2;181;181;181;48;2;254;254;254m▄\e[38;2;184;184;184;48;2;254;254;254m▄\e[38;2;188;188;188;48;2;254;254;254m▄\e[38;2;190;190;189;48;2;232;232;232m▄\e[38;2;134;133;134;48;2;193;193;193m▄\e[38;2;192;191;191;48;2;253;253;253m▄\e[38;2;192;192;192;48;2;254;254;254m▄▄\e[38;2;196;196;196;48;2;254;254;254m▄\e[38;2;199;199;199;48;2;254;254;254m▄\e[38;2;200;200;200;48;2;254;254;254m▄\e[38;2;206;206;206;48;2;254;254;254m▄\e[38;2;220;220;220;48;2;253;253;253m▄\e[38;2;228;228;228;48;2;253;253;253m▄\e[38;2;244;244;244;48;2;254;254;254m▄\e[38;2;213;213;213;48;2;252;252;252m▄\e[38;2;99;99;99;48;2;230;230;230m▄\e[38;2;23;23;23;48;2;170;168;169m▄\e[38;2;18;18;18;48;2;127;127;128m▄\e[38;2;67;67;68;48;2;199;199;201m▄\e[38;2;53;53;54;48;2;143;143;143m▄\e[38;2;126;126;125;48;2;184;184;184m▄\e[38;2;197;197;197;48;2;205;205;205m▄\e[38;2;248;248;248;48;2;249;249;249m▄\e[38;2;246;246;246;48;2;254;254;254m▄\e[38;2;241;241;241;48;2;254;254;254m▄\e[38;2;216;216;216;48;2;254;254;254m▄\e[38;2;192;192;192;48;2;254;254;254m▄\e[38;2;185;185;185;48;2;254;254;254m▄\e[38;2;181;181;181;48;2;255;255;255m▄▄\e[38;2;180;180;180;48;2;255;255;255m▄\e[38;2;175;175;175;48;2;254;254;254m▄\e[38;2;173;173;173;48;2;254;254;254m▄\e[38;2;173;173;172;48;2;254;254;254m▄\e[38;2;171;171;171;48;2;254;254;254m▄\e[38;2;168;168;168;48;2;254;254;254m▄\e[38;2;165;165;165;48;2;254;254;254m▄▄\e[38;2;166;166;166;48;2;254;254;254m▄\e[38;2;165;165;165;48;2;254;254;254m▄\e[38;2;164;164;164;48;2;255;255;255m▄\e[38;2;163;163;163;48;2;254;254;254m▄\e[38;2;162;162;162;48;2;254;254;254m▄\e[38;2;161;161;161;48;2;254;254;254m▄\e[38;2;158;158;158;48;2;254;254;254m▄\e[38;2;156;156;156;48;2;254;254;254m▄\e[38;2;155;155;154;48;2;254;254;253m▄\e[38;2;153;153;151;48;2;254;254;253m▄\e[38;2;151;151;151;48;2;254;254;254m▄\e[38;2;144;144;143;48;2;252;252;252m▄\e[38;2;116;116;115;48;2;203;201;202m▄\e[38;2;128;128;128;48;2;241;241;241m▄\e[38;2;122;122;122;48;2;253;253;253m▄\e[38;2;116;117;116;48;2;252;252;252m▄\e[38;2;113;114;112;48;2;249;249;249m▄\e[38;2;114;115;116;48;2;246;246;246m▄\e[38;2;124;124;125;48;2;240;240;240m▄\e[38;2;133;133;133;48;2;224;224;224m▄\e[38;2;133;133;133;48;2;206;206;206m▄\e[38;2;121;121;121;48;2;186;186;186m▄\e[38;2;71;71;72;48;2;159;159;159m▄\e[38;2;91;92;92;48;2;111;111;110m▄\e[38;2;191;191;191;48;2;196;196;195m▄\e[38;2;249;249;249;48;2;252;252;252m▄\e[38;2;239;239;239;48;2;253;253;253m▄\e[38;2;240;240;240;48;2;245;245;245m▄\e[38;2;245;245;245;48;2;234;234;234m▄\e[48;2;239;239;239m \e[m\n");
printf("\e[38;2;205;205;206;48;2;179;178;179m▄\e[38;2;219;219;219;48;2;249;249;249m▄\e[38;2;246;246;246;48;2;249;249;249m▄\e[38;2;170;170;170;48;2;148;148;148m▄\e[38;2;106;106;106;48;2;101;101;101m▄\e[38;2;171;172;171;48;2;210;209;209m▄\e[38;2;62;62;61;48;2;191;190;192m▄\e[38;2;146;146;147;48;2;154;155;156m▄\e[38;2;169;168;169;48;2;144;144;145m▄\e[38;2;202;202;202;48;2;121;121;121m▄\e[38;2;223;223;224;48;2;102;102;103m▄\e[38;2;179;179;178;48;2;82;82;81m▄\e[38;2;82;82;84;48;2;78;79;80m▄\e[38;2;48;48;48;48;2;82;83;83m▄\e[38;2;51;53;52;48;2;83;85;84m▄\e[38;2;69;69;69;48;2;79;78;79m▄\e[38;2;106;106;106;48;2;83;83;83m▄\e[38;2;159;160;158;48;2;83;83;83m▄\e[38;2;196;195;195;48;2;84;85;85m▄\e[38;2;226;224;226;48;2;87;89;87m▄\e[38;2;243;242;243;48;2;90;90;89m▄\e[38;2;250;250;250;48;2;101;101;101m▄\e[38;2;251;251;251;48;2;144;144;144m▄\e[38;2;251;252;251;48;2;183;183;183m▄\e[38;2;248;248;248;48;2;213;213;213m▄\e[38;2;198;197;198;48;2;212;211;212m▄\e[38;2;191;191;191;48;2;95;94;95m▄\e[38;2;93;93;93;48;2;12;12;12m▄\e[38;2;11;11;9;48;2;10;10;10m▄\e[38;2;12;12;12;48;2;11;11;11m▄▄▄\e[38;2;11;11;11;48;2;16;16;15m▄\e[38;2;58;58;58;48;2;100;100;100m▄\e[38;2;209;209;209;48;2;231;231;231m▄\e[38;2;252;252;252;48;2;227;227;227m▄\e[38;2;252;252;252;48;2;219;219;219m▄\e[38;2;252;252;252;48;2;181;181;181m▄\e[38;2;251;251;251;48;2;136;136;136m▄\e[38;2;248;248;248;48;2;111;112;111m▄\e[38;2;247;246;246;48;2;110;111;110m▄\e[38;2;243;242;243;48;2;109;111;110m▄\e[38;2;241;241;241;48;2;109;111;110m▄\e[38;2;241;239;240;48;2;110;111;110m▄\e[38;2;240;240;240;48;2;106;107;106m▄\e[38;2;240;239;239;48;2;107;109;108m▄\e[38;2;241;239;240;48;2;107;110;109m▄\e[38;2;240;238;239;48;2;111;112;111m▄\e[38;2;240;238;239;48;2;109;110;109m▄\e[38;2;239;237;238;48;2;107;108;108m▄\e[38;2;231;230;231;48;2;107;107;108m▄\e[38;2;218;218;219;48;2;106;106;107m▄\e[38;2;210;209;210;48;2;105;104;106m▄\e[38;2;200;199;201;48;2;109;108;110m▄\e[38;2;191;191;191;48;2;110;110;112m▄\e[38;2;188;188;189;48;2;111;111;112m▄\e[38;2;188;188;189;48;2;113;113;114m▄\e[38;2;190;189;191;48;2;112;112;114m▄\e[38;2;192;191;193;48;2;115;115;116m▄\e[38;2;195;194;196;48;2;119;119;120m▄\e[38;2;198;198;198;48;2;122;121;124m▄\e[38;2;202;202;202;48;2;126;126;126m▄\e[38;2;209;209;209;48;2;128;128;128m▄\e[38;2;213;213;213;48;2;126;126;126m▄\e[38;2;214;214;215;48;2;127;128;128m▄\e[38;2;212;213;214;48;2;115;116;117m▄\e[38;2;192;190;191;48;2;116;116;116m▄\e[38;2;180;180;181;48;2;145;146;147m▄\e[38;2;209;208;208;48;2;183;183;184m▄\e[38;2;215;214;215;48;2;213;212;213m▄\e[38;2;145;145;145;48;2;211;211;211m▄\e[38;2;26;26;25;48;2;213;213;213m▄\e[38;2;155;153;154;48;2;131;132;131m▄\e[38;2;116;116;116;48;2;70;70;70m▄\e[38;2;218;218;218;48;2;202;202;202m▄\e[38;2;248;248;248;48;2;249;249;249m▄\e[38;2;251;250;251;48;2;243;243;243m▄\e[38;2;248;246;248;48;2;223;221;222m▄\e[38;2;230;228;230;48;2;225;223;225m▄\e[38;2;187;185;187;48;2;249;248;249m▄\e[m\n");
printf("\e[38;2;253;253;253;48;2;240;240;240m▄\e[38;2;254;254;254;48;2;250;250;250m▄\e[38;2;252;252;251;48;2;250;250;250m▄\e[38;2;183;182;182;48;2;175;175;175m▄\e[38;2;126;126;126;48;2;114;114;114m▄\e[38;2;191;191;191;48;2;161;161;161m▄\e[38;2;107;106;107;48;2;62;61;61m▄\e[38;2;177;176;178;48;2;182;181;182m▄\e[38;2;245;245;245;48;2;233;232;232m▄\e[38;2;232;232;232;48;2;222;221;221m▄\e[38;2;188;188;189;48;2;183;183;184m▄\e[38;2;139;139;137;48;2;133;133;132m▄\e[38;2;129;129;128;48;2;153;153;154m▄\e[38;2;95;95;94;48;2;136;136;135m▄\e[38;2;190;189;189;48;2;184;184;183m▄\e[38;2;210;210;211;48;2;234;234;235m▄\e[38;2;219;219;219;48;2;250;250;250m▄\e[48;2;253;253;253m \e[38;2;238;237;238;48;2;246;246;246m▄\e[38;2;57;56;57;48;2;183;182;184m▄\e[38;2;79;78;79;48;2;190;188;189m▄\e[38;2;157;157;157;48;2;220;218;219m▄\e[38;2;206;205;206;48;2;232;231;231m▄\e[38;2;228;226;227;48;2;244;243;244m▄\e[38;2;212;212;212;48;2;231;231;231m▄\e[38;2;213;212;212;48;2;195;195;195m▄\e[38;2;120;119;119;48;2;208;208;208m▄\e[38;2;21;21;21;48;2;93;93;93m▄\e[38;2;11;11;11;48;2;10;10;10m▄\e[48;2;12;12;12m  \e[38;2;12;12;10;48;2;12;12;11m▄\e[38;2;31;31;30;48;2;13;13;12m▄\e[38;2;157;157;158;48;2;65;65;65m▄\e[38;2;225;225;226;48;2;207;207;207m▄\e[38;2;205;203;204;48;2;236;236;236m▄\e[38;2;150;150;150;48;2;215;215;215m▄\e[38;2;175;175;175;48;2;227;227;227m▄\e[38;2;110;110;109;48;2;208;208;209m▄\e[38;2;45;45;45;48;2;191;191;191m▄\e[38;2;38;38;38;48;2;189;189;189m▄\e[38;2;38;38;37;48;2;188;188;188m▄\e[38;2;37;37;37;48;2;187;187;187m▄\e[38;2;112;111;112;48;2;199;199;199m▄\e[38;2;221;221;221;48;2;227;227;227m▄\e[38;2;118;118;118;48;2;213;213;213m▄\e[38;2;38;38;38;48;2;189;189;189m▄\e[38;2;40;40;40;48;2;191;191;191m▄\e[38;2;40;40;40;48;2;190;190;190m▄\e[38;2;40;40;40;48;2;189;189;189m▄\e[38;2;39;39;39;48;2;189;189;189m▄\e[38;2;39;39;38;48;2;189;189;188m▄\e[38;2;39;39;38;48;2;190;190;189m▄▄\e[38;2;38;38;36;48;2;188;188;188m▄\e[38;2;109;109;109;48;2;205;205;205m▄\e[38;2;62;62;61;48;2;198;198;198m▄\e[38;2;235;235;235;48;2;246;246;246m▄\e[38;2;254;254;254;48;2;253;253;253m▄▄\e[38;2;243;243;243;48;2;252;252;252m▄\e[38;2;200;200;200;48;2;239;239;239m▄\e[38;2;221;221;221;48;2;225;224;224m▄\e[38;2;216;216;216;48;2;186;185;186m▄\e[38;2;135;135;135;48;2;83;83;83m▄\e[38;2;156;156;156;48;2;84;83;84m▄\e[38;2;110;110;110;48;2;92;92;93m▄\e[38;2;122;122;121;48;2;142;142;142m▄\e[38;2;57;57;56;48;2;149;149;149m▄\e[38;2;116;116;116;48;2;171;171;171m▄\e[38;2;172;171;172;48;2;103;102;102m▄\e[38;2;70;70;70;48;2;19;19;18m▄\e[38;2;162;162;162;48;2;154;152;153m▄\e[38;2;224;222;223;48;2;195;195;195m▄\e[38;2;224;224;224;48;2;223;222;222m▄\e[38;2;242;242;242;48;2;245;244;244m▄\e[38;2;230;228;229;48;2;238;236;237m▄\e[38;2;236;234;235;48;2;237;235;236m▄\e[48;2;251;251;251m \e[38;2;248;248;248;48;2;234;232;233m▄\e[m\n");
printf("\e[38;2;238;238;238;48;2;252;252;252m▄\e[48;2;253;253;253m \e[48;2;253;253;252m \e[38;2;193;192;193;48;2;187;186;188m▄\e[38;2;156;156;157;48;2;141;142;141m▄\e[38;2;231;231;232;48;2;216;216;218m▄\e[38;2;136;136;135;48;2;123;122;123m▄\e[38;2;82;82;82;48;2;199;198;199m▄\e[38;2;209;207;208;48;2;236;235;236m▄\e[38;2;184;182;183;48;2;249;248;248m▄\e[38;2;236;236;236;48;2;247;247;247m▄\e[38;2;164;164;163;48;2;211;211;210m▄\e[38;2;218;218;219;48;2;152;151;150m▄\e[38;2;155;154;155;48;2;186;184;186m▄\e[38;2;217;215;216;48;2;246;245;246m▄\e[38;2;231;230;230;48;2;243;242;243m▄\e[38;2;113;113;113;48;2;146;146;146m▄\e[38;2;166;166;166;48;2;243;243;243m▄\e[38;2;251;251;251;48;2;247;245;246m▄\e[38;2;155;155;155;48;2;84;84;84m▄\e[38;2;106;106;106;48;2;88;88;88m▄\e[38;2;169;169;169;48;2;139;139;139m▄\e[38;2;201;200;201;48;2;207;206;206m▄\e[38;2;219;219;221;48;2;204;202;203m▄\e[38;2;198;198;198;48;2;224;224;224m▄\e[38;2;130;130;130;48;2;183;183;183m▄\e[38;2;39;39;39;48;2;56;56;56m▄\e[48;2;11;11;11m \e[38;2;12;12;12;48;2;11;11;11m▄\e[48;2;12;12;12m  \e[38;2;11;11;11;48;2;12;12;11m▄\e[38;2;206;205;205;48;2;115;115;115m▄\e[38;2;201;200;201;48;2;185;185;185m▄\e[38;2;207;207;207;48;2;215;215;215m▄\e[38;2;231;231;231;48;2;220;220;220m▄\e[38;2;174;174;174;48;2;153;153;153m▄\e[38;2;117;117;117;48;2;146;146;146m▄\e[38;2;48;48;49;48;2;69;69;69m▄\e[38;2;19;19;19;48;2;15;15;15m▄\e[38;2;17;17;17;48;2;11;11;10m▄\e[38;2;17;17;17;48;2;10;10;8m▄\e[38;2;39;39;39;48;2;10;10;8m▄\e[38;2;217;217;217;48;2;157;157;157m▄\e[38;2;181;181;180;48;2;227;227;227m▄\e[38;2;16;16;14;48;2;45;46;44m▄\e[38;2;16;16;15;48;2;11;11;10m▄\e[38;2;18;18;16;48;2;11;11;11m▄\e[38;2;19;19;18;48;2;11;11;9m▄\e[38;2;19;18;18;48;2;11;11;9m▄\e[38;2;20;19;19;48;2;10;10;10m▄\e[38;2;20;19;20;48;2;11;11;10m▄\e[38;2;20;19;18;48;2;10;10;8m▄\e[38;2;20;20;19;48;2;10;10;8m▄\e[38;2;91;91;90;48;2;25;25;23m▄\e[38;2;60;59;59;48;2;78;78;78m▄\e[38;2;143;143;143;48;2;53;53;52m▄\e[38;2;252;252;252;48;2;246;245;245m▄\e[48;2;253;253;253m \e[38;2;240;240;240;48;2;253;253;253m▄\e[38;2;131;131;131;48;2;205;204;205m▄\e[38;2;172;171;172;48;2;218;217;218m▄\e[38;2;210;209;210;48;2;246;245;245m▄\e[38;2;176;176;176;48;2;251;250;250m▄\e[38;2;168;168;168;48;2;242;241;241m▄\e[38;2;205;205;206;48;2;234;233;233m▄\e[38;2;241;240;241;48;2;190;190;189m▄\e[38;2;233;232;234;48;2;219;219;219m▄\e[38;2;241;240;241;48;2;165;165;164m▄\e[38;2;237;236;236;48;2;169;168;168m▄\e[38;2;209;208;209;48;2;204;203;204m▄\e[38;2;208;207;208;48;2;145;145;145m▄\e[38;2;199;197;198;48;2;177;175;176m▄\e[38;2;237;235;236;48;2;234;233;234m▄\e[38;2;227;226;226;48;2;225;225;225m▄\e[38;2;251;251;251;48;2;249;249;249m▄\e[38;2;249;249;249;48;2;250;249;249m▄\e[38;2;230;230;230;48;2;250;248;249m▄\e[38;2;235;235;235;48;2;252;252;252m▄\e[38;2;238;237;238;48;2;253;253;253m▄\e[m\n");
printf("\e[38;2;254;254;254;48;2;252;252;252m▄\e[48;2;254;254;254m \e[38;2;253;253;253;48;2;253;253;252m▄\e[38;2;197;197;197;48;2;199;199;199m▄\e[38;2;203;202;202;48;2;178;178;178m▄\e[38;2;234;233;233;48;2;236;235;236m▄\e[38;2;202;201;201;48;2;178;178;178m▄\e[38;2;158;159;160;48;2;105;107;106m▄\e[38;2;133;134;134;48;2;91;90;91m▄\e[38;2;153;153;154;48;2;154;153;153m▄\e[38;2;154;154;155;48;2;191;191;190m▄\e[38;2;168;167;169;48;2;136;136;135m▄\e[38;2;202;202;202;48;2;215;214;216m▄\e[38;2;213;213;213;48;2;218;218;219m▄\e[38;2;203;203;204;48;2;244;242;243m▄\e[38;2;177;176;177;48;2;192;191;191m▄\e[38;2;83;83;84;48;2;114;113;114m▄\e[38;2;94;94;94;48;2;115;115;115m▄\e[38;2;236;236;236;48;2;246;246;246m▄\e[38;2;249;249;249;48;2;223;223;223m▄\e[38;2;223;223;223;48;2;133;133;133m▄\e[38;2;209;207;208;48;2;212;210;211m▄\e[38;2;194;192;194;48;2;207;205;206m▄\e[38;2;220;218;220;48;2;197;196;198m▄\e[38;2;230;228;229;48;2;204;203;203m▄\e[38;2;93;93;93;48;2;146;146;146m▄\e[38;2;10;10;10;48;2;15;15;15m▄\e[48;2;11;11;11m \e[48;2;12;12;12m   \e[38;2;47;46;46;48;2;24;24;24m▄\e[38;2;245;245;245;48;2;234;233;233m▄\e[38;2;213;212;213;48;2;212;210;211m▄\e[38;2;201;200;200;48;2;210;210;210m▄\e[38;2;201;199;201;48;2;208;207;209m▄\e[38;2;241;241;241;48;2;198;198;198m▄\e[38;2;237;237;237;48;2;154;154;154m▄\e[38;2;237;237;237;48;2;129;129;129m▄\e[38;2;237;237;238;48;2;117;118;118m▄\e[38;2;238;238;239;48;2;117;118;119m▄\e[38;2;237;237;237;48;2;117;116;117m▄\e[38;2;235;235;235;48;2;139;139;139m▄\e[38;2;235;235;235;48;2;208;208;208m▄\e[38;2;235;235;235;48;2;172;172;170m▄\e[38;2;212;212;212;48;2;98;98;97m▄\e[38;2;218;218;218;48;2;111;111;111m▄\e[38;2;242;242;243;48;2;125;125;125m▄\e[38;2;241;241;243;48;2;128;128;128m▄\e[38;2;242;242;243;48;2;128;128;128m▄\e[38;2;242;242;243;48;2;129;130;130m▄\e[38;2;243;242;242;48;2;131;131;131m▄\e[38;2;242;242;243;48;2;129;130;129m▄\e[38;2;243;243;243;48;2;132;132;133m▄\e[38;2;239;239;239;48;2;176;176;177m▄\e[38;2;237;235;236;48;2;154;153;154m▄\e[38;2;252;251;251;48;2;235;235;235m▄\e[38;2;254;253;253;48;2;253;253;253m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;120;119;119;48;2;173;173;172m▄\e[38;2;90;90;90;48;2;130;130;131m▄\e[38;2;113;114;114;48;2;211;210;210m▄\e[38;2;157;156;157;48;2;235;234;235m▄\e[38;2;176;175;175;48;2;195;193;194m▄\e[38;2;135;136;136;48;2;115;116;115m▄\e[38;2;157;157;158;48;2;163;163;163m▄\e[38;2;174;174;174;48;2;189;188;188m▄\e[38;2;181;181;181;48;2;172;171;171m▄\e[38;2;152;152;152;48;2;161;161;161m▄\e[38;2;108;107;108;48;2;140;139;140m▄\e[38;2;87;87;87;48;2;142;142;143m▄\e[38;2;81;81;81;48;2;151;150;150m▄\e[38;2;85;85;85;48;2;160;159;160m▄\e[38;2;232;231;231;48;2;236;235;235m▄\e[38;2;226;225;226;48;2;228;227;227m▄\e[48;2;252;252;252m \e[38;2;254;254;254;48;2;252;252;252m▄\e[38;2;253;253;253;48;2;247;247;247m▄\e[38;2;253;253;253;48;2;245;245;245m▄\e[38;2;254;254;254;48;2;247;246;246m▄\e[m\n");
printf("\e[48;2;254;254;254m \e[48;2;255;255;255m \e[48;2;252;252;252m \e[38;2;195;195;195;48;2;139;139;139m▄\e[38;2;100;100;99;48;2;126;126;125m▄\e[38;2;201;201;201;48;2;204;203;204m▄\e[38;2;207;207;207;48;2;226;226;226m▄\e[38;2;206;206;206;48;2;227;227;228m▄\e[38;2;201;201;201;48;2;229;229;231m▄\e[38;2;199;199;199;48;2;228;228;230m▄\e[38;2;197;197;197;48;2;230;230;231m▄\e[38;2;199;199;199;48;2;234;232;233m▄\e[38;2;203;203;203;48;2;240;240;240m▄\e[38;2;203;203;203;48;2;236;236;236m▄\e[38;2;203;203;203;48;2;229;229;229m▄\e[38;2;176;176;176;48;2;229;229;229m▄\e[38;2;171;172;171;48;2;229;229;231m▄\e[38;2;191;188;189;48;2;234;234;234m▄\e[38;2;215;214;214;48;2;248;248;248m▄\e[38;2;158;158;158;48;2;177;177;177m▄\e[38;2;184;184;184;48;2;199;199;199m▄\e[38;2;188;187;187;48;2;208;208;208m▄\e[38;2;216;214;216;48;2;221;219;220m▄\e[38;2;223;221;224;48;2;249;247;249m▄\e[38;2;196;195;195;48;2;225;225;225m▄\e[38;2;13;13;11;48;2;39;39;39m▄\e[38;2;11;11;9;48;2;11;11;10m▄\e[38;2;11;11;10;48;2;12;12;11m▄\e[38;2;12;12;11;48;2;12;12;12m▄\e[38;2;11;11;11;48;2;12;12;12m▄▄\e[38;2;108;106;107;48;2;81;79;80m▄\e[38;2;250;249;251;48;2;251;251;251m▄\e[38;2;252;252;252;48;2;245;245;245m▄\e[38;2;216;215;215;48;2;186;186;186m▄\e[38;2;207;205;206;48;2;207;207;207m▄\e[38;2;212;210;211;48;2;229;229;229m▄\e[48;2;252;252;252m \e[48;2;254;254;254m  \e[38;2;255;255;255;48;2;254;254;254m▄▄▄▄▄\e[38;2;223;223;223;48;2;231;231;231m▄\e[38;2;182;182;182;48;2;230;230;230m▄\e[38;2;175;175;175;48;2;251;250;251m▄\e[38;2;150;150;150;48;2;252;252;252m▄\e[38;2;151;151;151;48;2;252;252;252m▄\e[38;2;153;153;153;48;2;253;252;253m▄\e[38;2;154;154;154;48;2;252;252;252m▄\e[38;2;152;152;152;48;2;251;251;251m▄\e[38;2;153;153;153;48;2;251;251;251m▄\e[38;2;155;155;155;48;2;252;251;252m▄\e[38;2;156;156;156;48;2;253;251;252m▄\e[38;2;157;157;157;48;2;253;251;252m▄\e[38;2;157;157;157;48;2;252;251;252m▄\e[38;2;158;158;159;48;2;251;251;251m▄\e[38;2;155;155;156;48;2;244;244;244m▄\e[38;2;156;156;158;48;2;239;239;239m▄\e[38;2;168;168;168;48;2;238;238;238m▄\e[38;2;194;194;196;48;2;236;236;236m▄\e[38;2;200;200;200;48;2;235;235;235m▄\e[38;2;201;201;202;48;2;236;236;236m▄\e[38;2;198;198;200;48;2;238;238;239m▄\e[38;2;173;173;175;48;2;238;238;239m▄\e[38;2;170;170;171;48;2;238;238;238m▄\e[38;2;203;203;204;48;2;235;236;236m▄\e[38;2;204;204;205;48;2;240;240;240m▄\e[38;2;202;202;202;48;2;245;245;245m▄\e[38;2;174;172;172;48;2;175;175;175m▄\e[38;2;144;144;144;48;2;30;30;30m▄\e[38;2;157;156;157;48;2;168;168;168m▄\e[38;2;220;220;220;48;2;221;221;221m▄\e[38;2;253;253;253;48;2;252;252;252m▄\e[48;2;255;255;255m    \e[m\n");
printf("\e[38;2;252;252;252;48;2;254;254;254m▄▄\e[48;2;252;252;252m \e[38;2;212;212;212;48;2;206;206;206m▄\e[38;2;183;183;183;48;2;169;169;170m▄\e[38;2;235;235;235;48;2;236;236;236m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[48;2;254;254;254m \e[38;2;255;255;255;48;2;254;254;254m▄▄▄▄▄▄\e[38;2;252;251;252;48;2;250;250;250m▄\e[38;2;193;192;192;48;2;131;131;130m▄\e[38;2;32;32;32;48;2;55;54;53m▄\e[38;2;60;60;60;48;2;93;92;92m▄\e[38;2;133;133;133;48;2;172;172;172m▄\e[38;2;166;166;166;48;2;202;202;202m▄\e[38;2;174;174;174;48;2;195;195;195m▄\e[38;2;173;173;173;48;2;191;191;191m▄\e[38;2;170;170;170;48;2;212;211;212m▄\e[48;2;234;234;234m \e[38;2;176;176;176;48;2;189;188;188m▄\e[38;2;147;147;146;48;2;38;38;37m▄\e[38;2;116;116;115;48;2;12;12;10m▄\e[38;2;54;54;53;48;2;11;11;10m▄\e[38;2;17;17;17;48;2;11;11;11m▄\e[48;2;11;11;9m \e[38;2;15;15;13;48;2;12;12;10m▄\e[38;2;156;156;156;48;2;130;129;130m▄\e[38;2;253;253;253;48;2;252;252;253m▄\e[38;2;254;254;254;48;2;253;253;253m▄\e[38;2;253;253;253;48;2;251;251;251m▄\e[38;2;223;221;222;48;2;190;188;189m▄\e[38;2;188;186;187;48;2;206;205;205m▄\e[38;2;188;187;187;48;2;226;225;226m▄\e[38;2;242;242;242;48;2;251;251;251m▄\e[48;2;254;254;254m \e[48;2;255;255;255m    \e[38;2;254;254;254;48;2;255;255;255m▄\e[38;2;234;234;234;48;2;233;233;233m▄\e[38;2;208;208;208;48;2;230;230;230m▄\e[38;2;48;48;47;48;2;138;138;137m▄\e[38;2;13;13;13;48;2;44;44;44m▄\e[38;2;14;14;14;48;2;44;44;44m▄\e[38;2;14;13;14;48;2;45;45;45m▄▄\e[38;2;16;15;15;48;2;43;43;43m▄\e[38;2;16;15;15;48;2;44;44;44m▄\e[38;2;15;14;14;48;2;44;44;44m▄\e[38;2;16;15;15;48;2;44;44;44m▄\e[38;2;15;15;15;48;2;44;44;44m▄\e[38;2;15;15;15;48;2;43;43;43m▄\e[38;2;15;15;15;48;2;42;42;42m▄\e[38;2;16;16;16;48;2;43;43;43m▄\e[38;2;33;34;34;48;2;46;46;45m▄\e[38;2;182;182;181;48;2;116;116;116m▄\e[38;2;250;250;250;48;2;239;239;239m▄\e[48;2;252;252;252m \e[38;2;239;238;238;48;2;252;252;252m▄\e[38;2;187;185;185;48;2;242;242;243m▄\e[38;2;108;107;107;48;2;132;132;132m▄\e[38;2;166;166;166;48;2;88;88;88m▄\e[38;2;252;252;252;48;2;251;251;251m▄\e[38;2;254;254;254;48;2;252;252;253m▄\e[48;2;252;252;252m \e[38;2;252;252;252;48;2;250;250;250m▄\e[38;2;230;230;230;48;2;204;204;204m▄\e[38;2;189;187;189;48;2;168;167;168m▄\e[38;2;223;223;223;48;2;223;223;224m▄\e[48;2;254;254;254m \e[48;2;255;255;255m    \e[m\n");
printf("\e[38;2;254;254;254;48;2;228;228;228m▄\e[38;2;253;253;253;48;2;233;233;233m▄\e[38;2;252;252;252;48;2;246;246;246m▄\e[38;2;246;246;246;48;2;193;192;192m▄\e[38;2;179;179;179;48;2;126;126;126m▄\e[38;2;139;138;139;48;2;176;176;176m▄\e[38;2;139;139;139;48;2;230;230;230m▄\e[38;2;164;164;164;48;2;244;244;244m▄\e[38;2;169;169;169;48;2;245;245;245m▄\e[38;2;173;173;173;48;2;245;245;245m▄\e[38;2;175;175;175;48;2;246;246;246m▄▄\e[38;2;174;174;174;48;2;246;246;246m▄\e[38;2;175;175;175;48;2;246;246;246m▄\e[38;2;178;177;178;48;2;246;244;245m▄\e[38;2;179;178;179;48;2;243;242;243m▄\e[38;2;181;181;181;48;2;199;199;199m▄\e[38;2;184;183;183;48;2;195;194;194m▄\e[38;2;186;186;186;48;2;200;200;200m▄\e[38;2;195;195;195;48;2;204;204;204m▄\e[38;2;202;202;202;48;2;214;214;214m▄\e[38;2;213;212;213;48;2;220;219;220m▄\e[38;2;237;236;237;48;2;232;231;232m▄\e[38;2;250;249;250;48;2;246;245;245m▄\e[38;2;147;146;146;48;2;148;147;147m▄\e[38;2;174;173;173;48;2;155;154;154m▄\e[38;2;188;187;187;48;2;206;206;206m▄\e[38;2;210;210;210;48;2;227;227;227m▄\e[38;2;212;212;212;48;2;195;195;195m▄\e[38;2;164;164;164;48;2;103;103;103m▄\e[38;2;177;177;177;48;2;130;130;129m▄\e[38;2;195;194;195;48;2;203;203;203m▄\e[38;2;236;236;236;48;2;252;252;252m▄\e[38;2;234;234;234;48;2;252;252;252m▄\e[38;2;232;232;232;48;2;252;251;252m▄\e[38;2;230;230;230;48;2;250;248;249m▄\e[38;2;230;229;229;48;2;225;224;225m▄\e[38;2;228;228;227;48;2;196;194;195m▄\e[38;2;228;227;227;48;2;246;245;246m▄\e[38;2;229;229;229;48;2;252;252;252m▄\e[38;2;226;226;225;48;2;252;252;252m▄\e[38;2;227;227;227;48;2;251;251;251m▄\e[38;2;225;225;225;48;2;251;251;251m▄\e[38;2;224;224;224;48;2;252;252;252m▄\e[38;2;227;227;227;48;2;252;252;252m▄\e[38;2;211;211;211;48;2;231;231;231m▄\e[38;2;186;186;186;48;2;213;213;213m▄\e[38;2;189;189;189;48;2;189;189;190m▄\e[38;2;190;190;190;48;2;188;189;189m▄\e[38;2;190;190;189;48;2;191;191;192m▄\e[38;2;192;192;191;48;2;196;195;195m▄\e[38;2;193;193;193;48;2;197;197;197m▄\e[38;2;193;193;193;48;2;199;200;200m▄\e[38;2;192;192;192;48;2;200;201;200m▄\e[38;2;192;192;192;48;2;200;201;201m▄\e[38;2;195;195;195;48;2;200;201;200m▄\e[38;2;194;194;195;48;2;198;199;199m▄\e[38;2;195;194;195;48;2;199;200;199m▄\e[38;2;196;196;196;48;2;200;201;200m▄\e[38;2;195;194;194;48;2;198;198;198m▄\e[38;2;195;195;195;48;2;213;213;213m▄\e[38;2;195;195;195;48;2;247;247;247m▄\e[38;2;195;193;195;48;2;247;247;247m▄\e[38;2;195;194;195;48;2;230;228;229m▄\e[38;2;201;200;200;48;2;193;191;192m▄\e[38;2;201;200;201;48;2;226;224;225m▄\e[38;2;195;195;195;48;2;245;243;244m▄\e[38;2;187;187;187;48;2;246;246;246m▄\e[38;2;150;150;151;48;2;242;242;242m▄\e[38;2;108;108;108;48;2;228;228;228m▄\e[38;2;107;107;107;48;2;201;201;201m▄\e[38;2;129;128;130;48;2;138;138;137m▄\e[38;2;195;194;195;48;2;83;81;82m▄\e[38;2;210;209;210;48;2;179;177;179m▄\e[38;2;252;252;252;48;2;227;226;227m▄\e[48;2;254;254;254m \e[48;2;255;255;255m    \e[m\n");
printf("\e[38;2;255;255;255;48;2;254;254;254m▄▄\e[48;2;254;254;254m \e[38;2;254;254;254;48;2;252;252;252m▄\e[38;2;254;254;254;48;2;244;244;244m▄\e[38;2;248;248;248;48;2;217;216;217m▄\e[38;2;194;194;194;48;2;216;216;216m▄\e[38;2;179;179;181;48;2;200;200;201m▄\e[38;2;161;161;162;48;2;162;162;162m▄\e[38;2;182;182;182;48;2;143;143;144m▄\e[38;2;176;176;177;48;2;129;129;130m▄\e[38;2;155;154;155;48;2;116;116;116m▄\e[38;2;140;139;142;48;2;112;112;112m▄\e[38;2;85;85;86;48;2;110;110;110m▄\e[38;2;21;21;21;48;2;111;111;111m▄\e[38;2;11;11;11;48;2;112;112;112m▄\e[38;2;11;11;11;48;2;114;114;114m▄\e[38;2;13;13;13;48;2;115;115;115m▄\e[38;2;14;14;14;48;2;115;115;115m▄\e[38;2;128;128;128;48;2;168;168;168m▄\e[38;2;163;163;163;48;2;181;181;182m▄\e[38;2;163;163;163;48;2;182;182;182m▄\e[38;2;200;199;200;48;2;196;196;196m▄\e[38;2;243;242;242;48;2;232;232;232m▄\e[38;2;187;185;188;48;2;164;162;164m▄\e[38;2;218;218;220;48;2;201;200;201m▄\e[38;2;157;156;157;48;2;170;169;170m▄\e[38;2;212;211;213;48;2;197;197;197m▄\e[38;2;204;202;203;48;2;198;197;197m▄\e[38;2;193;193;193;48;2;186;186;187m▄\e[38;2;189;189;191;48;2;188;188;189m▄\e[38;2;237;237;237;48;2;221;219;220m▄\e[38;2;213;212;213;48;2;197;196;196m▄\e[38;2;183;183;183;48;2;188;187;188m▄\e[38;2;163;163;163;48;2;184;184;184m▄\e[38;2;170;170;170;48;2;188;188;188m▄\e[38;2;155;155;155;48;2;177;177;177m▄\e[38;2;163;163;163;48;2;180;180;180m▄\e[38;2;168;168;168;48;2;181;181;181m▄\e[38;2;166;166;166;48;2;181;181;181m▄\e[38;2;164;164;164;48;2;176;176;176m▄\e[38;2;169;169;169;48;2;180;180;180m▄\e[38;2;162;162;162;48;2;175;175;175m▄\e[38;2;156;156;156;48;2;173;173;173m▄▄\e[38;2;162;162;162;48;2;176;176;176m▄\e[38;2;165;165;165;48;2;182;182;182m▄\e[38;2;169;169;169;48;2;182;182;182m▄\e[38;2;156;156;156;48;2;175;175;175m▄\e[38;2;169;169;169;48;2;179;179;179m▄\e[38;2;168;168;168;48;2;179;179;179m▄▄\e[38;2;177;177;177;48;2;182;182;182m▄\e[38;2;174;174;174;48;2;183;183;183m▄\e[38;2;173;173;173;48;2;183;183;184m▄\e[38;2;164;164;164;48;2;182;182;183m▄\e[38;2;162;162;162;48;2;179;179;180m▄\e[38;2;145;145;145;48;2;173;173;174m▄\e[38;2;140;140;141;48;2;170;170;171m▄\e[38;2;30;30;30;48;2;121;121;122m▄\e[38;2;12;12;13;48;2;113;113;114m▄\e[38;2;13;13;13;48;2;114;114;115m▄\e[38;2;13;13;13;48;2;115;114;116m▄\e[38;2;13;13;13;48;2;113;112;114m▄\e[38;2;12;12;12;48;2;113;113;114m▄\e[38;2;11;11;11;48;2;113;113;113m▄\e[38;2;12;12;12;48;2;114;114;114m▄\e[38;2;12;12;13;48;2;113;113;115m▄\e[38;2;12;11;12;48;2;112;112;113m▄\e[38;2;57;57;57;48;2;130;130;131m▄\e[38;2;204;204;204;48;2;202;202;202m▄\e[38;2;252;252;252;48;2;222;220;221m▄\e[38;2;253;253;253;48;2;230;230;230m▄\e[38;2;254;254;254;48;2;253;253;253m▄\e[48;2;254;254;254m \e[48;2;255;255;255m     \e[m\n");
printf("\e[38;2;254;254;254;48;2;255;255;255m▄▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;251;251;251;48;2;253;253;253m▄\e[38;2;181;181;181;48;2;247;247;247m▄\e[38;2;113;113;113;48;2;188;188;188m▄\e[38;2;143;143;143;48;2;148;148;148m▄\e[38;2;178;178;178;48;2;171;171;171m▄\e[38;2;148;148;149;48;2;145;144;146m▄\e[38;2;170;170;171;48;2;191;191;190m▄\e[38;2;156;156;156;48;2;182;182;182m▄\e[38;2;147;147;147;48;2;166;166;166m▄\e[38;2;142;142;142;48;2;152;152;153m▄\e[38;2;101;101;101;48;2;122;124;123m▄\e[38;2;35;35;35;48;2;38;39;39m▄\e[48;2;11;11;11m \e[38;2;11;11;11;48;2;12;12;12m▄\e[48;2;11;11;11m \e[38;2;47;47;47;48;2;25;25;25m▄\e[38;2;178;178;178;48;2;150;150;150m▄\e[38;2;214;214;214;48;2;191;191;191m▄\e[38;2;232;231;231;48;2;204;204;204m▄\e[38;2;209;208;209;48;2;241;241;241m▄\e[38;2;210;208;209;48;2;242;240;241m▄\e[38;2;156;156;157;48;2;180;180;180m▄\e[38;2;148;147;148;48;2;210;210;210m▄\e[38;2;176;174;176;48;2;182;181;183m▄\e[38;2;176;175;176;48;2;209;207;210m▄\e[38;2;206;206;208;48;2;222;222;224m▄\e[38;2;188;188;188;48;2;219;219;219m▄\e[38;2;151;151;151;48;2;194;194;194m▄\e[38;2;224;224;224;48;2;241;241;241m▄\e[38;2;238;238;238;48;2;231;231;231m▄\e[38;2;165;165;165;48;2;184;184;184m▄\e[38;2;149;149;149;48;2;165;165;165m▄\e[38;2;124;124;124;48;2;153;153;153m▄\e[38;2;132;132;132;48;2;148;148;148m▄\e[38;2;136;136;136;48;2;155;155;155m▄\e[38;2;146;146;146;48;2;162;162;162m▄\e[38;2;145;145;145;48;2;158;158;158m▄\e[38;2;135;135;135;48;2;155;155;155m▄\e[38;2;145;145;145;48;2;159;159;159m▄\e[38;2;133;133;133;48;2;153;153;153m▄\e[38;2;121;121;121;48;2;148;148;148m▄\e[38;2;140;140;140;48;2;153;153;153m▄\e[38;2;137;137;137;48;2;155;155;155m▄\e[38;2;144;144;144;48;2;160;160;160m▄\e[38;2;146;146;146;48;2;161;161;161m▄\e[38;2;139;139;139;48;2;152;152;152m▄\e[38;2;138;138;138;48;2;162;162;162m▄\e[38;2;140;140;140;48;2;155;155;155m▄\e[38;2;142;142;142;48;2;161;161;161m▄\e[38;2;141;141;141;48;2;163;163;163m▄\e[38;2;141;141;141;48;2;164;164;164m▄\e[38;2;149;149;149;48;2;166;166;166m▄\e[38;2;140;140;140;48;2;163;163;163m▄\e[38;2;140;140;140;48;2;151;151;151m▄\e[38;2;125;125;125;48;2;135;135;135m▄\e[38;2;112;112;112;48;2;129;129;129m▄\e[38;2;56;56;56;48;2;35;35;35m▄\e[38;2;9;9;8;48;2;10;10;9m▄\e[38;2;11;11;11;48;2;12;12;11m▄\e[38;2;11;11;11;48;2;12;12;12m▄▄\e[48;2;11;11;11m \e[38;2;11;11;11;48;2;12;12;12m▄▄▄\e[38;2;13;13;13;48;2;11;11;11m▄\e[38;2;77;77;77;48;2;52;52;52m▄\e[38;2;137;137;137;48;2;174;174;174m▄\e[38;2;182;182;182;48;2;244;244;244m▄\e[38;2;247;247;247;48;2;253;253;253m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;254;254;254;48;2;255;255;255m▄\e[48;2;255;255;255m     \e[m\n");
printf("\e[38;2;225;225;225;48;2;254;254;254m▄\e[38;2;236;236;236;48;2;254;254;254m▄\e[38;2;235;235;235;48;2;251;251;251m▄\e[38;2;82;82;82;48;2;181;181;181m▄\e[38;2;78;78;78;48;2;86;86;86m▄\e[38;2;96;96;96;48;2;107;107;107m▄\e[38;2;119;119;119;48;2;139;139;139m▄\e[38;2;144;144;144;48;2;167;167;167m▄\e[38;2;135;135;135;48;2;154;154;154m▄\e[38;2;113;113;113;48;2;117;117;117m▄\e[38;2;125;125;125;48;2;111;111;111m▄\e[38;2;125;125;125;48;2;104;104;104m▄\e[38;2;132;132;132;48;2;91;91;91m▄\e[38;2;104;104;104;48;2;58;58;58m▄\e[38;2;108;108;108;48;2;25;25;25m▄\e[38;2;120;120;120;48;2;12;12;12m▄\e[38;2;121;121;121;48;2;12;12;12m▄\e[38;2;113;113;113;48;2;12;12;12m▄\e[38;2;174;174;174;48;2;85;85;85m▄\e[38;2;246;244;245;48;2;215;214;215m▄\e[38;2;142;141;141;48;2;236;234;235m▄\e[38;2;160;159;159;48;2;192;191;192m▄\e[38;2;211;211;211;48;2;187;186;187m▄\e[38;2;157;157;156;48;2;199;198;199m▄\e[38;2;169;169;171;48;2;218;218;220m▄\e[38;2;184;183;184;48;2;167;166;168m▄\e[38;2;212;211;212;48;2;173;172;173m▄\e[38;2;211;211;212;48;2;207;207;207m▄\e[38;2;238;238;238;48;2;211;211;211m▄\e[38;2;200;200;200;48;2;166;166;166m▄\e[38;2;215;215;215;48;2;168;168;168m▄\e[38;2;191;191;191;48;2;193;193;193m▄\e[38;2;243;242;242;48;2;234;234;234m▄\e[38;2;176;175;175;48;2;168;168;168m▄\e[38;2;115;115;115;48;2;131;131;131m▄\e[38;2;83;83;83;48;2;108;108;108m▄\e[38;2;86;86;86;48;2;112;112;112m▄\e[38;2;83;83;83;48;2;120;120;120m▄\e[38;2;81;81;81;48;2;128;128;128m▄\e[38;2;95;95;95;48;2;126;126;126m▄\e[38;2;78;78;78;48;2;110;110;110m▄\e[38;2;96;96;96;48;2;123;123;123m▄\e[38;2;78;78;78;48;2;108;108;108m▄\e[38;2;76;76;76;48;2;93;93;93m▄\e[38;2;79;79;79;48;2;111;111;111m▄\e[38;2;88;88;88;48;2;120;120;120m▄\e[38;2;101;101;101;48;2;125;125;125m▄\e[38;2;103;103;103;48;2;129;129;129m▄\e[38;2;99;99;99;48;2;124;124;124m▄\e[38;2;94;94;94;48;2;114;114;114m▄\e[38;2;89;89;89;48;2;120;120;120m▄\e[38;2;87;87;87;48;2;113;113;113m▄\e[38;2;110;110;110;48;2;128;128;128m▄\e[38;2;101;101;101;48;2;126;126;126m▄\e[38;2;89;89;89;48;2;132;132;132m▄\e[38;2;117;117;117;48;2;135;135;135m▄\e[38;2;102;102;102;48;2;133;133;133m▄\e[38;2;93;93;93;48;2;112;112;112m▄\e[38;2;84;84;84;48;2;98;98;98m▄\e[38;2;63;63;63;48;2;75;75;75m▄\e[38;2;106;106;106;48;2;11;11;11m▄\e[38;2;121;121;121;48;2;10;10;10m▄\e[38;2;115;115;115;48;2;11;11;11m▄\e[38;2;108;108;108;48;2;11;11;11m▄\e[38;2;115;115;114;48;2;10;10;10m▄\e[38;2;125;125;125;48;2;10;10;10m▄\e[38;2;130;130;130;48;2;11;11;11m▄\e[38;2;129;129;129;48;2;11;11;11m▄\e[38;2;131;131;131;48;2;22;22;22m▄\e[38;2;134;134;134;48;2;115;115;115m▄\e[38;2;105;105;105;48;2;131;131;131m▄\e[38;2;96;96;96;48;2;109;109;109m▄\e[38;2;84;84;84;48;2;180;180;180m▄\e[38;2;187;187;187;48;2;251;251;251m▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;254;254;254;48;2;255;255;255m▄\e[48;2;255;255;255m    \e[m\n");
printf("\e[38;2;254;254;254;48;2;253;253;253m▄▄\e[38;2;253;253;253;48;2;234;234;234m▄\e[38;2;192;192;192;48;2;79;79;79m▄\e[38;2;136;136;136;48;2;46;46;46m▄\e[38;2;142;142;142;48;2;69;69;69m▄\e[38;2;141;141;141;48;2;83;83;83m▄\e[38;2;143;143;145;48;2;87;87;87m▄\e[38;2;142;142;142;48;2;98;98;98m▄\e[38;2;143;143;144;48;2;73;73;73m▄\e[38;2;145;145;148;48;2;83;83;84m▄\e[38;2;137;136;139;48;2;91;91;91m▄\e[38;2;132;132;132;48;2;71;71;71m▄\e[38;2;136;136;137;48;2;69;69;69m▄\e[38;2;143;143;144;48;2;93;93;93m▄\e[38;2;135;135;135;48;2;86;86;86m▄\e[38;2;134;134;134;48;2;78;78;78m▄\e[38;2;144;144;144;48;2;95;95;96m▄\e[38;2;191;191;192;48;2;158;158;160m▄\e[38;2;159;159;160;48;2;118;116;117m▄\e[38;2;113;113;113;48;2;22;21;21m▄\e[38;2;241;240;241;48;2;90;90;90m▄\e[38;2;230;229;229;48;2;199;197;199m▄\e[38;2;186;186;186;48;2;200;200;202m▄\e[38;2;183;183;183;48;2;177;177;177m▄\e[38;2;191;191;191;48;2;197;197;197m▄\e[38;2;165;165;165;48;2;154;154;154m▄\e[38;2;162;162;162;48;2;151;151;151m▄\e[38;2;202;202;202;48;2;191;191;191m▄\e[38;2;191;191;190;48;2;193;193;193m▄\e[38;2;204;204;204;48;2;215;215;215m▄\e[38;2;162;162;162;48;2;165;165;165m▄\e[38;2;242;242;242;48;2;243;241;242m▄\e[38;2;205;205;205;48;2;177;176;177m▄\e[38;2;151;151;151;48;2;96;96;96m▄\e[38;2;117;117;118;48;2;56;56;56m▄\e[38;2;123;123;123;48;2;58;58;58m▄\e[38;2;113;113;113;48;2;45;45;45m▄\e[38;2;121;121;121;48;2;52;52;52m▄\e[38;2;118;118;118;48;2;53;53;53m▄\e[38;2;117;117;117;48;2;44;44;44m▄\e[38;2;126;126;126;48;2;64;64;64m▄\e[38;2;123;123;123;48;2;51;51;51m▄\e[38;2;114;114;114;48;2;40;40;40m▄\e[38;2;130;130;130;48;2;64;64;64m▄\e[38;2;124;124;124;48;2;62;62;62m▄\e[38;2;121;121;121;48;2;69;69;69m▄\e[38;2;135;135;135;48;2;83;83;83m▄\e[38;2;129;129;129;48;2;69;69;69m▄\e[38;2;124;124;124;48;2;66;66;66m▄\e[38;2;109;109;109;48;2;50;50;50m▄\e[38;2;111;111;111;48;2;55;55;55m▄\e[38;2;127;127;127;48;2;79;79;79m▄\e[38;2;123;123;123;48;2;70;70;70m▄\e[38;2;119;119;119;48;2;66;66;66m▄\e[38;2;114;114;114;48;2;63;63;63m▄\e[38;2;121;121;121;48;2;71;71;71m▄\e[38;2;116;116;116;48;2;62;62;62m▄\e[38;2;116;116;117;48;2;55;55;55m▄\e[38;2;114;115;116;48;2;47;47;47m▄\e[38;2;113;113;113;48;2;57;57;56m▄\e[38;2;134;134;134;48;2;109;109;109m▄\e[38;2;128;128;129;48;2;94;94;95m▄\e[38;2;118;118;119;48;2;75;75;75m▄\e[38;2;114;114;114;48;2;66;66;67m▄\e[38;2;115;115;115;48;2;85;85;85m▄\e[38;2;118;118;118;48;2;92;92;92m▄\e[38;2;116;116;116;48;2;99;99;99m▄\e[38;2;115;115;115;48;2;94;94;94m▄\e[38;2;113;113;114;48;2;100;100;100m▄\e[38;2;108;108;108;48;2;87;87;87m▄\e[38;2;105;105;105;48;2;64;64;64m▄\e[38;2;83;83;83;48;2;48;47;47m▄\e[38;2;130;130;130;48;2;84;83;83m▄\e[38;2;230;230;230;48;2;220;219;219m▄\e[38;2;254;254;254;48;2;253;253;253m▄\e[48;2;255;255;255m    \e[m\n");
printf("\e[48;2;255;255;255m  \e[38;2;255;255;255;48;2;254;254;254m▄\e[38;2;255;255;255;48;2;253;253;253m▄\e[38;2;255;255;255;48;2;251;251;251m▄▄▄\e[38;2;255;255;255;48;2;250;250;251m▄\e[38;2;255;255;255;48;2;250;250;250m▄\e[38;2;254;254;254;48;2;250;250;250m▄\e[38;2;254;254;254;48;2;250;250;251m▄\e[38;2;255;255;255;48;2;250;250;251m▄\e[38;2;255;255;255;48;2;250;250;250m▄\e[38;2;255;255;255;48;2;250;250;251m▄▄\e[38;2;255;255;255;48;2;250;250;250m▄\e[38;2;254;254;254;48;2;250;250;250m▄\e[38;2;225;225;225;48;2;228;228;228m▄\e[38;2;186;186;186;48;2;195;195;195m▄\e[38;2;174;172;173;48;2;176;175;177m▄\e[38;2;252;250;251;48;2;205;204;205m▄\e[38;2;254;254;254;48;2;252;251;251m▄\e[38;2;255;255;255;48;2;252;251;251m▄\e[38;2;255;255;255;48;2;251;251;251m▄\e[38;2;255;255;255;48;2;250;250;250m▄\e[38;2;255;255;255;48;2;249;249;249m▄▄▄\e[38;2;254;254;254;48;2;249;249;249m▄\e[38;2;246;246;246;48;2;203;203;203m▄\e[38;2;168;168;168;48;2;190;190;190m▄\e[38;2;134;132;133;48;2;188;188;188m▄\e[38;2;120;120;120;48;2;212;212;211m▄\e[38;2;252;252;252;48;2;249;249;249m▄\e[38;2;253;253;253;48;2;248;248;248m▄\e[38;2;254;254;254;48;2;246;246;246m▄\e[38;2;255;255;255;48;2;246;246;246m▄\e[38;2;255;255;255;48;2;245;245;245m▄▄\e[38;2;255;255;255;48;2;244;244;244m▄\e[38;2;255;255;255;48;2;245;245;245m▄▄▄▄\e[38;2;255;255;255;48;2;246;246;246m▄\e[38;2;255;255;255;48;2;244;244;244m▄\e[38;2;254;254;254;48;2;244;244;244m▄▄\e[38;2;255;255;255;48;2;244;244;244m▄\e[38;2;255;255;255;48;2;243;243;243m▄\e[38;2;255;255;255;48;2;242;242;242m▄▄▄\e[38;2;255;255;255;48;2;241;241;241m▄▄▄\e[38;2;255;255;255;48;2;240;240;240m▄▄\e[38;2;253;253;253;48;2;239;239;240m▄\e[38;2;253;253;253;48;2;239;239;239m▄\e[38;2;252;252;252;48;2;239;239;240m▄\e[38;2;253;253;253;48;2;240;240;240m▄\e[38;2;254;254;254;48;2;239;239;239m▄\e[38;2;254;254;254;48;2;236;236;237m▄\e[38;2;255;255;255;48;2;237;237;237m▄\e[38;2;255;255;255;48;2;236;236;236m▄\e[38;2;255;255;255;48;2;234;234;234m▄\e[38;2;255;255;255;48;2;233;233;233m▄\e[38;2;255;255;255;48;2;230;230;230m▄\e[38;2;255;255;255;48;2;229;229;229m▄\e[38;2;255;255;255;48;2;228;228;228m▄▄▄\e[38;2;255;255;255;48;2;239;239;239m▄\e[38;2;255;255;255;48;2;252;252;252m▄\e[38;2;255;255;255;48;2;254;254;254m▄\e[48;2;255;255;255m    \e[m\n");
printf("\e[48;2;255;255;255m    \e[38;2;254;254;254;48;2;255;255;255m▄▄▄\e[48;2;255;255;255m  \e[38;2;254;253;253;48;2;254;254;254m▄\e[38;2;251;250;251;48;2;253;253;253m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;254;254;254;48;2;255;255;255m▄▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;251;251;251;48;2;253;253;253m▄\e[48;2;254;254;254m \e[38;2;253;253;253;48;2;241;241;241m▄\e[38;2;230;230;230;48;2;172;172;172m▄\e[38;2;238;239;238;48;2;181;181;181m▄\e[38;2;254;254;254;48;2;252;252;252m▄\e[48;2;255;255;255m   \e[38;2;254;254;254;48;2;255;255;255m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;251;251;251;48;2;254;254;254m▄\e[48;2;254;254;254m  \e[38;2;252;252;252;48;2;253;253;253m▄\e[38;2;250;249;249;48;2;220;219;219m▄\e[38;2;136;135;136;48;2;50;51;51m▄\e[38;2;146;145;146;48;2;47;47;48m▄\e[38;2;182;181;182;48;2;196;196;196m▄\e[38;2;192;191;192;48;2;230;230;230m▄\e[38;2;180;181;181;48;2;238;238;238m▄\e[38;2;246;246;246;48;2;253;253;253m▄\e[48;2;254;254;254m \e[48;2;255;255;255m      \e[38;2;254;254;254;48;2;255;255;255m▄▄\e[48;2;255;255;255m       \e[48;2;254;254;254m \e[38;2;252;252;252;48;2;253;253;253m▄\e[38;2;250;250;250;48;2;253;253;253m▄\e[48;2;253;253;253m \e[48;2;255;255;255m \e[38;2;251;251;251;48;2;253;253;253m▄\e[38;2;152;152;152;48;2;182;182;182m▄\e[38;2;130;130;130;48;2;138;138;138m▄\e[38;2;164;163;164;48;2;217;217;217m▄\e[38;2;225;225;225;48;2;247;247;247m▄\e[48;2;254;254;254m \e[48;2;255;255;255m                \e[m\n");
printf("\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;254;254;254;48;2;255;255;255m▄▄\e[38;2;253;253;253;48;2;255;255;255m▄\e[38;2;248;248;248;48;2;251;251;251m▄\e[38;2;251;251;251;48;2;249;249;249m▄\e[48;2;254;254;254m \e[38;2;254;254;254;48;2;255;255;255m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;249;248;249;48;2;252;251;251m▄\e[38;2;249;248;249;48;2;249;248;248m▄\e[38;2;254;254;254;48;2;253;253;253m▄\e[48;2;254;254;254m \e[38;2;248;247;248;48;2;253;253;253m▄\e[38;2;245;244;245;48;2;245;245;245m▄\e[38;2;252;252;252;48;2;249;249;249m▄\e[38;2;254;254;254;48;2;253;253;253m▄\e[38;2;249;249;249;48;2;252;252;252m▄\e[38;2;251;251;251;48;2;253;253;253m▄\e[48;2;253;253;253m \e[38;2;251;251;251;48;2;254;254;254m▄▄\e[38;2;254;254;254;48;2;255;255;255m▄▄\e[38;2;251;251;251;48;2;254;254;254m▄\e[38;2;247;247;247;48;2;251;251;251m▄\e[38;2;247;247;247;48;2;249;249;249m▄\e[48;2;253;253;253m \e[48;2;254;254;254m \e[38;2;248;248;248;48;2;250;250;250m▄\e[38;2;243;243;243;48;2;247;247;247m▄\e[38;2;243;243;243;48;2;181;180;181m▄\e[38;2;241;241;241;48;2;149;147;148m▄\e[38;2;250;250;250;48;2;152;151;152m▄\e[38;2;250;249;250;48;2;163;163;165m▄\e[38;2;252;250;251;48;2;199;198;200m▄\e[38;2;254;254;254;48;2;249;249;249m▄\e[38;2;251;251;251;48;2;253;253;253m▄\e[38;2;251;251;251;48;2;254;254;254m▄\e[48;2;254;254;254m \e[48;2;255;255;255m   \e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;251;251;251;48;2;253;253;253m▄\e[38;2;248;248;248;48;2;252;252;252m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;254;254;254;48;2;255;255;255m▄▄▄▄\e[38;2;253;253;253;48;2;255;255;255m▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;251;251;251;48;2;254;254;254m▄\e[48;2;253;253;253m \e[38;2;249;249;249;48;2;250;250;250m▄\e[38;2;248;248;248;48;2;253;253;253m▄\e[38;2;254;254;254;48;2;255;255;255m▄\e[38;2;251;251;251;48;2;252;252;252m▄\e[38;2;249;249;249;48;2;211;211;211m▄\e[38;2;250;250;250;48;2;182;182;182m▄\e[38;2;245;245;245;48;2;188;188;188m▄\e[38;2;247;247;247;48;2;236;236;236m▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;253;253;253;48;2;255;255;255m▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;251;251;251;48;2;254;254;254m▄\e[38;2;253;253;253;48;2;255;255;255m▄\e[38;2;254;254;254;48;2;255;255;255m▄▄▄▄\e[48;2;255;255;255m \e[38;2;254;254;254;48;2;255;255;255m▄▄▄\e[48;2;255;255;255m \e[38;2;254;254;254;48;2;255;255;255m▄▄▄\e[m\n");
printf("\e[38;2;248;248;248;48;2;251;251;251m▄\e[38;2;245;244;245;48;2;252;252;252m▄\e[38;2;243;242;243;48;2;251;251;251m▄\e[38;2;233;232;233;48;2;246;246;246m▄\e[38;2;248;248;248;48;2;245;245;245m▄\e[38;2;249;249;249;48;2;252;252;252m▄\e[38;2;252;252;252;48;2;253;253;253m▄\e[38;2;250;249;250;48;2;253;253;253m▄\e[38;2;237;236;236;48;2;248;248;248m▄\e[38;2;242;242;242;48;2;239;239;239m▄\e[38;2;252;252;252;48;2;250;250;250m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;248;247;248;48;2;252;252;252m▄\e[38;2;237;236;237;48;2;243;241;242m▄\e[38;2;243;243;243;48;2;244;243;244m▄\e[38;2;251;251;251;48;2;252;252;252m▄\e[38;2;248;248;248;48;2;252;252;252m▄\e[38;2;235;235;236;48;2;243;243;243m▄\e[48;2;247;247;247m \e[38;2;250;249;249;48;2;252;252;252m▄\e[38;2;233;233;233;48;2;239;239;239m▄\e[38;2;248;248;248;48;2;247;247;247m▄\e[38;2;251;251;251;48;2;252;252;252m▄\e[38;2;247;247;247;48;2;252;252;252m▄\e[38;2;244;242;243;48;2;247;247;247m▄\e[38;2;236;235;236;48;2;243;242;242m▄\e[38;2;244;243;244;48;2;244;243;243m▄\e[48;2;253;253;253m \e[38;2;251;250;251;48;2;253;253;253m▄\e[38;2;236;235;237;48;2;243;243;243m▄\e[38;2;234;234;234;48;2;239;239;239m▄\e[38;2;243;243;243;48;2;245;245;245m▄\e[38;2;247;247;247;48;2;252;252;252m▄\e[38;2;241;241;241;48;2;249;249;249m▄\e[38;2;233;233;234;48;2;243;243;243m▄\e[38;2;250;250;250;48;2;251;251;251m▄\e[38;2;252;252;252;48;2;253;253;253m▄\e[38;2;244;244;245;48;2;248;248;248m▄\e[38;2;245;245;246;48;2;249;249;249m▄\e[38;2;253;253;253;48;2;254;254;254m▄▄▄\e[48;2;254;254;254m \e[38;2;247;247;247;48;2;251;251;251m▄\e[48;2;251;251;251m \e[38;2;244;244;244;48;2;246;246;246m▄\e[38;2;245;245;245;48;2;251;251;251m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;248;248;248;48;2;252;252;252m▄\e[38;2;250;250;250;48;2;253;253;253m▄\e[38;2;252;252;252;48;2;253;253;253m▄\e[48;2;253;253;253m \e[38;2;246;245;245;48;2;250;250;250m▄\e[38;2;243;243;244;48;2;248;248;249m▄\e[38;2;245;245;245;48;2;251;251;251m▄\e[38;2;250;250;250;48;2;251;251;251m▄\e[38;2;243;242;243;48;2;243;243;243m▄\e[38;2;247;246;247;48;2;253;253;253m▄\e[38;2;253;253;253;48;2;253;253;252m▄\e[38;2;244;241;243;48;2;243;241;243m▄\e[38;2;228;228;229;48;2;244;244;244m▄\e[38;2;241;240;240;48;2;242;242;242m▄\e[38;2;232;230;232;48;2;239;238;238m▄\e[38;2;242;240;242;48;2;250;248;249m▄\e[38;2;250;248;249;48;2;252;251;252m▄\e[38;2;253;253;253;48;2;252;252;252m▄\e[38;2;242;242;242;48;2;247;247;247m▄\e[38;2;245;245;245;48;2;251;251;251m▄\e[38;2;250;250;250;48;2;252;252;252m▄\e[38;2;245;245;245;48;2;250;250;250m▄\e[38;2;251;251;251;48;2;253;253;253m▄\e[38;2;253;253;253;48;2;254;254;254m▄\e[38;2;252;252;252;48;2;254;254;254m▄\e[38;2;251;251;251;48;2;253;253;253m▄\e[38;2;248;248;248;48;2;252;252;252m▄\e[38;2;252;252;252;48;2;253;253;253m▄\e[48;2;254;254;254m  \e[38;2;250;249;249;48;2;253;253;253m▄\e[38;2;248;248;248;48;2;252;252;252m▄\e[m\n");
printf("\e[49;38;2;238;236;237m▀\e[49;38;2;238;236;238m▀\e[49;38;2;228;226;227m▀\e[49;38;2;241;239;240m▀\e[49;38;2;247;246;247m▀\e[49;38;2;241;241;241m▀\e[49;38;2;250;250;250m▀\e[49;38;2;239;237;239m▀\e[49;38;2;230;228;229m▀\e[49;38;2;250;249;249m▀\e[49;38;2;252;252;252m▀\e[49;38;2;250;250;250m▀\e[49;38;2;234;233;234m▀\e[49;38;2;240;239;239m▀\e[49;38;2;247;247;247m▀\e[49;38;2;252;252;252m▀\e[49;38;2;238;238;238m▀\e[49;38;2;230;230;231m▀\e[49;38;2;248;248;248m▀\e[49;38;2;241;239;240m▀\e[49;38;2;237;236;236m▀\e[49;38;2;250;250;250m▀▀\e[49;38;2;240;240;240m▀\e[49;38;2;239;237;238m▀\e[49;38;2;230;228;231m▀\e[49;38;2;245;244;245m▀\e[49;38;2;253;253;253m▀\e[49;38;2;244;244;244m▀\e[49;38;2;231;230;232m▀\e[49;38;2;231;230;231m▀\e[49;38;2;244;244;244m▀\e[49;38;2;241;241;241m▀\e[49;38;2;238;238;238m▀\e[49;38;2;230;230;230m▀\e[49;38;2;251;251;251m▀\e[49;38;2;253;253;253m▀\e[49;38;2;241;241;241m▀\e[49;38;2;242;242;242m▀\e[49;38;2;252;252;252m▀\e[49;38;2;251;251;251m▀▀\e[49;38;2;253;253;253m▀\e[49;38;2;242;242;242m▀\e[49;38;2;250;250;250m▀\e[49;38;2;244;244;244m▀\e[49;38;2;237;237;237m▀\e[49;38;2;252;252;252m▀\e[49;38;2;241;240;240m▀\e[49;38;2;247;247;247m▀\e[49;38;2;249;249;249m▀\e[49;38;2;253;252;252m▀\e[49;38;2;243;241;242m▀\e[49;38;2;238;237;238m▀\e[49;38;2;237;236;237m▀\e[49;38;2;249;247;248m▀\e[49;38;2;244;242;245m▀\e[49;38;2;239;238;239m▀\e[49;38;2;251;251;251m▀\e[49;38;2;251;249;250m▀\e[49;38;2;224;223;224m▀\e[49;38;2;233;231;233m▀▀\e[49;38;2;226;224;226m▀\e[49;38;2;242;240;241m▀\e[49;38;2;252;252;252m▀\e[49;38;2;247;247;247m▀\e[49;38;2;234;234;234m▀\e[49;38;2;250;250;250m▀\e[49;38;2;245;245;245m▀\e[49;38;2;243;243;243m▀\e[49;38;2;249;249;249m▀\e[49;38;2;248;248;248m▀\e[49;38;2;251;251;251m▀\e[49;38;2;248;248;248m▀\e[49;38;2;242;242;242m▀\e[49;38;2;251;251;251m▀\e[49;38;2;253;253;253m▀\e[49;38;2;246;245;245m▀\e[49;38;2;239;239;239m▀\e[m\n");
printf("\e[0m");
}

void thank()
{
printf("\e[34;47m");
printf("\e[34;47m████████████████████████████████████████████████████████████████████████████████\e[0m\n");
printf("\e[34;47m█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█\e[0m\n");
printf("\e[34;47m█░░░░░░░░░░░░░░░\e[0;104m╔════╗╔╗\e[34;47m░\e[0;104m╔╗╔═══╗╔═╗\e[34;47m░\e[0;104m╔╗╔╗╔═╗\e[34;47m░░\e[0;104m╔╗\e[34;47m░░\e[0;104m╔╗╔═══╗╔╗\e[34;47m░\e[0;104m╔╗\e[34;47m░\e[0;104m╔╗\e[34;47m░░░░░░░░░░░░░░░█\e[0m\n");
printf("\e[34;47m█░░░░░░░░░░░░░░░\e[0;104m║╔╗╔╗║║║\e[34;47m░\e[0;104m║║║╔═╗║║║╚╗║║║║║╔╝\e[34;47m░░\e[0;104m║╚╗╔╝║║╔═╗║║║\e[34;47m░\e[0;104m║║\e[34;47m░\e[0;104m║║\e[34;47m░░░░░░░░░░░░░░░█\e[0m\n");
printf("\e[34;47m█░░░░░░░░░░░░░░░\e[0;104m╚╝║║╚╝║╚═╝║║║\e[34;47m░\e[0;104m║║║╔╗╚╝║║╚╝╝\e[34;47m░░░\e[0;104m╚╗╚╝╔╝║║\e[34;47m░\e[0;104m║║║║\e[34;47m░\e[0;104m║║\e[34;47m░\e[0;104m║║\e[34;47m░░░░░░░░░░░░░░░█\e[0m\n");
printf("\e[34;47m█░░░░░░░░░░░░░░░░░\e[0;104m║║\e[34;47m░░\e[0;104m║╔═╗║║╚═╝║║║╚╗║║║╔╗║\e[34;47m░░░░\e[0;104m╚╗╔╝\e[34;47m░\e[0;104m║║\e[34;47m░\e[0;104m║║║║\e[34;47m░\e[0;104m║║\e[34;47m░\e[0;104m╚╝\e[34;47m░░░░░░░░░░░░░░░█\e[0m\n");
printf("\e[34;47m█░░░░░░░░░░░░░░░░░\e[0;104m║║\e[34;47m░░\e[0;104m║║\e[34;47m░\e[0;104m║║║╔═╗║║║\e[34;47m░\e[0;104m║║║║║║╚╗\e[34;47m░░░░\e[0;104m║║\e[34;47m░░\e[0;104m║╚═╝║║╚═╝║\e[34;47m░\e[0;104m╔╗\e[34;47m░░░░░░░░░░░░░░░█\e[0m\n");
printf("\e[34;47m█░░░░░░░░░░░░░░░░░\e[0;104m╚╝\e[34;47m░░\e[0;104m╚╝\e[34;47m░\e[0;104m╚╝╚╝\e[34;47m░\e[0;104m╚╝╚╝\e[34;47m░\e[0;104m╚═╝╚╝╚═╝\e[34;47m░░░░\e[0;104m╚╝\e[34;47m░░\e[0;104m╚═══╝╚═══╝\e[34;47m░\e[0;104m╚╝\e[34;47m░░░░░░░░░░░░░░░█\e[0m\n");
printf("\e[34;47m█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█\e[0m\n");
printf("\e[34;47m████████████████████████████████████████████████████████████████████████████████\e[0m");
printf("\n");
}