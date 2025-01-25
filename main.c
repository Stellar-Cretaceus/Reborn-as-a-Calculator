#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "function.h"
/* 
*Main Objective*
1.ทำหน้า Interface ตรง main
  1) หน้าให้กดพิมพ์สมการเลขปกติ (√)
  2) หน้าให้เลือกแปลง Infix Prefix Postfix (√)
  3) หน้าดูประวัติ 5 ตัวท้าย (√)
  4) เมนูปิดโปรแกรม (√)
2.ทำ Function แปลง Prefix Infix Postfix
ทำแค่ Infix to Prefix หรือ Postfix พอ (√)
3. ทำ Queue สำหรับ AutoSave แล้วดูได้หรือเอามาคิดต่อได้ (√)
4. ทำหน้า Setting ไว้ตั้งค่าจุดทศนิยม (√)
5. คิดรูทให้ได้ ยกกำลังให้ได้ (√)
√√√√√√√√√√√√√√√√√√√√√√√√√√√√√√

*Extras*
1. Save slot ที่เพิ่มมากขึ้นกว่าเดิม
2. คิดเลขจาก Prefix Postfix โดยตรง
3. ดักพิมพ์ผิด Function มั่ว (พวกหาร 0) (√)
4. ให้คิดตัวแปรได้ (ติดตัวแปรตรงคำตอบ)
5. Prefix Postfix ไปอย่างอื่นได้



*/




int main(void) {
  int set=2;
  char operation;
  char intbuff[50];

  queue* q = malloc(sizeof(queue));
  initialize(q);
  //สร้างคิวรอ

slime();
//printf("Welcome to \"Reborn as a calculator!\" \n");
welcome();
  
printf("\e[0;94m");
printf("\n================================================================\n\n");
printf("\e[0m");
  //Loop Interface
  while (1)
    {
      printf("Menu\n");
      printf("1. Normal calculator\n");
      printf("2. Convert to Infix Prefix Postfix\n");
      printf("3. History page\n");
      printf("4. Setting decimal point\n");
      printf("5. Exit the program\n");
      printf("Please select the following options : ");

      fgets(intbuff, 50, stdin);
      removeEnter(intbuff);
      operation = intbuff[0];
      //ดัก
      if(isprint(intbuff[1])!=0)
      {
        printf("\e[0;31m");
        printf("\n-----------------------------Error!-----------------------------\n\n");
        printf("\e[0m");
        continue;
      }
      switch(operation)
      {
        case '1':
            //Input Function
            CalculateFunction(set,q);
            break;

        case '2':
            //Infix Prefix postfix case
            InfixSelect();
            break;

        case '3':
            //History
            display(q, set);
            break;

        case '4':
            set=setting(set);
            break;

        case '5':
            printf("\e[0;94m");
            printf("\n================================================================\n\n");
            printf("\e[0m");
            thank();
            trucksan();
            return 0;
            break;

        default:
            printf("\e[0;31m");
            printf("\n-----------------------------Error!-----------------------------\n");
            printf("\e[0m");
      }
        printf("\e[0;94m");
        printf("\n================================================================\n\n");
        printf("\e[0m");
    }

    
  return 0;
}