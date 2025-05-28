/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:32:26 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/28 16:49:29 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>     // memset
# include <unistd.h>     //fork(), exec()
# include <sys/wait.h>   // wait(), waitpid()
# include <signal.h>     // kill()
# include <pthread.h>    // pthread_* functions
# include <semaphore.h>  // semaphores
# include <stdlib.h>     // malloc, free
# include <unistd.h>     // write, usleep
# include <sys/time.h>   // gettimeofday
# include <stdbool.h>    // bool type
# include <stdio.h>      //
# include <fcntl.h>

# define MAXPH 200
# define SUCCESS 0
# define FAIL -1
# define FULL 1
# define DIED 2
# define SEMFORK "/forks"
# define SEMDIE "/die"
# define SEMWRI "/write"
# define SEMFUL "/full"
# define SEMUNI "/universal"
# define SEMGO "/go"

typedef struct s_ctx	t_ctx;

typedef struct s_philo
{
	int					id;
	int					pid;
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
	pthread_t			*observer;
	sem_t				*forks;
	sem_t				*semful;
	sem_t				*semdie;
	sem_t				*semuni;
	sem_t				*semwri;
	sem_t				*go;
	int					n_philos;
	int					n_meals;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				t_start;
}	t_ctx;

int		validate(char **argv, int argc);
t_ctx	*init(char **argv);
void	simulate(t_ctx *ctx);
void	*routine(t_philo *philo);
void	eating(t_philo *philo, t_ctx *ctx);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	check_death(t_philo *philo);
void	queue_philos(t_philo *philo, t_ctx *ctx);
void	kill_all_philos(t_ctx *ctx);
void	monitor_death(t_ctx *ctx);
void	monitor_meals(t_ctx *ctx);
void	*monitor_full(void *arg);
void	destroy(t_philo *philo, t_ctx *ctx);
// sem wrappers
sem_t	*smopen(const char *name, unsigned int value, t_ctx *ctx);
void	smclose(sem_t *sem, t_ctx *ctx);
void	smwait(sem_t *sem, t_ctx *ctx);
void	smpost(sem_t *sem, t_ctx *ctx);
void	smunlink(const char *name, t_ctx *ctx);
//
void	join_thread(pthread_t *thread, t_ctx *ctx);
void	create_thread(pthread_t *t, void *(*f)(void *), void *arg, t_ctx *ctx);
// utils
void	*memalloc(size_t size, void *ctx);
void	esleep(t_philo *philo, long t_act);
void	ft_exit(int err, const char *msg, t_ctx *ctx);
long	ft_atol(const char *str);
long	ft_strlen(const char *str);
void	writestatus(t_philo *philo, char *str);
void	writedeath(t_philo *philo);
void	writestd(const char *msg, int std);
long	gettime(t_ctx *ctx);

#endif