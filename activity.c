/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:28:02 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/08 19:31:26 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_think(t_flow *ph)
{	
	pthread_mutex_lock(ph->mes);
	printf("%lld %d ", ph->timestamp, ph->id);
	write(1, "is thinking\n", 12);
	pthread_mutex_unlock(ph->mes);
}

void	ft_sleep(t_flow *ph)
{	
	pthread_mutex_lock(ph->mes);
	printf("%lld %d ", ph->timestamp, ph->id);
	write(1, "is sleeping\n", 12);
	pthread_mutex_unlock(ph->mes);
	ft_my_uslep(ph->sleep);
}

void	ft_eat(t_flow *ph)
{
	pthread_mutex_lock(ph->right);
	pthread_mutex_lock(ph->mes);
	printf("%lld %d ", ph->timestamp, ph->id);
	write(1, "has taken a fork\n", 17);
	pthread_mutex_unlock(ph->mes);
	pthread_mutex_lock(ph->left);
	pthread_mutex_lock(ph->mes);
	printf("%lld %d ", ph->timestamp, ph->id);
	write(1, "has taken a fork\n", 17);
	pthread_mutex_unlock(ph->mes);
	pthread_mutex_lock(ph->mes);
	printf("%lld %d ", ph->timestamp, ph->id);
	write(1, "is eating\n", 14);
	pthread_mutex_unlock(ph->mes);
	ft_my_uslep(ph->eat);
	pthread_mutex_unlock(ph->right);
	pthread_mutex_unlock(ph->left);
}

void	*ft_routine(void *philo)
{
	struct timeval	watch;
	t_flow			*ph;

	ph = (t_flow *) philo;
	gettimeofday(&watch, NULL);
	if (ph->timestamp == -1)
	{
		ph->plus_time = watch.tv_sec * 1000 + watch.tv_usec / 1000;
		printf("ph->plus_time %lld\n", ph->plus_time); //del
		printf("%lld %d \n", ph->timestamp, ph->id);
		ph->timestamp = 0;
	}
	else
		ph->timestamp = 1;
	while (*ph->itr)
	{
		ft_eat(ph);
		ft_sleep(ph);
		ft_think(ph);
		if ((*ph->itr) > 0)
			(*ph->itr)--;
	}
	return (NULL);
}
