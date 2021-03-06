/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 09:05:47 by ybouddou          #+#    #+#             */
/*   Updated: 2020/12/04 09:24:51 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void			bmp(t_cub3d *cub, int ac, char **av)
{
	if (ac == 3)
	{
		if (!ft_strncmp(av[2], "--save", ft_strlen("--save")))
			bmp_save(cub);
		else if (ft_strncmp(av[2], "--save", ft_strlen("--save")))
			error_msg_free("Error\nInvalid param", cub);
		free(cub->image);
		system("killall afplay");
		ft_putstr_fd("Screenshot saved!\n", 2);
		exit(0);
	}
}

void			bmp_filling(t_cub3d *cub)
{
	if (cub->ac == 3)
	{
		cub->image[(cub->abrv) * 3 + 2] = cub->color >> 16;
		cub->image[(cub->abrv) * 3 + 1] = cub->color >> 8;
		cub->image[(cub->abrv) * 3 + 0] = cub->color;
	}
}

unsigned char	*bmp_header(int filesize)
{
	unsigned char *bmpfileheader;

	bmpfileheader = (unsigned char *)malloc(14);
	ft_memset(bmpfileheader, 0, 14);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[10] = (unsigned char)(54);
	return (bmpfileheader);
}

unsigned char	*bmp_info(t_cub3d *cub)
{
	unsigned char *bmpinfoheader;

	bmpinfoheader = (unsigned char *)malloc(40);
	ft_memset(bmpinfoheader, 0, 40);
	bmpinfoheader[0] = (unsigned char)(40);
	bmpinfoheader[4] = (unsigned char)(cub->res.w);
	bmpinfoheader[5] = (unsigned char)(cub->res.w >> 8);
	bmpinfoheader[6] = (unsigned char)(cub->res.w >> 16);
	bmpinfoheader[7] = (unsigned char)(cub->res.w >> 24);
	bmpinfoheader[8] = (unsigned char)(cub->res.h);
	bmpinfoheader[9] = (unsigned char)(cub->res.h >> 8);
	bmpinfoheader[10] = (unsigned char)(cub->res.h >> 16);
	bmpinfoheader[11] = (unsigned char)(cub->res.h >> 24);
	bmpinfoheader[12] = (unsigned char)(1);
	bmpinfoheader[14] = (unsigned char)(24);
	return (bmpinfoheader);
}

void			bmp_save(t_cub3d *cub)
{
	unsigned char	*bmpfileheader;
	unsigned char	*bmpinfoheader;
	unsigned char	*bmppad;
	int				fd;
	int				abrv;

	cub->bmp.pad = (4 - (cub->res.w * 3) % 4) % 4;
	cub->bmp.filesize = 54 + cub->res.w * cub->res.h * 3;
	bmpfileheader = (unsigned char *)malloc(14);
	bmpinfoheader = (unsigned char *)malloc(40);
	bmppad = (unsigned char *)malloc(3);
	ft_memset(bmppad, 0, 3);
	bmpfileheader = bmp_header(cub->bmp.filesize);
	bmpinfoheader = bmp_info(cub);
	fd = open("Bonus/save_bonus.bmp", O_WRONLY | O_CREAT, 0666);
	write(fd, bmpfileheader, 14);
	write(fd, bmpinfoheader, 40);
	cub->bmp.i = -1;
	while (++cub->bmp.i < cub->res.h)
	{
		abrv = cub->bmp.i * cub->res.w * 3;
		write(fd, cub->image + abrv, cub->res.w * 3);
		write(fd, bmppad, cub->bmp.pad);
	}
	close(fd);
}
