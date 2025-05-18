/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:41:17 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/18 10:57:44 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(int status, const char *msg, t_ctx *ctx)
{
	int	std;

	if (status == FAIL)
	{
		std = 2;
		if (ctx && ctx->f_error == false)
			ctx->f_error = true;
	}
	else
		std = 1;
	writestd(msg, std);
	return (status); 
}

void	writestd(const char *msg, int std)
{
	if (std == 2)
		write(std, "Error: ", 7);
	write(std, msg, strlen(msg));
	write(std, "\n", 1);
}
