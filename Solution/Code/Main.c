
#include <stdio.h>
#include <stdlib.h>

#include "ParseData.h"
#include "LinkedList.h"
#include "DataTypes.h"
#include "Graph.h"


int main()
{
	char ch0[100]="lag0";
	char ch1[100]="lag1";
	char ch2[100]="lag2";
	char ch3[100]="lag1";
	char ch4[100]="lag4";

	char first[100]="first";
	char second[100]="second";
	char third[100]="third";

	printf("!!!!!Pass 1!!!!!!\n\n");
	printf("Initializing Graph....\n");
	initGraph(&graph1);
	initGraph(&graph2);
	printf("Parsing Data....\n");
	parseData();
	calcSxx(0, NUM_YEARS);
	printf("Creating Graph.... \n");
	createGraphFromData(0, NUM_YEARS, 0, ch0);
	printf("Calculating clustering coefficient...\n");
	calcClusteringCoefficient(&graph1, "lag0_cc_1.txt");
	calcClusteringCoefficient(&graph2, "lag0_cc_2.txt");
	printf("Calculating path length.... \n");
	calcPathLength(&graph1, "lag0_pl_1.txt");
	calcPathLength(&graph2, "lag0_pl_2.txt");

	printf("!!!!!Pass 2!!!!!!\n\n");
	printf("Initializing Graph....\n");
	initGraph(&graph1);
	initGraph(&graph2);
	printf("Parsing Data....\n");
	parseData();
	calcSxx(0, NUM_YEARS);
	printf("Creating Graph.... \n");
	createGraphFromData(0, NUM_YEARS, 1, ch1);
	printf("Calculating clustering coefficient...\n");
	calcClusteringCoefficient(&graph1, "lag1_cc_1.txt");
	calcClusteringCoefficient(&graph2, "lag1_cc_2.txt");
	printf("Calculating path length.... \n");
	calcPathLength(&graph1, "lag1_pl_1.txt");
	calcPathLength(&graph2, "lag1_pl_2.txt");

	printf("!!!!!Pass 3!!!!!!\n\n");
	printf("Initializing Graph....\n");
	initGraph(&graph1);
	initGraph(&graph2);
	printf("Parsing Data....\n");
	parseData();
	calcSxx(0, NUM_YEARS);
	printf("Creating Graph.... \n");
	createGraphFromData(0, NUM_YEARS, 2, ch2);
	printf("Calculating clustering coefficient...\n");
	calcClusteringCoefficient(&graph1, "lag2_cc_1.txt");
	calcClusteringCoefficient(&graph2, "lag2_cc_2.txt");
	printf("Calculating path length.... \n");
	calcPathLength(&graph1, "lag2_pl_1.txt");
	calcPathLength(&graph2, "lag2_pl_2.txt");

	printf("!!!!!Pass 4!!!!!!\n\n");
	printf("Initializing Graph....\n");
	initGraph(&graph1);
	initGraph(&graph2);
	printf("Parsing Data....\n");
	parseData();
	calcSxx(0, NUM_YEARS);
	printf("Creating Graph.... \n");
	createGraphFromData(0, NUM_YEARS, 3, ch3);
	printf("Calculating clustering coefficient...\n");
	calcClusteringCoefficient(&graph1, "lag3_cc_1.txt");
	calcClusteringCoefficient(&graph2, "lag3_cc_2.txt");
	printf("Calculating path length.... \n");
	calcPathLength(&graph1, "lag3_pl_1.txt");
	calcPathLength(&graph2, "lag3_pl_2.txt");

	printf("!!!!!Pass 5!!!!!!\n\n");
	printf("Initializing Graph....\n");
	initGraph(&graph1);
	initGraph(&graph2);
	printf("Parsing Data....\n");
	parseData();
	calcSxx(0, NUM_YEARS);
	printf("Creating Graph.... \n");
	createGraphFromData(0, NUM_YEARS, 4, ch4);
	printf("Calculating clustering coefficient...\n");
	calcClusteringCoefficient(&graph1, "lag3_cc_4.txt");
	calcClusteringCoefficient(&graph2, "lag3_cc_4.txt");
	printf("Calculating path length.... \n");
	calcPathLength(&graph1, "lag4_pl_1.txt");
	calcPathLength(&graph2, "lag4_pl_2.txt");

	printf("!!!!!Pass 6!!!!!!\n\n");
	printf("Initializing Graph....\n");
	initGraph(&graph1);
	initGraph(&graph2);
	printf("Parsing Data....\n");
	parseData();
	calcSxx(0, NUM_YEARS/3);
	printf("Creating Graph.... \n");
	createGraphFromData(0, NUM_YEARS/3, 0, first);
	printf("Calculating clustering coefficient...\n");
	calcClusteringCoefficient(&graph1, "first_cc_1.txt");
	calcClusteringCoefficient(&graph2, "first_cc_2.txt");
	printf("Calculating path length.... \n");
	calcPathLength(&graph1, "first_pl_1.txt");
	calcPathLength(&graph2, "first_pl_2.txt");

	printf("!!!!!Pass 7!!!!!!\n\n");
	printf("Initializing Graph....\n");
	initGraph(&graph1);
	initGraph(&graph2);
	printf("Parsing Data....\n");
	parseData();
	calcSxx(NUM_YEARS/3+1, 2*NUM_YEARS/3);
	printf("Creating Graph.... \n");
	createGraphFromData(NUM_YEARS/3+1, 2*NUM_YEARS/3, 0, second);
	printf("Calculating clustering coefficient...\n");
	calcClusteringCoefficient(&graph1, "second_cc_1.txt");
	calcClusteringCoefficient(&graph2, "second_cc_2.txt");
	printf("Calculating path length.... \n");
	calcPathLength(&graph1, "second_pl_1.txt");
	calcPathLength(&graph2, "second_pl_2.txt");

	printf("!!!!!Pass 8!!!!!!\n\n");
	printf("Initializing Graph....\n");
	initGraph(&graph1);
	initGraph(&graph2);
	printf("Parsing Data....\n");
	parseData();
	calcSxx(2*NUM_YEARS/3+1, NUM_YEARS);
	printf("Creating Graph.... \n");
	createGraphFromData(2*NUM_YEARS/3+1, NUM_YEARS, 0, third);
	printf("Calculating clustering coefficient...\n");
	calcClusteringCoefficient(&graph1, "third_cc_1.txt");
	calcClusteringCoefficient(&graph2, "third_cc_2.txt");
	printf("Calculating path length.... \n");
	calcPathLength(&graph1, "third_pl_1.txt");
	calcPathLength(&graph2, "third_pl_2.txt");
	return 0;
}


