#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#define min(a,b) (((a) < (b)) ? (a) : (b))
struct stack{    	      
	int top;    		 
	char data[2000];	 
	int loc[2000];  	
};
struct stack s,ss;      
char a[2000];            
char *p,*pp,ch;         
int i,j,line=0,flag=0,len;  
void check()
{
	p=strstr(a,"//"); 
	pp=strstr(a,"/*");
	if(p==NULL && pp==NULL)
	{
		len=strlen(a);
	}
	else if(p==NULL && pp!=NULL)
	{
		len=pp-a;
	}
	else if(p!=NULL && pp==NULL)
	{
		len=p-a;
	}
	else if(p!=NULL && pp!=NULL)
	{
		len=min(p-a,pp-a);
	}
	for(i=0;i<len;i++)
	{
		if(a[i]=='(')          
		{
			s.data[s.top]='(';  
			ss.data[ss.top]='(';
			s.loc[s.top]=line;  
			s.top++,ss.top++;
		}
		else if(a[i]==')')
		{
			ss.data[ss.top]=')'; 
			ss.top++;
			if(s.data[s.top-1]=='(')  
			{
				s.top--;     
			}
			else
			{
				ch=')';   
				flag=1;   
				break;
			}
		}
		else if(a[i]=='{')
		{
			ss.data[ss.top]='{';
			ss.top++;
			if(s.data[s.top-1]!='(')  
			{
				s.data[s.top]='{';
				s.loc[s.top]=line;
				s.top++;
			}
			else
			{
				ch='(';  
				flag=1; 
				break;
			}
		}
		else if(a[i]=='}')
		{
			ss.data[ss.top]='}';
			ss.top++;
			if(s.data[s.top-1]=='{')
			{
				s.top--; 
			}
			else
			{
				ch='}'; 
				flag=1; 
				break;
			}
		}
		else if(a[i]==39) 
		{
			p=strchr(a+i+1,39);
			if(p!=NULL) i=p-a; 
			else continue;
		}
		else if(a[i]==34) 
		{
			p=strchr(a+i+1,34);
			if(p!=NULL) i=p-a;
			else continue;
		}
	}
}

int main()
{	
	FILE *in = fopen("example.c","r");
	s.top=0,ss.top=0;             
	while (fgets(a,2000,in) != NULL)
	{
		line++;                   
		check();                 
		if(flag==1)                
		{
			if(ch=='(')           
					printf("without maching '%c' at line %d",ch,s.loc[s.top-1]);
			else	printf("without maching '%c' at line %d",ch,line);
			break;
		}
	}
	if(flag==0)       
	{
		if(s.top==0)         
		{
			puts(ss.data);   
		}
		else  
		{ 
			printf("without maching '%c' at line %d",s.data[s.top-1],s.loc[s.top-1]);
		}
	} 
	
	return 0;
}

