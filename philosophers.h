/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:49:55 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/09 19:36:11 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h> //del

typedef struct s_flow
{
	int				id;
	int				life;
	int				eat;
	int				sleep;
	int				hungry;
	long long		last_eat;
	long long		timestamp;
	long long		plus_time;
	int				*itr;
	pthread_mutex_t	fork;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	pthread_mutex_t	*mes;
}	t_flow;

typedef struct s_data
{
	int				n_ph;
	int				t_life;
	int				t_eat;
	int				t_sleep;
	int				iter;
	t_flow			*philo;
	pthread_t		*th;
	pthread_mutex_t	mutex;
}	t_data;

int			ft_filling_data(t_data *data, char **argv);
int			ft_dining_room(t_data *data, int i);

int			ft_error_free(t_data *data, int flag, int i);
int			ft_memory_and_tool_allocation(t_data *data, int i);
void		ft_my_uslep(int time);

void		*ft_routine(void *argv);

void		ft_putstr_fd(char *s, int fd);
long long	ft_number(char *done);
int			ft_atoi_ph(char *s);

#endif