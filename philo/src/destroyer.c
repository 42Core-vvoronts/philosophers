/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:23 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/05 13:52:18 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_ctx **ctx)
{
	int			i;
	t_thread	*philo;

	i = 0;
	philo = (*ctx)->philos;
	while (i < (*ctx)->n_ph)
	{
		mxdestroy(&philo[i].leftlock, *ctx);
		mxdestroy(&philo[i].rightlock, *ctx);
		i++;
	}
	mxdestroy(&(*ctx)->meallock, *ctx);
	mxdestroy(&(*ctx)->deadlock, *ctx);
	mxdestroy(&(*ctx)->lock, *ctx);
	free((*ctx)->philos);
	free(*ctx);
}