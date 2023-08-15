#include "monty.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
    
	fprintf(stderr, "Usage: monty file");
    //	fprintf(stderr, "Usage: %s <bytecode_file>\n", argv[0]);
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

