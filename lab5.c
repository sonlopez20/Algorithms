
// Command line compilation -					 gcc lab5.c
// Command line run -  example:       ./a.out <lab5fall18.a.dat.txt or ./a.out (copy and paste data)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

int n; //number of nodes
int e; //number of edges
int pos;
char ** result;
int *vertexStatus,*secondDFSrestarts;

// Strongly connected components using Kosaraju's DFS technique
// BPW, 4/2003
//Used and edited code provided in the website
// the counting of the hash table size is for some reason not doing so correctly in some cases

int prime (int number)//keeps track pf prime number
{
	int i;
	for(i = 2; i<number; i++)
	{
		if(number%i == 0)
		{
			number ++;
			i = 2;
		}
		else
		{
			continue;
		}
	}
	return number;
}

int check_words (char** word, int* pos, char new_string []) //compare to see if the word entered matches the word already in the double char array
{
	int i;
	char temp [50];
	for (i = 0; i < *pos; i ++)
	{
		strcpy(temp,word[i]);
		if (strcmp(new_string , temp) == 0)
		{
			return i;
		}
	}
	return -1;
}

int read_info (char ** word, int size, int *pos, char* new_string) //reads info
{
	if(*pos >= size)
	{
		printf("Invalid input\nExiting Program...\n");
		exit(0);
	}
	else
	{
		word[*pos] = new_string;
		*pos += 1;
		return *pos -1;
	}
}

int key (char* s) // keeps track of the last string
{
	int n = strlen(s);
	int i;
	int last = 0;
	for (i=0; i<n; i++)
	{
		last += s[i];
	}
	return last;
}

int hash (int* hash_table, char** word, int size) //calculate hash table size
{
	int i;
	int k;
	int m = prime (size);
	int try;
	int index;
	int h1, h2;
	int complete;
	char * temp;
	int ret;
	temp = (char*) malloc (50 * sizeof(char));
	scanf("%s",temp);
	k = key(temp);
	h1 = k % m;
	h2 = 1 + (k % (m-1));
	try = 0;
	complete = 0;
	while (!complete && try<50)
	{
		index = (h1 + try + h2)%m;
		if (hash_table [index] == -1)
		{
			ret = read_info(word, size,&pos,temp);
			hash_table [index] = pos;
			complete = 1;
		}
		else if (hash_table[index]>-1)
		{
			complete = check_words(word, &pos, temp);
			if (complete != -1)
			{
				ret = complete;
				complete = -1;
			}
			else
				complete = 0;
		}
		try ++;
	}
	return ret;
}

struct edge {
  int tail,head,type; 
};

typedef struct 
	edge edgeType;
	edgeType *edgeTab;
	int *firstEdge;  // Table indicating first in range of edges with a common tail

int tailThenHead(const void* xin, const void* yin)
// Used in calls to qsort() and bsearch() for read_input_file()
{
	int result;
	edgeType *x,*y;
	
	x=(edgeType*) xin;
	y=(edgeType*) yin;
	result=x->tail - y->tail;
	
	if (result!=0)
	{
		return result;
	}
	else
	{
		return x->head - y->head;
	}
}

void read_input_file()
{
	int a,b,i,j;
	int vertices, edges; //variables to store the number of vertices and edges
	char **data; //store the unique vertices in this array
	int *hashtable;
	pos = 0;
	scanf("%d %d",&n,&e);
	vertices = n;
	edges = e;
	
	hashtable = (int *) calloc(prime(vertices),sizeof(int));
	data = (char **)calloc(vertices , (50 + 1) * sizeof(char));
	result = data;
	for ( i = 0 ; i < prime(vertices); i++)
		hashtable[i] = -1;
	
	printf("\n\nDouble hash table size is %d",prime(vertices) ); //prints out while reading the info, tried putting in a different spot but it would print incorrect thing 
	edgeType work;
	edgeType *ptr;
	
	edgeTab=(edgeType*) malloc(e*sizeof(edgeType));
	if (!edgeTab)
		{
			printf("edgeTab malloc failed %d\n",__LINE__);
			exit(0);
		}
		
		// read edges
		for (i=0; i<e; i++)
		{
			a = hash (hashtable,data,vertices);
			b = hash (hashtable,data,vertices);
			if (a<0 || a>=n || b<0 || b>=n)
				{
					printf("Invalid input %d %d at %d\n",a,b,__LINE__);
					exit(0);
				}
				edgeTab[i].tail=a;
				edgeTab[i].head=b;
			}
// sort edges
qsort(edgeTab,e,sizeof(edgeType),tailThenHead);
// Coalesce duplicates into a single edge
j=0;
for (i=1; i<e; i++)
	if (edgeTab[j].tail==edgeTab[i].tail && edgeTab[j].head==edgeTab[i].head)
			;
	else
	{
		j++;
		edgeTab[j].tail=edgeTab[i].tail;
		edgeTab[j].head=edgeTab[i].head;
  }
	e=j+1;
	
	// For each vertex as a tail, determine first in range of edgeTab entries
	firstEdge=(int*) malloc((n+1)*sizeof(int));
	if (!firstEdge)
		{
			printf("malloc failed %d\n",__LINE__);
			exit(0);
		}
		j=0;
		for (i=0; i<n; i++)
		{
			firstEdge[i]=j;
			for ( ; 
			j<e && edgeTab[j].tail==i;
			j++)
				;
		}
		firstEdge[n]=e;
	}
	int finishIndex;

void DFSvisit(int u)
{
	int i,v;
	vertexStatus[u]=GRAY;
	
	for (i=firstEdge[u];i<firstEdge[u+1];i++)
	{
		v=edgeTab[i].head;
		if (vertexStatus[v]==WHITE)
			DFSvisit(v);
	}
	vertexStatus[u]=BLACK;
	secondDFSrestarts[--finishIndex]=u;
}

void reverseEdges()
{
	int a,b,i,j;
	edgeType work;
	edgeType *ptr;
	
	for (i=0; i<e; i++)
	{
		a=edgeTab[i].tail;
		b=edgeTab[i].head;
		edgeTab[i].tail=b;
		edgeTab[i].head=a;
	}
	
	// sort edges
	qsort(edgeTab,e,sizeof(edgeType),tailThenHead);
	
	// For each vertex as a tail, determine first in range of edgeTab entries
	if (!firstEdge)
		{
			printf("malloc failed %d\n",__LINE__);
			exit(0);
		}
		j=0;
		for (i=0; i<n; i++)
		{
			firstEdge[i]=j;
			for ( ;
			j<e && edgeTab[j].tail==i;
			j++)
				;
		}
		firstEdge[n]=e;
}

void DFSvisit2(int u)
{
	int i,v;
	
	printf("%s\n",result[u]); // Indicate that u is in SCC for this restart
	vertexStatus[u]=GRAY;
	
	for (i=firstEdge[u];i<firstEdge[u+1];i++)
	{
		v=edgeTab[i].head;
		if (vertexStatus[v]==WHITE)
			DFSvisit2(v);
	}
	vertexStatus[u]=BLACK;
}

int main()
{
	int u,i,j,k,nextDFS;
	int SCCcount=0;
	
	read_input_file();
	
	vertexStatus=(int*) malloc(n*sizeof(int));
	secondDFSrestarts=(int*) malloc(n*sizeof(int));
	if (!vertexStatus || !secondDFSrestarts)
		{
			printf("malloc failed\n");
			exit(0);
		}
		
		//DFS code
		for (u=0;u<n;u++)
			vertexStatus[u]=WHITE;
		finishIndex=n;
		for (u=0;u<n;u++)
			if (vertexStatus[u]==WHITE)
				DFSvisit(u);
		
		reverseEdges();
		//DFS code
		for (u=0;u<n;u++)
			vertexStatus[u]=WHITE;
		for (i=0;i<n;i++)
		if (vertexStatus[secondDFSrestarts[i]]==WHITE)
		{
			SCCcount++;
			printf("SCC %d\n",SCCcount);
			DFSvisit2(secondDFSrestarts[i]);
		}
		free(edgeTab);
		free(firstEdge);
		free(vertexStatus);
		free(secondDFSrestarts);
		return 0;
}

