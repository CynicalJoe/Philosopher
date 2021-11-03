/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtournay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:03:03 by gtournay          #+#    #+#             */
/*   Updated: 2021/10/19 16:03:05 by gtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_st(t_philo *philo, char *str, int mode)
{
	int	stamp;

	stamp = get_stamp(philo->val->start);
	pthread_mutex_lock(&philo->val->write);
	if (!philo->val->ded || mode)
		printf("%d %d %s", stamp, philo->id, str);
	pthread_mutex_unlock(&philo->val->write);
}

void	my_usleep(int ms)
{
	struct timeval	sleep;

	gettimeofday(&sleep, NULL);
	while (get_stamp(&sleep) < ms)
		usleep(100);
}
