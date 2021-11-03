/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtournay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:02:54 by gtournay          #+#    #+#             */
/*   Updated: 2021/10/19 16:02:55 by gtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_ded(t_philo *philo)
{
	int	astamp;

	astamp = get_stamp(philo->val->start);
	if (astamp - philo->last_eaten < philo->val->to_die
		|| philo->eaten == philo->val->eaten)
		return (0);
	philo->val->ded = 1;
	print_st(philo, "has died\n", 1);
	return (1);
}

void	taking_f(t_philo *philo)
{
	pthread_mutex_lock(&philo->left->lock);
	print_st(philo, "has taken a fork\n", 0);
	pthread_mutex_lock(&philo->right->lock);
	print_st(philo, "has taken a fork\n", 0);
}

int	eating(t_philo *philo)
{
	int	stamp;

	taking_f(philo);
	if (!philo->val->ded)
	{	
		stamp = get_stamp(philo->val->start);
		philo->last_eaten = stamp;
		print_st(philo, "is eating\n", 0);
		my_usleep(philo->val->to_eat);
		philo->eaten++;
	}
	pthread_mutex_unlock(&philo->left->lock);
	pthread_mutex_unlock(&philo->right->lock);
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->eaten == philo->val->eaten)
		return (NULL);
	eating(philo);
	if (philo->eaten == philo->val->eaten)
		return (NULL);
	if (!philo->val->ded)
	{
		print_st(philo, "is sleeping\n", 0);
		my_usleep(philo->val->to_sleep);
	}
	if (!philo->val->ded)
		print_st(philo, "is thinking\n", 0);
	if (!philo->val->ded)
		philo_routine(philo);
	return (NULL);
}
