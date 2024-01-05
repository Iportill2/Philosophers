#include "philo.h"

void print_value(t_list *d)
{
	printf("d->num_philo=%ld\n",d->n_f);
	printf("d->time_to_die=%ld\n",d->t_d);
	printf("d->time_to_eat=%ld\n",d->t_e);
	printf("d->time_to_sleep=%ld\n",d->t_s);
	printf("d->philo_eats=%i\n",d->nt_me);
	printf("******************************\n");
}

int ft_free_s(t_list *d)
{
	/* if(d->thread != NULL)
		free(d->thread);
	if(d->philo != NULL)
		free(d->philo);
	if(d->mutex != NULL)
		free(d->mutex); */
	free(d);
	return(0);
}

int error(t_list *d,int n)
{
	if(n == 1)
	{
		printf("invalid value\n");
		print_value(d);
		ft_free_s(d);
		exit(1);
	}
	if(n == 2)
	{	
		printf("error in start_table\n");
		ft_free_s(d);
		exit(1);
	}
	if(n == 3)
	{
		printf("0 1 has taken a fork\n60 1 died\n");
		if(d != NULL)
		{
			free(d);
			d=NULL;
			printf("Program end succesfully!\n");
			exit(1);
		}
	}
	return(0);
}