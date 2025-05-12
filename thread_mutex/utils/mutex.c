/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:38:48 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/12 15:19:35 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mxinit(pthread_mutex_t *lock, t_ctx *ctx)
{
	int	code;
	
	code = pthread_mutex_init(lock, NULL);
	if (code != SUCCESS)
		return (ft_exit(FAIL, "pthread_mutex_init()", ctx));
}

int	mxdestroy(pthread_mutex_t *lock, t_ctx *ctx)
{
	int	code;
	
	code = pthread_mutex_destroy(lock);
	if (code != SUCCESS)
		return (ft_exit(FAIL, "pthread_mutex_destroy()", ctx));
}

int	mxlock(pthread_mutex_t *lock, t_ctx *ctx)
{
	int	code;
	
	code = pthread_mutex_lock(lock);
	if (code != SUCCESS)
		return (ft_exit(FAIL, "pthread_mutex_lock()", ctx));
}

int	mxunlock(pthread_mutex_t *lock, t_ctx *ctx)
{
	int	code;
	
	code = pthread_mutex_unlock(lock);
	if (code != SUCCESS)
		return (ft_exit(FAIL, "pthread_mutex_unlock()", ctx));
}
