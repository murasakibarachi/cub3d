/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 13:37:19 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/16 13:29:58 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spriteposition(t_cub3d *cub, int x)
{
	cub->sprite[cub->sprite_n].x = x + 0.5;
	cub->sprite[cub->sprite_n].y = cub->parse.y + 0.5;
	cub->sprite_n++;
	cub->parse.y++;
}

void	spritesort(t_cub3d *cub)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < cub->sprite_num - 1)
	{
		j = 0;
		while (j < cub->sprite_num - i - 1)
		{
			if (cub->sprite[j].dist < cub->sprite[j + 1].dist)
			{
				tmp = cub->sprite[j];
				cub->sprite[j] = cub->sprite[j + 1];
				cub->sprite[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	spritedistance(t_cub3d *cub)
{
	int		num;

	cub->sprite_n = 0;
	while (cub->sprite_n < cub->sprite_num)
	{
		num = cub->sprite_n;
		cub->sprite[cub->sprite_n].order = cub->sprite_n;
		cub->sprite[num].dist = pow(cub->posx - cub->sprite[num].x, 2) +
			pow(cub->posy - cub->sprite[cub->sprite_n].y, 2);
		cub->sprite_n++;
	}
	spritesort(cub);
	cub->sprite_n = 0;
}

void	sprite(t_cub3d *cub)
{
	spritedistance(cub);
	cub->bmp_pos = 0;
	while (cub->sprite_n < cub->sprite_num)
	{
		cub->spritex = cub->sprite[cub->sprite_n].x - cub->posx;
		cub->spritey = cub->sprite[cub->sprite_n].y - cub->posy;
		cub->invdet = 1.0 / (cub->planex * cub->diry - cub->dirx * cub->planey);
		cub->transformx = cub->invdet * (cub->diry * cub->spritex -
			cub->dirx * cub->spritey);
		cub->transformy = cub->invdet * (-cub->planey * cub->spritex +
			cub->planex * cub->spritey);
		cub->spritescreenx = (int)((cub->res.w / 2) * (1 + cub->transformx /
			cub->transformy));
		cub->spriteheight = abs((int)(cub->res.h / cub->transformy));
		cub->drawstarty = -cub->spriteheight / 2 + cub->res.h / 2;
		cub->drawstarty = (cub->drawstarty < 0) ? 0 : cub->drawstarty;
		cub->drawendy = cub->spriteheight / 2 + cub->res.h / 2;
		if (cub->drawendy >= cub->res.h)
			cub->drawendy = cub->res.h - 1;
		cub->spritewidth = abs((int)(cub->res.h / (cub->transformy)));
		spriterendering(cub);
		cub->sprite_n++;
	}
}

void	spriterendering(t_cub3d *cub)
{
	cub->drawstartx = -cub->spritewidth / 2 + cub->spritescreenx;
	if (cub->drawstartx < 0)
		cub->drawstartx = 0;
	cub->drawendx = cub->spritewidth / 2 + cub->spritescreenx;
	if (cub->drawendx >= cub->res.w)
		cub->drawendx = cub->res.w - 1;
	while (cub->drawstartx < cub->drawendx)
	{
		cub->bmp_pos = 0;
		cub->tex_x = (int)(256 * (cub->drawstartx - (-cub->spritewidth / 2 +
			cub->spritescreenx)) * cub->texwidth / cub->spritewidth) / 256;
		if (cub->transformy > 0 && cub->drawstartx > 0 &&
				cub->drawstartx < cub->res.w &&
				cub->transformy < cub->sprite_buf[cub->drawstartx])
		{
			cub->spriteline = cub->drawstarty;
			while (cub->spriteline < cub->drawendy)
			{
				sprite_image(cub);
				cub->spriteline++;
			}
		}
		cub->drawstartx++;
	}
}
