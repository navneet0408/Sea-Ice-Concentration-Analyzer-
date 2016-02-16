
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "DataTypes.h"
#include "LinkedList.h"
#include "Graph.h"

//Global Data Structures
Graph graph1;
Graph graph2;
HistogramData histoGram1[2000];
HistogramData histoGram2[2000];

//Initialize the graph
void initGraph(Graph *graph)
{
	int i,j;
	graph->edges = NULL;
	graph->numEdges = 0;
	graph->numVertices = 0;
	graph->numLand = 0;
	graph->numMissing = 0;
	graph->clusteringCoefficient = 0.0;
	graph->charPathLength = 0.0;
	for(i=0; i<NUM_ROWS; ++i)
	{
		for(j=0; j<NUM_COLUMNS; ++j)
		{
			graph->vertices[i][j].row = i;
			graph->vertices[i][j].column = j;
			graph->vertices[i][j].edges = NULL;
			graph->vertices[i][j].neighbours = NULL;
			graph->vertices[i][j].degree = 0;
			graph->vertices[i][j].numTotalEdgesInCluster = 0;
			graph->vertices[i][j].distFromSource = 0;
			graph->vertices[i][j].clusteringCoefficient = 0.0;
			graph->vertices[i][j].charPathLength = 0.0;
			graph->vertices[i][j].sxx = 0.0;
			graph->vertices[i][j].visited = false;
		}
	}
}

//Add Edge between two vertices
void addEdge(int fromRow, int fromColumn, int toRow, int toColumn, Graph *graph)
{
	Edge 	*edge				= malloc(sizeof(Edge));
	Vertex 	*fromVertex 		= &graph->vertices[fromRow][fromColumn];
	Vertex	*toVertex 			= &graph->vertices[toRow][toColumn];
	Node 	*node1 				= malloc(sizeof(Node));
	Node 	*node2				= malloc(sizeof(Node));
	Node 	*node3 				= malloc(sizeof(Node));
	Node 	*fromVertexNode 	= malloc(sizeof(Node));
	Node 	*toVertexNode 		= malloc(sizeof(Node));

	edge->edgeFrom 			= &graph->vertices[fromRow][fromColumn];
	edge->edgeTo 			= &graph->vertices[toRow][toColumn];
	node1->data 			= (void *) edge;
	node2->data 			= (void *) edge;
	node3->data				= (void *) edge;
	fromVertexNode->data 	= (void *) fromVertex;
	toVertexNode->data		= (void *) toVertex;

	add(&graph->vertices[fromRow][fromColumn].edges, node1);
	add(&graph->vertices[toRow][toColumn].edges, node2);
	add(&graph->edges, node3);
	add(&graph->vertices[fromRow][fromColumn].neighbours, toVertexNode);
	add(&graph->vertices[toRow][toColumn].neighbours, fromVertexNode);

	graph->vertices[fromRow][fromColumn].degree++;
	graph->vertices[toRow][toColumn].degree++;
	graph->numEdges++;
}

//Calculate the Pearson correlation coefficient for two vertices...
double calcPCC(int xRow, int xColumn, int yRow, int yColumn,
		int startYear, int stopYear, int timeLag)
{

	double sxy=0, pcc;
	int i, j, yWeek, yYear;
	for(i=startYear; i<stopYear; ++i)
	{
		for(j=0; j<NUM_WEEKS; ++j)
		{
			if((seaIceConc[xRow][xColumn][i][j] == 168) || (seaIceConc[xRow][xColumn][i][j] == 157)
					|| (seaIceConc[yRow][yColumn][i][j] == 168) || (seaIceConc[yRow][yColumn][i][j] == 157))
			{
				continue;
			}
			else
			{
				yWeek = (j+timeLag) % NUM_WEEKS;
				yYear = (i + (j+timeLag)/NUM_WEEKS);
				if(yYear < stopYear)
					sxy = sxy + ( seaIceConc[xRow][xColumn][i][j] * seaIceConc[yRow][yColumn][yYear][yWeek]);
			}
		}
	}
	pcc = sxy / sqrt(sxx[xRow][xColumn]*sxx[yRow][yColumn]);

	return pcc;
}

//Create the graph from the parsed data
void createGraphFromData(int startYear, int stopYear, int timeLag, char *fileName)
{
	int xRow,xCol, yRow, yCol;
	char filename1[100], filename2[100];
	for(xRow=0; xRow<NUM_ROWS; ++xRow)
	{
		for(xCol=0; xCol<NUM_COLUMNS; ++xCol)
		{
			for(yRow=xRow; yRow<NUM_ROWS; ++yRow)
			{
				for(yCol=xCol+1; yCol<NUM_COLUMNS; ++yCol)
				{
					double pcc = calcPCC(xRow, xCol, yRow, yCol, startYear, stopYear, timeLag);
					if(fabs(pcc) >=0.9)
					{
						addEdge(xRow, xCol, yRow, yCol, &graph1);
					}
					if(fabs(pcc) >=0.95)
					{
						addEdge(xRow, xCol, yRow, yCol, &graph2);
					}
				}
			}
		}
		printf("%d\n", xRow);
	}
	graph1.numLand = graph2.numLand = numLand;
	graph1.numMissing = graph2.numMissing = numMissing;
	printf("Average Degree: %f\n", (float) graph1.numEdges/(NUM_ROWS*NUM_COLUMNS - graph1.numLand - graph1.numMissing));
	printf("Average Degree: %f\n", (float) graph2.numEdges/(NUM_ROWS*NUM_COLUMNS - graph2.numLand - graph2.numMissing));
	strcpy(filename1, fileName);
	strcpy(filename2, fileName);
	calcHistogram(&graph1, histoGram1, strcat(filename1,"_hist_1.csv"));
	calcHistogram(&graph2, histoGram2, strcat(filename2, "_hist_2.csv"));
}

//Calculate the histogram data
void calcHistogram(Graph *graph, HistogramData *histoGram, char *fileName)
{
	int i,j;
	FILE *file  = fopen(fileName, "w");
	if(file == NULL)
	{
		printf("Error reading file!!!");
		return;
	}
	for(i=0; i<2000;++i)
	{
		histoGram[i].degree = i;
		histoGram[i].numVertices = 0;
		histoGram[i].vertices = NULL;
	}
	for(i=0; i<NUM_ROWS; ++i)
	{
		for(j=0; j<NUM_COLUMNS; ++j)
		{
			if(graph->vertices[i][j].degree>2000)
				printf("ERROR..... ERROR...... \n");
			histoGram[graph->vertices[i][j].degree].numVertices++;
			Node *node = malloc(sizeof(Node));
			node->data = (void *) &graph->vertices[i][j];
			add(&histoGram[graph->vertices[i][j].degree].vertices, node);
		}
	}
	fprintf(file, "\n");
	for(i=0; i<2000;++i)
	{
		fprintf(file, "%d", histoGram[i].degree);
		fprintf(file, ",");
		fprintf(file, "%d", histoGram[i].numVertices);
		fprintf(file, ",");
		Node *current = histoGram[i].vertices;
		fprintf(file, ",");
		if(current!=NULL)
		{
			do
			{
				Vertex *v = current->data;
				fprintf(file, "%d", v->row);
				fprintf(file, ",");
				fprintf(file, "%d", v->column);
				fprintf(file, ",");
				fprintf(file, "->");
				fprintf(file, ",");
				current = current->next;
			}while(current!=histoGram[i].vertices);
		}
		fprintf(file, "\n");
	}
	fclose (file);
}

//Calculate the clustering coefficient
void calcClusteringCoefficient(Graph *graph, char *fileName)
{
	int row, col;
	FILE *file  = fopen(fileName, "w");
	if(file == NULL)
	{
		printf("Error reading file!!!");
		return;
	}
	for(row=0; row<NUM_ROWS; ++row)
	{
		for(col=0; col<NUM_COLUMNS; ++col)
		{
			int k = graph->vertices[row][col].degree;
			if(k!=0)
			{
				graph->numVertices++;
				calcNumEdges(&graph->vertices[row][col]);
			}
			graph->clusteringCoefficient = graph->clusteringCoefficient
					+ graph->vertices[row][col].clusteringCoefficient;
		}
	}

//	printf("\n!!!!!!!NUM VERTICES: %d!!!!!!!!!!!!!!!!\n", graph->numVertices);
	graph->clusteringCoefficient =
			graph->clusteringCoefficient/ (NUM_ROWS*NUM_COLUMNS - graph->numLand - graph->numMissing);

	printf("Clustering Coefficient: %f\n", graph->clusteringCoefficient);
	fprintf(file, "Clustering Coefficient: %f\n", graph->clusteringCoefficient);
	fclose(file);
}

//Internal Logic for calculating clustering coefficient
void calcNumEdges(Vertex *vertex)
{
	Node *neighbours = vertex->neighbours;
	int numEdges = vertex->degree;
	int i=0;
	int index1, index2;
	Vertex *neighbouringVertices[2000];
	Node *current = neighbours;

	if(numEdges==0)
		return;

	do
	{
		neighbouringVertices[i] = (Vertex *) current->data;
		current = current->next;
		i++;
	}while(current != neighbours);

	for(index1=0; index1<i; ++index1)
	{
		for(index2=index1+1; index2<i; ++index2)
		{
			Node *currentNeighbour = neighbouringVertices[index1]->neighbours;
			do
			{
				if(currentNeighbour->data == (void *) neighbouringVertices[index2])
				{
					numEdges++;
				}
				currentNeighbour = currentNeighbour->next;
			}while(currentNeighbour != neighbouringVertices[index1]->neighbours);
		}
	}
	vertex->numTotalEdgesInCluster = numEdges;
	vertex->clusteringCoefficient = (double) (numEdges*2.0)/((vertex->degree+1) * (vertex->degree));

}

//Calculate the path length
void calcPathLength(Graph *graph, char *fileName)
{
	int i,j, ii, jj;
	FILE *file  = fopen(fileName, "w");
	if(file == NULL)
	{
		printf("Error reading file!!!");
		return;
	}
	for(i=0; i<NUM_ROWS; ++i)
	{
		for(j=0; j<NUM_COLUMNS; ++j)
		{
			bfs(&graph->vertices[i][j]);
			graph->charPathLength = graph->charPathLength + graph->vertices[i][j].charPathLength;
			for(ii=0; ii<NUM_ROWS; ++ii)
			{
				for(jj=0; jj<NUM_COLUMNS; ++jj)
				{
					//graph1.vertices[i][j].charPathLength=0;
					graph->vertices[ii][jj].distFromSource=0;
					graph->vertices[ii][jj].visited=false;
				}
			}
		}
	}
	graph->charPathLength =
			(graph->charPathLength/(double) (NUM_ROWS*NUM_COLUMNS - graph->numLand - graph->numMissing));
	printf("Characteristic path Length: %f\n", graph->charPathLength);
	fprintf(file, "Characteristic path Length: %f\n", graph->charPathLength);
	fclose(file);
}

//Breadth First Search for claculating shortest paths
int bfs(Vertex *v)
{
	int i;
	int numConnectedVertices=0;
	Node *qHead = NULL;
	Node *curNeighbourNode;
	Vertex *curVertex;
	Vertex *neighbourVertex;
	Node *node;
	Node *item = malloc(sizeof(Node));
	item->data = v;
	v->visited = true;
	v->distFromSource=0;
	add(&qHead, item);

	while (qHead!=NULL)
	{
		item = del(&qHead);
		curVertex = item->data;
		curNeighbourNode = curVertex->neighbours;
		for(i=0; i<curVertex->degree; ++i)
		{
			neighbourVertex = curNeighbourNode->data;
			if(neighbourVertex->visited == false)
			{
				neighbourVertex->visited = true;
				neighbourVertex->distFromSource = curVertex->distFromSource+1;
				v->charPathLength = v->charPathLength + neighbourVertex->distFromSource;
				numConnectedVertices++;
				node = malloc(sizeof(Node));
				node->data = neighbourVertex;
				add(&qHead, node);
			}
			curNeighbourNode = curNeighbourNode->next;
		}
		free(item);
	}
	if(numConnectedVertices!=0)
		v->charPathLength = (v->charPathLength / (double) numConnectedVertices);
	return numConnectedVertices;
}
