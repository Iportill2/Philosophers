/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:00:36 by iportill          #+#    #+#             */
/*   Updated: 2024/01/11 11:56:24 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_ok(t_phi *f)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&f->d->dead);
	if (f->d->stop == 0)
		i = 1;
	pthread_mutex_unlock(&f->d->dead);
	return (i);
}

void	ft_dead(t_phi *f, int p_n)
{
	pthread_mutex_lock(&f->d->dead);
	if (f->d->stop == 0)
	{
		f->d->stop = 1;
		pthread_mutex_lock(&f->d->print);
		printf(RR"Elapsed run time %lu\nPhilo nº%i died ☠️\n\n"WW, \
get_time() - f->d->time, p_n + 1);
		pthread_mutex_unlock(&f->d->print);
	}
	pthread_mutex_unlock(&f->d->dead);
}

void	ft_eating(t_phi *f, int p_n)
{
	pthread_mutex_lock(&f->d->get_t);
	f->d->t_left[p_n] = get_time();
	pthread_mutex_unlock(&f->d->get_t);
	pthread_mutex_lock(&f->d->print);
	printf(GG"Elapsed run time %lu\nPhilo nº%i is eating 🍜\n\n"WW, \
get_time() - f->d->time, p_n + 1);
	pthread_mutex_unlock(&f->d->print);
	pthread_mutex_unlock(&f->d->fork[f->f1]);
	pthread_mutex_unlock(&f->d->fork[f->f2]);
	pthread_mutex_lock(&f->d->eat);
	f->d->eat_n[p_n] = f->d->eat_n[p_n] + 1;
	pthread_mutex_unlock(&f->d->eat);
	ft_usleep(f->d->t_e);
}

void	ft_eat(t_phi *f)
{
	pthread_mutex_lock(&f->d->fork[f->f1]);
	if (ft_check_ok(f) == 1)
	{
		pthread_mutex_lock(&f->d->print);
		printf(KK"Elapsed run time %lu\nPhilo nº%i has taken a right fork\
🍴\n\n"WW, get_time() - f->d->time, f->phi_id + 1);
		pthread_mutex_unlock(&f->d->print);
	}
	pthread_mutex_lock(&f->d->fork[f->f2]);
	if (ft_check_ok(f) == 1)
	{
		pthread_mutex_lock(&f->d->print);
		printf(BB"Elapsed run time %lu\nPhilo nº%i has taken a left fork \
🍴🥄\n\n"WW, get_time() - f->d->time, f->phi_id + 1);
		pthread_mutex_unlock(&f->d->print);
	}
	if (ft_check_ok(f) == 1)
		ft_eating (f, f->phi_id);
}

void	ft_live(t_phi *f)
{
	while (ft_check_ok(f) == 1)
	{
		ft_eat(f);
		if (ft_check_ok(f) == 1)
		{
			pthread_mutex_lock(&f->d->print);
			printf(YY"Elapsed run time %lu\nPhilo nº%i is sleeping \
💤\n\n"WW, get_time() - f->d->time, f->phi_id + 1);
			pthread_mutex_unlock(&f->d->print);
			ft_usleep(f->d->t_s);
		}
		if (ft_check_ok(f) == 1)
		{
			pthread_mutex_lock(&f->d->print);
			printf (OO"Elapsed run time %lu\nPhilo nº%i is thinking \
🤦\n\n"WW, get_time() - f->d->time, f->phi_id + 1);
			pthread_mutex_unlock(&f->d->print);
		}
	}
}
