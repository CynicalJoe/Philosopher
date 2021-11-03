/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtournay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:02:26 by gtournay          #+#    #+#             */
/*   Updated: 2021/10/19 16:02:29 by gtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_rules	*create_sim(void)
{
	t_rules	*sim;

	sim = malloc(sizeof(t_rules));
	if (!sim)
		return (NULL);
	sim->philo = NULL;
	sim->forks = NULL;
	return (sim);
}

t_rules	*init_forks(t_rules *sim)
{
	int	i;

	i = 0;
	sim->forks = malloc(sizeof(t_fork *) * (sim->val->nbr + 1));
	if (!sim->forks)
		return (big_free(sim));
	while (i < sim->val->nbr)
	{
		sim->forks[i] = malloc(sizeof(t_fork));
		if (!sim->forks[i])
			return (big_free(sim));
		pthread_mutex_init(&sim->forks[i]->lock, NULL);
		i++;
	}
	sim->forks[i] = NULL;
	return (sim);
}

t_rules	*init_philo(t_rules *sim)
{
	int	i;

	i = 0;
	sim->philo = malloc(sizeof(t_philo *) * (sim->val->nbr + 1));
	if (!sim->philo)
		return (big_free(sim));
	while (i < sim->val->nbr)
	{
		sim->philo[i] = malloc(sizeof(t_philo));
		if (!sim->philo[i])
			return (big_free(sim));
		sim->philo[i]->id = i + 1;
		sim->philo[i]->eaten = 0;
		sim->philo[i]->last_eaten = 0;
		if (i == 0)
			sim->philo[i]->left = sim->forks[sim->val->nbr - 1];
		else
			sim->philo[i]->left = sim->forks[i - 1];
		sim->philo[i]->right = sim->forks[i];
		sim->philo[i]->val = sim->val;
		i++;
	}
	sim->philo[i] = NULL;
	return (sim);
}

t_rules	*init_rules(int argc, char **argv, t_rules *sim)
{
	sim->val = malloc(sizeof(t_val));
	if (!sim->val)
		return (big_free(sim));
	sim->val->start = malloc(sizeof(struct timeval));
	if (!sim->val->start)
		return (big_free(sim));
	sim->val->nbr = ft_atoi(argv[1]);
	sim->val->to_die = ft_atoi(argv[2]);
	sim->val->to_eat = ft_atoi(argv[3]);
	sim->val->to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->val->eaten = ft_atoi(argv[5]);
	else
		sim->val->eaten = -1;
	pthread_mutex_init(&sim->val->write, NULL);
	if (!init_forks(sim))
		return (NULL);
	if (!init_philo(sim))
		return (NULL);
	return (sim);
}
