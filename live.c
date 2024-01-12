/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:00:36 by iportill          #+#    #+#             */
/*   Updated: 2024/01/12 13:18:05 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_ok(t_phi *f)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&f->d->stop_mutex);
	if (f->d->stop == 0)
		i = 0;
	pthread_mutex_unlock(&f->d->stop_mutex);
	return (i);
}

void	ft_dead(t_phi *f, int p_n)
{
	pthread_mutex_lock(&f->d->stop_mutex);
	if (f->d->stop == 0)
	{
		f->d->stop = 1;
		pthread_mutex_lock(&f->d->print_mutex);
		printf(RR"Elapsed run time %lu\nPhilo nº%i died ☠️\n\n"WW, \
get_time() - f->d->time, p_n + 1);
		pthread_mutex_unlock(&f->d->print_mutex);
	}
	pthread_mutex_unlock(&f->d->stop_mutex);
}

void	ft_eating(t_phi *f, int p_n)
{
	pthread_mutex_lock(&f->d->get_t_mutex);
	f->d->t_left[p_n] = get_time();
	pthread_mutex_unlock(&f->d->get_t_mutex);
	pthread_mutex_lock(&f->d->print_mutex);
	printf(GG"Elapsed run time %lu\nPhilo nº%i is eating 🍜\n\n"WW, \
get_time() - f->d->time, p_n + 1);
	pthread_mutex_unlock(&f->d->print_mutex);
	pthread_mutex_lock(&f->d->eat_mutex);
	f->d->eat_n[p_n] = f->d->eat_n[p_n] + 1;
	pthread_mutex_unlock(&f->d->eat_mutex);
	ft_usleep(f->d->t_e);
	pthread_mutex_unlock(&f->d->fork_mutex[f->right_fork]);
	pthread_mutex_unlock(&f->d->fork_mutex[f->left_fork]);
}

void	ft_eat(t_phi *f)
{
	pthread_mutex_lock(&f->d->fork_mutex[f->right_fork]);
	if (ft_check_ok(f) == 0)
	{
		pthread_mutex_lock(&f->d->print_mutex);
		printf(KK"Elapsed run time %lu\nPhilo nº%i has taken a right fork\
🍴\n\n"WW, get_time() - f->d->time, f->phi_id + 1);
		pthread_mutex_unlock(&f->d->print_mutex);
	}
	pthread_mutex_lock(&f->d->fork_mutex[f->left_fork]);
	if (ft_check_ok(f) == 0)
	{
		pthread_mutex_lock(&f->d->print_mutex);
		printf(BB"Elapsed run time %lu\nPhilo nº%i has taken a left fork \
🍴🥄\n\n"WW, get_time() - f->d->time, f->phi_id + 1);
		pthread_mutex_unlock(&f->d->print_mutex);
	}
	if (ft_check_ok(f) == 0)
		ft_eating (f, f->phi_id);
}

void	ft_routine(t_phi *f)
{
	while (ft_check_ok(f) == 0)
	{
		ft_eat(f);
		if (ft_check_ok(f) == 0)
		{
			pthread_mutex_lock(&f->d->print_mutex);
			printf(YY"Elapsed run time %lu\nPhilo nº%i is sleeping \
💤\n\n"WW, get_time() - f->d->time, f->phi_id + 1);
			pthread_mutex_unlock(&f->d->print_mutex);
			ft_usleep(f->d->t_s);
		}
		if (ft_check_ok(f) == 0)
		{
			pthread_mutex_lock(&f->d->print_mutex);
			printf (OO"Elapsed run time %lu\nPhilo nº%i is thinking \
🤦\n\n"WW, get_time() - f->d->time, f->phi_id + 1);
			pthread_mutex_unlock(&f->d->print_mutex);
		}
	}
}
