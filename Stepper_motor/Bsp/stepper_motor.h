
/**
 ******************************************************************************
 * @file     Stepper_motor.h
 * @author   Rafael Hernández Marrero (rafaelh96@gmail.com)
 * @version  V1.0
 * @date     10/12/2023 10:18:40
 * @brief	 Functions declarations available to the user for working with the Stepper motor 28BYJ-48 over the
 * motor driver ULN2003
 ******************************************************************************
 */

#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

//**************************************** Stepper Motor types ******************************************//

#define StepMot_PinDef 					uint16_t
#define StepMot_PortDef 				GPIO_TypeDef*


//******************************************** Helper Macros ********************************************//

#define PIN_CONFIGURATION_4				0x4

typedef enum{
	COUNTER_CLOCKWISE,
	CLOCKWISE
}StepMot_Direction;

/**
 * @struct StepMot_HandleTypeDef stepper_motor.h "stepper_motor.h"
 * @brief Store GPIO pins and ports in their corresponding struct member.
 *
 */
typedef struct{

	StepMot_PinDef gpio_pin[PIN_CONFIGURATION_4];
	StepMot_PortDef gpio_port[PIN_CONFIGURATION_4];

	uint32_t steps_per_rev;

}StepMot_HandleTypeDef;


//************************************** Function declarations **************************************//


StepMot_HandleTypeDef StepMot_create(uint32_t, StepMot_PinDef [], StepMot_PortDef []);
void StepMot_Steps(StepMot_HandleTypeDef, uint32_t, uint32_t, StepMot_Direction);

#endif /* STEPPER_MOTOR_H_ */
