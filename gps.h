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
char GPS_LineIsGPGLL(char * RXBuffer);
void GPS_ReadLine(char * RXBuffer);
void GPS_WaitForLine(void);

#ifdef	__cplusplus
}
#endif

#endif	/* GPS_H */

