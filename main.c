#include "monty.h"

/*
 * main - open a file to read
 * @argc: program name
 * @argv: filename is first argument
 *
 * Return: exit 1 success
 */
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	FILE *file = fopen(argv[1], "r");

	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}
	read_bytecode_file(file);
	fclose(file);
	return (EXIT_SUCCESS);
}

