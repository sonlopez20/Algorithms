
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Command line compilation -					 gcc lab6.c
// Command line run -  example:       ./a.out <lab6fall18.c.dat.txt or ./a.out (copy and paste data)

// this code does not produce the same output as that seen on the website for all the .dat

// used http://ranger.uta.edu/~weems/NOTES2320/kruskal.c
int numVertices,numEdges;
int *parent, *weight, numTrees;

struct edge{
	int tail,head;
	double weight;
};

struct coordinate{
	int x,y;
};

typedef struct coordinate coordinateType;
coordinateType *points;

typedef struct edge edgeType;
edgeType *edgeTab;

int find(int x)
// Find root of tree containing x
{
	int i,j,root;
	// Find root
	for (i=x;
	parent[i]!=i;
	i=parent[i])
		;
	root=i;
	// path compression - make all nodes on path
	// point directly at the root
	for (i=x;
	parent[i]!=i;
	j=parent[i],parent[i]=root,i=j)
		;
	return root;
}

void unionFunc(int i,int j)
	// i and j must be roots!
{
	if (weight[i]>weight[j])
	{
		parent[j]=i;
		weight[i]+=weight[j];
	}
	else
	{
		parent[i]=j;
		weight[j]+=weight[i];
	}
	numTrees--;
}

int weightAscending(const void* xin, const void* yin)
	// Used in call to qsort()
{
	edgeType *x,*y;
	
	x=(edgeType*) xin;
	y=(edgeType*) yin;
	return x->weight - y->weight;
}

double MST ()
{
	double MSTweight=0;
	int i,j;
	int root1,root2;
	int k=0;
	for(i=0; i<numVertices-1; i++){
		for(j=i+1;j<numVertices;j++){
			double distance=sqrt(((points[j].x-points[i].x)*(points[j].x-points[i].x))+((points[j].y-points[i].y)*(points[j].y-points[i].y)));
			edgeTab[k].weight=distance;
			edgeTab[k].tail=i;
			edgeTab[k].head=j;
			k++;
		}
	}
	qsort(edgeTab,numEdges,sizeof(edgeType),weightAscending);
	for (i=0;i<numEdges;i++)
	{
		root1=find(edgeTab[i].tail);
		root2=find(edgeTab[i].head);
		if (i == numVertices )
		{
			break;
		}
		else if (root1==root2)
			printf("%d %d \t%.3f discarded\n",edgeTab[i].tail,edgeTab[i].head,
		edgeTab[i].weight);
		else
			{
				printf("%d %d \t%.3f included\n",edgeTab[i].tail,edgeTab[i].head,
				edgeTab[i].weight);
				MSTweight+=edgeTab[i].weight;
				unionFunc(root1,root2);
			}  
		}
		return MSTweight;
}
int main()
{
	int i;
	double MSTweight=0;
	//int root1,root2;
	
	scanf("%d",&numVertices);
	numEdges=(numVertices*(numVertices-1))/2;
	edgeTab=(edgeType*) malloc(numEdges*sizeof(edgeType));
	points=(coordinateType*) malloc(numVertices*sizeof(coordinateType));
	parent=(int*) malloc(numVertices*sizeof(int));
	weight=(int*) malloc(numVertices*sizeof(int));
	if (!edgeTab ||!points|| !parent || !weight)
		{
			printf("error 2\n");
			exit(0);
		}
		for (i=0;i<numVertices;i++)
			scanf("%d %d",&points[i].x,&points[i].y);
		
		for (i=0;i<numVertices;i++)
		{
			parent[i]=i;
			weight[i]=1;
		}
		printf("==================================\n");
		for(i=0; i<numVertices; i++){
			printf("%d %d %d \n",i,points[i].x,points[i].y);
		}
		MSTweight=MST();
		printf("Sum of weights of spanning edges %.3f\n",MSTweight);
		free(edgeTab);
		free(points);
		free(parent);
		free(weight);
}