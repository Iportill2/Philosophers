/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:51:03 by iportill          #+#    #+#             */
/*   Updated: 2023/12/27 18:23:37 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void* ft_calloc(size_t num, size_t size) 
{
    void* ptr = malloc(num * size);
    if (ptr == NULL) 
        return NULL;
    memset(ptr, 0, num * size);
    return (ptr);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		num = (str[i] - 48) + (num * 10);
		i++;
	}
	return (num * sign);
}
static int check_argv_num(t_list *d,char *argv,int pos)
{
	(void)d;
	(void)argv;
	int n = 0;
	n = ft_atoi(argv);
	printf("POS = [%d] \nN = [%d]\n",pos,n);
	if(!n || n < 0 || (pos == 1 && n > 200) || (pos == 2 && n < 60) || (pos ==3 && n < 60) ||
	(pos == 4 && n < 60))
	{
		free(d);
		printf("Incorrect Values\n");
		return(1);
	}
	else
	{
		if(pos == 1)
			d->num_philo = n;
		if(pos == 2)
			d->time_to_die = n;
		if(pos == 3)
			d->time_to_eat = n;
		if(pos == 4)
			d->time_to_sleep = n;
		if(pos == 5)
			d->philo_eats = n;
	}
	return(n);	
}
void set_struct(int argc,char **argv)
{
	t_list *d;
	(void)argc;
	d = ft_calloc(1,sizeof(t_list));
	int i=1;

	while(i != argc)
	{
		if(check_argv_num(d,argv[i],i) < 0)
			return;
		i++;
	}
	
	printf("d->num_philo = [%ld]\n",d->num_philo);
	printf("d->time_to_die = [%ld]\n",d->time_to_die);
	printf("d->time_to_eat = [%ld]\n",d->time_to_eat);
	printf("d->time_to_sleep = [%ld]\n",d->time_to_sleep);
	if(d->philo_eats != 0)
		printf("d->philo_eats = [%ld]\n",d->philo_eats);
	return;
	/* d->num_philo = ft_atoi(argv[1]);
	d->time_to_die = ft_atoi(argv[2]);
	d->time_to_eat = ft_atoi(argv[3]);
	d->time_to_sleep = ft_atoi(argv[4]); */
	
	/* if(argv[5] == NULL)
		d->philo_eats = ft_atoi(argv[6]); */
	
	/* printf("[%ld]\n",d->num_philo);
	printf("[%ld]\n",d->time_to_die);
	printf("[%ld]\n",d->time_to_eat);
	printf("[%ld]\n",d->time_to_sleep); */
	/* if(argv[5] == NULL)
		printf("[%ld]\n",d->num_philo); */

}