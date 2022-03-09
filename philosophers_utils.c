/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:04:29 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/09 18:37:47 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_my_uslep(int time)
{
	struct timeval	watch;
	int				t_current;
	int				t_exit;

	t_exit = time * 1000;
	gettimeofday(&watch, NULL);
	// printf("%d\n", watch.tv_usec);
	// if (watch.tv_usec < 100000)
	// 	watch.tv_usec *= 10;
	t_current = watch.tv_usec;
	t_exit += watch.tv_usec;
	if (t_exit > 1000000)
		t_current = 1000000 + watch.tv_usec;
	while (1)
	{
		gettimeofday(&watch, NULL);
		t_current = watch.tv_usec;
		if (t_exit > 1000000)
			t_current = 1000000 + watch.tv_usec;
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
			pthread_mutex_destroy(data->philo[i].right);
	}
	else
	{
		i++;
		while (i-- != -1)
			pthread_mutex_destroy(data->philo[i].right);
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
	i = -1;
	while (++i < data->n_ph)
	{
		data->philo[i].id = i + 1;
		data->philo[i].life = data->t_life;
		data->philo[i].eat = data->t_eat;
		data->philo[i].sleep = data->t_sleep;
		data->philo[i].itr = &data->iter;
		data->philo[i].mes = &data->mutex;
		data->philo[i].timestamp = -1;
		data->philo[i].plus_time = 0;
		data->philo[i].last_eat = 0;
	}
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
	while (i++ < data->n_ph)
	{
		if (pthread_mutex_init(&data->philo[i].fork, NULL))
			return (ft_error_free(data, 4, i));
	}
	i = -1;
	while (++i < data->n_ph)
	{
		data->philo[i].left = &data->philo[i].fork;
		if ((i + 1) > (data->n_ph - 1))
			data->philo[i].right = &data->philo[0].fork;
		else
			data->philo[i].right = &data->philo[i + 1].fork;
	}
	if (pthread_mutex_init(&data->mutex, NULL))
		return (ft_error_free(data, 4, -2));
	ft_filling_struct_ph(data, i);
	return (0);
}
