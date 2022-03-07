/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:04:29 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/07 18:52:08 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_my_uslep(t_data *data)
{
	struct timeval	times;
	int				t_current;
	int				t_exit;

	t_exit = data->t_life * 1000;
	gettimeofday(&times, NULL);
	if (times.tv_usec < 100000)
		times.tv_usec *= 10;
	t_current = times.tv_usec;
	t_exit += times.tv_usec;
	if (t_exit > 1000000)
		t_current = 1000000 + times.tv_usec;
	while (1)
	{
		gettimeofday(&times, NULL);
		t_current = times.tv_usec;
		if (t_exit > 1000000)
			t_current = 1000000 + times.tv_usec;
		if (t_current == t_exit)
			return ;
	}
}

void	ft_destroy_mutex(t_data *data, int i)
{
	if (i == -3)
		pthread_mutex_destroy(&data->mutex);
	if (i < -1)
	{
		i = -1;
		while (i++ < data->n_ph)
			pthread_mutex_destroy(&data->philo[i]);
	}
	else
	{
		i++;
		while (i-- != -1)
			pthread_mutex_destroy(&data->philo[i]);
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
		ft_putstr_fd("Don't work pthread_join\n", 2);
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
	while (i++ < data->n_ph)
	{
		data->philo[i].id = i;
		data->philo[i].life = data->t_life;
		data->philo[i].eat = data->t_eat;
		data->philo[i].think = data->t_think;
	}
}

int	ft_memory_and_tool_allocation(t_data *data, int i)
{
	data->philo = malloc (sizeof(t_flow) * data->n_ph);
	if (data->philo)
		return (ft_error_free(data, 3, -1));
	data->th = malloc(sizeof(pthread_t) * data->n_ph);
	if (data->philo)
		return (ft_error_free(data, 3, -1));
	i = -1;
	ft_filling_struct_ph(data, i);
	while (i++ < data->n_ph)
	{
		if (pthread_mutex_init(&data->philo[i].fork, NULL))
			return (ft_error_free(data, 4, i));
	}
	i = -1;
	while (i++ < data->n_ph)
	{
		data->philo[i].left = &data->philo[i].fork;
		if ((i + 1) > (data->n_ph - 1))
			data->philo[i].right = &data->philo[0].fork;
		else
			data->philo[i].right = &data->philo[i + 1].fork;
	}
	if (pthread_mutex_init(&data->mutex, NULL))
		return (ft_error_free(data, 4, -2));
	return (0);
}
