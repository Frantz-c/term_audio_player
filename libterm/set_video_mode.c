/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display_attributes.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 12:53:51 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:30:18 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"
//

void	lt_set_video_mode(int mode)
{
	static char		*cap[7] = {
		"md", "us", "mb", "mh", "mk", "mp", "mr"
	};
	static char		*modes[7] = {NULL};
	unsigned int	i;
	unsigned int	b;

	i = 0;
	b = 1u;
	while (b != LT_MODE_END)
	{
		if ((mode & b))
		{
			if (modes[i] == NULL)
			{
				if ((modes[i] = tgetstr(cap[i], NULL)) != NULL)
					write(2, modes[i], strlen(modes[i]));
			}
			else
				write(2, modes[i], strlen(modes[i]));
		}
		i++;
		b <<= 1;
	}
}
