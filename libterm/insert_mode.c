/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   insert_mode.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 13:46:45 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:26:29 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


/* 
** don't move cursor in insert mode ??
*/
void	lt_insert_mode_on(void)
{
	static char			*insert;
	static uint32_t		len;

	if (!insert)
	{
		if ((insert = tgetstr("im", NULL)) == NULL)
			return ;
		len = strlen(insert);
	}
	write(2, insert, len);
}

void	lt_insert_mode_off(void)
{
	static char			*insert;
	static unsigned int	len;

	if (!insert)
	{
		if ((insert = tgetstr("ei", NULL)) == NULL)
			return ;
		len = strlen(insert);
	}
	write(2, insert, len);
}
