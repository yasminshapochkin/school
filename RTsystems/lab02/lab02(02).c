/*PART 2
2)
*/
#define STACK_SIZE 2000
#define CLOCK_TICK 20
#define ITER 10
void print(int i);


void lab02(){
	taskSpawn("task1",120,0x100,STACK_SIZE,print,1,0,0,0,0,0,0,0,0,0);
	taskSpawn("task2",120,0x100,STACK_SIZE,print,2,0,0,0,0,0,0,0,0,0);

}

void print(int i){
	int j;
	for(j = 0 ; j < ITER ; j++){
		printf("Hello - I am task%d %d\n" ,i , taskIdSelf());
		taskDelay(CLOCK_TICK);

	}

}
