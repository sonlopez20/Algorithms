
//CSE2320 Lab 3
//Compiled on omega using gcc lab3.c



#include <stdio.h>
#include <stdlib.h>


int main()
{
    int n,m,i,j,k,b,potential_sum;//initialize variables
    scanf("%d",&n);
    scanf("%d",&m);
    int *S;
    int **Table;
    S = (int *)calloc(n+1,sizeof(int)); //using calloc so all numbers will automatically be a zero
    Table=(int **)calloc(n+1,sizeof(int*));//dynamically allocate a table for sequence vales
    for(i=0; i<=n;i++)
		{
        Table[i]=(int *)calloc(m+1,sizeof(int)); 
    }
    Table[0][0]=0;//Create a 2D table, creating base case
    
		    
    for(j=1;j<=m;j++)
		{
        Table[0][j]=n+1;
    }
    for(j=1;j<=n;j++)
		{
        Table[j][0]=n+1;
    }
    
    for(i=0; i<=n; i++)
		{
        if(i==0)
				{
            S[0]=0;
    		}
				else
				{
    			scanf("%d",S+i);
				}
    }
//filling in the sequence values
    for(i=1;i<=m;i++)
		{
        for(j=1;j<=n;j++)
				{
            for(k=1;k<=n;k++)
						{
                int a;
                a=i-S[k];
                if(a<0)
								{
                     Table[j][i]=n+1;
                }
                if(a>=0)
								{
                    b=Table[j-1][a];
                    if(k>b)
										{
                        Table[j][i]=k;
                        break;
                    }
										else
										{
                        Table[j][i]=n+1;
                    }   
                }
            }
        }
    }

    printf("m is %d\n",m);
    printf("   i   S\n---------\n");

    for(i=0; i<=n; i++)
		{
    	printf("   %d   %d\n",i,S[i]); //prints the 2D table 
    } 

    printf("\n\n  i   Card   C\n---------------\n"); //displaying what is in the table
    for(i=0;i<=m;i++)
		{
        for(j=1;j<=n;j++)
				{
            printf("  %d    %d   %d\n",i,j,Table[j][i]);
        }
    }

    for(i=1;i<=n;i++) //calculating cost 
		{
            if(Table[i][m]<n+1)
						{
                int h,d;
                printf("Solution with %d elements.\n   i   S\n---------\n",i);
                printf("   %d   %d\n",Table[i][m],S[Table[i][m]]);
                h=m-S[Table[i][m]];
                d=Table[i-1][h];
                int k=2;
                while(d>0)
								{
                    printf("   %d   %d\n",d,S[d]);
                    h=h-S[d];
                    d=Table[i-k][h];
                    k++;
                }
            }
						else
						{
                printf("No solution with %d elements.\n",i);
            }
        }
				//freeing memory
    free(S);
    for(i=0; i<=n;i++){
        free(Table[i]);
    }
    free(Table);
}

