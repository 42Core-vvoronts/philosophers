/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:41:17 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/05 11:57:37 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	errexit(int err, const char *msg, t_ctx **ctx)
{
	int	std;

	if (err != SUCCESS)
		std = 2;
	else
		std = 0;
	writestd(msg, std);
	destroy(ctx);
	exit(err);
}

void	writestd(const char *msg, int std)
{
	if (std == 2)
		write(2, "Error: ", 7);
	if (msg)
		write(std, msg, ft_strlen(msg));
	if (std == 2)
		write(2, "\n", 1);
}
