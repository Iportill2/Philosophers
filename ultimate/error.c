#include "philo.h"

void print_value(t_list *d)
{
	printf("d->n_f=%d\n",d->n_f);
	printf("d->t_d=%ld\n",d->t_d);
	printf("d->t_e=%ld\n",d->t_e);
	printf("d->t_s=%ld\n",d->t_s);
	printf("d->nt_me=%i\n",d->nt_me);
	printf("d->time=%ld\n",d->time);
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