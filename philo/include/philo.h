/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:32:26 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/03 19:47:47 by vvoronts         ###   ########.fr       */
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
	int					id;
	pthread_t			thread;
	pthread_mutex_t		lfork;
	pthread_mutex_t		rfork;
	bool				eat;
	bool				dead;
	int					meals;
	int					musteat;
	int					last;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	t_ctx				*dining;
	pthread_mutex_t		meallock;
	pthread_mutex_t		writelock;
	pthread_mutex_t		deadlock;
}	t_thread;

typedef struct s_ctx
{
	pthread_t			waiter;
	t_thread			*philos;
	int					number;
	bool				death;
	pthread_mutex_t		meallock;
	pthread_mutex_t		writelock;
	pthread_mutex_t		deadlock;
	size_t				start;
}	t_ctx;

// programm
void	init(t_ctx **dining, int argc, char **argv);
void	*routine(void *arg);
void	*monitor(void *arg);


// utils
void	writestd(const char *msg, int std);
void	errexit(int err, const char *msg, t_ctx *dining);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
void	*memalloc(size_t size, t_ctx *dining);
void	destroy(t_ctx *dining);

size_t	get_current_time(void);
int	ft_usleep(size_t milliseconds);

#endif