#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <fcntl.h>
#include <math.h>


void IntToBinary(unsigned char n)
{
    int i, k;

    for (i = 7; i >= 0; i--)
    {
        k = n >> i;

        if (k & 1)
                printf("1");
            else
                printf("0");
    }
   printf("   ");
}
void Opoznienie()
{ 
    int c,d = 0;
    for (c = 1; c <= 32767; c++)
            for (d = 1; d <= 8192; d++)
            {}
}
void binInk()
{
    printf( "\n rozpoczeto binInk \n");
    unsigned char licznik = 0;
    
   while (!(_kbhit()))
   {
    
       printf("\r %d  ", licznik);
       IntToBinary(licznik);

       Opoznienie();

       licznik ++;      
       
   }
}
void binDek()
{ 
    printf( "\n rozpoczeto binDek \n");
    unsigned char licznik = 0;

   while (!(_kbhit()))
   {
       printf("\r %d  ", licznik);
       IntToBinary(licznik);

       Opoznienie();

       licznik --; 
   }
}
void greyU()
{  
    printf( "\n rozpoczeto greyU \n");
   unsigned char licznik = 0;
   unsigned char display = 0;

   while (!(_kbhit()))
   {
       display = licznik ^ (licznik >> 1);
       printf("\r %d  ", licznik);
       IntToBinary(display);

       Opoznienie();

       licznik ++;
    }
   
}
void greyD()
{
    printf( "\n rozpoczeto greyD \n");
   unsigned char licznik = 0;
   unsigned char display = 0;

   while (!(_kbhit()))
   {
       display = licznik ^ (licznik >> 1);
       printf("\r %d  ", licznik);
       IntToBinary(display);

       Opoznienie();

       licznik --;
   }
   
}
void bcdU()
{
    printf( "\n rozpoczeto bcdU \n");
    unsigned char licznik = 0;
    unsigned char display = 0;

   while (!(_kbhit()))
   {
        if(licznik > 99)
        licznik = 0;

        display = ((licznik / 10) << 4) | (licznik % 10);
        printf("\r %d  ", licznik);
        IntToBinary(display);

        Opoznienie();

        licznik ++;
   }

}
void bcdD()
{
    printf( "\n rozpoczeto bcdD \n");
    unsigned char licznik = 0;
    unsigned char display = 0;

   while (!(_kbhit()))
   {
       if(licznik > 99)
        licznik = 99;

        display = ((licznik / 10) << 4) | (licznik % 10);
        printf("\r %d  ", licznik);
        IntToBinary(display);

        Opoznienie();

        licznik --;
   }
}
void snake()
{
    printf( "\n rozpoczeto snake \n");
    
    unsigned char wezyk = 7;
    short kierunek = 0;   
 
   while (!(_kbhit()))
   {
      
       printf("\r ");
       IntToBinary(wezyk);

       Opoznienie();

        if(wezyk == 7)
            kierunek = 0;
        else if(wezyk == 224)
            kierunek = 1;

        if(kierunek == 0)
            wezyk <<= 1;
        else
            wezyk >>= 1;
    }
}
void kolejka()
{
   
    printf( "\n rozpoczeto kolejka \n");

    unsigned char stop = 8;
    unsigned char position = 0;
    unsigned char display = 0;

    while(!(_kbhit()))
    {
        if(position<stop)
            {
                printf("\r ");
                display ^= 1UL << position;
                IntToBinary(display);
                display ^= 1UL << position;
                Opoznienie(1000); //Opoznienie
                position++;
            }
            /*else
            {
               printf("\r ");
               display ^= 1UL << stop;
               IntToBinary(display);
               Opoznienie(1000); //Opoznienie
               stop--;
               position=0;
            }*/
    }

  /*  while(!(_kbhit()))
    {
        unsigned char display = 0;
        unsigned char licznik = 0;
        unsigned char w = 8;
       
        for(int j = 0; j < 8; j++)
        {
            for (int i = 0; i < w; i++)
            {
                display ^= licznik << i;
                printf("\r ");
                
                IntToBinary(display);
                                
                Opoznienie(); 

                if(_kbhit()) return;
            }
            w--;
            licznik = display;
        }            
    }
    */
}
void prng()
{

    void IntToBinary6(unsigned char n)
    {
        int i, k;

        for (i = 5; i >= 0; i--)
        {
            k = n >> i;

            if (k & 1)
                    printf("1");
                else
                    printf("0");
        }
        printf("   ");
    }

    printf( "\n rozpoczeto prng \n");

    unsigned char display = 1;
    unsigned char wyz = 51;
    
    while(!(kbhit()))
    {
        unsigned char licznik = 0;
                
        for(int i = 0; i < 6; i++)
        {
            if(((wyz >> i) & 1) == 1)
                if(((display >> i) & 1) == 1) licznik++;                
        }
        
        display = display >> 1;

        if(licznik % 2 == 0) licznik = 0;
            else licznik = 1;  

        display = display | (licznik << 5);
        
        printf("\r ");
        IntToBinary6(display);
        
        Opoznienie();
    }
    
}
void setup(unsigned char input)
{
    if (input == 0 ) {binInk();}
    if (input == 1 ) {binDek();}
    if (input == 2 ) {greyU();}
    if (input == 3 ) {greyD();}
    if (input == 4 ) {bcdU();}
    if (input == 5 ) {bcdD();}
    if (input == 6 ) {snake();}
    if (input == 7 ) {kolejka();}
    if (input == 8 ) {prng();}
   
}

int main(void)
{
  
unsigned char button = 7;

again:


    printf("\r");
    setup(button);
 
    char ch; 
    ch = _getch();


    if(ch == 'p')
        button--;
    else if(ch == 'n')
        button ++;
    
    if(button == 9) button = 0;

    if(button == 255) button = 8;

goto again;
	

}
 
