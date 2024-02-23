#include "sqllib.h"

int main(int argc, char const* argv[]) {

    Table table = create("My Table", 3, "Char Col", CHAR, "Decimal Col", DECIMAL, "Integer Col", INTEGER);
    printTable(table);

    insert(&table, 2, "Decimal Col", 44.55, "Char Col", "Luigi");
    printTable(table);
    insert(&table, 1, "Char Col", "Mario");
    printTable(table);

    insert(&table, 1, "Integer Col", 4);
    insert(&table, 3, "Integer Col", 44, "Decimal Col", 88.77, "Char Col", "WAHHLUIGI");
    printTable(table);

    Where where1 = newWhere("Char Col", "==", "Luigi");
    double newNum = 9999.999;


    update(&table, "Decimal Col", &newNum, 1, where1);
    printTable(table);

    newNum = 0;
    Where where2 = newWhere("Decimal Col", "==", &newNum);

    int newInt = 1735;

    update(&table, "Integer Col", &newInt, 2, where1, '&', where2);
    printTable(table);

    Where where3 = newWhere("Char Col", "==", "NULL");
    // update(&table, "Char Col", "WAAAAARIOOOOOOO", 1, where3);
    printTable(table);

    insert(&table, 1, "Decimal Col", 444.0);

    printTable(table);
    newInt = 666;
    update(&table, "Integer Col", &newInt, 3, where3, '&', where2, '|', where1);
    printTable(table);

    Where where4 = newWhere("Integer Col", "==", &newInt);
    update(&table, "Char Col", "WAAAAARIOOOOOO", 2, where3, '&', where4);
    printTable(table);

    // where3.comparison = "<>";

    // update(&table, "Char Col", "Peach", 1, where3);
    // printTable(table);

    double dec = 444.0;

    Where where5 = newWhere("Char Col", "==", "WAAAAARIOOOOOO");
    Where where6 = newWhere("Decimal Col", ">", &dec);
    Where where7 = newWhere("Decimal Col", "==", &dec);
    Where where8 = newWhere("Integer Col", "==", &newNum);
    where1.comparison = "!=";
    delete(&table, 7, where5, '|', where3, '&', where6, '|', where4, '|', where1, '&', where7, '&', where8);

    // deleteAll(&table);
    printTable(table);

    return 0;
}

/**
 * Format: create(char *tableName, int numCols, char *col1Name, int col1Type, char *col2Name, ...)
 * SQL Origin:
 *  CREATE tableName (col1Name col1Type, col2Name col2Type, ...)
*/
Table create(char* tableName, int numCols, ...) {

    va_list ap;
    Table table;

    table.name = strdup(tableName);
    table.cols = malloc(sizeof(Column) * numCols);

    va_start(ap, numCols);

    for(int i = 0; i < numCols; i++) {
        table.cols[i].name = strdup(va_arg(ap, char*));
        table.cols[i].type = va_arg(ap, int);
    }

    va_end(ap);

    table.numCols = numCols;
    table.numRows = 0;

    return table;

}

/**
 * Format: insert(Table *table, int numValues, char *col1Name, void *value1, char *col2Name, ...)
 * SQL Origin:
 *  INSERT
 *   INTO tableName(col1Name, col2Name, ...)
 *   VALUES (val1, val2, ...)
*/
void insert(Table* table, int numValues, ...) {

    if(numValues > table->numCols) {
        printf("Error: To many arguments provided. Insertion failed.\n");
        return;
    }

    va_list ap;
    table->numRows++;
    char* colName = "";
    Column currCol;

    va_start(ap, numValues);

    for(int i = 0; i < table->numCols; i++) {
        table->cols[i].values = realloc(table->cols[i].values, sizeof(Column) * table->numRows);
        if(table->cols[i].type == CHAR)
            table->cols[i].values[table->numRows - 1].CHAR = "NULL";
        else if(table->cols[i].type == INTEGER)
            table->cols[i].values[table->numRows - 1].INTEGER = 0;
        else if(table->cols[i].type == DECIMAL)
            table->cols[i].values[table->numRows - 1].DECIMAL = 0.0;
    }

    for(int i = 0; i < numValues; i++) {
        colName = strdup(va_arg(ap, char*));
        currCol = nameToCol(table, colName);

        if(currCol.type == CHAR)
            currCol.values[table->numRows - 1].CHAR = va_arg(ap, char*);
        else if(currCol.type == INTEGER)
            currCol.values[table->numRows - 1].INTEGER = va_arg(ap, int);
        else if(currCol.type == DECIMAL)
            currCol.values[table->numRows - 1].DECIMAL = va_arg(ap, double);
        else {
            printf("Error: Nonexistent column name, \"%s\", provided.\n", colName);
            va_arg(ap, void*);
        }

        free(colName);
    }

    va_end(ap);
}

/**
 * Format: update(Table* table, char* colName, void* newValue, int numConds, Where where1, char connective1, Where where2, ...)
 * (Accepted connectives being '&' or '|' meaning AND or OR)
 * SQL Origin:
 *  UPDATE tableName
 *   SET colName = newValue
 *   WHERE tableName.whereColName =, >, <, >=, <=, != whereValue
*/
void update(Table* table, char* colName, void* newValue, int numConds, ...) {
    va_list ap;

    va_start(ap, numConds);

    Column column = nameToCol(table, colName);
    Where currentWhere;
    char currConnect = '\0';

    int toUpdate[table->numRows];
    for(int i = 0; i < table->numRows; i++) {
        toUpdate[i] = 1;
    }

    for(int i = 0; i < numConds; i++) {
        currentWhere = va_arg(ap, Where);
        for(int j = 0; j < table->numRows; j++) {
            if(currConnect == '&' || currConnect == 'a' || currConnect == 'A') {
                if(toUpdate[j] == 1 && !compare(nameToCol(table, currentWhere.searchColName), j, currentWhere.comparison, currentWhere.searchValue)) {
                    toUpdate[j] = 0;
                }
            }
            else if(currConnect == '|' || currConnect == 'o' || currConnect == 'O') {
                if(toUpdate[j] == 1) {
                    if(column.type == CHAR)
                        column.values[j].CHAR = (char*)newValue;
                    else if(column.type == INTEGER)
                        column.values[j].INTEGER = *((int*)newValue);
                    else if(column.type == DECIMAL)
                        column.values[j].DECIMAL = *((double*)newValue);

                    return;
                }

                if(toUpdate[j] == 0 && compare(nameToCol(table, currentWhere.searchColName), j, currentWhere.comparison, currentWhere.searchValue)) {
                    toUpdate[j] = 1;
                }
            }
            else if(currConnect == '\0') {
                if(!compare(nameToCol(table, currentWhere.searchColName), j, currentWhere.comparison, currentWhere.searchValue))
                    toUpdate[j] = 0;
            }
            else {
                printf("Error: Invalid where connective '%c' provided into update function.", currConnect);
            }
            if(i == numConds - 1 && toUpdate[j] == 1) {
                if(column.type == CHAR)
                    column.values[j].CHAR = (char*)newValue;
                else if(column.type == INTEGER)
                    column.values[j].INTEGER = *((int*)newValue);
                else if(column.type == DECIMAL)
                    column.values[j].DECIMAL = *((double*)newValue);
            }

        }
        if(i < numConds - 1) {
            currConnect = va_arg(ap, int);
        }
    }

}

/**
 * Format: delete(Table* table, int numConds, Where where1, char connective1, Where where2, ...)
 * SQL Origin:
 *  DELETE
 *   FROM tableName
 *   WHERE tableName.whereColName =, >, <, >=, <=, != whereValue
*/
void delete(Table* table, int numConds, ...) {
    va_list ap;

    va_start(ap, numConds);

    Where currentWhere;
    char currConnect = '\0';
    int* prevGoodJs;
    int numPrevGoodJs;

    int toDelete[table->numRows];
    for(int i = 0; i < table->numRows; i++)
        toDelete[i] = 1;

    for(int i = 0; i < numConds; i++) {
        currentWhere = va_arg(ap, Where);
        prevGoodJs = malloc(sizeof(int));
        numPrevGoodJs = 0;
        for(int j = 0; j < table->numRows; j++) {
            switch(currConnect) {
                case '&':
                case 'a':
                case 'A':
                    if(toDelete[j] == 1 && !compare(nameToCol(table, currentWhere.searchColName), j, currentWhere.comparison, currentWhere.searchValue))
                        toDelete[j] = 0;
                    break;
                case '|':
                case 'o':
                case 'O':
                    toDelete[j] = 1;
                case '\0':
                    if(!compare(nameToCol(table, currentWhere.searchColName), j, currentWhere.comparison, currentWhere.searchValue))
                        toDelete[j] = 0;
                    break;
                default:
                    printf("Error: Invalid where connective '%c' provided into delete function.", currConnect);
                    break;
            }

            if(toDelete[j] == 1) {
                prevGoodJs = realloc(prevGoodJs, sizeof(int) * (++numPrevGoodJs));
                prevGoodJs[numPrevGoodJs - 1] = j;
            }

        }
        if(i < numConds - 1)
            currConnect = va_arg(ap, int);

        if((((currConnect == '|' || currConnect == 'o' || currConnect == 'O')) || (i == numConds - 1)) && (numPrevGoodJs > 0 && numPrevGoodJs <= table->numRows)) {
            for(int k = 0; k < numPrevGoodJs; k++) {
                for(int l = 0; l < table->numCols; l++)
                    table->cols[l].values[prevGoodJs[k]] = table->cols[l].values[table->numRows - 1];
                table->numRows--;
            }
        }
        free(prevGoodJs);
    }

    if(numConds <= 0)
        table->numRows = 0;
}

void deleteAll(Table* table) {
    table->numRows = 0;
}

Column nameToCol(Table* table, char* colName) {

    for(int i = 0; i < table->numCols; i++)
        if(strcmp(table->cols[i].name, colName) == 0)
            return table->cols[i];

    Column errCol;
    errCol.name = "COL NOT FOUND";
    errCol.type = -1;
    printf("Error: Failed to find column '%s'\n", colName);

    return errCol;
}

int compare(Column column, int valIndex, char* comparison, void* value) {
    if(strcmp(comparison, "=") == 0 || strcmp(comparison, "==") == 0) {
        if(column.type == CHAR)
            return strcmp(column.values[valIndex].CHAR, (char*)value) == 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].INTEGER == *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].DECIMAL == *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, "<") == 0) {
        if(column.type == CHAR)
            return strcmp(column.values[valIndex].CHAR, (char*)value) < 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].INTEGER < *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].DECIMAL < *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, "<=") == 0) {
        if(column.type == CHAR)
            return strcmp(column.values[valIndex].CHAR, (char*)value) <= 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].INTEGER <= *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].DECIMAL <= *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, ">") == 0) {
        if(column.type == CHAR)
            return strcmp(column.values[valIndex].CHAR, (char*)value) > 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].INTEGER > *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].DECIMAL > *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, ">=") == 0) {
        if(column.type == CHAR)
            return strcmp(column.values[valIndex].CHAR, (char*)value) >= 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].INTEGER >= *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].DECIMAL >= *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, "<>") == 0 || strcmp(comparison, "!=") == 0) {
        if(column.type == CHAR)
            return strcmp(column.values[valIndex].CHAR, (char*)value) != 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].INTEGER != *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].DECIMAL != *((double*)value);
        else
            return 0;
    }
    else {
        printf("Error: Invalid comparison entered.\n");
        return 0;
    }

}

Where newWhere(char* searchColName, char* comparison, void* searchValue) {
    Where newWhere;
    newWhere.searchColName = strdup(searchColName);
    newWhere.comparison = strdup(comparison);
    // newWhere.searchValue = malloc(sizeof(void*));
    // memcpy(newWhere.searchValue, searchValue, strlen(searchValue));
    newWhere.searchValue = searchValue;

    return newWhere;
}

void printTable(Table table) {

    printf("\nTABLE:\n\t\t%s\n\nCOLUMNS:\n\t   ", table.name);
    char printString[50];

    for(int i = 0; i < table.numCols; i++)
        printf("%-25s", table.cols[i].name);

    for(int i = 0; i < table.numRows; i++) {
        printf("\n\t");
        for(int j = 0; j < table.numCols; j++) {
            if(table.cols[j].type == CHAR) {
                sprintf(printString, "    [ %s ]", table.cols[j].values[i].CHAR);
                printf("%-25s", printString);
            }
            else if(table.cols[j].type == INTEGER) {
                sprintf(printString, "    [ %d ]", table.cols[j].values[i].INTEGER);
                printf("%-25s", printString);
            }
            else if(table.cols[j].type == DECIMAL) {
                sprintf(printString, "    [ %.3lf ]", table.cols[j].values[i].DECIMAL);
                printf("%-25s", printString);
            }
        }
    }

    printf("\n");
}
