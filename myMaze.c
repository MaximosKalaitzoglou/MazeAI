#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#define N 15
#define p 0.5

int G2[2];
int flag = 0;
int isValid(int mat[N][N], int visited[N][N], int row, int col);

void printSolution(int solution[N][N]);
/*int maze[N][N] = {{0,1,1,1},
				  {1,0,0,0},
				  {1,1,0,1},
				  {1,0,1,1}};
*/
int maze[N][N];
int visited[N][N] = {{0}};
int solution[N][N] = {{0}};
int min_dist = 0;
void display();


typedef struct Node
{
    // (x, y) represents matrix cell coordinates
    // dist represent its minimum distance from the source
    int x, y;
	int i,j;
}NODE;

NODE previous;
void printMaze(int maze[N][N]){
	int x,y;
	for (int x = 0; x < N; x++){
		for(int y = 0; y < N; y++){
			printf("%d\t",maze[x][y]);

		}
		printf("\n");
	}
}

int isValid(int mat[N][N], int visited[N][N], int row, int col)
{
	if((row >= 0) && (row < N) && (col >= 0) && (col < N) && (mat[row][col] == 1) && (visited[row][col] == 0)){
		return 0;
	}
	return 1;
}




void try_path_left(NODE start,int gx,int gy){

	if(start.x == gx && start.y == gy){
		flag++;
		if(flag == 2){
			//printSolution(visited);
			exit(0);
		}
		printSolution(visited);
 		start.x	= previous.x;
		start.y = previous.y;
		min_dist = 0;
		try_path_left(start,G2[0],G2[1]);
		
	}

	min_dist++;
	

	if(start.x < gx && start.y == gy){
		if(isValid(maze,visited,start.x + 1,start.y) == 0){
			start.x += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start,gx,gy);
		}
		if(isValid(maze,visited,start.x + 1,start.y + 1) == 0){
			start.x += 1;
			start.y += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start,gx,gy);
		}
		if(isValid(maze,visited,start.x + 1,start.y - 1) == 0){
			start.x += 1;
			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start,gx,gy);
		}
		min_dist--;
		
		try_path_left(previous,gx,gy);
		
	}else if (start.x < gx && start.y < gy){
		if (isValid(maze, visited, start.x + 1, start.y + 1) == 0)
		{
			start.x += 1;
			start.y += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}

		if (isValid(maze, visited, start.x + 1, start.y) == 0)
		{
			start.x += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x, start.y + 1) == 0)
		{
			start.y += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x + 1, start.y - 1) == 0)
		{
			start.x += 1;
			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x - 1, start.y - 1) == 0)
		{
			start.x -= 1;
			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x, start.y - 1) == 0)
		{
			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}

		min_dist = 0;
	
		try_path_left(previous, gx, gy);

	}else if(start.x < gx && start.y > gy){

		if (isValid(maze, visited, start.x + 1, start.y - 1) == 0)
		{
			start.x += 1;
			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}

		if (isValid(maze, visited, start.x + 1, start.y ) == 0)
		{
			start.x += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}

		if (isValid(maze, visited, start.x, start.y - 1) == 0)
		{
			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x + 1, start.y + 1) == 0)
		{
			start.x += 1;
			start.y += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}

		min_dist = 0;

		try_path_left(previous, gx, gy);

	}else if(start.x > gx && start.y == gy){
		if (isValid(maze, visited, start.x - 1, start.y) == 0)
		{
			start.x -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x - 1, start.y + 1) == 0)
		{
			start.x -= 1;
			start.y += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x - 1, start.y - 1) == 0)
		{
			start.x -= 1;
			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x, start.y - 1) == 0)
		{

			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x, start.y + 1) == 0)
		{

			start.y += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}

		min_dist = 0;
		try_path_left(previous, gx, gy);

	}else if(start.x > gx && start.y > gy){
		if (isValid(maze, visited, start.x - 1, start.y - 1) == 0)
		{
			start.x -= 1;
			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x - 1, start.y) == 0)
		{
			start.x -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x - 1, start.y + 1) == 0)
		{
			start.x -= 1;
			start.y += 1;

			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x, start.y - 1) == 0)
		{
			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x, start.y + 1) == 0)
		{
			start.y += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x + 1, start.y) == 0)
		{
			start.x += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		
		
		min_dist = 0;

		try_path_left(previous, gx, gy);
	}else if(start.x == gx && start.y > gy ){
		if (isValid(maze, visited, start.x, start.y - 1) == 0)
		{
			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}

		if (isValid(maze, visited, start.x + 1, start.y - 1) == 0)
		{
			start.x += 1;
			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x - 1, start.y - 1) == 0)
		{
			start.x -= 1;
			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x + 1, start.y - 1) == 0)
		{
			start.x += 1;
			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		min_dist = 0;

		try_path_left(previous, gx, gy);
	}else if (start.x == gx && start.y < gy){
		if (isValid(maze, visited, start.x, start.y + 1) == 0)
		{
			start.y += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);

		}
		if (isValid(maze, visited, start.x + 1, start.y + 1) == 0)
		{
			start.x += 1;
			start.y += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x - 1, start.y + 1) == 0)
		{
			start.x -= 1;
			start.y += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		min_dist = 0;

		try_path_left(previous, gx, gy);
	}else if(start.x > gx && start.y < gy){

		if (isValid(maze, visited, start.x - 1, start.y + 1) == 0)
		{
			start.x -= 1;
			start.y += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x, start.y + 1) == 0)
		{
			
			start.y += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x - 1, start.y) == 0)
		{

			start.x -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x - 1, start.y - 1) == 0)
		{
			start.y -= 1;
			start.x -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x, start.y - 1) == 0)
		{

			start.y -= 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		if (isValid(maze, visited, start.x + 1, start.y) == 0)
		{

			start.x += 1;
			visited[start.x][start.y] = 1;
			try_path_left(start, gx, gy);
		}
		min_dist = 0;

		try_path_left(previous, gx, gy);
	}
	
	return;

}



void printSolution(int solution[N][N]) 
{ 
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) 
            printf(" %d ", solution[i][j]); 
        printf("\n"); 
    }
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			solution[i][j] = 0;
	}
	printf("minimum distance is %d\n",min_dist);
}

int main(){
	int S[2],G1[2];
	int ap = -1;
	double num = -1;
	srand((double)time(NULL));

	
	for(int x = 0; x < N; x++){
		for(int y = 0; y < N; y++){
			num = ((double)rand()/(double) RAND_MAX);

			//printf("%f\n",num);
				if (num < p){
					ap = 1;
				}else{
					ap = 0;
				}
				maze[x][y] = ap;
		}
	}
	
	

	printMaze(maze);
	
	
	
	do{
	printf("Please give S (start), G1 (Goal 1) and G2 (Goal 2)\n");
	printf("Maze is of size %d\n",N);
	scanf("%d %d %d %d %d %d", &S[0],&S[1],&G1[0],&G1[1],&G2[0],&G2[1]);
		//printf("%d,%d\n%d,%d\n%d,%d\n", S[0],S[1],G1[0],G1[1],G2[0],G2[1]); Test for value 

	}while(isValid(maze,visited,S[0],S[1]) == 1 || isValid(maze,visited,G1[0],G1[1]) == 1 || isValid(maze,visited,G2[0],G2[1]) == 1);
	//int n = testValue(S,G1,G2);
	//printf("test value = %d\n",n);
	
	NODE tempest;
    tempest.x = S[0];
    tempest.y = S[1];
	previous.x = S[0];
	previous.y = S[1];
    //enqueue(tmp);
	visited[tempest.x][tempest.y] = 1;

	try_path_left(tempest, G1[0], G1[1]);
	//try_path_left(tempest, G2[0], G2[1]);

	return 0;

	//robot[0] = S[0];
	//robot[1] = S[1]; 
}