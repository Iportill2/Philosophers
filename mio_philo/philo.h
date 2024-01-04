#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo//esta structura representa a cada philo 
{
	size_t num_eats;//numero de veces que ha comido
	size_t last_eat;//la ultima vez que comio
	size_t fork_r;//mano r con tenedor(si cumple ambas puede comer)
	size_t fork_l;//mano l con tenedor(si cumple ambas puede comer)
}t_philo;

typedef struct s_list
{
	size_t time_sleep;
	char *prueba;
	size_t init_philo;
	size_t stat;
	size_t id;
	size_t num_philo;//numero de filosofos >200
	size_t time_to_die;//tiempo para morir <60
	size_t time_to_eat;//tiempo que comen  <60
	size_t time_to_sleep;//tiempo que duermen < 60
	size_t time_to_think;//tiempo que piensan
	size_t philo_eats;//contador que se usa en caso de haber metido el paramero argv(6)correctamente
	
	/*se reserva memoria en init_values*/
	pthread_t	*thread;//
	t_philo	*philo;//puntero  a la structura philo
	pthread_mutex_t *mutex;
	
	pthread_mutex_t mutex_last_eat;
	pthread_mutex_t mutex_stat;
	pthread_mutex_t mutex_i;
	pthread_mutex_t mutex_msg;
	pthread_mutex_t mutex_fork;
	long	s_time;//variable para guardar el tiempo del sistema
}t_list;

/*MAIN*/
int main (int argc,char **argv);
int ft_init_struct(char **argv);
int argv_to_int(char **argv,int pos,t_list *d);
int init_values(t_list *d);
int start_table(t_list *d);
//void ft_temp_free(char *temp);
/*UTILS*/
void* ft_calloc(size_t num, size_t size);
size_t ft_strlen(const char *s);
char *ft_strdup(const char *s);
int	ft_atoi(const char *str);
int	ft_spaces(char c);
/*ERROR*/
int error(t_list *d,int n);

void print_value(t_list *d);
/*create_thread&mutex*/
long	time_calc(void);
int create_mutex(t_list *d);
int create_thread(t_list *d);
void *philo_routine(void *f);
int routine(t_list *d); 

#endif