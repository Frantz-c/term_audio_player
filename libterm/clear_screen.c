/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clear_screen.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 13:36:56 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:23:16 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


/*
**	clear screen and cursor home
*/
void	lt_clear_screen(void)
{
	static char			*s = NULL;
	static unsigned int	len = 0;

	if (!s)
	{
		if ((s = tgetstr("cl", NULL)) == NULL)
			return ;
		len = strlen(s);
	}
	write(2, s, len);
}
