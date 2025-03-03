/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:41:17 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/03 19:18:32 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	errexit(int err, const char *msg, t_ctx *dining)
{
	int	std;

	if (err != SUCCESS)
		std = 2;
	else
		std = 0;
	writestd(msg, std);
	destroy(dining);
	exit(err);
}
