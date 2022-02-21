/*
 * state.h
 *
 *  Created on: Jan 1, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdint.h>
#include <stdio.h>

#define SET_BIT(ADDRESS,BIT)   ADDRESS |=  (1<<BIT)
#define RESET_BIT(ADDRESS,BIT) ADDRESS &= ~(1<<BIT)
#define TOGGLE_BIT(ADDRESS,BIT)  ADDRESS ^=  (1<<BIT)
#define READ_BIT(ADDRESS,BIT) ((ADDRESS) &   (1<<(BIT)))


#define GPIO_PORTA 0x40010800
#define BASE_RCC   0x40021000

#define APB2ENR   *(volatile uint32_t *)(BASE_RCC + 0x18)

#define GPIOA_CRL *(volatile uint32_t *)(GPIO_PORTA + 0x00)
#define GPIOA_CRH *(volatile uint32_t *)(GPIO_PORTA + 0X04)
#define GPIOA_IDR *(volatile uint32_t *)(GPIO_PORTA + 0x08)
#define GPIOA_ODR *(volatile uint32_t *)(GPIO_PORTA + 0x0C)

/*
#define Cprint(...)	{fflush(stdin);\
					fflush(stdout);\
					printf(__VA_ARGS__);\
					fflush(stdin);\
					fflush(stdout);\
					}
*/
typedef enum
{
	false,
	true
}bool;

#define Pressure_fun(pressure_state)	void Pr_##pressure_state()
#define Pressure(pressure_state)		Pr_##pressure_state

#define Al_fun(Main_state)				void Algoritma_##Main_state()
#define Al_d(Main_state)				Algoritma_##Main_state

#define Timer_define_f(Timer_ST)		void Timer_##Timer_ST()
#define Timer_define(Timer_ST)			Timer_##Timer_ST

#define Alarm_define_f(Alarm)			void Al_##Alarm()
#define Alarm_define(Alarm)				Al_##Alarm

void Send_pressure_value(unsigned int p);
void Timer_starting();
void Alarm_on_off_fun(bool alarm_state);

#endif /* STATE_H_ */
