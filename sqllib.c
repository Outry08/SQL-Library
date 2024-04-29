#include "sqllib.h"

int main(int argc, char const* argv[]) {

    Table* tables = malloc(sizeof(Table) * 2);

    // Table* tables = userTableOperator();
    tables[0] = create("My Table", 3, nameList(3, "Char Col", "Decimal Col", "Integer Col"), typeList(3, CHAR, DECIMAL, INTEGER));
    printTable(tables[0]);

    insertRow(&tables[0], 2, nameList(2, "Decimal Col", "Char Col"), valueList(2, typeList(2, DECIMAL, CHAR), 44.55, "Luigi"));
    printTable(tables[0]);
    insertRow(&tables[0], 1, nameList(1, "Char Col"), valueList(1, typeList(1, CHAR), "Mario"));
    printTable(tables[0]);

    insertRow(&tables[0], 1, nameList(1, "Integer Col"), valueList(1, typeList(1, INTEGER), 4));
    insertRow(&tables[0], 3, nameList(3, "Integer Col", "Decimal Col", "Char Col"), valueList(3, typeList(3, INTEGER, DECIMAL, CHAR), 44, 88.77, "WAHHLUIGI"));
    printTable(tables[0]);

    Where where1 = newWhere("Char Col", "==", "Luigi");
    double newNum = 9999.999;


    update(&tables[0], 1, (nameList(1, "Decimal Col")), &newNum, 1, whereList(1, where1), connectiveList(0));
    printTable(tables[0]);

    newNum = 0;
    Where where2 = newWhere("Decimal Col", "==", &newNum);

    int newInt = 1735;

    update(&tables[0], 2, nameList(2, "Integer Col", "Decimal Col"), &newInt, 2, whereList(2, where1, where2), connectiveList(1, '|'));
    printTable(tables[0]);

    Where where3 = newWhere("Char Col", "==", "NULL");
    update(&tables[0], 1, nameList(1, "Char Col"), "WAAAAARIOOOOOOO", 1, whereList(1, where3), connectiveList(0));
    printTable(tables[0]);

    insertRow(&tables[0], 1, nameList(1, "Decimal Col"), valueList(1, typeList(1, DECIMAL), 444.0));

    printTable(tables[0]);
    newInt = 666;

    update(&tables[0], 1, nameList(1, "Integer Col"), &newInt, 3, whereList(3, where3, where2, where1), connectiveList(2, '&', '|'));
    printTable(tables[0]);

    Where where4 = newWhere("Integer Col", "==", &newInt);
    update(&tables[0], 1, nameList(1, "Char Col"), "WAAAAAAAAAAAAAAARIOOOOOO", 2, whereList(2, where3, where4), connectiveList(1, '&'));
    printTable(tables[0]);

    update(&tables[0], 1, nameList(1, "Char Col"), "Princess Peach", 1, whereList(1, where3), connectiveList(0));
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

    insertIntoRow(tables, 3, nameList(3, "Char Col", "Integer Col", "Decimal Col"), valueList(3, typeList(3, CHAR, INTEGER, DECIMAL), "Princess Peach", 777, 19.64), 3);

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
    if(numCols > 0)
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
void insertRow(Table* table, int numValues, char** colNames, void** values) {

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
            currCol.values[table->numRows - 1].type = DECIMAL;
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
    if(rowNum > table->numRows || rowNum < 0) {
        printf("Error: Row number out of range.\n");
        return;
    }

    table->numRows++;
    char* colName = "";
    Column currCol;

    for(int i = 0; i < table->numCols; i++) {
        table->cols[i].values = realloc(table->cols[i].values, sizeof(ElementUnion) * table->numRows);
        for(int j = table->numRows - 1; j >= rowNum; j--) {
            memcpy(&table->cols[i].values[j + 1], &table->cols[i].values[j], sizeof(ElementUnion));
        }

        table->cols[i].values = realloc(table->cols[i].values, sizeof(ElementUnion) * table->numRows);
        table->cols[i].values[rowNum].type = vNULL;
    }

    for(int i = 0; i < numValues; i++) {
        colName = strdup(colNames[i]);
        currCol = nameToCol(table, colName);

        if(currCol.type == CHAR) {
            // printf("CHAR VAL\n");
            currCol.values[rowNum].type = CHAR;
            currCol.values[rowNum].CHAR = strdup((char*)values[i]);
        }
        else if(currCol.type == INTEGER) {
            // printf("INTEGER VAL\n");
            currCol.values[rowNum].type = INTEGER;
            currCol.values[rowNum].INTEGER = *(int*)values[i];
        }
        else if(currCol.type == DECIMAL) {
            // printf("DECIMAL VAL\n");
            currCol.values[rowNum].type = DECIMAL;
            currCol.values[rowNum].DECIMAL = *(double*)values[i];
        }
        else {
            printf("Error: Nonexistent column name, \"%s\", provided.\n", colName);
        }

        free(colName);
    }
}

void insertCol(Table* table, char* colName, int colType, int numValues, int* rowNums, void** values) {
    table->numCols++;
    if(table->numCols > 1)
        table->cols = realloc(table->cols, sizeof(Column) * table->numCols);
    else
        table->cols = malloc(sizeof(Column));
    table->cols[table->numCols - 1].type = colType;
    table->cols[table->numCols - 1].name = strdup(colName);
    table->cols[table->numCols - 1].values = malloc(sizeof(ElementUnion) * table->numRows);
    for(int i = 0; i < table->numRows; i++) {
        table->cols[table->numCols - 1].values[i].type = vNULL;
    }

    for(int i = 0; i < numValues; i++) {
        table->cols[table->numCols - 1].values[rowNums[i]].type = colType;
        if(colType == CHAR) {
            table->cols[table->numCols - 1].values[rowNums[i]].CHAR = strdup((char*)values[i]);
        }
        else if(colType == INTEGER) {
            table->cols[table->numCols - 1].values[rowNums[i]].INTEGER = *(int*)values[i];
        }
        else if(colType == DECIMAL) {
            table->cols[table->numCols - 1].values[rowNums[i]].DECIMAL = *(double*)values[i];
        }
        else {
            printf("Error: Nonexistent row number, \"%d\", provided.\n", rowNums[i]);
        }

    }
}

void insertIntoCol(Table* table, char* colName, int colType, int numValues, int* rowNums, void** values, char* colPos) {
    int colNum = letterToInt(colPos) - 1;
    if(colNum < 0 || colNum > table->numCols) {
        printf("Error: Invalid column position provided. Inserting into the end of table.\n");
        insertCol(table, colName, colType, numValues, rowNums, values);
    }
    table->numCols++;

    if(table->numCols > 1)
        table->cols = realloc(table->cols, sizeof(Column) * table->numCols);
    else
        table->cols = malloc(sizeof(Column));

    table->cols[table->numCols - 1].values = malloc(sizeof(ElementUnion) * table->numRows);

    for(int i = table->numCols - 1; i > colNum; i--) {
        table->cols[i] = copyColumn(table->numRows, table->cols[i - 1]);
    }

    table->cols[colNum].type = colType;
    table->cols[colNum].name = strdup(colName);
    table->cols[colNum].values = malloc(sizeof(ElementUnion) * table->numRows);
    for(int i = 0; i < table->numRows; i++) {
        table->cols[colNum].values[i].type = vNULL;
    }

    for(int i = 0; i < numValues; i++) {
        table->cols[colNum].values[rowNums[i]].type = colType;
        if(colType == CHAR) {
            table->cols[colNum].values[rowNums[i]].CHAR = strdup((char*)values[i]);
        }
        else if(colType == INTEGER) {
            table->cols[colNum].values[rowNums[i]].INTEGER = *(int*)values[i];
        }
        else if(colType == DECIMAL) {
            table->cols[colNum].values[rowNums[i]].DECIMAL = *(double*)values[i];
        }
        else {
            printf("Error: Nonexistent row number, \"%d\", provided.\n", rowNums[i]);
        }

    }

}

/**
 * SQL Origin:
 *  UPDATE tableName
 *   SET colName = newValue
 *   WHERE tableName.whereColName =, >, <, >=, <=, != whereValue
*/
void update(Table* table, int numUpdCols, char** colNames, void* newValue, int numWheres, Where* wheres, char* conns) {

    int allType;
    for(int i = 0; i < numUpdCols; i++) {
        if(i == 0)
            allType = nameToCol(table, colNames[i]).type;
        else if(nameToCol(table, colNames[i]).type != allType) {
            printf("Update Error: Not all provided columns are of the same type.\n");
            return;
        }
    }

    Column currCol;
    int* prevGoodJs;
    int numPrevGoodJs;
    int toUpdate[table->numRows];

    // printf("HELLO THERE\n");

    for(int i = 0; i < table->numRows; i++)
        toUpdate[i] = 1;

    // printf("YO THERE\n");

    for(int i = 0; i < numWheres; i++) {
        // printf("HOOOOOOOOO\n");
        prevGoodJs = malloc(sizeof(int));
        numPrevGoodJs = 0;
        for(int j = 0; j < table->numRows; j++) {
            // printf("HAAAAAA\n");
            // printf("CONNS: %c\n", conns[i]);
            switch(conns[i]) {
                case '&':
                case 'a':
                case 'A':
                    if(toUpdate[j] == 1 && !compare(nameToCol(table, wheres[i].searchColName), j, wheres[i].comparison, wheres[i].searchValue))
                        toUpdate[j] = 0;
                    // printf("LLLLLLLLLLLL");
                    break;
                case '|':
                case 'o':
                case 'O':
                    toUpdate[j] = 1;
                    // printf("BBBBBBBB\n");
                case '~':
                    if(!compare(nameToCol(table, wheres[i].searchColName), j, wheres[i].comparison, wheres[i].searchValue))
                        toUpdate[j] = 0;

                    // printf("EEEEEEE\n");
                    break;
                default:
                    printf("Error: Invalid where connective '%c' provided into update function.", conns[i]);
                    break;
            }

            if(toUpdate[j] == 1) {
                // printf("WATCHU\n");
                prevGoodJs = realloc(prevGoodJs, sizeof(int) * (++numPrevGoodJs));
                prevGoodJs[numPrevGoodJs - 1] = j;
                // printf("HOBGOBLIN\n");
            }

        }
        // printf("WHAT'S GOOD THERE\n");
        if((i == numWheres - 1 || conns[i + 1] == '|' || conns[i + 1] == 'o' || conns[i + 1] == 'O') && (numPrevGoodJs > 0 && numPrevGoodJs <= table->numRows)) {

            for(int l = 0; l < numPrevGoodJs; l++) {
                //Equivalent to "deleting" a specific value instead of a row or col
                if(newValue == NULL || strcmp(newValue, "NULL") == 0) {
                    for(int k = 0; k < numUpdCols; k++) {
                        currCol = nameToCol(table, colNames[k]);
                        currCol.values[prevGoodJs[l]].type = vNULL;
                    }
                }
                else if(allType == CHAR) {
                    for(int k = 0; k < numUpdCols; k++) {
                        currCol = nameToCol(table, colNames[k]);
                        currCol.values[prevGoodJs[l]].type = CHAR;
                        currCol.values[prevGoodJs[l]].CHAR = strdup((char*)newValue);
                    }
                }
                else if(allType == INTEGER) {
                    for(int k = 0; k < numUpdCols; k++) {
                        currCol = nameToCol(table, colNames[k]);
                        currCol.values[prevGoodJs[l]].type = INTEGER;
                        currCol.values[prevGoodJs[l]].INTEGER = *((int*)newValue);
                    }
                }
                else if(allType == DECIMAL) {
                    for(int k = 0; k < numUpdCols; k++) {
                        currCol = nameToCol(table, colNames[k]);
                        currCol.values[prevGoodJs[l]].type = DECIMAL;
                        currCol.values[prevGoodJs[l]].DECIMAL = *((double*)newValue);
                    }
                }
            }
        }
        free(prevGoodJs);
    }

    // printf("GOODBYE THERE\n");

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
        // printf("DELETION TIME\n");
        if((i == numWheres - 1 || conns[i + 1] == '|' || conns[i + 1] == 'o' || conns[i + 1] == 'O') && (numPrevGoodJs > 0 && numPrevGoodJs <= table->numRows)) {
            for(int k = 0; k < numPrevGoodJs; k++) {
                for(int l = 0; l < table->numCols; l++) {
                    //Keep an eye on the index calculation: prevGoodJs[k] % (table->numRows). It's working for now, but I'm not 100% confident in it.
                    // table->cols[l].values[prevGoodJs[k] % (table->numRows)] = table->cols[l].values[table->numRows - 1];
                    //This may break. Can almost certainly be optimized. 
                    for(int m = prevGoodJs[k]; m < table->numRows - 1; m++) {
                        // printf("SHIFTING SANDLAND\n");
                        // if(table->cols[l].type == CHAR)
                        //     printf("%s => %s\n", table->cols[l].values[m].CHAR, table->cols[l].values[m + 1].CHAR);
                        memcpy(&table->cols[l].values[m], &table->cols[l].values[m + 1], sizeof(ElementUnion));
                    }
                }
                table->numRows--;
                if(k + 1 < numPrevGoodJs)
                    if(prevGoodJs[k + 1] > prevGoodJs[k])
                        prevGoodJs[k + 1]--;
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

    free(tableCopy.name);
    tableCopy.name = strdup(table.name);

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
    newTable.name = realloc(newTable.name, strlen(newTable.name) + 10);
    strcat(newTable.name, " selected"); //Add selected numbers
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
    newTable.name = realloc(newTable.name, strlen(newTable.name) + 6);
    strcat(newTable.name, " copy"); //Add copy numbers

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

    // printf("ENTERING COPYCOL\n");

    colCopy.name = strdup(col.name);
    colCopy.type = col.type;
    colCopy.values = malloc(sizeof(ElementUnion) * numVals);
    memcpy(colCopy.values, col.values, sizeof(ElementUnion) * numVals);

    // printf("EXITING COPYCOL\n");

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

    printf("\n\t");
    for(int i = 0; i < table.numCols; i++) {
        printf("\e[1m%-*s\e[m", colWidth / 2, " ");
        printf("%s", intToLetter(i));
        printf("\e[1m%-*s\e[m", (int)(colWidth / 2 - strlen(intToLetter(i)) + 1), " ");
    }

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
                    printString[17] = ' ';
                    printString[16] = '.';
                    printString[15] = '.';
                    printString[14] = '.';
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

/**
 * A=0
 * Z=25
 * AA=26
 * AZ=51
*/
char* intToLetter(int number) {
    // int alphaLoop = number / 26;
    // char letter = 65 + (number / 26);
    // char* stringOfLetters = malloc(sizeof(char) * MAX_LEN);

    // int numLetters = 1;
    // int dummy = 26;

    // while(dummy < number) {
    //     dummy *= 26;
    //     numLetters++;
    // }
    char* stringOfLetters = malloc(sizeof(char) * MAX_LEN);

    int remainder = 1, quot = number, i = 0;
    char dummy;

    do {

        remainder = quot % 26;
        quot = quot / 26;
        stringOfLetters[i] = 65 + remainder;
        // printf("Quotient: %d, Remainder: %d, Letter: %c\n", quot, remainder, stringOfLetters[i]);
        i++;
    } while(quot > 0);

    if(i > 1)
        stringOfLetters[i - 1] -= 1;

    stringOfLetters[i] = '\0';

    stringOfLetters = realloc(stringOfLetters, sizeof(char) * (strlen(stringOfLetters) + 1));
    for(int j = 0; j < strlen(stringOfLetters) / 2; j++) {
        dummy = stringOfLetters[j];
        stringOfLetters[j] = stringOfLetters[strlen(stringOfLetters) - j - 1];
        stringOfLetters[strlen(stringOfLetters) - j - 1] = dummy;
    }

    return stringOfLetters;
}

int letterToInt(char* stringOfLetters) {
    int number = 0;
    int j = 0;

    for(int i = strlen(stringOfLetters) - 1; i >= 0; i--) {
        stringOfLetters[i] = toupper(stringOfLetters[i]);
        number += (stringOfLetters[j] - 65 + (j > 0 ? 0 : 1)) * pow(26, i);
        j++;
    }

    return number;
}

Table* userTableOperator(int numTables, Table* tables) {

    Table* currentTable = NULL;

    int* menuChoices;
    int currTableIndex;

    char yesno[MAX_LEN];

    char tableName[MAX_LEN];
    char colName[MAX_LEN];
    int numThings;
    int rowNum;

    char** nameList = NULL;
    int* typeList = NULL;
    void** valueList = NULL;
    Where* whereList = NULL;
    int numWheres = 0;
    char* connectiveList = NULL;
    int* numList;

    Select sel;

    printf("\t\t-- Welcome to CQL! --\n");

    //ADD QUESTION FOR SELECTED TABLE IF THE USER WANTS TO APPLY THE CHANGES TO THE BASE TABLE!

    do {
        numWheres = 0;

        menuChoices = actionMenu(currentTable);

        switch(menuChoices[0]) {
            case 1:
                //"1. CREATE"
                // "1. CREATE a table"
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
                    if(numThings < 0)
                        printf("Please input a positive number or 0: ");
                } while(numThings < 0);
                if(numThings > 0) {
                    nameList = malloc(sizeof(char*) * numThings);
                    typeList = malloc(sizeof(int) * numThings);
                    for(int i = 0; i < numThings; i++) {
                        printf("Name for column #%d: ", i + 1);
                        nameList[i] = malloc(sizeof(char) * MAX_LEN);
                        fgetsUntil(nameList[i], MAX_LEN);
                        nameList[i] = realloc(nameList[i], sizeof(char) * (strlen(nameList[i]) + 1));
                        typeList[i] = typeInput();
                    }
                    tables[numTables - 1] = create(tableName, numThings, nameList, typeList);
                    currentTable = &tables[numTables - 1];
                    currTableIndex = numTables - 1;

                    for(int i = 0; i < numThings; i++) {
                        free(nameList[i]);
                    }
                    free(nameList);
                    free(typeList);
                    nameList = NULL;
                    typeList = NULL;
                }
                else {
                    tables[numTables - 1] = create(tableName, numThings, NULL, NULL);
                    currentTable = &tables[numTables - 1];
                    currTableIndex = numTables - 1;
                }
                break;
            case 2:
                //"2. PRINT"
                // "1. PRINT a table"
                if(numTables > 0) {
                    printf("Which table would you like to print?\n");
                    printTable(tables[tableMenu(numTables, tables)]);
                }
                else
                    printf("There are no tables to print.\n");
                break;
            case 3:
                //"3. CHOOSE"
                // "1. CHOOSE new current table"
                if(numTables > 0) {
                    printf("Which table would you like to become your current table?\n");
                    currTableIndex = tableMenu(numTables, tables);
                    currentTable = &tables[currTableIndex];
                }
                else
                    printf("There are no tables to choose.\n");

                break;
            case 4:
                //"4. RENAME"
                switch(menuChoices[1]) {
                    case 1:
                        // "1. RENAME column in current table"
                        printf("Name of column you wish to rename: ");

                        Column column;

                        do {
                            fgetsUntil(colName, MAX_LEN);
                            column = nameToCol(currentTable, colName);
                            if(column.type == -1)
                                printf("That column does not exist. Please try again: ");
                        } while(column.type == -1);

                        printf("New name for column '%s': ", colName);
                        fgetsUntil(column.name, MAX_LEN);
                        break;

                    case 2:
                        // "2. RENAME current table"
                        printf("New name for table '%s': ", currentTable->name);
                        fgetsUntil(currentTable->name, MAX_LEN);
                        break;
                }
                break;
            case 5:
                //"5. SELECT"
                // "1. SELECT from current table"
                if(numTables <= 0) {
                    printf("There are no tables to select from.\n");
                    break;
                }
                if(currentTable == NULL) {
                    printf("Which table would you like to select from?\n");
                    currTableIndex = tableMenu(numTables, tables);
                    currentTable = &tables[currTableIndex];
                    printf("Here is your current table:\n");
                    printTable(*currentTable);
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
                if(sel.numCols < currentTable->numCols) {
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
                        sel.colNames[i] = realloc(sel.colNames[i], sizeof(char) * (strlen(sel.colNames[i]) + 1));
                    }
                }
                else {
                    for(int i = 0; i < sel.numCols; i++) {
                        sel.colNames[i] = NULL;
                        //sel.colnames[0] = "*";
                    }
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
                currentTable = &(tables[currTableIndex]);

                tables[numTables - 1] = select(*currentTable, sel, numWheres, whereList, connectiveList);

                currentTable = &tables[numTables - 1];
                currTableIndex = numTables - 1;

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

            case 6:
                //"6. INSERT"
                switch(menuChoices[1]) {
                    case 1:
                        // "1. INSERT a new row into current table"
                        if(numTables <= 0) {
                            printf("There are no tables to insert into.\n");
                            break;
                        }
                        if(currentTable == NULL) {
                            printf("Which table would you like to insert into?\n");
                            currTableIndex = tableMenu(numTables, tables);
                            currentTable = &tables[currTableIndex];
                            printf("Here is your current table:\n");
                            printTable(*currentTable);
                        }

                        printf("How many columns would you like to provide values for? (0-%d): ", currentTable->numCols);
                        do {
                            scanfWell("%d", &numThings);
                            if(numThings < 0)
                                printf("Please input a positive number or 0: ");
                            if(numThings > currentTable->numCols)
                                printf("Your current table doesn't have that many columns. Try again: ");
                        } while(numThings < 0 || numThings > currentTable->numCols);
                        if(numThings > 0) {
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

                                    nameList[i] = realloc(nameList[i], sizeof(char) * (strlen(nameList[i]) + 1));

                                    printf("New value for %s (of type ", nameList[i]);
                                    printType(nameToCol(currentTable, nameList[i]).type);
                                    printf("): ");



                                    if(nameToCol(currentTable, nameList[i]).type == INTEGER) {
                                        valueList[i] = malloc(sizeof(int));
                                        scanfWell("%d", valueList[i]);
                                    }
                                    else if(nameToCol(currentTable, nameList[i]).type == CHAR) {
                                        valueList[i] = malloc(sizeof(char) * MAX_LEN);
                                        fgetsUntil(valueList[i], MAX_LEN);
                                        valueList[i] = realloc(valueList[i], sizeof(char) * (strlen(valueList[i]) + 1));
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
                                        fgetsUntil(valueList[i], MAX_LEN);
                                        valueList[i] = realloc(valueList[i], sizeof(char) * (strlen(valueList[i]) + 1));
                                    }
                                    else if(nameToCol(currentTable, nameList[i]).type == DECIMAL) {
                                        valueList[i] = malloc(sizeof(double));
                                        scanfWell("%lf", valueList[i]);
                                    }
                                }
                            }
                        }

                        if(currentTable->numRows > 0) {
                            printf("Which row would you like to insert into? (1-%d): ", currentTable->numRows + 1);
                            do {
                                scanfWell("%d", &rowNum);
                                if(rowNum < 1 || rowNum > currentTable->numRows + 1)
                                    printf("Please input a valid row number. (1-%d): ", currentTable->numRows + 1);
                            } while(rowNum < 1 || rowNum > currentTable->numRows + 1);

                            insertIntoRow(currentTable, numThings, nameList, valueList, rowNum);
                        }
                        else
                            insertRow(currentTable, numThings, nameList, valueList);

                        for(int i = 0; i < numThings; i++) {
                            free(nameList[i]);
                            free(valueList[i]);
                        }
                        free(nameList);
                        free(valueList);
                        nameList = NULL;
                        valueList = NULL;

                        break;
                    case 2:
                        // "2. INSERT a new column into current table"

                        if(numTables <= 0) {
                            printf("There are no tables to insert into.\n");
                            break;
                        }
                        if(currentTable == NULL) {
                            printf("Which table would you like to insert into?\n");
                            currTableIndex = tableMenu(numTables, tables);
                            currentTable = &tables[currTableIndex];
                            printf("Here is your current table:\n");
                            printTable(*currentTable);
                        }

                        // Column* newCol = malloc(sizeof(Column) * 1);
                        int colType;

                        printf("Please input the name of the new column: ");
                        fgetsUntil(colName, MAX_LEN);

                        printf("What type should this column be?:\n");
                        colType = typeInput();

                        // newCol->values = malloc(sizeof(ElementUnion) * currentTable->numRows);
                        // for(int i = 0; i < currentTable->numRows; i++) {
                        //     newCol->values[i].type = vNULL;
                        // }
                        printf("How many rows would you like to provide values for? (0-%d): ", currentTable->numRows);
                        do {
                            scanfWell("%d", &numThings);
                            if(numThings < 0)
                                printf("Please input a positive number or 0: ");
                            if(numThings > currentTable->numRows)
                                printf("Your current table doesn't have that many rows. Try again: ");
                        } while(numThings < 0 || numThings > currentTable->numRows);

                        if(numThings > 0) {
                            valueList = malloc(sizeof(void*) * numThings);
                            numList = malloc(sizeof(int) * numThings);
                            if(numThings < currentTable->numRows) {

                                for(int i = 0; i < numThings; i++) {
                                    printf("Row Number to provide value for (1-%d): ", currentTable->numRows);
                                    do {
                                        scanfWell("%d", &numList[i]);
                                        numList[i]--;
                                        if(numList[i] < 0 || numList[i] >= currentTable->numRows)
                                            printf("Please input a valid row number (1-%d): ", currentTable->numRows);
                                    } while(numList[i] < 0 || numList[i] >= currentTable->numRows);

                                    printf("New value for row #%d (of type ", numList[i] + 1);
                                    printType(colType);
                                    printf("): ");

                                    if(colType == INTEGER) {
                                        valueList[i] = malloc(sizeof(int));
                                        scanfWell("%d", valueList[i]);
                                    }
                                    else if(colType == CHAR) {
                                        valueList[i] = malloc(sizeof(char) * MAX_LEN);
                                        fgetsUntil(valueList[i], MAX_LEN);
                                        valueList[i] = realloc(valueList[i], sizeof(char) * (strlen(valueList[i]) + 1));
                                    }
                                    else if(colType == DECIMAL) {
                                        valueList[i] = malloc(sizeof(double));
                                        scanfWell("%lf", valueList[i]);
                                    }
                                }
                            }
                            else {
                                for(int i = 0; i < numThings; i++) {

                                    numList[i] = i;

                                    printf("New value for row #%d (of type ", i + 1);
                                    printType(colType);
                                    printf("): ");

                                    if(colType == INTEGER) {
                                        valueList[i] = malloc(sizeof(int));
                                        scanfWell("%d", valueList[i]);
                                    }
                                    else if(colType == CHAR) {
                                        valueList[i] = malloc(sizeof(char) * MAX_LEN);
                                        fgetsUntil(valueList[i], MAX_LEN);
                                        valueList[i] = realloc(valueList[i], sizeof(char) * (strlen(valueList[i]) + 1));
                                    }
                                    else if(colType == DECIMAL) {
                                        valueList[i] = malloc(sizeof(double));
                                        scanfWell("%lf", valueList[i]);
                                    }
                                }
                            }
                        }

                        char* colString = malloc(sizeof(char) * MAX_LEN);
                        int colPos;

                        if(currentTable->numCols > 0) {
                            printf("Which column position would you like to insert into? (A-%s): ", intToLetter(currentTable->numCols));
                            do {
                                fgetsUntil(colString, MAX_LEN);
                                colPos = letterToInt(colString) - 1;
                                if(colPos < 0 || colPos > currentTable->numCols)
                                    printf("Please input a valid column position. (A-%s): ", intToLetter(currentTable->numCols));
                            } while(colPos < 0 || colPos > currentTable->numCols);
                            printf("\n%d\n", colPos);

                            // currentTable->cols[colPos] = *newCol;
                            insertIntoCol(currentTable, colName, colType, numThings, numList, valueList, colString);
                            // memcpy(&currentTable->cols[colPos], newCol, sizeof(Column));
                            // currentTable->cols[colPos] = copyColumn(currentTable->numRows, *newCol);
                        }
                        else {
                            insertCol(currentTable, colName, colType, numThings, numList, valueList);
                        }

                        if(valueList != NULL) {
                            for(int i = 0; i < numThings; i++)
                                free(valueList[i]);
                            free(valueList);
                            free(numList);
                        }
                        free(colString);
                        valueList = NULL;
                        numList = NULL;

                        break;
                }
                break;
            case 7:
                //"7. UPDATE"
                // "1. UPDATE an existing value in current table"
                break;
            case 8:
                //"8. SWAP"
                // "1. SWAP two rows in current table\n"
                // "2. SWAP two columns in current table\n"
                break;
            case 9:
                //"9. COPY"
                // "1. COPY row in current table\n"
                // "2. COPY column in current table\n"
                // "3. Make a COPY of current table\n"
                break;
            case 10:
                //"10. PASTE"
                // "1. PASTE row in current table\n"
                // "2. PASTE column in current table\n"
                break;
            case 11:
                //"11. DELETE"
                // "1. DELETE row(s) from current table\n"
                // "2. DELETE column(s) from current table\n"
                // "3. DELETE value(s) from current table\n"
                // "4. DELETE current table\n"
                break;
            case 12:
                //"12. IMPORT"
                // "1. IMPORT Table(s) from .sql File\n"
                // "2. IMPORT Table(s) from .db File\n"
                break;
            case 13:
                //"13. EXPORT"
                // "1. EXPORT Table(s) to .SQL File\n"
                // "2. EXPORT Table(s) to .db File\n"
                break;

                /*
                perhaps incorporate a where or select saving system, allowing the user to swiftly use frequently used where or select statements.
                I would save these in a separate .cql file separate from the .sql file that can be converted to .db.
                I could add other useful CQL specific saves later on.
                */

            case 0:
                //"0. EXIT"
                switch(menuChoices[1]) {
                    case 1:
                        // "1. SAVE & EXIT"
                        printf("Saving\n");
                        for(int i = 0; i < 3; i++) {
                            sleep(750);
                            printf(".\n");
                        }
                        sleep(1000);
                        printf("Database Saved.\n");
                        break;
                    case 2:
                        // "2. EXIT WITHOUT SAVING"
                        printf("Exiting Program.\n");
                        break;
                }
                break;

        }

    } while(menuChoices[0] > 0);

    return tables;

}

int* actionMenu(Table* table) {

    int* menuChoices = malloc(sizeof(int) * 2);
    int numOptions;

    if(table != NULL) {
        printf("\nYour current table is:\n");
        printTable(*table);
    }
    do {
        printf("\nWhat would you like to do?\n");
        printf("1. CREATE\n"
            "2. PRINT\n"
            "3. CHOOSE\n"
            "4. RENAME\n"
            "5. SELECT\n"
            "6. INSERT\n"
            "7. UPDATE\n"
            "8. SWAP\n"
            "9. COPY\n"
            "10. PASTE\n"
            "11. DELETE\n"
            "12. IMPORT\n"
            "13. EXPORT\n"
            "0. EXIT\n"
            "Your choice : ");
        do {
            scanfWell("%d", &menuChoices[0]);
            if(menuChoices[0] < 0 || menuChoices[0] > 13)
                printf("Please choose between 0 and 13: ");
        } while(menuChoices[0] < 0 || menuChoices[0] > 13);

        switch(menuChoices[0]) {
            case 1:
                printf("1. CREATE a table\n");
                numOptions = 1;
                break;

            case 2:
                printf("1. PRINT a table\n");
                numOptions = 1;
                break;

            case 3:
                printf("1. CHOOSE new current table\n");
                numOptions = 1;
                break;

            case 4:
                printf("1. RENAME column in current table\n"
                    "2. RENAME current table\n");
                numOptions = 2;
                break;

            case 5:
                printf("1. SELECT from current table\n");
                numOptions = 1;
                break;

            case 6:
                printf("1. INSERT a new row into current table\n"
                    "2. INSERT a new column into current table\n");
                numOptions = 2;
                break;

            case 7:
                printf("1. UPDATE an existing value in current table\n");
                numOptions = 1;
                break;

            case 8:
                printf("1. SWAP two rows in current table\n"
                    "2. SWAP two columns in current table\n");
                numOptions = 2;
                break;

            case 9:
                printf("1. COPY row in current table\n"
                    "2. COPY column in current table\n"
                    "3. Make a COPY of current table\n");
                numOptions = 3;
                break;

            case 10:
                printf("1. PASTE row in current table\n"
                    "2. PASTE column in current table\n");
                numOptions = 2;
                break;

            case 11:
                printf("1. DELETE row(s) from current table\n"
                    "2. DELETE column(s) from current table\n"
                    "3. DELETE value(s) from current table\n"
                    "4. DELETE current table\n");
                numOptions = 4;
                break;

            case 12:
                printf("1. IMPORT Table(s) from .sql File\n"
                    "2. IMPORT Table(s) from .db File\n");
                numOptions = 2;
                break;

            case 13:
                printf("1. EXPORT Table(s) to .SQL File\n"
                    "2. EXPORT Table(s) to .db File\n");
                numOptions = 2;
                break;

            case 0:
                printf("1. SAVE & EXIT\n"
                    "2. EXIT WITHOUT SAVING\n");
                numOptions = 2;
                break;

        }
        printf("0. Back\n"
            "Your choice : ");
        do {
            scanfWell("%d", &menuChoices[1]);
            if(menuChoices[1] < 0 || menuChoices[1] > numOptions)
                printf("Please choose between 0 and %d: ", numOptions);
        } while(menuChoices[1] < 0 || menuChoices[1] > numOptions);
    } while(menuChoices[1] == 0);

    // printf("1. CREATE a table\n"
    //     "2. PRINT a table\n"
    //     "3. CHOOSE new current table\n"
    //     "4. RENAME column in current table\n"
    //     "5. RENAME current table\n"
    //     "6. SELECT from current table\n"
    //     "7. INSERT a new row into current table\n"
    //     "8. INSERT a new column into current table\n"
    //     "9. UPDATE an existing value in current table\n"
    //     "10. SWAP two rows in current table\n"
    //     "11. SWAP two columns in current table\n"
    //     "12. COPY row in current table\n"
    //     "13. PASTE row in current table\n"
    //     "14. COPY column in current table\n"
    //     "15. PASTE column in current table\n"
    //     "16. Make a Copy of current table\n"
    //     "17. DELETE row(s) from current table\n"
    //     "18. DELETE column(s) from current table\n"
    //     "19. DELETE value(s) from current table\n"
    //     "20. DELETE current table\n"
    //     "21. IMPORT Table(s) from .sql File\n"
    //     "22. IMPORT Table(s) from .db File\n"
    //     "23. EXPORT Table(s) to .SQL File\n"
    //     "24. EXPORT Table(s) to .db File\n"
    //     "0. SAVE & EXIT\n"
    //     "-1. EXIT WITHOUT SAVING\n"
    //     "Your choice : ");
    // do {
    //     scanfWell("%d", &menuChoices[1]);
    //     if(menuChoices[1] < -1 || menuChoices[1] > 24)
    //         printf("Please choose between -1 and 24: ");
    // } while(menuChoices[1] < -1 || menuChoices[1] > 24);

    printf("\n");

    return menuChoices;
}
int tableMenu(int numTables, Table* tableList) {

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
            *connectiveList = realloc(*connectiveList, sizeof(char) * numWheres);
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

        (*whereList)[numWheres - 1].searchColName = realloc((*whereList)[numWheres - 1].searchColName, sizeof(char) * (strlen((*whereList)[numWheres - 1].searchColName) + 1));

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
        (*whereList)[numWheres - 1].comparison = realloc((*whereList)[numWheres - 1].comparison, sizeof(char) * (strlen((*whereList)[numWheres - 1].comparison) + 1));

        if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName).type == INTEGER) {
            printf("Please input the integer value you are looking for: ");
            (*whereList)[numWheres - 1].searchValue = malloc(sizeof(int));
            scanfWell("%d", (*whereList)[numWheres - 1].searchValue);
        }
        else if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName).type == CHAR) {
            printf("Please input the string value you are looking for: ");
            (*whereList)[numWheres - 1].searchValue = malloc(sizeof(char) * MAX_LEN);
            fgetsUntil((*whereList)[numWheres - 1].searchValue, MAX_LEN);
            (*whereList)[numWheres - 1].searchValue = realloc((*whereList)[numWheres - 1].searchValue, sizeof(char) * (strlen((*whereList)[numWheres - 1].searchValue) + 1));
            // printf("%s\n", (*whereList)[numWheres - 1].searchValue);
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

int typeInput(void) {

    int choice;

    printf("Type Chart:\n"
        "  1. CHAR (String)\n"
        "  2. INTEGER (Int)\n"
        "  3. DECIMAL (Double)\n"
        "  4. DATE\n");
    printf("Type for column: ");
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
    // printf("%s\n", string);
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
