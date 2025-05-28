/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:18:50 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/28 14:35:15 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	writestatus(t_philo *philo, char *str)
{
	// smwait(philo->ctx->semwri, philo->ctx);
	// smwait(philo->ctx->semdie, philo->ctx);
	// if (philo->ctx->f_end == true)
	// {
	// 	// smpost(philo->ctx->semdie, philo->ctx);
	// 	// smpost(philo->ctx->semwri, philo->ctx);
	// 	return ;
	// }
	// smpost(philo->ctx->semdie, philo->ctx);
	philo->t_now = gettime(philo->ctx) - philo->ctx->t_start;
	printf("%011ld %d %s\n", philo->t_now, philo->id, str);
	// smpost(philo->ctx->semwri, philo->ctx);
}

void	writedeath(t_philo *philo)
{
	// smwait(philo->ctx->semwri, philo->ctx);
	// smwait(philo->ctx->semdie, philo->ctx);
	// if (philo->ctx->f_end == true)
	// {
	// 	// smpost(philo->ctx->semdie, philo->ctx);
	// 	// smpost(philo->ctx->semwri, philo->ctx);
	// 	return ;
	// }
	// philo->ctx->f_end = true;
	// smpost(philo->ctx->semdie, philo->ctx);
	philo->t_now = gettime(philo->ctx) - philo->ctx->t_start;
	printf("%011ld %d %s\n", philo->t_now, philo->id, "is dead");
	// smpost(philo->ctx->semwri, philo->ctx);
}
