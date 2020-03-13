/* 
 * File:   aglots.h
 * Author: Javier
 *
 * Created on 18 de febrero de 2014, 10:23
 */

#ifndef AGLOTS_H
#define	AGLOTS_H

#ifdef _WINDLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif

#ifdef	__cplusplus 
extern "C" { 
#endif 
DLLEXPORT bool NumberBars(int NBarsSell);    
DLLEXPORT bool CalcDifVolume(double lastbar, double previousbar);    
DLLEXPORT bool TimeBet(time_t currenttime, const wchar_t *begin, const wchar_t *end);
DLLEXPORT time_t cal(time_t currenttime,const wchar_t *hour);
DLLEXPORT time_t bcalc(time_t currenttime);
DLLEXPORT double calcm(double price,double min);
#ifdef	__cplusplus 
} 
#endif 

#endif	/* AGLOTS_H */

