#include "philo.h"
void	ft_usleep(size_t t)
{
	size_t	start;

	start = ft_get_t();
	while ((ft_get_t() - start) < t)
		usleep(500);
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
		ft_watcher(f);
		//printf("ft_whach(f);\n");
	}
	if (f->p_n % 2 == 0 && f->p_n != f->d->n_f)
	{
		ft_live(f);
		//printf("1ft_live(f);\n");
	}
	else if (f->p_n % 2 != 0 && f->p_n != f->d->n_f)
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
	pthread_mutex_init(&d->ded, NULL);
	pthread_mutex_init(&d->eat, NULL);
	pthread_mutex_init(&d->print, NULL);
	pthread_mutex_init(&d->get_t, NULL);
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
	pthread_mutex_destroy(&d->ded);
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
		f =ft_calloc (sizeof(t_phi),1);
		if(f == NULL)
			return(1);
		f->p_n = i;
		f->d = d;
		if (pthread_create(&d->phi[i], NULL, &ft_born, f) != 0)//hacer funcion
			return (1);
		i++;
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
