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
#define MAX_LEN 100

//DATE datatype struct with fields related to days, months, years, hours, minutes, and seconds
typedef struct {
    //-1 = unused, signifying what to output
    int year;
    int month;
    int day;
    int hours;
    int minutes;
    int seconds;
} Date;

//Enum holding integer definitions of column datatypes
typedef enum {
    CHAR = 0,
    INTEGER = 1,
    DECIMAL = 2,
    DATE = 3,
    BOOL = 4,
} TypeEnum;

//Union allowing seamless, datatype-independent value storage within columns.
typedef union {
    char* CHAR;
    int INTEGER;
    double DECIMAL;
    Date DATE;
    int BOOL;
} ElementUnion;

//Struct used to hold values. An array of these is a column.
typedef struct {
    ElementUnion val;
    int isNULL;
} Value;

//Struct used to hold a value along with its datatype if a value is not already associated with a column.
typedef struct {
    Value value;
    TypeEnum type;
    char* colName;
} LoneValue;

//Struct for a column in a table. Consists of values, its datatype, as well as many other attributes.
typedef struct Column {
    Value* values;
    char* name;
    TypeEnum type;
    int numRows;

    int notNull;
    int autoIncrement;
    Value defaultValue;
    int isPrimaryKey;
    int hasForeignKey;

    char* fKeyName;
    struct Column** fKeyPointer;
    int fKeyIndex;
} Column;

//Struct to mimic an SQL table, containing an array of columns, as well as row and column counts.
typedef struct {
    Column* cols;
    char* name;
    int numCols;
    int numRows;
} Table;

//Struct to hold the attributes of WHERE statements, being the column name, comparison, and value.
typedef struct {
    char* searchColName;
    char* comparison;
    void* searchValue; //Can be a SELECT struct. May need searchValueType for this instead of relying on the column's type.
    //int searchValueType
} Where;

//Struct to hold the attributes of SELECT statements, being an array of selected column names, and whether or not it is a distinct selection.
typedef struct {
    int numCols;
    char** colNames; //Can include SUM(col), COUNT(col), AVG(col), MIN(col), MAX(col)
    // char** groupByCols;
    int distinct; //0 or 1
} Select;

/**
 * Direct SQL Function Simulations
**/

Table create(char* tableName, int numCols, char** colNames, int* colTypes, char** colAttrs, void** defaultValues, char** foreignKeyNames); //Implemented

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
void insertCol(Table* table, char* colName, int colType, int numValues, int* rowNums, void** values, char* colAttrs, void* defaultValue, char* foreignKeyName); //Implemented
void insertIntoCol(Table* table, char* colName, int colType, int numValues, int* rowNums, void** values, char* colAttrs, void* defaultValue, char* foreignKeyName, char* colPos); //Implemented
void deleteColumn(Table* table, char* colName); //Implemented
void deleteRow(Table* table, int rowNum); //Implemented
void deleteDuplicateValues(Column* col); //Implemented
void deleteDuplicateValRows(Table* table, int numCols, char** colNames); //Implemented
int deleteInvalidFKeyVals(Column* col); //Implemented
int getValIndex(Column col, void* value);
void sortTableByCol(Table* table, char* colName, int ascending); //Implemented

/**
 * C Types to SQL Table Types and Vice Versa
**/

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
void freeDatabase(Table* tables, int numTables); //Implemented
void freeList(void** nameList, int numNames); //Implemented
void freeWhere(Where* where); //Implemented

Table createMasterTable(Table* tableList, int numTables); //Implemented
void printTable(Table table); //Implemented
void printSeparatorLine(int numCols, int rowNum); //Implemented
void printRow(Table table, int rowIndex); //Implemented
void printLoneRow(LoneValue* row, int numValues); //Implemented
void printColumn(Column col); //Implemented
char* intToLetter(int number); //Implemented
int letterToInt(char* stringOfLetters); //Implemented

void initColAttrs(Column* col); //Implemented
void assignColAttrs(Column* col, char* attrs, void* defaultVal, char* foreignKeyName);

int* actionMenu(Table* table); //Implemented
int tableMenu(int numTables, Table* tableList); //Implemented
int whereInput(Table* currentTable, Where** whereList, char** connectiveList); //Implemented
int typeInput(void); //Implemented
char* yesnoInput(void); //Implemented
int isYes(char* yesno); //Implemented
int isNo(char* yesno); //Implemented
int colPosInput(int** colNums, int numCols); //Implemented
int rowNumInput(int** rowNums, int numRows); //Implemented
void attrInputByCol(Column* col); //Implemented
char* attrInputByType(int colType, void** defaultVal, char** foreignKeyName); //Implemented
int changeColType(Column* col, int newType); //Implemented
void printType(int type); //Implemented
void printValue(void* value, int type); //Implemented
char* typeToString(int type); //Implemented
int stringToType(char* type); //Implemented
int endsWith(char* str, char* ext); //Implemented
char* addQuotesToString(char* string); //Implemented
char* removeQuotesFromString(char* string); //Implemented
void shrinkSpaces(char** string); //Implemented

int getRowIndex(Table table, char* colName, void* value);
Table copyTable(Table table); //Implemented
Column copyColumn(Column col); //Implemented
LoneValue* copyRow(Table* currentTable, int rowNum); //Implemented

char* dateToString(Date date);
Date stringToDate(char* dateString);

int isAggregate(char* name); //Implemented
char* getAggregateName(char* name); //Implemented
char* getColNameFromAggregate(char* name); //Implemented

int verifyDelete(void); //Implemented

void checkDupTableNames(Table* tables, int numTables, char* nameToCheck, int newNameIndex); //Implemented
void checkDupColumnNames(Table table, char* nameToCheck, int newNameIndex); //Implemented
int checkInvalidName(char* name); //Implemented

void fgetsUntil(char* string, int size); //Implemented
void scanfWell(char* formSpec, void* val); //Implemented
void scanfWellNull(char* formSpec, void* val); //Implemented
void cql_sleep(int milliseconds); //Implemented
void* memdup(void* src, int numBytes);
int equalsIgnoreCase(char* string1, char* string2); //Implemented
int containsIgnoreCase(char* big, char* small); //Implemented

/**
 * Communication with SQL Language
**/

void exportTable(Table table, char* fileName, int trunc); //Implemented
Table* importTable(char* tableName, char* filename); //Implemented
int importDatabase(char* filename, Table** tables); //Implemented
int callbackCheckExists(void* value, int numCols, char** values, char** columnNames); //Implemented
int callbackPrintData(void* value, int numCols, char** values, char** columnNames); //Implemented
int callbackCreateTable(void* value, int numCols, char** values, char** colNames); //Implemented
int callbackInsertData(void* value, int numCols, char** values, char** colNames); //Implemented
int callbackGetTableNames(void* value, int numCols, char** values, char** colNames); //Implemented
int callbackGetAttributes(void* value, int numCols, char** values, char** colNames); //Implemented
int userTableOperator(int numTables, Table** tables);

/**
 * Struct and List Constructors
**/

Where newWhere(char* searchColName, char* comparison, void* searchValue); //Implemented
Select newSelect(int numCols, char** colNames, int distinct); //Implemented
char** nameList(int numNames, ...); //Implemented
int* typeList(int numTypes, ...); //Implemented
void** valueList(int numValues, int* types, ...); //Implemented
Where* whereList(int numWheres, ...); //Implemented
char* connectiveList(int numConns, ...); //Implemented
Where* notWheres(int numWheres, Where* whereList); //Implemented
char* notConnectives(int numConns, char* conns); //Implemented
