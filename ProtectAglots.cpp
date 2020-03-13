/*----------------------------------------------------------------
programm: dll expert advisor: AGLots
author: xavier Elorduy 
Copyright 2014
http://www.onurabat.com   |
-----------------------------------------------------------------*/

#include <cstring>
#include <stdlib.h>
#include <ctime>
#include <cstdio>
#include "FileLog.h"

#define	_WINDLL
#include "aglots.h"
int one=1;
/*
 * Separe hour
 */
int shour(const wchar_t *hour){
    wchar_t *chour;
        
    wcsncpy(chour, hour, 2);
    chour[2] = '\0'; 
    return ((int)chour);
}

/*
 * Separe minutes
 */
int sminutes(const wchar_t *minutes){
    wchar_t *cminutes;
    int i,j;
        
    if(wcslen(minutes)>2){
        i=3;j=0;
        while(i<=4){
           cminutes[j]=minutes[i]; 
           i++;j++;
        }
        cminutes[2]='\0';
    }else{   
        cminutes[0]='0';
        cminutes[1]='\0';
    }    
    return ((int)cminutes);
}

//calcul time_t
time_t cal(time_t currenttime,const wchar_t *hour){
    int hourh,hourm;
    
     //separe hour/minutes
    hourh=shour(hour); 
    hourm=sminutes(hour);  
    
    struct tm * timecurrent = gmtime(&currenttime);// currentime
      
    /*struct tm stime={0,hourm,hourh+1,timecurrent->tm_mday,timecurrent->tm_mon,timecurrent->tm_year,
    timecurrent->tm_wday,timecurrent->tm_yday,timecurrent->tm_isdst};*/
    
    struct tm * stime= timecurrent;
    stime->tm_hour=hourh+1;
    stime->tm_min=hourm;
    
    time_t result=mktime(stime);
    return (result); 
}

/*------------------------------------------------------------------
Calculated if the volume of the current bar is x times the       
previous bar, the variable x is DifVolume                        
------------------------------------------------------------------*/
bool NumberBars(int NBarsSell) {
    int NumBarsDelay = 3; //Delay numbers bars
             
    if(NBarsSell == NumBarsDelay)
        return (true);
    else
        return (false);
}

/*------------------------------------------------------------------
Calculated if the volume of the current bar is x times the       
previous bar, the variable x is DifVolume                        
------------------------------------------------------------------*/
bool CalcDifVolume(double lastbar, double previousbar) {
    double DifVolume = 1.1; //volume diferential
    if(lastbar > (previousbar * DifVolume))
        return (true);
    else
        return (false);
}
/*------------------------------------------------------------------
Boolean function return true if current time is between         
variable Begin and variable End                                  
entry:current hour                                               
------------------------------------------------------------------*/
bool TimeBet(time_t currenttime, const wchar_t *begin, const wchar_t *end){
    //int one=1;
    time_t t1 = cal(currenttime,begin); //Begin hour
    time_t t2 = cal(currenttime,end); //End hour
    const wchar_t *begin1=L"24:00";
    if(one==1){
        char buffer[1000];
        char namefile[]="aglots.log";

        FileLog log(namefile);
     
        memset(buffer,0,1000);
        sprintf(buffer,"begin=%s end=%s test=%s\n",begin,end,begin1);
        log.WriteFile(buffer);

        memset(buffer,0,1000);
        struct tm * tt1 = gmtime(&t1);// currentime
        sprintf(buffer,"d=%d m=%d y=%d h=%d mi=%d\n",tt1->tm_mday,tt1->tm_mon,tt1->tm_year,tt1->tm_hour,tt1->tm_min);
        log.WriteFile(buffer);
        
        memset(buffer,0,1000);
        struct tm * tt2 = gmtime(&t2);// currentime
        sprintf(buffer,"d=%d m=%d y=%d h=%d mi=%d\n",tt2->tm_mday,tt2->tm_mon,tt2->tm_year,tt2->tm_hour,tt2->tm_min);
        log.WriteFile(buffer);
        
        memset(buffer,0,1000);
        struct tm * cur = gmtime(&currenttime);// currentime
        sprintf(buffer,"d=%d m=%d y=%d h=%d mi=%d\n",cur->tm_mday,cur->tm_mon,cur->tm_year,cur->tm_hour,cur->tm_min);
        log.WriteFile(buffer);
        
        memset(buffer,0,1000);
        sprintf(buffer,"t1=%lld\n",t1);
        log.WriteFile(buffer);

        memset(buffer,0,1000);
        sprintf(buffer,"t2=%lld\n",t2);
        log.WriteFile(buffer);

        memset(buffer,0,1000);
        sprintf(buffer,"cu=%lld\n",currenttime);
        log.WriteFile(buffer);
        
        log.CloseFile();
        one++;
    }
      

    //test if hour between begin and end

    if((long)currenttime >= (long)t1 && (long)currenttime <= (long)t2){
         return (true);
    }else{
        return (false);
    }    
}

/*------------------------------------------------------------------
time_t function return return fix hour        
entry:current hour                                               
------------------------------------------------------------------*/
time_t bcalc(time_t currenttime){
    const wchar_t *begin=L"00:00";
    
    return (cal(currenttime,begin));
}
/*------------------------------------------------------------------
Double function return min valor         
entry:low, minimum                                               
------------------------------------------------------------------*/
double calcm(double price,double min){
      if(min==0) min=price;//If 0
      else if(price<min) min=price;  
      return (min);
}

/*------------------------------------------------------------------
Calculation Asia meeting time                                  
------------------------------------------------------------------*/
