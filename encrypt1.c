#include "functions.h"

struct num
{
  int number;
  int freq;
};

int ip[64] = {0};
int e[48] = {0};
int pc1a[28] = {0}; // Pc1 first half
int pc1b[28] = {0}; // Pc1 second half.
int pc2[48] = {0};
int v_shift[16] = {0};
int k[17][48]={};
int k1[17][48]={};
int k2[17][48]={};
int p_arr[48]={0};
int invp_arr[64]={0};
//s1-s8
int s1[4][16] = {};
int s2[4][16] = {};
int s3[4][16] = {};
int s4[4][16] = {};
int s5[4][16] = {};
int s6[4][16] = {};
int s7[4][16] = {};
int s8[4][16] = {};
int row;
int col;

void get_row_col(int six_bits[6])  // gives row and col number from 6 bit input
{
  row = (six_bits[0] * 2 )+ (six_bits[5] * 1);
  col = (six_bits[1]*8) + (six_bits[2]*4)+ (six_bits[3]*2)+ (six_bits[4]);
}

int testIPe(char * line)
{
  char *values;
  char s[2] = ",";
  int flag=0;
  values = strtok(line, s);
  int count=0;
  int i_value;
  struct num obj[64];
  int i;
  int k=0;
  for(i = 0; i < 64; ++i)
  {
    obj[i].number=i+1;
    obj[i].freq=0;  
  }
  while( values != NULL ) 
    {
      i_value=atoi(values);
      ip[k]=i_value;
      k++;
      if(i_value>=1 && i_value<=64)
      {
        obj[i_value-1].freq++;
        flag=1;
      }
      else
      { flag=0;
        fprintf(stderr, "(IP ) Contains invalid entries.\n");
        exit(0);
      }
      values = strtok(NULL, s);
      count++;
    }
    for(i=0;i<64;i++)
    {
      if(obj[i].freq>1)
      {

        fprintf(stderr, "(IP) the value %d in the IP table occur too many times\n", obj[i].number);
      }
      if (obj[i].freq==0)
      {
        fprintf(stderr, "(IP) the value %d did not occur in the IP table\n", obj[i].number);
      }
    }
    if(count<64)
    {
      fprintf(stderr, "(IP) too few values read\n");
    exit(0);
  }
  if(count>64)
  {
    fprintf(stderr, "(IP) too many values read\n");
    exit(0);
  }
    return flag;
}

int testEe(char * line)
{
  char *values;
  char s[2] = ",";
  int flag=0;
  values = strtok(line, s);
  int count=0;
  int i,i_value;
  int k=0;
  struct num obj[32];
  for (i = 0; i < 32; ++i)
  {
    obj[i].number=i+1;
    obj[i].freq=0;  
  }
  
  while( values != NULL ) 
    {
      i_value=atoi(values);
      e[k]=i_value;
      k++;
      if(i_value>=1 && i_value<=32)
      {
        obj[i_value-1].freq++;
        flag=1;
      }
      else
      { flag=0;
        fprintf(stderr, "(E ) Contains invalid entries.\n");
      exit(0);
      }
      values = strtok(NULL, s);
      
      count++;
    }
    for(i=0;i<32;i++)
    {
      if(obj[i].freq>2)
      {

        fprintf(stderr, "(E) the value %d in the E table occur too many times\n", obj[i].number);
      }
      if (obj[i].freq==0)
      {
        fprintf(stderr, "(E) the value %d did not occur in the E table\n", obj[i].number);
      }
    }
    if(count<48)
    {
      fprintf(stderr, "(E) too few values read\n");
    exit(0);
  }
  if(count>48)
  {
    fprintf(stderr, "(E) too many values read\n");
    exit(0);
  }
  
    return flag;
}



int testVe(char * line)// checks PC1 and populates v_shift
{
  char *values;
  char s[2] = ",";
  int flag=0;
  values = strtok(line, s);
  int count=0;
  int i,i_value;
  int k=0;
  struct num obj[2];
  for (i = 0; i < 2; ++i)
  {
    obj[i].number=i+1;
    obj[i].freq=0;  
  }
  
  while( values != NULL ) 
    {
      i_value=atoi(values);
      v_shift[k]=i_value;
      k++;
      if(i_value>=1 && i_value<=2)
      {
        obj[i_value-1].freq++;
        flag=1;
      }
      else
      { flag=0;
        fprintf(stderr, "(V ) Contains invalid entries.\n");
      exit(0);
      }
      values = strtok(NULL, s);
      
      count++;
    }
    
  if(obj[0].freq!=4)
  {
    fprintf(stderr, "(V) the value %d in the V table did not occur 4 times\n", obj[0].number);
  }
  if (obj[1].freq!=12)
  {
    fprintf(stderr, "(V) the value %d in the V table did not occur 12 times\n", obj[1].number);
  }
   
    if(count<16)
    {
      fprintf(stderr, "(V) too few values read\n");
    exit(0);
  }
  if(count>16)
  {
    fprintf(stderr, "(V) too many values read\n");
    exit(0);
  }
  
    return flag;
}
int testSe(char * line, int type)
{
  if(type<1 || type>8)
  {
    fprintf(stderr, "S%d exceeding limit. \n", type);
    exit(0);
  }
  // int type=1;
  struct num S[16];// for S-boxes
  char *values;
  char s[2] = ",";
  int flag=0;
  values = strtok(line, s);
  int count=0;
  int i,i_value,x;
  int k=0;

  int Sbox[4][16];
  memset(Sbox,99,16*4);
  for(x=0;x<16;x++)
  {
    S[x].number=x;
    S[x].freq=0;
  }
  int S_lines=0;
  int ctr=0;
  while( values != NULL ) 
    {
        i=0;
        while(i<16 && values != NULL)
        {
            i_value=atoi(values);
            Sbox[S_lines][k]=i_value;
            k++;
            if(i_value>=0 && i_value<=15)
            {
                S[i_value].freq++;
                flag=1;
                if(type ==1)
                {
                  s1[ctr][i] = i_value;
                }
                if(type ==2)
                {
                  s2[ctr][i] = i_value;
                  
                }
                if(type ==3)
                {
                  s3[ctr][i] = i_value;
                  
                }
                if(type ==4)
                {
                  s4[ctr][i] = i_value;
                  
                }
                if(type ==5)
                {
                  s5[ctr][i] = i_value;
                  
                }
                if(type ==6)
                {
                  s6[ctr][i] = i_value;
                  
                }
                if(type ==7)
                {
                  s7[ctr][i] = i_value;
                  
                }
                if(type ==8)
                {
                  s8[ctr][i] = i_value;
                  
                }
            }
            else
            { flag=0;
              fprintf(stderr, "(S%d ) Contains invalid entries.\n",type);
              exit(0);
            }
            values = strtok(NULL, s);
            i++;
            if(k==16)
            { 
              k=0;
              S_lines++;
            }
            count++;
        }
        ctr++;
            
    }

    for(i=0;i<16;i++)
    {
      if(S[i].freq>4)
      {

        fprintf(stderr, "(S%d) the value %d in the S1 table did not occur 4 times\n",type,S[i].number);
      }
      if (S[i].freq==0)
      {
        fprintf(stderr, "(S%d) the value %d did not occur in the E table\n",type,S[i].number);
      }
    }
    if(count<64)
    {
      fprintf(stderr, "(S%d) %d values read but 64 expected\n",type,count);
    exit(0);
  }
  if(count>64)
  {
    fprintf(stderr, "(S%d) too many values read\n",type);
    exit(0);
  }
    return flag;
}
int testPC1e(char * line) // checks PC1 and populates pc1a and pc1b
{
  int pc1a_ctr = 0;
  int pc1b_ctr = 0;
  char *values;
  char s[2] = ",";
  int flag=0;
  values = strtok(line, s);
  int count=0;
  int i,i_value;
  int k=0;
  struct num obj[64];
  for (i = 0; i < 64; ++i)
  {
    //for the numbers with multiple of 8, i am setting their value in obj to 0.
    if ((i+1)%8==0)
    {
      obj[i].number=0;
      obj[i].freq=0;
      continue;
    }
    obj[i].number=i+1;
    obj[i].freq=99; 
  }
  
  while( values != NULL ) 
    {
      i_value=atoi(values);
      k++;
      if(i_value>=1 && i_value<=64)
      {
        if(i_value%8!=0)
        {
          obj[i_value-1].freq++;
          flag=1;
          if(pc1a_ctr<29)
            {pc1a[pc1a_ctr++] = i_value;}

        if(pc1a_ctr>=29)
         {
          pc1b[pc1b_ctr++] = i_value;
         } 
        }
        else
        {
          flag=0;
        break;
        }
        
      }
      else
      { flag=0;
        fprintf(stderr, "(PC1) Contains invalid entries.\n");
      exit(0);
      }
      values = strtok(NULL, s);
      
      count++;
    }
    for(i=0;i<64;i++)
    {
      if(obj[i].freq==99 && (i+1)%8!=0)
      {
        fprintf(stderr, "(PC1) the value %d in the PC1 table did not occur\n", obj[i].number);
        exit(0);
      }
    }
    if(count<56)
    {
      fprintf(stderr, "(PC1) too few values read\n");
    exit(0);
  }
  if(count>56)
  {
    fprintf(stderr, "(PC1) too many values read\n");
    exit(0);
  }
  
    return flag;

}
int testPC2e(char * line)
{
  char *values;
  char s[2] = ",";
  int flag=0;
  values = strtok(line, s);
  int count=0;
  int i,i_value;
  int obj[56]={0};
  int k=0;
  while( values != NULL ) 
    {
      i_value=atoi(values);
      
      if(i_value>=1 && i_value<=56)
      {
        pc2[k]=i_value;
        k++;
        obj[i_value-1]+=1;
      flag=1;
      }
    else
    {
      flag=0;
      fprintf(stderr, "(PC2) Contains invalid entries.\n");
      exit(0);
    }
      values = strtok(NULL, s);
      
      count++;
    }
    for(i=0;i<56;i++)
    {
      if(obj[i]>1)
      {
        fprintf(stderr, "(PC2) the value %d in the PC2 table occur too many times\n", i+1);
        exit(0);
      }
    }
    if(count<48)
    {
      fprintf(stderr, "(PC2) too few values read\n");
    exit(0);
  }
  if(count>48)
  {
    fprintf(stderr, "(PC2) too many values read\n");
    exit(0);
  }
  
    return flag;
}
int testPe(char * line)
{
  char *values;
  char s[2] = ",";
  int flag=0;
  values = strtok(line, s);
  int count=0;
  int i,i_value;
  int k=0;
  int p_ctr=0;
  struct num obj[32];
  for (i = 0; i < 32; ++i)
  {
    obj[i].number=i+1;
    obj[i].freq=0;  
  }
  
  while( values != NULL ) 
    {
      i_value=atoi(values);
      k++;
      if(i_value>=1 && i_value<=32)
      {
        obj[i_value-1].freq++;
        flag=1;
        p_arr[p_ctr++] = i_value;
      }
      else
      { flag=0;
        fprintf(stderr, "(P ) Contains invalid entries.\n");
      exit(0);
      }
      values = strtok(NULL, s);
      
      count++;
    }
    for(i=0;i<32;i++)
    {
      if(obj[i].freq>1)
      {

        fprintf(stderr, "(E) the value %d in the E table occur too many times\n", obj[i].number);
      }
      if (obj[i].freq==0)
      {
        fprintf(stderr, "(E) the value %d did not occur in the E table\n", obj[i].number);
      }
    }
    if(count<32)
    {
      fprintf(stderr, "(E) too few values read\n");
    exit(0);
  }
  if(count>32)
  {
    fprintf(stderr, "(E) too many values read\n");
    exit(0);
  }
  
    return flag;
}

void bintoHex(int * bin, int len) // converts binay string to hex
{
    int i=0, j=0, sum=0;
    while(i<len)
    {
        for(j=3;j>=0;j--)
        {
            sum = sum+pow(2,j)*(bin[i]);
            i++;
        }
        if(sum<10)
            fprintf(stderr, "%d", sum);
        else
        {
            char pr = (char)(sum+87);
            fprintf(stderr, "%c", pr);
        }
        sum = 0;
    }
   
}


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
char*  byte_to_binary(char  byte)
{
  
   int x = (int)byte;
    static char b[9];
    b[0] = '\0';

    int q;
    for (q = 128; q > 0; q >>= 1)
    {
        strcat(b, ((x & q) == q) ? "1" : "0");
    }

    return b;

}

char * dectobinstr(int s_val, char *output)
{
    int i;
    // char * output= malloc(sizeof(char)*5);
    // output[4] = '\0';
    for(i=3;i >= 0;--i, s_val>>= 1)
    {
        output[i] = (s_val & 1) + '0';
    }
    return output;
}

int binary_decimal(int * num) // converts binary string to decimal
{   
    int decimal_num = 0, base = 1, rem;
    //binary_num = num;
    int i;
    for(i=7;i>=0;i--)
    {
        rem = num[i];
        decimal_num = decimal_num + rem * base;
        //num = num / 10 ;
        base = base * 2;
    }
    return decimal_num;
}


int get_pos(int num) // returns position of number in the IP inverse table
{
    int i;
    for(i=0;i<64;i++)
    {
      if(ip[i]==num)
        return i;
    }
    return 0;
}
void test_table_encrypt(FILE *fp)
{
  
  int lines=0;
  //count number of lines in fp_key
  char ch;
  while((ch = fgetc(fp)) != EOF)
  {
    if(ch=='\n'|| ch==10 || ch=='\0')
    {
      lines++;
    }
    else if(ch==' ' || ch=='\t' )
        {
          fprintf(stderr, "Incorrect table file format\n" );
          exit(0);
        }
  }
  if(lines!=14)
  {
      fprintf(stderr, "Incorrect table file format\n" );
      exit(0);
  }
  rewind(fp);

  char * innertable;
  innertable=(char*)malloc(sizeof(char)*300);
  memset(innertable,99,300);//memset with 99

  char *t_key =(char*)malloc(sizeof(char)*4);
  memset(t_key,0,4);
  char *equal_pos;//pointer value of = position

  int equal_pos_i;//int value of = position
  int i;

  //testing the tablefile
  for(i=0;i<14;i++)
  {
    fgets(innertable,300,fp);
    equal_pos=strchr(innertable,'=');
    equal_pos_i = (int)(equal_pos-innertable);
    strncpy(t_key, innertable, equal_pos_i);

    t_key[equal_pos_i+1] = '\0';
    equal_pos++;//will contain the values
    t_key[equal_pos_i+1] = '\0';


    if(strncmp(t_key, "IP",2)==0 )
    {
        if(!testIPe(equal_pos))
        {
          fprintf(stderr, "IP table error!\n");

          exit(0);
        }
      }

      else if(strncmp(t_key, "E",1)==0)
      {

          if(!testEe(equal_pos))
          {
            fprintf(stderr, "E table error!\n");
            exit(0);
          }
      }
       
      else if(strncmp(t_key, "S", 1)==0)
      {
        //converting the type to int
        char *key_type=t_key;
        int type=(int)atoi(&key_type[1]);
        if(!testSe(equal_pos,type))
        {
          fprintf(stderr, "%s%d table error!\n",t_key,type);
          exit(0);
        }
      }
      else if(strncmp(t_key, "V", 1)==0)
      {
        if(!testVe(equal_pos))
        {
          fprintf(stderr, "V table error!\n" );
          exit(0);
        }
      }
      else if(strncmp(t_key, "PC1", 3)==0)
      {
        // f_isp = 0;
        if(!testPC1e(equal_pos))
        {
          fprintf(stderr, "PC1 table error!\n");
          exit(0);
        }
      }
      else if(strncmp(t_key, "PC2", 3)==0)
      {
        if(!testPC2e(equal_pos))
        {
          fprintf(stderr, "PC2 table error!\n");
          exit(0);
        }
      }
      else if(strncmp(t_key, "P", 1)==0)
      {

        if(!testPe(equal_pos))
        {
          fprintf(stderr, "P table error!\n");
          exit(0);
        }
      }
      else
      {
        fprintf(stderr, "Invalid table file\n");
      exit(0);
      }
      memset(t_key,0,4);
    memset(innertable,99,300);

  }
}
void generate_keys(int bin_key[64])
{
      int i;
  
      int C0[28]={0};
      for(i=0;i<28;i++)
      {
        C0[i]=bin_key[pc1a[i]-1];
      }
      
      fprintf(stderr, "(C0,D0)=");
      bintoHex(C0, 28);
    
      

      int D0[28]={0};
      for(i=0;i<28;i++)
      {
        D0[i]=bin_key[pc1b[i]-1];
      }
     
      bintoHex(D0, 28);
      
      fprintf(stderr, "\n");

    //================================== C1,D1=========================================
        int C1[28]={0};
        int D1[28]={0};
        for(i=0;i<28;i++)
        {
          C1[i] = C0[i];
          D1[i] = D0[i];
        }


        if(v_shift[0]==1)
        {
          int x,y;
          x=C1[0];
          y=D1[0];
          for(i=0;i<27;i++)
          {
            C1[i] = C1[i+1];
            D1[i] = D1[i+1];
          }
          C1[27]=x;
          D1[27]=y;

        }
        if(v_shift[0]==2)
        {
          int x,y;
          x=C1[0];
          y=D1[0];
          for(i=0;i<27;i++)
          {
            C1[i] = C1[i+1];
            D1[i] = D1[i+1];
          }
          C1[27]=x;
          D1[27]=y;

          x=C1[0];
          y=D1[0];
          for(i=0;i<27;i++)
          {
            C1[i] = C1[i+1];
            D1[i] = D1[i+1];
          }
          C1[27]=x;
          D1[27]=y;

        }
        
        fprintf(stderr, "(C1,D1)=");
        bintoHex(C1, 28);
        bintoHex(D1, 28);
                  
        //merge C1 and D1 into k1, then use PC2 to get 48 values out of 56 values, then print hex value
        int k1_temp[56]={0};
        int m,n;
        for(m=0;m<28;m++)
        {
          k1_temp[m]=C1[m];
        }
        for(m=0;m<28;m++)
        {
          k1_temp[m+28]=D1[m];
        }

        for(n=0;n<48;n++)
        {
          k[1][n]=k1_temp[pc2[n]-1];
        }
        
      fprintf(stderr, "\nk1=");
      bintoHex(k[1],48);
      fprintf(stderr, "\n" ); 
           
     //================================== C2,D2=========================================
        int C2[28]={0};
        int D2[28]={0};
        for(i=0;i<28;i++)
        {
          C2[i] = C1[i];
          D2[i] = D1[i];
        }


        if(v_shift[1]==1)
        {
          int x,y;
          x=C2[0];
          y=D2[0];
          for(i=0;i<27;i++)
          {
            C2[i] = C2[i+1];
            D2[i] = D2[i+1];
          }
          C2[27]=x;
          D2[27]=y;

        }
        if(v_shift[1]==2)
        {
          int x,y;
          x=C2[0];
          y=D2[0];
          for(i=0;i<27;i++)
          {
            C2[i] = C2[i+1];
            D2[i] = D2[i+1];
          }
          C2[27]=x;
          D2[27]=y;

          x=C2[0];
          y=D2[0];
          for(i=0;i<27;i++)
          {
            C2[i] = C2[i+1];
            D2[i] = D2[i+1];
          }
          C2[27]=x;
          D2[27]=y;

        }   

        fprintf(stderr, "(C2,D2)=");
        bintoHex(C2, 28);
        bintoHex(D2, 28);
        
        int k2_temp[56]={0};
        for(m=0;m<28;m++)
        {
          k2_temp[m]=C2[m];
        }
        for(m=0;m<28;m++)
        {
          k2_temp[m+28]=D2[m];
        }

        for(n=0;n<48;n++)
        {
          k[2][n]=k2_temp[pc2[n]-1];
        }
        
        fprintf(stderr, "\nk2=");
        bintoHex(k[2],48);
        fprintf(stderr, "\n" ); 
        
        //================================== C3,D3=========================================
        int C3[28]={0};
        int D3[28]={0};
        for(i=0;i<28;i++)
        {
          C3[i] = C2[i];
          D3[i] = D2[i];
        }


        if(v_shift[2]==1)
        {
          int x,y;
          x=C3[0];
          y=D3[0];
          for(i=0;i<27;i++)
          {
            C3[i] = C3[i+1];
            D3[i] = D3[i+1];
          }
          C3[27]=x;
          D3[27]=y;

        }
        if(v_shift[2]==2)
        {
          int x,y;
          x=C3[0];
          y=D3[0];
          for(i=0;i<27;i++)
          {
            C3[i] = C3[i+1];
            D3[i] = D3[i+1];
          }
          C3[27]=x;
          D3[27]=y;

          x=C3[0];
          y=D3[0];
          for(i=0;i<27;i++)
          {
            C3[i] = C3[i+1];
            D3[i] = D3[i+1];
          }
          C3[27]=x;
          D3[27]=y;

        } 
        
        fprintf(stderr, "(C3,D3)=");
        bintoHex(C3, 28);
        bintoHex(D3, 28);
        
        int k3_temp[56]={0};
        for(m=0;m<28;m++)
        {
          k3_temp[m]=C3[m];
        }
        for(m=0;m<28;m++)
        {
          k3_temp[m+28]=D3[m];
        }

        for(n=0;n<48;n++)
        {
          k[3][n]=k3_temp[pc2[n]-1];
        }
    
        fprintf(stderr, "\nk3=");
        bintoHex(k[3],48);
        fprintf(stderr, "\n" );
      

        //================================== C4,D4=========================================
        int C4[28]={0};
        int D4[28]={0};
        for(i=0;i<28;i++)
        {
          C4[i] = C3[i];
          D4[i] = D3[i];
        }


        if(v_shift[3]==1)
        {
          int x,y;
          x=C4[0];
          y=D4[0];
          for(i=0;i<27;i++)
          {
            C4[i] = C4[i+1];
            D4[i] = D4[i+1];
          }
          C4[27]=x;
          D4[27]=y;

        }
        if(v_shift[3]==2)
        {
          int x,y;
          x=C4[0];
          y=D4[0];
          for(i=0;i<27;i++)
          {
            C4[i] = C4[i+1];
            D4[i] = D4[i+1];
          }
          C4[27]=x;
          D4[27]=y;

          x=C4[0];
          y=D4[0];
          for(i=0;i<27;i++)
          {
            C4[i] = C4[i+1];
            D4[i] = D4[i+1];
          }
          C4[27]=x;
          D4[27]=y;

        }   
        
        fprintf(stderr, "(C4,D4)=");
        bintoHex(C4, 28);
        bintoHex(D4, 28);
        
        int k4_temp[56]={0};
        for(m=0;m<28;m++)
        {
          k4_temp[m]=C4[m];
        }
        for(m=0;m<28;m++)
        {
          k4_temp[m+28]=D4[m];
        }

        for(n=0;n<48;n++)
        {
          k[4][n]=k4_temp[pc2[n]-1];
        }
    
        fprintf(stderr, "\nk4=");
        bintoHex(k[4],48);
        fprintf(stderr, "\n" ); 
        
        
        //================================== C5,D5=========================================
        int C5[28]={0};
        int D5[28]={0};
        for(i=0;i<28;i++)
        {
          C5[i] = C4[i];
          D5[i] = D4[i];
        }

        if(v_shift[4]==1)
        {
          int x,y;
          x=C5[0];
          y=D5[0];
          for(i=0;i<27;i++)
          {
            C5[i] = C5[i+1];
            D5[i] = D5[i+1];
          }
          C5[27]=x;
          D5[27]=y;

        }
        if(v_shift[4]==2)
        {
          int x,y;
          x=C5[0];
          y=D5[0];
          for(i=0;i<27;i++)
          {
            C5[i] = C5[i+1];
            D5[i] = D5[i+1];
          }
          C5[27]=x;
          D5[27]=y;

          x=C5[0];
          y=D5[0];
          for(i=0;i<27;i++)
          {
            C5[i] = C5[i+1];
            D5[i] = D5[i+1];
          }
          C5[27]=x;
          D5[27]=y;

        } 
         
        fprintf(stderr, "(C5,D5)=");
        bintoHex(C5, 28);
        bintoHex(D5, 28);
        
        int k5_temp[56]={0};
        for(m=0;m<28;m++)
        {
          k5_temp[m]=C5[m];
        }
        for(m=0;m<28;m++)
        {
          k5_temp[m+28]=D5[m];
        }

        for(n=0;n<48;n++)
        {
          k[5][n]=k5_temp[pc2[n]-1];
        }
        
        fprintf(stderr, "\nk5=");
        bintoHex(k[5],48);
        fprintf(stderr, "\n" );
        

        //================================== C6,D6=========================================
        int C6[28]={0};
        int D6[28]={0};
        for(i=0;i<28;i++)
        {
          C6[i] = C5[i];
          D6[i] = D5[i];
        }

        if(v_shift[5]==1)
        {
          int x,y;
          x=C6[0];
          y=D6[0];
          for(i=0;i<27;i++)
          {
            C6[i] = C6[i+1];
            D6[i] = D6[i+1];
          }
          C6[27]=x;
          D6[27]=y;

        }
        if(v_shift[5]==2)
        {
          int x,y;
          x=C6[0];
          y=D6[0];
          for(i=0;i<27;i++)
          {
            C6[i] = C6[i+1];
            D6[i] = D6[i+1];
          }
          C6[27]=x;
          D6[27]=y;

          x=C6[0];
          y=D6[0];
          for(i=0;i<27;i++)
          {
            C6[i] = C6[i+1];
            D6[i] = D6[i+1];
          }
          C6[27]=x;
          D6[27]=y;

        }   
       
        fprintf(stderr, "(C6,D6)=");
        bintoHex(C6, 28);
        bintoHex(D6, 28);
        
        int k6_temp[56]={0};
        for(m=0;m<28;m++)
        {
          k6_temp[m]=C6[m];
        }
        for(m=0;m<28;m++)
        {
          k6_temp[m+28]=D6[m];
        }

        for(n=0;n<48;n++)
        {
          k[6][n]=k6_temp[pc2[n]-1];
        }
       
        fprintf(stderr, "\nk6=");
        bintoHex(k[6],48);
        fprintf(stderr, "\n" ); 
      

        //================================== C7,D7=========================================
        int C7[28]={0};
        int D7[28]={0};
        for(i=0;i<28;i++)
        {
          C7[i] = C6[i];
          D7[i] = D6[i];
        }


        if(v_shift[6]==1)
        {
          int x,y;
          x=C7[0];
          y=D7[0];
          for(i=0;i<27;i++)
          {
            C7[i] = C7[i+1];
            D7[i] = D7[i+1];
          }
          C7[27]=x;
          D7[27]=y;

        }
        if(v_shift[6]==2)
        {
          int x,y;
          x=C7[0];
          y=D7[0];
          for(i=0;i<27;i++)
          {
            C7[i] = C7[i+1];
            D7[i] = D7[i+1];
          }
          C7[27]=x;
          D7[27]=y;

          x=C7[0];
          y=D7[0];
          for(i=0;i<27;i++)
          {
            C7[i] = C7[i+1];
            D7[i] = D7[i+1];
          }
          C7[27]=x;
          D7[27]=y;

        }   
        
        fprintf(stderr, "(C7,D7)=");
        bintoHex(C7, 28);
        bintoHex(D7, 28);
        
        int k7_temp[56]={0};
        for(m=0;m<28;m++)
        {
          k7_temp[m]=C7[m];
        }
        for(m=0;m<28;m++)
        {
          k7_temp[m+28]=D7[m];
        }

        for(n=0;n<48;n++)
        {
          k[7][n]=k7_temp[pc2[n]-1];
        }
       
        fprintf(stderr, "\nk7=");
        bintoHex(k[7],48);
        fprintf(stderr, "\n" ); 
        

