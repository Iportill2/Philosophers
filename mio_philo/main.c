#include "philo.h"

/* void ft_temp_free(char *temp)
{
	if(temp != NULL)
	{
		free(temp);
		temp=NULL;
	}
} */
void ft_free(t_list *d)
{
	size_t i =0;
	while(i <= d->num_philo)
	{
		pthread_mutex_destroy(&d->mutex[i]);
		i++;
	}
	i = 0;
	if(d->num_philo == 1)
		pthread_detach(d->thread[i]);
	else
		while(i < d->num_philo)
		{
			pthread_detach(d->thread[i]);
			i++;
		}
}

void ft_print_die(long t, size_t i)
{
	printf("[%ld] [%ld] DIE\n",t,i);
}

void main_checker(t_list *d)
{
	size_t i;
	long t;

	i=0;
	while (d->stat == 0)
	{
		while (i < d->num_philo)
		{
			t = time_calc() - d->s_time;
			if(t - d->philo[i].last_eat > d->time_to_die || check_eats(d) == 1)
			{
				if(d->stat == 2)
					break;
				d->stat = 1;
				ft_print_die(t,i);
				break;
			}
			i++;
		}
		i = 0;
	}
	ft_free(d);
}

int start_table(t_list *d)
{
	//int i =0;
	pthread_mutex_init(&d->mutex_last_eat,NULL);
	pthread_mutex_init(&d->mutex_stat,NULL);
	d->stat = 0;
	d->id = 1;
	if(init_values(d) == 1)
		return(1);
	if(create_mutex(d) == 1)
		return(1);
	d->s_time =time_calc();//crear la funcion
	if(create_thread(d) == 1)
		return(1);
	main_checker(d);
	return(0);
}
int init_values(t_list *d)
{
	size_t i = 0;
	d->init_philo = 0;
	d->thread = ft_calloc(sizeof(pthread_t),d->num_philo);
	if(d->thread == NULL)
		return(1);
	pthread_mutex_init(&d->mutex_i,NULL);//inicializamos mutex_i
	pthread_mutex_init(&d->mutex_msg,NULL);//inicializamos mutex_msg
	pthread_mutex_init(&d->mutex_fork,NULL);//inicializamos mutex_fork
	d->philo = ft_calloc(sizeof(t_philo),d->num_philo);//reservamos memoria para cada struct philo
	if(d->philo == NULL)
		return(1);
	d->mutex = ft_calloc(sizeof(pthread_mutex_t),d->num_philo);//reservamos para pthread_t	*thread
	if(d->mutex == NULL)
		return(1);
	while (i < d->num_philo)
	{
		d->philo[i].num_eats = 0;
		d->philo[i].fork_r = i;
		d->philo[i].fork_r = i+1;
		i++;
	}
	d->philo[0].fork_r=d->num_philo -1;
	return(0);

}
int argv_to_int(char **argv,int pos,t_list *d)
{
	int value;
	printf("[pos=%i]\n",pos);
	value = ft_atoi(argv[pos]);
	printf("[value=%i]\n",value);

	if (value == 0 || value < 0 || (pos == 1 && value > 200)
	 || (pos == 2 && value < 60)|| (pos == 3 && value < 60)
	  || (pos == 4 && value < 60))
	{
		error(d,1);

	}
	if(pos == 1)
		d->num_philo=value;
	if(pos == 2)
		d->time_to_die=value;
	if(pos == 3)
		d->time_to_eat=value;
	if(pos == 4)
		d->time_to_sleep=value;
	if(pos == 5)
		d->philo_eats=value;
	print_value(d);
	
	return(0);
}

int ft_init_struct(char **argv)
{
	t_list *d;
	int i;

	i=1;
	d = NULL;
	d=ft_calloc(sizeof(t_list),1);
	if(d == NULL)
		return(1);
	while(argv[i] != NULL)
	{
		argv_to_int(argv,i,d);
		i++;
	}
	
	if(start_table(d) == 1)
		error(d,2);
	return(0);
}

int main (int argc,char **argv)
{
	(void)argv;
	if(argc == 5 || argc == 6)
	{
		if(ft_init_struct(argv) == 1)
			return(1);
		else
			printf("programa finaliza satisfactoriamente\n");
	}
	else
	{
		printf("incorrect number of arguments\n");
		return(1);
	}

	return(0);
}