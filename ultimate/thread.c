#include "philo.h"

void	ft_mutex_init(t_list *d)
{
	size_t	i;

	i = 0;
	while (i < d->n_f)
	{
		pthread_mutex_init(&d->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&d->ded, NULL);
	pthread_mutex_init(&d->eat, NULL);
	pthread_mutex_init(&d->print, NULL);
	pthread_mutex_init(&d->get_t, NULL);
}

void	ft_mutex_destroy(t_list *d)
{
	size_t	i;

	i = 0;
	while (i < d->n_f)
	{
		pthread_mutex_destroy(&d->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&d->ded);
	pthread_mutex_destroy(&d->eat);
	pthread_mutex_destroy(&d->print);
	pthread_mutex_destroy(&d->get_t);
}

void	*ft_born(void *arg)
{
	t_phi	*f;

	f = (t_phi *)arg;
	f->f1 = f->p_n;
	if (f->p_n == f->d->n_f - 1)
		f->f2 = 0;
	else
		f->f2 = f->p_n + 1;
	if (f->p_n == f->d->n_f)
	{
		//ft_whach(f);
		printf("ft_whach(f);");
	}
	if (f->p_n % 2 == 0 && f->p_n != f->d->n_f)
	{
		//ft_live(f);
		printf("ft_live(f);");
	}
	else if (f->p_n % 2 != 0 && f->p_n != f->d->n_f)
	{
		usleep((10) * 1000);
		//ft_live(f);
		printf("ft_live(f);");
	}
	free (f);
	return (0);
}

int	ft_thread(t_list *d)
{
	size_t		i;
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

	d->fork = ft_calloc (sizeof(pthread_mutex_t) , d->n_f);
	if (!d->fork)
		return (0);
	d->phi = ft_calloc (sizeof(pthread_t) , (d->n_f + 1));
	if (!d->phi)
		return (0);
	d->eat_n = ft_calloc (sizeof(int) , d->n_f);
	if (!d->eat_n)
		return (0);
	d->t_left = ft_calloc (sizeof(long) , d->n_f);
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