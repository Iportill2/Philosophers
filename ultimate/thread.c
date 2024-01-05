#include "philo.h"


int	ft_thread(t_list *d)
{
	int		i;
	t_phi	*f;

	ft_mutex_init(d);//hacer funcion
	i = 0;
	while (i <= d->n_f)
	{
		f = malloc (sizeof(t_phi));
		f->p_n = i;
		f->d = d;
		if (pthread_create(&d->phi[i++], NULL, &ft_born, f) != 0)//hacer funcion
			return (1);
	}
	i = 0;
	while (i <= d->n_f)
	{
		if (pthread_join(d->phi[i], NULL) != 0)
			return (1);
		i++;
	}
	ft_mutex_destroy(d);
	return (0);
}
int ft_struc_calloc(t_list *d)
{
	size_t	i;

	d->fork = malloc (sizeof(pthread_mutex_t) * d->n_f);
	if (!d->fork)
		return (0);
	d->phi = malloc (sizeof(pthread_t) * (d->n_f + 1));
	if (!d->phi)
		return (0);
	d->eat_n = malloc (sizeof(int) * d->n_f);
	if (!d->eat_n)
		return (0);
	d->t_left = malloc (sizeof(long) * d->n_f);
	if (d->t_left == 0)
		return (0);
	i = 0;
	while (i < d->n_f)//hacer una funcion para recortar lineas
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
	return (1);
}