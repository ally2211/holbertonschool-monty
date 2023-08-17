#include "monty.h"

/**
 * pop - remove the value at the top of the stack.
 * @stack: double pointer to the head of the stack.
 * @line_number: line number of the opcode in the file.
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (!*stack)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	*stack = (*stack)->next;
	if (*stack)
		(*stack)->prev = NULL;
	free(temp);
}

/**
 * pint - prints the value at the top of the stack, followed by a new line.
 * @stack: double pointer to the head of the stack.
 * @line_number: line number of the opcode in the file.
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}
/**
 * swap - swaps the top two elements of the stack.
 * @stack: double pointer to the head of the stack.
 * @line_number: line number of the opcode in the file.
 */
void swap(stack_t **stack, unsigned int line_number)
{
	int temp_val;

	 /* Check if stack has less than two elements*/
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	/* Swap the values of the top two nodes*/
	temp_val = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp_val;
}
/**
 * add - adds the top two elements of the stack.
 * @stack: double pointer to the head of the stack.
 * @line_number: line number of the opcode in the file.
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp_node;

	/* Check if stack has less than two elements */
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	/* Add the values of the top two nodes*/
	(*stack)->next->n += (*stack)->n;

	/* Remove the top node (free it) and re-assign the top*/
	temp_node = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(temp_node);
}

/**
 * nop - doesn't do anything.
 * @stack: double pointer to the head of the stack.
 * @line_number: line number of the opcode in the file.
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}
