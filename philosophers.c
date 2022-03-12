/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:04:29 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/12 19:39:50 by lcorinna         ###   ########.fr       */
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
	data->t_sleep = ft_atoi_ph(argv[4]);
	if (data->t_sleep == 2147483647)
		return (1);
	data->iter = -1;
	if (argv[5] != NULL)
		data->iter = ft_atoi_ph(argv[5]);
	if (data->iter == 2147483647)
		return (1);
	data->zero_time = -1;
	return (0);
}

int	ft_heart_monitor(t_data *data, int i)
{
	int	j;

	if (data->n_ph == 1)
		return (ft_exception(data));
	while (1)
	{
		i = -1;
		j = 0;
		while (++i < data->n_ph)
		{
			ft_time_passed(&data->philo[i]);
			if (data->philo[i].death > data->t_life)
			{
				pthread_mutex_lock(&data->mutex);
				printf("%lld %d died\n", data->timestamp, i + 1);
				return (0);
			}
			if (data->philo[i].itr == 0)
				j++;
		}
		if (j == data->n_ph)
			return (0);
	}
	return (0);
}

void	ft_time_zero(t_data *data)
{
	struct timeval	watch;

	gettimeofday(&watch, NULL);
	data->zero_time = watch.tv_sec * 1000 + watch.tv_usec / 1000;
}

int	ft_dining_room(t_data *data, int i)
{
	if (ft_memory_and_tool_allocation(data, i))
		return (1);
	ft_time_zero(data);
	while (i < data->n_ph)
	{
		if (pthread_create(&data->th[i], NULL, ft_routine, &data->philo[i]))
			return (ft_error_free(data, 5, -3));
		i += 2;
	}
	usleep(300);
	i = 1;
	while (i < data->n_ph)
	{
		if (pthread_create(&data->th[i], NULL, ft_routine, &data->philo[i]))
			return (ft_error_free(data, 5, -3));
		i += 2;
	}
	i = -1;
	while (++i < data->n_ph)
	{
		if (pthread_detach(data->th[i]))
			return (ft_error_free(data, 6, -3));
	}
	ft_heart_monitor(data, i);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.philo = NULL;
	data.th = NULL;
	if (argc < 5 || argc > 6)
		return (ft_error_free(&data, 1, -1));
	if (ft_filling_data(&data, argv))
		return (ft_error_free(&data, 2, -1));
	argc = 0;
	if (ft_dining_room(&data, argc))
		return (1);
	ft_error_free(&data, 0, -3);
	exit(0);
	return (0);
}
