#include "philo.h"
void	ft_usleep(size_t t)
{
	size_t	start;

	start = ft_get_t();
	while ((ft_get_t() - start) < t)
		usleep(500);
}

void	*watch_phi_rou(void *born)
{
	t_phi	*f;

	f = (t_phi *)born;
	f->f1 = f->phi_id;//asigna el tenedor 1 a cada philo
	if (f->phi_id == f->d->n_f - 1)
		f->f2 = 0;//asigna el tenedor 2 con la posicion 0
	else
		f->f2 = f->phi_id + 1;//asigna el tenedor 2 en la posicion del philo +1
	if (f->phi_id == f->d->n_f)
	{
		ft_watcher(f);
		//printf("ft_whach(f);\n");
	}
	if (f->phi_id % 2 == 0 && f->phi_id != f->d->n_f)
	{
		ft_live(f);//check
		//printf("1ft_live(f);\n"); 
	}
	else if (f->phi_id % 2 != 0 && f->phi_id != f->d->n_f)
	{
		usleep((10) * 1000);
		ft_live(f);
		//printf("2ft_live(f);\n");
	}
	free (f);
	return (0);
}

void	ft_mutex_init(t_list *d)
{
	int	i;


	i = 0;
	while (i < d->n_f)
	{
		pthread_mutex_init(&d->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&d->dead, NULL);//mutex para ded
	pthread_mutex_init(&d->eat, NULL);//mutex para eat
	pthread_mutex_init(&d->print, NULL);//mutex para imprimir
	pthread_mutex_init(&d->get_t, NULL);//mutex para get_time
	printf("ft_mutex_init ejecutado con exito\n");
}

void	ft_mutex_destroy(t_list *d)
{
	int	i;

	i = 0;
	while (i < d->n_f)
	{
		pthread_mutex_destroy(&d->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&d->dead);
	pthread_mutex_destroy(&d->eat);
	pthread_mutex_destroy(&d->print);
	pthread_mutex_destroy(&d->get_t);
	printf("ft_mutex_destroy ejecutado con exito\n");
}



int	ft_thread(t_list *d)
{
	int		i;
	t_phi	*f;

	ft_mutex_init(d);//hacer funcion
	i = 0;
	while (i <= d->n_f)
	{
		f =ft_calloc (sizeof(t_phi),1);//reserva memoria para cada struc phi
		if(f == NULL)
			return(1);
		f->phi_id = i;
		f->d = d;
		if (pthread_create(&d->phi[i], NULL, &watch_phi_rou, f) != 0)//crea los hilos con su rutina
			return (1);
		i++;
	}
	i = 0;
	while (i <= d->n_f)
	{
		if (pthread_join(d->phi[i], NULL) != 0)//espera a que termine cada hilo creado con pthread_create
			return (1);
		i++;
	}
	ft_mutex_destroy(d);//destruye los hilos
	return (0);
}
