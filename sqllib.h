#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef union {
    char* CHAR;
    int INTEGER;
    double DECIMAL;
} ElementUnion;

typedef enum {
    CHAR = 0,
    INTEGER = 1,
    DECIMAL = 2,
} TypeEnum;

typedef struct {
    ElementUnion* values;
    char* name;
    TypeEnum type;
} Column;

typedef struct {
    Column* cols;
    char* name;
    int numCols;
    int numRows;
} Table;

typedef struct {
    char* searchColName;
    char* comparison;
    void* searchValue;
} Where;

Table create(char* tableName, int numCols, ...); //Implemented
//... --> char *col1Name, ...

Table select(char* colName, Table table, int distinct);
Table selectWhere(char* colName, Table table, int distinct, int numConds, ...);
//... --> Where where1, char &/|, Where where2, ...

void insert(Table* table, int numValues, ...); //Implemented
//... --> char *col1Name, void *value1, ...
void update(Table* table, char* colName, void* newValue, int numConds, ...); //Implemented
//... --> Where where1, char* AND/OR, Where where2, ...
void delete(Table* table, int numConds, ...);
//... --> Where where1, char* AND/OR, Where where2, ...
void deleteAll(Table* table);
void freeTable(Table* table);

void addColumn(Table* table, char* colName);
Column nameToCol(Table* table, char* colName); //Implemented

void printTable(Table table); //Implemented
void exportString(Table table);
void exportSQL(Table table, char* filename);
Table importTable(char* filename);
int compare(Column column, int valIndex, char* comparison, void* value); //Implemented
Where newWhere(char* searchColName, char* comparison, void* searchValue); //Implemented

Table matrixToTable(void** matrix, char* tableName, char** colNames, int type);
void matrixToSQL(void** matrix, int type, char* filename);

//Perhaps change to add ... parameters to these functions instead of using arrays of elements and columns.
//Need stdarg.h for this
