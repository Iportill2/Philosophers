/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:50:21 by iportill          #+#    #+#             */
/*   Updated: 2024/01/02 12:33:21 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
static int	check_num_arg(char *num_arg, int pos, t_list *d)
{
	int	n;

	n = ft_atoi(num_arg);
	printf(" [pos = %i][n = %d]\n",pos,n);
	if (n == 0 || n < 0 || (pos == 1 && n > 200) || (pos == 2 && n < 60)
		|| (pos == 3 && n < 60) || (pos == 4 && n < 60))
	{
		free(d);
		write(1, "Numero incorrecto.\n", 20);
		return (-1);
	}
	else
	{
		if (pos == 1)
			d->num_philo = n;
		if (pos == 2)
			d->time_to_die = n;
		if (pos == 3)
			d->time_to_eat = n;
		if (pos == 4)
			d->time_sleep = n;
		if (pos == 5)
			d->philo_eats = n;
		return (n);
	}
}

static	int	start_simulation(t_list *d)
{

	pthread_mutex_init(&d->mutex_last_eat, NULL);
	pthread_mutex_init(&d->mutex_stat, NULL);
	d->stat = 0;
	d->id = 1;
	if (init_values(d) == -1)
		return (-1);
	if (create_mutex(d) == -1)
		return (-1);
	d->s_time = calc_time();
	if (create_thread(d) == -1)
		return (-1);
	d->init_philo = 1;
	main_checker(d);
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_list	*d;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid number of arguments\n");
		return (0);
	}
	i = 1;
	d = malloc(sizeof(t_list));
	if (!d)
		return (0);
	while (i != argc)
	{
		if (check_num_arg(argv[i], i, d) < 0)
			return (0);
		i++;
	}
	if (start_simulation(d) != 0)
		return (-1);
	return (0);
}
