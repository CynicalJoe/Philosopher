/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtournay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:02:34 by gtournay          #+#    #+#             */
/*   Updated: 2021/10/19 16:02:36 by gtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_stamp(struct timeval *start)
{
	struct timeval		now;
	int					startms;
	int					nowms;
	int					ret;

	gettimeofday(&now, NULL);
	startms = (start->tv_usec / 1000) + (start->tv_sec * 1000);
	nowms = (now.tv_usec / 1000) + (now.tv_sec * 1000);
	ret = nowms - startms;
	return (ret);
}

int	check_if_done(t_rules *sim)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < sim->val->nbr)
	{
		if (sim->philo[i]->eaten == sim->val->eaten)
			ret++;
		i++;
	}
	return (ret);
}

void	create_thd(t_rules *sim)
{
	int	i;

	i = 0;
	while (i < sim->val->nbr)
	{
		pthread_create(&sim->philo[i]->tid, NULL, philo_routine, sim->philo[i]);
		pthread_detach(sim->philo[i]->tid);
		usleep(100);
		i++;
	}
}

int	philo(t_rules *sim)
{
	int	i;

	sim->val->ded = 0;
	sim->val->done = 0;
	gettimeofday(sim->val->start, NULL);
	create_thd(sim);
	while (!sim->val->ded)
	{
		i = 0;
		sim->val->done = check_if_done(sim);
		if (sim->val->done == sim->val->nbr)
			break ;
		while (i < sim->val->nbr)
		{
			my_usleep(1);
			if (!sim->val->ded)
				sim->val->ded = check_ded(sim->philo[i]);
			i++;
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_rules	*sim;

	if (argc < 5 || argc > 6)
	{
		write(0, "Usage Error\n", 13);
		return (1);
	}
	if (!check_arg(argv))
		return (1);
	sim = create_sim();
	if (!sim)
		return (1);
	if (!init_rules(argc, argv, sim))
		return (1);
	philo(sim);
	big_free(sim);
	return (0);
}
