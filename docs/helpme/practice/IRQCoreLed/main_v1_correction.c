#include "stm32f10x.h"

/*****************************************************************
Preambule : indiquez ici les periopheriques que vous avez utilisez
*****************************************************************/

// GPIOA   : broche 6 pour controler la LED verte
// GPIOC : broche 13 pour détecter l'appui du bouton
// TIM2 : chronometre les 300 ms
// TIM3 : chronometre l'intervalle de temps avant d'aller la LED


/*****************************************************************
Declaration des fonctions²²
*****************************************************************/
int rand(void);
void configure_gpio_pa5(void) ;
void configure_gpio_pc13(void) ;
void set_gpio(GPIO_TypeDef *GPIO, int n) ;
void reset_gpio(GPIO_TypeDef *GPIO, int n) ;
void configure_timer(TIM_TypeDef *TIM, int psc, int arr) ;
void configure_it(void) ;
void start_timer(TIM_TypeDef *TIM) ;
void stop_timer(TIM_TypeDef *TIM) ;
~
/*****************************************************************
Varibales globales
 *****************************************************************/

/*****************************************************************
MAIN
*****************************************************************/

int main(void){
	
    // Configuration des ports d'entree/sortie
	configure_gpio_pa5();
	configure_gpio_pc13();
    
    // Configuration des timers
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN ;
	configure_timer(TIM2, 7199, 2999);
	configure_timer(TIM3, 7199, 10*rand());
    
    // Configuration des interruptions
	configure_it();
    
    // Demarrage du permier timer
    start_timer(TIM3);
    
    // Boucle d'attente du processeur
	while (1);
    
	return 0;
}

/*****************************************************************
Corps des fonctions
*****************************************************************/

/**
Configure la broche 5 du port A (led verte)
*/
void configure_gpio_pa5(void){
	// Activation de l'horloge de GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	// Ouput push-pull : 0b0001
	GPIOA->CRL &= ~(0xF << 20);
	GPIOA->CRL |= (0x01 << 20);
}

/**
Configure la broche 13 du port C (bouton USER) 
*/
void configure_gpio_pc13(void) {
	// Activation de l'horloge de GPIOC
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	// Input floating 0b0100
	GPIOC->CRH &= ~(0xF << 20);
	GPIOC->CRH |= (0x01 << 22 );
}

/**
Met a 1 la sortie la broche n du port GPIO
*/
void set_gpio(GPIO_TypeDef *GPIO, int n) {
	GPIO->ODR |= (0x01 << n);
}

/**
Met a 0 la sortie la broche n du port GPIO
*/
void reset_gpio(GPIO_TypeDef *GPIO, int n) {
		GPIO->ODR &= ~(0x01 << n);
}

/**
Configure la periode du timer TIM en fonction des parametres
psc (prescaler) et arr (autoreload) sans lancer le timer
*/
void configure_timer(TIM_TypeDef *TIM, int psc, int arr) {
	TIM->ARR = arr;
	TIM->PSC = psc;
}

/**
Demarre le timer TIM
*/
void start_timer(TIM_TypeDef *TIM) {
	TIM->CR1 |= 0x01;
}

/**
Arrete le timer TIM
*/
void stop_timer(TIM_TypeDef *TIM) {
	TIM->CR1 &= ~0x01;
}

/**
Configure toutes les interruptions du systeme
*/
void configure_it(void) {
	// Interruption du timer 2
	TIM2->DIER |= TIM_DIER_UIE; // validation de l'it de TIM2
	NVIC->ISER[0] |= NVIC_ISER_SETENA_28 ; // validation de l'IT 28 (TIM2) dans le NVIC
	// Interruption du timer 3
	TIM3->DIER |= TIM_DIER_UIE; // validation de l'it de TIM3
	NVIC->ISER[0] |= NVIC_ISER_SETENA_29 ; // validation de l'IT 29 (TIM3) dans le NVIC
}

/**
Configure le port PC13 comme source d'interruption externe
Fonction uniquement utile pour la version 2 du rendu.
*/
void configure_afio_exti_pc13(void) {

}

/*****************************************************************
Fonctions d'interruption
*****************************************************************/

void TIM2_IRQHandler(void){
	reset_gpio(GPIOA, 5); // eteind la led
	stop_timer(TIM2); // arret du timer TIM2
	configure_timer(TIM3, 7199, 10*rand()); // mise ˆ jour des parametres de TIM3
	start_timer(TIM3); // demarrage de TIM2
	TIM2->SR &= ~TIM_SR_UIF ; // validation de l'IT dans le periph
}

void TIM3_IRQHandler(void){
	set_gpio(GPIOA, 5); // allume la led
	stop_timer(TIM3); // arret du timer TIM3
	start_timer(TIM2); // demarrage du time TIM2 (les paramtres restent les memes)
	TIM3->SR &= ~TIM_SR_UIF ; // validation de l'IT dans le periph
}

/*****************************************************************
Fonctions pre-definies
*****************************************************************/

/**
Retourne une valeur entiere aleatoire comprise entre 800 et 1800
*/
int rand(){
	static int randomseed = 0;
	randomseed = (randomseed * 9301 + 49297) % 233280;
	return 800 + (randomseed % 1000);
}

