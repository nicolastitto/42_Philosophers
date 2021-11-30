/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nide-mel <nide-mel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:54:08 by nide-mel          #+#    #+#             */
/*   Updated: 2021/11/30 22:37:58 by nide-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data, int id)
{
	data->philo[id].id = id + 1;
	data->philo[id].start_eat = 0;
	data->philo[id].start_sleep = get_time;
	data->philo[id].status = sleep;
	if (data->philo[id].id == data->s_arg.nb_philo)
		data->philo[id].r_fork = data->forks[0];
	else
		data->philo[id].r_fork = data->forks[id + 1];
	data->philo[id].l_fork = data->forks[id];
}

void	init_args(t_arg *s_philo, char **av, int ac)
{
	s_philo->nb_philo = ft_atoi(av[2]);
	s_philo->t_die = ft_atoi(av[3]);
	s_philo->t_eat = ft_atoi(av[4]);
	s_philo->t_sleep = ft_atoi(av[5]);
	if (ac == 6)
		s_philo->times_eat = ft_atoi(av[6]);
	else
		s_philo->times_eat = -1;
	s_philo->kill = 0;
}

t_bool	init_data(t_data *data)
{	int		i;

	i = -1;
	gettimeofday(&data->start, NULL);
	data->philo = calloc(data->s_arg.nb_philo, sizeof(t_philo));
	data->forks = calloc(data->s_arg.nb_philo, sizeof(t_philo));
	if (!data->forks || !data->philo)
		return (falso);
	while (++i < data->s_arg.nb_philo)
	{
		data->forks[i] = verdade;
		init_philo(&data->philo[i], i);
	}
	return (verdade);
}

t_data	*init_struct(int ac, char **av)
{
	t_data	*data;

	init_args(&data->s_arg, av, ac);
	if (data->s_arg.nb_philo == 1)
	{
		usleep(data->s_arg.t_die * 1000);
		printf(RED "%ld %d died" RST, get_time(&data->start), 1);
		return (NULL);
	}
	if (!init_data(data))
		return (NULL);
	get_data(data);
	return (data);
}