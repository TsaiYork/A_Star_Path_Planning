#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



#define COL 60
#define RAW 60
#define OLvalue 1000

void Processing(int nodex, int nodey, int goaly, int goalx);
void CompareOpen();
int CompareOpenY();

struct PATH_NODE
{
	char name;
	int open;
	int prex, prey;
	int h;
	int g;		//����
	int f;
};
struct PATH_NODE map[RAW][COL];			//map[Y][X]

int OpenList[OLvalue][2] = { NULL,NULL };					//OpenList[0]=Y,OpenList[1]=X
int openi = 0;
int count_openi;
int temp[2];					//�Ȯɦs��x y ��
int main()
{
	FILE *fptr;
	FILE *fptr2;

	int start_x, start_y, goal_x, goal_y;
	fptr = fopen("Map.txt", "r");
	fptr2 = fopen("Path.txt", "w");
	char ch;
	int arr_x = 0, arr_y = 0;
	int count_x = 0, count_y = 1;

	//Ū���a��
	if (fptr != NULL)
	{
		while (!feof(fptr))
		{

			map[arr_y][arr_x].name = getc(fptr);

			if (map[arr_y][arr_x].name != 10)
			{
				arr_x++;
				count_x++;
				//printf("%d",count_x);
			}
			else
			{
				//printf("[%d]",count_y);
				arr_y++;
				count_y++;
				count_x = 0; arr_x = 0;
			}
		}
		count_x = count_x - 1;		//col�b�p�Ʈɥ]�t�̫ᵲ���@��NULL�r���A�G�b�������A�}�C�]���ݭnmap[0][50]���ťզr���A�u�ݭn�Ψ�map[0][49]���}�C
									//printf("%c\n",map[0][49].name);
		printf("X=%d,Y=%d\n", count_x, count_y);		//����ܦ��X��X�C�A�G�H�ڭ̪��[���Ʀr�A��1�}�l�ơA�G�[1
		printf("�ɮ�Ū������\n");
		fclose(fptr);
	}
	else
	{
		printf("�ɮ׶}�ҥ���\n");
	}

	//�L�X�a�ϡA��_�I�A�w�q���
	for (int i = 0; i<count_y; i++)
	{
		for (int j = 0; j<count_x; j++)
		{
			printf("%c", map[i][j].name);
			map[i][j].open = 0;				//��open�ȳ]0�A���]�Ҧ��ȳ����Q�[�J�}��C��L
			if (map[i][j].name == 83)
			{
				start_y = i;
				start_x = j;
			}
			else if (map[i][j].name == 71)
			{
				goal_y = i;
				goal_x = j;
			}
		}
		printf("\n");
	}

	map[start_y][start_x].g = 0;
	printf("start(%d,%d),goal(%d,%d)\n", start_y, start_x, goal_y, goal_x);
	system("pause");
	OpenList[0][0] = start_y;
	OpenList[0][1] = start_x;
	openi = 1;
	count_openi = 1;
	Processing(start_y, start_x, goal_y, goal_x);

	int count_path = 0;
	while (map[goal_y][goal_x].open != -1)
	{
		printf("\n%d\t%d\t%d", count_path, temp[0], temp[1]);
		//int now_y,now_x;
		CompareOpen();

		//system("pause");

		count_path++;


		Processing(temp[0], temp[1], goal_y, goal_x);
	}
	int pathx = map[goal_y][goal_x].prex;
	int pathy = map[goal_y][goal_x].prey;
	int newpathy, newpathx;
	while (1)
	{
		printf("y=%d,x=%d\t", pathy, pathx);
		if (map[pathy][pathx].name == 83)
			break;
		else
		{
			map[pathy][pathx].name = 50;
			newpathy = map[pathy][pathx].prey;
			newpathx = map[pathy][pathx].prex;
		}
		pathy = newpathy;
		pathx = newpathx;
	}
	printf("\n");
	for (int i = 0; i<count_y; i++)
	{
		for (int j = 0; j<count_x + 1; j++)
		{
			printf("%c", map[i][j].name);
			putc(map[i][j].name, fptr2);
		}
		//printf("\n");
	}

	printf("\n���W%d", map[start_y - 1][start_x - 1].g);
	printf("\n����%d", map[start_y][start_x - 1].g);
	printf("\n���U%d", map[start_y + 1][start_x - 1].g);
	printf("\n���W%d", map[start_y - 1][start_x].g);
	printf("\n���U%d", map[start_y + 1][start_x].g);
	printf("\n�k�W%d", map[start_y - 1][start_x + 1].g);
	printf("\n�k��%d", map[start_y][start_x + 1].g);
	printf("\n�k�U%d", map[start_y + 1][start_x + 1].g);
	printf("\n");
	printf("\n���W%d", map[start_y - 1][start_x - 1].h);
	printf("\n����%d", map[start_y][start_x - 1].h);
	printf("\n���U%d", map[start_y + 1][start_x - 1].h);
	printf("\n���W%d", map[start_y - 1][start_x].h);
	printf("\n���U%d", map[start_y + 1][start_x].h);
	printf("\n�k�W%d", map[start_y - 1][start_x + 1].h);
	printf("\n�k��%d", map[start_y][start_x + 1].h);
	printf("\n�k�U%d", map[start_y + 1][start_x + 1].h);
	printf("\n");
	printf("\n���W%d", map[start_y - 1][start_x - 1].f);
	printf("\n����%d", map[start_y][start_x - 1].f);
	printf("\n���U%d", map[start_y + 1][start_x - 1].f);
	printf("\n���W%d", map[start_y - 1][start_x].f);
	printf("\n���U%d", map[start_y + 1][start_x].f);
	printf("\n�k�W%d", map[start_y - 1][start_x + 1].f);
	printf("\n�k��%d", map[start_y][start_x + 1].f);
	printf("\n�k�U%d", map[start_y + 1][start_x + 1].f);

	fclose(fptr);
	fclose(fptr2);
	system("pause");
}

void Processing(int nodey, int nodex, int goaly, int goalx)
{

	if (map[nodey - 1][nodex - 1].name != 48 && map[nodey - 1][nodex - 1].open == 0)		//���W
	{
		if (map[nodey - 1][nodex - 1].open == 1)			//�쥻�N�b�}��C��
		{
			if (((map[nodey][nodex].g + 14) + (map[nodey - 1][nodex - 1].h))<map[nodey - 1][nodex - 1].f)
			{
				map[nodey - 1][nodex - 1].f = ((map[nodey][nodex].g + 14) + (map[nodey - 1][nodex - 1].h));//�s��f�Ȥ���p�A�N��s
				map[nodey - 1][nodex - 1].prey = nodey;
				map[nodey - 1][nodex - 1].prex = nodex;
			}
		}
		else if (map[nodey - 1][nodex - 1].open == 0)
		{
			OpenList[openi][0] = nodey - 1;
			OpenList[openi][1] = nodex - 1;
			openi++;
			count_openi++;
			map[nodey - 1][nodex - 1].g = map[nodey][nodex].g + 14;
			map[nodey - 1][nodex - 1].h = (abs(goaly - (nodey - 1)) + abs((goalx - (nodex - 1)))) * 10;
			map[nodey - 1][nodex - 1].f = map[nodey - 1][nodex - 1].g + map[nodey - 1][nodex - 1].h;
			map[nodey - 1][nodex - 1].prey = nodey;
			map[nodey - 1][nodex - 1].prex = nodex;
			map[nodey - 1][nodex - 1].open = 1;
		}
	}
	if (map[nodey][nodex - 1].name != 48 && map[nodey][nodex - 1].open == 0)		//����
	{
		if (map[nodey][nodex - 1].open == 1)			//�쥻�N�b�}��C��
		{
			if (((map[nodey][nodex].g + 14) + (map[nodey][nodex - 1].h))<map[nodey][nodex - 1].f)	//�s��g+�s��h(���ª��@��)=�s��f�A�Y�p���ª�f
			{
				map[nodey][nodex - 1].f = ((map[nodey][nodex].g + 14) + (map[nodey][nodex - 1].h));	//�s��f�Ȥ���p�A�N��s
				map[nodey][nodex - 1].prey = nodey;
				map[nodey][nodex - 1].prex = nodex;
			}
		}
		else if (map[nodey][nodex - 1].open == 0)
		{
			OpenList[openi][0] = nodey;
			OpenList[openi][1] = nodex - 1;
			openi++;
			count_openi++;
			map[nodey][nodex - 1].g = map[nodey][nodex].g + 10;
			map[nodey][nodex - 1].h = (abs((goaly - nodey)) + abs((goalx - (nodex - 1)))) * 10;
			map[nodey][nodex - 1].f = map[nodey][nodex - 1].g + map[nodey][nodex - 1].h;
			map[nodey][nodex - 1].prey = nodey;
			map[nodey][nodex - 1].prex = nodex;
			map[nodey][nodex - 1].open = 1;
		}
	}
	if (map[nodey + 1][nodex - 1].name != 48 && map[nodey + 1][nodex - 1].open == 0)		//���U
	{
		if (map[nodey + 1][nodex - 1].open == 1)			//�쥻�N�b�}��C��
		{
			if (((map[nodey][nodex].g + 14) + (map[nodey + 1][nodex - 1].h))<map[nodey + 1][nodex - 1].f)	//�s��g+�s��h(���ª��@��)=�s��f�A�Y�p���ª�f
			{
				map[nodey + 1][nodex - 1].f = ((map[nodey][nodex].g + 14) + (map[nodey + 1][nodex - 1].h));	//�s��f�Ȥ���p�A�N��s
				map[nodey + 1][nodex - 1].prey = nodey;
				map[nodey + 1][nodex - 1].prex = nodex;
			}
		}
		else if (map[nodey + 1][nodex - 1].open == 0)
		{
			OpenList[openi][0] = nodey + 1;
			OpenList[openi][1] = nodex - 1;
			openi++;
			count_openi++;
			map[nodey + 1][nodex - 1].g = map[nodey][nodex].g + 14;
			map[nodey + 1][nodex - 1].h = (abs((goaly - (nodey + 1))) + abs((goalx - (nodex - 1)))) * 10;
			map[nodey + 1][nodex - 1].f = map[nodey + 1][nodex - 1].g + map[nodey + 1][nodex - 1].h;
			map[nodey + 1][nodex - 1].prey = nodey;
			map[nodey + 1][nodex - 1].prex = nodex;
			map[nodey + 1][nodex - 1].open = 1;
		}
	}
	if (map[nodey - 1][nodex].name != 48 && map[nodey - 1][nodex].open == 0)		//���W
	{
		if (map[nodey - 1][nodex].open == 1)			//�쥻�N�b�}��C��
		{
			if (((map[nodey][nodex].g + 14) + (map[nodey - 1][nodex].h))<map[nodey - 1][nodex].f)	//�s��g+�s��h(���ª��@��)=�s��f�A�Y�p���ª�f
			{
				map[nodey - 1][nodex].f = ((map[nodey][nodex].g + 14) + (map[nodey - 1][nodex].h));	//�s��f�Ȥ���p�A�N��s
				map[nodey - 1][nodex].prey = nodey;
				map[nodey - 1][nodex].prex = nodex;
			}
		}
		else if (map[nodey - 1][nodex].open == 0)
		{
			OpenList[openi][0] = nodey - 1;
			OpenList[openi][1] = nodex;
			openi++;
			count_openi++;
			map[nodey - 1][nodex].g = map[nodey][nodex].g + 10;
			map[nodey - 1][nodex].h = (abs((goaly - (nodey - 1))) + abs((goalx - nodex))) * 10;
			map[nodey - 1][nodex].f = map[nodey - 1][nodex].g + map[nodey - 1][nodex].h;
			map[nodey - 1][nodex].prey = nodey;
			map[nodey - 1][nodex].prex = nodex;
			map[nodey - 1][nodex].open = 1;
		}
	}
	if (map[nodey + 1][nodex].name != 48 && map[nodey + 1][nodex].open == 0)		//���U
	{
		if (map[nodey + 1][nodex].open == 1)			//�쥻�N�b�}��C��
		{
			if (((map[nodey][nodex].g + 14) + (map[nodey + 1][nodex].h))<map[nodey + 1][nodex].f)	//�s��g+�s��h(���ª��@��)=�s��f�A�Y�p���ª�f
			{
				map[nodey + 1][nodex].f = ((map[nodey][nodex].g + 14) + (map[nodey + 1][nodex].h));	//�s��f�Ȥ���p�A�N��s
				map[nodey + 1][nodex].prey = nodey;
				map[nodey + 1][nodex].prex = nodex;
			}
		}
		else if (map[nodey + 1][nodex].open == 0)
		{
			OpenList[openi][0] = nodey + 1;
			OpenList[openi][1] = nodex;
			openi++;
			count_openi++;
			map[nodey + 1][nodex].g = map[nodey][nodex].g + 10;
			map[nodey + 1][nodex].h = (abs((goaly - (nodey + 1))) + abs((goalx - nodex))) * 10;
			map[nodey + 1][nodex].f = map[nodey + 1][nodex].g + map[nodey + 1][nodex].h;
			map[nodey + 1][nodex].prey = nodey;
			map[nodey + 1][nodex].prex = nodex;
			map[nodey + 1][nodex].open = 1;
		}
	}
	if (map[nodey - 1][nodex + 1].name != 48 && map[nodey - 1][nodex + 1].open == 0)		//�k�W
	{
		if (map[nodey - 1][nodex + 1].open == 1)			//�쥻�N�b�}��C��
		{
			if (((map[nodey][nodex].g + 14) + (map[nodey - 1][nodex + 1].h))<map[nodey - 1][nodex + 1].f)	//�s��g+�s��h(���ª��@��)=�s��f�A�Y�p���ª�f
			{
				map[nodey - 1][nodex + 1].f = ((map[nodey][nodex].g + 14) + (map[nodey - 1][nodex + 1].h));	//�s��f�Ȥ���p�A�N��s
				map[nodey - 1][nodex + 1].prey = nodey;
				map[nodey - 1][nodex + 1].prex = nodex;
			}
		}
		else if (map[nodey - 1][nodex + 1].open == 0)
		{
			OpenList[openi][0] = nodey - 1;
			OpenList[openi][1] = nodex + 1;
			openi++;
			count_openi++;
			map[nodey - 1][nodex + 1].g = map[nodey][nodex].g + 14;
			map[nodey - 1][nodex + 1].h = (abs((goaly - (nodey - 1))) + abs((goalx - (nodex + 1)))) * 10;
			map[nodey - 1][nodex + 1].f = map[nodey - 1][nodex + 1].g + map[nodey - 1][nodex + 1].h;
			map[nodey - 1][nodex + 1].prey = nodey;
			map[nodey - 1][nodex + 1].prex = nodex;
			map[nodey - 1][nodex + 1].open = 1;
		}
	}
	if (map[nodey][nodex + 1].name != 48 && map[nodey][nodex + 1].open == 0)		//�k��
	{
		if (map[nodey][nodex + 1].open == 1)			//�쥻�N�b�}��C��
		{
			if (((map[nodey][nodex].g + 14) + (map[nodey][nodex + 1].h))<map[nodey][nodex + 1].f)	//�s��g+�s��h(���ª��@��)=�s��f�A�Y�p���ª�f
			{
				map[nodey][nodex = 1].f = ((map[nodey][nodex].g + 14) + (map[nodey][nodex + 1].h));	//�s��f�Ȥ���p�A�N��s
				map[nodey][nodex + 1].prey = nodey;
				map[nodey][nodex + 1].prex = nodex;
			}
		}
		else if (map[nodey][nodex + 1].open == 0)
		{
			OpenList[openi][0] = nodey;
			OpenList[openi][1] = nodex + 1;
			openi++;
			count_openi++;
			map[nodey][nodex + 1].g = map[nodey][nodex].g + 10;
			map[nodey][nodex + 1].h = (abs((goaly - nodey)) + abs((goalx - (nodex + 1)))) * 10;
			map[nodey][nodex + 1].f = map[nodey][nodex + 1].g + map[nodey][nodex + 1].h;
			map[nodey][nodex + 1].prey = nodey;
			map[nodey][nodex + 1].prex = nodex;
			map[nodey][nodex + 1].open = 1;
		}
	}
	if (map[nodey + 1][nodex + 1].name != 48 && map[nodey + 1][nodex + 1].open == 0)		//�k�U
	{
		if (map[nodey + 1][nodex + 1].open == 1)			//�쥻�N�b�}��C��
		{
			if (((map[nodey][nodex].g + 14) + (map[nodey + 1][nodex + 1].h))<map[nodey + 1][nodex + 1].f)	//�s��g+�s��h(���ª��@��)=�s��f�A�Y�p���ª�f
			{
				map[nodey + 1][nodex + 1].f = ((map[nodey][nodex].g + 14) + (map[nodey + 1][nodex + 1].h));	//�s��f�Ȥ���p�A�N��s
				map[nodey + 1][nodex + 1].prey = nodey;
				map[nodey + 1][nodex + 1].prex = nodex;
			}
		}
		else if (map[nodey + 1][nodex + 1].open == 0)
		{
			OpenList[openi][0] = nodey + 1;
			OpenList[openi][1] = nodex + 1;
			openi++;
			count_openi++;
			map[nodey + 1][nodex + 1].g = map[nodey][nodex].g + 14;
			map[nodey + 1][nodex + 1].h = (abs((goaly - (nodey + 1))) + abs((goalx - (nodex + 1)))) * 10;
			map[nodey + 1][nodex + 1].f = (map[nodey + 1][nodex + 1].g + map[nodey + 1][nodex + 1].h);
			map[nodey + 1][nodex + 1].prey = nodey;
			map[nodey + 1][nodex + 1].prex = nodex;
			map[nodey + 1][nodex + 1].open = 1;
		}
	}
	map[nodey][nodex].open = -1;
	//count_openi=count_openi-1;
}
void CompareOpen()
{
	//int X;
	int min = 999999;
	for (int i = 0; i<count_openi; i++)
	{
		if (map[OpenList[i][0]][OpenList[i][1]].open == 1)
		{
			int y = OpenList[i][0];
			int x = OpenList[i][1];

			if (map[y][x].f<min)
			{
				min = map[y][x].f;
				temp[0] = y;
				temp[1] = x;
			}
		}
	}
}
