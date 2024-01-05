/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoikoet <jgoikoet@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:30:45 by jgoikoet          #+#    #+#             */
/*   Updated: 2023/09/26 12:19:04 by jgoikoet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_get_t(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long int	ft_atoi(char *s)
{
	int			i;
	long int	n;

	i = 0;
	n = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] && s[i] >= '0' && s[i] <= '9' )
	{
		n = n * 10;
		n = n + s[i++] - '0';
	}
	return ((int)n);
}

int	ft_set_fork_phi_eat(t_data *d)
{
	int	i;

	d->fork = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * d->n_f);
	if (!d->fork)
		return (0);
	d->phi = (pthread_t *) malloc (sizeof(pthread_t) * (d->n_f + 1));
	if (!d->phi)
		return (0);
	d->eat_n = (int *) malloc (sizeof(int) * d->n_f);
	if (!d->eat_n)
		return (0);
	i = 0;
	while (i < d->n_f)
		d->eat_n[i++] = 0;
	d->t_left = (long *) malloc (sizeof(long) * d->n_f);
	if (!d->t_left)
		return (0);
	i = 0;
	while (i < d->n_f)
		d->t_left[i++] = d->time;
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*d;

	if (argc < 5 || argc > 6)
		return (printf("Incorrect number of arguments\n"), 0);
	if (ft_error_spe(argc, argv))
		return (0);
	d = (t_data *) malloc (sizeof(t_data));
	if (!d)
		return (printf("Error creating structure\n"), 0);
	d->n_f = ft_atoi(argv[1]);
	d->t_d = ft_atoi(argv[2]);
	d->t_e = ft_atoi(argv[3]);
	d->t_s = ft_atoi(argv[4]);
	d->time = ft_get_t();
	d->ok = 1;
	if (argv[5])
		d->nt_me = ft_atoi(argv[5]);
	else
		d->nt_me = -1;
	if (!ft_set_fork_phi_eat(d))
		return (printf("Error creating structure\n"), free (d), 0);
	ft_thread(d);
	free(d->fork);
	free(d->phi);
	return (free(d->eat_n), free(d->t_left), free(d), 0);
}
