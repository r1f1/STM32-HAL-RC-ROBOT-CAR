/**
 ******************************************************************************
 * @file     dc_motor.h
 * @author   Rafael Hernández Marrero (rafaelh96@gmail.com)
 * @version  V1.0
 * @date     10/12/2023 10:18:40
 * @brief	 Functions declarations available to the user for working with a 3V-12V DC motor over the L298N H Bridge
 ******************************************************************************
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_


#include <stdint.h>
#include "stm32f4xx_hal.h"

//**************************************** DC Motor types ******************************************//

#define DcMot_PinDef 					uint16_t
#define DcMot_PortDef 				GPIO_TypeDef*


//******************************************** Helper Macros ********************************************//

typedef enum{
	FORWARD,
	REVERSE
}DcMot_Direction;

/**
 * @struct DcMot_HandleTypeDef dc_motor.h "dc_motor.h"
 * @brief Store GPIO pins and ports in their corresponding struct member.
 *
 */
typedef struct{

	DcMot_PinDef gpio_pin_en;
	DcMot_PortDef gpio_port_en;

	DcMot_PinDef gpio_pin_in1;
	DcMot_PortDef gpio_port_in1;

	DcMot_PinDef gpio_pin_in2;
	DcMot_PortDef gpio_port_in2;

}DcMot_HandleTypeDef;


//************************************** Function declarations **************************************//


DcMot_HandleTypeDef DcMot_create(DcMot_PinDef, DcMot_PortDef, DcMot_PinDef, DcMot_PortDef, DcMot_PinDef, DcMot_PortDef);
void DcMot_SetDirection(DcMot_HandleTypeDef, DcMot_Direction);
void DcMot_SetSpeed(uint32_t);

#endif /* DC_MOTOR_H_ */
