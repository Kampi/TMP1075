 /*
 * tmp1075.cpp
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

#include "../include/tmp1075.h"

#define TMP1075_REG_TEMP                      	0x00
#define TMP1075_REG_CFGR                 	    0x01
#define TMP1075_REG_LLIM                       	0x02
#define TMP1075_REG_HLIM                        0x03
#define TMP1075_REG_DIEID                     	0x0F

#define TMP1075_BIT_SD				            (0x01 << 0x00)
#define TMP1075_BIT_OS                          (0x01 << 0x07)

#define TMP1075_DEV_ID                         	0x7500

/** @brief          Modify the content of a given register.
 *  @param Register Register address
 *  @param Mask     Bit mask for the bits to modify
 *  @param Value    New value
 *  @return         TMP1075_ERR_OK when no error occurs
 */
static int32_t TMP1075_ModifyRegister(TMP1075_t* p_Device, uint8_t Register, uint8_t Mask, uint8_t Value)
{
    uint8_t Temp;

    if(!p_Device->Internal.isInitialized)
    {
        return TMP1075_ERR_NOT_INITIALIZED;
    }

    if(p_Device->I2C.I2C_Read(Register, &Temp, 1, &p_Device->I2C.I2C_Address) != 0)
    {
        return TMP1075_ERR_INVALID_RESPONSE;
    }

    Temp &= ~Mask;
    Temp |= Value;

    if(p_Device->I2C.I2C_Write(Register, &Temp, 1, &p_Device->I2C.I2C_Address) != 0)
    {
        return TMP1075_ERR_INVALID_RESPONSE;
    }

    return TMP1075_ERR_OK;
}

int32_t TMP1075_Init(TMP1075_t* p_Device)
{
    uint8_t Temp[2];

    if((p_Device->I2C.I2C_Read == NULL) || (p_Device->I2C.I2C_Write == NULL) || (p_Device->Delay == NULL) || (p_Device->I2C.I2C_Address == 0))
    {
        return TMP1075_ERR_INVALID_ARG;
    }
    else if(p_Device->Internal.isInitialized)
    {
        return TMP1075_ERR_OK;
    }

    if(p_Device->I2C.I2C_Read(TMP1075_REG_DIEID, Temp, 2, &p_Device->I2C.I2C_Address) != 0)
    {
        return TMP1075_ERR_INVALID_RESPONSE;
    }

    p_Device->ID = (((uint16_t)Temp[0]) << 8) | Temp[1];
    if(p_Device->ID != TMP1075_DEV_ID)
    {
        return TMP1075_ERR_NO_DEVICE;
    }

    if(p_Device->I2C.I2C_Read(TMP1075_REG_CFGR, Temp, 2, &p_Device->I2C.I2C_Address) != 0)
    {
        return TMP1075_ERR_INVALID_RESPONSE;
    }

    Temp[0] = TMP1075_BIT_SD;
    if(p_Device->I2C.I2C_Write(TMP1075_REG_CFGR, Temp, 2, &p_Device->I2C.I2C_Address) != 0)
    {
        return TMP1075_ERR_INVALID_RESPONSE;
    }

    p_Device->Internal.isShutdown = 1;
    p_Device->Internal.isInitialized = 1;

    return TMP1075_ERR_OK;
}

int32_t TMP1075_OneShot(TMP1075_t* p_Device, int8_t* p_Temperature, int8_t* p_Decimal)
{
    if(p_Temperature == NULL)
    {
        return TMP1075_ERR_INVALID_ARG;
    }
    else if(!p_Device->Internal.isShutdown)
    {
        return TMP1075_ERR_INVALID_MODE;
    }

    TMP1075_ERROR_CHECK(TMP1075_ModifyRegister(p_Device, TMP1075_REG_CFGR, TMP1075_BIT_OS, TMP1075_BIT_OS));

    p_Device->Delay(35, &p_Device->I2C.I2C_Address);

    return TMP1075_ReadResult(p_Device, p_Temperature, p_Decimal);
}

int32_t TMP1075_StartContinuous(TMP1075_t* p_Device, TMP1075_Rate_t Rate)
{
    TMP1075_ERROR_CHECK(TMP1075_ModifyRegister(p_Device, TMP1075_REG_CFGR, TMP1075_BIT_SD, 0));

    p_Device->Internal.isShutdown = false;

    return TMP1075_ERR_OK;
}

int32_t TMP1075_EnableShutdown(TMP1075_t* p_Device)
{
    TMP1075_ERROR_CHECK(TMP1075_ModifyRegister(p_Device, TMP1075_REG_CFGR, TMP1075_BIT_SD, TMP1075_BIT_SD));

    p_Device->Internal.isShutdown = true;

    return TMP1075_ERR_OK;
}

int32_t TMP1075_ReadResult(TMP1075_t* p_Device, int8_t* p_Temperature, int8_t* p_Decimal)
{
    uint8_t Temp[2];
    int16_t Temperature;

    if(p_Temperature == NULL)
    {
        return TMP1075_ERR_INVALID_ARG;
    }
    else if(!p_Device->Internal.isInitialized)
    {
        return TMP1075_ERR_NOT_INITIALIZED;
    }

    if(p_Device->I2C.I2C_Read(TMP1075_REG_TEMP, Temp, 2, &p_Device->I2C.I2C_Address) != 0)
    {
        return TMP1075_ERR_INVALID_RESPONSE;
    }

    Temperature = (((int16_t)Temp[0]) << 8) | Temp[1];
    Temperature >>= 4;

    if(Temperature & (0x01 << 12))
    {
        Temperature = ~Temperature;
        Temperature++;
    }

    *p_Temperature = Temperature >> 4;

    if(p_Decimal != NULL)
    {
        *p_Decimal = Temperature & 0x0F;
    }

    return TMP1075_ERR_OK;
}
