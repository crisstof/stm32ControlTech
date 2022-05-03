
//main.c
/* Includes */
#include "stm32l4xx.h"
#include "stm32l476xx.h"

void TIM2_IRQHandler(void);


int main(void){
	
	
		//sortie PA6
	  RCC -> AHB2ENR |= 1<<0;
	  GPIOA->MODER &= 0xFFFFDFFF;
   
	  //TIM2
		 RCC -> APB1ENR1 |= 1<<0;//RCC_APB1ENR1_TIM3EN;// 1<<1;  //RCC_APB1ENR1_TIM3EN;
  		TIM2->PSC = 8000;//prescaler      configuration de la periode
			TIM2->ARR = 999;

       //débordement on envoit une demande d'interuption au coeur
	     TIM2->DIER |= (1<<0);
       //config de l'irq sur le coeur
     	NVIC->ISER[0] = NVIC->ISER[0]  | (1<<28);//irq doit être accepté
  	  NVIC->IP[28] |= (7<<4);
	
	//lancer  le timer2
	 TIM2->CR1 = TIM1->CR1 | (1<<0);
					
	
	
    while(1) {

       /*traitement de scrutation*/
   	}
}

void TIM2_IRQHandler(void){
  TIM2->SR &= ~TIM_SR_UIF;
	GPIOA->ODR = GPIOA->ODR ^(1<<6);
}
