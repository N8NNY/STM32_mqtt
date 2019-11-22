#ifndef ESP_01_STM32_H
#define ESP_01_STM32_H
#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef *uart_ESP01;

//Save UART Object
bool initESP01(UART_HandleTypeDef*);
//Send AT Command
void sendCommand(char* buff);
//ConnectWIFI
bool connectWIFI(char* ssid, char* pw);
//Establishes TCP Connection
bool openTCPConnect(char* domain, uint16_t port);
//Send Message
int sendData(char *buf, int blen);
//Wait for specific input string until timeout runs out
bool waitForString(char* input, int length, unsigned int timeout);
#endif /* ESP-01_STM32_H */
