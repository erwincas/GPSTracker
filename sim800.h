/* 
 * File:   sim800.h
 * Author: erwin
 *
 * Created on May 5, 2019, 5:13 PM
 */

#ifndef SIM800_H
#define	SIM800_H

#include "mcc_generated_files/mcc.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
#define BUFFER_SIZE 70

char makeGPRSConnection(void);
void makeHTTPRequest(char * lat, char * lon, char * battery, char * satellites, char * height);
void makeTestHTTPRequest(void);
void closeGPRSConnection(void);
void simSleep(void);
void simWakeUp(void);
void getBatteryLevel(char * batBuf);
char waitForConnection(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SIM800_H */

