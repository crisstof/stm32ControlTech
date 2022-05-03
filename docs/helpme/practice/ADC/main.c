//main.c
/* Includes */
#include "stm32l4xx.h"
#include "stm32l476xx.h"

//#include "IT_TIM2.h"

void configure_usart1_9600bps(void);
void send(char data);
void configure_gpio_alternate_push_pull(void);
int  main(void){
	char data = 'A';
	int cmpt = 0;
	configure_gpio_alternate_push_pull ();
	configure_usart1_9600bps ();
	while (cmpt < 26)	{
				send(data);
				cmpt ++;
		}
    while(1) {
       /*traitement de scrutation*/
   	}
}
void configure_usart1_9600bps(){
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // validation horloge USART1
     USART1->CR1 |= USART_CR1_TE; // Envoi de la première trame d'attente
																	//bit d'activation de transmission (TE) 
																	//doit être défini pour activer la fonction emetteur
	 USART1->CR1 |= USART_CR1_RE; // Envoi de la première trame d'attente
																	//bit d'activation de transmission (TE) 
																	//doit être défini pour activer la fonction emetteur
   USART1->BRR |= 0x001A << 4;  // Fixe le baud rate à 9600bps mauvais calcul 520 
    USART1->BRR |= 0x01; // Fixe le baud rate à 9600bps 83  
   USART1->CR1 |= USART_CR1_UE; // Activation de l'USART
}
void send(char data){
    USART1->TDR |= data; // Ecriture de la donnée dans le registre DR 0x0041 = A
    while(!(USART1->ISR & USART_ISR_TC)) {} //attente fin de transmission
} //attendre le bit TC du registre SR passe à 1 (indique la dernière trame a été transmise)

//Broche USART PA.9 en mode alternat push pull
void configure_gpio_alternate_push_pull(){
	//uint32_t position = 0x20u;
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
		GPIOA->MODER &= 0xABFBFFFF; //PA9 alternate function mode 10
		//GPIOA->OTYPER = 0x0000000;
		GPIOA->AFR[1] = 0x0000070;
}





