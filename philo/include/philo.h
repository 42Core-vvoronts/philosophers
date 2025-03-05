/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:32:26 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/05 13:51:02 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>     // memset
# include <stdio.h>      // printf
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
	pthread_mutex_t		leftlock;
	pthread_mutex_t		rightlock;
	int					id;
	int					ate;
	size_t				t_born;
	int					t_meal;
	t_ctx				*ctx;
}	t_thread;

typedef struct s_ctx
{
	pthread_t			waiter;
	t_thread			*philos;
	pthread_mutex_t		deadlock;
	pthread_mutex_t		meallock;
	pthread_mutex_t		lock;
	bool				death;
	int					n_ph;
	int					meals;
	size_t				t_die;
	size_t				t_eat;
	size_t				t_sleep;
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
//

// utils
void	mxinit(pthread_mutex_t *lock, t_ctx *ctx);
void	mxdestroy(pthread_mutex_t *lock, t_ctx *ctx);
void	mxlock(pthread_mutex_t *lock, t_ctx *ctx);
void	mxunlock(pthread_mutex_t *lock, t_ctx *ctx);
void	writestatus(t_thread *philo, char *str);
void	writestd(const char *msg, int std);
void	errexit(int err, const char *msg, t_ctx **ctx);
size_t	gettime(void);
void	waittime(size_t time);
void	*memalloc(size_t size, t_ctx *ctx);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);

#endif