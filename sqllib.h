#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

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

//Possinly add BETWEEN functionality to this struct? As an allowed comparion?
typedef struct {
    char* searchColName;
    char* comparison;
    void* searchValue; //Can be a SELECT struct. May need searchValueType for this instead of relying on the column's type.
    //int searchValueType
} Where;

typedef struct {
    int numCols;
    char** colNames; //Can include SUM(col), COUNT(col), AVG(col), MIN(col), MAX(col), AS newCol
    char** orderByCols; //Can include ASC or DESC
    char** groupByCols;
    int distinct; //0 or 1
} Select;

//Primary and Foreign Keys are something yet to be added.
//Primary keys use hashtables in SQL, so we could do that here too.
Table create(char* tableName, int numCols, ...); //Implemented
//... --> char *col1Name, int col1Type, ...

Table select(Table table, Select select, int numWheres, Where* wheres, char* conns);
Table selCreate(Table baseTable, int numCols, char** colNames); //Implemented

void insert(Table* table, int numValues, ...); //Implemented
//... --> char *col1Name, void *value1, ...
void update(Table* table, char* colName, void* newValue, int numWheres, Where* wheres, char* conns);
void delete(Table* table, int numWheres, Where* wheres, char* conns); //Implemented
void deleteAll(Table* table); //Implemented
void freeTable(Table* table);

void addColumn(Table* table, char* colName, int colType);
Column nameToCol(Table* table, char* colName); //Implemented
Column arrayToCol(char* colName, void** arr);

void printTable(Table table); //Implemented
void exportString(Table table);
void exportSQL(Table table, char* filename);
Table importTable(char* filename);
int compare(Column column, int valIndex, char* comparison, void* value); //Implemented
char* oppComp(char* comparison); //Implemented

Where newWhere(char* searchColName, char* comparison, void* searchValue); //Implemented
Select newSelect(int numCols, char** colNames, char** orderByCols, char** groupByCols, int distinct); //Implemented
char** nameList(int numNames, ...); //Implemented
Where* whereList(int numWheres, ...); //Implemented
char* connectiveList(int numConns, ...); //Implemented
Where* notWheres(int numWheres, Where* whereList); //Implemented
char* notConnectives(int numConns, char* conns); //Implemented

Table matrixToTable(void** matrix, char* tableName, char** colNames, int type);
void matrixToSQL(void** matrix, int type, char* filename);
