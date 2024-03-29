/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:11:09 by iportill          #+#    #+#             */
/*   Updated: 2024/01/12 13:41:49 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_struc_calloc_bis(t_list *d)
{
	int	i;

	i = 0;
	while (i < d->n_f)
	{
		d->eat_n[i] = 0;
		i++;
	}
	i = 0;
	while (i < d->n_f)
	{
		d->t_left[i] = d->time;
		i++;
	}
	return ;
}

int	ft_struc_calloc(t_list *d)
{
	d->eat_n = ft_calloc (sizeof(int), d->n_f);
	if (!d->eat_n)
		return (1);
	d->t_left = ft_calloc (sizeof(long), d->n_f);
	if (d->t_left == 0)
		return (1);
	d->phi = ft_calloc (sizeof(pthread_t), d->n_f + 1);
	if (!d->phi)
		return (1);
	d->fork_mutex = ft_calloc (sizeof(pthread_mutex_t), d->n_f);
	if (!d->fork_mutex)
		return (1);
	ft_struc_calloc_bis(d);
	return (0);
}

void	argv_to_int(char **argv, int pos, t_list *d)
{
	int	value;

	value = ft_atoi(argv[pos]);
	if (value == 0 || value < 0 || (pos == 1 && value > 200)
		|| (pos == 2 && value < 60) || (pos == 3 && value < 60)
		|| (pos == 4 && value < 60))
		error (d, 1);
	if (pos == 1)
		d->n_f = value;
	if (pos == 2)
		d->t_d = value;
	if (pos == 3)
		d->t_e = value;
	if (pos == 4)
		d->t_s = value;
	if (pos == 5)
		d->nt_me = value;
	else
		d->nt_me = -1;
	d->stop = 0;
	d->time = get_time();
	return ;
}

int	ft_init_struct(char **argv)
{
	t_list	*d;
	int		i;

	i = 1;
	d = NULL;
	d = ft_calloc(sizeof(t_list), 1);
	if (d == NULL)
		return (1);
	while (argv[i] != NULL)
	{
		argv_to_int(argv, i, d);
		i++;
	}
	if (d->n_f == 1)
		error (d, 2);
	if (ft_struc_calloc(d) == 1)
		return (printf("Error creating structure\n"), free(d), exit(1), 1);
	else
		if (ft_thread(d) == 1)
			return (free(d), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc == 5 || argc == 6)
	{
		if (ft_init_struct(argv) == 1)
			return (1);
	}
	else
	{
		printf("Incorrect number of arguments!\n");
		return (1);
	}
	return (0);
}
