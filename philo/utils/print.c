/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:18:50 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/19 11:52:08 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	writestatus(t_philo *philo, char *str)
{
	mxlock(philo->ctx->write_lock, philo->ctx);
	philo->t_now = gettime(philo->ctx) - philo->ctx->t_start;
    printf("%011ld %d %s\n", philo->t_now, philo->id, str);
	mxunlock(philo->ctx->write_lock, philo->ctx);	
}
