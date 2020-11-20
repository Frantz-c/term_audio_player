/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   insert_line_before_cursor.c                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 13:54:49 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:26:07 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_insert_line_before_cursor(void)
{
	static char			*insert = NULL;
	static unsigned int	len;

	if (!insert)
	{
		if ((insert = tgetstr("al", NULL)) == NULL)
			return ;
		len = strlen(insert);
	}
	write(2, insert, len);
}
