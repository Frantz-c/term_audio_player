/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_fg_color.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 14:34:30 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:30:03 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_set_fg_color(int color)
{
	static const char	*fg = NULL;
	char				*cmd;

	if (!fg)
	{
		if ((fg = tgetstr("AF", NULL)) == NULL)
			return ;
	}
	cmd = tgoto(fg, 0, color);
	write(2, cmd, strlen(cmd));
}
