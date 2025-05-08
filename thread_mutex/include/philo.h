/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:32:26 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/08 18:14:27 by vvoronts         ###   ########.fr       */
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

typedef struct s_ctx t_ctx;
typedef struct s_thread t_thread;

typedef struct s_thread
{
	pthread_t			thread;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	long				id;
	long				ate;
	long				t_meal;
	bool				eating;
	t_ctx				*ctx;
}	t_thread;

typedef struct s_ctx
{
	pthread_t			waiter;
	t_thread			*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*mealmx;
	pthread_mutex_t		*deadmx;
	pthread_mutex_t		*rwmx;
	bool				death;
	bool				ready;
	
	long				t_born;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				n_ph;
	long				meals;
}	t_ctx;

// programm
void	validate(char **argv, int argc);
void	init(t_ctx **ctx, char **argv);
void	init_philo(t_thread *philo, t_ctx *ctx, int i);
void	simulate(t_ctx **ctx);
void	destroy(t_ctx **ctx);
//
void	*routine(void *arg);
void	*monitor(void *arg);
void	sync_threads(t_ctx *ctx);
//

// utils
void	mxinit(pthread_mutex_t *lock, t_ctx *ctx);
void	mxdestroy(pthread_mutex_t *lock, t_ctx *ctx);
void	mxlock(pthread_mutex_t *lock, t_ctx *ctx);
void	mxunlock(pthread_mutex_t *lock, t_ctx *ctx);
void	writestatus(t_thread *philo, char *str);
void	writestd(const char *msg, int std);
void	errexit(int err, const char *msg, t_ctx **ctx);
long	gettime(void);
void	waittime(long time);
void	*memalloc(long size, t_ctx *ctx);
int		ft_atoi(const char *str);
long	ft_strlen(const char *str);

#endif