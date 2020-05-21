
// gcc lab1.c
// ./a.out
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int cmpfunc (const void * a, const void * b) //compare function needed for qsort
{
   
   int val1 = *(int*)a;
   int val2 = *(int*)b;
	 // qsort() expects the comparison function to return:
	 // 
	 //    a negative result if val1 < val2
	 //    0 if val1 == val2
	 //    a positive result if val1 > val2
	 return ( val1 - val2 ); 
}

int cmpfunc2 (const void * a, const void * b) //compare function needed for qsort
{
   
   int *val1 = (int*)a;
   int *val2 = (int*)b;
	 return ( val1[1] - val2[2]); 
}

void sort_delete_sort(int list_array[][2],int size) //function sorts by value, deletes duplicates, sorts by index and prints output
{
	int i=0;
	int new_size=0;
	qsort(list_array,size,2*sizeof(int),cmpfunc); //sorting by value
	
	for(i=1;i<size;i++)
	{
		if(list_array[new_size][0]!=list_array[i][0]) //checking for duplicates
		{
			list_array[++new_size][0]=list_array[i][0];
			list_array[new_size][1]=list_array[i][1];
		}
	}
	new_size=new_size+1; //gives the amount of "unique" numbers left after deleting duplicates
	qsort(list_array,new_size,2*sizeof(int),cmpfunc2); //sorting by index
  
	printf("\n%d\n",new_size); //printing new size

  for(i=0;i<new_size;i++) //printing new order of numbers
  {
      printf("%d\n",list_array[i][0]);
  }
}

int main (int argc, char*argv[])
{
	int size;
	int i=0;
	scanf("%d",&size);
	int list_array[size][2];
	
	for (i=0;i<size;i++) //reading in numbers, assigning position indicator
	{
		scanf("%d",&list_array[i][0]);
		list_array[i][1]=i;
	}
	sort_delete_sort(list_array,size);
	return 0;
}
	