/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:32:15 by pcredibl          #+#    #+#             */
/*   Updated: 2019/12/14 17:14:25 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void 	print_frame()
{
	int		i;

	color_set (FRAME, NULL);
	i = 0;
	while (++i < (3 * DUMP_COLUMNS) + 75)
	{
		mvaddch(1, i, ' ');
		mvaddch(DUMP_ROWS + 4, i, ' ');
	}
	i = 0;
	while (++i < DUMP_ROWS + 5)
	{
		mvaddch(i, 0, ' ');
		mvaddch(i, (3 * DUMP_COLUMNS) + 4, ' ');
		mvaddch(i, (3 * DUMP_COLUMNS) + 75, ' ');
	}
	color_set (WHITE_TEXT, NULL);
}

static void		print_src_arena(t_vm *vm, char *byte)
{
	int		i;
	int		j;
	t_champ	*temp;
	char	color_code;
	int		champ_begin;

	color_code = 0;
	temp = vm->champs;
	attron(A_BOLD);
	i = 0;
	while (i < DUMP_ROWS)
	{
		j = 0;
		if (!(((i * DUMP_COLUMNS) + j) % ((DUMP_COLUMNS * DUMP_ROWS) / vm->num_of_champs)))
		{
			color_code++;
			color_set(color_code, NULL);
			champ_begin = (i * DUMP_COLUMNS) + j;
		}
		else if (temp && (((i * DUMP_COLUMNS) + j) - champ_begin) >= temp->code_size)
		{
			color_set(WHITE_TEXT, NULL);
			champ_begin = 0;
			temp->next ? temp = temp->next : 0;
		}

		while (j < DUMP_COLUMNS)
		{
			//mvwprintw(arena, i, 3 * j, "X");
			//move(i + 3, (3 * j) + 3);
			mvprintw(i + 3, (3 * j) + 3, "%02hhx ", *byte);
			byte += 1;
			j++;
		}
		i++;
	}
	refresh();

}

static void		print_info(t_vm *vm)
{
	int		i;
	
	attron(A_BOLD);
	mvaddstr(5, (3 * DUMP_COLUMNS) + 8, "Cycles/second limit : ");
	//тут будет пока несуществующий параметр структуры
	//printw("\t%d", vm->vis_speed);
	mvaddstr(8, (3 * DUMP_COLUMNS) + 8, "Cycle : ");
	printw("\t%d", vm->cycles);
	mvaddstr(14, (3 * DUMP_COLUMNS) + 8, "Processes : ");
	//тут будет пока несуществующий параметр структуры
	//printw("\t%d", vm->num_of_cursors);
	i = 0;
	/*информация про игроков;
	while (++i <= vm->num_of_champs)
		print_champ_info(vm->champs);*/
	mvprintw(20 + (6 * i), (3 * DUMP_COLUMNS) + 8, "CYCLE TO DIE :\t%d",\
	vm->cycles_to_die);
	mvprintw(22 + (6 * i), (3 * DUMP_COLUMNS) + 8, "CYCLE DELTA :\t%d",\
	CYCLE_DELTA);
	mvprintw(24 + (6 * i), (3 * DUMP_COLUMNS) + 8, "NBR LIVE :\t%d",\
	NBR_LIVE);
	mvprintw(26 + (6 * i), (3 * DUMP_COLUMNS) + 8, "MAX CHECKS :\t%d",\
	MAX_CHECKS);
	refresh();
	attron(A_NORMAL);
}

static void color_init(void)
{
	start_color();
	init_pair(RED_TEXT, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN_TEXT, COLOR_GREEN, COLOR_BLACK);
	init_pair(BLUE_TEXT, COLOR_BLUE, COLOR_BLACK);
	init_pair(YELLOW_TEXT, COLOR_YELLOW, COLOR_BLACK);
	init_pair(WHITE_TEXT, COLOR_WHITE, COLOR_BLACK);
	init_pair(FRAME, COLOR_BLACK, COLOR_WHITE);
}

void	visualizator(t_vm *vm)
{
	WINDOW *exp;
	WINDOW *arena;

	if (!initscr())
		ft_exit(NCURSES_INIT_ERROR, &vm);
	//arena = newwin(DUMP_ROWS, 3 * DUMP_COLUMNS, 3, 3);
	color_init();
	//box(arena, 0, 0);
	print_src_arena(vm, vm->arena);
	print_info(vm);
	print_frame();
	
	getch();
	//wclear(arena);
	//wrefresh(arena);
	getch();
	//print_src_arena(vm, vm->arena);
	getch();
	/*exp = newwin(30, 75, 5, (3 * DUMP_COLUMNS) + 80);
	//box(exp, 1, 1);
	wattron(exp, A_BOLD);
	//wcolor_set(exp, 2, NULL);
	mvwaddstr(exp, 0, 1, "hello");
	mvwaddstr(exp, 1, 1, "world");
	wrefresh(exp);*/
	/*getch();
	wclear(exp);
	wrefresh(exp);
	getch();*/
}