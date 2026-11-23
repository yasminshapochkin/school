/*3)*/
#define STACK_SIZE 2000
#define ITER 10
void print(int i , int tick);

void lab02(){
	taskSpawn("task1",120,0x100,STACK_SIZE,print,1,20,0,0,0,0,0,0,0,0);
	taskSpawn("task2",120,0x100,STACK_SIZE,print,2,40,0,0,0,0,0,0,0,0);

}

void print(int i , int tick){
	int j;
	for(j= 0 ; j < ITER ; j++){
		printf("Hello - I am task%d %d\n" ,i , taskIdSelf());
		taskDelay(tick);

	}

}
