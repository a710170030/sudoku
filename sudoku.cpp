#include <iostream>
#include <stdlib.h>  
#include <iomanip>
#include <time.h>
using namespace std;

int board[9][9]={0};
int flag[9][9]={0};
int c[9][9][9]={0};
int count[9][9]={0};
int min_i[80]={0};
int min_j[80]={0};
int counter;
int re=0;
int a,b;

bool judge(int x ,int y)
{
	int i,j,i1,j1;

	if (board[x][y]>9)
		return false;
	for (i=0;i<9;i++)
	{
		if (i!=x)
		{
			if (board[i][y] == board[x][y])
				return false;
		}
		if (i!=y)
		{
			if (board[x][i] == board[x][y])
				return false;
		}
	}
	i1=(x/3)*3;
	j1=(y/3)*3;
	for (i=i1; i<i1+3; i++)
		for (j=j1; j<j1+3 ;j++)
		{
			if (i!=x && j!=y)
				if (board[i][j] == board[x][y])
					return false;
		}
	return true;
}


void output()
{
	for (int i=0;i<9;i++)
	{
		cout<<endl<<endl;
		for (int j=0;j<9;j++)
		{
			cout<<setw(3)<<board[i][j]<<" ";
		}
	}
	cout<<endl<<endl;
}

void run(int x, int y,int number)
{
	int i,j,i1,j1,min;
	counter++;
	i1=(x/3)*3;
	j1=(y/3)*3;
	board[x][y]=number;
	flag[x][y]=2;
	for (i=0;i<9;i++)
	{
		if (i!=x && flag[i][y]==0)
		{
			if (c[i][y][number-1]>0)
			{
				if (c[i][y][number-1]==1)
					count[i][y]--;
				c[i][y][number-1]++;
			}
		}
		if (i!=y && flag[x][i]==0)
		{
			if (c[x][i][number-1]>0)
			{
				if (c[x][i][number-1]==1)
					count[x][i]--;
				c[x][i][number-1]++;
			}
		}
	}
	for (i=i1; i<i1 +3 ;i++)
		for (j=j1;j<j1+3;j++)
			if (i!=x && j!=y && flag[i][j]==0)
			{
				if (c[i][j][number-1]>0)
				{
					if (c[i][j][number-1]==1)
						count[i][j]--;
					c[i][j][number-1]++;
				}
			}
	min_i[counter]=0;
	min_j[counter]=0;
	min=9;
	for (i=0;i<9;i++)
		for (j=0;j<9;j++)
		{
			if (flag[i][j]==0)
			{
				if (count[i][j]<min)
				{
					min_i[counter]=i;
					min_j[counter]=j;
					min=count[i][j];
				}
			}
		}

//------输出
	if (min_i[counter]==0 && min_j[counter]==0 && flag[0][0]!=0)
	{
		output();
		b=clock();
		cout<<b-a;
		system("pause");
		exit(1);
	}
//--------迭代
	if (count[min_i[counter]][min_j[counter]]>0)
	{
		for (i=0;i<9;i++)
			if (c[min_i[counter]][min_j[counter]][i]==1)
				run(min_i[counter],min_j[counter],i+1);
	}
	//--------回溯
	counter--;
	board[x][y]=0;
	for (i=0;i<9;i++)
	{
		if (i!=x && flag[i][y]==0)
		{
			if (c[i][y][number-1]>1)
			{
				c[i][y][number-1]--;
				if (c[i][y][number-1]==1)
					count[i][y]++;
			}
		}
		if (i!=y && flag[x][i]==0)
		{
			if (c[x][i][number-1]>1)
			{
				c[x][i][number-1]--;
				if (c[x][i][number-1]==1)
					count[x][i]++;
			}
		}
	}
	for (i=i1; i<i1 +3 ;i++)
		for (j=j1;j<j1+3;j++)
			if (i!=x && j!=y && flag[i][j]==0)
			{
				if (c[i][j][number-1]>1)
				{
					c[i][j][number-1]--;
					if (c[i][j][number-1]==1)
						count[i][j]++;
				}
			}
	flag[x][y]=0;
}

void prenum()
{
	int x1,y1,z1,a;
	cout<<"请输入已知数字的个数"<<endl;
	cin>>a;
	cout<<"已知总数为"<<a<<",开始输入坐标及数值"<<endl;
	cout<<"格式:x y z"<<endl;
	cout<<"其中x为行，y为列，z为数值"<<endl;
	for (int i=0;i<a;i++)
	{
		cin>>x1;
		cin>>y1;
		cin>>z1;
		board[x1-1][y1-1]=z1;
		cout<<"输入成功,坐标("<<x1<<","<<y1<<")处数字为"<<z1<<endl;
	}
}
void precount()
{
	for (int i=0;i<9;i++)
		for (int j=0;j<9;j++)
		{
			if (!flag[i][j])
			{
				for (int k=1;k<=9;k++)
				{
					board[i][j]=k;
					if (judge(i,j))
					{
						c[i][j][k-1]=1;
						count[i][j]++;
					}
				}
				board[i][j]=0;
			}
		}
}
				

int main()
{
	int i0,j0;
	prenum();
	a=clock();
	for (int i=0;i<9;i++)
		for (int j=0;j<9;j++)
		{
			if (board[i][j]!=0)
				flag[i][j]=1;
			else
			{
				i0=i;
				j0=j;
			}
		}
	precount();
	for (i=0;i<9;i++)
		for (int j=0;j<9;j++)
		{
			if (flag[i][j]==0)
			{
				if (count[i][j]<count[i0][j0])
				{
					i0=i;
					j0=j;
				}
			}
		}
	min_i[counter]=i0;
	min_j[counter]=j0;
//	cout<<i0<<" "<<j0<<endl;
	for (int k=1;k<=9;k++)
		if (c[min_i[counter]][min_j[counter]][k-1]==1)
			run(min_i[counter],min_j[counter],k);
	cout<<"no solution"<<endl;
	return 0;
}



