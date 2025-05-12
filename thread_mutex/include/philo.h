/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:32:26 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/12 16:55:38 by vvoronts         ###   ########.fr       */
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

typedef struct s_ctx;
typedef struct s_philo;

typedef struct s_ctx
{
	struct t_philo		*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*uni_lock;
	pthread_mutex_t		*write_lock;
	bool				f_end;
	bool				f_ready;
	bool				f_error;
	long				t_start;
	int					n_philos;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	int					n_meals;
}	t_ctx;

typedef struct s_philo
{
	int					id;
	pthread_t			id_pthread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long				t_last_meal;
	int					n_meals;
	t_ctx				*ctx;
}	t_philo;


// 
int		validate(char **argv, int argc);
int		init(t_ctx *ctx, char **argv);
int		ft_exit(int err, const char *msg, t_ctx *ctx);

void	init_philo(t_philo *philo, t_ctx *ctx, int i);
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
void	writestatus(t_philo *philo, char *str);
void	writestd(const char *msg, int std);
long	gettime(void);
void	waittime(long time);
void	*memalloc(long size, t_ctx *ctx);
int		ft_atoi(const char *str);
long	ft_strlen(const char *str);

#endif