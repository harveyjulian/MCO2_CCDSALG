#include <stdio.h>
#include <string.h>

void separator1()
{
	printf("*************************************** \n");
}

void menuTab()
{
	printf("RAT SIMULATOR \n");
	printf("\n");
	printf("[1] Start Simulator \n");
	printf("[2] Load File \n");
	printf("[3] Quit \n");
	printf("\n");
}

int main()
{
	int opt = 0;
	
	separator1();
	menuTab();
	
	separator1();
	
	printf(">> ");
	scanf("%d", &opt);
	
	while(opt != 1 && opt != 2 && opt != 3)
	{
		printf("Invalid input! Press Enter to try again... \n");
		while(getchar() != '\n');
        getchar();
        opt = 0; 
        
        separator1();
        printf(">> ");
		scanf("%d", &opt);
	}

		if(opt == 1)
		{
			printf("test 1");
		}
		else if(opt == 2)
		{
			printf("test 2");
		}
		else if(opt == 3)
		{
			printf("\n");
			printf("Leaving simulator. Thank you!");
		}
	
}
