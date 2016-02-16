
#ifndef GRAPH_H_
#define GRAPH_H_

extern Graph graph1;
extern Graph graph2;
extern HistogramData histoGram[100];

void initGraph(Graph *graph);
void addEdge(int fromRow, int fromColumn, int toRow, int toColumn, Graph *graph);
void createGraphFromData(int startYear, int stopYear, int timeLag, char *fileName);
void calcHistogram(Graph *graph, HistogramData *histoGram, char *fileName);
void calcClusteringCoefficient(Graph *graph, char *fileName);
void calcNumEdges(Vertex *vertex);
void calcPathLength(Graph *graph, char *fileName);
int bfs(Vertex *v);
#endif /* GRAPH_H_ */
