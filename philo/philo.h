/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:50:58 by iportill          #+#    #+#             */
/*   Updated: 2023/12/27 17:25:28 by iportill         ###   ########.fr       */
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

typedef struct s_philo//esta structura representa a cada philo 
{
	size_t num_eats;//numero de veces que ha comido
	size_t last_eat;//la ultima vez que comio
	size_t fork_r;//mano r con tenedor(si cumple ambas puede comer)
	size_t fork_l;//mano l con tenedor(si cumple ambas puede comer)
}t_philo;

typedef struct s_list
{
	char *prueba;
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
void set_struct(int argc,char **argv);

#endif