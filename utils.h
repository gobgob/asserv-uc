#ifndef UTILS_H
#define UTILS_H

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define INT_MAX = (32767)
#define INT_MIN = (-32768)

#define cbi(x,y)	x&= ~(1<<y) //cbi(x,y) 
#define sbi(x,y)	x|= (1<<y)//sbi(x,y) 

#endif