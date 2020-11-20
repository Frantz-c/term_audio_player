/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   erase_end_of_line.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 13:42:15 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:22:45 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_clear_end_of_line(void)
{
	static char			*s = NULL;
	static unsigned int	len = 0;

	if (!s)
	{
		if ((s = tgetstr("ce", NULL)) == NULL)
			return ;
		len = strlen(s);
	}
	write(2, s, len);
}
