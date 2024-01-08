#include <stdarg.h>
#include <unistd.h>

size_tft_strlen(const char *s)
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
int ft_format(va_list args,const char c)
{
    int lenght = 0;
    if( c =='s')
        lenght += printf_s(va_arg(args,char *));
    else if( c =='d')
        lenght += printf_s(va_arg(args,int));
    else if( c =='x')
        lenght += printf_s(va_arg(args,unsigned int));
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

        }
        else
        {

        }
    }
    va_end(args);
    return(lenght);
}
