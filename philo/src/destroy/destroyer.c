/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:23 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/07 18:54:54 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_ctx **ctx)
{
	int	i;

	i = 0;
	if (!ctx || !*ctx)
		return ;
	while (i < (*ctx)->n_ph)
	{
		mxdestroy(&(*ctx)->forks[i], *ctx);
		i++;
	}
	mxdestroy(&(*ctx)->meallock, *ctx);
	mxdestroy(&(*ctx)->deadlock, *ctx);
	mxdestroy(&(*ctx)->writelock, *ctx);
	free((*ctx)->philos);
	free(*ctx);
}