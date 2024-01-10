#include "philo.h"

void ft_struc_calloc_bis(t_list *d)
{
	int	i;

	i = 0;
	while (i < d->n_f)//hacer una funcion para recortar lineas
	{
		d->eat_n[i] = 0;//setea a 0 el numero de veces que a comido cada filosofo
		//printf("d->eat_n[%i] = %d\n",i,d->eat_n[i]);//solo pruebas
		i++;
	}
	i = 0;
	while (i < d->n_f)
	{
		d->t_left[i] = d->time;//setea el tiempo actual en d->t_left
		//printf("d->t_left[%i] = %ld\n",i,d->t_left[i]);//solo pruebas
		i++;
	}
	printf("ft_struc_calloc OK\n");//solo pruebas
	return ;
}

int ft_struc_calloc(t_list *d)
{

	d->eat_n = ft_calloc (sizeof(int) , d->n_f);
	if (!d->eat_n)
		return (1);
	else
		printf("d->eat_n creado con exito\n");
	d->t_left = ft_calloc (sizeof(long) , d->n_f);
	if (d->t_left == 0)
		return (1);
	else
		printf("d->t_left creado con exito\n");
	d->phi = ft_calloc (sizeof(pthread_t) , (d->n_f + 1));
	if (!d->phi)
		return (1);
	else
		printf("d->phi creado con exito\n");
	d->fork = ft_calloc (sizeof(pthread_mutex_t) , d->n_f);
	if (!d->fork)
		return (1);
	else
		printf("d->fork creado con exito\n");
	ft_struc_calloc_bis(d);
	return(0);
}

int argv_to_int(char **argv,int pos,t_list *d)
{
	int value;

	printf("[pos=%i]\n",pos);
	value = ft_atoi(argv[pos]);
	printf("[value=%d]\n",value);
	if (value == 0 || value < 0 ||(pos == 1 && value > 200)
	 || (pos == 2 && value < 60)|| (pos == 3 && value < 60)
	  || (pos == 4 && value < 60))
		error(d,1);
	if(pos == 1)
		d->n_f=value;
	if(pos == 2)
		d->t_d=value;
	if(pos == 3)
		d->t_e=value;
	if(pos == 4)
		d->t_s=value;
	if(pos == 5)
		d->nt_me=value;
	else
		d->nt_me= -1;//si argv5 no existe setea nt_me en -1
	d->stop = 0;//si ok esta en 0 el programa sigue, sino para
	d->time = get_time();
	//print_value(d);//
	return (0);
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
		argv_to_int(argv,i,d);//cheackea los argumentos y los mete en t_list d
		i++;
	}
	if(d->n_f == 1)
		error(d,4);
	
	if(ft_struc_calloc(d) == 1)
		return (printf("Error creating structure\n"), free (d), 1);
	ft_thread(d);//crear un if para gestionar los errores
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