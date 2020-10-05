//Mohamed-Amin Cheaito
//1/22/20
//HW1

#include<stdio.h>
#include<string.h>
#include"hw1given.h"
#include"hw1_edit.h"

int main(int argc,char * argv[])
{
	//Make sure what was entered in command line was appropriate
	if(argc >= 3)
	{
		char ** PlinkoBoard;
		//Holds the actual row/cols for the board
		struct Location original;
		
		int i,n;
		//Initialize random # generator
		InitRandom();
		//If we read from a file enter
		if(readInFromFile(&PlinkoBoard, &original, argv[1]))
		{
			printf("\n");

			printf("Columns: %d | Rows: %d\n",original.row,original.col);
			printf("\n");
			//Print the board
			for(i = 0;i<original.col;++i)
			{
				for(n = 0;n<original.row;++n)
					printf("%c",PlinkoBoard[i][n]);
				printf("\n");
			}
			printf("\n");
			
			//Traverse the Board however many times it was specified within
			//command line
			Traverse(atoi(argv[2]),&original,PlinkoBoard);

			//Free dynamic memory
			for(i = 0;i<original.col;++i)
				free(PlinkoBoard[i]);

			free(PlinkoBoard);

		}
	}
	//File not opened properly
	else
		printf("Command line not appropriate!!!\n");

	return 0;
}
