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
		char cwd[1024]=".";
		//getcwd(cwd, sizeof(cwd));	
		printf("ptr 값 : %s\n", ptr);

		//해당 이름과 권한을 가진 디렉토리 생성 후, 그 위치로 이동
		mode = umask(0022);
		mkdir(ptr, 0777);
		//strcat(cwd, "/");
		//strcat(cwd, ptr);
		printf("cwd : %s\n", cwd);
		switch( chdir(ptr) )
		{
			case 0:
				printf("이동 성공\n");
				break;
			case -1:
				printf("이동 실패\n");
				break;
		}
		//현재 위치 표시
		//getcwd(cwd, sizeof(cwd));
		//printf("cwd 값 : %s\n", cwd);

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
	int make_fd = open(argv[2], O_CREAT, mode);
	close(make_fd);
	
	//파일까지만 형성할시에 종료시키는 부분
	if(argc == 3)
		return 0;

	//파일에 쓰일 내용까지 쓰였을 때, 진행되는 부분.
	int write_fd;
	int size_text = strlen(argv[3]);
	int size_filename = strlen(argv[2]);
	int size_total = size_text + size_filename + strlen(" > ");
	char order[size_total];
	strcat(order, argv[2]);
	strcat(order, " > ");
	strcat(order, argv[3]);
	printf("내용물 문자열 길이 : %d\n", size_text);
	printf("파일 이름 길이 : %d\n", size_filename);
	printf("배열 총 길이 : %d\n", size_total);
	printf("명렁 문자열 : %s\n", order);

	char *s1 = argv[2];
	char *s2 = malloc(sizeof(char) * (strlen(argv[2])+strlen(argv[3])+4));
	strcpy(s2, argv[3]);
	strcat(s2, s1);
	printf("%s\n", s2);
	free(s2);

	int ret = system(order);

	return 0;
}
