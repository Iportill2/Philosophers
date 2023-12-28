/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:51:03 by iportill          #+#    #+#             */
/*   Updated: 2023/12/28 16:52:42 by iportill         ###   ########.fr       */
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
int check_argv_num(t_list *d,char *argv,int pos)
{
	int value = 0;
	value = ft_atoi(argv);
	printf("POS = [%d] \nN = [%d]\n",pos,value);
	if(value == 0 || value < 0 || (pos == 1 && value > 200) || (pos == 2 && value < 60) || (pos ==3 && value < 60) ||
	(pos == 4 && value < 60))
	{
		free(d);
		d = NULL;
		printf("Incorrect Values\n");
		return(1);
	}
	else
	{
		if(pos == 1)
			d->num_philo = value;
		if(pos == 2)
			d->time_to_die = value;
		if(pos == 3)
			d->time_to_eat = value;
		if(pos == 4)
			d->time_to_sleep = value;
		if(pos == 5)
			d->philo_eats = value;
	}
	return(0);	
}
int create_mutex(t_list *d)
{
	size_t	i;

	i = 0;
	while (i < d->num_philo)
	{
		if (pthread_mutex_init(&d->mutex[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
int init_values(t_list *d)
{
	//int i ;
	d->init_philo = 0;
	d->thread = malloc(sizeof(pthread_t)*(d->num_philo));
	if(d->thread == NULL)
		return(1);
	pthread_mutex_init(&d->mutex_i,NULL);
	pthread_mutex_init(&d->mutex_msg,NULL);
	pthread_mutex_init(&d->mutex_fork,NULL);
	d->philo = malloc(sizeof(t_philo)*(d->num_philo));
	if(d->philo == NULL)
		return(1);
	d->mutex = malloc(sizeof(pthread_mutex_t)* d->num_philo);
	if(d->mutex == NULL)
		return(1);
	return(0);
}
long time_calculation()
{
	
}
/* int main_checker(t_list *d)
{
	
} */
int start_table(t_list *d)
{
	if(pthread_mutex_init(&d->mutex_last_eat,NULL) != 0)
		return(1);//== 0 en caso de exito
	if(pthread_mutex_init(&d->mutex_stat,NULL) != 0)
		return(1);
	d->stat = 0;
	d->id = 1;
	if(init_values(d) == 1)
		return(1);
	if(create_mutex(d)== 1)
		return(1); 
	 d->s_time = time_calculation();
	/*if(create_thread(d) == 1)
		return(1);
	d->init_philo = 1;//lo inicializas a 0 en init_values
	main_checker(d);
	*/
	return(0); 
}

void print_d(t_list *d)
{
	if( d != NULL)
	{
		//PRUEBAS
		printf("d->num_philo = [%ld]\n",d->num_philo);
		printf("d->time_to_die = [%ld]\n",d->time_to_die);
		printf("d->time_to_eat = [%ld]\n",d->time_to_eat);
		printf("d->time_to_sleep = [%ld]\n",d->time_to_sleep);
		printf("d->philo_eats = [%ld]\n",d->philo_eats);
	}
}
int set_struct(int argc,char **argv)
{
	t_list *d;
	(void)argc;
	d = ft_calloc(1,sizeof(t_list));
	int i=1;
	while(i != argc)
	{
		if(check_argv_num(d,argv[i],i) == 1)
			return(1);
		i++;
	}
	print_d(d);
	
	if(start_table(d) == 1)
		return(1);
	return(0);
	

}