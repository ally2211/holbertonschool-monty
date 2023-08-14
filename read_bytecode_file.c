#include "main.h"

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
char *value;

void read_bytecode_file(FILE *file)
{
    char *line = NULL, *opcode;
    size_t len = 0, read;
    unsigned int line_number = 0;
    char delimiters[] = " $\t\n";
    stack_t *stack = NULL;
    bool opcode_found;
	
    while ((read = getline(&line, &len, file)) != (ssize_t) -1)
	{
		opcode = strtok(line, delimiters);
		value = strtok(NULL, delimiters);
		opcode_found = false;

	/*	// Just as a debug print for now:
		if (value != NULL)
		{
			printf("Opcode: %s, Value: %s\n", opcode, value);
		}
		else
		{
			printf("Opcode: %s\n", opcode);
		}
	*/
		if (opcode)
		{
			for (int i = 0; ops[i].opcode; i++)
			{
				if (strcmp(opcode, ops[i].opcode) == 0)
				{
					if (strcmp(opcode, "push") == 0 && (value == NULL || !is_integer(value)))
					{
						fprintf(stderr, "L%d: usage: push integer. value is %s\n", line_number, value);
						free(line);
						fclose(file);
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
				free(line);
				fclose(file);
				exit(EXIT_FAILURE);
			}

			line_number++;
			line++;
		}
	}
}

int is_integer(char *str)
{
    if (!str || *str == '\0')
        return 0;
    if (*str == '-' || *str == '+')
        str++;
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}
