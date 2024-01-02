/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:50:58 by iportill          #+#    #+#             */
/*   Updated: 2024/01/02 12:54:40 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo//esta structura representa a cada philo 
{
	size_t num_eats;//numero de veces que ha comido
	size_t last_eat;//la ultima vez que comio
	size_t fork_r;//mano r con tenedor(si cumple ambas puede comer)
	size_t fork_l;//mano l con tenedor(si cumple ambas puede comer)
}t_philo;

typedef struct s_list
{
	size_t time_sleep;
	pthread_mutex_t *mutex;
	char *prueba;
	size_t init_philo;
	size_t stat;
	size_t id;
	size_t num_philo;//numero de filosofos >200
	size_t time_to_die;//tiempo para morir <60
	size_t time_to_eat;//tiempo que comen  <60
	size_t time_to_sleep;//tiempo que duermen < 60
	size_t time_to_think;//tiempo que piensan
	size_t philo_eats;//contador que se usa en caso de haber metido el paramero argv(6)correctamente
	t_philo	*philo;//puntero  a la structura philo
	pthread_t	*thread;
	pthread_mutex_t mutex_last_eat;
	pthread_mutex_t mutex_stat;
	pthread_mutex_t mutex_i;
	pthread_mutex_t mutex_msg;
	pthread_mutex_t mutex_fork;
	long	s_time;//variable para guardar el tiempo del sistema
}t_list;

/*UTILS*/
void* ft_calloc(size_t num, size_t size);
int	ft_atoi(const char *str);
int	check_eats(t_list *d);
int check_argv_num(t_list *d,char *argv,int pos);
void	w_status(char *s, t_list *d, size_t i);
int create_mutex(t_list *d);
long time_calculation(void);
int death_philo(t_list *d);
void ft_usleep(int condition);
int routine(t_list *d);
void *philo_routine(void *f);
int create_thread(t_list *d);
int init_values(t_list *d);
int start_table(t_list *d);
void print_d(t_list *d);
int set_struct(int argc,char **argv);

void	main_checker(t_list *d);
long	time_calculation(void);
#endif