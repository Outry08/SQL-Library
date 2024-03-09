//CQL Name
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sqlite3.h>
#include <time.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int year;
    int month;
    int day;
    int hours;
    int minutes;
    int seconds;
} Date;

typedef union {
    char* CHAR;
    int INTEGER;
    double DECIMAL;
    Date DATE;
} ElementUnion;

typedef enum {
    // cNULL = -1,
    CHAR = 0,
    INTEGER = 1,
    DECIMAL = 2,
    DATE = 3,
} TypeEnum;

typedef struct {
    ElementUnion* values;
    char* name;
    TypeEnum type;
    // int notNull; //0 or 1
    // int primaryKey; //0 or 1
    // int foreign key; //0 or 1
    // int chained key; //0 or 1; the pointer is shared among multiple tables so that simultaneous updates aren't needed.
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

/**
 * Direct SQL Function Simulations
**/
//Primary Keys, Foreign Keys, NOT NULL, and AUTOINCREMENT are something yet to be added.
//Primary keys use hashtables in SQL, so we could do that here too.
Table create(char* tableName, int numCols, char** colNames, int* colTypes); //Implemented

Table select(Table table, Select select, int numWheres, Where* wheres, char* conns);
Table selCreate(Table baseTable, int numCols, char** colNames); //Implemented
Table joinSelect(Table* tables, int numTables, Select select, int numWheres, Where* wheres, char* conns);

void insert(Table* table, int numValues, char** colNames, void** values); //Implemented
//... --> char *col1Name, void *value1, ...
void update(Table* table, char* colName, void* newValue, int numWheres, Where* wheres, char* conns);
void delete(Table* table, int numWheres, Where* wheres, char* conns); //Implemented

/**
 * More C-Like Functions for Table Operations
**/
void addColumn(Table* table, char* colName, int colType);
void deleteColumn(Table* table, char* colName);
int getValIndex(Column col, void* value);

/**
 * C Types to SQL Table Types and Vice Versa
*/
Column arrayToCol(char* colName, void** arr);
Table matrixToTable(void** matrix, char* tableName, char** colNames, int type);
void matrixToSQL(void** matrix, int type, char* filename);
void** rowToArray();
void** colToArray();
void** tableToMatrix();

/**
 * Helper Functions
**/
Column nameToCol(Table* table, char* colName); //Implemented

int compare(Column column, int valIndex, char* comparison, void* value); //Implemented
char* oppComp(char* comparison); //Implemented
void deleteAll(Table* table); //Implemented
void freeTable(Table* table); //I fear valgrind

void printTable(Table table); //Implemented
void printTableRow(int numCols); //Implemented
int printActionMenu(Table* table);
int printTableMenu(int numTables, Table* tableList);
int whereInput(Table* currentTable, Where** whereList, char** connectiveList);
int printTypeChart(int colNum);

int getRowIndex(Table table, char* colName, void* value);
Column copyColumn(int numVals, Column col);

char* dateToString(Date date);
Date stringToDate(char* dateString);

int isAggregate(char* name);
char* getAggregateName(char* name);

void fgetsUntil(char* string, int size);
void sleep(int milliseconds);

/**
 * Communication with SQL Language
**/
void exportString(Table table);
void exportSQL(Table table, char* filename);
Table importTable(char* filename);
Table* userTableOperator(int numTables, Table* tables);

/**
 * Struct and List Constructors
**/
Where newWhere(char* searchColName, char* comparison, void* searchValue); //Implemented
Select newSelect(int numCols, char** colNames, char** orderByCols, char** groupByCols, int distinct); //Implemented
char** nameList(int numNames, ...); //Implemented
int* typeList(int numTypes, ...); //Implemented
void** valueList(int numValues, int* types, ...); //Implemented
Where* whereList(int numWheres, ...); //Implemented
char* connectiveList(int numConns, ...); //Implemented
Where* notWheres(int numWheres, Where* whereList); //Implemented
char* notConnectives(int numConns, char* conns); //Implemented
