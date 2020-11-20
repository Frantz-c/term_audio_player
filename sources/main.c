#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "libterm.h"

#define DISPLAY_SIZE	25

typedef struct	s_song
{
	char		**title;
	char		**path;
	uint32_t	l;			// length
	uint32_t	a;			// allocated
	uint32_t	b;			// block size (n^2)
}
t_song;

void	set_raw_mode(void)
{
	static int				mode = 0;
	static struct termios	term;
	struct termios			tmp;

	if (mode == 0)
	{
		tcgetattr(STDIN_FILENO, &term);
		tmp = term;
		tmp.c_lflag &= ~(ECHO | ICANON);
		tmp.c_cc[VMIN] = 0;
		tmp.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &tmp);
	}
	else
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}

	mode ^= 1;
}

enum	e_status
{
	PLAYING, PAUSED, STOPED
};

void	write_list(t_song *list, uint32_t i, uint32_t size, uint32_t disp_size, uint32_t current)
{
	uint32_t	start;
	uint32_t	half_size;

	if (disp_size > size)
		disp_size = size;
	half_size = disp_size / 2;

	if (size - i < half_size)
		start = size - disp_size;
	else if (i < half_size)
		start = 0;
	else
		start = i - half_size;

	for (uint8_t j = 0; j != disp_size && j+start < list->l; j++)
	{
		lt_move_cursor(0, 8+j);

		lt_clear_end_of_line();

		if (j+start == current)
		{
			lt_set_video_mode(LT_BOLD);
			write(STDOUT_FILENO, "🦊 ", strlen("🦊 "));
		}
		if (j+start == i)
		{
			lt_set_bg_color(7);
			lt_set_fg_color(0);
		}

		if (list->title[j+start])
			write(STDOUT_FILENO, list->title[j+start], strlen(list->title[j+start]));
		else	// normalement on a toujours un titre
			write(STDOUT_FILENO, list->path[j+start], strlen(list->path[j+start]));

		if (j+start == i || j+start == current)
			lt_reset_attr();
	}
}

void	write_status(int volume, int status)
{
	char	barre[64];
	size_t	i = 0;
	lt_move_cursor(0, 6);
	
	volume /= 4;
	i = sprintf(barre, "🔈 [");
	memset(barre+i, '#', volume);
	i += volume;
	if (32 - volume)
	{
		memset(barre+i, ' ', 32 - volume);
		i += 32 - volume;
	}
	if (status == PLAYING)
		i += sprintf(barre+i, "]  ▶️");
	else if (status == PAUSED)
		i += sprintf(barre+i, "]  ⏸");
	else if (status == STOPED)
		i += sprintf(barre+i, "]  ⏹");
	else
	{
		barre[i++] = ']';
		barre[i++] = ' ';
		barre[i++] = '{';
	}


	write(STDOUT_FILENO, barre, i);
}

void	music_player_interface(t_song *list)
{
	Mix_Music	*music;
	uint32_t	mi = 0;
	uint32_t	current = 0;

	int		volume = 100;
	int		status = PLAYING;
	char	*help[4] =
	{
		"+/-        = volume control | up/down    = move cursor",
		"left/right = prev/next song | d          = delete song", 
		"space      = play/pause     | s          = stop",
		"enter      = choose song    | q          = quit",
	};
	uint8_t	button[8];


	if ((music = Mix_LoadMUS(list->path[mi])) == NULL)
	{
		fprintf(stderr, "ERREUR: Mix_LoadMUS(): %s\n", Mix_GetError());
		return;
	}



	lt_init();
	lt_full_screen_mode(LT_ON);
	set_raw_mode();
	lt_show_cursor(LT_OFF);

	for (uint8_t i = 0; i != 4; i++)
	{
		lt_move_cursor(0, i);
		write(1, help[i], strlen(help[i]));
	}

	write_status(volume, status);
	write_list(list, mi, list->l, DISPLAY_SIZE, current);

	Mix_PlayMusic(music, 0);
	Mix_VolumeMusic(volume);

	while (1)
	{
		ssize_t	rlen;

		if (Mix_PlayingMusic() == 0 && (status == PLAYING || status == PAUSED))
		{
			if (current != list->l-1)
			{
				current++;
				Mix_HaltMusic();
				Mix_FreeMusic(music);
				if ((music = Mix_LoadMUS(list->path[current])) == NULL)
				{
					fprintf(stderr, "ERREUR: Mix_LoadMUS(): %s\n", Mix_GetError());
					return;
				}
				Mix_PlayMusic(music, 0);
				status = PLAYING;
				write_list(list, mi, list->l, DISPLAY_SIZE, current);
			}
			else
			{
				status = STOPED;
				current = UINT32_MAX;
				write_status(volume, status);
				write_list(list, mi, list->l, DISPLAY_SIZE, current);
			}
		}

		if ((rlen = read(STDIN_FILENO, &button, 8)) == 0)
		{
			usleep(10000);
			continue;
		}
	
		if (rlen == 1)
		{
			if (button[0] == ' ')
			{
				if (Mix_PlayingMusic())
				{
					if (status == PLAYING)
					{
						Mix_PauseMusic();
						status = PAUSED;
					}
					else if (status == PAUSED)
					{
						Mix_ResumeMusic();
						status = PLAYING;
					}
				}
				else if (status == STOPED)
				{
					if ((music = Mix_LoadMUS(list->path[mi])) == NULL)
					{
						fprintf(stderr, "ERREUR: Mix_LoadMUS(): %s\n", Mix_GetError());
						return;
					}
					Mix_PlayMusic(music, 0);
					Mix_VolumeMusic(volume);
					status = PLAYING;
				}
			}
			else if (button[0] == 's')
			{
				Mix_HaltMusic();
				Mix_FreeMusic(music);
				current = UINT32_MAX;
				status = STOPED;
			}
			else if (button[0] == 'q')
			{
				Mix_HaltMusic();
				break;
			}
			else if (button[0] == 'd')
			{
				lt_move_cursor(0, 5);
				lt_set_bg_color(3);
				lt_set_fg_color(0);
				dprintf(STDOUT_FILENO, "Delete piste %s ? (y/n)", list->title[mi]);
				lt_reset_attr();

				while (1)
				{
					if ((rlen = read(STDIN_FILENO, &button, 8)) == 0)
					{
						usleep(10000);
						continue;
					}

					lt_move_cursor(0, 5);
					lt_clear_end_of_line();

					if (rlen == 1 && button[0] == 'y')
					{

						if (current == mi || list->l == 1)
						{
							Mix_HaltMusic();
							Mix_FreeMusic(music);
							if (list->l == 1)
								goto __end_function;
							current = UINT32_MAX;
							status = STOPED;
						}
						list->l--;
						free(list->title[mi]);
						memmove(list->title+mi, list->title+mi+1, (list->l - mi) * sizeof(char *));
						free(list->path[mi]);
						memmove(list->path+mi, list->path+mi+1, (list->l - mi) * sizeof(char *));
						write_status(volume, status);
						write_list(list, mi, list->l, DISPLAY_SIZE, current);
					}
					break;
				}
			}
			else if (button[0] == '\n')
			{
				current = mi;
				if (Mix_PlayingMusic() == 1)
				{
					Mix_HaltMusic();
					Mix_FreeMusic(music);
				}
				if ((music = Mix_LoadMUS(list->path[mi])) == NULL)
				{
					fprintf(stderr, "ERREUR: Mix_LoadMUS(): %s\n", Mix_GetError());
					return;
				}
				Mix_PlayMusic(music, 0);
				status = PLAYING;
				write_list(list, mi, list->l, DISPLAY_SIZE, current);
			}
			else if (button[0] == '+')
			{
				if (volume != 128)
				{
					volume += 4;
					Mix_VolumeMusic(volume);
				}
			}
			else if (button[0] == '-')
			{
				if (volume != 0)
				{
					volume -= 4;
					Mix_VolumeMusic(volume);
				}
			}
		}
		else if (rlen == 3)
		{
			if (memcmp(button, R_ARROW, 3) == 0)
			{
				if (current < list->l-1)
				{
					current++;
					Mix_HaltMusic();
					Mix_FreeMusic(music);
					if ((music = Mix_LoadMUS(list->path[current])) == NULL)
					{
						fprintf(stderr, "ERREUR: Mix_LoadMUS(): %s\n", Mix_GetError());
						return;
					}
					Mix_PlayMusic(music, 0);
					status = PLAYING;
					write_list(list, mi, list->l, DISPLAY_SIZE, current);
				}
			}
			else if (memcmp(button, L_ARROW, 3) == 0)
			{
				if (current != 0)
				{
					current--;
					Mix_HaltMusic();
					Mix_FreeMusic(music);
					if ((music = Mix_LoadMUS(list->path[current])) == NULL)
					{
						fprintf(stderr, "ERREUR: Mix_LoadMUS(): %s\n", Mix_GetError());
						return;
					}
					Mix_PlayMusic(music, 0);
					status = PLAYING;
					write_list(list, mi, list->l, DISPLAY_SIZE, current);
				}
			}
			else if (memcmp(button, U_ARROW, 3) == 0)
			{
				if (mi > 0)
				{
					mi--;
					write_list(list, mi, list->l, DISPLAY_SIZE, current);
				}
			}
			else if (memcmp(button, D_ARROW, 3) == 0)
			{
				if (mi < list->l-1)
				{
					mi++;
					write_list(list, mi, list->l, DISPLAY_SIZE, current);
				}
			}
		}

		write_status(volume, status);
	}

	Mix_FreeMusic(music);
	__end_function:
	set_raw_mode();
	lt_full_screen_mode(LT_OFF);
	lt_show_cursor(LT_ON);
}

int		music_player(t_song *list)
{

	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0)
	{
		fprintf(stderr, "ERREUR: Mix_Init(): %s\n", Mix_GetError());
		return (1);
	}

	{
		int err = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
		if (err != 0)
		{
			fprintf(stderr, "ERREUR: Mix_OpenAudio(): %s\n", Mix_GetError());
			return (2);
		}
	}
	

	music_player_interface(list);

	Mix_CloseAudio();
	Mix_Quit();

	return (0);
}

/*
**	norme ISO/CEI 10646 : UCS-2	-> 16 bits unicode
**
**	fonction de conversion en UTF-8
**
**	0 + 7 bits											0     - 7F
**	0b110   + 5  &  0b10 + 6							80    - 7FF
**	0b1110  + 4  &  0b10 + 6  &  0b10 + 6				800   - FFFF
**	0b11110 + 3  &  0b10 + 6  &  0b10 + 6  &  0b10 + 6	10000 - 1FFFFF
*/
char	*usc2_to_utf8_string(char *s, uint32_t len)
{
	uint8_t		*utf8;
	uint32_t	j;
	uint8_t		le = 0;

	if (len & 1) fprintf(stderr, "WARNING: USC-2 length impair\n");

	utf8 = malloc(len * 2);
	j = 0;

	if (*(uint8_t *)s == 0xFFu && *((uint8_t *)s+1) == 0xFEu)
	{
		s += 2;
		len -= 2;
		le++;		// byte order = little-endian
	}
	else if (*(uint8_t *)s == 0xFEu && *((uint8_t *)s+1) == 0xFFu)
	{
		s += 2;
		len -= 2;
	}

	for (uint32_t i = 0; i < len; i += 2)
	{
		uint16_t	u;
		
		if (le)
			u = ((uint8_t *)s)[i] | (*((uint8_t *)s+i+1) << 8);
		else
			u = (*((uint8_t *)s+i) << 8) | *((uint8_t *)s+i+1);

		if (u < 0x80u)
		{
			utf8[j++] = (uint8_t)u;
		}
		else if (u < 0x800u)
		{
			utf8[j++] = 0xC0u | (u >> 11);
			utf8[j++] = 0x80u | (u & 0x3Fu);
		}
		else
		{
			utf8[j++] = (0xE0u | ((u >> 12) & 0x0Fu));
			utf8[j++] = (0x80u | ((u >> 6) & 0x3Fu));
			utf8[j++] = (0x80u | (u & 0x3Fu));
		}
	}
	utf8[j] = '\0';

	if (le)
		free(s-2);
	else
		free(s);
	return ((char*)utf8);
}

// https://id3.org/id3v2.3.0
char	*get_mp3_ID3v2(char *s, ssize_t len)
{
	uint8_t		version, flag, info = 0;
	uint32_t	size;
	char		*artist = NULL, *title = NULL;
	char		*new_title = NULL;


	if (memcmp(s, "ID3", 3))
		return (NULL);
	

	version = ((uint8_t *)s)[3];
	s += 6;	// skip "ID3", version (2bytes) and flags (1byte)
	len -= 6;
	flag = ((uint8_t *)s)[-1];
	if (flag) return (NULL);

	if (version == 3)
	{
		char		*frame_name;
		uint32_t	fsize;
		uint8_t		fflag;


		size = ((uint8_t *)s)[3] | (((uint8_t *)s)[2] << 7) | (((uint8_t *)s)[1] << 14) | (((uint8_t *)s)[0] << 21);
		s += 4;
		len -= 4;

		// On veut les frames TPE1, TIT2	(artiste et titre)
		for (uint32_t i = 0; i < size && i < len;)
		{
			if (len - i <= 10)
				break;

			frame_name = s+i;
			fsize = ((uint8_t *)s)[i+7] | (((uint8_t *)s)[i+6] << 8) | (((uint8_t *)s)[i+5] << 16) | (((uint8_t *)s)[i+4] << 24);
			fflag = (((uint8_t *)s)[i+8] << 8) | ((uint8_t *)s)[i+9];
			if (flag != 0)
			{
				i += 10 + fsize;
				continue;
			}
			i += 10;	// skip header

			if ((info & 0x01) == 0 && memcmp(frame_name, "TPE1", 4) == 0)
			{
				uint32_t	k = 0;
				uint8_t		encoding;
				artist = malloc(fsize);

				encoding = ((uint8_t *)s)[i];

				memcpy(artist, s+i+1, fsize-1);
				artist[fsize-1] = '\0';

				if (encoding == 1)		// ucs-2
					artist = usc2_to_utf8_string(artist, fsize-1);
				else if (encoding == 2)	// utf-16
					fprintf(stderr, "WARNING: unsupported encoding UTF16\n");

				info |= 0x01;
			}
			else if ((info & 0x02) == 0 && memcmp(frame_name, "TIT2", 4) == 0)
			{
				uint32_t	k = 0;
				uint8_t		encoding;
				title = malloc(fsize);

				encoding = ((uint8_t *)s)[i];

				memcpy(title, s+i+1, fsize-1);
				title[fsize-1] = '\0';

				if (encoding == 1)		// ucs-2
					title = usc2_to_utf8_string(title, fsize-1);
				else if (encoding == 2)	// utf-16
					fprintf(stderr, "WARNING: unsupported encoding UTF16\n");

				info |= 0x02;
			}

			if (info == 0x3)
				break;

			i += fsize;
		}
	}
	else
		return (NULL);

		
	if (info)
	{
		if (info == 1)
		{
			free(artist);
			return (NULL);
		}
		if (info == 3)
		{
			new_title = malloc(strlen(title) + strlen(artist) + 8);
			sprintf(new_title, "%s  - %s", title, artist);
			free(title);
			free(artist);
		}
		else
			new_title = title;
	}

	return (new_title);
}


char	*get_song_name_and_artist(const char *filename)
{
	char	*new_title = NULL;
	char	buffer[2048];
	size_t	len;


	// si le fichier est d'extension mp3 : 
	if (strncmp(filename + strlen(filename) - 4, ".mp3", 4) == 0)
	{
		int	fd = open(filename, O_RDONLY);
		ssize_t	len;

		if (fd == -1)	goto __delete_extension_and_path;
		len = read(fd, buffer, 2048);
		close(fd);

		// on cherche le header ID3v2
		if ((new_title = get_mp3_ID3v2(buffer, len)) != NULL)
			return (new_title);
	}

	__delete_extension_and_path:
	len = strlen(filename);

	new_title = malloc(len+1);
	memcpy(new_title, filename, len+1);
	
	uint32_t last_point = len - 1;
	for (uint32_t i = len - 1; i != UINT32_MAX; i--)
	{
		if (new_title[i] == '.')
		{
			new_title[i] = '\0';
			last_point = i;
		}
	}

	for (uint32_t i = last_point; i != UINT32_MAX; i--)
	{
		if (new_title[i] == '/')
		{
			memmove(new_title, new_title+i+1, strlen(new_title+i));
			break;
		}
	}

	return (new_title);
}

extern
void	realloc_song_if_needed(t_song *s)
{
	if ( (s->l & (s->b - 1)) == 0)
	{
		s->a += s->b;
		s->title = realloc(s->title, sizeof(char *) * s->a);
		s->path = realloc(s->path, sizeof(char *) * s->a);
	}
}

extern
void	free_song(t_song *s)
{
	if (s->path && s->title)
	{
		for (uint32_t i = 0; i != s->l; i++)
		{
			if (s->path[i])
				free(s->path[i]);
			if (s->title[i])
				free(s->title[i]);
		}
		free(s->path);
		free(s->title);
	}
	free(s);
}

extern
t_song	*load_list_from_playlist(const char *filename)
{
	FILE	*f = fopen(filename, "r");
	char	*line = NULL;
	t_song	*list = NULL;
	size_t	len = 0;
	char	prefix[256] = {0};



	if (f == NULL)
	{
		fprintf(stderr, "ERREUR: impossible d'ouvrir %s\n", filename);
		return (NULL);
	}

	list = calloc(1, sizeof(t_song));
	list->b = 0x20;

	while (getline(&line, &len, f) != -1)
	{
		char	*s = line;

		// skip spaces, empty lines and comments
		while (*s == ' ' || *s == '\t') s++;
		if (*s == '\n' || *s == '\0' || *s == '#')
			continue;

		/*
		**	set prefix instruction
		*/
		if (memcmp(s, "$prefix", 7) == 0)
		{
			s += 7;
			while (*s == ' ' || *s == '\t') s++;
			if (*s != '=')
				goto __error;
			while (*(++s) == ' ' || *s == '\t');
			if (*s != '"')
				goto __error;

			s++;
			uint8_t i = 0;
			while (1)
			{
				if (*s == '\\') s++;
				else if (*s == '"' || *s == '\n' || *s == '\0')
					break;
				prefix[i++] = *s;
				s++;
			}
			prefix[i] = 0;
		}
		/*
		**	song path
		*/
		else
		{
			char	*start = s;

			while (*s != '\n' && *s != '\0')	s++;

			realloc_song_if_needed(list);
			list->path[list->l] = malloc(strlen(prefix) + (s - start) + 1);
			sprintf(list->path[list->l], "%s%.*s", prefix, (int)(s - start), start);
			list->title[list->l] = get_song_name_and_artist(list->path[list->l]);
			list->l++;
		}
	}

	free(line);
	return (list);

	__error:
	fprintf(stderr, "ERREUR: syntaxe de la liste\n");
	free(line);
	//free tous les éléments de la liste
	free_song(list);
	return (NULL);
}

extern
t_song	*load_list_from_argv(char *argv[], int argc)
{
	t_song	*list = NULL;

	list = calloc(1, sizeof(t_song));
	list->b = 0x10;
	list->a = argc + (list->b - (argc & (list->b-1)));
	list->l = 0;
	list->path = malloc(sizeof(char *) * list->a);
	list->title = malloc(sizeof(char *) * list->a);

	for (uint32_t i = 0; i != argc; i++)
	{
		list->path[list->l] = strdup(argv[i]);
		list->title[list->l] = get_song_name_and_artist(list->path[list->l]);
		list->l++;
	}

	return (list);
}


/*
**	une liste est composée de variables et de chemins :
**
**	$prefix = "/Users/frantz/Music/"
**	toto.mp3
**	...
**	
**	accepter un nombre indéfini d'arguments
*/
int	main(int argc, char *argv[])
{
	t_song	*music_list = NULL;

	if (argc < 2)
	{
		__print_help:
		fprintf(stderr,
			"%s [music path]...\n"
			"%s --list=[list path]\n",
			*argv, *argv
		);
		return (1);
	}

	if (memcmp(argv[1], "--list=", 7) == 0)
	{
		if (argc != 2)
			goto __print_help;
		music_list = load_list_from_playlist(argv[1] + 7);
		if (music_list == NULL)
			return (2);
	}
	else
	{
		music_list = load_list_from_argv(argv+1, argc-1);
	}


	return (music_player(music_list));
}
