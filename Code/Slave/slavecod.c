#include<reg51.h>



//LCD Module Connections
#define display_port P1    //Data pins connected to port 2 on microcontroller
sbit rs = P3^6;            //RS pin connected to pin 6 of port 3
sbit rw = P3^5;            // RW pin connected to pin 5 of port 3
sbit e =  P3^4;            //E pin connected to pin 4 of port 3
//End LCD Module Connections

//Stepper Motor connections
sbit motor_pin_1=P2^0;
sbit motor_pin_2=P2^1;
sbit motor_pin_3=P3^2;
sbit motor_pin_4=P2^3;

//End of stepper motor connections

//Led connections
  sbit yellow_led=P2^4;
  sbit green_led=P2^5;
  sbit red_led=P2^6;
   sbit orange_led=P2^7;
  //End of led connections
  
int counter=0;
void msdelay(unsigned int time)  // Function for creating delay in milliseconds.
{
    unsigned i,j ;
    for(i=0;i<time;i++)    
    for(j=0;j<1275;j++);
}


void lcd_cmd(unsigned char command)  //Function to send command instruction to LCD
{
    display_port = command;
    rs= 0;
    rw=0;
    e=1;
    msdelay(1);
    e=0;
}

void lcd_data(unsigned char disp_data)  //Function to send display data to LCD
{
    display_port = disp_data;
    rs= 1;
    rw=0;
    e=1;
    msdelay(1);
    e=0;
}


 void lcd_init()    //Function to prepare the LCD  and get it ready
{
    lcd_cmd(0x38);  // for using 2 lines and 5X7 matrix of LCD
    msdelay(10);
    lcd_cmd(0x0F);  // turn display ON, cursor blinking
    msdelay(10);
    lcd_cmd(0x01);  //clear screen
    msdelay(10);
    lcd_cmd(0x81);  // bring cursor to position 1 of line 1
    msdelay(10);
}



void Ext_int_Init()				
{
	EA  = 1;		   /* Enable global interrupt */
	ES = 1;  		/* Enable serial interrupt */			
}


void UART_Init()
{
	TMOD = 0x20;		/* Timer 1, 8-bit auto reload mode */
	TH1 = 0xFD;		/* Load value for 9600 baud rate */
	SCON = 0x50;		/* Mode 1, reception enable */
	TR1 = 1;		/* Start timer 1 */
}

void display_msg1(){
	lcd_init();
	lcd_cmd(0x0C);
   lcd_data('A');
	lcd_data('S');
	lcd_data('C');
	lcd_data('I');
	lcd_data('I');
	lcd_data(' ');
	lcd_data('C');
	lcd_data('o');
	lcd_data('d');
	lcd_data('e');
	lcd_data(':');
    
}

void display_msg2(){
lcd_cmd(0xC0);   //Force cursor to the start of second line
lcd_data(' ');
lcd_data('R');
lcd_data('o');
lcd_data('t');
lcd_data('a');
lcd_data('t');	
lcd_data('i');
lcd_data('o');
lcd_data('n');
lcd_data(':');

}

void Serial_ISR() interrupt 4    
{
   counter++;
	//lcd_data(SBUF);		/* Give received data to LCD */
	RI = 0;			/* Clear RI flag */
	
	if(counter==4){
		display_msg1();
	  lcd_data('4');
	  lcd_data('5');
	  lcd_data('C');
	  lcd_data('W');
	  display_msg2();
		 lcd_data('4');
	  lcd_data('5');
		lcd_data(' ');
		lcd_data('d');
		lcd_data('e');
		lcd_data('g');
		lcd_data(' ');
	  lcd_data('C');
	  lcd_data('W');
		P2=0x00;
		P2=0x08;
		yellow_led=1;
	}
	if(counter==8){
	  display_msg1();
	  lcd_data('9');
	  lcd_data('0');
	  lcd_data('C');
	  lcd_data('W');
		display_msg2();
		lcd_data('9');
	  lcd_data('0');
		
		lcd_data(' ');
		lcd_data('d');
		lcd_data('e');
		lcd_data('g');
		lcd_data(' ');
		
	  lcd_data('C');
	  lcd_data('W');
		P2=0x00;
		P2=0x0C;
      green_led=1;
	}
	if(counter==12){
		display_msg1();
	  lcd_data('4');
	  lcd_data('5');
	  lcd_data('A');
	  lcd_data('W');
		display_msg2();
		lcd_data('4');
	  lcd_data('5');
		
		lcd_data(' ');
		lcd_data('d');
		lcd_data('e');
		lcd_data('g');
		lcd_data(' ');
		
	  lcd_data('A');
	  lcd_data('W');
		P2=0x00;
		P2=0x01; // value for 45 deg CW
	   red_led=1;
	}
	
	if(counter==16){
		display_msg1();
	  lcd_data('9');
	  lcd_data('0');
	  lcd_data('A');
	  lcd_data('W');
		display_msg2();
		lcd_data('9');
	  lcd_data('0');
		 
		lcd_data(' ');
		lcd_data('d');
		lcd_data('e');
		lcd_data('g');
		lcd_data(' ');
		
	  lcd_data('A');
	  lcd_data('W');
		
	   P2=0x00;
	   P2=0x03;
		orange_led=1;
	  counter=0;
	}
	
	
} 


void rotate_motor(){


}
void main(){
  P2=0x00;

	P1 = 0x00;		/* Make P1 output */
	Ext_int_Init();  	/* Call Ext. interrupt initialize */
	UART_Init();      /*Initializing the Serial Port */
	
	 lcd_init();
	while(1){
	 
	}
}