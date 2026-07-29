#include <stdio.h>
#include <string.h>

int main()
{
	int opt = 0;
	
	printf("RAT SIMULATOR \n");
	printf("\n");
	printf("[1] Start Simulator \n");
	printf("[2] Load File \n");
	printf("[3] Quit \n");
	printf("\n");
	
	scanf(">> %d", &opt);
	
	if(opt != 1 || opt != 2 || opt != 3)
	{
		printf("Invalid input! Press Enter to try again...");
		while(getchar() != '\n');
        getchar();
        option = 0; 
	}
	else
	{
		if(opt == 1)
		{
			printf("1");
		}
		else if(opt == 2)
		{
			printf("2");
		}
		else if(opt == 3)
		{
			printf("3");
		}
		
	}
	
	
}