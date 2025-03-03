/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:23 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/03 18:08:24 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_ctx *dining)
{
	int			i;
	t_thread	*philo;

	i = 0;
	if (!dining)
		return ;
	while (i < dining->number)
	{
		philo = &dining->philos[i];
		pthread_mutex_destroy(&philo->lfork);
		pthread_mutex_destroy(&philo->rfork);
		i++;
	}
	free(dining->philos);
	free(dining);
	dining = NULL;
}