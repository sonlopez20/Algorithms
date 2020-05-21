
// Command line compilation -					 gcc lab4.c
// Command line run -  example:       ./a.out <lab4fall18.b.dat.txt

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

float elapsedCPU()
// to find the time used by CPU to process a sort
{
    struct rusage rusage;
    getrusage(RUSAGE_SELF,&rusage);
    return rusage.ru_utime.tv_sec+rusage.ru_utime.tv_usec/1000000.0 + rusage.ru_stime.tv_sec+rusage.ru_stime.tv_usec/1000000.0;
}


// quickselection sort functions
int partition(int *arr,int p,int r)
{
    int x,i,j,temp;

    x=arr[r];
    i=p-1;
    for (j=p;j<r;j++)
        if (arr[j]<=x)
        {
            i++;
            temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    temp=arr[i+1];
    arr[i+1]=arr[r];
    arr[r]=temp;
    return i+1;
}

int quickSelection(int *arr,int n,int k)
// quickselection sort
{
    int lowRange,highRange,q;

    lowRange=0;
    highRange=n-1;
    while (lowRange<=highRange)
    {
    
    q=partition(arr,lowRange,highRange);
    if (k-1==q)
        return q;
    else if (k-1<q)
        highRange=q-1;
    else
        lowRange=q+1;
}
printf("quickSelection error\n");
exit(0);
}


//qsort functions:
int intCompare(const void* xin, const void* yin)
{
    int *x,*y;

    x=(int*) xin;
    y=(int*) yin;
    return (*x) - (*y);
}

int sort1(int stopper, int hold3)
	//sorts needed for msd radix sort
{
	int hold;
	int i;
	int hold2;
	int dividend = 10;
	hold = hold3;
	for(i=0;i<stopper;i++)
	{
		hold= hold/dividend;
	}
	hold2 = hold%10;
	return hold2;
}

int sort (int array[], int stop1, int stop2, int k)
	//sorts needed for msd radix sort
{
		int i;
		int b;
		int size = 10;
		int up[10];
		int down [10];
		int print_all [stop1];
		int num;
		for(i=0; i<size; i++)
		{
			up[i] = 0;
		}
		for(i=0; i<stop1; i++)
		{
			int num_holder = sort1(stop2-1,array[i]);
			up[num_holder]++;
		}
		down[0]=0;
		for(i=1;i<size;i++)
		{
			down[i] = down[i-1]+up[i-1];
		}
		for(i=0;i<stop1;i++)
		{
			print_all[down[sort1(stop2-1,array[i])]++] = array[i];
		}
		for(i=9;i>0;i--) //prints positions and remaining numbers as long as conditions are met
		{
			down[i]=down[i-1];
		}
		down[0] = 0;
		i=sort1(stop2-1,print_all[k]);
		int hold_1 = up[i];
		printf("position %d n %d\n",stop2,stop1);
		
		if(hold_1>1) 
		{
			int reject[hold_1];
			for(b=0;b<hold_1;b++)
			{
				reject[b] = print_all[b+down[i]];
			}
			if(stop2==1)
			{
				printf("The value at rank k is%d\n",print_all[k-1]);
			}
			sort(reject,hold_1,stop2-1,k-down[i]);
		}
		else
		{
			printf("position %d n %d\n",stop2-1,hold_1);
			num = print_all[k-1];
			return num;
		}	
}
int main(int argc, char **argv)
{
    float startCPU;
    int n=0;
    int k=0;
    scanf("%d%d",&n,&k); //read the first line of the input, being the n values and k value
    
    int array [n];
    int i=0;

    for(i=0; i<n ; i++)
    // read in the values and fill the array
    {
        scanf("%d",&array[i]);
    }
    //first sort check with quickSelection
    startCPU=elapsedCPU();
    printf("quickSelection:  The value with rank %d is %d\n",k,array[quickSelection(array,n,k)]);
    printf("quickSelection time used is %f\n", elapsedCPU()-startCPU);

    //second sort check with qsort
    startCPU=elapsedCPU();
    qsort(array,n,sizeof(int),intCompare);
    printf("qsort: The value with rank %d is %d\n",k,array[k-1]);
    printf("qsort time used is %f\n", elapsedCPU()-startCPU);

    //third sort with MSD radix sort
		int done = 9;
		int num;
		num = sort(array, n, done, k);
		printf("MSD 10 radix: The value with rank %d is %d \n",k,array[quickSelection(array,n,k)]);
		printf("radix selection time used is %f\n",startCPU);	
	
}