/*-----------------------------------------------------------------------------------
*   格式化串口库  fuart.c
*   2023-8-1   Ver1.0.0
*   By Simgor001 https://blog.simgor.cn
*-----------------------------------------------------------------------------------*/
#include "fuart.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief 初始化fuart
 * 
 * @param fuart_InitStruct 初始化参数
 * @param fuart_h 存放的句柄地址
 * @return char 
 */
char fuart_Init(fuart_InitTypeDef* fuart_InitStruct, fuart_t * fuart_h)
{
    *fuart_h = (fuart_t)malloc(sizeof(fuart_InitTypeDef));
    memcpy(*fuart_h, fuart_InitStruct, sizeof(fuart_InitTypeDef));
    return fuart_OK; // 初始化成功
}

/**
 * @brief 释放fuart
 * 
 * @param fuart_h 
 */
void fuart_DeInit(fuart_t fuart_h)
{
    free(fuart_h);
}

/**
 * @brief 发送字符串
 * 
 * @param fuart_h 句柄
 * @param format 格式化字符串
 * @param ... 可变参数
 * @return int 
 */
int fuart_printf(fuart_t fuart_h, const char *format, ...)
{
    va_list args;
    char buf[256];

    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);

    fuart_h->Send((uint8_t*)buf, strlen(buf));

    return strlen(buf);
}

/**
 * @brief 接收字符串
 * 
 * @param fuart_h 句柄
 * @param format 格式化字符串
 * @param ... 可变参数
 * @return int 
 */
int fuart_scanf(fuart_t fuart_h, const char *format, ...)
{
    va_list args;
    char buf[256];
    int pos = 0;

    uint8_t c = 0;
    memset(buf, 0, sizeof(buf));

    for (; pos < 256; ++pos)
    {
        c = fuart_h->Receive();
        
        if (c != '\n')
            buf[pos] = c;
        else
            break;        
    }
    
    va_start(args, format);
    vsscanf(buf, format, args);
    va_end(args);

    return strlen(buf);
}
