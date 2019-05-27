/* 
 * File:   utils.h
 * Author: erwin
 *
 * Created on May 5, 2019, 5:14 PM
 */

#ifndef UTILS_H
#define	UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_PRECISION	(6)
static const double rounders[MAX_PRECISION + 1] =
{
	0.5,				// 0
	0.05,				// 1
	0.005,				// 2
	0.0005,				// 3
	0.00005,			// 4
	0.000005,			// 5
	0.0000005,			// 6
};

char * ftoa(double f, char * buf, int precision);


#ifdef	__cplusplus
}
#endif

#endif	/* UTILS_H */

