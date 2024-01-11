/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:01:23 by iportill          #+#    #+#             */
/*   Updated: 2024/01/11 11:07:54 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_value(t_list *d)
{
	printf("d->n_f=%d\n", d->n_f);
	printf("d->t_d=%ld\n", d->t_d);
	printf("d->t_e=%ld\n", d->t_e);
	printf("d->t_s=%ld\n", d->t_s);
	printf("d->nt_me=%i\n", d->nt_me);
	printf("d->time=%ld\n", d->time);
	printf("******************************\n");
}

int	ft_free_s(t_list *d)
{
	free(d);
	return (0);
}

int	error(t_list *d, int n)
{
	if (n == 1)
	{
		printf(RR"Invalid value\n"WW);
		print_value(d);
		ft_free_s(d);
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
