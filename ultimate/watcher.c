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
		pthread_mutex_lock(&f->d->ded);
		f->d->ok = 0;
		pthread_mutex_unlock(&f->d->ded);
		printf(RR"All the philosophers ate %d times!!\n"WW,f->d->nt_me);
	}
}

void	ft_watcher_t_d(t_phi *f)
{
	int	i;

	i = 0;
	while (ft_check_ok(f) && i < f->d->n_f)
	{
		pthread_mutex_lock(&f->d->get_t);
		if ((ft_get_t() - f->d->t_left[i]) >= f->d->t_d)
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