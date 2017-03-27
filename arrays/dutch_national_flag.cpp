#include <iostream>
using namespace std;

#define SWAP(a,b) int temp=b; b =a; a= temp;

void arrange_dutch_nf(int *a, int size)
{
	int l =0 , h= size -1;
	int counter =0;	
	while(l<=h)
	{
		++counter;
		if(a[l] == 0 && a[h] == 2)
		{
			l++;
			h--;
		}
		else if(a[l] == 0)
			l++;
		else if(a[h] == 2)
			h--;
		else
		{
			SWAP(a[l],a[h]);
			l++;
			h--;
		}
	}

	h = size -1;	
	while(l<=h)
	{
		++counter;
		if(a[l] == 1 && a[h] == 2)
		{
			l++;
			h--;
		}
		else if(a[l] == 1)
			l++;
		else if(a[h] == 2)
			h--;
		else
		{
			SWAP(a[l],a[h]);
			l++;
			h--;
		}
	}
	cout<<"total no of times the loop ran is :"<<counter<<endl;
}

int main()
{

	int arr[] = {0,0,1,2,1,0,2,0};
	int n = sizeof(arr)/sizeof(arr[0]);
	arrange_dutch_nf(arr,n);
	cout << "after rearrangement:";
	for (int i=0; i<n;i++)
		cout << arr[i];
	
}
