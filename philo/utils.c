/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:51:03 by iportill          #+#    #+#             */
/*   Updated: 2024/01/02 11:29:03 by iportill         ###   ########.fr       */
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
long time_calculation(void)
{
	struct timeval	time;
	long			actual_time;
	
	if(gettimeofday(&time, NULL) == -1)//man gettimeofday
		printf("error al usar gettimeofday\n");
	actual_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);//tv_sec = segundos //tv.usec = microsegundos
	return (actual_time);
}
int death_philo(t_list *d)
{
	size_t c;
	long time;

	c=0;
	while (c < d->num_philo)
	{
		time = time_calculation() - d->s_time;
		if(time - d->philo[c].last_eat > d->time_to_die)
		{
			if(d->stat == 0)
			{
				d->stat = 1;
				printf("[%ld] [%ld] im die\n",time,c);
			}
			return(1);
		}
	}
	return(0);
}
void ft_usleep(int condition)
{
	long start;
	start = time_calculation();
	while (time_calculation()- start < condition)
	{
		usleep(condition / 2);
	}
}
int check_eats(t_list *d)
{
	size_t i;

	i=0;
	size_t x = 0;
	if(d->philo_eats)
		return(0);
	while(i < d->num_philo)
	{
		if(d->philo[i].num_eats >= d->philo_eats)
			x++;
		else
			break;
		i++;
	}
	if(x >= d->num_philo)
	{
		d->stat = 2;
		return(1);
	}
	return(0);
}
void wstatus(char *s,t_list *d,size_t i)
{
	long time;
	pthread_mutex_lock(&d->mutex_msg);
	time = time_calculation() - d->s_time;
	if(i <= d->num_philo && check_eats(d) == 0 && d->stat == 0 )
		printf("[%ld] [%ld] %s",time, i ,s);
	pthread_mutex_unlock(&d->mutex_msg);
}
void ft_take_fork(t_list *d, size_t i)
{
	pthread_mutex_lock(&d->mutex[d->philo[i].fork_r]);
	wstatus("has taken a fork\n",d,i+1);
	if(d->num_philo == 1)
		ft_usleep(d->time_to_die +1);
	pthread_mutex_lock(&d->mutex[d->philo[i].fork_l]);
	wstatus("has taken a fork\n",d,i+1);
}
void ft_eat(t_list *d,size_t i)
{
	wstatus("mis eating\n",d,i+1);
	d->philo[i].num_eats ++;
	ft_usleep(d->time_to_eat);
	pthread_mutex_unlock(&d->mutex[d->philo[i].fork_l]);
	pthread_mutex_unlock(&d->mutex[d->philo[i].fork_r]);
	pthread_mutex_lock(&d->mutex_last_eat);
	d->philo[i].last_eat = time_calculation() - d->s_time;
	pthread_mutex_unlock(&d->mutex_last_eat);
}
void ft_sleep(t_list *d, size_t i)
{
	wstatus("mis sleeping\n",d,i+1);
	ft_usleep(d->time_sleep);
	wstatus("mis thinking\n",d,i+1);
}
static void ft_print_die(long t, size_t c)
{
	printf("[%ld] [%ld] die\n",t, c);
}
int routine(t_list *d)
{
	size_t i;

	i=0;
	pthread_mutex_lock(&d->mutex_i);//////////
	i = d->id -1;
	d->id++;
	pthread_mutex_unlock(&d->mutex_i);/////////
	if(i%2 == 0)
		ft_usleep(d->time_to_eat/2);
	while (d->stat == 0 || death_philo(d) == 0)
	{
		pthread_mutex_lock(&d->mutex_fork);
		ft_take_fork(d,i);
		pthread_mutex_unlock(&d->mutex_fork);
		ft_eat(d,i);
		ft_sleep(d,i);
		if(d->num_philo % 2 != 0)
			ft_usleep(d->time_sleep/3); 
	}
	return(0);
}

void *philo_routine(void *f)
{
	t_list *d;
	d =(t_list *)f;
	while (d->init_philo == 0)
	{
		usleep(10);
	}
	if(routine(d) == 1)
		return(NULL);
	return(NULL);
}
int create_thread(t_list *d)
{
	size_t i;

	i=0;
	while(i < d->num_philo)
	{
		pthread_mutex_lock(&d->mutex_last_eat);
		d->philo[i].last_eat = 0;
		pthread_mutex_unlock(&d->mutex_last_eat);
		if(pthread_create(&d->thread[i],NULL,&philo_routine,(void*)d) != 0)
			return(1);
		i++;
	}
	return(0);
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
void ft_free(t_list *d)
{
	size_t i;
	i = 0;
	while(i <= d->num_philo)
	{
		pthread_mutex_destroy(&d->mutex[i]);
		i++;
	}
	i = 0;
	if(d->num_philo == 1)
		pthread_detach(d->thread[i]);
	else
	{
		while(i <= d->num_philo)
		{
			pthread_detach(d->thread[i]);
			i++;
		}
	}
}
int main_checker(t_list *d)
{
	size_t c;
	long t;
	
	c = 0;
	while(d->stat == 0)
	{
		while(c < d->num_philo)
		{
			t = time_calculation() - d->s_time;
			if(t - d->philo[c].last_eat > d->time_to_die || check_eats(d) == 1)
			{
				if(d->stat == 2)
				{
					break;
				}
				d->stat = 1;
				ft_print_die(t,c);
				break;
			}
			c++;
		}
		c = 0;
	}
	ft_free(d);
	return(0);
}

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
	if(create_thread(d) == 1)//peta
	{
		printf("fallo al crear los hilos\n");
		return(1);
	}
	d->init_philo = 1;//lo inicializas a 0 en init_values
	main_checker(d);
	printf("HH\n");
	
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
		printf("d->s_time = [%ld]\n",d->s_time);
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
	printf("jaja\n");
	
	if(start_table(d) == 1)
		return(1);
	return(0);
	

}