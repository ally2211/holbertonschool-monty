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
char *value;


bool is_empty_or_spaces(const char* str) {
    while (*str) {
        if (!isspace((unsigned char)*str))
            return false; // found a non-space character
        str++;
    }
    return true;
}

void read_bytecode_file(FILE *file)
{
    char *line = NULL, *opcode;
    size_t len = 0, read, eof = -1;
    unsigned int line_number = 1;
    char delimiters[] = " $\t\n";
    stack_t *stack = NULL;
    bool opcode_found;


	while ((read = getline(&line, &len, file)) != eof)
	{
		if (is_empty_or_spaces(line))
		{
			free(line);
			line_number++;
		//	printf("Error: Line contains only spaces or is empty.\n");
		}
		else
		{
			opcode = strtok(line, delimiters);
			value = strtok(NULL, delimiters);
			opcode_found = false;
	
		/*	if (value != NULL)
			{
				printf("Opcode: %s, Value: %s\n", opcode, value);
			}
			else
			{
				printf("Opcode: %s\n", opcode);
				exit(EXIT_FAILURE);
			}*/	
			if (opcode)
			{
				for (int i = 0; ops[i].opcode; i++)
				{
					if (strcmp(opcode, ops[i].opcode) == 0)
					{
						if (strcmp(opcode, "push") == 0 && (value == NULL || !is_integer(value)))
						{
							fprintf(stderr, "L%d: usage: push integer\n", line_number);
							free(line);
							exit(EXIT_FAILURE);
						}

						ops[i].f(&stack, line_number);
						opcode_found = true;
						free(line);
						break;
					}
				}
				if (!opcode_found)
				{
					fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
					free(line);
		//			fclose(file);
					exit(EXIT_FAILURE);
				}
				line_number++;
				line++;
			}
		}
	}
	free(line);
	fclose(file);
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
