/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:14:44 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/05 11:49:09 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	everyone_full(t_thread *philos, t_ctx *ctx)
{
	return (philos || ctx);
}

bool	someone_dead(t_thread *philos, t_ctx *ctx)
{
	return (philos || ctx);
}

void	*monitor(void *arg)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)arg;
	while (true)
	{
		if (someone_dead(ctx->philos, ctx) == true 
			|| everyone_full(ctx->philos, ctx) == true)
			break;
	}
	return (NULL);
}

