#include "monty.h"

/**
 * free_stack - free stack
 * @stack: pointerr to the head of the stack.
 **/
void free_stack(stack_t **stack)
{
	stack_t *current_node;

	while (*stack)
	{
		current_node = *stack;
		*stack = (*stack)->next;
		free(current_node);
	}
}
/**
 * push - push a value at the top of the stack.
 * @stack: double pointer to the head of the stack.
 * @line_number: line number of the opcode in the file.
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new_node;
	(void) line_number;

	new_node = malloc(sizeof(stack_t));
	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = atoi(value);
	new_node->next = *stack;
	new_node->prev = NULL;
	if (*stack)
		(*stack)->prev = new_node;
	*stack = new_node;
}

/**
 * pall - print all the values starting at the top of the stack.
 * @stack: double pointer to the head of the stack.
 * @line_number: line number of the opcode in the file.
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	(void) line_number;

	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
	free_stack(&current);
}
