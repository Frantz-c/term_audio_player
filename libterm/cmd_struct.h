/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cmd_struct.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/27 19:58:10 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/15 16:28:03 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CMD_STRUCT_H
# define CMD_STRUCT_H

# include <stdint.h>

typedef struct	s_2ddim
{
	uint32_t	w;
	uint32_t	h;
}
t_2ddim;

typedef struct	s_select
{
	uint32_t	sx;
	uint32_t	sy;
	uint32_t	ex;
	uint32_t	ey;
}
t_select;

typedef struct	s_pos
{
	uint32_t	x;
	uint32_t	y;
}
t_pos;

typedef struct	s_term
{
	int32_t		w;
	int32_t		h;
	t_pos		curs;
}
t_term;

// remove pasted_end, pasted_start and use selected ?
// if (pasted) selected = pasted zone
// if (!pasted) selected = select_zone
typedef struct	s_cmds
{
	char		**line;		// command
	t_pos		curs;		// cursor (dans la chaine)
	uint32_t	*len;		// longueur de la ligne (remplie)
	uint32_t	*real_len;	// longueur de la ligne (allouée)
	uint32_t	*pad;		// padding de la ligne (width)
	char		**prefix;	// prefixe de chaque ligne (prefix[0] = prompt) // FREE IT !
	// <-- member to save the video/colors values and offsets of prompt
	const char	*prompt;	// prompt (avant interpretation)
	uint32_t	plen;		// longueur du prompt
	uint32_t	n_row;		// nombre de lignes
	uint32_t	total_len;	// longueur de la commande *
	uint32_t	locked_rows;// nombre de lignes non-modifiables
	uint32_t	origin_y;	// cmd start y position
	t_pos		end;		// cmd end coordinates
	t_select	selected;	// selection zone
	uint8_t		mode;		// SELECT_MODE or PASTE_MODE or NORMAL_MODE
	char		*buf;		// internal copy buffer
	uint32_t	buflen;		// internal buffer length
}
t_cmds;

typedef struct	s_escape_action
{
	char	*value;
	void	(*exec_action)(t_cmds *);
}
t_escape_action;

typedef struct	s_control_action
{
	char	value;
	void	(*exec_action)(t_cmds *);
}
t_control_action;

#endif
