/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:32:05 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/21 16:24:03 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

/*
** THIS HEADER ONLY FOR FUNCTIONS PROTOTYPES
*/

# include <stdio.h>
# include "corewar_structs.h"


# define FILE_FAILED 300
# define INVALID_CHAMP_NUM 301
# define WAITING_FILE 303
# define TYPE_ERROR 304


/*
** MANAGMENT ERRORS
*/

void			ft_exit_core(int err, char *file_name);

/*
** CURSOR
*/

t_cursor		*new_cursor(void);

void			add_cursor(t_cursor **list, t_cursor *cursor);

#endif
