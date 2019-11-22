#include "ESP-01_STM32.h"
#include "usart.h"

UART_HandleTypeDef *uart_ESP01;

//Save Init ESP01
bool initESP01(UART_HandleTypeDef* huart) {
	uart_ESP01 = huart;
	
	// Check TX,RX 
	sendCommand("AT\r\n");
  if (!waitForString("OK", 2, 1000)) {
    return false;
  }
	
		//Local echo off
  sendCommand("ATE0\n\r");
  if (!waitForString("OK", 2, 1000)) {
    return false;
	}
	
	return true;
}

void sendCommand(char* buff) {
	HAL_UART_Transmit(&huart4, (uint8_t*) buff, strlen(buff),600);
}

bool waitForString(char* input, int length, uint32_t timeout) {
	char ch1[15];
	uint8_t index = 0;
	HAL_UART_Receive(&huart4, (uint8_t*) &ch1, 15, 600);
	for(int i = 0;i<strlen(ch1);i++) {
		if(ch1[i] == input[index]){
			index++;
		}
		if(index==length) return true;
	}
	return false;
}

bool openTCPConnect(char* domain, uint16_t port) {
	char str[50];
	sprintf(str,"AT+CIPSTART=\"%s\",%d/r/n",domain,port);
	sendCommand(str);
	if(!waitForString("Linked",6,5000))
		return false;
	else
		return true;
}

bool connectWIFI(char* ssid, char* pw) {
	char str[100];
	sprintf(str,"AT+CIPSTART=\"TCP\"\"%s\",\"%s\"/r/n",ssid,pw);
	sendCommand(str);
	if(!waitForString("Linked",6,5000))
		return false;
	else
		return true;
}

int sendData(char *buf, int blen) {
	char atcmd[64];
	sprintf(atcmd,"AT+CIPSEND=%d", blen);
	if (!waitForString(">", 1, 1000)) return 1;
	
	//Send Packet
  for(int i=0;i<blen;i++) HAL_UART_Transmit(&huart4, (uint8_t*) buf[i], 1, 300);
  if (!waitForString("SEND OK", 7, 1000)) return 2;

  return 0;  
}



