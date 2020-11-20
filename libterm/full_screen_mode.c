/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   full_screen_mode.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/17 14:03:03 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/17 14:09:16 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_full_screen_mode(uint8_t on)
{
	static char		*full_on = NULL;
	static char		*full_off = NULL;
	static uint32_t	on_len = 0;
	static uint32_t	off_len = 0;

	if (on)
	{
		if (!full_on)
		{
			if ((full_on = tgetstr("ti", NULL)) == NULL)
				return ;
			on_len = strlen(full_on);
		}
		write(STDERR_FILENO, full_on, on_len);
	}
	else
	{
		if (!full_off)
		{
			if ((full_off = tgetstr("te", NULL)) == NULL)
				return ;
			off_len = strlen(full_off);
		}
		write(STDERR_FILENO, full_off, off_len);
	}
}
