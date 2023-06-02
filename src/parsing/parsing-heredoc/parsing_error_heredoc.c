/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:30:22 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/02 15:46:07 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <errno.h>
// #include "../../../includes/parsing_meta_state_machine.h"
// #include "../../../includes/minishell.h"

// /* Handles error in state machine : Delivers error message and set state of 
// state machine to error */
// void	parsing_error_meta(t_state *current_state)
// {
// 	printf("minishell: malloc() failed: %s\n", strerror(errno));
// 	g_exit_code = errno;
// 	*current_state = error;
// }
