/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:08:52 by ybouddou          #+#    #+#             */
/*   Updated: 2020/12/04 09:17:18 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exist(t_cub3d *cub)
{
	if (cub->rep.res == 0)
		error_msg_free("ERROR\nResolution not found", cub);
	else if (cub->rep.no == 0 || cub->rep.so == 0 || cub->rep.ea == 0 ||
		cub->rep.we == 0 || cub->rep.s == 0)
		error_msg_free("ERROR\nPath not found", cub);
	else if (cub->rep.f == 0)
		error_msg_free("ERROR\nF not found", cub);
	else if (cub->rep.c == 0)
		error_msg_free("ERROR\nC not found", cub);
	if (cub->parse.x == 0)
	{
		cub->map = (char**)malloc(2 * sizeof(char*));
		cub->map[0] = ft_strdup(cub->parse.line);
		cub->map[1] = NULL;
	}
	else
		push(cub);
}

void	error_msg_free(char *s, t_cub3d *cub)
{
	free(cub->parse.line);
	free(cub->path.no);
	free(cub->path.so);
	free(cub->path.ea);
	free(cub->path.we);
	free(cub->path.s);
	free(cub->image);
	if (cub->parse.x > 0)
		ft_free(cub->map);
	ft_putstr_fd(s, 2);
	exit(1);
}

void	error_free(char *s, t_cub3d *cub, char **tofree)
{
	ft_free(tofree);
	free(cub->parse.line);
	free(cub->path.no);
	free(cub->path.so);
	free(cub->path.ea);
	free(cub->path.we);
	free(cub->path.s);
	free(cub->image);
	ft_putstr_fd(s, 2);
	exit(1);
}

void	error_msg(char *s)
{
	ft_putstr_fd(s, 2);
	exit(1);
}

void	ft_free(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
