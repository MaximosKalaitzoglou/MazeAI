#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 8
#define p 0.7
#define QUEUE_SIZE 30000000

void printSolution(int solution[N][N],int flag);

int maze[N][N]; /*= {{1, 1, 1, 1, 1},
				  {1, 1, 0, 1, 1},
				  {1, 1, 0, 1, 1},
				  {0, 0, 1, 1, 1},
				  {1, 0, 0, 1, 1}};
				  */

int visited[N][N] = {{0}};
int Head =-1;
int Tail = -1;
int size = 0;
int pos = 1;
int movement_cost = 0;
int Hn1 = 0;
int Hn2 = 0;



struct Node
{
	int x, y;
	int previousx;
	int previousy;
	int min_dist;

}NODE;

int a_search(struct Node start, int gx, int gy,int flag);

struct Node queue[QUEUE_SIZE];
struct Node queue2[QUEUE_SIZE];

void printMaze(int maze[N][N]){
	int x,y;
	for ( x = 0; x < N; x++){
		for(y = 0; y < N; y++){
			printf("%d\t",maze[x][y]);
		}
		printf("\n");
	}
}




void enqueue(struct Node queue[QUEUE_SIZE],struct Node value) //Enqueues the given request to the queue
{
	if (size < QUEUE_SIZE)
	{
		if (size == 0)
		{
			queue[0].x = value.x;
			queue[0].y = value.y;
			queue[0].previousx = value.previousx;
			queue[0].previousy = value.previousy;
			queue[0].min_dist = value.min_dist;
			
			Head = Tail = 0;
			size = 1;

		}
		else if (Tail == QUEUE_SIZE - 1)
		{
			queue[0].x = value.x;
			queue[0].y = value.y;
			queue[0].previousx = value.previousx;
			queue[0].previousy = value.previousy;
			queue[0].min_dist = value.min_dist;
			size++;

		}
		else
		{
			queue[Tail + 1].x = value.x;
			queue[Tail + 1].y = value.y;
			queue[Tail + 1].previousx = value.previousx;
			queue[Tail + 1].previousy = value.previousy;
			queue[Tail + 1].min_dist = value.min_dist;

			Tail++;
			size++;
	
		}
	}
	else
	{
		printf("Queue is full\n");
	}
}

struct Node dequeue(struct Node q[QUEUE_SIZE]) //Dequeues a request from the queue
{
	struct Node tmp;
	if (size == 0)
	{
		return tmp;
		
	}
	else
	{
		tmp.x = q[Head].x;
		tmp.y = q[Head].y;
		tmp.previousx = q[Head].previousx;
		tmp.previousy = q[Head].previousy;
		tmp.min_dist = q[Head].min_dist;
		
		size--;
		Head++;
		if (Head == QUEUE_SIZE)
			Head = 0;
	}
	return tmp;
}


int row[] = {-1, 0, 0, 1,1,-1,1,-1};
int col[] = {0, -1, 1, 0,1,-1,-1,1};


int isValid(int mat[N][N], int visited[N][N], int row, int col)
{
	if((row >= 0) && (row < N) && (col >= 0) && (col < N) && (mat[row][col] == 1) && visited[row][col] == 0){
		return 0;
	}
	return 1;
}

void empty_queue(struct Node queue[QUEUE_SIZE]){
	while(size != 0){
		struct Node tmp = dequeue(queue);
	}
}

void empty_queue2(){
	while(pos != 1){
		struct Node tmp = dequeue(queue2);
		pos--;
	}
}

void empty_visited(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			visited[i][j] = 0;
		}
	}
}

void queue_sort(struct Node queue[QUEUE_SIZE],struct Node G1)
{


	for (int i = Head; i < Tail; i++) //Loop for ascending ordering
	{
		for (int j = Head; j < Tail; j++) //Loop for comparing other values
		{
			int k = a_search(queue[j], G1.x, G1.y,0);
			int o = a_search(queue[j + 1], G1.x, G1.y,1);
			
			if(k > o ) //Comparing other array elements
			{

				
				struct Node tmp = queue[j]; //Using temporary variable for storing last value
				queue[j] = queue[j + 1];	//replacing value
				queue[j + 1] = tmp;			//storing last value
			}
			Hn1 = 0;
			Hn2 = 0;
		}
	}
}

void found(struct Node tmp, struct Node src)
{
	int i;

	for (i = 0; i < pos; i++)
	{
		if (tmp.x == src.x && tmp.y == src.y)
		{
			//exit(0);
			return;
		}
		if ((tmp.previousx == queue2[i].x) && (tmp.previousy == queue2[i].y))
		{

			printf(" <-- %d.%d", queue2[i].x, queue2[i].y);

			tmp.x = queue2[i].x;
			tmp.y = queue2[i].y;
			tmp.previousx = queue2[i].previousx;
			tmp.previousy = queue2[i].previousy;

			//printf("x = %d and y = %d\n", tmp.previousx, tmp.previousy);
			found(tmp, src);
		}
	}
}
int a_search(struct Node start, int gx, int gy,int flag)
{
	

	if (start.x == gx && start.y == gy)
	{
		if(flag == 0){
			return Hn1;
		}else{
			return Hn2;
		}
		
	}

	if(flag == 0){
		Hn1++;
	}else{
		Hn2++;
	}	
	
	if (start.x < gx && start.y == gy)
	{
				
		start.x += 1;
		a_search(start, gx, gy,flag);
		
	}
	else if (start.x < gx && start.y < gy)
	{
		
		start.x += 1;
		start.y += 1;

		a_search(start, gx, gy, flag);
	}
	else if (start.x < gx && start.y > gy)
	{

		
		start.x += 1;
		start.y -= 1;

		a_search(start, gx, gy, flag);
	}
	else if (start.x > gx && start.y == gy)
	{
	
	
		start.x -= 1;

		a_search(start, gx, gy, flag);
	}
	else if (start.x > gx && start.y > gy)
	{
		start.x -= 1;
		start.y -= 1;
		a_search(start, gx, gy, flag);
	}
	else if (start.x == gx && start.y > gy)
	{
		start.y -= 1;
		a_search(start, gx, gy, flag);
	}
	else if (start.x == gx && start.y < gy)
	{
		
		start.y += 1;
		a_search(start, gx, gy, flag);
	}
	else if (start.x > gx && start.y < gy)
	{

		
		start.x -= 1;
		start.y += 1;
		a_search(start, gx, gy, flag);
	}

}

void UCS(struct Node src,struct Node dest1,struct Node dest2,int yog)
{
	int posx,posy;

	enqueue(queue,src);
	queue2[0].x = src.x;
	queue2[0].y = src.y;
	queue2[0].min_dist = src.min_dist;
	visited[src.x][src.y] = 1;
	while(size != 0){
		struct Node tmp;
		tmp = dequeue(queue);

		
		
		visited[tmp.x][tmp.y] = 1;
		if(tmp.x == dest1.x && tmp.y == dest1.y || tmp.x == dest2.x && tmp.y == dest2.y){
			printSolution(visited,tmp.min_dist);
			printf(" <-- %d.%d", tmp.x, tmp.y);
			found(tmp,src);		
			
			return;
			
		}
		
		int i;
		for(i = 0; i < 8; i ++){
			posx = tmp.x + row[i];
			posy = tmp.y + col[i];
			if (isValid(maze, visited, posx, posy) == 0)
			{
				struct Node Next;
				
				Next.x = posx;
				Next.y = posy;
				Next.previousx = tmp.x;
				Next.previousy = tmp.y;
				Next.min_dist = tmp.min_dist + 1;
				visited[posx][posy] = 1;
				movement_cost++;
				
				enqueue(queue,Next);
				queue2[pos].x = posx;
				queue2[pos].y = posy;
				queue2[pos].previousx = tmp.x;
				queue2[pos].previousy = tmp.y;
				pos++;

			}
		}
		if (yog == 1)
		{
			if (a_search(src, dest1.x, dest1.y, 0) > a_search(src, dest2.x, dest2.y, 1))
			{
				queue_sort(queue, dest2);
			}
			else
			{
				queue_sort(queue, dest1);
			}
		}
	}
	
	printf("can't find exit\n");		
}

void printSolution(int solution[N][N],int flag) { 
	int i,j;
    for (i = 0; i < N; i++) { 
        for (j = 0; j < N; j++) 
            printf(" %d ", solution[i][j]); 
        printf("\n"); 
    } 
	printf("minimum distance to goal  is : %d\n",flag);
	
}




int main(){
	struct Node S,G1,G2;
	int ap = -1;
	double num = -1;
	srand((double)time(NULL));
	int x,y;
	for(x = 0; x < N; x++){
		for(y = 0; y < N; y++){
			num = ((double)rand()/(double) RAND_MAX);

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
		scanf("%d %d %d %d %d %d", &S.x,&S.y,&G1.x,&G1.y,&G2.x,&G2.y);

	}while (isValid(maze, visited, S.x, S.y) == 1 || isValid(maze, visited, G1.x, G1.y) == 1 || isValid(maze, visited, G2.x, G2.y) == 1);

	S.min_dist = 0;
	UCS(S,G1,G2,0);
	printf("\nmovement cost is : %d\n",movement_cost);
	empty_queue(queue);
	empty_queue2(queue2);
	empty_visited();
	movement_cost = 0;
	UCS(S,G1,G2,1);
	printf("\nmovement cost of A* is : %d\n", movement_cost);

	return 0;

}

