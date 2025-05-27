/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:33:37 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/27 19:23:16 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Main function, program entry point
 * 
 * @param argc Number of arguments
 * @param argv Arguments
 * 
 * @return int
 */
int	main(int argc, char **argv)
{
	t_ctx	*ctx;

	if (validate(argv, argc) == FAIL)
		return (FAIL);
	ctx = init(argv);
	if (ctx == NULL)
		return (FAIL);
	simulate(ctx);
	destroy(NULL, ctx);
	return (SUCCESS);
}
