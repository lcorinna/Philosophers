/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:49:55 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/04 19:17:02 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> //del

typedef struct s_flow
{
	int			id;
	pthread_t	fork;
}	t_flow;

typedef struct s_data
{
	int		philo;
	int		t_life;
	int		t_eat;
	int		t_think;
	int		iter;
	t_flow	*philo;
}	t_data;

int			ft_filling_data(t_data *data, char **argv);

int			ft_error(char *str, int flag);

void		ft_putstr_fd(char *s, int fd);
long long	ft_number(char *done);
int			ft_atoi_ph(char *s);

#endif