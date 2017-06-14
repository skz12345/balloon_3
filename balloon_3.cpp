#include <stdlib.h>
#include <stdio.h>
#include <math.h>


typedef struct ball
{
	double x;
	double y;
	double z;
	double r;
}Ball;

//用来储存已经放置的气球
typedef struct ballList
{
	struct ballList * next;
	Ball ball;
}BallList;

void insert(Ball ball);
double distance(Ball b1, Ball b2);
int judge(Ball b);
void putBall();
void putPoint(double x, double y,double z);

BallList *head = NULL;
double step = 0.01;
int num = 0;
double sum = 0;
int main()
{
	int n, pointNum, i;
	printf_s("请输入空间内所要放置的气球数量: ");
	scanf_s("%d", &n);
	printf_s("请输入空间内点的数量: ");
	scanf_s("%d", &pointNum);
	for (i = 0; i < pointNum; i++)
	{
		printf_s("请输入第%d个点的坐标(其间用空格隔开)：", i + 1);
		double x, y,z;
		scanf_s("%lf %lf %lf", &x, &y,&z);
		putPoint(x, y,z);
	}
	//printf("\n球编号\t x坐标\t y坐标\t 半径\t r^2之和\n");
	for (i = 0; i < n; i++)
	{
		putBall();
	}
	printf_s("\nr^2之和为:\t %lf\n", sum);
	_sleep(100000);
	return 0;
}

void putPoint(double x, double y,double z)
{
	Ball ball = { x, y, z };
	insert(ball);
}

void insert(Ball ball)
{
	ballList * newBall = (ballList *)malloc(sizeof(ballList));
	newBall->ball = ball;
	newBall->next = head;
	head = newBall;
}

void putBall()
{
	Ball ball = { -1 + step, -1 + step,-1+step };
	Ball maxBall = ball;
	int i, j,k;
	for (i = 0; ball.x < 1; ++i)
	{
		ball.x += step;
		ball.y = -1 + step;
		for (j = 0; ball.y < 1; ++j)
		{
			ball.y += step;
			ball.z = -1 + step;
			for (k = 0; ball.z < 1; ++j){
				ball.z += step;
				ball.r = 0;
			double rstep = 0.1;
			while (rstep > 0.00001)
			{
				if (ball.r > maxBall.r)
				{
					maxBall = ball;
				}
				ball.r += rstep;
				if (!judge(ball))
				{
					ball.r -= rstep;
					rstep /= 10;
				}
			}
			}
		}
	}
	if (judge(maxBall))
	{
		insert(maxBall);
		num++;
		sum += maxBall.r * maxBall.r;
		//printf("%d\t %.3lf\t %.3lf\t %.3lf\t %lf \n", num, maxBall.x, maxBall.y, maxBall.r, sum);
	}
}

int judge(Ball b)
{
	if ((abs(b.x) + b.r) > 1 || (abs(b.y) + b.r) > 1 || (abs(b.z) + b.r) > 1)
	{
		return false;
	}
	ballList *tmp = head;
	while (tmp)
	{
		Ball ball = tmp->ball;
		if (distance(b, ball) < b.r + ball.r)
		{
			return false;
		}
		tmp = tmp->next;
	}
	return true;
}
double distance(Ball b1, Ball b2)
{
	double x1 = b1.x;
	double y1 = b1.y;
	double x2 = b2.x;
	double y2 = b2.y;
	double z1 = b1.z;
	double z2 = b2.z;
	return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)+(z1-z2)*(z1-z2), 0.5);
}