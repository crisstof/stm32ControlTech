//main.c
/* Includes */
#include "stm32l4xx.h"
#include "stm32l476xx.h"

void configure_gpio_pa6_push_pull(void);
void configure_pwm_ch1_20khz(TIM_TypeDef *TIMER);
void start_timer(TIM_TypeDef *TIMER);
void set_pulse_percentage(TIM_TypeDef *TIMER, unsigned int pulse);

void configure_timer2_with_IT(void);
void TIM2_IRQHandler(void);


int main(void){
	 
	configure_gpio_pa6_push_pull();
	configure_pwm_ch1_20khz(TIM3);
	set_pulse_percentage(TIM3, 0x100);

	configure_timer2_with_IT();
	start_timer(TIM3);

	start_timer(TIM2);

    while(1) {

       /*traitement de scrutation*/
   	}
}
	
void configure_gpio_pa6_push_pull(void){
	 uint32_t position = 0x00u;
	//configuration de la broche en sortie PA.6
			RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOAEN  ;// Activer l'horloge gpioa
			GPIOA->MODER &= 0xFFFFEFFF; //alternate function mode 10/0xABFFEFFF
	    GPIOA->AFR[position>>3u] = 0x02000000;// |= 0x02000000;
	 
}	
	
void configure_pwm_ch1_20khz(TIM_TypeDef *TIMER){
	/*****Set timer Period PWM*****
	Timer clock 80MHz
	Period required = (1/50HZ)=0.02 seconds
	TIM3 16bits resolution  653535
	ARR value be 65535 then
	prescaler + 1   = 80000000/(ARR+1)50Hz
	prescaler = 24 (approx)	
	TIM3
  ********************************/
	//configuration du timer3 TIM3 (32bits)
			RCC -> APB1ENR1 |= RCC_APB1ENR1_TIM3EN;
			TIMER->PSC = 0;//prescaler  (80)    configuration de la periode
			//TIMER->ARR = 3999;//autoreload (100)configuration de la periode
	          //Configurer canal CH1 en mode pwm
	        //affecter la valeur 0b110 aux bits OC1M dans
	        //le registre CCMR1 du timer
			TIMER->CCMR1 |=  TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE;
	        //il faut aussi que CH1 de sortie est validé
	        //par le bit CC1E du Reg CCER du timer
			TIMER->CCER |= TIM_CCER_CC1E;
}
	
void start_timer(TIM_TypeDef *TIMER){
	//enfin lancer le timer
	        TIMER->CR1 |= TIM_CR1_CEN;
}
	
void set_pulse_percentage(TIM_TypeDef *TIMER, unsigned int pulse){
	//régler la durée de l'impulsion
	        //fixe dans Reg CCR1 à 20% de la résolution soit 719
	        //TIM3->CCR1=719;
	TIMER->CCR1 = TIMER->ARR * pulse/100;

}


void configure_timer2_with_IT(void){

	RCC->APB1ENR1 |= 1<<0;
	TIM2->ARR= 999;
	TIM2->PSC=8000;
    TIM2->DIER |= (1<<0);
    NVIC->ISER[0] = NVIC->ISER[0] | (1<<28);
    NVIC->IP[28] |= (7<<4);
}


void TIM2_IRQHandler(void){

	static unsigned int pulse =0;
	TIM3->SR &= TIM_SR_UIF;
	pulse = (pulse +5) %101;
	set_pulse_percentage(TIM3, pulse);
}