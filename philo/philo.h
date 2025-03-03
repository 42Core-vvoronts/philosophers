/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:32:26 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/03 11:25:41 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <string.h>     // memset
#include <stdio.h>      // printf
#include <stdlib.h>     // malloc, free
#include <unistd.h>     // write, usleep
#include <sys/time.h>   // gettimeofday
#include <pthread.h>    // pthread_* functions

// number_of_philosophers: 
//	The number of philosophers and also the number of forks
//
// time_to_die: (in milliseconds): 
//	If a philosopher has not started eating within 
//	time_to_die milliseconds since the beginning of their last meal 
//	or the start of the simulation, he dies.
// 
// time_to_eat:(in milliseconds): 
//	The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
//
// time_to_sleep: (in milliseconds): 
//	The time a philosopher will spend sleeping.
//
// [number_of_times_each_philosopher_must_eat](optional argument): 
//	If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, 
//	the simulation stops. If not specified, the simulation stops when a philosopher dies.
//

// typedef struct s_philo
// {
// 	pthread_t		*philo;
// 	int				time_to_die;
// 	int				time_to_eat;
// 	int				time_to_sleep;
// 	int				number_of_times_each_philosopher_must_eat;
// }	t_philo;


void	validate(int argc, char **argv);

#endif