/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:48:24 by lcorinna          #+#    #+#             */
/*   Updated: 2022/03/04 19:06:19 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
}

long long	ft_number(char *done)
{
	long long	res;
	int			i;

	i = 0;
	res = 0;
	while (done[i] > 47 && done[i] < 58)
	{
		res = res * 10 + (done[i] - 48);
		i++;
	}
	return (res);
}

int	ft_atoi_ph(char *s)
{
	long long	res;
	int			i;
	int			j;

	res = 0;
	i = 0;
	j = 0;
	while ((s[i] == 32) || (s[i] > 8 && s[i] < 14))
		i++;
	j = i;
	while (s[j])
	{
		if (s[j] < '0' || s[j] > '9')
			return (2147483647);
		j++;
	}
	res = (ft_number(&s[i]));
	if (res > 2147483646 || res < -2147483648)
		return (2147483647);
	return (res);
}
