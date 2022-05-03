//main.c
/* Includes */
#include "stm32l4xx.h"
#include "stm32l476xx.h"

//#include "IT_TIM2.h"

//ADC12_IN15  PB.0  pin26
void configure_gpio_pb0_analog_input(void);

void  configure_pwm_ch1_20khz(TIM3); 
void set_pulse_percentage(TIM_TypeDef  *TIMER, unsigned int pulse);
void configure_adc_in8(void);
void start_timer(TIM_TypeDef *TIMER);


int  main(void){
	int res = 0;
    // Configuration de la PWM
    void configure_gpio_pb0_analog_input(); 
    configure_pwm_ch1_20khz(TIM3); 
    set_pulse_percentage(TIM3, 0); 
    // Configuration de l'ADC
    configure_gpio_alternate_push_pull();
    configure_adc_in8();
    // Démarrage de la PWM
    start_timer(TIM3);
    while(1)
	{
        res = convert_single(); // conversion
        set_pulse_percentage(TIM3, 100 * res / 0xFFF ) // mise à jour de l’intensité de la led
	}
}

void configure_adc_in8(){
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // validation horloge ADC1
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; // passage de l'horloge ADC1 à 12MHz
    ADC1->CR2|= ADC_CR2_ADON; // démarrage ADC1
    ADC1->SQR1&= ADC_SQR1_L; // fixe le nombre de conversion à 1
    ADC1->SQR3|= 8; // indique la voie à convertir
    ADC1->CR2 |= ADC_CR2_CAL; // dÈbut de la calibration
    while ((ADC1->CR2 & ADC_CR2_CAL)); // attente de la fin de la calibration
}

int convert_single(){
    ADC1->CR2 |= ADC_CR2_ADON; // lancement de la conversion
    While(!(ADC1->SR & ADC_SR_EOC) ) {} // attente de la fin de conversion
    ADC1->SR &= ~ADC_SR_EOC; // validation de la conversion
    return ADC1->DR & ~((0x0F) << 12); // retour de la conversion
}

//Broche USART PA.9 en mode alternat push pull
void configure_gpio_pb0_analog_input(){
	//uint32_t position = 0x20u;
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
		GPIOA->MODER &= 0xABFBFFFF; //PA9 alternate function mode 10
		//GPIOA->OTYPER = 0x0000000;
		GPIOA->AFR[1] = 0x0000070;
}


void set_pulse_percentage(TIM_TypeDef  *TIMER, unsigned int pulse){
	
	TIMER->CCR1 = TIMER->ARR * pulse/100;
}

void start_timer(TIM_TypeDef *TIMER){
    TIMER->CR1 |= TIM_CR1_CEN;
}
