/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:55:03 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 19:08:27 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/*                              INCLUDES                                      */
/* ************************************************************************** */

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* ************************************************************************** */
/*                              COLOR CODES                                   */
/* ************************************************************************** */

# define COLOR_RESET     "\033[0m"
# define COLOR_RED       "\033[0;31m"
# define COLOR_GREEN     "\033[1;32m"
# define COLOR_BLUE      "\033[0;34m"
# define COLOR_CYAN      "\033[1;36m"
# define COLOR_YELLOW    "\033[0;33m"
# define COLOR_PURPLE    "\033[35m"
# define COLOR_ORANGE    "\033[38;5;208m"

/* ************************************************************************** */
/*                              STRUCTURES                                    */
/* ************************************************************************** */

typedef struct s_philo	t_philo;

typedef struct s_data
{
	/* Input parameters */
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;

	/* Simulation state */
	int				someone_died;
	int				all_ate;
	long			start_time;

	/* Threads */
	pthread_t		monitor;
	t_philo			*philos;

	/* Synchronization */
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	status_lock;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

/* ************************************************************************** */
/*                              FUNCTION PROTOTYPES                          */
/* ************************************************************************** */

/* === MAIN & CORE === */
int		main(int ac, char **av);
int		init_simulation(t_data *data);
int		create_threads(t_data *data);
int		join_threads(t_data *data);
void	*philo_routine(void *philo_arg);
int		create_monitor_thread(t_data *data);

/* === ARGUMENT PARSING === */
int		parse_args(int ac, char **av, t_data *data);
int		is_error(int ac, char **av);
int		is_valid_time(int value);
int		is_valid_meals(int ac, int meals);
int		is_valid_philos(int n_philos);

/* === TIME UTILITIES === */
long	get_time(void);
void	precise_usleep(long m_seconds_to_wait, t_data *data, t_philo *philo);
long	calculate_initial_delay(t_data *data);

/* === PHILOSOPHER ACTIONS === */
void	philo_eat(t_philo *philo);
void	philo_sleep_and_think(t_philo *philo);
int		handle_single_philo(t_philo *philo);
int		has_completed_meals(t_data *data, int philo_idx);

/* === FORK MANAGEMENT === */
int		take_forks(t_philo *philo);
int		take_two_forks(t_philo *philo);
void	release_forks(t_philo *philo);

/* === MONITORING === */
void	*monitor(void *philo);
int		check_philo_death(t_data *data, int philo_idx);
int		check_all_meals_done(t_data *data);
int		check_if_is_dead(t_data *data);
void	set_death(t_data *data);

/* === INITIALIZATION & CLEANUP === */
int		init_mutexes(t_data *data);
int		init_forks(t_data *data);
int		cleanup_forks(t_data *data);
void	cleanup_simulation(t_data *data);
int		cleanup_simulation_stage(t_data *data, int stage);

/* === OUTPUT === */
void	print_philo_status(t_philo *philo, char *msg);
void	print_numeric_error(void);
void	print_usage_error(void);

/* === UTILITY FUNCTIONS === */
int		is_number(char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
