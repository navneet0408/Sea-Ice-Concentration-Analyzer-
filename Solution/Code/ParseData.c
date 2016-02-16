
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ParseData.h"


float seaIceConc[NUM_ROWS][NUM_COLUMNS][NUM_YEARS][NUM_WEEKS];
double sxx[NUM_ROWS][NUM_COLUMNS];
int numLand=0;
int numMissing=0;

/* Function to read data from input files and store it in array */
//Can read either of the big data or small data...
void parseData()
{
	int res;
	int year, week, x, y;

	for(year=START_YEAR; year<=END_YEAR;++year)
	{
		for(week=1; week<=52; ++week)
		{
			char *fileName = (char *)malloc(255*sizeof(char));
			getFileName(fileName, week, year);
//			getFileName_small(fileName, week, year);
			FILE *file  = fopen(fileName, "r");
			if(file == NULL)
			{
				printf("Error reading file!!!");
				return;
			}

			for(x=0; x<NUM_ROWS; ++x)
			{
				for(y=0; y<NUM_COLUMNS; ++y)
				{
					res = fread(&seaIceConc[x][y][year-START_YEAR][week-1], sizeof(float), 1, file);
					if(res!=1)
					{
						printf("Error reading file!!!\n");
						return;
					}

					if(seaIceConc[x][y][year-START_YEAR][week-1]==168)
					{
						numLand++;
					}
					else if(seaIceConc[x][y][year-START_YEAR][week-1]==157)
					{
						numMissing++;
					}
				}
			}

			fclose(file);
			free(fileName);
		}
	}
	numLand = numLand/(NUM_WEEKS*NUM_YEARS);
	numMissing = numMissing/(NUM_WEEKS*NUM_YEARS);
}

/*	Function to get the file names */
void getFileName(char *fileName, int week, int year)
{
	strcpy(fileName, "with_landmask/");
	const char *mid 	= "/diff";
	const char *suffix	= "+landmask";
	char yearInAscii[5];
	char weekInAscii[3];
	sprintf(yearInAscii, "%04d", year);
	sprintf(weekInAscii, "%02d", week);
	strcat(fileName, yearInAscii);
	strcat(fileName, mid);
	strcat(fileName, "w");
	strcat(fileName, weekInAscii);
	strcat(fileName, "y");
	strcat(fileName, yearInAscii);
	strcat(fileName, suffix);

}

//Optimization: Calculate SXX during the parsing of data
void calcSxx(int startYear, int stopYear)
{
	int year, week, x, y;
	for(x=0; x<NUM_ROWS; ++x)
	{
		for(y=0; y<NUM_COLUMNS; ++y)
		{
			sxx[x][y]=0;
			for(year=startYear; year<stopYear;++year)
			{
				for(week=0; week<NUM_WEEKS; ++week)
				{
					sxx[x][y] = sxx[x][y] +	seaIceConc[x][y][year][week] * seaIceConc[x][y][year][week];
				}
			}
		}
	}
}

//Get file name for small data set
void getFileName_small(char *fileName, int week, int year)
{
	strcpy(fileName, "CS310_project_subregion/");
	const char *mid 	= "/Beaufort_Sea_diff";
	const char *suffix	= "+landmask";
	char yearInAscii[5];
	char weekInAscii[3];
	sprintf(yearInAscii, "%04d", year);
	sprintf(weekInAscii, "%02d", week);
	strcat(fileName, yearInAscii);
	strcat(fileName, mid);
	strcat(fileName, "w");
	strcat(fileName, weekInAscii);
	strcat(fileName, "y");
	strcat(fileName, yearInAscii);
	strcat(fileName, suffix);

}
