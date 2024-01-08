#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>

typedef struct s_list
{
	size_t			ok;

	int 			n_f;
	long			t_d;
	size_t			t_e;
	size_t			t_s;

	int			nt_me;

	long			time;
	int				*eat_n;
	long			*t_left;
	pthread_t		*phi;
	pthread_mutex_t	get_t;
	pthread_mutex_t	print;
	pthread_mutex_t	ded;
	pthread_mutex_t	eat;
	pthread_mutex_t	*fork;
}				t_list;

typedef struct s_phi
{
	int				p_n;
	int				f1;
	int				f2;
	t_list			*d;
}				t_phi;

/*MAIN*/
long int	ft_get_t(void);
int 		argv_to_int(char **argv,int pos,t_list *d);
int			ft_init_struct(char **argv);
int			main(int argc, char **argv);
int 		ft_struc_calloc(t_list *d);


/*ERROR*/
void	print_value(t_list *d);
int		ft_free_s(t_list *d);
int 	error(t_list *d,int n);
/*THREAD*/
void	ft_mutex_init(t_list *d);
void	ft_mutex_destroy(t_list *d);
int		ft_thread(t_list *d);
void	*ft_born(void *arg);
void	ft_usleep(size_t t);

/*WHACH*/
void	ft_whach_nt_me(t_phi *f);
void	ft_whach_t_d(t_phi *f);
void	ft_whach(t_phi *f);

/*LIVING*/
int	ft_check_ok(t_phi *f);
void	ft_dead(t_phi *f, int p_n);
void	ft_eating(t_phi *f, int p_n);
void	ft_eat(t_phi *f);
void	ft_live(t_phi *f);

/*UTILS*/
void	*ft_calloc(size_t num, size_t size);
size_t 	ft_strlen(const char *s);
char 	*ft_strdup(const char *s);
int		ft_spaces(char c);
int		ft_atoi(const char *str);

#endif