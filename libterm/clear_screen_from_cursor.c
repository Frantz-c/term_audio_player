/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clear_screen_from_cursor.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 13:40:47 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:23:34 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_clear_screen_from_cursor(void)
{
	static char			*s = NULL;
	static unsigned int	len = 0;

	if (!s)
	{
		if ((s = tgetstr("cd", NULL)) == NULL)
			return ;
		len = strlen(s);
	}
	write(2, s, len);
}
