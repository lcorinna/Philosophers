/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:04:29 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/07 18:53:34 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_filling_data(t_data *data, char **argv)
{
	data->n_ph = ft_atoi_ph(argv[1]);
	if (data->n_ph > 200)
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
		data->iter = ft_atoi_ph(argv[5]);
	if (data->iter == 2147483647)
		return (1);
	return (0);
}

int	ft_dining_room(t_data *data, int i)
{
	if (ft_memory_and_tool_allocation(data, i))
		return (1);
	i = -1;
	while (i++ < data->n_ph)
	{
		if (pthread_create(&data->th[i], NULL, ft_routine, &data->philo[i]))
			return (ft_error_free(data, 5, -3));
		if (pthread_join(&data->th[i], NULL))
			return (ft_error_free(data, 6, -3));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_error_free(&data, 1, -1));
	if (ft_filling_data(&data, argv))
		return (ft_error_free(&data, 2, -1));
	if (ft_dining_room(&data, argc))
		return (1);
	ft_error_free(data, 0, -3); //is this the end of my program?
	// ft_my_uslep(&data);
	// printf("data->philo %d\n", data.n_ph); //del
	// printf("data->t_life %d\n", data.t_life); //del
	// printf("data->t_eat %d\n", data.t_eat); //del
	// printf("data->t_think %d\n", data.t_think); //del
	// printf("data->iter %d\n", data.iter); //del
	return (0);
}

// pthread_mutex_init(&data.mutex, NULL);
// pthread_mutex_lock(&data.mutex); 
// somebody
// pthread_mutex_unlock(&data.mutex);
// pthread_mutex_destroy(&data.mutex);