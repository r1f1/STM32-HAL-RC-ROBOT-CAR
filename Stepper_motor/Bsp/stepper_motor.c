

/**
 ******************************************************************************
 * @file     Stepper_motor.h
 * @author   Rafael Hernández Marrero (rafaelh96@gmail.com)
 * @version  V1.0
 * @date     10/12/2023 10:18:40
 * @brief	 Functions definitions available to the user for working with the Stepper motor 28BYJ-48 over the
 * motor driver ULN2003
 ******************************************************************************
 */

#include "stepper_motor.h"

extern TIM_HandleTypeDef htim6;

static void microDelay(uint32_t);
static void stepMotor(StepMot_HandleTypeDef, uint8_t);

/**
 * @fn StepMot_HandleTypeDef StepMot_create(uint16_t[], GPIO_TypeDef*[])
 * @brief Initialise the Stepper motor handler with the GPIO pins and GPIO ports configured by the user.
 * @param gpio_pin Array with the GPIO pins assigned in a 4-pin configuration.
 * @param gpio_port Array with the GPIO ports assigned in a 4-pin configuration.
 * @return StepMot_HandleTypeDef Stepper motor handler.
 */

StepMot_HandleTypeDef StepMot_create(uint32_t steps_per_rev, StepMot_PinDef gpio_pin[], StepMot_PortDef gpio_port[]){

	StepMot_HandleTypeDef StepMot;

	for (int8_t i = 0; i < PIN_CONFIGURATION_4; i++){

		StepMot.gpio_pin[i] = gpio_pin[i];
		StepMot.gpio_port[i] = gpio_port[i];

	}

	StepMot.steps_per_rev = steps_per_rev;

	return StepMot;
}

static void microDelay (uint32_t delay){

	while (delay){
	  if(__HAL_TIM_GET_FLAG(&htim6, TIM_FLAG_UPDATE)){
		  __HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);
		  delay--;
	  }
	}
}

void StepMot_Steps(StepMot_HandleTypeDef StepMot, uint32_t Steps, uint32_t Speed, StepMot_Direction Direction){

	uint32_t delay;
	delay = 60000000UL / (StepMot.steps_per_rev * Speed);

	uint32_t step_number = 0;

	// decrement the number of steps, moving one step each time:
	while (Steps > 0){
		microDelay(delay);

		if (Direction == CLOCKWISE){
			step_number++;
			if (step_number == StepMot.steps_per_rev) {
			  step_number = 0;
			}

		}else if (Direction == COUNTER_CLOCKWISE){
			if (step_number == 0) {
			  step_number = StepMot.steps_per_rev;
			}
			step_number--;
		}

		Steps--;
		stepMotor(StepMot, (step_number % 4));
	}

}

static void stepMotor(StepMot_HandleTypeDef StepMot, uint8_t command){
	switch (command) {
		case 0: // 1010
			HAL_GPIO_WritePin(StepMot.gpio_port[0], StepMot.gpio_pin[0], GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMot.gpio_port[1], StepMot.gpio_pin[1], GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMot.gpio_port[2], StepMot.gpio_pin[2], GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMot.gpio_port[3], StepMot.gpio_pin[3], GPIO_PIN_RESET);
			break;
		case 1: // 0110
			HAL_GPIO_WritePin(StepMot.gpio_port[0], StepMot.gpio_pin[0], GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMot.gpio_port[1], StepMot.gpio_pin[1], GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMot.gpio_port[2], StepMot.gpio_pin[2], GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMot.gpio_port[3], StepMot.gpio_pin[3], GPIO_PIN_RESET);
			break;
		case 2: //0101
			HAL_GPIO_WritePin(StepMot.gpio_port[0], StepMot.gpio_pin[0], GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMot.gpio_port[1], StepMot.gpio_pin[1], GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMot.gpio_port[2], StepMot.gpio_pin[2], GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMot.gpio_port[3], StepMot.gpio_pin[3], GPIO_PIN_SET);
			break;
		case 3: //1001
			HAL_GPIO_WritePin(StepMot.gpio_port[0], StepMot.gpio_pin[0], GPIO_PIN_SET);
			HAL_GPIO_WritePin(StepMot.gpio_port[1], StepMot.gpio_pin[1], GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMot.gpio_port[2], StepMot.gpio_pin[2], GPIO_PIN_RESET);
			HAL_GPIO_WritePin(StepMot.gpio_port[3], StepMot.gpio_pin[3], GPIO_PIN_SET);
			break;
	}
}


