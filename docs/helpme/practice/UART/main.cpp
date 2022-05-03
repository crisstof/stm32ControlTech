//main.c
/* Includes */
#include "stm32l4xx.h"
#include "stm32l476xx.h"

//#include "IT_TIM2.h"

void configure_usart1_9600bps();
void send(char data);
int configure_gpio_alternate_push_pull(GPIO_TypeDef *gpio, int pin);



int main(void){

	char data = 'A';
	int cmpt = 0;
	configure_gpio_alternate_push_pull (GPIOA, 9);
	configure_usart1_9600bps ();
while (cmpt < 26)	{
	    send(data+cmpt);
	    cmpt ++;
	}
    while(1) {

       /*traitement de scrutation*/
   	}
		
		return 0;
}


void configure_usart1_9600bps(){
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // validation horloge USART1
    USART1->CR1 |= USART_CR1_UE; // Activation de l'USART
    USART1->CR1 &= ~USART_CR1_M; // Choix d'une taille de 8 bits de données
    USART1->CR2 &= USART_CR2_STOP; // Choix d'un seul bit de stop
    USART1->BRR |= 468 << 4; // Fixe le baud rate à 9600bps
    USART1->BRR |= 75; // Fixe le baud rate à 9600bps
    USART1->CR1 |= USART_CR1_TE; // Envoi de la première trame d'attente
}

void send(char data){
    USART1->DR |= data; // Ecriture de la donnée dans le registre DR
    while(!(USART1->SR & USART_SR_TC)) {} // Attente de la fin de transmission
}

int configure_gpio_alternate_push_pull(GPIO_TypeDef *gpio, int pin){
    If (gpio == GPIOA) {
        RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	
    } else if (gpio == GPIOB){
        RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    } else if (gpio == GPIOC){
        RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    } else {
	    return -1;
    }
    if (pin < 8){
        gpio->CRL &= ~((0xF << 4*pin)| (0xF << 4*pin));
        gpio ->CRL |= (0xA << 4*pin);
    } else if (pin < 15){
        pin = pin – 8;
        gpio ->CRH &= ~((0xF << 4*pin) | (0xF << 4*pin));
        gpio ->CRH |= (0xA << 4*pin);
    } else {
        return -1;
    }
		
		
		/*
		pa6 altrrnate push_pull
		uint32_t position = 0x00u;
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
		GPIOA->MODER &= 0xFFFFFFFF;
		GPIOA->AFR[position>>3u] = 0x02000000;
		
		*/
    return 0;
}