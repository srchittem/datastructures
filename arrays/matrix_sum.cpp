#include <iostream>
using namespace std;

#define ROWS 5
#define COLS 5

void precompute_matrix(int a[ROWS][COLS])
{

	int i=COLS-2, j = 0;
	for(;i>=0;i--)
	{
		
		for(j=0;j<ROWS;j++)
		{
			a[j][i]+=a[j][i+1];
		}
	}

}


int submatrix_sum(int a[ROWS][COLS],int r1,int c1, int r2, int c2)
{
	int res =0;
	for (int i=r1;i<=r2;i++)
	{
		res += a[i][c1];
	}
	
	if(c2 != COLS-1)
	{
		for (int i=r1;i<=r2;i++)
		{
			res -= a[i][c2+1];

		}
	}
	return res;
}

int main()
{

	int arr[][COLS]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
	precompute_matrix(arr);
	cout << "precomputed array";
	for (int i=0; i<ROWS;i++)
	{
		for(int j=0;j<COLS;j++)
		{
			cout << arr[i][j];
		}
		cout <<endl;
	}
	cout << "sum of sub array:"<<submatrix_sum(arr,2,0,2,4);

}
