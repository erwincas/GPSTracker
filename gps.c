#include "gps.h"


void GPS_WaitForLine(void){
    while(EUSART_Read() != '$');
}

double GPS_NMEAToDouble(char * RXBuffer, char startPos){
    char coordinateBuffer[11];
    int i;
    double coordinate, degrees, seconds;
    
    for(i=0; i<10; i++){
        coordinateBuffer[i] = RXBuffer[i+startPos] ;
    }
    
    coordinateBuffer[i+1] = '\0';           
    coordinate = atof(coordinateBuffer);
    
    degrees = (int)(coordinate/100);
    seconds = coordinate - degrees * 100;
    coordinate = degrees + seconds/60;
    
    if(RXBuffer[startPos+11] == 'S' || RXBuffer[startPos+11] == 'W')
        coordinate *= -1; //Negate
    
    return coordinate;
}

char GPS_LineIsGPGLL(char * RXBuffer){
    char toMatch[5] = "GPGLL";
    
    for(int i=0; i<5; i++){
        if(toMatch[i] != RXBuffer[i]) return 0;
    }
    
    return 1;
}

void GPS_ReadLine(char * RXBuffer){
    unsigned char readByte;
    uint8_t i=0;

    // Fill the buffer
    for(; i<BUFFER_SIZE;){
        readByte = EUSART_Read();
        if(readByte == '$') break;

        RXBuffer[i] = readByte;
            
        i++;
    }
    RXBuffer[i] = '\0';
}
