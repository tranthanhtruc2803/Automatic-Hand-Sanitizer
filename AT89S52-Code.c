
#include <REGX51.h>

#define ON 			1
#define OFF 		0
#define HAND_DETECT 0
       
sbit sensor = P3^2;     
sbit pump = P1^0;     

int lock = 0;

void delay(unsigned int msec){
	// create delay
	unsigned int i, j;
   for(i = 0; i < msec; i++){        
		for(j = 0; j < 1000; j++);
    }
}

void hand_sanitizer(void){
	if(sensor == HAND_DETECT){
			if (lock == 0){
				lock = 1;
				pump = ON;
				delay(2000);
			pump = OFF;
			}
			else{
				pump = OFF;
				}
		}
		else{
			pump = OFF;
			lock = 0;
			delay(50);
		}
}

void main(){
	while(1){
		hand_sanitizer();
	}
}

