/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtournay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:02:07 by gtournay          #+#    #+#             */
/*   Updated: 2021/10/19 16:02:12 by gtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_rules	*free_forks(t_rules *sim)
{
	int	i;

	i = 0;
	if (sim->forks)
	{
		while (sim->forks[i])
		{
			pthread_mutex_destroy(&sim->forks[i]->lock);
			free(sim->forks[i]);
			i++;
		}
		free(sim->forks);
	}
	return (NULL);
}

t_rules	*free_philo(t_rules *sim)
{
	int	i;

	i = 0;
	if (sim->philo)
	{
		while (sim->philo[i])
			free(sim->philo[i++]);
		free(sim->philo);
	}
	return (NULL);
}

t_rules	*big_free(t_rules *sim)
{
	free_forks(sim);
	free_philo(sim);
	if (sim->val)
	{	
		if (sim->val->start)
			free(sim->val->start);
		free(sim->val);
	}
	free(sim);
	return (NULL);
}
