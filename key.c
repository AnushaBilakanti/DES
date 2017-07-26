#include <stdio.h>
#include <stdlib.h>
char * hex_to_bin(char ch) // converts hex to binary string
{
    switch (ch)
    {
        case '0':
            return("0000"); break;
        case '1':
            return("0001"); break;
        case '2':
            return("0010"); break;
        case '3':
            return("0011"); break;
        case '4':
            return("0100"); break;
        case '5':
            return("0101"); break;
        case '6':
            return("0110"); break;
        case '7':
            return("0111"); break;
        case '8':
            return("1000"); break;
        case '9':
            return("1001"); break;
        case 'A':
            return("1010"); break;
        case 'B':
            return("1011"); break;
        case 'C':
            return("1100"); break;
        case 'D':
            return("1101"); break;
        case 'E':
            return("1110"); break;
        case 'F':
            return("1111"); break;
        case 'a':
            return("1010"); break;
        case 'b':
            return("1011"); break;
        case 'c':
            return("1100"); break;
        case 'd':
            return("1101"); break;
        case 'e':
            return("1110"); break;
        case 'f':
            return("1111"); break;
        default:
               return 0;
    } 
}
int main(int argc, char const *argv[])
{
    int bin_key1[64]={0};
    int bin_key2[64]={0};
    int bin_key3[64]={0};
    char *key="1596369d5aa562355453ae44101c2614c729a00607319591";
    int hex_c=0,i;
    char *str_temp=(char*)malloc(sizeof(char)*4);
    int key_c,key_c1,key_c2;
    key_c2=key_c1=key_c=0;
    while(key[hex_c])
    {
          str_temp=hex_to_bin(key[hex_c]);
          for(i=0;i<4;i++)
          { 
              bin_key1[key_c++] = ((int)str_temp[i]-48);
              if(key_c==64)
              {
                    bin_key2[key_c1++] = ((int)str_temp[i]-48);
              }
              if(key_c1==64)
              {
                  bin_key3[key_c2++] = ((int)str_temp[i]-48);
              }
          }
          hex_c++;
    }
    printf("KEYS\n");
    printf("KEY-1\n");
    for(i=0;i<64;i++)
    {
      printf("%d",bin_key1[i]);
    }
    printf("\n");
    for(i=0;i<64;i++)
    {
      printf("%d",bin_key2[i]);
    }
    printf("\n");
    for(i=0;i<64;i++)
    {
      printf("%d",bin_key3[i]);
    }
    return 0;
}


