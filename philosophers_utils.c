/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:04:29 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/12 19:29:30 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_destroy_mutex(t_data *data, int i)
{
	if (i == -3)
		pthread_mutex_destroy(&data->mutex);
	if (i < -1)
	{
		i = -1;
		while (++i < data->n_ph)
			pthread_mutex_destroy(&data->philo[i].fork);
	}
	else
	{
		while (--i != -1)
			pthread_mutex_destroy(&data->philo[i].fork);
	}
}

int	ft_error_free(t_data *data, int flag, int i)
{
	if (flag == 1)
		ft_putstr_fd("The number of arguments should be 4 or 5\n", 2);
	else if (flag == 2)
		ft_putstr_fd("Invalid value of arguments\n", 2);
	else if (flag == 3)
		ft_putstr_fd("Memory allocation problem\n", 2);
	else if (flag == 4)
		ft_putstr_fd("Don't work pthread_mutex_init\n", 2);
	else if (flag == 5)
		ft_putstr_fd("Don't work pthread_create\n", 2);
	else if (flag == 6)
		ft_putstr_fd("Don't work pthread_detach\n", 2);
	if (data->philo != NULL)
		free(data->philo);
	if (data->th != NULL)
		free(data->th);
	if (i != -1)
		ft_destroy_mutex(data, i);
	return (1);
}

void	ft_filling_struct_ph(t_data *data, int i)
{
	i = -1;
	while (++i < data->n_ph)
	{
		data->philo[i].id = i + 1;
		data->philo[i].life = data->t_life;
		data->philo[i].eat = data->t_eat;
		data->philo[i].sleep = data->t_sleep;
		data->philo[i].itr = data->iter;
		data->philo[i].mes = &data->mutex;
		data->philo[i].zero_t = &data->zero_time;
		data->philo[i].time = &data->timestamp;
		data->philo[i].last_eat = 0;
	}
}

int	ft_exception(t_data *data)
{
	usleep(data->t_eat * 1000 + data->t_sleep * 1000);
	printf("%d %d died\n", data->t_life + 3, 1);
	return (1);
}

int	ft_memory_and_tool_allocation(t_data *data, int i)
{
	data->philo = (t_flow *) malloc (sizeof(t_flow) * data->n_ph);
	if (data->philo == NULL)
		return (ft_error_free(data, 3, -1));
	data->th = malloc(sizeof(pthread_t) * data->n_ph);
	if (data->th == NULL)
		return (ft_error_free(data, 3, -1));
	i = -1;
	while (++i < data->n_ph)
	{
		if (pthread_mutex_init(&data->philo[i].fork, NULL))
			return (ft_error_free(data, 4, i));
	}
	i = -1;
	while (++i < data->n_ph)
	{		
		data->philo[i].left = &data->philo[i].fork;
		if ((i + 1) != data->n_ph)
			data->philo[i].right = &data->philo[i + 1].fork;
		else
			data->philo[i].right = &data->philo[0].fork;
	}
	if (pthread_mutex_init(&data->mutex, NULL))
		return (ft_error_free(data, 4, -2));
	ft_filling_struct_ph(data, i);
	return (0);
}
