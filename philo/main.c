/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:50:21 by iportill          #+#    #+#             */
/*   Updated: 2023/12/29 16:31:33 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int main(int argc,char **argv)
{
	(void)argv;
	if(argc == 5 || argc == 6)
	{
		printf("argumentos correctos\n");
		set_struct(argc,argv);
		return(0);
	}
	else
	{
		printf("argumentos incorrectos\n");
		return(1);
	}
	return(0);
}