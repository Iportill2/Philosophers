#include "philo.h"

void	ft_watcher_nt_me(t_phi *f)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (i < f->d->n_f)
	{
		pthread_mutex_lock(&f->d->eat);
		if (f->d->eat_n[i] >= f->d->nt_me)
			c++;
		pthread_mutex_unlock(&f->d->eat);
		i++;
	}
	if (c == f->d->n_f)
	{
		pthread_mutex_lock(&f->d->dead);
		f->d->stop = 1;//lo ponemos para que terminen los hilos despues de imprimir el mensaje, sino corta la rutina 
		pthread_mutex_unlock(&f->d->dead);
		printf(RR"All the philosophers ate %d times!!\n"WW,f->d->nt_me);
	}
}

void	ft_watcher_t_d(t_phi *f)
{
	int	i;

	i = 0;
	while (ft_check_ok(f) == 1 && i < f->d->n_f)
	{
		pthread_mutex_lock(&f->d->get_t);
		if ((get_time() - f->d->t_left[i]) >= f->d->t_d)
		{
			ft_dead(f, i);
			//printf("ft_dead(f,i);\n");
		}
		pthread_mutex_unlock(&f->d->get_t);
		i++;
	}
}

void	ft_watcher(t_phi *f)
{
	while (ft_check_ok(f) == 1)
	{
		usleep(100);
		if (f->d->nt_me != -1)
			ft_watcher_nt_me(f);
		ft_watcher_t_d(f);
	}
}
void ft_struc_calloc_bis(t_list *d)
{
	int	i;

	i = 0;
	while (i < d->n_f)//hacer una funcion para recortar lineas
	{
		d->eat_n[i] = 0;//setea a 0 el numero de veces que a comido cada filosofo
		printf("d->eat_n[%i] = %d\n",i,d->eat_n[i]);//solo pruebas
		i++;
	}
	i = 0;
	while (i < d->n_f)
	{
		d->t_left[i] = d->time;//setea el tiempo actual en d->t_left
		printf("d->t_left[%i] = %ld\n",i,d->t_left[i]);//solo pruebas
		i++;
	}
	printf("ft_struc_calloc OK\n");//solo pruebas
	return ;
}