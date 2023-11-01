 /*
 * tmp1075.h
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

#ifndef TMP1075_H_
#define TMP1075_H_

#include "tmp1075_defs.h"
#include "tmp1075_errors.h"

/** @brief          Initialize a TMP1075 device.
 *  @param p_Device Device instance
 *  @return         TMP1075_ERR_OK when no error occurs
 */
int32_t TMP1075_Init(TMP1075_t* p_Device);

/** @brief                  Perform a one shot temperature measurement.
 *  @param p_Device         Device instance
 *  @param p_Temperature    Pointer to temperature data
 *  @param p_Decimal        (Optional) Decimal temperature data
 *  @return                 TMP1075_ERR_OK when no error occurs
 */
int32_t TMP1075_OneShot(TMP1075_t* p_Device, int8_t* p_Temperature, int8_t* p_Decimal);

/** @brief          Put the device from shutdown into continuous mode and enabled the measuring.
 *  @param p_Device Device instance
 *  @param Rate     Measurement rate
 *  @return         TMP1075_ERR_OK when no error occurs
 */
int32_t TMP1075_StartContinuous(TMP1075_t* p_Device, TMP1075_Rate_t Rate);

/** @brief          Put the device into shutdown mode.
 *  @param p_Device Device instance
 *  @return         TMP1075_ERR_OK when no error occurs
 */
int32_t TMP1075_EnableShutdown(TMP1075_t* p_Device);

/** @brief                  Read a measurement result from the device.
 *  @param p_Device         Device instance
 *  @param p_Temperature    Pointer to temperature data
 *  @param p_Decimal        (Optional) Decimal temperature data
 *  @return                 TMP1075_ERR_OK when no error occurs
 */
int32_t TMP1075_ReadResult(TMP1075_t* p_Device, int8_t* p_Temperature, int8_t* p_Decimal);

#endif /* TMP1075_H_ */
