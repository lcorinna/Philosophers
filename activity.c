/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:28:02 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/09 19:38:14 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_time_passed(t_flow *ph)
{
	struct timeval	watch;

	gettimeofday(&watch, NULL);
	if (ph->timestamp == -1)
		ph->timestamp = watch.tv_sec * 1000 + watch.tv_usec / 1000;
	else
		ph->plus_time = watch.tv_sec * 1000 + watch.tv_usec / 1000 - \
		ph->timestamp;
}

void	ft_think(t_flow *ph)
{	
	ft_time_passed(ph);
	pthread_mutex_lock(ph->mes);
	printf("%lld %d is thinking ===================\n", ph->plus_time, ph->id);
	pthread_mutex_unlock(ph->mes);
}

void	ft_sleep(t_flow *ph)
{	
	ft_time_passed(ph);
	pthread_mutex_lock(ph->mes);
	printf("%lld %d is sleeping ----------------\n", ph->plus_time, ph->id);
	pthread_mutex_unlock(ph->mes);
	// ft_my_uslep(ph->sleep);
	usleep(ph->sleep * 1000);
}

void	ft_eat(t_flow *ph)
{
	ft_time_passed(ph);
	// ph->hungry = ph->plus_time - ph->last_eat;
	// ph->last_eat = ph->plus_time;
	// printf("____________last_eat %d\n", ph->hungry); //del
	pthread_mutex_lock(ph->right);
	pthread_mutex_lock(ph->mes);
	printf("%lld %d has taken a fork\n", ph->plus_time, ph->id);
	pthread_mutex_unlock(ph->mes);
	pthread_mutex_lock(ph->left);
	pthread_mutex_lock(ph->mes);
	printf("%lld %d has taken a fork\n", ph->plus_time, ph->id);
	pthread_mutex_unlock(ph->mes);
	pthread_mutex_lock(ph->mes);
	printf("%lld %d is eating ++++++++++++++++\n", ph->plus_time, ph->id);
	pthread_mutex_unlock(ph->mes);
	usleep(ph->eat * 1000);
	// ft_my_uslep(ph->eat);
	pthread_mutex_unlock(ph->right);
	pthread_mutex_unlock(ph->left);
}

void	*ft_routine(void *philo)
{
	t_flow			*ph;

	ph = (t_flow *) philo;
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
