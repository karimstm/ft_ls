/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:40:12 by mfilahi           #+#    #+#             */
/*   Updated: 2018/12/13 14:40:51 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int argc, char **argv)
{
	int		i;
	int		flag;
	char	**files;

	i = 1;
	flag = 0;
	files = NULL;
	if (argc > 1)
	{
		while (i <= argc - 1 && argv[i][0] == '-' && ft_strlen(argv[i]) > 1)
			parse_op_1(++argv[i++], &flag);
		if (i <= argc - 1)
		{
			if (!(argc - 1 - i >= 1))
				ft_ls(argv[i++], flag);
			else
				param_files(files, flag, argv, argc);
		}
		else
			ft_ls(".", flag);
	}
	else
		ft_ls(".", flag);
	exit(SUCCESS);
}
