/* 
 * File:   gps.h
 * Author: erwin
 *
 * Created on May 5, 2019, 2:59 PM
 */

#ifndef GPS_H
#define	GPS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/mcc.h"
    
#define BUFFER_SIZE 70
    
double GPS_NMEAToDouble(char * RXBuffer, char startPos);
char GPS_GetGPGGALine(char * RXBuffer);
void GPS_GetGPVTGLine(char * RXBuffer);
void GPS_WaitForLine(void);
void GPS_Get_Satellites(char * GPGGALine, char * satBuf); 
void GPS_Get_Height(char * GPGGALine, char * heightBuf); 
void GPS_Get_Velocity(char * GPGVTGLine, char * velocityBuf);
#ifdef	__cplusplus
}
#endif

#endif	/* GPS_H */

