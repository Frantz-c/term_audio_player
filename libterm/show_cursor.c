/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   show_cursor.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/17 20:37:30 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/17 20:44:02 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_show_cursor(uint8_t show_cursor)
{
	static char			*show = NULL;
	static char			*hide = NULL;
	static unsigned int	len1;
	static unsigned int	len2;

	if (show_cursor)
	{
		if (!show)
		{
			if ((show = tgetstr("ve", NULL)) == NULL)
				return ;
			len1 = strlen(show);
		}
		write(2, show, len1);
	}
	else
	{
		if (!hide)
		{
			if ((hide = tgetstr("vi", NULL)) == NULL)
				return ;
			len2 = strlen(hide);
		}
		write(2, hide, len2);
	}
}
