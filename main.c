#include "mcc_generated_files/mcc.h"
#include "gps.h"
#include "sim800.h"
#include "utils.h"

void main(void) {
    double lat, lon;
    char RXBuffer[BUFFER_SIZE], batBuf[4];
    char latArray[11], lonArray[11];

    // initialize the device
    SYSTEM_Initialize();

    // give all the devices some time to wake up
    __delay_ms(1000);

    EUSART_ChangeToSim();
    simWakeUp();

    EUSART_ChangeToGPS();
    GPS_WaitForLine();

    while (1) {
        //Fill the buffer
        GPS_ReadLine(RXBuffer);

        //Check the first 5 characters of the buffer
        if (GPS_LineIsGPGLL(RXBuffer)) {
            //First check if the 7th character is not a comma as this would mean
            //There is no gps data available yet
            if (RXBuffer[6] != ',') {
                //Fill the lat & lon double
                lat = GPS_NMEAToDouble(RXBuffer, 6);
                lon = GPS_NMEAToDouble(RXBuffer, 19);

                ftoa(lat, latArray, 6);
                ftoa(lon, lonArray, 6);

                break;
            }
        }
    }
    EUSART_ChangeToSim();

    getBatteryLevel(batBuf);
    memset(RXBuffer, 0, BUFFER_SIZE);
    // Check if a connection has been made
    if (waitForConnection()) {
        // If so, make the GET request
        if (makeGPRSConnection()) {
            makeHTTPRequest(latArray, lonArray, batBuf);
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