/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   insert_blank_char.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 13:50:32 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:25:26 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_insert_blank_char(void)
{
	static char			*insert = NULL;
	static unsigned int	len;

	if (!insert)
	{
		if ((insert = tgetstr("ic", NULL)) == NULL)
			return ;
		len = strlen(insert);
	}
	write(2, insert, len);
}
