/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:17:06 by iportill          #+#    #+#             */
/*   Updated: 2024/01/12 13:15:02 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t t)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < t)
		usleep(500);
}

void	*watch_phi_rou(void *born)
{
	t_phi	*f;

	f = (t_phi *)born;
	f->right_fork = f->phi_id;
	if (f->phi_id == f->d->n_f - 1)
		f->left_fork = 0;
	else
		f->left_fork = f->phi_id + 1;
	if (f->phi_id == f->d->n_f)
		ft_watcher(f);
	if (f->phi_id % 2 == 0 && f->phi_id != f->d->n_f)
	{
		ft_routine(f);
	}
	else if (f->phi_id % 2 != 0 && f->phi_id != f->d->n_f)
	{
		usleep((10) * 1000);
		ft_routine(f);
	}
	free (f);
	return (0);
}

void	ft_mutex_init(t_list *d)
{
	int	i;

	i = 0;
	while (i < d->n_f)
	{
		pthread_mutex_init(&d->fork_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&d->stop_mutex, NULL);
	pthread_mutex_init(&d->eat_mutex, NULL);
	pthread_mutex_init(&d->print_mutex, NULL);
	pthread_mutex_init(&d->get_t_mutex, NULL);
}

void	ft_mutex_destroy(t_list *d)
{
	int	i;

	i = 0;
	while (i < d->n_f)
	{
		pthread_mutex_destroy(&d->fork_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&d->stop_mutex);
	pthread_mutex_destroy(&d->eat_mutex);
	pthread_mutex_destroy(&d->print_mutex);
	pthread_mutex_destroy(&d->get_t_mutex);
}

int	ft_thread(t_list *d)
{
	int		i;
	t_phi	*f;

	ft_mutex_init(d);
	i = 0;
	while (i <= d->n_f)
	{
		f = ft_calloc (sizeof(t_phi), 1);
		if (f == NULL)
			return (1);
		f->phi_id = i;
		f->d = d;
		if (pthread_create (&d->phi[i], NULL, &watch_phi_rou, f) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i <= d->n_f)
	{
		if (pthread_join (d->phi[i], NULL) != 0)
			return (1);
		i++;
	}
	ft_mutex_destroy(d);
	return (ft_free_d(d), 0);
}
