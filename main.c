#include "mcc_generated_files/mcc.h"
#include "gps.h"
#include "sim800.h"
#include "utils.h"

void main(void) {
    double lat, lon;
    char RXBuffer[BUFFER_SIZE], batBuf[4], satBuf[3], heightBuf[10], velocityBuf[10];
    char latArray[11], lonArray[11];
    char response;

    // initialize the device
    SYSTEM_Initialize();

    // give all the devices some time to wake up
    __delay_ms(5000);

    EUSART_ChangeToSim();
    simWakeUp();

    EUSART_ChangeToGPS();
    
    while (1) {
        //Clear the buffer
        memset(RXBuffer, 0, BUFFER_SIZE);
        
        //Wait for a GPGGA line
        if(GPS_GetGPGGALine(RXBuffer)){
            EUSART_PrintLn(RXBuffer);
            // Get amount of satellites
            GPS_Get_Satellites(RXBuffer, satBuf);
            
            // Get current height
            GPS_Get_Height(RXBuffer, heightBuf);

            //Fill the lat & lon double
            lat = GPS_NMEAToDouble(RXBuffer, 10);
            lon = GPS_NMEAToDouble(RXBuffer, 23);

            ftoa(lat, latArray, 6);
            ftoa(lon, lonArray, 6);
            
            break;
        }
        
        __delay_ms(1000);
    }
    EUSART_ChangeToSim();

    getBatteryLevel(batBuf);
    memset(RXBuffer, 0, BUFFER_SIZE);
    // Check if a connection has been made
    if (waitForConnection()) {
        // If so, make the GET request
        if (makeGPRSConnection()) {
            makeHTTPRequest(latArray, lonArray, batBuf, satBuf, heightBuf);
        }
        closeGPRSConnection();
    }

    // Put the sim module to sleep
    simSleep();

    SLEEP();
}
/**
 End of File
 */