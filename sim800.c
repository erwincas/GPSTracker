#include "sim800.h"

void makeGPRSConnection(void){
     EUSART_PrintLn("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
    __delay_ms(3000);
    EUSART_PrintLn("AT+SAPBR=3,1,\"APN\",\"Internet\"");
    __delay_ms(3000);
    EUSART_PrintLn("AT+SAPBR=1,1");
    __delay_ms(3000);
}

void getBatteryLevel(char * batBuf){
    EUSART_PrintLn("AT+CBC");
    EUSART_ReadLn(batBuf);
}

void makeHTTPRequest(char * lat, char * lon){
    EUSART_PrintLn("AT+HTTPINIT");
    __delay_ms(3000);
    EUSART_Print("AT+HTTPPARA=\"URL\",\"http://api.erwincastricum.nl/test.php?lat=");
    EUSART_Print(lat);
    EUSART_Print("&lon=");
    EUSART_Print(lon);
    EUSART_PrintLn("\"");
    __delay_ms(2000);
    EUSART_PrintLn("AT+HTTPACTION=0");
    __delay_ms(6000);
    EUSART_PrintLn("AT+HTTPTERM");
    __delay_ms(2000);
}

void makeTestHTTPRequest(void){
    EUSART_PrintLn("AT+HTTPINIT");
    __delay_ms(3000);
    EUSART_PrintLn("AT+HTTPPARA=\"URL\",\"http://api.erwincastricum.nl/test.php?lat=10&lon=10\"");
    __delay_ms(2000);
    EUSART_PrintLn("AT+HTTPACTION=0");
    __delay_ms(6000);
    EUSART_PrintLn("AT+HTTPTERM");
    __delay_ms(2000);
}

void closeGPRSConnection(void){
    EUSART_PrintLn("AT+SAPBR=0,1");
    __delay_ms(2000);
}

void simSleep(void){
    EUSART_PrintLn("AT+CSCLK=2");
    
    //Wait until SIM800L Falls asleep
    __delay_ms(6000);
}

void simWakeUp(void){
    EUSART_PrintLn("AT");
    __delay_ms(1000);
    EUSART_PrintLn("AT+CSCLK=0");
    __delay_ms(1000);
}