#include <stdio.h>
#include "stm32f4xx.h"

 int conteo[24]={63, 6, 91, 79, 102, 109, 125, 7, 127, 103, 119, 124, 57, 94, 121, 113, 1, 2, 4, 8, 16, 32, 64, 128};
 //               0  1   2   3    4    5    6  7    8    9    A    B   C   D    E    F
 int led[8]={1,2,4,8,16,32,64,128};
 int pulsador=0,base=0, num1, num2, time;
	 
 void Ascendente(){
	 for(int a=num1;a<=num2;a++){  
		 for(int t=0;t<500000;t++)		
			 GPIOD -> ODR = conteo[a];
	 }
 }
 
 void Descendente(){
	 for(int b=num2;b>=num1;b--){  
		 for(int t=0;t<500000;t++)		
			 GPIOD -> ODR = conteo[b];
	 }
 }

 void LEDS(){
	 if(pulsador == 3){//de izquierda a derecha
			 for(int a=17; a<=24; a++){
				GPIOE -> ODR = conteo[a];for(time=0; time<600000; time++);
			 }
	 }else if(pulsador == 4){//de derecha a izquierda
			 for(int a=24; a>=17; a--){
				 GPIOE -> ODR = conteo[a];for(time=0; time<600000; time++);
			 }
	 }	  
 } 
 
int main(void)
{
RCC ->AHB1ENR=0x1C; // habilitar puerto C,D,E 
	GPIOD ->MODER=0x00555555;             
	GPIOD -> OTYPER=0;       
	GPIOD -> OSPEEDR=0x00555555;               
	GPIOD -> PUPDR=0x005555;                 
	
	GPIOE -> MODER=0x00555555;         
	GPIOE -> OTYPER=0;                   
	GPIOE -> OSPEEDR=0x00555555;      
	GPIOE -> PUPDR=0x005555;     
	
	GPIOC -> MODER=0x0;        
  while (1)
  {
    
		if((GPIOC -> IDR&0x2000)==0x2000){   
			pulsador++;
			if(pulsador>4)(pulsador=0);	
      base++;
			if(base>3)(base=0);			
  }
		
	switch (base){
		case 1:  //decimal
			num1=0;num2=9;
		if (pulsador==1) {Ascendente();} 
		else { Descendente();}
		break;
		
		case 2://hexadecimal
			num1=11;num2=16;
		if (pulsador==1) {Ascendente();}
		else { Descendente();}
		break;
		
		case 3://octal
			num1=0;num2=8;
		if (pulsador==1) {Ascendente();}
		else { Descendente();}
		break;
		
		default:
			num1=0;num2=0;
		if (pulsador==1) {Ascendente();}
		else { Descendente();}
		break;
	}LEDS();
 }
}
