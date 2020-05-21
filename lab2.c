
// gcc lab2.c
// ./a.out <filename.txt
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int subsequence_function (int middle, int * arraya, int * arrayx, int sizea, int sizex)
{
	int newsizex = sizex * middle;
	int arrayx2[newsizex];
	int i=0,j=0,n=0;
  // Making B^(i) array,
  for(i=0; i<sizex; i++)
  {   
      for(j=0; j<middle ; j++)
      {
          arrayx2[n++] = arrayx[i];
      }
  }

  i=0;
  n=0;
  while((n<newsizex)&&(i<sizea)) // O(n)
  {
      if(arraya[i]==arrayx2[n])
      {
          if((n+1)==newsizex)  // means that the last element of B^(i) matched with A's element!
          {
              return 1;  // test complete, passed!
              break;
          }
          ++i;
          ++n;
      }
      else
      {
          i+=1;
      }
  }
  return 0; // test did not pass!
}

void search (int high, int * arraya , int * arrayx , int sizex, int sizea)
{
	int score = 0;
	int low = 0;
	int dummy = 0;
	while (low<=high)
	{
		int middle = (high + low) / 2;
		dummy = subsequence_function(middle,arraya,arrayx,sizea,sizex);
		if(dummy == 1)
		{
			printf ("Low %d, Middle %d, High %d SUCCESS\n",low,middle,high);
			score = middle;
			low++;
		}
		else if (dummy == 0)
		{
			printf("Low %d, Middle %d, High %d FAILURE\n",low,middle,high);
			high--;
		}
		else 
		{
			printf ("Error.");
			break;
		}
		printf ("Max Count: %d\n",score);
	}
}

int main()
{
	int sizea;
	int sizex;
	int high;
	int i = 0;
	scanf("%d%d",&sizea,&sizex);
	//making arrays dynamically
	int *arraya = malloc(sizeof(int)*sizea);
	int *arrayx = malloc(sizeof(int)*sizex);
	
	for(i=0;i<sizex;i++)
	{
		scanf("%d",&arraya[i]);
	}
	scanf("%d",&high);
	
	for(i= 0; i<sizex; i++)
	{
		scanf("%d", &arrayx[i]);
	}
	scanf("%d", &high);
	high = sizea / sizex;
	search ( high,arraya,arrayx,sizea,sizex);
	free(arraya);
	free(arrayx);
	return 0;
	}