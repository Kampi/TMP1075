 /*
 * tmp1075_errors.h
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

#ifndef TMP1075_ERRORS_H_
#define TMP1075_ERRORS_H_

/** @brief
 */
#define TMP1075_ERR_OK				                            0

/** @brief
 */
#define TMP1075_ERR_INVALID_ARG			                        -1

/** @brief
 */
#define TMP1075_ERR_INVALID_RESPONSE		                    -2

/** @brief
 */
#define TMP1075_ERR_NO_DEVICE			                        -3

/** @brief
 */
#define TMP1075_ERR_NOT_INITIALIZED		                        -4

/** @brief
 */
#define TMP1075_ERR_INVALID_MODE                                -5

/** @brief      Generic error check macro.
 *  @param Func Function that should be checked
 */
#define TMP1075_ERROR_CHECK(Func)                               do                                      \
                                                                {                                       \
                                                                    int32_t Error = Func;               \
                                                                    if(Error != TMP1075_ERR_OK)         \
                                                                    {                                   \
                                                                        return Error;                   \
                                                                    }                                   \
                                                                } while(0);

#endif /* TMP1075_ERRORS_H_ */
