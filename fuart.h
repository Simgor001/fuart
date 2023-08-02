/*-----------------------------------------------------------------------------------
*   格式化串口库  fuart.h
*   2023-8-1   Ver1.0.0
*   By Simgor001 https://blog.simgor.cn
*   Copyright (C) 2023 Simgor001
*------------------------------------------------------------------------------------
*   # 介绍
*   - 本库用于接入单片机的UART通信。
*------------------------------------------------------------------------------------
*   # 使用流程：
*   - 需要按照平台封装好UART相关的函数，并且传入初始化结构体，用于新建一个句柄
*------------------------------------------------------------------------------------
*   The MIT License (MIT)
*
*   Copyright (C) 2023 Simgor001
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*-----------------------------------------------------------------------------------*/
#ifndef _fuart_H_
#define _fuart_H_

#include "r_cg_macrodriver.h"

#define fuart_ERR -1
#define fuart_OK 0

/* 设备初始化结构体 */
typedef struct
{
    void (*Send)(uint8_t * const tx_buf, uint16_t tx_num); /**< 发送数据的函数指针 */
    uint8_t (*Receive)(); /**< 接收数据的函数指针 */
} fuart_InitTypeDef;

/* 设备句柄 */
typedef fuart_InitTypeDef * fuart_t;

/**
 * @brief 初始化fuart
 * 
 * @param fuart_InitStruct 初始化参数
 * @param fuart_h 存放的句柄地址
 * @return char 
 */
char fuart_Init(fuart_InitTypeDef* fuart_InitStruct, fuart_t * fuart_h);

/**
 * @brief 释放fuart
 * 
 * @param fuart_h 
 */
void fuart_DeInit(fuart_t fuart_h);

/**
 * @brief 发送字符串
 * 
 * @param fuart_h 句柄
 * @param format 格式化字符串
 * @param ... 可变参数
 * @return int 
 */
int fuart_printf(fuart_t fuart_h, const char *format, ...);

/**
 * @brief 接收字符串
 * 
 * @param fuart_h 句柄
 * @param format 格式化字符串
 * @param ... 可变参数
 * @return int 
 */
int fuart_scanf(fuart_t fuart_h, const char *format, ...);

#endif
