#include<stdio.h>
#include<ctype.h>
int main(void)
{
printf("Input base64 code: ");
char input[101];
char output[101]={0};
scanf("%100s",input);
char ch;
int cin=0;
_Bool isquit=0;
while(1)
{
    //judge if quit
    if(input[cin]=='\0'||input[cin]=='=')
    {
        output[(cin*3)/4]='\0';
        break;
    }
    //convert to base64
    ch=input[cin];
    if(isupper(ch)){
        ch=ch-'A';
    }else if(islower(ch)){
        ch=ch-'a'+26;
    }else if(isdigit(ch)){
        ch=ch-'0'+52;
    }else if(ch=='+'){
        ch=62;
    }else if(ch=='/'){
        ch=63;
    }else
    {
        printf("Can't find this value in base64!\n");
        isquit=1;
        break;
    }
    //set 6 to 8
    if(cin%4==0){
        output[(cin/4)*3]   |=(ch<<2);
    }else if(cin%4==1){
        output[(cin/4)*3]   |=(ch>>4);
        output[(cin/4)*3+1] |=(ch<<4);
    }else if(cin%4==2){
        output[(cin/4)*3+1] |=(ch>>2);
        output[(cin/4)*3+2] |=(ch<<6);
    }else if(cin%4==3){
        output[(cin/4)*3+2] |=ch;
    }
    cin++;
}
if(isquit)
    return 1;
printf("%s\n",output);
return 0;
}
