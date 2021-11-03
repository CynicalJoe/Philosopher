/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtournay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:01:37 by gtournay          #+#    #+#             */
/*   Updated: 2021/10/19 16:01:44 by gtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_val
{
	int				nbr;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				eaten;
	int				ded;
	int				done;
	pthread_mutex_t	write;
	struct timeval	*start;
}	t_val;

typedef struct s_philo
{
	int					id;
	int					eaten;
	int					last_eaten;
	t_fork				*right;
	t_fork				*left;
	t_val				*val;
	pthread_t			tid;
}	t_philo;

typedef struct s_rules
{
	t_fork			**forks;
	t_philo			**philo;
	t_val			*val;
}	t_rules;

int					ft_atoi(const char *nptr);

int					check_arg(char **argv);

int					check_ded(t_philo *philo);

void				print_st(t_philo *philo, char *str, int mode);

void				*philo_routine(void *philo);

void				my_usleep(int ms);

int					get_stamp(struct timeval *start);

t_rules				*create_sim(void);

t_rules				*init_rules(int argc, char **argv, t_rules *sim);

t_rules				*big_free(t_rules *sim);

#endif
