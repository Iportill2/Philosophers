/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:50:21 by iportill          #+#    #+#             */
/*   Updated: 2024/01/02 12:54:21 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	check_num_arg(char *num_arg, int pos, t_list *d)
{
	int	value;

	value = ft_atoi(num_arg);
	if (value == 0 || value < 0 || (pos == 1 && value > 200)
	 || (pos == 2 && value < 60)|| (pos == 3 && value < 60)
	  || (pos == 4 && value < 60))
	{
		free(d);
		printf("Incorreect value of argument.\n");
		return (1);
	}
	else
	{
		if (pos == 1)
			d->num_philo = value;
		if (pos == 2)
			d->time_to_die = value;
		if (pos == 3)
			d->time_to_eat = value;
		if (pos == 4)
			d->time_sleep = value;
		if (pos == 5)
			d->philo_eats = value;
		return (0);
	}
	return(0);
}

int	start_table(t_list *d)
{

	pthread_mutex_init(&d->mutex_last_eat, NULL);
	pthread_mutex_init(&d->mutex_stat, NULL);
	d->stat = 0;
	d->id = 1;
	if (init_values(d) == -1)
		return (-1);
	if (create_mutex(d) == -1)
		return (-1);
	d->s_time = time_calculation();
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
	d = ft_calloc(sizeof(t_list), 1);
	if (!d)
		return (0);
	while (i != argc)
	{
		if (check_num_arg(argv[i], i, d) == 1)
			return (0);
		i++;
	}
	if (start_table(d) != 0)
		return (-1);
	return (0);
}
