#include "monty.h"

instruction_t ops[] = {
	{"push", push},
	{"pall", pall},
	{"pint", pint},
	{"pop", pop},
	{"swap", swap},
	{"add", add},
	{"nop", nop},
	{NULL, NULL}
};
char *value = NULL;
/**
 * is_empty_or_spaces - check if spaces or empty line
 * @str:  string to check
 *
 * Return: bool true no spaces
 */
bool is_empty_or_spaces(const char *str)
{
	while (*str)
	{
		if (!isspace((unsigned char)*str))
			return (false);
		str++;
	}
	return (true);
}
/**
 * is_integer - check if is integer including a zero
 * @str:  string to check
 *
 * Return: 1 for yes is an integer
 **/
int is_integer(char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
/**
 * read_bytecode_file - getline and tokenize
 * @file:  name of file
 *
 * Return: void
 **/
void read_bytecode_file(FILE *file)
{
	char *opcode, *line = NULL;
	size_t len = 0, read, eof = -1;
	unsigned int line_number = 1;
	stack_t *stack = NULL;
	bool opcode_found;

	while ((read = getline(&line, &len, file)) != eof)
	{
		if (is_empty_or_spaces(line))
			line_number++;
		else
		{
			opcode = strtok(line, " $\t\n");
			if (opcode != NULL)
				value = strtok(NULL, " $\t\n");
			opcode_found = false;
			if (opcode)
			{
				for (int i = 0; ops[i].opcode; i++)
				{
					if (strcmp(opcode, ops[i].opcode) == 0)
					{
					if (!is_integer(value))
						value = NULL;
					if (strcmp(opcode, "push") == 0 && (value == NULL || !is_integer(value)))
					{
						fprintf(stderr, "L%d: usage: push integer\n", line_number);
						free_stack(&stack);
					if (line != NULL)
					{
						free(opcode);
						line = NULL;
					}
					exit(EXIT_FAILURE);
					}
					ops[i].f(&stack, line_number);
					opcode_found = true;
					break;
					}
				}
				if (!opcode_found)
				{
					fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
					if (line != NULL)
					{
					free(opcode);
					if (!value)
						free(value);
					line = NULL;
					}
					free_stack(&stack);
					exit(EXIT_FAILURE);
				}
				line_number++;
			}
		}
	}
	free_stack(&stack);
	if (line != NULL)
	{
		free(value);
		free(opcode);
		line = NULL;
	}
}
