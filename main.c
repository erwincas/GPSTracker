#include "mcc_generated_files/mcc.h"
#include "gps.h"
#include "sim800.h"
#include "utils.h"

void main(void)
{
    double lat, lon;
    char RXBuffer[BUFFER_SIZE];
    char latArray[11], lonArray[11];
    char batBuf[4];
    int status;
    
    // initialize the device
    SYSTEM_Initialize();
    
    EUSART_ChangeToSim();
    simWakeUp();
    //EUSART_ReadLn(RXBuffer);
    //EUSART_PrintLn(RXBuffer);
    
    
    EUSART_ChangeToGPS();
    GPS_WaitForLine();
    
    while(1){
        //Fill the buffer
        GPS_ReadLine(RXBuffer);
        
        //Check the first 5 characters of the buffer
        if(GPS_LineIsGPGLL(RXBuffer)){
            //First check if the 7th character is not a comma as this would mean
            //There is no data yet
            if(RXBuffer[6] != ','){
                //Fill the lat & lon double
                lat = GPS_NMEAToDouble(RXBuffer, 6);
                lon = GPS_NMEAToDouble(RXBuffer, 19);
                
                ftoa(lat,latArray,6);
                ftoa(lon,lonArray,6);
                
                break;
            }
        }
    }
    __delay_ms(2000);
    EUSART_ChangeToSim();
    
    makeGPRSConnection();
    makeHTTPRequest(latArray, lonArray);
    closeGPRSConnection();
    
    // puts the sim module into sleep mode
    simSleep();
     
    SLEEP();
}
/**
 End of File
*/