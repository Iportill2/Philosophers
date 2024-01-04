#include "philo.h"

long	time_calc(void)
{
	struct timeval time;
	long actualtime;

	actualtime=0;
	
	
	gettimeofday(&time,NULL);
	actualtime=(time.tv_sec * 1000) + (time.tv_usec /1000);
	printf("segundos = %ld,Microsegundos %ld\n",time.tv_sec,time.tv_usec);

	return(actualtime);
}

int routine(t_list *d)
{
	int i;
	pthread_mutex_lock(&((t_list*)d)->mutex_i);
	i = d ->id -1;
	d -> id++;
	pthread_mutex_lock(&((t_list*)d)->mutex_i);
	if(i % 2 == 0)
		//ft_usleep((d->time_to_eat /2));
	while(d->stat == 0 /* || death_philo(d) == 0 */)//hacer death philo
	{
		pthread_mutex_lock(&((t_list*)d)->mutex_fork);
		//ft_take_fork((t_list*)d,i);//hacer take_fork
		pthread_mutex_unlock(&((t_list*)d)->mutex_fork);
		//ft_eat((t_list*)d,i);//hacer ft_eat
		//ft_sleep((t_list*)d,i);//hacer ft_sleep
		//if(d->num_philo % 2 != 0 )
			//ft_usleep(d->time_sleep / 3);//hacer ft_usleep
	}
	return(0);
}

void *philo_routine(void *f)
{
	t_list *d;
	d = (t_list *)f;
	while(d->init_philo == 0)
	{
		if(usleep(10) == 0);

		else
			printf("fallo al ejecutar usleep en philo_routine\n");
	}
	//if(routine(d) == 1)
		return(NULL);
	return(NULL);
}

int create_mutex(t_list *d)
{
	size_t i;

	i =0;
	while(i < d->num_philo)
	{
		if(pthread_mutex_init(&d->mutex[i],NULL) != 0)
		{
			printf("Error al crear el mutex[%li]\n",i);
			return(1);
		}
		else
			printf("d->mutex[%li] creado con exito :)\n",i);
		i++;
	}
	return(0);
}
int create_thread(t_list *d)
{
	size_t i;

	i =0;
	while(i < d->num_philo)
	{
		pthread_mutex_lock(&d->mutex_last_eat);
		d->philo[i].last_eat = 0; ///
		pthread_mutex_unlock(&d->mutex_last_eat);
		if(pthread_create(&d->thread[i],NULL,&philo_routine,(void*)d) != 0)
			return(1);
		else
			printf("d->thread[%li] creado con exito :)\n",i);
		i++;
	}
	return(0);
}