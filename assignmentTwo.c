#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
/*************************/
void decToIEEE()
{
   float user_response = 0.0;//original user response
   float dec_number = 0.0;//copy of original user response
   int sign = 0; //sign(positive or negative) of dec value
   float exponent = 0.0;
   
   printf("Enter the decimal representation: ");
   scanf("%f", &user_response);//sets user response
   dec_number = user_response;
   if(dec_number == 0.0) //Conditional Case, if user value is 0
   {
      printf("\nSign: 0");
      printf("\nBiased exponent: 00000000");
      printf("\nMantissa: 00000000000000000000000");
      printf("\nIEEE-754 format: 00000000");
      return;
   }
   
   printf("\nDecNumber: %f\n",dec_number);
   if(dec_number > 0.0)
   {
      sign = 0;

   }
   else {

      sign = 1;
      dec_number = 0.0 - dec_number;
   }
   printf("\nSign: %d",sign);
   
   while(dec_number >= 2.0)//Normalising the value;
   {
      dec_number = dec_number/2;
      exponent++;
   }
   while(dec_number < 1)
   {
      dec_number = dec_number * 2.0;
      exponent--;
   }
   
   float savedExponent = exponent;
   
   exponent = exponent + 127;
   int i = 1;
   printf("\nBiased exponent: ");
      
   for(i = 1; i <=8;i+=1)
   {
      if(exponent >= 127)
      {
         printf("1");
         exponent = exponent - 127;
      }
      else
      {
         printf("0");
         exponent = exponent * 2;
      }
   }

   dec_number = dec_number - 1;
   /* Print IEEE-754 representation */
   printf("\nMantissa: ");
   int j = 1;

   float original_number =  user_response - floor(user_response);
   for(j = 1; j <=23;j+=1)
   {
      
      if(original_number >= 1)
      {
         printf("1");
         original_number = original_number - 1;
      }
      else
      {
         printf("0");
         
         original_number = original_number * 2;

      }
   }
   
   /**CODE BORROWED AND MODIFIED FROM https://stackoverflow.com/questions/45228925/how-to-print-float-as-hex-bytes-format-in-c**/
    float ieee_number = (float)user_response;
    union {
        float f;
        uint32_t u;
    } f2u = { .f = ieee_number };

    printf("\nIEEE-754 format: %" PRIx32 "\n", f2u.u);


}
/***********************************************************************/
void ieeeToDec()
{
   /* declare local variables */
   int ieee;
   int exponent = 0;
   int sign = 0;
   float mantissa = 0.0;
   float decimal_format = 0.0;
   /* prompt for IEEE-754 representation */
   printf("Enter the IEEE-754 representation: ");
   scanf("%x",&ieee);
   /* check for special cases: 0, -0, +infinity, -infinity, NaN,
   if so, print and return */
   if(ieee == 0x00000000)
   {
      printf("\nSign: +\nSpecial Case: 0 ");
      return;
   }
   if(ieee == 0x80000000)
   {
      printf("\nSign: -\nSpecial Case: 0 ");
      return;
   }
   if(ieee == 0x7f800000)
   {
      printf("\nSign: +\nSpecial Case: infinity ");
      return;
   }
   if(ieee == 0xff800000)
   {
      printf("\nSign: -\nSpecial Case: infinity ");
      return;
   }
   if(ieee == 0xffffffff)
   {
      printf("\nSpecial Case: NaN ");
      return;
   }
   if(ieee & 0x7fffffff > 0x7f800000)
   {
      printf("\nSpecial Case: NaN ");
      return;
   }
   /* Mask sign from number: if sign=0, print "+", else print "-" */
   sign = floor(ieee / pow(2,31)); 
   if( sign == 0)
   {
      printf("\nSign: +");
   }
   else
   {
      printf("\nSign: -");
   } 
   
   exponent = (ieee & 0x7f800000) / pow(2,23);
   if(exponent == 0)
   {
      mantissa = (ieee & 0x007fffff) / pow(2,23);
      printf("\nUnbiased exponent: -126");
      if(sign ==0)
      {
         printf("\nDenormalized decimal format: %f*2^ (-126)",mantissa);
         return;
      }
      mantissa = mantissa + sign;
      printf("\nDenormalized decimal format: %f*2^ (-126)",mantissa);
         
      return;
   }
   else
   {
   
      exponent = exponent - 127;
      printf("\nUnbiased exponent: %d",exponent);
      
      mantissa = 1 + ((ieee & 0x007fffff) / pow(2,23));
      printf("\nNormalized decimal: %f",mantissa);
      
      decimal_format = mantissa * pow(2,exponent);
      
      printf("\nDecimal format: %f",decimal_format); 
      
   }   
}

void menu()
{
   int i = 0;
   while( i == 0)
   {
      int userChoice = 0;
      printf("\n***Floating-point conversion:***\n-----------------\n");
      printf("1) Decimal to IEEE-754 conversion\n2) IEEE-754 to Decimal Conversion\n3) Exit \nEnter Selection: ");
      scanf("%d",&userChoice);
      
      if(userChoice == 1)
      { 
           decToIEEE();
      }
      else if(userChoice == 2)
      {
           ieeeToDec();
      }
      else if(userChoice == 3)
      {
           exit(1);
      }
   }

}

int main()
{
   menu();
   return 0;
}