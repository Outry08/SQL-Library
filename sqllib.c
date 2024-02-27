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


    update(&table, "Decimal Col", &newNum, 1, whereList(1, where1), connectiveList(0));
    printTable(table);

    newNum = 0;
    Where where2 = newWhere("Decimal Col", "==", &newNum);

    int newInt = 1735;

    update(&table, "Integer Col", &newInt, 2, whereList(2, where1, where2), connectiveList(1, '|'));
    printTable(table);

    Where where3 = newWhere("Char Col", "==", "NULL");
    update(&table, "Char Col", "WAAAAARIOOOOOOO", 1, whereList(1, where3), connectiveList(0));
    printTable(table);

    insert(&table, 1, "Decimal Col", 444.0);

    printTable(table);
    newInt = 666;

    update(&table, "Integer Col", &newInt, 3, whereList(3, where3, where2, where1), connectiveList(2, '&', '|'));
    printTable(table);

    Where where4 = newWhere("Integer Col", "==", &newInt);
    update(&table, "Char Col", "WAAAAAAAAAAAAAAARIOOOOOO", 2, whereList(2, where3, where4), connectiveList(1, '&'));
    printTable(table);

    where3.comparison = "==";

    update(&table, "Char Col", "Peach", 1, whereList(1, where3), connectiveList(0));
    printTable(table);

    double dec = 444.0;

    Where where5 = newWhere("Char Col", "==", "WAAAAAAAAAAAAAAARIOOOOOO");
    Where where6 = newWhere("Decimal Col", ">", &dec);
    Where where7 = newWhere("Decimal Col", "==", &dec);
    Where where8 = newWhere("Integer Col", "==", &newNum);
    where1.comparison = "!=";
    delete(&table, 7, whereList(7, where5, where3, where6, where4, where1, where7, where8), connectiveList(6, '|', '&', '|', '|', '&', '&'));
    where3.comparison = "!=";
    delete(&table, 2, whereList(2, where5, where3), connectiveList(1, '&'));

    // deleteAll(&table);
    printTable(table);

    printf("\n\n\n");
    where3.searchValue = "Mario";

    Select select1 = newSelect(2, nameList(2, "Decimal Col", "Char Col"), NULL, NULL, 0);

    // where3.comparison = "==";
    // where5.comparison = "!=";
    // delete(&table, 2, whereList(2, where5, where3), connectiveList(1, '&'));
    // printTable(table);

    printTable(select(table, select1, 2, whereList(2, where5, where3), connectiveList(1, '|')));

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
 * Format: update(Table* table, char* colName, void* newValue, int numWheres, Where where1, char connective1, Where where2, ...)
 * (Accepted connectives being '&' or '|' meaning AND or OR)
 * SQL Origin:
 *  UPDATE tableName
 *   SET colName = newValue
 *   WHERE tableName.whereColName =, >, <, >=, <=, != whereValue
*/
void update(Table* table, char* colName, void* newValue, int numWheres, Where* wheres, char* conns) {

    Column column = nameToCol(table, colName);
    int* prevGoodJs;
    int numPrevGoodJs;
    int toUpdate[table->numRows];

    for(int i = 0; i < table->numRows; i++)
        toUpdate[i] = 1;

    for(int i = 0; i < numWheres; i++) {
        prevGoodJs = malloc(sizeof(int));
        numPrevGoodJs = 0;
        for(int j = 0; j < table->numRows; j++) {
            switch(conns[i]) {
                case '&':
                case 'a':
                case 'A':
                    if(toUpdate[j] == 1 && !compare(nameToCol(table, wheres[i].searchColName), j, wheres[i].comparison, wheres[i].searchValue))
                        toUpdate[j] = 0;
                    break;
                case '|':
                case 'o':
                case 'O':
                    toUpdate[j] = 1;
                case '~':
                    if(!compare(nameToCol(table, wheres[i].searchColName), j, wheres[i].comparison, wheres[i].searchValue))
                        toUpdate[j] = 0;
                    break;
                default:
                    printf("Error: Invalid where connective '%c' provided into delete function.", conns[i]);
                    break;
            }

            if(toUpdate[j] == 1) {
                prevGoodJs = realloc(prevGoodJs, sizeof(int) * (++numPrevGoodJs));
                prevGoodJs[numPrevGoodJs - 1] = j;
            }

        }

        if((i == numWheres - 1 || conns[i + 1] == '|' || conns[i + 1] == 'o' || conns[i + 1] == 'O') && (numPrevGoodJs > 0 && numPrevGoodJs <= table->numRows)) {
            for(int k = 0; k < numPrevGoodJs; k++) {
                if(column.type == CHAR)
                    column.values[prevGoodJs[k]].CHAR = (char*)newValue;
                else if(column.type == INTEGER)
                    column.values[prevGoodJs[k]].INTEGER = *((int*)newValue);
                else if(column.type == DECIMAL)
                    column.values[prevGoodJs[k]].DECIMAL = *((double*)newValue);
            }
        }
        free(prevGoodJs);
    }

}

/**
 * Format: delete(Table* table, int numWheres, Where where1, char connective1, Where where2, ...)
 * SQL Origin:
 *  DELETE
 *   FROM tableName
 *   WHERE tableName.whereColName =, >, <, >=, <=, != whereValue
*/
void delete(Table* table, int numWheres, Where* wheres, char* conns) {
    int* prevGoodJs;
    int numPrevGoodJs;

    int toDelete[table->numRows];
    for(int i = 0; i < table->numRows; i++)
        toDelete[i] = 1;

    for(int i = 0; i < numWheres; i++) {
        prevGoodJs = malloc(sizeof(int));
        numPrevGoodJs = 0;
        for(int j = 0; j < table->numRows; j++) {
            switch(conns[i]) {
                case '&':
                case 'a':
                case 'A':
                    if(toDelete[j] == 1 && !compare(nameToCol(table, wheres[i].searchColName), j, wheres[i].comparison, wheres[i].searchValue))
                        toDelete[j] = 0;
                    break;
                case '|':
                case 'o':
                case 'O':
                    toDelete[j] = 1;
                case '~':
                    if(!compare(nameToCol(table, wheres[i].searchColName), j, wheres[i].comparison, wheres[i].searchValue))
                        toDelete[j] = 0;
                    break;
                default:
                    printf("Error: Invalid where connective '%c' provided into delete function.", conns[i]);
                    break;
            }

            if(toDelete[j] == 1) {
                prevGoodJs = realloc(prevGoodJs, sizeof(int) * (++numPrevGoodJs));
                prevGoodJs[numPrevGoodJs - 1] = j;
            }

        }
        if((i == numWheres - 1 || conns[i + 1] == '|' || conns[i + 1] == 'o' || conns[i + 1] == 'O') && (numPrevGoodJs > 0 && numPrevGoodJs <= table->numRows)) {
            for(int k = 0; k < numPrevGoodJs; k++) {
                for(int l = 0; l < table->numCols; l++)
                    table->cols[l].values[prevGoodJs[k] % (table->numRows - 1)] = table->cols[l].values[table->numRows - 1];
                table->numRows--;
            }
        }
        free(prevGoodJs);
    }

    if(numWheres <= 0)
        table->numRows = 0;
}

void deleteAll(Table* table) {
    table->numRows = 0;
}

Table select(Table table, Select select, int numWheres, Where* wheres, char* conns) {
    Table selectedTable;

    selectedTable = selCreate(table, select.numCols, select.colNames);

    delete(&selectedTable, numWheres, notWheres(numWheres, wheres), notConnectives(numWheres - 1, conns));

    return selectedTable;
}

/**
 * A create() variant designed for internal use of the select function.
*/
Table selCreate(Table baseTable, int numCols, char** colNames) {

    Table newTable;

    newTable.name = strdup(baseTable.name);
    newTable.cols = malloc(sizeof(Column) * numCols);

    for(int i = 0; i < numCols; i++) {
        newTable.cols[i] = nameToCol(&baseTable, colNames[i]);
        newTable.cols[i].name = strdup(colNames[i]);
        newTable.cols[i].type = nameToCol(&baseTable, colNames[i]).type;
    }

    newTable.numCols = numCols;
    newTable.numRows = baseTable.numRows;

    return newTable;

}

Where* notWheres(int numWheres, Where* whereList) {
    Where* notWheres = malloc(sizeof(Where) * numWheres);

    for(int i = 0; i < numWheres; i++) {
        notWheres[i].searchColName = strdup(whereList[i].searchColName);
        notWheres[i].searchValue = malloc(max(sizeof(double), strlen(whereList[i].searchValue)));
        memcpy(notWheres[i].searchValue, whereList[i].searchValue, max(sizeof(double), strlen(whereList[i].searchValue)));
        notWheres[i].comparison = oppComp(whereList[i].comparison);
    }
    return notWheres;
}

char* notConnectives(int numConns, char* conns) {
    char* notConns = malloc(sizeof(char) * (numConns + 2));
    notConns[0] = '~';
    for(int i = 1; i < numConns + 1; i++) {
        switch(conns[i]) {
            case '&':
            case 'a':
            case 'A':
                notConns[i] = '|';
                break;
            case '|':
            case 'o':
            case 'O':
                notConns[i] = '&';
                break;
            default:
                printf("Error: Invalid where connective '%c' provided into delete function.", conns[i]);
                notConns[i] = conns[i];
                break;
        }
    }

    notConns[numConns + 1] = '\0';

    return notConns;
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
    // printf("Column name: %s, Comparison: %s, Search Value: ", column.name, comparison);
    // if(column.type == CHAR)
    //     printf("%s\n", (char*)value);
    // else if(column.type == INTEGER)
    //     printf("%d\n", *(int*)value);
    // else if(column.type == DECIMAL)
    //     printf("%lf\n", *(double*)value);

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

char* oppComp(char* comparison) {
    char* oppComp;

    if(strcmp(comparison, "=") == 0 || strcmp(comparison, "==") == 0)
        oppComp = "!=";
    else if(strcmp(comparison, "<") == 0)
        oppComp = ">=";
    else if(strcmp(comparison, "<=") == 0)
        oppComp = ">";
    else if(strcmp(comparison, ">") == 0)
        oppComp = "<=";
    else if(strcmp(comparison, ">=") == 0)
        oppComp = "<";
    else if(strcmp(comparison, "<>") == 0 || strcmp(comparison, "!=") == 0)
        oppComp = "==";
    else {
        printf("Error: Invalid comparison entered.\n");
        oppComp = NULL;
    }

    return oppComp;
}

Where newWhere(char* searchColName, char* comparison, void* searchValue) {
    Where newWhere;
    newWhere.searchColName = strdup(searchColName);
    newWhere.comparison = strdup(comparison);
    newWhere.searchValue = malloc(max(sizeof(double), strlen(searchValue)));
    memcpy(newWhere.searchValue, searchValue, max(sizeof(double), strlen(searchValue)));
    // newWhere.searchValue = searchValue;

    return newWhere;
}
Select newSelect(int numCols, char** colNames, char** orderByCols, char** groupByCols, int distinct) {
    Select select;

    select.numCols = numCols;
    select.colNames = colNames;
    select.orderByCols = orderByCols;
    select.groupByCols = groupByCols;
    select.distinct = distinct;

    return select;
}
char** nameList(int numNames, ...) {
    va_list ap;
    char** nameList = malloc(sizeof(char*) * numNames);
    va_start(ap, numNames);

    for(int i = 0; i < numNames; i++)
        nameList[i] = strdup(va_arg(ap, char*));

    va_end(ap);

    return nameList;
}
Where* whereList(int numWheres, ...) {
    va_list ap;
    va_start(ap, numWheres);

    Where* wheres = malloc(sizeof(Where) * numWheres);

    for(int i = 0; i < numWheres; i++)
        wheres[i] = va_arg(ap, Where);

    va_end(ap);

    return wheres;
}
char* connectiveList(int numConns, ...) {

    va_list ap;
    va_start(ap, numConns);

    char* conns = malloc(sizeof(char) * (numConns + 2));
    conns[0] = '~';

    for(int i = 1; i < numConns + 1; i++)
        conns[i] = va_arg(ap, int);

    va_end(ap);

    conns[numConns + 1] = '\0';

    return conns;

}
// int* typeList(int numTypes, ...) {
//     va_list ap;
//     int* typeList = malloc(sizeof(int) * numTypes);
//     va_start(ap, numTypes);

//     for(int i = 0; i < numTypes; i++)
//         typeList[i] = va_arg(ap, int);

//     va_end(ap);

//     return typeList;
// }

void printTable(Table table) {

    printf("\nTABLE: %s\n\t  ", table.name);
    char printString[50];

    for(int i = 0; i < table.numCols; i++)
        printf("%-20s", table.cols[i].name);

    for(int i = 0; i < table.numRows; i++) {
        printf("\n\t  ");
        for(int j = 0; j < table.numCols; j++) {
            if(table.cols[j].type == CHAR) {
                sprintf(printString, "[ %s ]", table.cols[j].values[i].CHAR);
                if(strlen(printString) > 18) {
                    printString[18] = '\0';
                    printString[17] = ']';
                    printString[16] = ' ';
                    printString[15] = '.';
                    printString[14] = '.';
                    printString[13] = '.';
                }
                printf("%-20s", printString);
            }
            else if(table.cols[j].type == INTEGER) {
                sprintf(printString, "[ %d ]", table.cols[j].values[i].INTEGER);
                printf("%-20s", printString);
            }
            else if(table.cols[j].type == DECIMAL) {
                sprintf(printString, "[ %.3lf ]", table.cols[j].values[i].DECIMAL);
                printf("%-20s", printString);
            }
        }
    }

    printf("\n");
}
