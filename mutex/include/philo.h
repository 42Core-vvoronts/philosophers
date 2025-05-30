/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:32:26 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/21 12:23:59 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>     // memset
# include <stdio.h>      // prlongf
# include <stdlib.h>     // malloc, free
# include <unistd.h>     // write, usleep
# include <sys/time.h>   // gettimeofday
# include <pthread.h>    // pthread_* functions
# include <stdbool.h>    // bool type

# define MAXPH 200
# define FAIL -1
# define SUCCESS 0

typedef struct s_ctx	t_ctx;

typedef struct s_philo
{
	int					id;
	pthread_t			id_pthread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long				t_last_meal;
	long				t_remain;
	long				t_now;
	long				t_think;
	int					n_meals;
	t_ctx				*ctx;
}	t_philo;

typedef struct s_ctx
{
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*uni_lock;
	pthread_mutex_t		*die_lock;
	pthread_mutex_t		*write_lock;
	int					n_philos;
	int					n_full;
	int					n_meals;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				t_start;
	long				t_end;
	bool				f_ready;
	bool				f_end;
	bool				f_death;
	bool				f_error;
}	t_ctx;

int		validate(char **argv, int argc);
t_ctx	*init(char **argv);
void	init_philo(t_ctx *ctx, int i);
void	destroy(t_ctx *ctx);
void	simulate(t_ctx *ctx);
void	wait_threads(t_ctx *ctx);
void	queue_threads(t_philo *philo, t_ctx *ctx);
void	*routine(void *arg);
void	eating(t_philo *philo, t_ctx *ctx);
void	sleeping(t_philo *philo, t_ctx *ctx);
void	thinking(t_philo *philo, t_ctx *ctx);
bool	is_end(t_philo *philo, t_ctx *ctx);
bool	is_dead(t_philo *philo);
void	register_as_full(t_ctx *ctx);
bool	everyone_full(t_ctx *ctx, t_philo *philo);
// mutex wrappers
int		mxinit(pthread_mutex_t *lock, t_ctx *ctx);
int		mxdestroy(pthread_mutex_t *lock, t_ctx *ctx);
int		mxlock(pthread_mutex_t *lock, t_ctx *ctx);
int		mxunlock(pthread_mutex_t *lock, t_ctx *ctx);
// utils
void	*memalloc(size_t size, void *ctx);
void	esleep(t_philo *philo, long t_act);
int		ft_exit(int err, const char *msg, t_ctx *ctx);
long	ft_atol(const char *str);
long	ft_strlen(const char *str);
void	writestatus(t_philo *philo, char *str);
void	writedeath(t_philo *philo);
void	writestd(const char *msg, int std);
long	gettime(t_ctx *ctx);

#endif