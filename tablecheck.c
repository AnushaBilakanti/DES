#include "functions.h"

struct num
{
	int number;
	int freq;
};

int x;

struct num S[16];// for S-boxes


int testIP(char * line)
{
	char *values;
	char s[2] = ",";
	int flag=0;
	values = strtok(line, s);
	int count=0;
	int i_value;
	struct num obj[64];
	int i;
	for(i = 0; i < 64; ++i)
	{
		obj[i].number=i+1;
		obj[i].freq=0;	
	}
	while( values != NULL ) 
   	{
   		i_value=atoi(values);
   		if(i_value>=1 && i_value<=64)
   		{
   			obj[i_value-1].freq++;
   			flag=1;
   		}
   		else
   		{	flag=0;
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
        exit(0);
   		}
   		if (obj[i].freq==0)
   		{
   			fprintf(stderr, "(IP) the value %d did not occur in the IP table\n", obj[i].number);
        exit(0);
        
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


int testE(char * line)
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
   		
   		k++;
   		if(i_value>=1 && i_value<=32)
   		{
   			obj[i_value-1].freq++;
   			flag=1;
   		}
   		else
   		{	flag=0;
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
        exit(0);
   		}
   		if (obj[i].freq==0)
   		{
   			fprintf(stderr, "(E) the value %d did not occur in the E table\n", obj[i].number);
        exit(0);
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
int testP(char * line)
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
   		k++;
   		if(i_value>=1 && i_value<=32)
   		{
   			obj[i_value-1].freq++;
   			flag=1;
   		}
   		else
   		{	flag=0;
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

   			fprintf(stderr, "(P) the value %d in the E table occur too many times\n", obj[i].number);
        exit(0);
   		}
   		if (obj[i].freq==0)
   		{
   			fprintf(stderr, "(P) the value %d did not occur in the E table\n", obj[i].number);
        exit(0);
   		}
   	}
   	if(count<32)
   	{
   		fprintf(stderr, "(P) too few values read\n");
      exit(0);
	}
	if(count>32)
	{
		fprintf(stderr, "(P) too many values read\n");
		exit(0);
	}
  
   	return flag;
}
int testS(char * line, int type)
{
	if(type<1 || type>8)
	{
		fprintf(stderr, "S%d exceeding limit. \n", type);
		exit(0);
	}
	// int type=1;
	char *values;
	char s[2] = ",";
	int flag=0;
	values = strtok(line, s);
	int count=0;
	int i,i_value;
	int k=0;

	int Sbox[4][16];
	memset(Sbox,99,16*4);
	for(x=0;x<16;x++)
	{
		S[x].number=x;
		S[x].freq=0;
	}
	int S_lines=0;
	while( values != NULL ) 
   	{
   		i_value=atoi(values);
   		Sbox[S_lines][k]=i_value;
   		k++;
   		if(i_value>=0 && i_value<=15)
   		{
   			S[i_value].freq++;
   			flag=1;
   		}
   		else
   		{	flag=0;
   			fprintf(stderr, "(S%d ) Contains invalid entries.\n",type);
			exit(0);
   		}
   		values = strtok(NULL, s);
   		if(k==16)
   		{	
   			k=0;
   			S_lines++;
   		}
   		count++;
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
int testV(char * line)
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
   		k++;
   		if(i_value>=1 && i_value<=2)
   		{
   			obj[i_value-1].freq++;
   			flag=1;
   		}
   		else
   		{	flag=0;
   			fprintf(stderr, "(V ) Contains invalid entries.\n");
			exit(0);
   		}
   		values = strtok(NULL, s);
   		
   		count++;
   	}
   	
	if(obj[0].freq!=4)
	{
		fprintf(stderr, "(V) the value %d in the V table did not occur 4 times\n", obj[0].number);
    exit(0);
	}
	if (obj[1].freq!=12)
	{
		fprintf(stderr, "(V) the value %d in the V table did not occur 12 times\n", obj[1].number);
    exit(0);
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

int testPC1(char * line)
{
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
   			}
   			else
   			{
   				flag=0;
				break;
   			}
   			
   		}
   		else
   		{	flag=0;
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

int testPC2(char * line)
{
	char *values;
	char s[2] = ",";
	int flag=0;
	values = strtok(line, s);
	int count=0;
	int i,i_value;
	int obj[56]={0};
	
	while( values != NULL ) 
   	{
   		i_value=atoi(values);
   		
   		if(i_value>=1 && i_value<=56)
   		{
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

void tablecheck(char *tablefile)
{

	//count number of lines in file
	int lines=0;
	//count number of lines in fp_key
		char ch;
		FILE *fp;
	  	if(tablefile!=NULL)
	  	{
	      	fp=fopen(tablefile,"rb");
	  	}
		else
		{
		    fp=stdin;
		}
		if(fp==NULL)
	  	{
	    	fprintf(stderr, "Error opening file\n");
	    	exit(0);
	 	}



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

	char *key =(char*)malloc(sizeof(char)*4);
	memset(key,0,4);
	int i;
	char *equal_pos;//pointer value of = position

	int equal_pos_i;//int value of = position

	//getting the keys
	for(i=0;i<14;i++)
	{
		fgets(innertable,300,fp);
		equal_pos=strchr(innertable,'=');
		equal_pos_i = (int)(equal_pos-innertable);
		strncpy(key, innertable, equal_pos_i);

		key[equal_pos_i+1] = '\0';
		equal_pos++;//will contain the values
		key[equal_pos_i+1] = '\0';


		if(strncmp(key, "IP",2)==0 )
		{
    		if(!testIP(equal_pos))
    		{
    			fprintf(stderr, "IP table error!\n");

    			exit(0);
    		}
    	}

    	else if(strncmp(key, "E",1)==0)
    	{

    			if(!testE(equal_pos))
    			{
    				fprintf(stderr, "E table error!\n");
    				exit(0);
    			}
    	}
    	 
    	else if(strncmp(key, "S", 1)==0)
    	{
    		//converting the type to int
    		char *key_type=key;
    		int type=(int)atoi(&key_type[1]);
    		if(!testS(equal_pos,type))
    		{
    			fprintf(stderr, "%s%d table error!\n",key,type);
    			exit(0);
    		}
    	}
    	else if(strncmp(key, "V", 1)==0)
    	{
    		if(!testV(equal_pos))
    		{
    			fprintf(stderr, "V table error!\n" );
    			exit(0);
    		}
    	}
    	else if(strncmp(key, "PC1", 3)==0)
    	{
    		// f_isp = 0;
    		if(!testPC1(equal_pos))
    		{
    			fprintf(stderr, "PC1 table error!\n");
    			exit(0);
    		}
    	}
    	else if(strncmp(key, "PC2", 3)==0)
    	{
    		if(!testPC2(equal_pos))
    		{
    			fprintf(stderr, "PC2 table error!\n");
    			exit(0);
    		}
    	}
    	else if(strncmp(key, "P", 1)==0)
    	{

    		if(!testP(equal_pos))
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
    	memset(key,0,4);
		memset(innertable,99,300);

	}
}
