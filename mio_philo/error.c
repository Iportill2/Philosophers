#include "philo.h"

void print_value(t_list *d)
{
	printf("d->num_philo=%ld\n",d->num_philo);
	printf("d->time_to_die=%ld\n",d->time_to_die);
	printf("d->time_to_eat=%ld\n",d->time_to_eat);
	printf("d->time_to_sleep=%ld\n",d->time_to_sleep);
	printf("d->philo_eats=%ld\n",d->philo_eats);
	printf("******************************\n");
}

int ft_free(t_list *d)
{
	if(d->thread != NULL)
		free(d->thread);
	if(d->philo != NULL)
		free(d->philo);
	if(d->mutex != NULL)
		free(d->mutex);
	free(d);
	return(0);
}

int error(t_list *d,int n)
{
	if(n == 1)
	{
		printf("invalid value\n");
		print_value(d);
		ft_free(d);
		exit(1);
	}
	if(n == 2)
	{	
		printf("error in start_table\n");
		ft_free(d);
		exit(1);
	}
	return(0);
}