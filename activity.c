/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:28:02 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/07 18:59:04 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_routine(void *data)
{
	t_flow	*philo;

	philo = (t_flow *) data;
	ft_eat(philo)
	pthread_mutex_lock(&philo->right);
	pthread_mutex_lock(&philo->left);
	
}
