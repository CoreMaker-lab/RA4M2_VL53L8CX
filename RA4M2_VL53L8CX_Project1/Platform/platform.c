/**
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


#include "platform.h"
#include <string.h>


#include "r_sci_i2c.h"
extern sci_i2c_instance_ctrl_t g_i2c2_ctrl;
extern uint32_t  timeout_ms;
extern  i2c_master_event_t i2c_event;



uint8_t VL53L8CX_RdByte(
		VL53L8CX_Platform *p_platform,
		uint16_t RegisterAdress,
		uint8_t *p_value)
{
	uint8_t status = 255;
	
	/* Need to be implemented by customer. This function returns 0 if OK */

    uint8_t data_write[2];
    uint8_t data_read[1];

    data_write[0] = (RegisterAdress >> 8) & 0xFF;
    data_write[1] = RegisterAdress & 0xFF;
    //  status = HAL_I2C_Master_Transmit(&hi2c1, dev, data_write, 2, 100);

    status = R_SCI_I2C_Write(&g_i2c2_ctrl, data_write, 2, true);
    assert(FSP_SUCCESS == status);
    /* Since there is nothing else to do, block until Callback triggers*/
    //while ((I2C_MASTER_EVENT_TX_COMPLETE != i2c_event) && timeout_ms)
    while ((I2C_MASTER_EVENT_TX_COMPLETE != i2c_event) && timeout_ms > 0)
    {
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout_ms--;
    }
    if (I2C_MASTER_EVENT_ABORTED == i2c_event)
    {
        __BKPT(0);
    }
    /* Read data back from the I2C slave */
    i2c_event = I2C_MASTER_EVENT_ABORTED;
    timeout_ms = 1000000;
    //  status = HAL_I2C_Master_Receive(&hi2c1, dev, data_read, 1, 100);

    status = R_SCI_I2C_Read(&g_i2c2_ctrl, data_read, 1, false);
    assert(FSP_SUCCESS == status);
    while ((I2C_MASTER_EVENT_RX_COMPLETE != i2c_event) && timeout_ms)
    {
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MILLISECONDS);
        timeout_ms--;
    }
    if (I2C_MASTER_EVENT_ABORTED == i2c_event)
    {
        __BKPT(0);
    }

    i2c_event = I2C_MASTER_EVENT_ABORTED;
    timeout_ms = 1000000;


    *p_value = data_read[0];



	return status;
}

uint8_t VL53L8CX_WrByte(
		VL53L8CX_Platform *p_platform,
		uint16_t RegisterAdress,
		uint8_t value)
{
	uint8_t status = 255;

	/* Need to be implemented by customer. This function returns 0 if OK */

    uint8_t data_write[3];

    data_write[0] = (RegisterAdress >> 8) & 0xFF;
    data_write[1] = RegisterAdress & 0xFF;
    data_write[2] = value & 0xFF;
    //  status = HAL_I2C_Master_Transmit(&hi2c1, dev, data_write, 3, 100);

    status = R_SCI_I2C_Write(&g_i2c2_ctrl, data_write, 3, false);
    assert(FSP_SUCCESS == status);
    /* Since there is nothing else to do, block until Callback triggers*/
    //while ((I2C_MASTER_EVENT_TX_COMPLETE != i2c_event) && timeout_ms)
    while ((I2C_MASTER_EVENT_TX_COMPLETE != i2c_event) && timeout_ms > 0)
    {
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout_ms--;
    }
    if (I2C_MASTER_EVENT_ABORTED == i2c_event)
    {
        __BKPT(0);
    }
    /* Read data back from the I2C slave */
    i2c_event = I2C_MASTER_EVENT_ABORTED;
    timeout_ms = 1000000;



	return status;
}

uint8_t VL53L8CX_WrMulti(
		VL53L8CX_Platform *p_platform,
		uint16_t RegisterAdress,
		uint8_t *p_values,
		uint32_t size)
{
	uint8_t status = 255;
	
		/* Need to be implemented by customer. This function returns 0 if OK */

    uint8_t data_write[2 + size];

    data_write[0] = (RegisterAdress >> 8) & 0xFF;  // 寄存器高8位
    data_write[1] = RegisterAdress & 0xFF;         // 寄存器低8位

    memcpy(&data_write[2], p_values, size);        // 复制数据到缓冲区

    /* 向I²C设备写入寄存器地址和数据 */
    status = R_SCI_I2C_Write(&g_i2c2_ctrl, data_write, (uint32_t)(2 + size), true);
    assert(FSP_SUCCESS == status);

    /* 等待I²C发送完成事件 */
    i2c_event = I2C_MASTER_EVENT_ABORTED;
    timeout_ms = 1000000;
    while ((I2C_MASTER_EVENT_TX_COMPLETE != i2c_event) && timeout_ms > 0)
    {
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout_ms--;
    }

    if (I2C_MASTER_EVENT_ABORTED == i2c_event)
    {
        __BKPT(0);
        return 255;  // 通信失败
    }


//	   uint8_t addr_buffer[2];
//
//	    // 发送寄存器地址，不发送STOP条件
//	    addr_buffer[0] = (RegisterAdress >> 8) & 0xFF;
//	    addr_buffer[1] = RegisterAdress & 0xFF;
//        // 等待地址发送完成
//        i2c_event = I2C_MASTER_EVENT_ABORTED;
//        timeout_ms = 1000000;
//	    status = R_SCI_I2C_Write(&g_i2c2_ctrl, addr_buffer, 2, false);
//	    if(status != FSP_SUCCESS) return 255;
//
//
//	    while ((i2c_event != I2C_MASTER_EVENT_TX_COMPLETE) && timeout_ms--)
//	    {
//	        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
//	    }
//	    if(i2c_event == I2C_MASTER_EVENT_ABORTED) return 255;
//
//	    // 逐字节发送数据
//	    for(uint32_t i = 0; i < size; i++)
//	    {
//            // 等待当前字节发送完成
//            i2c_event = I2C_MASTER_EVENT_ABORTED;
//            timeout_ms = 1000000;
//
//            bool restart;
//	        // 最后一个字节发送后发送STOP条件
//            if(i == (size - 1))
//                restart=false;
//            else
//                restart=true;
//
//	        status = R_SCI_I2C_Write(&g_i2c2_ctrl, &p_values[i], 1, restart);
//	        if(status != FSP_SUCCESS) return 255;
//
//
//	        while ((i2c_event != I2C_MASTER_EVENT_TX_COMPLETE) && timeout_ms--)
//	        {
//	            R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
//	        }
//	        if(i2c_event == I2C_MASTER_EVENT_ABORTED) return 255;
//	    }



    /* Read data back from the I2C slave */
    i2c_event = I2C_MASTER_EVENT_ABORTED;
    timeout_ms = 1000000;


	return status;
}

uint8_t VL53L8CX_RdMulti(
		VL53L8CX_Platform *p_platform,
		uint16_t RegisterAdress,
		uint8_t *p_values,
		uint32_t size)
{
	uint8_t status = 255;
	
	/* Need to be implemented by customer. This function returns 0 if OK */
	
    uint8_t data_write[2];

    data_write[0] = (RegisterAdress >> 8) & 0xFF;  // 寄存器高8位
    data_write[1] = RegisterAdress & 0xFF;         // 寄存器低8位

    /* 写入寄存器地址（但不停止I²C总线）*/
    status = R_SCI_I2C_Write(&g_i2c2_ctrl, data_write, 2, false);
    assert(FSP_SUCCESS == status);


    /* 等待地址写入完成 */
    i2c_event = I2C_MASTER_EVENT_ABORTED;
    timeout_ms = 1000000;
    while ((I2C_MASTER_EVENT_TX_COMPLETE != i2c_event) && timeout_ms > 0)
    {
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout_ms--;
    }

    if (I2C_MASTER_EVENT_ABORTED == i2c_event)
    {
        __BKPT(0);
        return 255;  // 地址写入失败
    }

    /* 读取数据 */
    status = R_SCI_I2C_Read(&g_i2c2_ctrl, p_values, size, true);
    assert(FSP_SUCCESS == status);

    /* 等待数据读取完成 */
    i2c_event = I2C_MASTER_EVENT_ABORTED;
    timeout_ms = 1000000;
    while ((I2C_MASTER_EVENT_RX_COMPLETE != i2c_event) && timeout_ms > 0)
    {
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout_ms--;
    }

    if (I2C_MASTER_EVENT_ABORTED == i2c_event)
    {
        __BKPT(0);
        return 255;  // 数据读取失败
    }

//    /* 第一步：发送寄存器地址，不发送STOP条件 */
//    uint8_t addr_buffer[2];
//    addr_buffer[0] = (RegisterAdress >> 8) & 0xFF;
//    addr_buffer[1] = RegisterAdress & 0xFF;
//
//    status = R_SCI_I2C_Write(&g_i2c2_ctrl, addr_buffer, 2, false);
//    if(status != FSP_SUCCESS) return 255;
//
//    /* 等待地址发送完成 */
//    i2c_event = I2C_MASTER_EVENT_ABORTED;
//    timeout_ms = 1000000;
//    while ((i2c_event != I2C_MASTER_EVENT_TX_COMPLETE) && timeout_ms--)
//    {
//        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
//    }
//    if(i2c_event == I2C_MASTER_EVENT_ABORTED) return 255;
//
//    /* 第二步：开始读取数据，并发送STOP条件 */
//    status = R_SCI_I2C_Read(&g_i2c2_ctrl, p_values, size, true);
//    if(status != FSP_SUCCESS) return 255;
//
//    /* 等待数据读取完成 */
//    i2c_event = I2C_MASTER_EVENT_ABORTED;
//    timeout_ms = 1000000;
//    while ((i2c_event != I2C_MASTER_EVENT_RX_COMPLETE) && timeout_ms--)
//    {
//        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
//    }
//    if(i2c_event == I2C_MASTER_EVENT_ABORTED) return 255;

    /* Read data back from the I2C slave */
    i2c_event = I2C_MASTER_EVENT_ABORTED;
    timeout_ms = 1000000;

	return status;
}

uint8_t VL53L8CX_Reset_Sensor(
		VL53L8CX_Platform *p_platform)
{
	uint8_t status = 0;
	
	/* (Optional) Need to be implemented by customer. This function returns 0 if OK */
	
	/* Set pin LPN to LOW */
	/* Set pin AVDD to LOW */
	/* Set pin VDDIO  to LOW */
	/* Set pin CORE_1V8 to LOW */
	VL53L8CX_WaitMs(p_platform, 100);

	/* Set pin LPN to HIGH */
	/* Set pin AVDD to HIGH */
	/* Set pin VDDIO to HIGH */
	/* Set pin CORE_1V8 to HIGH */
	VL53L8CX_WaitMs(p_platform, 100);

	return status;
}

void VL53L8CX_SwapBuffer(
		uint8_t 		*buffer,
		uint16_t 	 	 size)
{
	uint32_t i, tmp;
	
	/* Example of possible implementation using <string.h> */
	for(i = 0; i < size; i = i + 4) 
	{
		tmp = (
		  buffer[i]<<24)
		|(buffer[i+1]<<16)
		|(buffer[i+2]<<8)
		|(buffer[i+3]);
		
		memcpy(&(buffer[i]), &tmp, 4);
	}
}	

uint8_t VL53L8CX_WaitMs(
		VL53L8CX_Platform *p_platform,
		uint32_t TimeMs)
{
	uint8_t status = 0;

	/* Need to be implemented by customer. This function returns 0 if OK */
    R_BSP_SoftwareDelay(TimeMs, BSP_DELAY_UNITS_MILLISECONDS);
	
	return status;
}
