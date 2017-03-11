
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int dig_the_ground(int**,int);
int fill_the_water(int**,int,int,int); //for if top,down,left,right are have water
void fill_the_water_2(int**,int,int,int);//for if cell is became a "2".water will look neighbor cell which is "1"
int mean(double,double,double*);
void writer(double, double);
int standartdev(double*,double,double);
void writer_board(int**,int);

int main(int argc, char *argv[]){

	srand(time(NULL));

	int length=atoi(argv[1]); //first argument it gives us size of ground
	double T=atoi(argv[2]);   //second argument is T how many times the program will work

	int **board;	// I called board to ground because i took like a table the ground. ( like in the reverse game i explained in my design report. )
	int i,j,k,z,t;		//Used for loops.
	int row;		//array's first
	int coloumn;	//and second items used in functions.
	double open_cells;
	double o_divide_t=0;
	double x=0; //i just called x doesnt mean anything

	double *stddev_array; // to hold our open cells
	stddev_array=(double*)malloc(T*sizeof(double));

	for(k=0;k<T;k++){

		board=(int **)calloc(length,sizeof(int));	//take memory for rows.
		for(i=-1;i<=length;i++){
			board[i]=(int*)calloc(length,sizeof(int));   //take memory for coloumn for each row.
		}

		dig_the_ground(board,length);
		open_cells=0;

		for(i=0;i<length;i++){					//to count how many
			for(j=0;j<length;j++){				//how many open cell
				if(board[i][j]==1||board[i][j]==2){
					open_cells++;
				}
			}
		}

		x=open_cells/(length*length); // how many open cell divided all board in one iterative
		stddev_array[k]=x;
		o_divide_t+=x;


		if(k==T-1){
			writer_board(board,length);
		}
		for(z=0;z<length;z++){
			for(t=0;t<length;t++){
				board[z][t]=0;
			}
		}
		
		
	}
	mean(o_divide_t,T,stddev_array); //for average all program.
	
	return 0;
}

int dig_the_ground(int *board[],int length){  // for open the cells
	int i,j;
	int a;// for two function .they are related and this is key
	int number_row,number_coloumn;

	while(1){

		number_row=rand()%length;
		number_coloumn=rand()%length;
		for(i=0;i<length;i++){				//this for loop and
			if(board[length-1][i]==2){ 		//if are for end one time the program.
				return 0;
			}
		}

		if(board[number_row][number_coloumn]==0){
			board[number_row][number_coloumn]=1;
		}else{
			continue;
		}
		if(board[number_row][number_coloumn]==1){
			a=fill_the_water(board,length,number_row,number_coloumn); //for if top,down,left,right are have water
				if(a==2){
					fill_the_water_2(board,length,number_row,number_coloumn);//for if cell is became a "2".water will look neighbor cell which is "1"
				}
		}
	}
}
int fill_the_water(int *board[], int length, int number_row, int number_coloumn){ // i made recursive function , i cannot find iterative solution

	if(number_row==0){
		board[number_row][number_coloumn]=2;

	}
	if(board[number_row][number_coloumn]==1&&board[number_row-1][number_coloumn]==2){ //looking for up

		board[number_row][number_coloumn]=2;
		return 2;
	}
	if(board[number_row][number_coloumn]==1&&board[number_row][number_coloumn+1]==2){ //looking for right

		board[number_row][number_coloumn]=2;
		return 2;
	}
	if(board[number_row][number_coloumn]==1&&board[number_row][number_coloumn-1]==2){ //looking for left

		board[number_row][number_coloumn]=2;
		return 2;
	}
	if(board[number_row][number_coloumn]==1&&board[number_row+1][number_coloumn]==2){ //looking for down

		board[number_row][number_coloumn]=2;
		return 2;
	}

}
void fill_the_water_2(int *board[], int length, int number_row, int number_coloumn){ // same as fill_the_water

	if(board[number_row][number_coloumn]==2){
		if(board[number_row-1][number_coloumn]==1){ //looking up
			board[number_row-1][number_coloumn]=2;
			fill_the_water_2(board,length,number_row-1,number_coloumn);
		}
		if(board[number_row][number_coloumn+1]==1){ //looking for right
			board[number_row][number_coloumn+1]=2;
			fill_the_water_2(board,length,number_row,number_coloumn+1);
		}
		if(board[number_row][number_coloumn-1]==1){ //looking for left
			board[number_row][number_coloumn-1]=2;
			fill_the_water_2(board,length,number_row,number_coloumn-1);
		}
		if(board[number_row+1][number_coloumn]==1){ //looking for down
			board[number_row+1][number_coloumn]=2;
			fill_the_water_2(board,length,number_row+1,number_coloumn);
		}
	}
}
int mean(double o_divide_t,double T,double *stddev_array){ //calculate mean o_divide_t and T.
	double mean;
	mean=o_divide_t/T;

	standartdev(stddev_array,mean,T);
}

int standartdev(double *stddev_array,double mean,double T){
	double stddev=1.0;
	int k,p;
	double total_of_substractions=0;
	double square_of_std=0;
	//for squre root

	for(k=0;k<T;k++){    //x-average's square
		total_of_substractions+=(stddev_array[k]-mean)*(stddev_array[k]-mean);

	}
	square_of_std=total_of_substractions/(T-1); //square of standartdev
	for(p=0;p<20;p++){							// square root of standartdev
		stddev=(stddev+square_of_std/stddev)/2;
	}

	writer(mean,stddev);

}

void writer_board(int *board[],int length){//writer
	FILE* outputz;
	outputz=fopen("output.txt","w");
	int i,j;
	for(i=0;i<length;i++){
		for(j=0;j<length;j++){
			fprintf(outputz," %d",board[i][j]);
		}
		fprintf(outputz," \n");
	}
	fprintf(outputz," \n");
	fclose(outputz);
}
void writer(double mean, double stddev){// for write
	FILE* outputz;
	outputz=fopen("output.txt","a");
	fprintf(outputz,"mean()   = %lf \n", mean);
	fprintf(outputz,"stddev() = %lf \n", stddev);
	fclose(outputz);
}
