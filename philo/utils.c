/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:51:03 by iportill          #+#    #+#             */
/*   Updated: 2024/01/02 12:08:46 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_mutex(t_list *d)
{
	size_t	i;

	i = 0;
	while (i < d->num_philo)
	{
		if (pthread_mutex_init(&d->mutex[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	create_thread(t_list *d)
{
	size_t	i;

	i = 0;
	while (i < d->num_philo)
	{
		pthread_mutex_lock(&d->mutex_last_eat);
		d->philo[i].last_eat = 0;
		pthread_mutex_unlock(&d->mutex_last_eat);
		if (pthread_create(&d->thread[i], NULL, &philo_routine, (void *)d) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	w_status(char *s, t_list *d, size_t i)
{
	long	time;

	pthread_mutex_lock(&d->mutex_msg);
	time = calc_time() - d->s_time;
	if (i <= d->num_philo && check_eats(d) == 0 && d->stat == 0)
	{
		printf("\033[1;89m[%ld]	[%ld] \033[0;39m%s", time, i, s);
	}
	pthread_mutex_unlock(&d->mutex_msg);
}

void	ft_take_fork(t_list *d, int i)
{
	pthread_mutex_lock(&d->mutex[d->philo[i].fork_r]);
	w_status("\033[1;92mhas taken a fork 🍴\033[0;39m\n", d, i + 1);
	if (d->num_philo == 1)
		ft_usleep(d->time_to_die + 1);
	pthread_mutex_lock(&d->mutex[d->philo[i].fork_l]);
	w_status("\033[1;92mhas taken a fork 🍴\033[0;39m\n", d, i + 1);
}

void	ft_eat(t_list *d, int i)
{
	w_status("\033[1;94mis eating 🍜\033[0;39m\n", d, i + 1);
	d->philo[i].num_eats++;
	ft_usleep(d->time_to_eat);
	pthread_mutex_unlock(&d->mutex[d->philo[i].fork_l]);
	pthread_mutex_unlock(&d->mutex[d->philo[i].fork_r]);
	pthread_mutex_lock(&d->mutex_last_eat);
	d->philo[i].last_eat = calc_time() - d->s_time;
	pthread_mutex_unlock(&d->mutex_last_eat);
}

void	ft_sleep(t_list *d, int i)
{
	w_status("\033[1;89mis sleeping 😴\033[0;39m\n", d, i + 1);
	ft_usleep(d->time_sleep);
	w_status("\033[1;91mis thinking 🙇🏻‍♂️💭\033[0;39m\n", d, i + 1);
}

int	ft_spaces(char c)
{
	if(c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return(1);
	else
		return(0);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				valorfinal;
	long long int	nbr;

	nbr = 0;
	i = 0;
	valorfinal = 1;
	while (str[i] && ft_spaces(str[i]) == 0)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			valorfinal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
		if (nbr < INT_MIN && valorfinal == -1)
			return (0);
		if (nbr > INT_MAX && valorfinal == 1)
			return (-1);
	}
	return (nbr * valorfinal);
}

int	init_values(t_list *d)
{
	size_t	i;

	d->init_philo = 0;
	d->thread = malloc(sizeof(pthread_t *) * (d->num_philo));
	if (!d->thread)
		return (-1);
	pthread_mutex_init(&d->mutex_i, NULL);
	pthread_mutex_init(&d->mutex_msg, NULL);
	pthread_mutex_init(&d->mutex_fork, NULL);
	d->philo = malloc(sizeof(t_philo) * d->num_philo);
	if (!d->philo)
		return (-1);
	d->mutex = malloc(sizeof(pthread_mutex_t) * d->num_philo);
	if (!d->mutex)
		return (-1);
	i = 0;
	while (i < d->num_philo)
	{
		d->philo[i].num_eats = 0;
		d->philo[i].fork_r = i - 1;
		d->philo[i].fork_l = i;
		i++;
	}
	d->philo[0].fork_r = d->num_philo - 1;
	return (0);
}

int	check_eats(t_list *d)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!d->philo_eats)
		return (0);
	while (++i < d->num_philo)
	{
		if (d->philo[i].num_eats >= d->philo_eats)
			j++;
		else
			break ;
		i++;
	}
	if (j >= d->num_philo)
	{
		d->stat = 2;
		return (1);
	}
	return (0);
}

static void	ft_print_die(long t, int c)
{
	printf("\033[1;89m[%ld]	[%d] \033[1;91mdied ☠️\033[0;39m\n", t, c);
}

void	ft_free(t_list *d)
{
	size_t	i;

	i = 0;
	while (++i <= d->num_philo)
	{
		pthread_mutex_destroy(&d->mutex[i]);
		i++;
	}
	i = 0;
	if (d->num_philo == 1)
		pthread_detach(d->thread[i]);
	else
	{
		while (++i <= d->num_philo)
		{
			pthread_detach(d->thread[i]);
			i++;
		}
	}
}

void	main_checker(t_list *d)
{
	size_t		c;
	long	t;

	c = 0;
	while (d->stat == 0)
	{
		while (c < d->num_philo)
		{
			t = calc_time() - d->s_time;
			if (t - d->philo[c].last_eat > d->time_to_die || check_eats(d) == 1)
			{
				if (d->stat == 2)
				{
					break ;
				}
				d->stat = 1;
				ft_print_die(t, c + 1);
				break ;
			}
			c++;
		}
		c = 0;
	}
	ft_free(d);
}

int	death_philo(t_list *d)
{
	size_t		c;
	long	time;

	c = 0;
	while (c < d->num_philo)
	{
		time = calc_time() - d->s_time;
		if (time - d->philo[c].last_eat > d->time_to_die)
		{
			if (d->stat == 0)
			{
				d->stat = 1;
				printf("[%ld]	[%ld] \033[1;91mdied ☠️\033[0;39m\n", time, c + 1);
			}
			return (1);
		}
	}
	return (0);
}

int	routine(t_list *d)
{
	int	i;

	pthread_mutex_lock(&((t_list *)d)->mutex_i);
	i = d->id - 1;
	d->id++;
	pthread_mutex_unlock(&((t_list *)d)->mutex_i);
	if (i % 2 == 0)
		ft_usleep(d->time_to_eat / 2);
	while (d->stat == 0 || death_philo(d) == 0)
	{
		pthread_mutex_lock(&((t_list *)d)->mutex_fork);
		ft_take_fork((t_list *)d, i);
		pthread_mutex_unlock(&((t_list *)d)->mutex_fork);
		ft_eat((t_list *)d, i);
		ft_sleep((t_list *)d, i);
		if (d->num_philo % 2 != 0)
			ft_usleep(d->time_sleep / 3);
	}
	return (0);
}

void	*philo_routine(void *f)
{
	t_list	*d;

	d = (t_list *)f;
	while (d->init_philo == 0)
	{
		usleep(10);
	}
	if (routine(d) == -1)
		return (NULL);
	return (NULL);
}
long	calc_time(void)
{
	struct timeval	time;
	long			actual_time;

	gettimeofday(&time, NULL);
	actual_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (actual_time);
}

void	ft_usleep(int condition)
{
	long	start;

	start = calc_time();
	while (calc_time() - start < condition)
	{
		usleep(condition / 2);
	}
}
