/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:28:02 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/12 19:34:09 by lcorinna         ###   ########.fr       */
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
	usleep((ph->sleep - 5) * 1000);
}

void	ft_eat(t_flow *ph)
{
	pthread_mutex_lock(ph->left);
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
	usleep((ph->eat - 3) * 1000);
	ph->death = *ph->time - ph->last_eat;
	printf("num %d ph->death %d\n", ph->id, ph->death); //del
	ph->last_eat = *ph->time;
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
