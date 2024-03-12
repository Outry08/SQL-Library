#include "sqllib.h"

int main(int argc, char const* argv[]) {

    Table* tables = malloc(sizeof(Table) * 2);

    // Table* tables = userTableOperator();
    tables[0] = create("My Table", 3, nameList(3, "Char Col", "Decimal Col", "Integer Col"), typeList(3, CHAR, DECIMAL, INTEGER));
    printTable(tables[0]);

    insert(&tables[0], 2, nameList(2, "Decimal Col", "Char Col"), valueList(2, typeList(2, DECIMAL, CHAR), 44.55, "Luigi"));
    printTable(tables[0]);
    insert(&tables[0], 1, nameList(1, "Char Col"), valueList(1, typeList(1, CHAR), "Mario"));
    printTable(tables[0]);

    insert(&tables[0], 1, nameList(1, "Integer Col"), valueList(1, typeList(1, INTEGER), 4));
    insert(&tables[0], 3, nameList(3, "Integer Col", "Decimal Col", "Char Col"), valueList(3, typeList(3, INTEGER, DECIMAL, CHAR), 44, 88.77, "WAHHLUIGI"));
    printTable(tables[0]);

    Where where1 = newWhere("Char Col", "==", "Luigi");
    double newNum = 9999.999;


    update(&tables[0], "Decimal Col", &newNum, 1, whereList(1, where1), connectiveList(0));
    printTable(tables[0]);

    newNum = 0;
    Where where2 = newWhere("Decimal Col", "==", &newNum);

    int newInt = 1735;

    update(&tables[0], "Integer Col", &newInt, 2, whereList(2, where1, where2), connectiveList(1, '|'));
    printTable(tables[0]);

    Where where3 = newWhere("Char Col", "==", "NULL");
    update(&tables[0], "Char Col", "WAAAAARIOOOOOOO", 1, whereList(1, where3), connectiveList(0));
    printTable(tables[0]);

    insert(&tables[0], 1, nameList(1, "Decimal Col"), valueList(1, typeList(1, DECIMAL), 444.0));

    printTable(tables[0]);
    newInt = 666;

    update(&tables[0], "Integer Col", &newInt, 3, whereList(3, where3, where2, where1), connectiveList(2, '&', '|'));
    printTable(tables[0]);

    Where where4 = newWhere("Integer Col", "==", &newInt);
    update(&tables[0], "Char Col", "WAAAAAAAAAAAAAAARIOOOOOO", 2, whereList(2, where3, where4), connectiveList(1, '&'));
    printTable(tables[0]);

    update(&tables[0], "Char Col", "Peach", 1, whereList(1, where3), connectiveList(0));
    printTable(tables[0]);

    double dec = 444.0;

    Where where5 = newWhere("Char Col", "==", "WAAAAAAAAAAAAAAARIOOOOOO");
    Where where6 = newWhere("Decimal Col", ">", &dec);
    Where where7 = newWhere("Decimal Col", "==", &dec);
    Where where8 = newWhere("Integer Col", "==", &newNum);
    where1.comparison = "!=";
    delete(&tables[0], 7, whereList(7, where5, where3, where6, where4, where1, where7, where8), connectiveList(6, '|', '&', '|', '|', '&', '&'));
    printTable(tables[0]);
    where3.comparison = "!=";
    delete(&tables[0], 2, whereList(2, where5, where3), connectiveList(1, '&'));

    // deleteAll(&tables[0]);
    printTable(tables[0]);

    printf("\n\n\n");
    where3.searchValue = "Mario";
    where3.comparison = "==";

    Select select1 = newSelect(2, nameList(2, "Decimal Col", "Char Col"), NULL, NULL, 0);

    // where3.comparison = "==";
    // where5.comparison = "!=";
    // delete(&tables[0], 2, whereList(2, where5, where3), connectiveList(1, '&'));
    // printTable(tables[0]);

    tables[1] = select(tables[0], select1, 2, whereList(2, where5, where3), connectiveList(1, '|'));

    Select select2 = newSelect(1, nameList(1, "Char Col"), NULL, NULL, 0);
    Where where9 = newWhere("Char Col", "=", "WAHHLUIGI");

    tables[1] = select(tables[0], select2, 2, whereList(2, where3, where9), connectiveList(1, '|'));

    insertIntoRow(tables, 3, nameList(3, "Char Col", "Integer Col", "Decimal Col"), valueList(3, typeList(3, CHAR, INTEGER, DECIMAL), "Peach", 777, 19.64), 3);

    userTableOperator(2, tables);

    return 0;
}

/**
 * SQL Origin:
 *  CREATE tableName (col1Name col1Type, col2Name col2Type, ...)
*/
Table create(char* tableName, int numCols, char** colNames, int* colTypes) {

    Table table;

    table.name = strdup(tableName);
    table.cols = malloc(sizeof(Column) * numCols);

    for(int i = 0; i < numCols; i++) {
        table.cols[i].name = strdup(colNames[i]);
        table.cols[i].type = colTypes[i];
    }

    table.numCols = numCols;
    table.numRows = 0;

    table.selected = 0;

    return table;

}

/**
 * SQL Origin:
 *  INSERT
 *   INTO tableName(col1Name, col2Name, ...)
 *   VALUES (val1, val2, ...)
*/
void insert(Table* table, int numValues, char** colNames, void** values) {

    if(numValues > table->numCols) {
        printf("Error: To many arguments provided. Insertion failed.\n");
        return;
    }

    table->numRows++;
    char* colName = "";
    Column currCol;

    for(int i = 0; i < table->numCols; i++) {
        table->cols[i].values = realloc(table->cols[i].values, sizeof(ElementUnion) * table->numRows);
        table->cols[i].values[table->numRows - 1].type = vNULL;
        // if(table->cols[i].type == CHAR)
        //     table->cols[i].values[table->numRows - 1].CHAR = "NULL";
        // else if(table->cols[i].type == INTEGER)
        //     table->cols[i].values[table->numRows - 1].INTEGER = 0;
        // else if(table->cols[i].type == DECIMAL)
        //     table->cols[i].values[table->numRows - 1].DECIMAL = 0.0;
    }

    for(int i = 0; i < numValues; i++) {
        colName = strdup(colNames[i]);
        currCol = nameToCol(table, colName);

        if(currCol.type == CHAR) {
            // printf("CHAR VAL\n");
            currCol.values[table->numRows - 1].type = CHAR;
            currCol.values[table->numRows - 1].CHAR = strdup((char*)values[i]);
        }
        else if(currCol.type == INTEGER) {
            // printf("INTEGER VAL\n");
            currCol.values[table->numRows - 1].type = INTEGER;
            currCol.values[table->numRows - 1].INTEGER = *(int*)values[i];
        }
        else if(currCol.type == DECIMAL) {
            // printf("DECIMAL VAL\n");
            currCol.values[table->numRows - 1].type = DATE;
            currCol.values[table->numRows - 1].DECIMAL = *(double*)values[i];
        }
        else {
            printf("Error: Nonexistent column name, \"%s\", provided.\n", colName);
        }

        free(colName);
    }
}

void insertIntoRow(Table* table, int numValues, char** colNames, void** values, int rowNum) {

    rowNum--;

    if(numValues > table->numCols) {
        printf("Error: To many arguments provided. Insertion failed.\n");
        return;
    }
    if(rowNum >= table->numRows || rowNum < 0) {
        printf("Error: Row number out of range.\n");
        return;
    }

    table->numRows++;
    char* colName = "";
    Column currCol;

    for(int i = 0; i < table->numCols; i++) {
        table->cols[i].values = realloc(table->cols[i].values, sizeof(ElementUnion) * table->numRows);
        for(int j = table->numRows - 2; j >= rowNum; j--) {
            memcpy(&table->cols[i].values[j + 1], &table->cols[i].values[j], sizeof(ElementUnion));
        }

        table->cols[i].values = realloc(table->cols[i].values, sizeof(ElementUnion) * table->numRows);
        table->cols[i].values[table->numRows - 1].type = vNULL;
    }

    for(int i = 0; i < numValues; i++) {
        colName = strdup(colNames[i]);
        currCol = nameToCol(table, colName);

        if(currCol.type == CHAR) {
            // printf("CHAR VAL\n");
            currCol.values[table->numRows - 1].type = CHAR;
            currCol.values[table->numRows - 1].CHAR = strdup((char*)values[i]);
        }
        else if(currCol.type == INTEGER) {
            // printf("INTEGER VAL\n");
            currCol.values[table->numRows - 1].type = INTEGER;
            currCol.values[table->numRows - 1].INTEGER = *(int*)values[i];
        }
        else if(currCol.type == DECIMAL) {
            // printf("DECIMAL VAL\n");
            currCol.values[table->numRows - 1].type = DATE;
            currCol.values[table->numRows - 1].DECIMAL = *(double*)values[i];
        }
        else {
            printf("Error: Nonexistent column name, \"%s\", provided.\n", colName);
        }

        free(colName);
    }
}

/**
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

    printf("HELLO THERE\n");

    for(int i = 0; i < table->numRows; i++)
        toUpdate[i] = 1;

    printf("YO THERE\n");

    for(int i = 0; i < numWheres; i++) {
        printf("HOOOOOOOOO\n");
        prevGoodJs = malloc(sizeof(int));
        numPrevGoodJs = 0;
        for(int j = 0; j < table->numRows; j++) {
            printf("HAAAAAA\n");
            printf("CONNS: %c\n", conns[i]);
            switch(conns[i]) {
                case '&':
                case 'a':
                case 'A':
                    if(toUpdate[j] == 1 && !compare(nameToCol(table, wheres[i].searchColName), j, wheres[i].comparison, wheres[i].searchValue))
                        toUpdate[j] = 0;
                    printf("LLLLLLLLLLLL");
                    break;
                case '|':
                case 'o':
                case 'O':
                    toUpdate[j] = 1;
                    printf("BBBBBBBB\n");
                case '~':
                    if(!compare(nameToCol(table, wheres[i].searchColName), j, wheres[i].comparison, wheres[i].searchValue))
                        toUpdate[j] = 0;

                    printf("EEEEEEE\n");
                    break;
                default:
                    printf("Error: Invalid where connective '%c' provided into update function.", conns[i]);
                    break;
            }

            if(toUpdate[j] == 1) {
                printf("WATCHU\n");
                prevGoodJs = realloc(prevGoodJs, sizeof(int) * (++numPrevGoodJs));
                prevGoodJs[numPrevGoodJs - 1] = j;
                printf("HOBGOBLIN\n");
            }

        }
        printf("WHAT'S GOOD THERE\n");
        if((i == numWheres - 1 || conns[i + 1] == '|' || conns[i + 1] == 'o' || conns[i + 1] == 'O') && (numPrevGoodJs > 0 && numPrevGoodJs <= table->numRows)) {
            for(int k = 0; k < numPrevGoodJs; k++) {
                if(column.type == CHAR) {
                    column.values[prevGoodJs[k]].type = CHAR;
                    column.values[prevGoodJs[k]].CHAR = (char*)newValue;
                }
                else if(column.type == INTEGER) {
                    column.values[prevGoodJs[k]].type = INTEGER;
                    column.values[prevGoodJs[k]].INTEGER = *((int*)newValue);
                }
                else if(column.type == DECIMAL) {
                    column.values[prevGoodJs[k]].type = DECIMAL;
                    column.values[prevGoodJs[k]].DECIMAL = *((double*)newValue);
                }
            }
        }
        free(prevGoodJs);
    }

    printf("GOODBYE THERE\n");

}

/**
 * SQL Origin:
 *  DELETE
 *   FROM tableName
 *   WHERE tableName.whereColName =, >, <, >=, <=, != whereValue
*/

void delete(Table* table, int numWheres, Where* wheres, char* conns) {
    int* prevGoodJs;
    int numPrevGoodJs;

    int toDelete[table->numRows];
    for(int i = 0; i < table->numRows; i++) {
        // printf("%d\n", i);
        toDelete[i] = 1;
    }

    // printf("%d\n", numWheres);
    // printf("%c\n", conns[0]);
    for(int i = 0; i < numWheres; i++) {
        // printf("HEHE\n");
        prevGoodJs = malloc(sizeof(int));
        numPrevGoodJs = 0;
        for(int j = 0; j < table->numRows; j++) {
            // printf("BEFORE\n");
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
                for(int l = 0; l < table->numCols; l++) {
                    //Keep an eye on the index calculation: prevGoodJs[k] % (table->numRows). It's working for now, but I'm not 100% confident in it.
                    // table->cols[l].values[prevGoodJs[k] % (table->numRows)] = table->cols[l].values[table->numRows - 1];
                    //This may break. Can almost certainly be optimized. 
                    for(int m = prevGoodJs[k] % (table->numRows); m < table->numRows - 1; m++) {
                        printf("SHIFTING SANDLAND\n");
                        memcpy(&table->cols[l].values[m], &table->cols[l].values[m + 1], sizeof(ElementUnion));
                    }
                }
                table->numRows--;
            }
        }
        free(prevGoodJs);
    }

    if(numWheres <= 0)
        table->numRows = 0;

    // printf("POOOF\n");
}

void deleteAll(Table* table) {
    table->numRows = 0;
}

Table select(Table table, Select sel, int numWheres, Where* wheres, char* conns) {

    Table tableCopy = copyTable(table);

    if(numWheres > 0)
        delete(&tableCopy, numWheres, notWheres(numWheres, wheres), notConnectives(numWheres - 1, conns));

    Table selectedTable;

    if(sel.numCols == table.numCols) {
        // printf("YYYYYYYYYY\n");
        for(int i = 0; i < sel.numCols; i++)
            if(sel.colNames[i] != NULL)
                free(sel.colNames[i]);

        sel.numCols = tableCopy.numCols;

        for(int i = 0; i < tableCopy.numCols; i++) {
            sel.colNames[i] = strdup(tableCopy.cols[i].name);
        }
    }
    else {
        // printf("BHIJSKKFHJKSBFKS\n");
    }
    selectedTable = selCreate(tableCopy, sel.numCols, sel.colNames);

    // printf("10\n");

    return selectedTable;
}

/**
 * A create() variant designed for internal use of the select function.
*/
Table selCreate(Table baseTable, int numCols, char** colNames) {

    Table newTable;
    // printf("HELLO THERE\n");

    newTable.name = strdup(baseTable.name);
    // printf("1\n");
    strcat(newTable.name, " Select");
    newTable.cols = malloc(sizeof(Column) * numCols);

    newTable.numCols = numCols;
    newTable.numRows = baseTable.numRows;

    // int allAggs = 1;

    // char* newName;

    for(int i = 0; i < numCols; i++) {
        if(!isAggregate(colNames[i])) {
            // printf("2.1\n");
            newTable.cols[i] = copyColumn(baseTable.numRows, nameToCol(&baseTable, colNames[i]));
            // newTable.cols[i].name = strdup(colNames[i]);
            // newTable.cols[i].type = nameToCol(&baseTable, colNames[i]).type;

            // allAggs = 0;
        }
        // else {
        //     // printf("2.2\n");
        //     newName = &(strchr(colNames[i], '(')[1]);
        //     for(int j = 0; j < strlen(newName); j++)
        //         if(newName[j] == ')')
        //             newName[j] = '\0';
        //     newTable.cols[i].values = malloc(sizeof(ElementUnion) * newTable.numRows));
        //     newTable.cols[i].name = getAggregateName(colNames[i]);
        //     newTable.cols[i].type = nameToCol(&baseTable, newName).type;
        // }
    }

    // printf("3.0\n");

    // if(allAggs) {
    //     // printf("3.1\n");
    //     for(int i = 0; i < numCols; i++)
    //         newTable.cols[i].values = realloc(newTable.cols[i].values, 1);
    //     newTable.numRows = 1;
    // }

    newTable.selected = 1;

    // printf("GOODBYE THERE\n");

    return newTable;

}

Table copyTable(Table table) {
    Table newTable;

    newTable.name = strdup(table.name);

    newTable.numCols = table.numCols;
    newTable.numRows = table.numRows;

    newTable.cols = malloc(sizeof(Column) * newTable.numCols);

    for(int i = 0; i < newTable.numCols; i++) {
        newTable.cols[i] = copyColumn(table.numRows, table.cols[i]);
    }

    return newTable;
}

Column copyColumn(int numVals, Column col) {
    Column colCopy;

    printf("ENTERING COPYCOL\n");

    colCopy.name = strdup(col.name);
    colCopy.type = col.type;
    colCopy.values = malloc(sizeof(ElementUnion) * numVals);
    memcpy(colCopy.values, col.values, sizeof(ElementUnion) * numVals);

    printf("EXITING COPYCOL\n");

    return colCopy;
}

Where* notWheres(int numWheres, Where* whereList) {
    if(whereList == NULL || numWheres <= 0)
        return NULL;

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
    if(conns == NULL || numConns + 1 <= 0)
        return NULL;

    char* notConns = malloc(sizeof(char) * (numConns + 1));
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
                printf("Error: Invalid where connective '%c' provided into notConnectives function.", conns[i]);
                notConns[i] = conns[i];
                break;
        }
    }

    // notConns[numConns + 1] = '\0';

    return notConns;
}

Column nameToCol(Table* table, char* colName) {

    for(int i = 0; i < table->numCols; i++)
        if(strcmp(table->cols[i].name, colName) == 0)
            return table->cols[i];

    Column errCol;
    errCol.name = "COL NOT FOUND";
    errCol.type = -1;
    printf("Error: Failed to find column '%s' in table '%s'\n", colName, table->name);

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
        if(column.values[valIndex].type == vNULL) {
            if(value == NULL)
                return 1;
            else if(column.type == CHAR)
                return strcmp("NULL", (char*)value) == 0;
            else if(column.type == INTEGER)
                return 0 == *((int*)value);
            else if(column.type == DECIMAL)
                return 0 == *((double*)value);
            else
                return 0;
        }
        else if(column.type == CHAR)
            return strcmp(column.values[valIndex].CHAR, (char*)value) == 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].INTEGER == *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].DECIMAL == *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, "<") == 0) {
        if(column.values[valIndex].type == vNULL) {
            if(value == NULL)
                return 0;
            else if(column.type == CHAR)
                return strcmp("NULL", (char*)value) < 0;
            else if(column.type == INTEGER)
                return 0 < *((int*)value);
            else if(column.type == DECIMAL)
                return 0 < *((double*)value);
            else
                return 0;
        }
        else if(column.type == CHAR)
            return strcmp(column.values[valIndex].CHAR, (char*)value) < 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].INTEGER < *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].DECIMAL < *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, "<=") == 0) {
        if(column.values[valIndex].type == vNULL) {
            if(value == NULL)
                return 1;
            else if(column.type == CHAR)
                return strcmp("NULL", (char*)value) <= 0;
            else if(column.type == INTEGER)
                return 0 <= *((int*)value);
            else if(column.type == DECIMAL)
                return 0 <= *((double*)value);
            else
                return 0;
        }
        else if(column.type == CHAR)
            return strcmp(column.values[valIndex].CHAR, (char*)value) <= 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].INTEGER <= *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].DECIMAL <= *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, ">") == 0) {
        if(column.values[valIndex].type == vNULL) {
            if(value == NULL)
                return 0;
            else if(column.type == CHAR)
                return strcmp("NULL", (char*)value) > 0;
            else if(column.type == INTEGER)
                return 0 > *((int*)value);
            else if(column.type == DECIMAL)
                return 0 > *((double*)value);
            else
                return 0;
        }
        else if(column.type == CHAR)
            return strcmp(column.values[valIndex].CHAR, (char*)value) > 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].INTEGER > *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].DECIMAL > *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, ">=") == 0) {
        if(column.values[valIndex].type == vNULL) {
            if(value == NULL)
                return 1;
            else if(column.type == CHAR)
                return strcmp("NULL", (char*)value) >= 0;
            else if(column.type == INTEGER)
                return 0 >= *((int*)value);
            else if(column.type == DECIMAL)
                return 0 >= *((double*)value);
            else
                return 0;
        }
        else if(column.type == CHAR)
            return strcmp(column.values[valIndex].CHAR, (char*)value) >= 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].INTEGER >= *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].DECIMAL >= *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, "<>") == 0 || strcmp(comparison, "!=") == 0) {
        if(column.values[valIndex].type == vNULL) {
            if(value == NULL)
                return 0;
            else if(column.type == CHAR)
                return strcmp("NULL", (char*)value) != 0;
            else if(column.type == INTEGER)
                return 0 != *((int*)value);
            else if(column.type == DECIMAL)
                return 0 != *((double*)value);
            else
                return 0;
        }
        else if(column.type == CHAR)
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

int isValidComp(char* comparison) {
    if(strcmp(comparison, "=") == 0 || strcmp(comparison, "==") == 0)
        return 1;
    else if(strcmp(comparison, "<") == 0)
        return 1;
    else if(strcmp(comparison, "<=") == 0)
        return 1;
    else if(strcmp(comparison, ">") == 0)
        return 1;
    else if(strcmp(comparison, ">=") == 0)
        return 1;
    else if(strcmp(comparison, "<>") == 0 || strcmp(comparison, "!=") == 0)
        return 1;
    else
        return 0;
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

int isAggregate(char* name) {
    return strstr(name, "COUNT(") || strstr(name, "SUM(") || strstr(name, "AVG(") || strstr(name, "MAX(") || strstr(name, "MIN(")
        || !strcmp(name, "COUNT") || !strcmp(name, "SUM") || !strcmp(name, "AVG") || !strcmp(name, "MAX") || !strcmp(name, "MIN");
}

char* getAggregateName(char* name) {
    if(strstr(name, "COUNT("))
        return "COUNT";
    else if(strstr(name, "SUM("))
        return "SUM";
    else if(strstr(name, "AVG("))
        return "AVG";
    else if(strstr(name, "MAX("))
        return "MIN";
    else if(strstr(name, "MIN("))
        return "MIN";
    else
        return name;
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

    if(numCols < 0)
        select.numCols = 0;
    else
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
void** valueList(int numValues, int* types, ...) {

    static int intVal;
    static char* charVal;
    static double doubVal;

    va_list ap;
    void** valueList = malloc(sizeof(void*) * numValues);
    va_start(ap, types);

    for(int i = 0; i < numValues; i++) {
        if(types[i] == INTEGER) {
            valueList[i] = malloc(sizeof(int));
            intVal = va_arg(ap, int);
            memcpy(valueList[i], &intVal, sizeof(int));
        }
        else if(types[i] == CHAR) {
            charVal = va_arg(ap, char*);
            valueList[i] = strdup(charVal);
        }
        else if(types[i] == DECIMAL) {
            valueList[i] = malloc(sizeof(double));
            doubVal = va_arg(ap, double);
            memcpy(valueList[i], &doubVal, sizeof(double));
        }
    }

    va_end(ap);

    return valueList;
}
int* typeList(int numTypes, ...) {
    va_list ap;
    int* typeList = malloc(sizeof(int) * numTypes);
    va_start(ap, numTypes);

    for(int i = 0; i < numTypes; i++)
        typeList[i] = va_arg(ap, int);

    va_end(ap);

    return typeList;
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

    char* conns = malloc(sizeof(char) * (numConns + 1));
    conns[0] = '~';

    for(int i = 1; i < numConns + 1; i++)
        conns[i] = va_arg(ap, int);

    va_end(ap);

    return conns;

}


void printTable(Table table) {

    int colWidth = 23;

    printf("\n");
    for(int i = 0; i < colWidth * table.numCols / 2; i++) {
        printf(" ");
    }
    printf("TABLE: %s", table.name);
    char printString[MAX_LEN];

    printTableRow(table.numCols, 0);

    for(int i = 0; i < table.numCols; i++)
        printf("| \e[1m%-*s\e[m", colWidth - 2, table.cols[i].name);
    printf("|");

    for(int i = 0; i < table.numRows; i++) {
        printTableRow(table.numCols, i + 1);
        for(int j = 0; j < table.numCols; j++) {
            if(table.cols[j].values[i].type == vNULL)
                printf("| %-*s ", colWidth - 3, "NULL");

            else if(table.cols[j].type == CHAR) {
                sprintf(printString, "%s", table.cols[j].values[i].CHAR);
                if(strlen(printString) > 18) {
                    printString[18] = '\0';
                    printString[17] = ']';
                    printString[16] = ' ';
                    printString[15] = '.';
                    printString[14] = '.';
                    printString[13] = '.';
                }
                printf("| %-*s ", colWidth - 3, printString);
            }
            else if(table.cols[j].type == INTEGER) {
                sprintf(printString, "%d", table.cols[j].values[i].INTEGER);
                printf("| %-*s ", colWidth - 3, printString);
            }
            else if(table.cols[j].type == DECIMAL) {
                sprintf(printString, "%.3lf", table.cols[j].values[i].DECIMAL);
                printf("| %-*s ", colWidth - 3, printString);
            }
        }
        printf("|");
    }

    printTableRow(table.numCols, 0);
    printf("\n");
}

void printTableRow(int numCols, int rowNum) {
    printf("\n\t+");
    for(int j = 0; j < numCols; j++) {
        for(int k = 0; k < 22; k++) {
            printf("-");
        }
        printf("+");
    }
    if(rowNum > 0)
        printf("\n%d\t", rowNum);
    else
        printf("\n\t");
}

Table* userTableOperator(int numTables, Table* tables) {

    Table* currentTable = NULL;

    int menuChoice = 1;
    int tableChoice;

    char yesno[MAX_LEN];

    char tableName[MAX_LEN];
    int numThings;
    int rowNum;

    char** nameList = NULL;
    int* typeList = NULL;
    void** valueList = NULL;
    Where* whereList = NULL;
    int numWheres = 0;
    char* connectiveList = NULL;

    Select sel;

    printf("\t\t-- Welcome to CQL! --\n");

    while(menuChoice > 0) {
        numWheres = 0;

        menuChoice = printActionMenu(currentTable);

        switch(menuChoice) {
            case 1:
                //"1. Create a table"
                numTables++;
                if(numTables == 1)
                    tables = malloc(sizeof(Table));
                else
                    tables = realloc(tables, sizeof(Table) * numTables);

                printf("What is the name of your new table?: ");
                fgetsUntil(tableName, MAX_LEN);

                printf("How many columns would you like to have?: ");
                do {
                    scanfWell("%d", &numThings);
                    if(numThings <= 0)
                        printf("Please input a positive number: ");
                } while(numThings <= 0);
                nameList = malloc(sizeof(char*) * numThings);
                typeList = malloc(sizeof(int) * numThings);
                for(int i = 0; i < numThings; i++) {
                    printf("Name for column #%d: ", i + 1);
                    nameList[i] = malloc(sizeof(char) * MAX_LEN);
                    fgetsUntil(nameList[i], MAX_LEN);
                    typeList[i] = printTypeChart(i + 1);
                }
                tables[numTables - 1] = create(tableName, numThings, nameList, typeList);
                currentTable = &tables[numTables - 1];

                for(int i = 0; i < numThings; i++) {
                    free(nameList[i]);
                }
                free(nameList);
                free(typeList);
                nameList = NULL;
                typeList = NULL;
                break;
            case 2:
                //"2. Print a table"
                if(numTables > 0) {
                    printf("Which table would you like to print?\n");
                    printTable(tables[printTableMenu(numTables, tables)]);
                }
                else
                    printf("There are no tables to print.\n");
                break;
            case 3:
                //"3. Choose new current table"
                if(numTables > 0) {
                    printf("Which table would you like to become your current table?\n");
                    currentTable = &tables[printTableMenu(numTables, tables)];
                }
                else
                    printf("There are no tables to choose.\n");

                break;
            case 4:
                //"4. Select from current table"
                if(numTables <= 0) {
                    printf("There are no tables to select from.\n");
                    break;
                }
                if(currentTable == NULL) {
                    printf("Which table would you like to select from?\n");
                    tableChoice = printTableMenu(numTables, tables);
                    currentTable = &tables[tableChoice];
                }

                printf("How many columns would you like to select?: ");
                do {
                    scanfWell("%d", &sel.numCols);
                    if(sel.numCols <= 0)
                        printf("Please input a positive number: ");
                    else if(sel.numCols > currentTable->numCols)
                        printf("Your current table doesn't have that many columns. Try again: ");
                } while(sel.numCols <= 0 || sel.numCols > currentTable->numCols);

                sel.colNames = malloc(sizeof(char*) * sel.numCols);
                if(sel.numCols < currentTable->numCols)
                    for(int i = 0; i < sel.numCols; i++) {
                        sel.colNames[i] = malloc(sizeof(char) * MAX_LEN);

                        do {
                            printf("Name for select column #%d: ", i + 1);
                            fgetsUntil(sel.colNames[i], MAX_LEN);
                            if(nameToCol(currentTable, sel.colNames[i]).type == -1)
                                continue;
                            else
                                break;
                        } while(1);
                    }
                else {
                    sel.colNames[0] = strdup("*");
                }

                printf("Would you like to filter your result with a where statement? (yes/no): ");
                do {
                    fgetsUntil(yesno, MAX_LEN);
                    if(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0)
                        printf("Please input 'yes' or 'no': ");
                } while(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0);


                if(strcmp(yesno, "yes") == 0)
                    numWheres = whereInput(currentTable, &whereList, &connectiveList);

                /*
                group by stuff
                */

                /*
                order by stuff
                */

                printf("Do you want to omit duplicate values in this select? (yes/no): ");
                do {
                    fgetsUntil(yesno, MAX_LEN);
                    if(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0)
                        printf("Please input 'yes' or 'no': ");
                } while(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0);

                if(strcmp(yesno, "yes") == 0)
                    sel.distinct = 1;
                else
                    sel.distinct = 0;

                numTables++;
                tables = realloc(tables, sizeof(Table) * numTables);
                currentTable = &tables[tableChoice];

                printf("TIME TO SELECT!\n");

                tables[numTables - 1] = select(*currentTable, sel, numWheres, whereList, connectiveList);
                currentTable = &tables[numTables - 1];
                for(int i = 0; i < numWheres; i++) {
                    free(whereList[i].comparison);
                    free(whereList[i].searchColName);
                    free(whereList[i].searchValue);
                }
                free(whereList);
                free(connectiveList);
                whereList = NULL;
                connectiveList = NULL;
                break;

            case 5:
                //"5. Insert a new row into current table"
                if(numTables <= 0) {
                    printf("There are no tables to insert into from.\n");
                    break;
                }
                if(currentTable == NULL) {
                    printf("Which table would you like to insert into?\n");
                    tableChoice = printTableMenu(numTables, tables);
                    currentTable = &tables[tableChoice];
                }

                printf("How many columns would you like to insert into?: ");
                do {
                    scanfWell("%d", &numThings);
                    if(numThings <= 0)
                        printf("Please input a positive number: ");
                    if(numThings > currentTable->numCols)
                        printf("Your current table doesn't have that many columns. Try again: ");
                } while(numThings <= 0 || numThings > currentTable->numCols);
                nameList = malloc(sizeof(char*) * numThings);
                valueList = malloc(sizeof(void*) * numThings);
                if(numThings < currentTable->numCols) {

                    for(int i = 0; i < numThings; i++) {
                        nameList[i] = malloc(sizeof(char) * MAX_LEN);

                        do {
                            printf("Name for select column #%d: ", i + 1);
                            fgetsUntil(nameList[i], MAX_LEN);
                            if(nameToCol(currentTable, nameList[i]).type == -1)
                                continue;
                            else
                                break;
                        } while(1);

                        printf("New value for %s (of type ", nameList[i]);
                        printType(nameToCol(currentTable, nameList[i]).type);
                        printf("): ");



                        if(nameToCol(currentTable, nameList[i]).type == INTEGER) {
                            valueList[i] = malloc(sizeof(int));
                            scanfWell("%d", valueList[i]);
                        }
                        else if(nameToCol(currentTable, nameList[i]).type == CHAR) {
                            valueList[i] = malloc(sizeof(char) * MAX_LEN);
                            scanfWell("%s", valueList[i]);
                        }
                        else if(nameToCol(currentTable, nameList[i]).type == DECIMAL) {
                            valueList[i] = malloc(sizeof(double));
                            scanfWell("%lf", valueList[i]);
                        }
                    }
                }
                else {
                    for(int i = 0; i < numThings; i++) {
                        nameList[i] = strdup(currentTable->cols[i].name);

                        printf("New value for %s (of type ", nameList[i]);
                        printType(nameToCol(currentTable, nameList[i]).type);
                        printf("): ");

                        if(nameToCol(currentTable, nameList[i]).type == INTEGER) {
                            valueList[i] = malloc(sizeof(int));
                            scanfWell("%d", valueList[i]);
                        }
                        else if(nameToCol(currentTable, nameList[i]).type == CHAR) {
                            valueList[i] = malloc(sizeof(char) * MAX_LEN);
                            scanfWell("%s", valueList[i]);
                        }
                        else if(nameToCol(currentTable, nameList[i]).type == DECIMAL) {
                            valueList[i] = malloc(sizeof(double));
                            scanfWell("%lf", valueList[i]);
                        }
                    }
                }

                printf("Which row would you like to insert into? (1-%d): ", currentTable->numRows);
                do {
                    scanfWell("%d", &rowNum);
                    if(rowNum < 1 || rowNum > currentTable->numRows)
                        printf("Please input a valid row number. (1-%d): ", currentTable->numRows);
                } while(rowNum < 1 || rowNum > currentTable->numRows);


                insert(currentTable, numThings, nameList, valueList);

                for(int i = 0; i < numThings; i++) {
                    free(nameList[i]);
                    free(valueList[i]);
                }
                free(nameList);
                free(valueList);
                nameList = NULL;
                valueList = NULL;

                break;
            case 6:
                //"6. Insert a new column into current table"
                break;
            case 7:
                //"7. Update an existing value in current table"
                break;
            case 8:
                //"8. Delete records from current table"
                break;
            case 9:
                //"9. Delete current table"
                break;
            case 10:
                //"10. Import Table(s) from .sql File"
                break;
            case 11:
                //"11. Import Table(s) from .db File"
                break;
            case 12:
                //"12. Export Table(s) to .SQL File"
                break;
            case 13:
                //"13. Export Table(s) to .db File"
                break;

                /*
                perhaps incorporate a where or select saving system, allowing the user to sqitftly use frequently used where or select statements.
                I would save these in a separate .cql file separate from the .sql file that can be converted to .db.
                I could add other useful CQL specific saves later on.
                */

            case 0:
                //"0. Save & Exit"
                printf("Saving\n");
                for(int i = 0; i < 3; i++) {
                    sleep(750);
                    printf(".\n");
                }
                sleep(1000);
                printf("Database Saved.\n");
            default:
                //"-1. Exit Without Saving"
                printf("Exiting Program.\n");
                break;
        }

    }

    return tables;

}

int printActionMenu(Table* table) {

    int menuChoice;

    if(table != NULL) {
        printf("\nYour current table is:\n");
        printTable(*table);
    }
    printf("\nWhat would you like to do?\n");
    printf("1. CREATE a table\n"
        "2. PRINT a table\n"
        "3. CHOOSE new current table\n"
        "4. SELECT from current table\n"
        "5. INSERT a new row into current table\n"
        "6. INSERT a new column into current table\n"
        "7. UPDATE an existing value in current table\n"
        "8. DELETE records from current table\n"
        "9. DELETE current table\n"
        "10. IMPORT Table(s) from .sql File\n"
        "11. IMPORT Table(s) from .db File\n"
        "12. EXPORT Table(s) to .SQL File\n"
        "13. EXPORT Table(s) to .db File\n"
        "0. SAVE & EXIT\n"
        "-1. EXIT WITHOUT SAVING\n"
        "Your choice : ");
    do {
        scanfWell("%d", &menuChoice);
        if(menuChoice < -1 || menuChoice > 13)
            printf("Please choose between -1 and 13: ");
    } while(menuChoice < -1 || menuChoice > 13);

    printf("\n");

    return menuChoice;
}
int printTableMenu(int numTables, Table* tableList) {

    int tableChoice;

    for(int i = 0; i < numTables; i++)
        printf("Table %d. %s\n", i + 1, tableList[i].name);
    printf("Your choice: ");
    do {
        scanfWell("%d", &tableChoice);
        tableChoice--;
        if(tableChoice < 0 || tableChoice >= numTables)
            printf("Please input a valid table. (1-%d): ", numTables);
    } while(tableChoice < 0 || tableChoice >= numTables);

    return tableChoice;
}
int whereInput(Table* currentTable, Where** whereList, char** connectiveList) {

    char yesno[MAX_LEN];
    int numWheres = 0;
    // int numSpaces = 0;
    // char* token;
    // char* token2;
    // static int intVal;
    // static double doubVal;
    // char* stringVal;

    do {
        numWheres++;
        // numSpaces = 0;
        if(numWheres == 1) {
            *whereList = malloc(sizeof(Where));
            *connectiveList = malloc(sizeof(char));
            (*connectiveList)[0] = '~';
        }
        else {
            *whereList = realloc(*whereList, sizeof(Where) * numWheres);
        }

        (*whereList)[numWheres - 1].searchColName = malloc(sizeof(char) * MAX_LEN);
        do {
            printf("Please input the column name for your where statement: ");
            fgetsUntil((*whereList)[numWheres - 1].searchColName, MAX_LEN);
            if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName).type == -1)
                continue;
            else
                break;
        } while(1);
        // for(int i = 0; i < strlen((*whereList)[numWheres - 1].searchColName);i++)
        //     if((*whereList)[numWheres - 1].searchColName[i] == ' ')
        //         numSpaces++;
        // if(numSpaces >= 2) {
        //     (*whereList)[numWheres - 1].comparison = malloc(sizeof(char) * 5);
        //     printf("1\n");
        //     token = strtok((*whereList)[numWheres - 1].searchColName, " ");
        //     printf("2\n");
        //     (*whereList)[numWheres - 1].comparison = strtok((*whereList)[numWheres - 1].searchColName, " ");
        //     printf("3\n");
        //     token2 = strtok((*whereList)[numWheres - 1].searchColName, " ");
        //     printf("4\n");
        //     // strcpy(whereList[numWheres - 1].searchColName, token);
        //     (*whereList)[numWheres - 1].searchColName = token;
        //     printf("%s\n", (*whereList)[numWheres - 1].searchColName);
        //     printf("5\n");
        //     if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName).type == INTEGER) {
        //         printf("INT\n");
        //         intVal = atoi(token2);
        //         (*whereList)[numWheres - 1].searchValue = &intVal;
        //     }
        //     else if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName).type == CHAR) {
        //         printf("CHAR\n");
        //         (*whereList)[numWheres - 1].searchValue = token2;
        //     }
        //     else if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName).type == DECIMAL) {
        //         printf("DECIMAL\n");
        //         doubVal = strtod(token2, NULL);
        //         (*whereList)[numWheres - 1].searchValue = &doubVal;
        //     }
        //     printf("6\n");
        // }
        // else {

        printf("Please enter the comparison you will use (=, !=, <, >, <=, >=): ");
        (*whereList)[numWheres - 1].comparison = malloc(sizeof(char) * MAX_LEN);
        do {
            fgetsUntil((*whereList)[numWheres - 1].comparison, MAX_LEN);
            if(!isValidComp((*whereList)[numWheres - 1].comparison))
                printf("Invalid comparison. Try again: ");
        } while(!isValidComp((*whereList)[numWheres - 1].comparison));

        if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName).type == INTEGER) {
            printf("Please input the integer value you are looking for: ");
            (*whereList)[numWheres - 1].searchValue = malloc(sizeof(int));
            scanfWell("%d", (*whereList)[numWheres - 1].searchValue);
        }
        else if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName).type == CHAR) {
            printf("Please input the string value you are looking for: ");
            (*whereList)[numWheres - 1].searchValue = malloc(sizeof(char) * MAX_LEN);
            scanfWell("%s", (*whereList)[numWheres - 1].searchValue);
        }
        else if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName).type == DECIMAL) {
            printf("Please input the decimal value you are looking for: ");
            (*whereList)[numWheres - 1].searchValue = malloc(sizeof(double));
            scanfWell("%lf", (*whereList)[numWheres - 1].searchValue);
        }
        // }

        printf("Would you like to add another where statement? (yes/no): ");
        do {
            fgetsUntil(yesno, MAX_LEN);
            if(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0)
                printf("Please input 'yes' or 'no': ");
        } while(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0);

        if(strcmp(yesno, "yes") == 0) {
            *connectiveList = realloc(*connectiveList, sizeof(char) * (numWheres + 1));
            printf("Please input the connective to connect the where statement\nyou just made with the new one you're going to make. ('&' or '|'): ");
            do {
                do {
                    scanfWell("%c", &((*connectiveList)[numWheres]));
                    // printf("%c\n", (*connectiveList)[numWheres]);
                } while((*connectiveList)[numWheres - 1] == '\n');
                if((*connectiveList)[numWheres] != '&' && (*connectiveList)[numWheres] != '|')
                    printf("Invalid connective, try again: ");
            } while((*connectiveList)[numWheres] != '&' && (*connectiveList)[numWheres] != '|');
        }
    } while(strcmp(yesno, "yes") == 0);

    return numWheres;
}

int printTypeChart(int colNum) {

    int choice;

    printf("Type Chart:\n"
        "  1. CHAR (String)\n"
        "  2. INTEGER (Int)\n"
        "  3. DECIMAL (Double)\n"
        "  4. DATE\n");
    printf("Type for column #%d: ", colNum);
    do {
        scanfWell("%d", &choice);
        choice--;
        if(choice < 0 || choice > 3)
            printf("Please input a valid type (1-4): ");
    } while(choice < 0 || choice > 3);

    return choice;

}

void printType(int type) {
    if(type == CHAR)
        printf("CHAR");
    else if(type == INTEGER)
        printf("INTEGER");
    else if(type == DECIMAL)
        printf("DECIMAL");
    else
        printf("UNKOWN TYPE");
}

void fgetsUntil(char* string, int size) {
    do {
        fgets(string, size, stdin);
    } while(strcmp(string, "\n") == 0);
    string[strlen(string) - 1] = '\0';
}

void scanfWell(char* formSpec, void* val) {
    char buffer[MAX_LEN];
    int success;

    do {
        fgetsUntil(buffer, MAX_LEN);
        success = sscanf(buffer, formSpec, val);
        if(!success)
            printf("Please try that again: ");
    } while(!success);
}

void sleep(int milliseconds) {
    struct timespec ts;

    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;

    nanosleep(&ts, &ts);
}

// remember SQLITE3 terminal command can also read .sql files.
// sqlite3_exec(sqlite3_open(demo.sql), "CREATE TABLE Mario", NULL, NULL, "Error: SQL Execution Failed");
