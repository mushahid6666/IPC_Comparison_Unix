#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <semaphore.h>
#include "mythreads.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>

#include <sys/wait.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include "measure_time.h"
#include <time.h>
#include <stdint.h>

void *addr;
size_t length;

int main(int argc, char*argv[])
{
  int err;
  if (argc!=3)
    {
      printf("Usage: %s <length of buffer> <eval_type>", argv[0]);
      return 0;
    }
  sem_t *sem_empty;
  sem_t *sem_full;

  uint64_t begin, end;
  struct timespec begints, endts;
  //sem_init(&mutex, 0, 1);
  int i=0;
  length = atoi(argv[1]);
  //  int time = argv[2];
  int eval = atoi(argv[2]);

  //  printf("length = %d\n",length);
  //int fd = open("test.txt",O_RDWR);
  int fd = shm_open("shmname", O_CREAT, O_RDWR);
  addr = mmap(NULL,length*2,PROT_READ|PROT_WRITE,MAP_SHARED| MAP_ANONYMOUS, fd,0);

  //sem_empty = mmap(NULL,sizeof(sem_t),PROT_READ|PROT_WRITE,MAP_SHARED| MAP_ANONYMOUS, -1,0);
  int fd1 = shm_open("shmname1", O_CREAT, O_RDWR);
  ftruncate(fd1, sizeof(sem_t));
  sem_full = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
		  MAP_SHARED| MAP_ANONYMOUS, fd1, 0);

  int fd2 = shm_open("shmname2", O_CREAT, O_RDWR);
  ftruncate(fd2, sizeof(sem_t));
  sem_empty = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
		   MAP_SHARED | MAP_ANONYMOUS, fd2, 0);

  sem_init(sem_empty, 1, 1);
  sem_init(sem_full, 1, 0);


  //sem_unlink ("full");
  //sem_unlink ("empty");


  int cpid=fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  char c;
  char *tmp = (char*)addr;
  if (cpid == 0) {

    SetAffinity(2);
    int count = 1;
    while(count--){
    sem_wait(sem_full);
     i=0;
    while(i!=length)
      {
		c = *(tmp+i);
		// printf("%c\n",*(tmp+i));
			i++;
      }
    while(i!=length*2)
      {
		*(tmp+i)= '1';
		i++;
      }
    sem_post(sem_empty);}
    _exit(EXIT_SUCCESS);

  } else {
			SetAffinity(3);
			if (eval)
			{
				int count = 1;
				begin = RDTSCP();
				while(count--){
					i=0;
				sem_wait(sem_empty);
				while(i!=length)
				  {
					*(tmp+i)='0';
					i++;
				  }
				sem_post(sem_full);
				sem_wait(sem_empty);
				while(i!=length*2)
				  {
					 //printf("%c\n",*(tmp+i));
					c = *(tmp+i);
					i++;
				  }
				sem_post(sem_full);
				}
				end = RDTSCP();

				double time = ((double)(end-begin))/((double)FREQ);
				printf("RDTSCP: %f\n",time);
			  }
			else
			{
				sem_wait(sem_empty);
				clock_gettime(CLOCK_MONOTONIC, &begints);
				while(i!=length)
				  {
					*(tmp+i)='0';
					i++;
				  }
				sem_post(sem_full);
				sem_wait(sem_empty);
				while(i!=length*2)
				  {
					 //printf("%c\n",*(tmp+i));
					c = *(tmp+i);
					i++;
				  }
				clock_gettime(CLOCK_MONOTONIC, &endts);
				struct timespec tmpts = TimeSpecDiff(&endts, &begints);
				uint64_t nsecElapsed = tmpts.tv_sec * 1000000000LL + tmpts.tv_nsec;
				sem_post(sem_full);
				printf("clockgettime: %lld\n",nsecElapsed);
			  }
			//		munmap(addr,length);
    _exit(EXIT_SUCCESS);
  }
}
