/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:01:23 by iportill          #+#    #+#             */
/*   Updated: 2024/01/12 12:53:44 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_d(t_list *d)
{
	free(d->eat_n);
	free(d->t_left);
	free(d->phi);
	free(d->fork_mutex);
	free(d);
}

int	error(t_list *d, int n)
{
	if (n == 1)
	{
		printf(RR"Invalid value\n"WW);
		free(d);
		exit(1);
	}
	if (n == 2)
	{
		printf(CC"Elapsed run time 0\nPhilo nº1 \
has taken a right fork 🍴\n\n"WW);
		printf(RR"Elapsed run time %ld\nPhilo nº1 died ☠️\n"WW, d->t_d);
		free(d);
		exit(1);
	}
	return (0);
}
