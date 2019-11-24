#include "ESP-01_STM32.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>
#include "MQTTPacket.h"

UART_HandleTypeDef *uart_ESP01;

//Save Init ESP01
bool initESP01(UART_HandleTypeDef* huart) {
	uart_ESP01 = huart;
	
	//Local echo off
  sendCommand("ATE0\r\n");
  if (!waitForString("OK", 2, 1000)) {
    return false;
	}
	Rx[0] = 0;
	// Check TX,RX 
	sendCommand("AT\r\n");
  if (!waitForString("OK", 2, 1000)) {
    return false;
  }
	Rx[0] = 0;
	
	return true;
}

void sendCommand(char* buff) {
	while(__HAL_UART_GET_FLAG(&huart4,UART_FLAG_TC)==RESET){}
	HAL_UART_Transmit(&huart4, (uint8_t*) buff, strlen(buff),1000);
}

bool waitForString(char* input, int length, uint32_t timeout) {
	uint8_t index = 0;
		HAL_UART_Receive_DMA (&huart4, (uint8_t*) &Rx, 12);
	for(uint32_t i=0;i<strlen(Rx);i++){

		if(Rx[i] == input[index])
			index++;
		if(index==length)
			return true;
	}
	Rx[0] = 0;
	return false;
}

bool openTCPConnect(char* domain, uint16_t port) {
	char str[50];
	sprintf(str,"AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",domain,port);
	sendCommand(str);
	HAL_Delay(500);
	if(!waitForString("Linked",6,5000))
		return false;
	else
		return true;
}

bool connectWIFI(char* ssid, char* pw) {
	char str[64];

	sprintf(str,"AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,pw);
	
	//char test[] = "AT+CWJAP=\"N8NNY\",\"88888888\"\r\n";
	
	//char test1[] = "AT+CWMODE?\r\n";
	//char test2[] = "AT+CWJAP=\"NetworkLab\",\"NwLabOnly\"\r\n";
	//while(__HAL_UART_GET_FLAG(&huart4,UART_FLAG_TC)==RESET){}
	//HAL_UART_Transmit(&huart4, (uint8_t*) test, strlen(test),1000);
	sendCommand(str);
	HAL_Delay(3500);
	if(!waitForString("OK",2,10000))
		return false;
	else
		return true;
}

int sendData(char *buf, uint16_t blen) {
	char atcmd[64];
	sprintf(atcmd,"AT+CIPSEND=%d\r\n", blen);

	sendCommand(atcmd);
		// Connect Packet!
	
	HAL_Delay(100);

	//Send Packet
  //for(int i=0;i<blen;i++) 
	HAL_UART_Transmit_IT(&huart4, (uint8_t*) buf, blen);
	

	HAL_Delay(500);
  if (!waitForString("SEND", 4, 1000)) return 2;

  return 0;  
}




