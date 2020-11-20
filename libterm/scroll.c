/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scroll.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/02 17:19:01 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 21:13:48 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_scroll_n_up(int n)
{
	static const char	*scroll = NULL;
	char				*cmd;
	uint32_t			len;

	if (!scroll)
	{
		if ((scroll = tgetstr("SF", NULL)) == NULL)
			return ;
	}
	cmd = tgoto(scroll, 0, n);
	len = strlen(cmd);
	write(STDERR_FILENO, cmd, len);
}

void	lt_scroll_n_down(int n)
{
	const char		*scroll = NULL;
	char			*cmd;
	uint32_t		len;

	if (!scroll)
	{
		if ((scroll = tgetstr("SR", NULL)) == NULL)
			return ;
	}
	cmd = tgoto(scroll, 0, n);
	len = strlen(cmd);
	write(STDERR_FILENO, cmd, len);
}

void	lt_scroll_up(void)
{
	static const char	*scroll = NULL;
	static uint32_t		len;

	if (!scroll)
	{
		if ((scroll = tgetstr("sf", NULL)) == NULL)
			return ;
		len = strlen(scroll);
	}
	write(STDERR_FILENO, scroll, len);
}

void	lt_scroll_down(void)
{
	const char		*scroll = NULL;
	static uint32_t	len;

	if (!scroll)
	{
		if ((scroll = tgetstr("sr", NULL)) == NULL)
			return ;
		len = strlen(scroll);
	}
	write(STDERR_FILENO, scroll, len);
}
