
#ifndef DATATYPES_H_
#define DATATYPES_H_

#include "ParseData.h"

typedef struct Edge_t Edge;
typedef struct Node_t Node;
typedef struct Vertex_t Vertex;
typedef enum Boolean_t {false, true} Boolean;

//Data Structure To store Edges
typedef struct Edge_t
{
	Vertex 			*edgeFrom;
	Vertex 			*edgeTo;
} Edge;

//Data Structure for Linked List
typedef struct Node_t
{
	struct Node_t 	*previous;
	struct Node_t	*next;
	void 			*data;
} Node;

//Data Structure For Vertex Attributes
typedef struct Vertex_t
{
	int 	row;
	int 	column;
	Node 	*edges;
	Node	*neighbours;
	int 	degree;
	int 	numTotalEdgesInCluster;
	int		distFromSource;
	double	clusteringCoefficient;
	double	charPathLength;
	double	sxx;
	Boolean visited;
} Vertex;

//Data Structure for Graphs
typedef struct Graph_t
{
	Vertex 	vertices[NUM_ROWS][NUM_COLUMNS];
	Node 	*edges;
	int 	numEdges;
	int		numVertices;
	int		numLand;
	int 	numMissing;
	double	clusteringCoefficient;
	double	charPathLength;
} Graph;

//Data Structure to store hsitogram
typedef struct HistogramData_t
{
	int 	degree;
	int		numVertices;
	Node 	*vertices;
} HistogramData;

#endif /* DATATYPES_H_ */
