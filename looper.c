#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    if (argc != 4) 
	{
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) 
	{
        return EXIT_FAILURE;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) 
	{
        putchar(ch);
    }

    fclose(file);

    if (atoi(argv[3]) == 0) 
	{
        while (1) 
		{
            file = fopen(argv[1], "r");
            if (file == NULL) 
			{
                return EXIT_FAILURE;
            }
            while ((ch = fgetc(file)) != EOF) 
			{
                putchar(ch);;
            }
            fclose(file);
        }
    } 
	else if (atoi(argv[3]) > 0) 
	{
        size_t count = atoi(argv[3]);
        while (count > 0) 
		{
            file = fopen(argv[2], "r");
            if (file == NULL) 
			{
                return EXIT_FAILURE;
            }
            while ((ch = fgetc(file)) != EOF) 
			{
                putchar(ch);
            }
            fclose(file);
			count--;
        }
    }

    return EXIT_SUCCESS;
}
