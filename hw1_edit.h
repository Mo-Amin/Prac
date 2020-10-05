#include<stdio.h>
#include<string.h>
#include"hw1given.h"

struct Location{
	int row, col;
};

//Read the board from the file. PlinkoBoard and struct are passed by reference because
//we want to allocate the correct board, and rows/columns within the board
int readInFromFile(char *** PlinkoBoard, struct Location * original, char FileName[])
{
	FILE * pfile;
	
	int i,n;
	//Make the pfile ptr point to the designated file and set the read mode
	pfile = fopen(FileName, "r");
	//If pfile is not NULL then we have sucessfully opened the file
	if(pfile != NULL)
	{
		//Read the first two numbers which tell us the amount of columns & rows in the board
		fscanf(pfile,"%d,%d",&original->row,&original->col);

		//Assign a ptr to the 2-D array and allocate the columns first(Techincally rows)
		*PlinkoBoard = (char **)malloc(sizeof(char*)*original->col);
		//Go through each column you allocate and allocate the # of rows
		for(i = 0;i<original->col;i++)
			(*PlinkoBoard)[i] = (char *)malloc(sizeof(char)*original->row);

		//Now go through each column
		for(i = 0;i<original->col;++i)
		{
			//And go through the row and allocate into each index
			for(n = 0;n<original->row;++n)
				fscanf(pfile," %c",&((*PlinkoBoard)[i][n]));
		}
		//Close the file
		fclose(pfile);
		//Opened correctly
		return 1;
	}
	else
		printf("File cannot be opened!!\n");
	return 0;
}
//This function allows us to randomize and find where we will start
//and drop the disk.
int StartingColumn(int row)
{
	//We know that the first index and the last index will always be blocked
	//so we randomize between the second index and the second to last index. 
	return GetRandom(1,row-2);
}
//In this function we go through the array the holds how many times we have gone
//through each slot and prints out each slot and its probablity
void MonteCarloSimulation(int slotCount[], int slots, int simulations)
{
	int i;
	//So the # of slots is equivalent to the rows, so
	//go through the array
	for(i = 0;i<slots;++i)
		//Print the slot # and divide the number of times the slot appeared
		//by the total number of simulations/iterations.
                printf("Slot %d (%d) = %.3f\n",i,slotCount[i],(float)slotCount[i]/simulations);

}
//This is the traversal function where we traverse throughout the board
//and keep track of the end slot.
void Traverse(int num, const struct Location * original, char ** PlinkoBoard)
{
	int i = 0;
	//Where the disk is located within the board. The specific slot it's located
	struct Location slot;
	//Keeps track of how many times we ended at specific slot
	int * MonteCarlo;
	MonteCarlo = (int *)malloc(sizeof(int) * original->row);
	//Initialize array
	for(i = 0;i<original->row;++i)
		MonteCarlo[i] = 0;

	int temp = 0;
	//Go through amount of iterations specified
	for(i=0;i<num;++i)
        {
		//Find the random starting location
		slot.row = StartingColumn(original->row);
		//Always start at 0 place(Techincally this is row 0)
		slot.col = 0;

		//Prints the path of the disk
		//printf("Array[%d][%d]\n",slot.col,slot.row);

		++slot.col;
		//Go through entire board. If we surpassed the board get out of loop
		while(slot.col < original->col)
		{
			//If there is a peg then enter
			if(PlinkoBoard[slot.col][slot.row] == 'X')
			{
				//First column we will always go right
				if(slot.row == 0)
					slot.row = 1;
				//Last column we will go left
				else if(slot.row == original->row-1)
					slot.row = original->row-2;
				//Any other case
				else
				{
					//Randomize whether we go left or right
					temp = GetRandom(slot.row-1,slot.row+1);
					//Make sure the Getrandom function gives us another location
					while(temp == slot.row)
						temp = GetRandom(slot.row-1,slot.row+1);
					//If the side we went to has a peg then enter
					if(PlinkoBoard[slot.col][temp] == 'X')
					{
						//Can't go left then go back right
						if(temp == slot.row-1)
							++slot.row;
						//Can't go right so go left
						else
							--slot.row;
					}
					//Location Valid. Update it
					else
						slot.row = temp;
				}
			}
			//Path of disk
			//printf("Array[%d][%d]\n",slot.col,slot.row);

			//Increment the slot we went out of
			if(slot.col == original->col-1)
				++MonteCarlo[slot.row];
			//Keep going down the board.
			++slot.col;
		}
        }
	//Print the Monte Carlo simulation
	MonteCarloSimulation(MonteCarlo,original->row, num);
	free(MonteCarlo);
}
