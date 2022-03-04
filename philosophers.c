/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:04:29 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/04 18:41:36 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_filling_data(t_data *data, char **argv)
{
	data->philo = ft_atoi_ph(argv[1]);
	if (data->philo > 200)
		return (1);
	data->t_life = ft_atoi_ph(argv[2]);
	if (data->t_life == 2147483647)
		return (1);
	data->t_eat = ft_atoi_ph(argv[3]);
	if (data->t_eat == 2147483647)
		return (1);
	data->t_think = ft_atoi_ph(argv[4]);
	if (data->t_think == 2147483647)
		return (1);
	data->iter = -1;
	if (argv[5] != NULL)
	{
		data->iter = ft_atoi_ph(argv[5]);
		if (data->iter == 2147483647)
			return (1);
	}
	return (0);
}

int	ft_error(char *str, int flag)
{
	if (flag == 1)
		ft_putstr_fd(str, 2);
	if (flag == 2)
		ft_putstr_fd(str, 2);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_error("The number of arguments should be 4 or 5\n", 1));
	if (ft_filling_data(&data, argv))
		return (ft_error("Invalid value of arguments\n", 2));
	printf("data->philo %d\n", data.philo); //del
	printf("data->t_life %d\n", data.t_life); //del
	printf("data->t_eat %d\n", data.t_eat); //del
	printf("data->t_think %d\n", data.t_think); //del
	printf("data->iter %d\n", data.iter); //del
	return (0);
}
