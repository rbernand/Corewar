/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 13:52:48 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/07 17:20:17 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <sys/types.h>

# define NEW_LIST(X)			((X *)list_new(sizeof(X)))
# define PUSH_BACK(X, Y)		list_push_back((t_list **)(X), (t_list *)(Y))
# define PUSH_FRONT(X, Y)		list_push_front((t_list **)(X), (t_list *)(Y))
# define ITER_LIST(X, Y)		list_iter((t_list *)(X), (void (*)(t_list *))(Y))
# define LIST_DELETE(X, Y, F)	list_delete((t_list **)(X), (t_list *)(Y), (F))
# define LIST_BACK(X)			list_back((t_list *)(X))

typedef struct				s_list
{
	void					*next;
}							t_list;

void						list_push_back(t_list **start, t_list *new);
void						list_push_front(t_list **start, t_list *new);
t_list						*list_new(size_t size);
void						list_delete(t_list **lst,
							t_list *todel, void (*f)(void *));
t_list						*list_back(t_list *lst);

#endif
