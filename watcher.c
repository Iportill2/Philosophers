/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:15:48 by iportill          #+#    #+#             */
/*   Updated: 2024/01/12 13:18:13 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_watcher_nt_me(t_phi *f)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (i < f->d->n_f)
	{
		pthread_mutex_lock(&f->d->eat_mutex);
		if (f->d->eat_n[i] >= f->d->nt_me)
			c++;
		pthread_mutex_unlock(&f->d->eat_mutex);
		i++;
	}
	if (c == f->d->n_f)
	{
		pthread_mutex_lock(&f->d->stop_mutex);
		f->d->stop = 1;
		pthread_mutex_unlock(&f->d->stop_mutex);
		printf(RR"All the philosophers ate %d times!!\n"WW, f->d->nt_me);
	}
}

void	ft_watcher_t_d(t_phi *f)
{
	int	i;

	i = 0;
	while (ft_check_ok(f) == 0 && i < f->d->n_f)
	{
		pthread_mutex_lock(&f->d->get_t_mutex);
		if ((get_time() - f->d->t_left[i]) >= f->d->t_d)
			ft_dead(f, i);
		pthread_mutex_unlock(&f->d->get_t_mutex);
		i++;
	}
}

void	ft_watcher(t_phi *f)
{
	while (ft_check_ok(f) == 0)
	{
		usleep(100);
		if (f->d->nt_me != -1)
			ft_watcher_nt_me(f);
		ft_watcher_t_d(f);
	}
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
