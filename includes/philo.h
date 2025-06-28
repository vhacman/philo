/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:55:03 by vhacman           #+#    #+#             */
/*   Updated: 2025/06/28 20:54:54 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

/* ************************************************************************** */
/*                               INCLUDES                                     */
/* ************************************************************************** */

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define COLOR_RESET     "\033[0m"
# define COLOR_GREEN     "\033[32m"
# define COLOR_RED       "\033[0;31m"
# define COLOR_CYAN      "\033[36m"
# define COLOR_ORANGE    "\033[38;5;208m"
# define COLOR_PURPLE    "\033[35m"

/* Dichiarazione forward della struttura filosofo */
typedef struct s_philo	t_philo;

typedef struct s_data
{
	/* === PARAMETRI DI INPUT === */
	int				num_philos;			// Numero di filosofi al tavolo
	int				time_to_die;		// Tempo massimo senza mangiare (ms)
	int				time_to_eat;		// Durata della fase di alimentazione (ms)
	int				time_to_sleep;		// Durata della fase di sonno (ms)
	int				meals_required;		// Pasti richiesti per filosofo (-1 se illimitato)

	/* === STATO DELLA SIMULAZIONE === */
	int				someone_died;		// Flag di morte per terminazione
	long			start_time;			// Timestamp di inizio simulazione (ms)

	/* === THREAD DI CONTROLLO === */
	pthread_t		monitor;			// Thread per monitoraggio delle morti

	/* === MUTEX PER SINCRONIZZAZIONE === */
	pthread_mutex_t	*forks;				// Array di mutex per le forchette
	pthread_mutex_t	print_lock;			// Protegge l'output sulla console
	pthread_mutex_t	death_lock;			// Protegge il flag someone_died
	pthread_mutex_t	meal_lock;			// Protegge l'accesso a last_meal_time
	pthread_mutex_t	status_lock;
	/* === RIFERIMENTO AI FILOSOFI === */
	t_philo			*philos;			// Array delle strutture filosofo
	int				all_ate;
}	t_data;


typedef struct s_philo
{
	/* === IDENTIFICAZIONE === */
	int				id;					// Identificatore univoco filosofo (base 1)

	/* === STATO DEI PASTI === */
	int				meals_eaten;		// Numero di pasti consumati
	long			last_meal_time;		// Timestamp dell'ultimo inizio pasto (ms)

	/* === THREAD ASSOCIATO === */
	pthread_t		thread;				// Handle del thread del filosofo

	/* === ACCESSO ALLE FORCHETTE === */
	pthread_mutex_t	*left_fork;			// Puntatore al mutex forchetta sinistra
	pthread_mutex_t	*right_fork;		// Puntatore al mutex forchetta destra

	/* === RIFERIMENTO AI DATI GLOBALI === */
	t_data			*data;				// Riferimento alla struttura dati globale
}	t_philo;

int main(int ac, char **av);

int			is_number(char *str);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);

int			init_simulation(t_data *data);
int			initialize_data(t_data *data);
int			init_mutexes(t_data *data);
int			init_single_mutex(pthread_mutex_t *mutex, char *name);
int			create_threads(t_data *data);
int			join_threads(t_data *data);
void		*philo_routine(void *philo_arg);
void	precise_usleep(long m_seconds_to_wait, t_data *data);

/*parsing*/
int			is_error(int ac, char **av);
int			is_valid_time(int value);
int			is_valid_meals(int ac, int meals);
int			parse_args(int ac, char **av, t_data *data);
int			check_death(t_data *data);
void		set_death(t_data *data);
int	handle_single_philo(t_philo *philo);
void	release_forks(t_philo *philo);
int	take_forks(t_philo *philo);
int	take_two_forks(t_philo *philo);
void	print_philo_status(t_philo *philo, char *msg);
int	check_all_meals_done(t_data *data);
void	*monitor(void	*philo);
int	check_philo_death(t_data *data, int philo_idx);
int init_forks(t_data *data);
long	get_time();
int			cleanup_mutexes(t_data *data);
int		cleanup_simulation_stage(t_data *data, int stage);
void		cleanup_philos(t_data *data);
int		cleanup_forks(t_data *data);
void		cleanup_simulation(t_data *data);
void	update_meal_time(t_philo *philo);
#endif
