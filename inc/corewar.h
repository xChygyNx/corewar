/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:32:05 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/22 21:01:58 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

# include <stdio.h>
# include "corewar_structs.h"

#define DUMP_COLUMNS	64
#define DUMP_ROWS		64

typedef enum	e_error
{
	NONE,
	USAGE = 300,
	FILE_FAILED,
	INVALID_CHAMP_NUM,
	WAITING_FILE,
	FILETYPE_ERROR,
	NO_CODE_ERROR,
	INVALID_OPTION,
	INVALID_HEAD_SIZE,
	EXEC_CODE_ERROR,
	EXEC_SIZE_ERROR,
	CODE_SIZE_ERROR
}				t_error;

/*
** MANAGMENT ERRORS
*/

void			ft_exit(int err, char *file_name);

void			ft_exit_read(t_error err, char *file, int fd, int exec_size);

/*
** OPTIONS
*/

void			check_champ_num(char *num);

t_options		get_options(int ac, char **av);


/*
** UTILITY FUNCTIONS
*/

int				reverse_bits(int num, char full_bit);

void			dump_arena(char *arena);

int				isdigit_word(char *word);

/*
** CURSOR
*/

t_cursor		*new_cursor(int pos);

t_cursor		*copy_cursor(t_cursor *src, int pos, char mode);

void			add_cursor(t_cursor **list, t_cursor *cursor);

void			kill_cursor(t_cursor **list, t_cursor *cursor);

/*
** CHAMPION FUNCTIONS
*/

t_champ			*create_new_champ(t_header *head, void *code);

void			del_one_champion(t_champ **begin);

void			del_champions(t_champ **champ);

void			add_champion2end(t_champ **begin, t_champ *champ);

t_champ			*read_champions_from_args(int ac, char **av);

#endif
