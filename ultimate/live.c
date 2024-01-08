#include "philo.h"

int	ft_check_ok(t_phi *f)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&f->d->ded);
	if (f->d->ok)
		i = 1;
	pthread_mutex_unlock(&f->d->ded);
	return (i);
}

void	ft_dead(t_phi *f, int p_n)
{
	pthread_mutex_lock(&f->d->ded);
	if (f->d->ok == 1)
	{
		f->d->ok = 0;
		pthread_mutex_lock(&f->d->print);
		printf("Elapsed run time%lu\nPhilo nº%i died ☠️\n\n", ft_get_t() - f->d->time, p_n + 1);
		
		pthread_mutex_unlock(&f->d->print);
	}
	pthread_mutex_unlock(&f->d->ded);
}

void	ft_eating(t_phi *f, int p_n)
{
	pthread_mutex_lock(&f->d->get_t);
	f->d->t_left[p_n] = ft_get_t();
	pthread_mutex_unlock(&f->d->get_t);
	pthread_mutex_lock(&f->d->print);
	printf(G"Elapsed run time%lu\nPhilo nº%i is eating🍜\n\n"W, ft_get_t() - f->d->time, p_n + 1);
	pthread_mutex_unlock(&f->d->print);
	pthread_mutex_lock(&f->d->eat);
	f->d->eat_n[p_n] += 1;
	pthread_mutex_unlock(&f->d->eat);
	ft_usleep(f->d->t_e);
	pthread_mutex_unlock(&f->d->fork[f->f1]);
	pthread_mutex_unlock(&f->d->fork[f->f2]);
}

void	ft_eat(t_phi *f)
{
	pthread_mutex_lock(&f->d->fork[f->f1]);
	if (ft_check_ok(f))
	{
		pthread_mutex_lock(&f->d->print);
		printf("Elapsed run time%lu\nPhilo nº%i has taken a right fork 🍴\n\n", ft_get_t() - f->d->time, f->p_n + 1);
		pthread_mutex_unlock(&f->d->print);
	}		
	pthread_mutex_lock(&f->d->fork[f->f2]);
	if (ft_check_ok(f))
	{
		pthread_mutex_lock(&f->d->print);
		printf("Elapsed run time%lu\nPhilo nº%i has taken a left fork 🍴🍴\n\n", ft_get_t() - f->d->time, f->p_n + 1);
		pthread_mutex_unlock(&f->d->print);
	}
	if (ft_check_ok(f))
		ft_eating (f, f->p_n);
}

void	ft_live(t_phi *f)
{
	while (ft_check_ok(f))
	{
		ft_eat(f);
		if (ft_check_ok(f))
		{
			pthread_mutex_lock(&f->d->print);
			printf("Elapsed run time%lu\nPhilo nº%i is sleeping😴\n\n", ft_get_t() - f->d->time, f->p_n + 1);
			pthread_mutex_unlock(&f->d->print);
			ft_usleep(f->d->t_s);
		}
		if (ft_check_ok(f))
		{
			pthread_mutex_lock(&f->d->print);
			printf ("Elapsed run time%lu\nPhilo nº%i is thinking🙇🏻💭\n\n", ft_get_t() - f->d->time, f->p_n + 1);
			pthread_mutex_unlock(&f->d->print);
		}
	}
}