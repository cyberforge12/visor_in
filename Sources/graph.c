#include "../Includes/visor_in.h"

void			init_graph(t_graph *graph)
{
	graph->lem_count = 0;
	graph->node = NULL;
	graph->strokes = NULL;
	graph->str = NULL;
	read_all(graph);
	fill_node(graph);
	check_all(graph);
}

t_node			*create_node(char *str)
{
	char		**split;
	t_node		*node;
	static int	z;

	if (!str)
		ft_error("Input error");
	if (!(split = ft_strsplit(str, ' ')))
		ft_error("Malloc error");
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		ft_error("Room error");
	if (!(node = malloc(sizeof(t_node))))
		ft_error("Malloc error");
	node->name = split[0];
	node->point = (SDL_Point){ft_atoi(split[1]), ft_atoi(split[2])};
	free(split[1]);
	free(split[2]);
	free(split);
	return (node);
}

int				check_type(char *str)
{
	if (!str)
		ft_error("Input error");
	if (str[0] == '#')
	{
		str++;
		if (str[0] == '#')
		{
			str++;
			if (!ft_strcmp(str, "start"))
				return (1);
			else if (!ft_strcmp(str, "end"))
				return (2);
		}
		return (-1);
	}
	if (ft_strchr(str, '-'))
		return (-2);
	return (0);
}

SDL_Point		find_by_name(char *name, t_graph *graph)
{
	t_list		*tmp;

	tmp = graph->node;
	while (tmp)
	{
		if (!ft_strcmp(((t_node*)tmp->content)->name, name))
			return (((t_node*)tmp->content)->point);
		tmp = tmp->next;
	}
	return ((SDL_Point){-228});
}

t_stroke		*create_stroke(char *a, char *b, t_graph *graph)
{
	t_stroke	*ret;

	if (!a || !b || find_by_name(a, graph).x == -228 || find_by_name(b, graph).x == -228)
		ft_error("Room name error");
	if (!(ret = malloc(sizeof(t_stroke))))
		ft_error("Malloc error");
	ret->p1 = find_by_name(a, graph);
	ret->p2 = find_by_name(b, graph);
	return (ret);
}
