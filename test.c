#include "minishell.h"

void	print_phrase(t_phrase *phrase)
{
	t_token	*ptr;

	ptr = phrase->head;
	while (ptr)
	{
		printf("%s(%d) ", ptr->data, ptr->type);
		ptr = ptr->next;
	}
	printf("\n\n");
}

void print_input(t_input *list)
{
	t_phrase	*ptr;
	int			idx;

	idx = 1;
	ptr = list->head;
	while (ptr)
	{
		printf("phrase #%d\n", idx++);
		print_phrase(ptr);
		ptr = ptr->next;
	}
}

void	leaks(void)
{
	system("leaks minishell");
}
int main(void)
{
	t_input		*list;
	char		str[1000];

	atexit(leaks);
	gets(str);
	printf("input: %s\n\n", str);
	getchar();
	list = lexer(str);
	printf("Lexing Completed\n\n");
	if (list)
	{
		print_input(list);
		free_input(list);
	}
	return (0);	
}
