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

	size_t			n_f;
	size_t			t_d;
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
int argv_to_int(char **argv,int pos,t_list *d);
int ft_init_struct(char **argv);
int			main(int argc, char **argv);


/*ERROR*/
void print_value(t_list *d);
int ft_free_s(t_list *d);
int error(t_list *d,int n);
/*THREAD*/
int	ft_thread(t_list *d);
int ft_struc_calloc(t_list *d);

/*WHACH*/


/*LIVING*/

/*UTILS*/
void* ft_calloc(size_t num, size_t size);
size_t ft_strlen(const char *s);
char *ft_strdup(const char *s);
int	ft_spaces(char c);
int	ft_atoi(const char *str);

#endif