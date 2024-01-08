#include "philo.h"

long int	ft_get_t(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int argv_to_int(char **argv,int pos,t_list *d)
{
	int value;
	printf("[pos=%i]\n",pos);
	value = ft_atoi(argv[pos]);
	printf("[value=%i]\n",value);

	if (value == 0 || value < 0 || (pos == 1 && value > 200)
	 || (pos == 2 && value < 60)|| (pos == 3 && value < 60)
	  || (pos == 4 && value < 60))
	{
		error(d,1);
	}
	if(pos == 1)
	{
		if(value == 1)
			error(d,3);
		else
			d->n_f=(size_t)value;
	}
	if(pos == 2)
		d->t_d=(size_t)value;
	if(pos == 3)
		d->t_e=(size_t)value;
	if(pos == 4)
		d->t_s=(size_t)value;
	if(pos == 5)
		d->nt_me=value;
	else
		d->nt_me= -1;
	d->time = ft_get_t();
	d->ok = 1;
	if(ft_struc_calloc(d) == 1)
		return (printf("Error creating structure\n"), free (d), 0);

	print_value(d);//
	ft_thread(d);
	free(d->fork);
	free(d->phi);
	return (free(d->eat_n), free(d->t_left), free(d), 0);
}

int ft_init_struct(char **argv)
{
	t_list *d;
	int i;

	i=1;
	d = NULL;
	d=ft_calloc(sizeof(t_list),1);
	if(d == NULL)
		return(1);
	while(argv[i] != NULL)
	{
		argv_to_int(argv,i,d);
		i++;
	}
	
	/* if(start_table(d) == 1)
		error(d,2); */
	return(0);
}

int main(int argc,char **argv)
{
	(void)argv;
	if(argc == 5 || argc == 6)
	{
		if(ft_init_struct(argv) == 1)
			return(1);
		else
			printf("Program end succesfully!\n");
	}
	else
	{
		printf("Incorrect number of arguments!\n");
		return(1);
	}

	return(0);
}