/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 20:46:20 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/21 20:53:44 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_STRUCTS_H
# define COREWAR_STRUCTS_H

/*
** THIS HEADER ONLY FOR STRUCTURES
** AND DEFINE CONSTANTS NEEDED FOR PROJECT COREWAR
*/

# include "op.h"
# include "libftprintf.h"

/*
** КАРЕТКА
** id				- уникальный номер каретки
** reg[MAX_REG]		- регистры каретки
** carry			- флаг carry
** pos				- позиция каретки
** op_code			- код операции на котором стоит каретка
** cycles_to_exec	- время до выполнения операции, на котором стоит каретка
** step				- кол-во байт, которое должна перешагнуть каретка, чтоб оказаться на следующей команде
*/

typedef struct		s_cursor
{
	int				id;
	char			reg[(REG_NUMBER + 1) * REG_SIZE];
	char			carry;
	int				pos;
	char			op_code;
	int				time_to_exec;
	char			step;
	struct s_cursor	*next;
}					t_cursor;

/*
** ВИРТУАЛЬНАЯ МАШИНА
** champs			- список игроков
** cursors			- список кареток
** field[MEM_SIZE]	- арена
** cycles			- количество пройденных циклов
** cycles_to_die	- количество оставшихся до конца партии циклов
** num_of_champs	- количество игроков
**
*/

typedef struct		s_vm
{
	struct s_champ	*champs;
	struct s_cursor	*cursors;
	char			field[MEM_SIZE];
	int				cycles;
	int				cycles_to_die;
	char			num_of_champs;
}					t_vm;


/*
** ЧЕМПИОН
** считанный из *.cor файла
** name			- имя игрока
** comment		- комментарий
** code			- код, считанный из файла
** code_size	- размер исполняемого кода
** next			- указатель на следующего чемпиона
*/

typedef	struct s_champ
{
	int				id;
	char			*name;
	char			*comment;
	int				magic;
	int				code_size;
	char			*code;
	struct s_champ	*next;
}				t_champ;

#endif
