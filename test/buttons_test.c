#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

void delay(long time)

{ 

	long tmp = 5000; 

	while( time-- ) 

	{ 

		while(tmp--); 

		tmp = 5000; 

	} 

}

int main(void)
{
	int buttons_fd,leds_fd;
	char buttons[2] = {'0', '0'};
	char first_flag = 0;
	int loop = 11;
	int totalScore = 100;
	int random,rand_tmp;


	buttons_fd = open("/dev/dial_key", 0);
	leds_fd = open("/dev/led1", 0);
	if (buttons_fd < 0) {
		perror("open device buttons failed£¡");
		exit(1);
	}
	if (leds_fd < 0){
		perror("open device led failed!");
		exit(1);
	}

	//Shutdown LED
	ioctl(leds_fd,0,0);
	ioctl(leds_fd,0,1);
	ioctl(leds_fd,0,2);
	ioctl(leds_fd,0,3);

	for (;loop !=0;loop --) 
	{		
		int i;
		char current_buttons[2];
		char realchar;


		//Shutdown LED
		ioctl(leds_fd,0,0);
		ioctl(leds_fd,0,1);
		ioctl(leds_fd,0,2);
		ioctl(leds_fd,0,3);
		

		srand((unsigned)time(NULL));
		random = rand() % 16;
		rand_tmp = random;


		if(rand_tmp >= 8)
		{
			ioctl(leds_fd,1,3);
			rand_tmp -= 8;
		}
		if(rand_tmp >= 4)
		{
			ioctl(leds_fd,1,2);
			rand_tmp -= 4;
		}
		if(rand_tmp >= 2)
		{
			ioctl(leds_fd,1,1);
			rand_tmp -= 2;
		}
		if(rand_tmp >= 1)
			ioctl(leds_fd,1,0);
		if(loop != 11)
		{printf("please input %d \n",random);}		
			
		if (read(buttons_fd, current_buttons, sizeof current_buttons) != sizeof current_buttons) 
		{
			perror("read buttons:");
			exit(1);
		}

		if(loop == 11)
			continue;

		if((char)current_buttons[0] == 'q')
		{
			printf("too slow -10\n");
			totalScore -= 10;
		}
		
		else
		{
			if (buttons[0] != current_buttons[0] || buttons[1] != current_buttons[1]) 
			{
				buttons[0] = current_buttons[0];
				buttons[1] = current_buttons[1];
				switch(buttons[0])
				{
				case 51:
					switch(buttons[1])
					{
						case 51:realchar='1';rand_tmp=1;break;
						case 50:realchar='2';rand_tmp=2;break;
						case 49:realchar='3';rand_tmp=3;break;
						case 48:realchar='A';rand_tmp=10;break;
					}break;
				case 50:
					switch(buttons[1])
					{
						case 51:realchar='4';rand_tmp=4;break;
						case 50:realchar='5';rand_tmp=5;break;
						case 49:realchar='6';rand_tmp=6;break;
						case 48:realchar='B';rand_tmp=11;break;
					}break;
				case 49:
					switch(buttons[1])
					{
						case 51:realchar='7';rand_tmp=7;break;
						case 50:realchar='8';rand_tmp=8;break;
						case 49:realchar='9';rand_tmp=9;break;
						case 48:realchar='C';rand_tmp=12;break;
					}break;
				case 48:
					switch(buttons[1])
					{
						case 51:realchar='*';rand_tmp=14;break;
						case 50:realchar='0';rand_tmp=0;break;
						case 49:realchar='#';rand_tmp=15;break;
						case 48:realchar='D';rand_tmp=13;break;
					}break;
				}
				//printf("key(%c) is pressed!\n", realchar);
				//Judge whether they are equivalents
				if(random == rand_tmp)
					printf("correct!!\n");
				else
				{printf("wrong!! -10 \n"); totalScore -= 10;}

			}
		}
		
	}
	printf("your score is %d",totalScore);
	close(buttons_fd);
	return 0;
}
