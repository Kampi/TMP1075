 /*
 * tmp1075_defs.h
 *
 *  Copyright (C) Daniel Kampert, 2023
 *  Website: www.kampis-elektroecke.de
 *  File info: Texas Instruments TMP1075 driver.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Errors and commissions should be reported to DanielKampert@kampis-elektroecke.de
 */

#ifndef TMP1075_DEFS_H_
#define TMP1075_DEFS_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/** @brief              I2C master write function definition.
 *  @param RegAddr      Device address
 *  @param p_Data       Pointer to data buffer
 *  @param Length       Data length
 *  @param p_Instance   Pointer to interface instance
 *  @return             Status code
 */
typedef int32_t (*TMP1075_Write_t)(uint8_t RegAddr, const uint8_t* p_Data, uint8_t Length, const void* p_Instance);

/** @brief              I2C master read function definition.
 *  @param RegAddr      Device address
 *  @param p_Data       Pointer to data buffer
 *  @param Length       Data length
 *  @param p_Instance   Pointer to interface instance
 *  @return             Status code
 */
typedef int32_t (*TMP10755_Read_t)(uint8_t RegAddr, uint8_t* p_Data, uint8_t Length, const void* p_Instance);

/** @brief              Delay function definition.
 *  @param Delay        Delay time in ms
 *  @param p_Instance   Pointer to interface instance
 *  @return             Status code
 */
typedef void (*TMP10755_Delay_t)(uint8_t Delay, const void* p_Instance);

/** @brief TMP1075 conversion rate settings definition for continuous mode.
 */
typedef enum
{
    TMP1075_RATE_275    = 0,                                	/**< 27.5 ms (default). */
    TMP1075_RATE_55,                                       	    /**< 55 ms. */
    TMP1075_RATE_110,                                       	/**< 110 msg. */
    TMP1075_RATE_220,                                      	    /**< 220 ms (fixed 35 ms and default when using TMP1075N). */
} TMP1075_Rate_t;

/** @brief TMP1075 device object definition.
 */
typedef struct
{
    uint16_t ID;                                             	/**< Device ID. */
    TMP10755_Delay_t Delay;                                     /**< Platform specific delay function. */
    struct
    {
        TMP1075_Write_t I2C_Write;                              /**< Platform specific I2C write function. */
        TMP10755_Read_t I2C_Read;                               /**< Platform specific I2C read function. */
        uint8_t I2C_Address;                                	/**< I2C address of the device. */
    } I2C;
    struct
    {
        uint8_t isInitialized;					                /**< Device initialization status. */
        uint8_t isShutdown;					                    /**< Device shutdown status. */
    } Internal;
} TMP1075_t;

#endif /* TMP1075_DEFS_H_ */
