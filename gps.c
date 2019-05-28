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

void GPS_Get_Satellites(char * GPGGALine, char * satBuf){
    for(int i=0; i<2; i++){
        satBuf[i] = GPGGALine[39+i];
    }
    satBuf[2] = '\0';
}

void GPS_Get_Height(char * GPGGALine, char * heightBuf){
    uint8_t startIndex=44;
    uint8_t i=0;
    
    //First we have to skip some commas
    while(1){
        startIndex++;
        if(GPGGALine[startIndex] == ',') break;
    }
    //Skip the next comma
    startIndex++;
    
    do{
        heightBuf[i] = GPGGALine[startIndex+i];
        i++;
    } while(heightBuf[i-1] != ',');
    
    heightBuf[i-1] = '\0';
}

void GPS_Get_Velocity(char * GPGVTGLine, char * velocityBuf){
    uint8_t startIndex=12;
    uint8_t i=0;
    
    //First we have to skip some commas
    while(1){
        startIndex++;
        
        //Go to the end of the knots index
        if(GPGVTGLine[startIndex] == 'N') break;
    }
    //Skip the next comma
    startIndex++;
    
    do{
        velocityBuf[i] = GPGVTGLine[startIndex+i];
        i++;
    } while(velocityBuf[i-1] != ',');
    
    velocityBuf[i-1] = '\0';
}

char GPS_GetGPGGALine(char * RXBuffer){
    char toMatch[6] = "GPGGA,";
    char breakCondition = 0;
    
    while(1){
        //Wait for a new GPS line
        GPS_WaitForLine();
        
        //Set break condition to true
        char breakCondition = 1;
        
        //Start matching the first 6 characters
        for(int i=0; i<6; i++){
            //If one of them doesnt match, set the breakcondition to false
            if(toMatch[i] != EUSART_Read()) breakCondition = 0;
        }
        
        if(breakCondition) break;
    }
    
    //Start reading the rest of the line
    EUSART_ReadLn(RXBuffer, BUFFER_SIZE);
    
    //Check if the 7th character is not a comma as this would mean
    //There is no gps data available yet
    if (RXBuffer[11] == ',') return 0;
    
    return 1;
}

void GPS_GetGPVTGLine(char * RXBuffer){
    char toMatch[6] = "GPVTG,";
    char breakCondition = 0;
    
    while(1){
        //Wait for a new GPS line
        GPS_WaitForLine();
        
        //Set break condition to true
        char breakCondition = 1;
        
        //Start matching the first 6 characters
        for(int i=0; i<6; i++){
            //If one of them doesnt match, set the breakcondition to false
            if(toMatch[i] != EUSART_Read()) breakCondition = 0;
        }
        
        if(breakCondition) break;
    }
    
    //Start reading the rest of the line
    EUSART_ReadLn(RXBuffer, BUFFER_SIZE);
}
