/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:41:17 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/27 19:23:38 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(int status, const char *msg, t_ctx *ctx)
{
	int	std;

	std = 1;
	if (status == FAIL)
		std = 2;
	writestd(msg, std);
	destroy(NULL, ctx);
	exit(status);
}

void	writestd(const char *msg, int std)
{
	if (std == 2)
		write(std, "Error: ", 7);
	write(std, msg, strlen(msg));
	write(std, "\n", 1);
}
