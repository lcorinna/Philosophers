/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:28:02 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/11 19:29:16 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_time_passed(t_flow *ph)
{
	struct timeval	watch;

	gettimeofday(&watch, NULL);
	*ph->time = watch.tv_sec * 1000 + watch.tv_usec / 1000 - *ph->zero_t;
}

void	ft_think(t_flow *ph)
{	
	pthread_mutex_lock(ph->mes);
	printf("%lld %d is thinking\n", *ph->time, ph->id);
	pthread_mutex_unlock(ph->mes);
}

void	ft_sleep(t_flow *ph)
{	
	pthread_mutex_lock(ph->mes);
	printf("%lld %d is sleeping\n", *ph->time, ph->id);
	pthread_mutex_unlock(ph->mes);
	ft_my_uslep((long long)ph->sleep);
	// usleep(ph->sleep * 1000);
}

void	ft_eat(t_flow *ph)
{
	pthread_mutex_lock(ph->left);
	ph->death = *ph->time - ph->last_eat;
	ph->last_eat = *ph->time;
	// printf("ph->death ____%d\n\n", ph->death); //del
	pthread_mutex_lock(ph->mes);
	printf("%lld %d has taken a fork\n", *ph->time, ph->id);
	pthread_mutex_unlock(ph->mes);
	pthread_mutex_lock(ph->right);
	pthread_mutex_lock(ph->mes);
	printf("%lld %d has taken a fork\n", *ph->time, ph->id);
	pthread_mutex_unlock(ph->mes);
	pthread_mutex_lock(ph->mes);
	printf("%lld %d is eating\n", *ph->time, ph->id);
	pthread_mutex_unlock(ph->mes);
	// usleep(ph->eat * 1000);
	ft_my_uslep((long long)ph->eat);
	pthread_mutex_unlock(ph->right);
	pthread_mutex_unlock(ph->left);
}

void	*ft_routine(void *philo)
{
	t_flow			*ph;

	ph = (t_flow *) philo;
	while (ph->itr)
	{
		ft_eat(ph);
		ft_sleep(ph);
		ft_think(ph);
		if (ph->itr > 0)
			ph->itr--;
	}
	return (NULL);
}
