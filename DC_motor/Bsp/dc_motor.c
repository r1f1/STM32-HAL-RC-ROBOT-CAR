

/**
 ******************************************************************************
 * @file     dc_motor.h
 * @author   Rafael Hernández Marrero (rafaelh96@gmail.com)
 * @version  V1.0
 * @date     10/12/2023 10:18:40
 * @brief	 Functions definition available to the user for working with a 3V-12V DC motor over the L298N H Bridge
 ******************************************************************************
 */

#include "dc_motor.h"

extern TIM_HandleTypeDef htim2;

/*static void microDelay(uint32_t);
static void stepMotor(StepMot_HandleTypeDef, uint8_t);*/

/**
 * @fn StepMot_HandleTypeDef StepMot_create(uint16_t[], GPIO_TypeDef*[])
 * @brief Initialise the Stepper motor handler with the GPIO pins and GPIO ports configured by the user.
 * @param gpio_pin Array with the GPIO pins assigned in a 4-pin configuration.
 * @param gpio_port Array with the GPIO ports assigned in a 4-pin configuration.
 * @return StepMot_HandleTypeDef Stepper motor handler.
 */

DcMot_HandleTypeDef DcMot_create(DcMot_PinDef EN_pin, DcMot_PortDef EN_port, DcMot_PinDef IN1_pin, \
								 DcMot_PortDef IN1_port, DcMot_PinDef IN2_pin, DcMot_PortDef IN2_port){

	DcMot_HandleTypeDef DcMot;

	DcMot.gpio_pin_en = EN_pin;
	DcMot.gpio_port_en = EN_port;

	DcMot.gpio_pin_in1 = IN1_pin;
	DcMot.gpio_port_in1 = IN1_port;

	DcMot.gpio_pin_in2 = IN2_pin;
	DcMot.gpio_port_in2 = IN2_port;

	return DcMot;
}


/**
 * @fn void DcMot_SetDirection(DcMot_HandleTypeDef, DcMot_Direction)
 * @brief Set the direction of the motor.
 * @param DcMot DcMot_HandleTypeDef Dc motor handler.
 * @param Direction Motor move forward or reverse.
 */

void DcMot_SetDirection(DcMot_HandleTypeDef DcMot, DcMot_Direction Direction){

	if (Direction == FORWARD){

		HAL_GPIO_WritePin(DcMot.gpio_port_in1, DcMot.gpio_pin_in1, SET);
		HAL_GPIO_WritePin(DcMot.gpio_port_in2, DcMot.gpio_pin_in2, RESET);

	}else if (Direction == REVERSE){

		HAL_GPIO_WritePin(DcMot.gpio_port_in1, DcMot.gpio_pin_in1, RESET);
		HAL_GPIO_WritePin(DcMot.gpio_port_in2, DcMot.gpio_pin_in2, SET);
	}

}

/**
 * @fn void DcMot_SetSpeed(uin32_t)
 * @brief Set speed.
 * @param speed Values from 0 to 100.
 */

void DcMot_SetSpeed(uint32_t speed){

	uint32_t pulse_value = ((htim2.Init.Period + 1) / 100) * speed;

	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pulse_value);
}
