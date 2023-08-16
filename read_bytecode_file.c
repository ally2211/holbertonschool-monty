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

bool is_empty_or_spaces(const char* str) {
    while (*str) {
        if (!isspace((unsigned char)*str))
            return false; // found a non-space character
        str++;
    }
    return true;
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
		{
			line_number++;
		//	printf("Error: Line contains only spaces or is empty.\n");
		}
		else
		{
			opcode = strtok(line, " $\t\n");
		        if (opcode != NULL)
			{
				value = strtok(NULL, " $\t\n");
			}
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
	//			printf("atoi is %d\n", atoi(value));
				for (int i = 0; ops[i].opcode; i++)
				{
					if (strcmp(opcode, ops[i].opcode) == 0)
					{
						if (strcmp(opcode, "push") == 0 && (value == NULL || !is_integer(value)))
						{
							fprintf(stderr, "L%d: usage: push integer\n", line_number);
							free_stack(&stack);
							if (line != NULL)
							{	
								free(opcode);
							//	free(value);
								//free(line);
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
	//					printf("free 2");
						free(opcode);
						if (!value)
							free(value);
						line = NULL;
					}
					free_stack(&stack);
					exit(EXIT_FAILURE);
				}
//				printf("when am i here line number is line %d\n",line_number);
				line_number++;
				//line++;
			}//if opcode
	//		printf("checking when i get out of if opcode my line is %d\n",line_number);
		}//else
	}//while
//	printf("im out of while loop my line is %d\n and line is : %s\n", line_number, line);
	free_stack(&stack);
//	  printf("after free_stack im out of while loop my line is %d\n and line is : %s\n", line_number, line);
	if (line != NULL)
        {
		free(value);
		free(opcode);
          // printf("free 1");
//         	free(line);
           line = NULL;
        }
}
