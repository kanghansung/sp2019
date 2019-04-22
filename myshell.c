#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	printf("argc : %d\n", argc);
        for(int i=0;i<argc;i++)
        {
                printf("argv[%d] : %s\n",i,  argv[i]);
        }
	//폴더와 파일을 만들시 권한
	mode_t mode;
	//최소한 폴더 형성까지는 해야함.	
	if(argc < 2)
	{
		perror("Don't right number of arguments.\n");
		exit(1);
	}
	char *ptr = strtok(argv[1], "/");
	while(ptr != NULL)
	{
		//현재 위치와 만들값 확인용
		char cwd[1024];
		getcwd(cwd, sizeof(cwd));	
		printf("ptr 값 : %s\n", ptr);

		//해당 이름과 권한을 가진 디렉토리 생성 후, 그 위치로 이동
		mode = umask(0122);
		mkdir(ptr, 0777);
		strcat(cwd, "/");
		strcat(cwd, ptr);
		chdir(cwd);
		//현재 위치 표시
		getcwd(cwd, sizeof(cwd));
		printf("cwd 값 : %s\n", cwd);

		//만들 디렉토리 이름 바꾸기
		ptr = strtok(NULL, "/");
	}
	umask(mode);
	//매개변수가 2개까지 들어오면 폴더 생성까지니, 종료시킴.
	if(argc == 2)
		return 0;
	//매개변수가 3개라면 원하는 폴더 안에 파일까지 생성시킴.
	//파일 형성 부분	
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	open(argv[2], O_CREAT, mode);
	
	if(argc == 3)
		return 0;
		

	return 0;
}



