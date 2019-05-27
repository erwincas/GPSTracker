#include "sim800.h"

char waitForResponse(void){
    char response;
    while(1){
        response = EUSART_Read();
        if(response == 'O'){
            if(EUSART_Read() == 'K') return 1;
        } else if(response == 'E'){
            if(EUSART_Read() == 'R') return 0;
        }
    }
}

char waitForConnection(void){
    int seconds = 0;
    
    EUSART_PrintLn("AT+CREG=1");
    waitForResponse();

    while(seconds < 10){
        EUSART_PrintLn("AT+CREG?");
        while(EUSART_Read() != ':'); 
        EUSART_Read(); //Skip 1 char
        if(EUSART_Read() == '1' || EUSART_Read() == '5'){
            return 1;
        }
        __delay_ms(1000);
        seconds++;
    }
    return 0;
}

char makeGPRSConnection(void){
     EUSART_PrintLn("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
    if(!waitForResponse()) return 0;
    EUSART_PrintLn("AT+SAPBR=3,1,\"APN\",\"Internet\"");
    if(!waitForResponse()) return 0;
    EUSART_PrintLn("AT+SAPBR=1,1");
    if(!waitForResponse()) return 0;
    __delay_ms(100);
    return 1;
}

void getBatteryLevel(char * batBuf){
    int i=0;
    EUSART_PrintLn("AT+CBC");
    while(EUSART_Read() != ',');
    do{
        batBuf[i] = EUSART_Read(); 
        i++;
    } while(batBuf[i-1] != ',');
    batBuf[i-1] = '\0';
}

void readHTTPRequest(char * RXBuffer){
    uint8_t i=0;
    EUSART_PrintLn("AT+HTTPREAD");
    while(EUSART_Read() != '\n'); //Skip the echo
    while(EUSART_Read() != '\n'); //Skip the length
    do{
        RXBuffer[i] = EUSART_Read();
        i++;
    }while(RXBuffer[i-1] != '\n');
    
    RXBuffer[i-1] = '\0';
}

void makeHTTPRequest(char * lat, char * lon, char * battery){  
    EUSART_PrintLn("AT+HTTPINIT");
    waitForResponse();
    EUSART_Print("AT+HTTPPARA=\"URL\",\"http://api.erwincastricum.nl/test.php?lat=");
    EUSART_Print(lat);
    EUSART_Print("&lon=");
    EUSART_Print(lon);
    EUSART_Print("&bat=");
    EUSART_Print(battery);
    EUSART_PrintLn("\"");
    waitForResponse();
    EUSART_PrintLn("AT+HTTPACTION=0");
    __delay_ms(3000);
    EUSART_PrintLn("AT+HTTPTERM");
    waitForResponse();
}

void closeGPRSConnection(void){
    EUSART_PrintLn("AT+SAPBR=0,1");
    waitForResponse();
}

void simSleep(void){
    EUSART_PrintLn("AT+CSCLK=2");
    waitForResponse();
}

void simWakeUp(void){
    EUSART_PrintLn("AT");
    __delay_ms(500);
    EUSART_PrintLn("AT+CSCLK=0");
    __delay_ms(500);
}