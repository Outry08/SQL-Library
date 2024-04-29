#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sqlite3.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define MAX_LEN 50

typedef struct {
    int year;
    int month;
    int day;
    int hours;
    int minutes;
    int seconds;
} Date;

typedef enum {
    vNULL = -1,
    CHAR = 0,
    INTEGER = 1,
    DECIMAL = 2,
    DATE = 3,
} TypeEnum;

typedef union {
    char* CHAR;
    int INTEGER;
    double DECIMAL;
    Date DATE;
    TypeEnum type;
} ElementUnion;

// typedef struct {
//     ElementUnion val;
//     TypeEnum type;
// } Value;

typedef struct {
    ElementUnion* values;
    char* name;
    TypeEnum type;
    // int notNull; //0 or 1 //take user input along with column name, ask for '-nn' right after the name.
    // int primaryKey; //0 or 1 //take user input along with column name, ask for '-p' right after the name.
    // int foreign key; //0 or 1 //take user input along with column name, ask for '-f' right after the name.
    // int chained key; //0 or 1; the pointer is shared among multiple tables so that simultaneous updates aren't needed.
} Column;

typedef struct {
    Column* cols;
    char* name;
    int numCols;
    int numRows;
    int selected;
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

Table select(Table table, Select select, int numWheres, Where* wheres, char* conns); //Implemented
Table selCreate(Table baseTable, int numCols, char** colNames); //Implemented
Table joinSelect(Table* tables, int numTables, Select select, int numWheres, Where* wheres, char* conns);

void insertRow(Table* table, int numValues, char** colNames, void** values); //Implemented

void update(Table* table, int numUpdCols, char** colNames, void* newValue, int numWheres, Where* wheres, char* conns); //Implemented
void delete(Table* table, int numWheres, Where* wheres, char* conns); //Implemented

/**
 * More C-Like Functions for Table Operations
**/
void chackDupNames(Table* tableList);
void insertIntoRow(Table* table, int numValues, char** colNames, void** values, int rowNum); //Implemented
void insertCol(Table* table, char* colName, int colType, int numValues, int* rowNums, void** values); //Implemented
void insertIntoCol(Table* table, char* colName, int colType, int numValues, int* rowNums, void** values, char* colPos); //Implemented
void deleteColumn(Table* table, char* colName);
int getValIndex(Column col, void* value);
void swapRows(Table* table, int index1, int index2);
void swapCols(Table* table, char* colName1, int colName2);

/**
 * C Types to SQL Table Types and Vice Versa
*/
Column arrayToCol(char* colName, void** arr);
Table matrixToTable(void** matrix, char* tableName, char** colNames, int type);
void matrixToSQL(void** matrix, int type, char* filename);
void** rowToArray(void);
void** colToArray(void);
void** tableToMatrix(void);

/**
 * Helper Functions
**/
Column nameToCol(Table* table, char* colName); //Implemented

int compare(Column column, int valIndex, char* comparison, void* value); //Implemented
char* oppComp(char* comparison); //Implemented
void deleteAll(Table* table); //Implemented
void freeTable(Table* table);

void printTable(Table table); //Implemented
void printTableRow(int numCols, int rowNum); //Implemented
char* intToLetter(int number); //Implemented
int letterToInt(char* stringOfLetters); //Implemented
int* actionMenu(Table* table); //Implemented
int tableMenu(int numTables, Table* tableList); //Implemented
int whereInput(Table* currentTable, Where** whereList, char** connectiveList); //Implemented
int typeInput(void); //Implemented
void printType(int type); //Implemented

int getRowIndex(Table table, char* colName, void* value);
Table copyTable(Table table); //Implemented
Column copyColumn(int numVals, Column col); //Implemented

char* dateToString(Date date);
Date stringToDate(char* dateString);

int isAggregate(char* name); //Implemented
char* getAggregateName(char* name); //Implemented

void fgetsUntil(char* string, int size); //Implemented
void scanfWell(char* formSpec, void* val); //Implemented
void sleep(int milliseconds); //Implemented
void* memdup(void* src, int numBytes);

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
