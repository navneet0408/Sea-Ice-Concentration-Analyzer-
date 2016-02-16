
#ifndef PARSEDATA_H_
#define PARSEDATA_H_

//Defines for big data and small data

#define NUM_ROWS 		448
#define NUM_COLUMNS 	304
#define NUM_YEARS		27
#define NUM_WEEKS		52

#define START_YEAR		1979
#define END_YEAR		2005

//#define NUM_ROWS 		63
//#define NUM_COLUMNS 	63
//#define NUM_YEARS		16
//#define NUM_WEEKS		52
//
//#define START_YEAR	1990
//#define END_YEAR		2005


extern float seaIceConc[NUM_ROWS][NUM_COLUMNS][NUM_YEARS][NUM_WEEKS];
extern int numLand;
extern int numMissing;
extern double sxx[NUM_ROWS][NUM_COLUMNS];
void parseData();
void calcSxx(int startYear, int stopYear);
void getFileName_small(char *fileName, int week, int year);
void getFileName(char *fileName, int week, int year);

#endif /* PARSEDATA_H_ */
