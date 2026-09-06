#include<stdio.h>
#include<ctype.h>
char*s_gets(char*st,int n);
int main(void)
{
printf("Input a string: ");
char input[101];
//scanf("%100s",input);
s_gets(input,100);
int cin=0;
_Bool isend=0;
for(;input[cin]!='\0';cin++);
int cinmax=cin;
cin=0;
char output[101]={0};
int cout=0;
while(cin<cinmax)
{
if(cout%4==0){
    output[cout]=((unsigned int)252 & input[cin])>>2;//252=(1111 1100)
    cin--;
}else if(cout%4==1){
    output[cout]=((unsigned int)3 & input[cin])<<4;//3=(0000 0011)
    output[cout] |=((unsigned int)240 & input[cin+1])>>4;//240=(1111 0000)
}else if(cout%4==2){
    output[cout]=((unsigned int)15 & input[cin])<<2;//15=(0000 1111)
    output[cout] |=((unsigned int)192 & input[cin+1])>>6;//192=(1100 0000)
}else if(cout%4==3){
    output[cout]=((unsigned int)63 & input[cin]);//63=(0011 1111)
}
cout++;
cin++;
}
for(int i=0;i<cout;i++)
{
    if(output[i]<=25){
        printf("%c",'A'+output[i]);
    }else if(output[i]<=51){
        printf("%c",'a'+output[i]-26);
    }else if(output[i]<=61){
        printf("%c",output[i]-52+'0');
    }else if(output[i]==62){
        printf("+");
    }else if(output[i]==63){
        printf("/");
    }
}
//the result must be a multiple of 4
while(cout%4!=0){
printf("=");
cout++;
}
puts("");
return 0;
}

char*s_gets(char*st,int n)
{
char* ret_val;
char ch;
ret_val=fgets(st,n,stdin);
if(ret_val)
{
    while(*st!='\n' && *st!='\0')
        st++;
    if(*st=='\n')
        *st='\0';
    else
        while(getchar()!='\n');
}
return ret_val;
}
