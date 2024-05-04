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


    update(&tables[0], 1, (nameList(1, "Decimal Col")), valueList(1, typeList(1, DECIMAL), 9999.999), 1, whereList(1, where1), connectiveList(0));
    printTable(tables[0]);

    newNum = 0;
    Where where2 = newWhere("Decimal Col", "==", &newNum);

    int newInt = 1735;

    update(&tables[0], 2, nameList(2, "Integer Col", "Decimal Col"), valueList(2, typeList(2, INTEGER, DECIMAL), 1738, 22.5), 2, whereList(2, where1, where2), connectiveList(1, '|'));
    printTable(tables[0]);

    Where where3 = newWhere("Char Col", "==", "NULL");
    update(&tables[0], 1, nameList(1, "Char Col"), valueList(1, typeList(1, CHAR), "WAAAAARIOOOOOOO"), 1, whereList(1, where3), connectiveList(0));
    printTable(tables[0]);

    insertRow(&tables[0], 1, nameList(1, "Decimal Col"), valueList(1, typeList(1, DECIMAL), 444.0));

    printTable(tables[0]);
    newInt = 666;

    update(&tables[0], 1, nameList(1, "Integer Col"), valueList(1, typeList(1, INTEGER), newInt), 3, whereList(3, where3, where2, where1), connectiveList(2, '&', '|'));
    printTable(tables[0]);

    Where where4 = newWhere("Integer Col", "==", &newInt);
    update(&tables[0], 1, nameList(1, "Char Col"), valueList(1, typeList(1, CHAR), "WAAAAAAAAAAAAAAARIOOOOOO"), 2, whereList(2, where3, where4), connectiveList(1, '&'));
    printTable(tables[0]);

    update(&tables[0], 1, nameList(1, "Char Col"), valueList(1, typeList(1, CHAR), "Princess Peach"), 1, whereList(1, where3), connectiveList(0));
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
        table->cols[i].values = realloc(table->cols[i].values, sizeof(Value) * table->numRows);
        table->cols[i].values[table->numRows - 1].isNULL = 1;
        // if(table->cols[i].type == CHAR)
        //     table->cols[i].values[table->numRows - 1].CHAR = "NULL";
        // else if(table->cols[i].type == INTEGER)
        //     table->cols[i].values[table->numRows - 1].INTEGER = 0;
        // else if(table->cols[i].type == DECIMAL)
        //     table->cols[i].values[table->numRows - 1].DECIMAL = 0.0;
    }

    for(int i = 0; i < numValues; i++) {
        colName = strdup(colNames[i]);
        currCol = nameToCol(table, colName, NULL);

        if(currCol.type == CHAR) {
            // printf("CHAR VAL\n");
            currCol.values[table->numRows - 1].isNULL = 0;
            currCol.values[table->numRows - 1].val.CHAR = strdup((char*)values[i]);
        }
        else if(currCol.type == INTEGER) {
            // printf("INTEGER VAL\n");
            currCol.values[table->numRows - 1].isNULL = 0;
            currCol.values[table->numRows - 1].val.INTEGER = *(int*)values[i];
        }
        else if(currCol.type == DECIMAL) {
            // printf("DECIMAL VAL\n");
            currCol.values[table->numRows - 1].isNULL = 0;
            currCol.values[table->numRows - 1].val.DECIMAL = *(double*)values[i];
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
        table->cols[i].values = realloc(table->cols[i].values, sizeof(Value) * table->numRows);
        for(int j = table->numRows - 1; j >= rowNum; j--) {
            memcpy(&table->cols[i].values[j + 1], &table->cols[i].values[j], sizeof(Value));

            // if(table->cols[i].type == INTEGER) {
            //     table->cols[i].values[j + 1].type = table->cols[i].values[j].type;
            //     table->cols[i].values[j + 1].INTEGER = table->cols[i].values[j].INTEGER;
            // }
            // else if(table->cols[i].type == DECIMAL) {
            //     table->cols[i].values[j + 1].type = table->cols[i].values[j].type;
            //     table->cols[i].values[j + 1].INTEGER = table->cols[i].values[j].DECIMAL;
            // }
            // else if(table->cols[i].type == CHAR) {
            //     table->cols[i].values[j + 1].type = table->cols[i].values[j].type;
            //     table->cols[i].values[j + 1].CHAR = strdup(table->cols[i].values[j].CHAR);
            // }
        }

        table->cols[i].values = realloc(table->cols[i].values, sizeof(Value) * table->numRows);
        table->cols[i].values[rowNum].isNULL = 1;
    }

    for(int i = 0; i < numValues; i++) {
        colName = strdup(colNames[i]);
        currCol = nameToCol(table, colName, NULL);

        if(currCol.type == CHAR) {
            // printf("CHAR VAL\n");
            currCol.values[rowNum].isNULL = 0;
            currCol.values[rowNum].val.CHAR = strdup((char*)values[i]);
        }
        else if(currCol.type == INTEGER) {
            // printf("INTEGER VAL\n");
            currCol.values[rowNum].isNULL = 0;
            currCol.values[rowNum].val.INTEGER = *(int*)values[i];
        }
        else if(currCol.type == DECIMAL) {
            // printf("DECIMAL VAL\n");
            currCol.values[rowNum].isNULL = 0;
            currCol.values[rowNum].val.DECIMAL = *(double*)values[i];
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
    table->cols[table->numCols - 1].values = malloc(sizeof(Value) * table->numRows);
    for(int i = 0; i < table->numRows; i++) {
        table->cols[table->numCols - 1].values[i].isNULL = 1;
    }

    for(int i = 0; i < numValues; i++) {
        if(colType == CHAR) {
            table->cols[table->numCols - 1].values[rowNums[i]].isNULL = 0;
            table->cols[table->numCols - 1].values[rowNums[i]].val.CHAR = strdup((char*)values[i]);
        }
        else if(colType == INTEGER) {
            table->cols[table->numCols - 1].values[rowNums[i]].isNULL = 0;
            table->cols[table->numCols - 1].values[rowNums[i]].val.INTEGER = *(int*)values[i];
        }
        else if(colType == DECIMAL) {
            table->cols[table->numCols - 1].values[rowNums[i]].isNULL = 0;
            table->cols[table->numCols - 1].values[rowNums[i]].val.DECIMAL = *(double*)values[i];
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

    table->cols[table->numCols - 1].values = malloc(sizeof(Value) * table->numRows);

    for(int i = table->numCols - 1; i > colNum; i--) {
        table->cols[i] = copyColumn(table->numRows, table->cols[i - 1]);
    }

    table->cols[colNum].type = colType;
    table->cols[colNum].name = strdup(colName);
    table->cols[colNum].values = malloc(sizeof(Value) * table->numRows);
    for(int i = 0; i < table->numRows; i++) {
        table->cols[colNum].values[i].isNULL = 1;
    }

    for(int i = 0; i < numValues; i++) {
        if(colType == CHAR) {
            table->cols[colNum].values[rowNums[i]].isNULL = 0;
            table->cols[colNum].values[rowNums[i]].val.CHAR = strdup((char*)values[i]);
        }
        else if(colType == INTEGER) {
            table->cols[colNum].values[rowNums[i]].isNULL = 0;
            table->cols[colNum].values[rowNums[i]].val.INTEGER = *(int*)values[i];
        }
        else if(colType == DECIMAL) {
            table->cols[colNum].values[rowNums[i]].isNULL = 0;
            table->cols[colNum].values[rowNums[i]].val.DECIMAL = *(double*)values[i];
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
void update(Table* table, int numUpdCols, char** colNames, void** newValues, int numWheres, Where* wheres, char* conns) {

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
                    if(toUpdate[j] == 1 && !compare(nameToCol(table, wheres[i].searchColName, NULL), j, wheres[i].comparison, wheres[i].searchValue))
                        toUpdate[j] = 0;
                    // printf("LLLLLLLLLLLL");
                    break;
                case '|':
                case 'o':
                case 'O':
                    toUpdate[j] = 1;
                    // printf("BBBBBBBB\n");
                case '~':
                    if(!compare(nameToCol(table, wheres[i].searchColName, NULL), j, wheres[i].comparison, wheres[i].searchValue))
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
                for(int k = 0; k < numUpdCols; k++) {
                    currCol = nameToCol(table, colNames[k], NULL);
                    if(newValues[k] == NULL || strcmp(newValues[k], "NULL") == 0) {
                        currCol.values[prevGoodJs[l]].isNULL = 1;
                    }
                    else if(currCol.type == CHAR) {
                        currCol.values[prevGoodJs[l]].isNULL = 0;
                        currCol.values[prevGoodJs[l]].val.CHAR = strdup((char*)newValues[k]);
                    }
                    else if(currCol.type == INTEGER) {
                        currCol.values[prevGoodJs[l]].isNULL = 0;
                        currCol.values[prevGoodJs[l]].val.INTEGER = *((int*)newValues[k]);
                    }
                    else if(currCol.type == DECIMAL) {
                        currCol.values[prevGoodJs[l]].isNULL = 0;
                        currCol.values[prevGoodJs[l]].val.DECIMAL = *((double*)newValues[k]);
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
                    if(toDelete[j] == 1 && !compare(nameToCol(table, wheres[i].searchColName, NULL), j, wheres[i].comparison, wheres[i].searchValue))
                        toDelete[j] = 0;
                    break;
                case '|':
                case 'o':
                case 'O':
                    toDelete[j] = 1;
                case '~':
                    if(!compare(nameToCol(table, wheres[i].searchColName, NULL), j, wheres[i].comparison, wheres[i].searchValue))
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

                        memcpy(&table->cols[l].values[m], &table->cols[l].values[m + 1], sizeof(Value));

                        // if(table->cols[l].type == INTEGER) {
                        //     table->cols[l].values[m].isNULL = 0;
                        //     table->cols[l].values[m].INTEGER = table->cols[l].values[m + 1].INTEGER;
                        // }
                        // else if(table->cols[l].type == DECIMAL) {
                        //     table->cols[l].values[m].isNULL = 0;
                        //     table->cols[l].values[m].INTEGER = table->cols[l].values[m + 1].DECIMAL;
                        // }
                        // else if(table->cols[l].type == CHAR) {
                        //     table->cols[l].values[m].isNULL = 0;
                        //     table->cols[l].values[m].CHAR = strdup(table->cols[l].values[m + 1].CHAR);
                        // }
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

    newTable.name = malloc(sizeof(char) * MAX_LEN);

    strcpy(newTable.name, "Selected from ");

    strcat(newTable.name, baseTable.name);
    // printf("1\n");
    newTable.name = realloc(newTable.name, sizeof(char) * (strlen(newTable.name) + 1));
    newTable.cols = malloc(sizeof(Column) * numCols);

    newTable.numCols = numCols;
    newTable.numRows = baseTable.numRows;

    // int allAggs = 1;

    // char* newName;

    for(int i = 0; i < numCols; i++) {
        if(!isAggregate(colNames[i])) {
            // printf("2.1\n");
            newTable.cols[i] = copyColumn(baseTable.numRows, nameToCol(&baseTable, colNames[i], NULL));
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
        //     newTable.cols[i].values = malloc(sizeof(Value) * newTable.numRows));
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

    newTable.name = malloc(sizeof(char) * MAX_LEN);

    strcpy(newTable.name, "Copy of ");
    // strdup(table.name);
    // newTable.name = realloc(newTable.name, strlen(newTable.name) + 6);
    strcat(newTable.name, table.name);

    newTable.name = realloc(newTable.name, sizeof(char) * (strlen(newTable.name) + 1));

    newTable.numCols = table.numCols;
    newTable.numRows = table.numRows;

    newTable.cols = malloc(sizeof(Column) * newTable.numCols);

    for(int i = 0; i < newTable.numCols; i++)
        newTable.cols[i] = copyColumn(table.numRows, table.cols[i]);

    return newTable;
}

Column copyColumn(int numVals, Column col) {
    Column colCopy;

    // printf("ENTERING COPYCOL\n");

    colCopy.name = strdup(col.name);
    colCopy.type = col.type;
    colCopy.values = malloc(sizeof(Value) * numVals);
    for(int i = 0; i < numVals; i++) {
        colCopy.values[i].isNULL = col.values[i].isNULL;
        if(!colCopy.values[i].isNULL) {
            if(colCopy.type == INTEGER) {
                colCopy.values[i].val.INTEGER = col.values[i].val.INTEGER;
            }
            else if(colCopy.type == CHAR) {
                colCopy.values[i].val.CHAR = strdup(col.values[i].val.CHAR);
            }
            else if(colCopy.type == DECIMAL) {
                colCopy.values[i].val.DECIMAL = col.values[i].val.DECIMAL;
            }
        }
    }
    // for(int i = 0; i < numVals;i++) {
    //     memcpy(&colCopy.values[i].val, &col.values[i].val, sizeof(Value));
    // }

    // printf("EXITING COPYCOL\n");

    return colCopy;
}

LoneValue* copyRow(Table* table, int rowNum) {

    LoneValue* rowCopy = malloc(sizeof(Value) * table->numCols);
    for(int i = 0; i < table->numCols; i++) {
        rowCopy[i].value.isNULL = table->cols[i].values[rowNum].isNULL;
        rowCopy[i].type = table->cols[i].type;
        // printType(table->cols[i].values[rowNum].type);
        // printf("\n%s\n", table->cols[i].name);
        // printType(table->cols[i].type);
        if(!rowCopy[i].value.isNULL) {
            if(table->cols[i].type == INTEGER) {
                rowCopy[i].value.val.INTEGER = table->cols[i].values[rowNum].val.INTEGER;
            }
            else if(table->cols[i].type == CHAR) {
                rowCopy[i].value.val.CHAR = strdup(table->cols[i].values[rowNum].val.CHAR);
            }
            else if(table->cols[i].type == DECIMAL) {
                rowCopy[i].value.val.DECIMAL = table->cols[i].values[rowNum].val.DECIMAL;
            }

            // memcpy(&rowCopy[i].value.val, &table->cols[i].values[rowNum].val, sizeof(Value));
            // rowCopy[i].value.val.CHAR = strdup(table->cols[i].values[rowNum].val.CHAR);
        }
        // printf("ANNUNCEATE\n");
    }

    // printf("I DID IT\n");

    return rowCopy;

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

Column nameToCol(Table* table, char* colName, int* colIndex) {

    for(int i = 0; i < table->numCols; i++)
        if(strcmp(table->cols[i].name, colName) == 0) {
            if(colIndex != NULL)
                *colIndex = i;
            return table->cols[i];
        }

    Column errCol;
    errCol.name = "COL NOT FOUND";
    errCol.type = -1;
    if(colIndex != NULL)
        *colIndex = -1;
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
        if(column.values[valIndex].isNULL) {
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
            return strcmp(column.values[valIndex].val.CHAR, (char*)value) == 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].val.INTEGER == *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].val.DECIMAL == *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, "<") == 0) {
        if(column.values[valIndex].isNULL) {
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
            return strcmp(column.values[valIndex].val.CHAR, (char*)value) < 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].val.INTEGER < *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].val.DECIMAL < *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, "<=") == 0) {
        if(column.values[valIndex].isNULL) {
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
            return strcmp(column.values[valIndex].val.CHAR, (char*)value) <= 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].val.INTEGER <= *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].val.DECIMAL <= *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, ">") == 0) {
        if(column.values[valIndex].isNULL) {
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
            return strcmp(column.values[valIndex].val.CHAR, (char*)value) > 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].val.INTEGER > *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].val.DECIMAL > *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, ">=") == 0) {
        if(column.values[valIndex].isNULL) {
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
            return strcmp(column.values[valIndex].val.CHAR, (char*)value) >= 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].val.INTEGER >= *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].val.DECIMAL >= *((double*)value);
        else
            return 0;
    }
    else if(strcmp(comparison, "<>") == 0 || strcmp(comparison, "!=") == 0) {
        if(column.values[valIndex].isNULL) {
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
            return strcmp(column.values[valIndex].val.CHAR, (char*)value) != 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].val.INTEGER != *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].val.DECIMAL != *((double*)value);
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

Table createMasterTable(Table* tableList, int numTables) {
    // char** nameList = malloc(sizeof(char*)*numTables);
    // for(int i = 0; i < numTables; i++) {
    //     // nameList[i] = strdup(tableList[i].name);
    // }
    Table masterTable = create("MASTER", 3, nameList(3, "Name", "Num Cols", "Num Rows"), typeList(3, CHAR, INTEGER, INTEGER));
    for(int i = 0; i < numTables;i++) {
        insertRow(&masterTable, 3, nameList(3, "Name", "Num Cols", "Num Rows"), valueList(3, typeList(3, CHAR, INTEGER, INTEGER), tableList[i].name, tableList[i].numCols, tableList[i].numRows));
    }

    return masterTable;
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

    printSeparatorLine(table.numCols, 0);

    for(int i = 0; i < table.numCols; i++)
        printf("| \e[1m%-*s\e[m", colWidth - 2, table.cols[i].name);
    printf("|");

    for(int i = 0; i < table.numRows; i++) {
        printSeparatorLine(table.numCols, i + 1);
        for(int j = 0; j < table.numCols; j++) {
            if(table.cols[j].values[i].isNULL == 1)
                printf("| %-*s ", colWidth - 3, "NULL");

            else if(table.cols[j].type == CHAR) {
                sprintf(printString, "%s", table.cols[j].values[i].val.CHAR);
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
                sprintf(printString, "%d", table.cols[j].values[i].val.INTEGER);
                printf("| %-*s ", colWidth - 3, printString);
            }
            else if(table.cols[j].type == DECIMAL) {
                sprintf(printString, "%.3lf", table.cols[j].values[i].val.DECIMAL);
                printf("| %-*s ", colWidth - 3, printString);
            }
        }
        printf("|");
    }

    printSeparatorLine(table.numCols, 0);
    printf("\n");
}

void printSeparatorLine(int numCols, int rowNum) {
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

void printRow(Table table, int rowIndex) {

    printf("\t");
    for(int i = 0; i < table.numCols; i++) {
        printf(" | ");
        if(table.cols[i].values[rowIndex].isNULL) {
            printf("NULL");
        }
        else {
            if(table.cols[i].type == INTEGER) {
                printf("%d", table.cols[i].values[rowIndex].val.INTEGER);
            }
            else if(table.cols[i].type == CHAR) {
                printf("%s", table.cols[i].values[rowIndex].val.CHAR);
            }
            else if(table.cols[i].type == DECIMAL) {
                printf("%lf", table.cols[i].values[rowIndex].val.DECIMAL);
            }
        }
    }

    printf(" | \n");
}

void printLoneRow(LoneValue* row, int numValues) {
    printf("\t");
    for(int i = 0; i < numValues; i++) {
        printf(" | ");
        if(row[i].value.isNULL) {
            printf("NULL");
        }
        else {
            if(row[i].type == INTEGER) {
                printf("%d", row[i].value.val.INTEGER);
            }
            else if(row[i].type == CHAR) {
                printf("%s", row[i].value.val.CHAR);
            }
            else if(row[i].type == DECIMAL) {
                printf("%lf", row[i].value.val.DECIMAL);
            }
        }
    }

    printf(" | \n");
}

void printColumn(Column col, int numValues) {
    for(int i = 0; i < numValues; i++) {
        printf("\t| ");
        if(col.values[i].isNULL) {
            printf("NULL");
        }
        else {
            if(col.type == INTEGER) {
                printf("%d", col.values[i].val.INTEGER);
            }
            else if(col.type == CHAR) {
                printf("%s", col.values[i].val.CHAR);
            }
            else if(col.type == DECIMAL) {
                printf("%lf", col.values[i].val.DECIMAL);
            }
        }
        printf(" |\n");
    }
    printf("\n");
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

    LoneValue* rowCopy;
    int rowCopyLength;
    Column colCopy;
    int colCopyLength;

    printf("\t\t-- Welcome to CQL! --\n");

    //ADD QUESTION FOR SELECTED TABLE IF THE USER WANTS TO APPLY THE CHANGES TO THE BASE TABLE!

    do {
        numWheres = 0;

        menuChoices = actionMenu(currentTable);

        switch(menuChoices[0]) {
            case 1:
                //"1. CREATE"
                // "1. CREATE a table"

                printf("What is the name of your new table?: ");
                fgetsUntil(tableName, MAX_LEN);

                checkTableNames(tables, numTables, tableName, numTables);

                numTables++;
                if(numTables == 1)
                    tables = malloc(sizeof(Table));
                else
                    tables = realloc(tables, sizeof(Table) * numTables);

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
                switch(menuChoices[1]) {
                    case 1:
                        //PRINT the Master Table
                        // printf("\t\tTHE MASTER TABLE\n\n");
                        // for(int i = 0; i < numTables; i++)
                        //     printf("Table %d: %s\n\tNumber of Columns: %d\n\tNumber of Rows: %d\n\n", i + 1, tables[i].name, tables[i].numCols, tables[i].numRows);
                        printTable(createMasterTable(tables, numTables));
                        break;
                    case 2:
                        // "2. PRINT a table"
                        if(numTables > 0) {
                            printf("Which table would you like to print?\n");
                            printTable(tables[tableMenu(numTables, tables)]);
                        }
                        else
                            printf("There are no tables to print.\n");
                        break;

                }
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
                        int colIndex;

                        do {
                            fgetsUntil(colName, MAX_LEN);
                            column = nameToCol(currentTable, colName, &colIndex);
                            if(column.type == -1)
                                printf("That column does not exist. Please try again: ");
                        } while(column.type == -1);

                        printf("New name for column '%s': ", colName);
                        fgetsUntil(column.name, MAX_LEN);
                        checkColumnNames(*currentTable, column.name, colIndex);
                        break;

                    case 2:
                        // "2. RENAME current table"
                        printf("New name for table '%s': ", currentTable->name);
                        fgetsUntil(currentTable->name, MAX_LEN);
                        checkTableNames(tables, numTables, currentTable->name, currTableIndex);
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
                            if(nameToCol(currentTable, sel.colNames[i], NULL).type == -1)
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
                                        if(nameToCol(currentTable, nameList[i], NULL).type == -1)
                                            continue;
                                        else
                                            break;
                                    } while(1);

                                    nameList[i] = realloc(nameList[i], sizeof(char) * (strlen(nameList[i]) + 1));

                                    printf("New value for %s (of type ", nameList[i]);
                                    printType(nameToCol(currentTable, nameList[i], NULL).type);
                                    printf("): ");



                                    if(nameToCol(currentTable, nameList[i], NULL).type == INTEGER) {
                                        valueList[i] = malloc(sizeof(int));
                                        scanfWell("%d", valueList[i]);
                                    }
                                    else if(nameToCol(currentTable, nameList[i], NULL).type == CHAR) {
                                        valueList[i] = malloc(sizeof(char) * MAX_LEN);
                                        fgetsUntil(valueList[i], MAX_LEN);
                                        valueList[i] = realloc(valueList[i], sizeof(char) * (strlen(valueList[i]) + 1));
                                    }
                                    else if(nameToCol(currentTable, nameList[i], NULL).type == DECIMAL) {
                                        valueList[i] = malloc(sizeof(double));
                                        scanfWell("%lf", valueList[i]);
                                    }
                                }
                            }
                            else {
                                for(int i = 0; i < numThings; i++) {
                                    nameList[i] = strdup(currentTable->cols[i].name);

                                    printf("New value for %s (of type ", nameList[i]);
                                    printType(nameToCol(currentTable, nameList[i], NULL).type);
                                    printf("): ");

                                    if(nameToCol(currentTable, nameList[i], NULL).type == INTEGER) {
                                        valueList[i] = malloc(sizeof(int));
                                        scanfWell("%d", valueList[i]);
                                    }
                                    else if(nameToCol(currentTable, nameList[i], NULL).type == CHAR) {
                                        valueList[i] = malloc(sizeof(char) * MAX_LEN);
                                        fgetsUntil(valueList[i], MAX_LEN);
                                        valueList[i] = realloc(valueList[i], sizeof(char) * (strlen(valueList[i]) + 1));
                                    }
                                    else if(nameToCol(currentTable, nameList[i], NULL).type == DECIMAL) {
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

                        checkColumnNames(*currentTable, colName, currentTable->numCols);

                        printf("What type should this column be?:\n");
                        colType = typeInput();

                        // newCol->values = malloc(sizeof(Value) * currentTable->numRows);
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
                            // printf("\n%d\n", colPos);

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

                printf("How would you like to select the values to be updated?\n");
                printf("1. Using column names and a where statement\n");
                printf("2. Using the coordinate system (column letters and row numbers)\n");
                printf("Choice: ");
                do {
                    scanfWell("%d", &menuChoices[1]);
                    if(menuChoices[1] < 1 || menuChoices[1] > 2)
                        printf("Please input either 1 or 2: ");
                } while(menuChoices[1] < 1 || menuChoices[1] > 2);

                if(menuChoices[1] == 1) {
                    int numUpdCols = 0;
                    do {
                        numUpdCols++;
                        printf("Please input the name of a column you would like to update the value of: ");
                        if(numUpdCols == 1) {
                            nameList = malloc(sizeof(char*) * 1);
                            valueList = malloc(sizeof(void*) * 1);
                        }
                        else {
                            nameList = realloc(nameList, sizeof(char*) * numUpdCols);
                            valueList = realloc(valueList, sizeof(void*) * numUpdCols);
                        }

                        nameList[numUpdCols - 1] = malloc(sizeof(char) * MAX_LEN);
                        fgetsUntil(nameList[numUpdCols - 1], MAX_LEN);
                        nameList[numUpdCols - 1] = realloc(nameList[numUpdCols - 1], sizeof(char) * (strlen(nameList[numUpdCols - 1]) + 1));

                        printf("Please input the value you wish to replace your desired cells in the column '%s': ", nameList[numUpdCols - 1]);
                        int colType = nameToCol(currentTable, nameList[numUpdCols - 1], NULL).type;
                        if(colType == INTEGER) {
                            valueList[numUpdCols - 1] = malloc(sizeof(int));
                            scanfWell("%d", valueList[numUpdCols - 1]);
                        }
                        else if(colType == CHAR) {
                            valueList[numUpdCols - 1] = malloc(sizeof(char) * MAX_LEN);
                            fgetsUntil(valueList[numUpdCols - 1], MAX_LEN);
                            valueList[numUpdCols - 1] = realloc(valueList[numUpdCols - 1], sizeof(char) * (strlen(valueList[numUpdCols - 1]) + 1));
                        }
                        else if(colType == DECIMAL) {
                            valueList[numUpdCols - 1] = malloc(sizeof(double));
                            scanfWell("%lf", valueList[numUpdCols - 1]);
                        }

                        printf("Would you like to add another column to have its values updated? (yes/no): ");
                        do {
                            fgetsUntil(yesno, MAX_LEN);
                            if(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0)
                                printf("Please input 'yes' or 'no': ");
                        } while(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0);
                    } while(strcmp(yesno, "yes") == 0);

                    numWheres = whereInput(currentTable, &whereList, &connectiveList);

                    update(currentTable, numUpdCols, nameList, valueList, numWheres, whereList, connectiveList);
                }
                else {
                    char* input = malloc(sizeof(char) * MAX_LEN);
                    int* colNums;
                    char* temp;
                    char* colString = malloc(sizeof(char) * MAX_LEN);
                    char* token;
                    int numColsChosen = 0;
                    int colPosI, colPosF;
                    printf("Please input the column letter(s) you would like to choose\n(Eg. 'A' | 'A-E' | 'A, B, D'): ");
                    do {
                        // fgetsUntil(colString, MAX_LEN);
                        colPosI = 0;
                        colPosF = 1;
                        fgetsUntil(input, MAX_LEN);
                        token = strtok(input, ", \n");
                        while(token != NULL) {
                            temp = strstr(token, "-");
                            if(temp != NULL) {

                                strncpy(colString, token, temp - token);
                                // printf("%s %s\n", colString, ++temp);
                                colString[++temp - token] = '\0';
                                colPosI = letterToInt(colString);
                                colPosF = letterToInt(temp);
                                if(colPosI < 0 || colPosF > currentTable->numCols || colPosF <= colPosI) {
                                    printf("Invalid input. Please try again: ");
                                    break;
                                }
                                if(numColsChosen == 0)
                                    colNums = malloc(sizeof(int) * (colPosF - colPosI));
                                else
                                    colNums = realloc(colNums, sizeof(int) * (numColsChosen + colPosF - colPosI));
                                // printf("%d\n", colPosF - colPosI);
                                for(int i = colPosI - 1; i < colPosF; i++)
                                    colNums[numColsChosen++] = i;

                            }
                            else {
                                if(numColsChosen == 0)
                                    colNums = malloc(sizeof(int));
                                else
                                    colNums = realloc(colNums, sizeof(int) * (numColsChosen + 1));

                                colNums[numColsChosen++] = letterToInt(token) - 1;
                            }
                            token = strtok(NULL, ", \n");
                            // for(int i = 0; i < numColsChosen; i++)
                            //     printf("%d, ", colNums[i]);
                            // printf("\n");
                        }

                    } while(colPosI < 0 || colPosF > currentTable->numCols || colPosF <= colPosI);

                    int* rowNums;
                    char* rowString = malloc(sizeof(char) * MAX_LEN);
                    int numRowsChosen = 0;
                    int rowNumI, rowNumF;
                    printf("Please input the row number(s) you would like to choose\n(Eg. '1' | '2-5' | '1, 3, 6'): ");
                    do {
                        rowNumI = 0;
                        rowNumF = 1;
                        fgetsUntil(input, MAX_LEN);
                        token = strtok(input, ", \n");
                        while(token != NULL) {
                            temp = strstr(token, "-");
                            if(temp != NULL) {

                                strncpy(rowString, token, temp - token);
                                // printf("%s %s\n", rowString, ++temp);
                                rowString[++temp - token] = '\0';
                                rowNumI = atoi(rowString);
                                rowNumF = atoi(temp);
                                if(rowNumI < 0 || rowNumF > currentTable->numRows || rowNumF <= rowNumI) {
                                    printf("Invalid input. Please try again: ");
                                    break;
                                }
                                if(numRowsChosen == 0)
                                    rowNums = malloc(sizeof(int) * (rowNumF - rowNumI));
                                else
                                    rowNums = realloc(rowNums, sizeof(int) * (numRowsChosen + rowNumF - rowNumI));
                                // printf("%d\n", rowNumF - rowNumI);
                                for(int i = rowNumI - 1; i < rowNumF; i++)
                                    rowNums[numRowsChosen++] = i;

                            }
                            else {
                                if(numRowsChosen == 0)
                                    rowNums = malloc(sizeof(int));
                                else
                                    rowNums = realloc(rowNums, sizeof(int) * (numRowsChosen + 1));

                                rowNums[numRowsChosen++] = atoi(token) - 1;
                            }
                            token = strtok(NULL, ", \n");
                            // for(int i = 0; i < numRowsChosen; i++)
                            //     printf("%d, ", rowNums[i]);
                            // printf("\n");
                        }

                    } while(rowNumI < 0 || rowNumF > currentTable->numRows || rowNumF <= rowNumI);

                    int* intVal = NULL;
                    double* decVal = NULL;
                    char* charVal = NULL;
                    for(int i = 0; i < numColsChosen; i++) {
                        if(currentTable->cols[colNums[i]].type == INTEGER) {
                            if(intVal == NULL) {
                                intVal = malloc(sizeof(int));
                                printf("Please input your new value for columns of type INTEGER: ");
                                scanfWell("%d", intVal);
                            }
                            for(int j = 0; j < numRowsChosen; j++) {
                                currentTable->cols[colNums[i]].values[rowNums[j]].isNULL = 0;
                                currentTable->cols[colNums[i]].values[rowNums[j]].val.INTEGER = *intVal;
                            }
                        }
                        else if(currentTable->cols[colNums[i]].type == CHAR) {
                            if(charVal == NULL) {
                                charVal = malloc(sizeof(char) * MAX_LEN);
                                printf("Please input your new value for columns of type CHAR: ");
                                fgetsUntil(charVal, MAX_LEN);
                            }
                            for(int j = 0; j < numRowsChosen; j++) {
                                free(currentTable->cols[colNums[i]].values[rowNums[j]].val.CHAR);
                                currentTable->cols[colNums[i]].values[rowNums[j]].isNULL = 0;
                                currentTable->cols[colNums[i]].values[rowNums[j]].val.CHAR = strdup(charVal);
                            }
                        }
                        else if(currentTable->cols[colNums[i]].type == DECIMAL) {
                            if(decVal == NULL) {
                                decVal = malloc(sizeof(double));
                                printf("Please input your new value for columns of type DECIMAL: ");
                                scanfWell("%lf", decVal);
                            }
                            for(int j = 0; j < numRowsChosen; j++) {
                                currentTable->cols[colNums[i]].values[rowNums[j]].isNULL = 0;
                                currentTable->cols[colNums[i]].values[rowNums[j]].val.DECIMAL = *decVal;
                            }
                        }
                    }

                }

                break;
            case 8:
                //"8. MOVE"
                if(numTables <= 0) {
                    printf("There are no tables to choose from.\n");
                    break;
                }
                if(currentTable == NULL) {
                    if(menuChoices[1] == 1)
                        printf("Which table would you like to move rows in?\n");
                    else
                        printf("Which table would you like to move columns in?\n");
                    currTableIndex = tableMenu(numTables, tables);
                    currentTable = &tables[currTableIndex];
                    printf("Here is your current table:\n");
                    printTable(*currentTable);
                }

                switch(menuChoices[1]) {
                    case 1:
                        // "1. MOVE a row to new position in current table"

                        printf("Please input the number of the row you would like to move (1-%d): ", currentTable->numRows);
                        do {
                            scanfWell("%d", &rowNum);
                            if(--rowNum < 0 || rowNum > currentTable->numRows - 1)
                                printf("Please input a number between 1 and %d: ", currentTable->numRows);
                        } while(rowNum < 0 || rowNum > currentTable->numRows - 1);

                        if(currentTable->numRows > 1) {

                            int newPos;

                            printf("Which position would you like to insert this row into? (1-%d): ", currentTable->numRows);
                            do {
                                scanfWell("%d", &newPos);
                                if(--newPos < 0 || newPos > currentTable->numRows - 1)
                                    printf("Please input a number between 1 and %d: ", currentTable->numRows);
                            } while(newPos < 0 || newPos > currentTable->numRows - 1);

                            int nullDummy;
                            int intDummy;
                            double doubleDummy;
                            char charDummy[MAX_LEN];

                            for(int i = 0; i < currentTable->numCols; i++) {
                                nullDummy = currentTable->cols[i].values[rowNum].isNULL;

                                if(currentTable->cols[i].type == INTEGER) {
                                    intDummy = currentTable->cols[i].values[rowNum].val.INTEGER;

                                    if(newPos > rowNum) {
                                        for(int j = rowNum; j < newPos; j++) {
                                            currentTable->cols[i].values[j].val.INTEGER = currentTable->cols[i].values[j + 1].val.INTEGER;
                                            currentTable->cols[i].values[j].isNULL = currentTable->cols[i].values[j + 1].isNULL;
                                        }
                                    }
                                    else {
                                        for(int j = rowNum; j > newPos; j--) {
                                            currentTable->cols[i].values[j].val.INTEGER = currentTable->cols[i].values[j - 1].val.INTEGER;
                                            currentTable->cols[i].values[j].isNULL = currentTable->cols[i].values[j - 1].isNULL;
                                        }
                                    }

                                    currentTable->cols[i].values[newPos].val.INTEGER = intDummy;
                                }
                                else if(currentTable->cols[i].type == DECIMAL) {
                                    doubleDummy = currentTable->cols[i].values[rowNum].val.DECIMAL;

                                    if(newPos > rowNum) {
                                        for(int j = rowNum; j < newPos; j++) {
                                            currentTable->cols[i].values[j].val.DECIMAL = currentTable->cols[i].values[j + 1].val.DECIMAL;
                                            currentTable->cols[i].values[j].isNULL = currentTable->cols[i].values[j + 1].isNULL;
                                        }
                                    }
                                    else {
                                        for(int j = rowNum; j > newPos; j--) {
                                            currentTable->cols[i].values[j].val.DECIMAL = currentTable->cols[i].values[j - 1].val.DECIMAL;
                                            currentTable->cols[i].values[j].isNULL = currentTable->cols[i].values[j - 1].isNULL;
                                        }
                                    }

                                    currentTable->cols[i].values[newPos].val.DECIMAL = doubleDummy;
                                }
                                else if(currentTable->cols[i].type == CHAR) {
                                    strcpy(charDummy, currentTable->cols[i].values[rowNum].val.CHAR);

                                    if(newPos > rowNum) {
                                        for(int j = rowNum; j < newPos; j++) {
                                            printf("%s into %s\n", currentTable->cols[i].values[j + 1].val.CHAR, currentTable->cols[i].values[j].val.CHAR);
                                            // strcpy(currentTable->cols[i].values[j].CHAR, currentTable->cols[i].values[j + 1].CHAR);
                                            // if(currentTable->cols[i].values[j].type != vNULL)
                                            //     free(currentTable->cols[i].values[j].CHAR);
                                            currentTable->cols[i].values[j].val.CHAR = strdup(currentTable->cols[i].values[j + 1].val.CHAR);
                                            currentTable->cols[i].values[j].isNULL = currentTable->cols[i].values[j + 1].isNULL;
                                        }
                                    }
                                    else {
                                        for(int j = rowNum; j > newPos; j--) {
                                            printf("%s into %s\n", currentTable->cols[i].values[j - 1].val.CHAR, currentTable->cols[i].values[j].val.CHAR);
                                            // strcpy(currentTable->cols[i].values[j].CHAR, currentTable->cols[i].values[j - 1].CHAR);
                                            // if(currentTable->cols[i].values[j].type != vNULL)
                                            //     free(currentTable->cols[i].values[j].CHAR);
                                            currentTable->cols[i].values[j].val.CHAR = strdup(currentTable->cols[i].values[j - 1].val.CHAR);
                                            currentTable->cols[i].values[j].isNULL = currentTable->cols[i].values[j - 1].isNULL;
                                        }
                                    }
                                    printf("%s into %s\n", charDummy, currentTable->cols[i].values[newPos].val.CHAR);
                                    // strcpy(currentTable->cols[i].values[newPos].CHAR, charDummy);
                                    // if(currentTable->cols[i].values[newPos].type != vNULL)
                                    //     free(currentTable->cols[i].values[newPos].CHAR);
                                    currentTable->cols[i].values[newPos].val.CHAR = strdup(charDummy);

                                }

                                currentTable->cols[i].values[newPos].isNULL = nullDummy;

                            }
                        }
                        else
                            printf("There's not more than one row in this table. No movement necessary.\n");

                        break;
                    case 2:
                        // "2. MOVE a column to new position in current table"
                        if(currentTable->numCols > 1) {
                            char* colString = malloc(sizeof(char) * MAX_LEN);
                            int colPos;
                            printf("Please input the position of the column you would like to move (A-%s): ", intToLetter(currentTable->numCols - 1));
                            do {
                                fgetsUntil(colString, MAX_LEN);
                                colPos = letterToInt(colString) - 1;
                                if(colPos < 0 || colPos >= currentTable->numCols)
                                    printf("Please input a valid column position. (A-%s): ", intToLetter(currentTable->numCols - 1));
                            } while(colPos < 0 || colPos >= currentTable->numCols);

                            int newPos;

                            printf("Which position would you like to insert this column into? (A-%s): ", intToLetter(currentTable->numCols - 1));
                            do {
                                fgetsUntil(colString, MAX_LEN);
                                newPos = letterToInt(colString) - 1;
                                if(newPos < 0 || newPos >= currentTable->numCols)
                                    printf("Please input a valid column position. (A-%s): ", intToLetter(currentTable->numCols - 1));
                            } while(newPos < 0 || newPos >= currentTable->numCols);

                            Column dummyCol = copyColumn(currentTable->numRows, currentTable->cols[colPos]);

                            if(newPos > colPos)
                                for(int i = colPos; i < newPos; i++)
                                    currentTable->cols[i] = currentTable->cols[i + 1];
                            else
                                for(int i = colPos; i > newPos; i--)
                                    currentTable->cols[i] = currentTable->cols[i - 1];
                            currentTable->cols[newPos] = dummyCol;

                        }
                        else
                            printf("There's not more than one column in this table. No movement necessary.\n");

                        break;

                }
                break;
            case 9:
                //"9. COPY"
                if(numTables <= 0) {
                    printf("There are no tables to choose from.\n");
                    break;
                }
                if(currentTable == NULL) {
                    if(menuChoices[1] == 1)
                        printf("Which table would you like to copy a row from?\n");
                    else if(menuChoices[1] == 2)
                        printf("Which table would you like to copy a column from?\n");
                    else if(menuChoices[1] == 3)
                        printf("Which table would you like to copy?\n");
                    currTableIndex = tableMenu(numTables, tables);
                    currentTable = &tables[currTableIndex];
                    printf("Here is your current table:\n");
                    printTable(*currentTable);
                }

                switch(menuChoices[1]) {
                    case 1:
                        // "1. COPY row in current table"
                        printf("Which row would you like to copy? (1-%d): ", currentTable->numRows);
                        do {
                            scanfWell("%d", &rowNum);
                            if(--rowNum < 0 || rowNum > currentTable->numRows - 1)
                                printf("Please input a number between 1 and %d: ", currentTable->numRows);
                        } while(rowNum < 0 || rowNum > currentTable->numRows - 1);


                        rowCopy = copyRow(currentTable, rowNum);
                        rowCopyLength = currentTable->numCols;
                        printf("Row #%d copied:\n", rowNum + 1);

                        printLoneRow(rowCopy, rowCopyLength);

                        break;
                    case 2: {
                        // "2. COPY column in current table"
                        char* colString = malloc(sizeof(char) * MAX_LEN);
                        int colPos;
                        printf("Please input the position of the column you would like to copy. (A-%s): ", intToLetter(currentTable->numCols - 1));
                        do {
                            fgetsUntil(colString, MAX_LEN);
                            colPos = letterToInt(colString) - 1;
                            if(colPos < 0 || colPos >= currentTable->numCols)
                                printf("Please input a valid column position. (A-%s): ", intToLetter(currentTable->numCols - 1));
                        } while(colPos < 0 || colPos >= currentTable->numCols);

                        colCopy = copyColumn(currentTable->numRows, currentTable->cols[colPos]);
                        colCopyLength = currentTable->numRows;

                        printf("Column %s copied:\n", colString);

                        printColumn(colCopy, colCopyLength);

                        free(colString);

                        break;
                    }
                    case 3:
                        // "3. Make a COPY of current table"
                        numTables++;
                        tables = realloc(tables, sizeof(Table) * numTables);
                        currentTable = &tables[currTableIndex];
                        tables[numTables - 1] = copyTable(*currentTable);

                        printf("Table '%s' copied.\n", currentTable->name);

                        currentTable = &tables[numTables - 1];
                        currTableIndex = numTables - 1;

                        checkTableNames(tables, numTables, currentTable->name, currTableIndex);
                        break;
                }

                break;
            case 10:
                //"10. PASTE"

                switch(menuChoices[1]) {
                    case 1:
                        // "1. PASTE row in current table"
                        break;
                    case 2:
                        // "2. PASTE column in current table"
                        break;
                }


                break;
            case 11:
                //"11. DELETE"
                // "1. DELETE row(s) from current table"
                // "2. DELETE column(s) from current table"
                // "3. DELETE value(s) from current table"
                // "4. DELETE current table"
                break;
            case 12:
                //"12. IMPORT"
                // "1. IMPORT database from .sql File"
                // "2. IMPORT database from .db File"
                break;
            case 13:
                //"13. EXPORT"
                // "1. EXPORT database to .SQL File"
                // "2. EXPORT database to .db File"
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
            "8. MOVE\n"
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
                printf("1. PRINT the Master Table\n"
                    "2. PRINT a table\n");
                numOptions = 2;
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
                printf("1. MOVE a row to new position in current table\n"
                    "2. MOVE a column to new position in current table\n");
                numOptions = 2;
                break;

            case 9:
                printf("1. COPY row in current table\n"
                    "2. COPY column in current table\n"
                    "3. Make a COPY of current table\n");
                numOptions = 3;
                break;

            case 10:
                printf("1. PASTE row into current table\n"
                    "2. PASTE column into current table\n");
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
                printf("1. IMPORT database from .sql File\n"
                    "2. IMPORT database from .db File\n");
                numOptions = 2;
                break;

            case 13:
                printf("1. EXPORT database to .SQL File\n"
                    "2. EXPORT database to .db File\n");
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
            if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName, NULL).type == -1)
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

        if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName, NULL).type == INTEGER) {
            printf("Please input the integer value you are looking for: ");
            (*whereList)[numWheres - 1].searchValue = malloc(sizeof(int));
            scanfWell("%d", (*whereList)[numWheres - 1].searchValue);
        }
        else if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName, NULL).type == CHAR) {
            printf("Please input the string value you are looking for: ");
            (*whereList)[numWheres - 1].searchValue = malloc(sizeof(char) * MAX_LEN);
            fgetsUntil((*whereList)[numWheres - 1].searchValue, MAX_LEN);
            (*whereList)[numWheres - 1].searchValue = realloc((*whereList)[numWheres - 1].searchValue, sizeof(char) * (strlen((*whereList)[numWheres - 1].searchValue) + 1));
            // printf("%s\n", (*whereList)[numWheres - 1].searchValue);
        }
        else if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName, NULL).type == DECIMAL) {
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

void checkTableNames(Table* tables, int numTables, char* nameToCheck, int newNameIndex) {
    int numDupes = 0;
    char* nameSuffix;

    for(int i = 0; i < numTables; i++) {
        if(strcmp(nameToCheck, tables[i].name) == 0 && i != newNameIndex) {
            printf("DUPE FOUND\n");
            // numDupes++;
            nameSuffix = strstr(nameToCheck, "(");
            if(nameSuffix != NULL && strlen(nameSuffix) >= 3) {
                nameSuffix[strlen(nameSuffix) - 1] = '\0';
                sscanf(nameSuffix + 1, "%d", &numDupes);
                numDupes++;
                sprintf(nameSuffix, "(%d)", numDupes);
            }
            else {
                strcat(nameToCheck, " (1)");
            }
            i = 0;
        }
    }
}

void checkColumnNames(Table table, char* nameToCheck, int newNameIndex) {
    int numDupes = 0;
    char* nameSuffix;

    for(int i = 0; i < table.numCols; i++) {
        if(strcmp(nameToCheck, table.cols[i].name) == 0 && i != newNameIndex) {
            printf("DUPE FOUND\n");
            // numDupes++;
            nameSuffix = strstr(nameToCheck, "(");
            if(nameSuffix != NULL && strlen(nameSuffix) >= 3) {
                nameSuffix[strlen(nameSuffix) - 1] = '\0';
                sscanf(nameSuffix + 1, "%d", &numDupes);
                numDupes++;
                sprintf(nameSuffix, "(%d)", numDupes);
            }
            else {
                strcat(nameToCheck, " (1)");
            }
            i = 0;
        }
    }
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
