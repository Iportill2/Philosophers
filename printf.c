#include <stdarg.h>
#include <unistd.h>

size_t ft_strlen(const char *s)
{
    size_t i =0;
    while(s[i])
        i++;
    return(i);
}
int printf_c(int c)
{
    write(1,&c,1);
    return(1);
}
int printf_s(const char *s)
{
    int i =0;
    if(s == NULL)
    {
        write(1,"(null)",6);
        return(6);
    }
    
    i = write(1,s,ft_strlen(s));
    return(i);
}
int printf_d(int n)
{
    char *s="0123456789";
    int lenght =0;
    if(n == -2147483648)
    {
        write(1,"-2147483648",11);
        return(11);
    }
    if(n < 0)
    {
        n = n * -1;
        write(1,"-",1);
        lenght++;
    }
    if(n > 9)
        lenght +=printf_d(n/10);
    lenght +=write(1,&s[n%10],1);
    return(lenght);
}

int printf_x(unsigned int n)
{
    char *s="0123456789abcdef";
    int lenght =0;

    if(n > 15)
        lenght +=printf_x(n/16);
    lenght +=write(1,&s[n%16],1);
    return(lenght);
}
int ft_format(va_list args,const char c)
{
    int lenght = 0;
    if( c =='s')
        lenght += printf_s(va_arg(args,char *));
    else if( c =='d')
        lenght += printf_d(va_arg(args,int));
    else if( c =='x')
        lenght += printf_x(va_arg(args,unsigned int));
    return(lenght);
}

int ft_printf(const char *s,...)
{
    int lenght =0;
    int i =0;
    va_list(args);
    va_start(args,s);
    while(s[i])
    {
        if(s[i] == '%')
        {
            lenght += ft_format(args,s[i+1]);
            i++;
        }
        else
        {
            lenght += printf_c(s[i]);
        }
        i++;
    }
    va_end(args);
    return(lenght);
}
#include <stdio.h>
int main()
{
    char *s = NULL;
    int i =0;
    int e =0;
    i +=ft_printf("ft=%s\n",s);
    i +=ft_printf("ft=%s\n","hola");
    i +=ft_printf("ft=%x\n",42);
    i +=ft_printf("ft=%d\n",i);

    e +=printf("pr=%s\n",s);
    e +=printf("pr=%s\n","hola");
    e +=printf("pr=%x\n",42);
    e +=printf("pr=%d\n",e);
}
