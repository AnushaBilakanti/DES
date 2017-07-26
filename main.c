#include "functions.h"

int main(int argc, char const *argv[])
{

	char *tablefile;
	char *key;//key is in char
	
	int len,i;
	if(argc==1)
    {
        fprintf(stderr, "Error: Information given is not enough.\n");
        exit(0);
    }
    else
    {
    	if(strcmp(argv[1], "tablecheck")==0)
        {	
        	if(argc!=3)
        	{
        		fprintf(stderr, "Error: Malformed command. Please enter in the following format \nhw4 tablecheck -t=tablefile\n");
                exit(0);
        	}
        	else
        	{
 
        		if(argv[2][1]=='t')
                {
                    tablefile = strchr(argv[2], '=');
                  
                    tablefile++;
                }
             
                tablecheck(tablefile);

        	}
        }
        else if(strcmp(argv[1], "encrypt")==0)
        {
        	if(argc<4)
        	{
        		fprintf(stderr, "Error: Malformed command. Please enter in the following format \nhw4 encrypt -k=key -t=tablefile [file]\n");
                exit(0);	
        	}
        	if(argc==4)
        	{
        		if(argv[2][1]=='k')
        		{
        			key = strchr(argv[2], '=');
        			key++;
                    len=strlen(key);
                    if(len!=16)
                    {
                        fprintf(stderr, "Key  error!\n");
                        exit(0);
                    }
                    for(i=0;i<len;i++)
                    {
                        if(!( ( (key[i]>='a') && (key[i]<='f') ) || ( (key[i]>='0') && (key[i]<='9') )  ))
                        {
                            fprintf(stderr, "Invalid  key.\n");
                            exit(0);;
                        }  
                       
                    }    
        		}
        		if(argv[3][1]=='t')
                {
                    tablefile = strchr(argv[3], '=');
                    tablefile++;
                }
                FILE * fp;
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
                tablecheck(tablefile);
                read_encryption(fp,key, NULL, 1);
        	}
        	else if(argc==5)
        	{
        		if(argv[2][1]=='k')
        		{
                    
        			key = strchr(argv[2], '=');
        			key++;
                    len=strlen(key);
                    if(len!=16)
                    {
                        fprintf(stderr, "Key error!\n");
                        exit(0);
                    }
                    for(i=0;i<len;i++)
                    {
                        if(!( ( (key[i]>='a') && (key[i]<='f') ) || ( (key[i]>='0') && (key[i]<='9') )  ))
                        {
                            fprintf(stderr, "Invalid key.\n");
                            exit(0);;
                        }  
                       
                    }    
        		}
        		if(argv[3][1]=='t')
                {
                    tablefile = strchr(argv[3], '=');
                    tablefile++;
                }
                FILE * fp;
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
                tablecheck(tablefile);
                read_encryption(fp,key, argv[4], 1);
        	}
        }
        else if(strcmp(argv[1], "decrypt")==0)
        {
            if(argc<4)
            {
                fprintf(stderr, "Error: Malformed command. Please enter in the following format \nhw4 decrypt -k=key -t=tablefile [file]\n");
                exit(0);    
            }
            if(argc==4)
            {
                if(argv[2][1]=='k')
                {
                    key = strchr(argv[2], '=');
                    key++;
                    len=strlen(key);
                    if(len!=16)
                    {
                        fprintf(stderr, "Key error!\n");
                        exit(0);
                    }
                    for(i=0;i<len;i++)
                    {
                        if(!( ( (key[i]>='a') && (key[i]<='f') ) || ( (key[i]>='0') && (key[i]<='9') )  ))
                        {
                            fprintf(stderr, "Invalid key.\n");
                            exit(0);;
                        }  
                       
                    }    
                }
                if(argv[3][1]=='t')
                {
                    tablefile = strchr(argv[3], '=');
                    tablefile++;
                }
                FILE * fp;
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
                tablecheck(tablefile);
                read_encryption(fp,key, NULL, 2);
                
            }
            else if(argc==5)
            {
                if(argv[2][1]=='k')
                {
                    key = strchr(argv[2], '=');
                    key++;
                    len=strlen(key);
                    if(len!=16)
                    {
                        fprintf(stderr, "Key error!\n");
                        exit(0);
                    }
                    for(i=0;i<len;i++)
                    {
                        if(!( ( (key[i]>='a') && (key[i]<='f') ) || ( (key[i]>='0') && (key[i]<='9') )  ))
                        {
                            fprintf(stderr, "Invalid  key.\n");
                            exit(0);
                        }  
                       
                    }    
                }
                if(argv[3][1]=='t')
                {
                    tablefile = strchr(argv[3], '=');
                    tablefile++;
                }
                FILE * fp;
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
                tablecheck(tablefile);
                read_encryption(fp,key, argv[4], 2);
            }
        }
        else if(strcmp(argv[1], "encrypt3")==0)
        {
            if(argc<4)
            {
                fprintf(stderr, "Error: Malformed command. Please enter in the following format \nhw4 decrypt -k=key -t=tablefile [file]\n");
                exit(0);    
            }
            if(argc==4)
            {
                if(argv[2][1]=='k')
                {
                    key = strchr(argv[2], '=');
                    key++;
                    len=strlen(key);
                    if(len<48)
                    {
                        fprintf(stderr, "Key too short!\n");
                        exit(0);
                    }
                    else if(len>48)
                    {
                        fprintf(stderr, "Key too long!\n");
                        exit(0);
                    }
                    for(i=0;i<len;i++)
                    {
                        if(!( ( (key[i]>='a') && (key[i]<='f') ) || ( (key[i]>='0') && (key[i]<='9') )  ))
                        {
                            fprintf(stderr, "Invalid key.\n");
                            exit(0);;
                        }  
                       
                    }    
                }
                if(argv[3][1]=='t')
                {
                    tablefile = strchr(argv[3], '=');
                    tablefile++;
                }
                FILE * fp;
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
                // tablecheck(tablefile);
                read_encryption(fp,key, NULL, 3);
            }
            else if(argc==5)
            {
                if(argv[2][1]=='k')
                {
                    key = strchr(argv[2], '=');
                    key++;
                    len=strlen(key);
                    if(len<48)
                    {
                        fprintf(stderr, "Key too short!\n");
                        exit(0);
                    }
                    else if(len>48)
                    {
                        fprintf(stderr, "Key too long!\n");
                        exit(0);
                    }
                    for(i=0;i<len;i++)
                    {
                        if(!( ( (key[i]>='a') && (key[i]<='f') ) || ( (key[i]>='0') && (key[i]<='9') )  ))
                        {
                            fprintf(stderr, "Invalid  key.\n");
                            exit(0);;
                        }  
                       
                    }    
                }
                if(argv[3][1]=='t')
                {
                    tablefile = strchr(argv[3], '=');
                    tablefile++;
                }
                FILE * fp;
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
                // tablecheck(tablefile);
                read_encryption(fp,key, argv[4], 3);
                
            }
        }
        else if(strcmp(argv[1], "decrypt3")==0)
        {
            if(argc<4)
            {
                fprintf(stderr, "Error: Malformed command. Please enter in the following format \nhw4 decrypt -k=key -t=tablefile [file]\n");
                exit(0);    
            }
            if(argc==4)
            {
                if(argv[2][1]=='k')
                {
                    key = strchr(argv[2], '=');
                    key++;
                    len=strlen(key);
                    if(len<48)
                    {
                        fprintf(stderr, "Key too short!\n");
                        exit(0);
                    }
                    else if(len>48)
                    {
                        fprintf(stderr, "Key too long!\n");
                        exit(0);
                    }
                    for(i=0;i<len;i++)
                    {
                        if(!( ( (key[i]>='a') && (key[i]<='f') ) || ( (key[i]>='0') && (key[i]<='9') )  ))
                        {
                            fprintf(stderr, "Invalid key.\n");
                            exit(0);;
                        }  
                       
                    }    
                }
                if(argv[3][1]=='t')
                {
                    tablefile = strchr(argv[3], '=');
                    tablefile++;
                }
                FILE * fp;
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
                tablecheck(tablefile);
                read_encryption(fp,key, NULL, 4);
            }
            else if(argc==5)
            {
                if(argv[2][1]=='k')
                {
                    key = strchr(argv[2], '=');
                    key++;
                    len=strlen(key);
                    if(len<48)
                    {
                        fprintf(stderr, "Key too short!\n");
                        exit(0);
                    }
                    else if(len>48)
                    {
                        fprintf(stderr, "Key too long!\n");
                        exit(0);
                    }
                    for(i=0;i<len;i++)
                    {
                        if(!( ( (key[i]>='a') && (key[i]<='f') ) || ( (key[i]>='0') && (key[i]<='9') )  ))
                        {
                            fprintf(stderr, "Invalid  key.\n");
                            exit(0);;
                        }  
                       
                    }    
                }
                if(argv[3][1]=='t')
                {
                    tablefile = strchr(argv[3], '=');
                    tablefile++;
                }
                FILE * fp;
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
                tablecheck(tablefile);
                read_encryption(fp,key, argv[4], 4);
            }
        }
        else if(!((strcmp(argv[1], "decrypt3")==0) || (strcmp(argv[1], "encrypt3")==0) || 
            (strcmp(argv[1], "decrypt")==0) || (strcmp(argv[1], "encrypt")==0)|| 
            (strcmp(argv[1], "tablecheck")==0)))
        {
            fprintf(stderr, "Malformed command\n");
            exit(0);
        }

    }//else(argc!=1)
	
	return 0;
}
