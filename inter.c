/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:24:38 by vminomiy          #+#    #+#             */
/*   Updated: 2020/03/12 16:53:21 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int		main(int argc, char **argv)
{
	int		i;
	int		j;
	int		s[256];

	if (argc == 3)
	{
		i = 2;
		*s = 0;
		while(i > 0)
		{
			j = 0;
			while (argv[i][j])
			{
				if (i == 2 && !s[(unsigned char)argv[i][j]])
					s[(unsigned char)argv[i][j]] = 1;
				else if (i == 1 && s[(unsigned char)argv[i][j]] == 1)
				{
					write(1, &argv[i][j], 1);
					s[(unsigned char)argv[i][j]] = 2;
				}
				j++;
			}
			i--;
		}
	}
	write(1, "\n", 1);
	return (0);
}
