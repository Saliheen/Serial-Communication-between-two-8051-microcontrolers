
#include<reg51.h>
unsigned char ascii_values[4][4]={{52,53,67,87 },
                                {57,48,67,87},
                                {52,53,65,87 },
                                {57,48,67,87}};
int counter;
int i;
int j;
int k; 
int m;		
unsigned char ascii_code;										  
void delay(){
for(i=0;i<200;i++){
for(j=0; j<500; j++){
}
}
}			


void ser_init(){

	TMOD = 0x20;		/* Timer 1, 8-bit auto reload mode */
	TH1 = 0xFD;		/* Load value for 9600 baud rate */
	SCON = 0x50;		/* Mode 1, reception enable */
	TR1 = 1;		/* Start timer 1 */

}
void ser_txt(unsigned char value){
SBUF=value;
	while(TI==0);
	TI=0;
}
void main(){
	ser_init();
    while(1){
		 counter=0;
	 for(k=0; k<4; k++){
	 for(m=0; m<4; m++){
		 ascii_code=ascii_values[counter][m];
	  ser_txt(ascii_code);
		 delay();
		 delay();
	 }
	 counter++;
	 delay();
	 delay();
	 delay();
	 delay();
	 ser_txt(' ');
	 }
	 }
}