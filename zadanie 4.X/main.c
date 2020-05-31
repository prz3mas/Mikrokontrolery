// CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>


#define LENA  PORTEbits.RE1
#define LDAT  PORTEbits.RE2
#define LPORT PORTD

#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0
#define L_CR	0x0F		
#define L_NCR	0x0C	

#define L_CFG   0x38

void delay(unsigned int ms)
{
    unsigned int i;
    unsigned char j;
    
 for (i =0; i< ms; i++)
 {
 
  for (j =0 ; j < 200; j++)
   {
      Nop();
      Nop();
      Nop();
      Nop();
      Nop();
   }
 }
}

unsigned int adc(unsigned char kanal)
{
    switch(kanal)
    {
        case 0: ADCON0=0x01; break; //P1
        case 1: ADCON0=0x05; break; //P2
        case 2: ADCON0=0x09; break; 
    }
    
    ADCON0bits.GO=1;
    while(ADCON0bits.GO == 1);

   return ((((unsigned int)ADRESH)<<2)|(ADRESL>>6));
}

void lcd_wr(unsigned char val)
{
  LPORT=val;
}

void lcd_cmd(unsigned char val)
{
	LENA=1;
        lcd_wr(val);
        LDAT=0;
        //delay(3);
        LENA=0;
        //delay(3);
	LENA=1;
}
 
void lcd_dat(unsigned char val)
{
	LENA=1;
        lcd_wr(val);
        LDAT=1;
        //delay(3);
        LENA=0;
        //delay(3);
	LENA=1;
}

void lcd_init(void)
{
	LENA=0;
	LDAT=0;
	delay(20);
	LENA=1;
    
	
	lcd_cmd(L_CFG);
	delay(5);
	lcd_cmd(L_CFG);
        delay(1);
	lcd_cmd(L_CFG); //configura
	lcd_cmd(L_OFF);
	lcd_cmd(L_ON); //liga
	lcd_cmd(L_CLR); //limpa
	lcd_cmd(L_CFG); //configura
        lcd_cmd(L_L1);
}

void lcd_str(char* str)
{
 unsigned char i=0;
  
 while(str[i] != 0 )
 {
   lcd_dat(str[i]);
   i++;
 }  
}

void count(int a, int b)
{
    while(1)
    {
        while((a != 0) | (b != 0))
        {
            char buffer[32];
            sprintf(buffer, "    %02i:%02i            ", a, b);


                    lcd_cmd(L_CLR);
                    lcd_cmd(L_L1); //Ustawienie karetki w pierwszej linii
                    lcd_str("Grzanie:       "); //napis
                    lcd_cmd(L_L2); //Przej??ie do drugiej linii
                    lcd_str(buffer);
                    delay(1000);
                    b--;
                    if(b < 0){a--; b = 59;}

        }  
                lcd_cmd(L_CLR);
                lcd_cmd(L_L1); //Ustawienie karetki w pierwszej linii
                lcd_str("Koniec zabawy        "); //napis
                lcd_cmd(L_L2); //Przej??ie do drugiej linii
                lcd_str("Wyjmnij rzarcie       ");
                delay(1000);
    }
}

void time()
{
    int a=0, b=0;
    while(1)
           {
        
                char buffer[32];
                if(b > 50){b = 0;}
                sprintf(buffer, "    %02i:%02i            ", a, b);
        
                lcd_cmd(L_CLR);
                lcd_cmd(L_L1); //Ustawienie karetki w pierwszej linii
                lcd_str("Czas grzania:       "); //napis
                lcd_cmd(L_L2); //Przej??ie do drugiej linii
                lcd_str(buffer);
                delay(200);
        
                if(PORTBbits.RB4 == 0)
                {
                    a += 1;
                }
                
                if(PORTBbits.RB3 == 0)
                {
                    b += 10;
                }
               
                if(PORTBbits.RB2 == 0){count(a, b);}
                          
           }
    
    
}
void moc()
{
            while(1)
           {
                lcd_cmd(L_CLR);
                lcd_cmd(L_L1); //Ustawienie karetki w pierwszej linii
                lcd_str("Wybierz moc:       "); //napis
                lcd_cmd(L_L2); //Przej??ie do drugiej linii
                lcd_str("    800 W       ");
                delay(200);
                if(PORTBbits.RB5 == 0) break;
                if(PORTBbits.RB2 == 0) time();
           }

           while(1)
            {
                lcd_cmd(L_L2); //Przej??ie do drugiej linii
                lcd_str("    600 W       ");
                delay(200);
                if(PORTBbits.RB5 == 0) break;
                if(PORTBbits.RB2 == 0) time();
            }

           while(1)
            {
                lcd_cmd(L_L2); //Przej??ie do drugiej linii
                lcd_str("    350 W       ");
                delay(200); 
                if(PORTBbits.RB5 == 0) break;
                if(PORTBbits.RB2 == 0) time();
           }
           while(1)
           {
                lcd_cmd(L_L2); //Przej??ie do drugiej linii
                lcd_str("    200 W       ");
                delay(200);  
                if(PORTBbits.RB5 == 0) break;
                if(PORTBbits.RB2 == 0) time();
           }
}

void main(void) {
    
    //Inicjalizacja konwertera analogowo cyfrowego
    ADCON0=0x01;
    ADCON1=0x0B;
    ADCON2=0x01;
    
    TRISA=0xC3;
    TRISB=0x3F;   
    TRISC=0x01;
    TRISD=0x00;
    TRISE=0x00;
    
    lcd_init(); //Inicjalizacja wy?wietlacza
    lcd_cmd(L_CLR); //Czyszczenie wy?wietlacza
    
    while(PORTBbits.RB1 != 0)
    {
        moc();
    }


    
    
    
    return;
}