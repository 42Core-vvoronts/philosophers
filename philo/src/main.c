/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:33:37 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/03 18:08:46 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Main function
 * 
 * @param argc Number of arguments
 * @param argv Arguments
 * 
 * ./philo 5 800 200 200 7
 * 
 * @return int
 */
int main(int argc, char **argv)
{
	t_ctx	*dining;

	init(&dining, argc, argv);
	// simulate(dining);
	destroy(dining);
	return (0);
}
