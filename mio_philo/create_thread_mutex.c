#include "philo.h"

long	time_calc(void)
{
	struct timeval time;
	long actualtime;

	actualtime=0;
	
	
	gettimeofday(&time,NULL);
	actualtime=(time.tv_sec * 1000) + (time.tv_usec /1000);
	/* printf("segundos = %ld,Microsegundos %ld\n",time.tv_sec,time.tv_usec);
	printf("actualtime =  %ld\n",actualtime); */
	//printf("time_calc\n");
	return(actualtime);
}


int death_philo(t_list *d)
{
	size_t i;
	long time;
	printf("HHH\n");
	i = 0;
	while(i < d->num_philo)
	{
		time = time_calc() - d->s_time;
		if(time - d->philo[i].last_eat > d->time_to_die)
		{
			if(d->stat == 0)
			{
				d->stat = 1;
				printf("[%ld] [%ld]HA MUERTO UN PHILO!\n",time,i);
			}
			//gestionar errores y free
			return(1);
		}
		i++;
	}
	return(0);
}

int check_eats(t_list *d)
{
	size_t i = 0;
	size_t e = 0;
	if(d ->philo_eats)//if(d->philo_eat != 0)
		return(0);
	while(i < d->num_philo)
	{
		if(d->philo[i].num_eats >= d->philo_eats)
			e++;
		else
			break;//si algun filosofo a comido el numero de veces estipulado termina el programa
		i++;
	}
	if(e >= d->num_philo)//no se yo...
	{
		d->stat = 2;
		return(1);
	}
	return(0);
}

void w_status(char *s,t_list *d,size_t i)
{
	long time;
	pthread_mutex_lock(&d->mutex_msg);
	time =time_calc() -d->s_time;
	if(i <= d->num_philo && check_eats(d) == 0 && d->stat == 0)
		printf("[%ld] [%ld]%s\n",time,i,s);
	return;
}

void ft_sleep(t_list *d, size_t i)
{
	w_status("His sleeping\n",d,i+1);
	ft_usleep(d->time_sleep);
	w_status("His thinking\n",d,i+1);
	return;
}
void ft_eat(t_list *d,size_t i)
{
	w_status("HIs eating\n",d,i+1);
	d->philo[i].num_eats++;
	ft_usleep(d->time_to_eat);
	pthread_mutex_unlock(&d->mutex[d->philo[i].fork_r]);
	pthread_mutex_unlock(&d->mutex[d->philo[i].fork_l]);
	pthread_mutex_lock(&d->mutex_last_eat);
	d->philo[i].last_eat = time_calc() - d->s_time;
	pthread_mutex_unlock(&d->mutex_last_eat);
}

void ft_usleep(int condition)
{
	long start;

	start = time_calc();
	while (time_calc() - start < condition)
	{
		usleep(condition / 2);
	}
}

void ft_take_fork(t_list *d, int i)
{
	pthread_mutex_lock(&d->mutex[d->philo[i].fork_r]);
	w_status("Has take a fork R\n",d,i+1);
	if(d->num_philo == 1)//si hay 1 philo deja que se muera
		ft_usleep(d->time_to_die + 1);
	pthread_mutex_lock(&d->mutex[d->philo[i].fork_l]);
	w_status("Has take a fork R\n",d,i+1);
}
int routine(t_list *d)
{
	printf("ROUTINE\n");
	int i;
	pthread_mutex_lock(&((t_list*)d)->mutex_i);
	i = d ->id -1;
	d -> id++;
	pthread_mutex_lock(&((t_list*)d)->mutex_i);
	printf("usleep");
	if(i % 2 == 0)
		ft_usleep((d->time_to_eat /2));
	while(d->stat == 0 || death_philo(d) == 0)
	{
		pthread_mutex_lock(&((t_list*)d)->mutex_fork);
		ft_take_fork((t_list*)d,i);
		pthread_mutex_unlock(&((t_list*)d)->mutex_fork);
		ft_eat((t_list*)d,i);
		ft_sleep((t_list*)d,i);
		if(d->num_philo % 2 != 0 )
			ft_usleep(d->time_sleep / 3);
	}
	return(0);
}

void *philo_routine(void *f)
{

	t_list *d;
	d = (t_list *)f;
	while(d->init_philo == 0)
	{
		(usleep(10));
			/* printf("philo_routine\n");
		else
			printf("fallo al ejecutar usleep en philo_routine\n"); */
	}
	if(routine(d) == -1)
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

