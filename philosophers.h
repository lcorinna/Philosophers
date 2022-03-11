/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:49:55 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/11 18:48:46 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_flow
{
	int				id;
	int				life;
	int				eat;
	int				sleep;
	int				death;
	int				itr;
	long long		*time;
	long long		*zero_t;
	long long		last_eat;
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
	long long		zero_time;
	long long		timestamp;
	t_flow			*philo;
	pthread_t		*th;
	pthread_mutex_t	mutex;
}	t_data;

int			ft_filling_data(t_data *data, char **argv);
int			ft_dining_room(t_data *data, int i);
void		ft_heart_monitor(t_data *data, int i);
void		ft_time_zero(t_data *data);

void		ft_my_uslep(long long time);
void		ft_destroy_mutex(t_data *data, int i);
int			ft_error_free(t_data *data, int flag, int i);
void		ft_filling_struct_ph(t_data *data, int i);
int			ft_memory_and_tool_allocation(t_data *data, int i);

void		ft_time_passed(t_flow *ph);
void		ft_think(t_flow *ph);
void		ft_sleep(t_flow *ph);
void		ft_eat(t_flow *ph);
void		*ft_routine(void *argv);

void		ft_putstr_fd(char *s, int fd);
long long	ft_number(char *done);
int			ft_atoi_ph(char *s);

#endif