/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:38:48 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/05 13:50:25 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mxinit(pthread_mutex_t *lock, t_ctx *ctx)
{
	int	code;
	
	code = pthread_mutex_init(lock, NULL);
	if (code != SUCCESS)
		errexit(code, "pthread_mutex_init()", &ctx);
}

void	mxdestroy(pthread_mutex_t *lock, t_ctx *ctx)
{
	int	code;
	
	code = pthread_mutex_destroy(lock);
	if (code != SUCCESS)
		errexit(code, "pthread_mutex_init()", &ctx);
}

void	mxlock(pthread_mutex_t *lock, t_ctx *ctx)
{
	int	code;
	
	code = pthread_mutex_lock(lock);
	if (code != SUCCESS)
		errexit(code, "pthread_mutex_lock()", &ctx);
}

void	mxunlock(pthread_mutex_t *lock, t_ctx *ctx)
{
	int	code;
	
	code = pthread_mutex_unlock(lock);
	if (code != SUCCESS)
		errexit(code, "pthread_mutex_unlock()", &ctx);
}

