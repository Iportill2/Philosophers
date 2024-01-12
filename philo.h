/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iportill <iportill@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:14:57 by iportill          #+#    #+#             */
/*   Updated: 2024/01/12 13:42:08 by iportill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>

# define WW "\033[0m"    
# define RR "\033[91m"   
# define GG "\033[92m"   
# define BB "\033[94m"   
# define OO "\033[93m"   
# define YY "\033[33m"   
# define CC "\033[96m" 
# define KK "\033[90m" 

typedef struct s_list
{
	size_t			stop;

	int				n_f;
	size_t			t_d;
	size_t			t_e;
	size_t			t_s;

	int				nt_me;
	int				*eat_n;

	long			time;

	size_t			*t_left;
	pthread_t		*phi;
	pthread_mutex_t	*fork_mutex;

	pthread_mutex_t	get_t_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	eat_mutex;
}				t_list;

typedef struct s_phi
{
	int				phi_id;
	int				right_fork;
	int				left_fork;
	t_list			*d;
}				t_phi;

/*MAIN*/
void	argv_to_int(char **argv, int pos, t_list *d);
int		ft_init_struct(char **argv);
int		main(int argc, char **argv);
int		ft_struc_calloc(t_list *d);
void	ft_struc_calloc_bis(t_list *d);

/*ERROR*/
int		error(t_list *d, int n);
void	ft_free_d(t_list *d);
/*THREAD*/
void	ft_mutex_init(t_list *d);
void	ft_mutex_destroy(t_list *d);
int		ft_thread(t_list *d);
void	*watch_phi_rou(void *born);
void	ft_usleep(size_t t);

/*WATCHER*/
size_t	get_time(void);
void	ft_watcher_nt_me(t_phi *f);
void	ft_watcher_t_d(t_phi *f);
void	ft_watcher(t_phi *f);

/*LIVING*/
int		ft_check_ok(t_phi *f);
void	ft_dead(t_phi *f, int p_n);
void	ft_eating(t_phi *f, int p_n);
void	ft_eat(t_phi *f);
void	ft_routine(t_phi *f);

/*UTILS*/
void	*ft_calloc(size_t num, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int		ft_spaces(char c);
int		ft_atoi(const char *str);

#endif