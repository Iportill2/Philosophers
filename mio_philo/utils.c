#include "philo.h"
#include <stdlib.h>
#include <string.h>

void* ft_calloc(size_t num, size_t size) 
{
    void* ptr = malloc(num * size);
    if (ptr == NULL) 
        return NULL;
    memset(ptr, 0, num * size);
    return (ptr);
}

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if(s== NULL)
		return(0);
	while (s[i])
		i++;
	return(i);
	
}

char *ft_strdup(const char *s) 
{
    char *dup;
	size_t i;

	i = 0;
	dup = NULL;
	dup = ft_calloc(sizeof(char),ft_strlen(s) + 1);
    while(s[i])
	{
		dup[i]=s[i];
		i++;
	}
	dup[i]='\0';
    return (dup);
}

int	ft_spaces(char c)
{
	if(c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return(1);
	else
		return(0);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				valorfinal;
	long long int	nbr;

	nbr = 0;
	i = 0;
	valorfinal = 1;
	while (str[i] && ft_spaces(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			valorfinal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
		if (nbr < INT_MIN && valorfinal == -1)
			return (0);
		if (nbr > INT_MAX && valorfinal == 1)
			return (-1);
	}
	return (nbr * valorfinal);
}