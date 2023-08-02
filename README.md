# fuart库

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## 1. 介绍

fuart库用于接入单片机的UART通信。

使用时，需要按照平台封装好UART相关的函数，并且传入初始化结构体。

## 2. 授权

本软件遵循MIT开源协议。

## 3. 使用说明

根据所使用的平台，先封装好uart相关的函数（阻塞函数），
以RL78平台为例。
```c
extern volatile char uart0_tx_flag;
extern volatile char uart0_rx_flag;

void uart0_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    uint16_t len = strlen(tx_buf);
    uart0_tx_flag = R_UART0_Send((uint8_t *)tx_buf, len);
    while(uart0_tx_flag == 0);
}

uint8_t uart0_Receive()
{
    uint8_t buf;
    uart0_rx_flag = 0;
    uart0_rx_flag = R_UART0_Receive(&buf, 1);
    while(uart0_rx_flag == 0);
    return buf;
}
```

中断设置如下：
```c
volatile char uart0_tx_flag;
volatile char uart0_rx_flag;

static void r_uart0_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    uart0_tx_flag = 1;
    /* End user code. Do not edit comment generated here */
}

static void r_uart0_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    uart0_end_flag = 1;
    /* End user code. Do not edit comment generated here */
}
```

### 3.1 初始化

首先需要初始化FUART设备。这需要提供一个`fuart_InitTypeDef`类型的结构体，其中包含了设备的发送函数和接收函数。然后，调用`fuart_Init`函数进行初始化，并获取到一个设备句柄。

```c
fuart_InitTypeDef fuart_InitStruct;
fuart_t fuart;

fuart_InitStruct.Send = &uart0_Send; // 发送数据的函数指针
fuart_InitStruct.Receive = &uart0_Receive; // 接收数据的函数指针

fuart_Init(&fuart_InitStruct, &fuart);
```

### 3.2 发送字符串

使用`fuart_printf`函数发送字符串。可以使用格式化字符串和可变参数。

```c
int data = 114514;
fuart_printf(fuart, "data = %d!\r\n", buf); // 发送一个带有参数的字符串
```

### 3.3 接收字符串

使用`fuart_scanf`函数接收字符串。可以使用格式化字符串和可变参数。

```c
int buf = 0;
fuart_scanf(fuart, "%d", &buf); // 从串口接收一个整数
```

### 3.4 释放设备

最后，当我们不再需要使用FUART设备时，可以调用`fuart_DeInit`函数来释放设备句柄。

```c
fuart_DeInit(fuart);
```

## 4. 注意事项

在使用本库时，请确保你的平台上已经正确实现了UART通讯函数，并能够正常工作。
