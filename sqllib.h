#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sqlite3.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <unistd.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) > (b) ? (b) : (a))
#define MAX_LEN 50

typedef struct {
    //-1 = unused, signifying what to output
    int year;
    int month;
    int day;
    int hours;
    int minutes;
    int seconds;
} Date;

typedef enum {
    CHAR = 0,
    INTEGER = 1,
    DECIMAL = 2,
    DATE = 3,
    BOOL = 4,
} TypeEnum;

typedef union {
    char* CHAR;
    int INTEGER;
    double DECIMAL;
    Date DATE;
    int BOOL;
} ElementUnion;

typedef struct {
    ElementUnion val;
    int isNULL;
} Value;

typedef struct {
    Value value;
    TypeEnum type;
    char* colName;
} LoneValue;

typedef struct {
    Value* values;
    char* name;
    TypeEnum type;
    // int notNull; //0 or 1 //take user input along with column name, ask for '-nn' right after the name.
    // int primaryKey; //0 or 1 //take user input along with column name, ask for '-p' right after the name.
    // int foreignKey; //0 or 1 //take user input along with column name, ask for '-f' right after the name.
    // int chainedKey; //0 or 1 //the pointer is shared among multiple tables so that simultaneous updates aren't needed.
    // Value defaultValue; 
    // int unique; //0 or 1 //If duplicate values are allowed or not.
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
//Primary keys use hashtables in SQL, so could do that here too.
Table create(char* tableName, int numCols, char** colNames, int* colTypes); //Implemented

Table cql_select(Table table, Select select, int numWheres, Where* wheres, char* conns); //Implemented
Table selCreate(Table baseTable, int numCols, char** colNames); //Implemented
Table joinSelect(Table* tables, int numTables, Select select, int numWheres, Where* wheres, char* conns);

void insertRow(Table* table, int numValues, char** colNames, void** values); //Implemented

void update(Table* table, int numUpdCols, char** colNames, void** newValues, int numWheres, Where* wheres, char* conns); //Implemented
void delete(Table* table, int numWheres, Where* wheres, char* conns); //Implemented

/**
 * More C-Like Functions for Table Operations
**/
void chackDupNames(Table* tableList);
void insertIntoRow(Table* table, int numValues, char** colNames, void** values, int rowNum); //Implemented
void insertCol(Table* table, char* colName, int colType, int numValues, int* rowNums, void** values); //Implemented
void insertIntoCol(Table* table, char* colName, int colType, int numValues, int* rowNums, void** values, char* colPos); //Implemented
void deleteColumn(Table* table, char* colName); //Implemented
void deleteRow(Table* table, int rowNum); //Implemented
int getValIndex(Column col, void* value);
void sortTableByCol(Table* table, char* colName, int ascending);


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
Column nameToCol(Table* table, char* colName, int* colIndex); //Implemented
int containsCol(Table table, char* colName); //Implemented

int compare(Column column, int valIndex, char* comparison, void* value); //Implemented
char* oppComp(char* comparison); //Implemented
void freeTable(Table* table); //Implemented

Table createMasterTable(Table* tableList, int numTables); //Implemented
void printTable(Table table); //Implemented
void printSeparatorLine(int numCols, int rowNum); //Implemented
void printRow(Table table, int rowIndex); //Implemented
void printLoneRow(LoneValue* row, int numValues); //Implemented
void printColumn(Column col, int numValues); //Implemented
char* intToLetter(int number); //Implemented
int letterToInt(char* stringOfLetters); //Implemented

int* actionMenu(Table* table); //Implemented
int tableMenu(int numTables, Table* tableList); //Implemented
int whereInput(Table* currentTable, Where** whereList, char** connectiveList); //Implemented
int typeInput(void); //Implemented
int colPosInput(int** colNums, int numCols); //Implemented
int rowNumInput(int** rowNums, int numRows); //Implemented
void printType(int type); //Implemented
char* typeToString(int type); //Implemented
int stringToType(char* type); //Implemented
int endsWith(char* str, char* ext); //Implemented
void checkCharacters(char* string); //Implemented

int getRowIndex(Table table, char* colName, void* value);
Table copyTable(Table table); //Implemented
Column copyColumn(int numVals, Column col); //Implemented
LoneValue* copyRow(Table* currentTable, int rowNum); //Implemented

char* dateToString(Date date);
Date stringToDate(char* dateString);

int isAggregate(char* name); //Implemented
char* getAggregateName(char* name); //Implemented

int verifyDelete(void); //Implemented

void checkTableNames(Table* tables, int numTables, char* nameToCheck, int newNameIndex); //Implemented
void checkColumnNames(Table table, char* nameToCheck, int newNameIndex); //Implemented

void fgetsUntil(char* string, int size); //Implemented
void scanfWell(char* formSpec, void* val); //Implemented
void cql_sleep(int milliseconds); //Implemented
void* memdup(void* src, int numBytes);

/**
 * Communication with SQL Language
**/
void exportTable(Table table, char* fileName, int trunc);
Table* importTable(char* tableName, char* filename);
int importDatabase(char* filename, Table** tables);
int callbackCheckExists(void* value, int numCols, char** values, char** columnNames);
int callbackPrintData(void* value, int numCols, char** values, char** columnNames);
int callbackCreateTable(void* value, int numCols, char** values, char** colNames);
int callbackInsertData(void* value, int numCols, char** values, char** colNames);
int callbackGetTableNames(void* value, int numCols, char** values, char** colNames);
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
