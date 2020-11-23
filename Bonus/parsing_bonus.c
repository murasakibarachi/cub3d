/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 20:01:50 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/23 17:43:32 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	resolution(t_cub3d *cub)
{
	if (cub->rep.res == 1)
		error_msg_free("ERROR\nRepetition of res", cub);
	cub->parse.line++;
	if (*cub->parse.line != ' ')
		error_msg_free("ERROR\nAnother char found after R", cub);
	cub->parse.splitted = ft_split(cub->parse.line, ' ');
	if (cub->parse.splitted[2] || !cub->parse.splitted[1])
		error_free("ERROR\nR must have only 2 param", cub, cub->parse.splitted);
	checker(cub->parse.splitted, cub);
	cub->res.w = ft_atoi(cub->parse.splitted[0]);
	cub->res.w = (cub->res.w > 2560) ? 2560 : cub->res.w;
	cub->res.w = cub->res.w < 640 ? 640 : cub->res.w;
	cub->res.h = ft_atoi(cub->parse.splitted[1]);
	cub->res.h = (cub->res.h > 1440) ? 1440 : cub->res.h;
	cub->res.h = cub->res.h < 360 ? 360 : cub->res.h;
	ft_free(cub->parse.splitted);
	cub->rep.res = 1;
}

void	path(char **path, t_cub3d *cub, int *fd, int *rep)
{
	if (*rep == 1)
		error_msg_free("Error\nAdditional path found\n", cub);
	if (cub->parse.line[0] == 'S' && cub->parse.line[1] != 'O'
		&& cub->parse.line[2] == ' ')
		error_msg_free("Error\nInvalid indentifier\n", cub);
	if (cub->parse.line[2] != ' ')
	{
		if ((cub->parse.line[0] == 'S' || cub->parse.line[0] == 'F'
			|| cub->parse.line[0] == 'C') && cub->parse.line[1] != 'O')
		{
			if (cub->parse.line[1] != ' ')
				error_msg_free("Error\nInvalid indentifier\n", cub);
		}
		else
			error_msg_free("Error\nInvalid indentifier\n", cub);
	}
	cub->parse.splitted = ft_split(cub->parse.line, ' ');
	if (cub->parse.splitted[2])
		error_free("Error\nInvalid indentifier\n", cub, cub->parse.splitted);
	*path = ft_strdup(cub->parse.splitted[1]);
	ft_free(cub->parse.splitted);
	*fd = open(*path, O_RDONLY);
	if (*fd == -1)
		error_msg_free("Error\nPath not found\n", cub);
	*rep = 1;
}

void	identifier(t_cub3d *cub)
{
	if (*cub->parse.line == 'S' && *(cub->parse.line + 1) != 'O')
		path(&cub->path.s, cub, &cub->fd.s, &cub->rep.s);
	else if (*cub->parse.line == 'N' && *(cub->parse.line + 1) == 'O')
		path(&cub->path.no, cub, &cub->fd.no, &cub->rep.no);
	else if (*cub->parse.line == 'S' && *(cub->parse.line + 1) == 'O')
		path(&cub->path.so, cub, &cub->fd.so, &cub->rep.so);
	else if (*cub->parse.line == 'W' && *(cub->parse.line + 1) == 'E')
		path(&cub->path.we, cub, &cub->fd.we, &cub->rep.we);
	else if (*cub->parse.line == 'E' && *(cub->parse.line + 1) == 'A')
		path(&cub->path.ea, cub, &cub->fd.ea, &cub->rep.ea);
	else if (*cub->parse.line == 'F' && *(cub->parse.line + 1) == ' ')
		path(&cub->path.f, cub, &cub->fd.f, &cub->rep.f);
	else if (*cub->parse.line == 'C' && *(cub->parse.line + 1) == ' ')
		path(&cub->path.c, cub, &cub->fd.c, &cub->rep.c);
}