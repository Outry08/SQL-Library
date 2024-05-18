#include "sqllib.h"

int main(int argc, char const* argv[]) {

    Table* tables = malloc(sizeof(Table) * 2);

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

    printTable(tables[0]);

    printf("\n\n\n");
    where3.searchValue = "Mario";
    where3.comparison = "==";

    Select select1 = newSelect(2, nameList(2, "Decimal Col", "Char Col"), 0);

    tables[1] = cql_select(tables[0], select1, 2, whereList(2, where5, where3), connectiveList(1, '|'));

    Select select2 = newSelect(1, nameList(1, "Char Col"), 0);
    Where where9 = newWhere("Char Col", "=", "WAHHLUIGI");

    tables[1] = cql_select(tables[0], select2, 2, whereList(2, where3, where9), connectiveList(1, '|'));

    insertIntoRow(tables, 3, nameList(3, "Char Col", "Integer Col", "Decimal Col"), valueList(3, typeList(3, CHAR, INTEGER, DECIMAL), "Princess Peach", 777, 19.64), 3);

    insertCol(&tables[0], "Bool Col", BOOL, 4, typeList(4, 0, 1, 2, 3), valueList(4, typeList(4, BOOL, BOOL, BOOL, BOOL), 1, 0, 0, 1));

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

    printf("%s\n", table.name);
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
        if(table->numRows == 1)
            table->cols[i].values = malloc(sizeof(Value) * table->numRows);
        else
            table->cols[i].values = realloc(table->cols[i].values, sizeof(Value) * table->numRows);
        table->cols[i].values[table->numRows - 1].isNULL = 1;
    }

    for(int i = 0; i < numValues; i++) {
        colName = strdup(colNames[i]);
        currCol = nameToCol(table, colName, NULL);

        if(values[i] == NULL) {
            currCol.values[table->numRows - 1].isNULL = 1;
        }
        else {
            if(currCol.type == CHAR) {
                currCol.values[table->numRows - 1].isNULL = 0;
                currCol.values[table->numRows - 1].val.CHAR = strdup((char*)values[i]);
            }
            else if(currCol.type == INTEGER) {
                currCol.values[table->numRows - 1].isNULL = 0;
                currCol.values[table->numRows - 1].val.INTEGER = *(int*)values[i];
            }
            else if(currCol.type == DECIMAL) {
                currCol.values[table->numRows - 1].isNULL = 0;
                currCol.values[table->numRows - 1].val.DECIMAL = *(double*)values[i];
            }
            else if(currCol.type == BOOL) {
                printf("HI\n");
                currCol.values[table->numRows - 1].isNULL = 0;
                currCol.values[table->numRows - 1].val.BOOL = *(int*)values[i];
                printf("BYE\n");
            }
            else if(currCol.type == DATE) {
                printf("DATE datatype support coming soon.\n");
            }
            else {
                printf("Error: Nonexistent column name, \"%s\", provided.\n", colName);
            }
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
        for(int j = table->numRows - 2; j >= rowNum; j--) {
            table->cols[i].values[j + 1].isNULL = table->cols[i].values[j].isNULL;

            if(!table->cols[i].values[j + 1].isNULL) {
                if(table->cols[i].type == INTEGER)
                    table->cols[i].values[j + 1].val.INTEGER = table->cols[i].values[j].val.INTEGER;
                else if(table->cols[i].type == DECIMAL)
                    table->cols[i].values[j + 1].val.DECIMAL = table->cols[i].values[j].val.DECIMAL;
                else if(table->cols[i].type == CHAR)
                    table->cols[i].values[j + 1].val.CHAR = strdup(table->cols[i].values[j].val.CHAR);
                else if(table->cols[i].type == BOOL)
                    table->cols[i].values[j + 1].val.BOOL = table->cols[i].values[j].val.BOOL;
                else if(table->cols[i].type == DATE)
                    printf("DATE datatype functionality coming soon.\n");
            }
        }
        table->cols[i].values[rowNum].isNULL = 1;
    }

    for(int i = 0; i < numValues; i++) {
        colName = strdup(colNames[i]);
        currCol = nameToCol(table, colName, NULL);
        if(values[i] == NULL) {
            currCol.values[table->numRows - 1].isNULL = 1;
        }
        else {
            currCol.values[rowNum].isNULL = 0;
            if(currCol.type == CHAR)
                currCol.values[rowNum].val.CHAR = strdup((char*)values[i]);
            else if(currCol.type == INTEGER)
                currCol.values[rowNum].val.INTEGER = *(int*)values[i];
            else if(currCol.type == DECIMAL)
                currCol.values[rowNum].val.DECIMAL = *(double*)values[i];
            else if(currCol.type == BOOL)
                currCol.values[rowNum].val.BOOL = *(int*)values[i];
            else if(currCol.type == DATE)
                printf("DATE datatype functionality coming soon.\n");
            else
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
        if(values[i] == NULL) {
            table->cols[table->numCols - 1].values[rowNums[i]].isNULL = 1;
        }
        else {
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
            else if(colType == BOOL) {
                table->cols[table->numCols - 1].values[rowNums[i]].isNULL = 0;
                table->cols[table->numCols - 1].values[rowNums[i]].val.BOOL = *(int*)values[i];
            }
            else if(colType == DATE) {
                printf("DATE datatype functionality to be implemented soon.\n");
            }
            else {
                printf("Error: Nonexistent row number, \"%d\", provided.\n", rowNums[i]);
            }
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
        if(values[i] == NULL) {
            table->cols[table->numCols - 1].values[rowNums[i]].isNULL = 1;
        }
        else {
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
            else if(colType == BOOL) {
                table->cols[colNum].values[rowNums[i]].isNULL = 0;
                table->cols[colNum].values[rowNums[i]].val.BOOL = *(int*)values[i];
            }
            else if(colType == DATE) {
                printf("DATE datatype functionality to be implemented soon.\n");
            }
            else {
                printf("Error: Nonexistent row number, \"%d\", provided.\n", rowNums[i]);
            }
        }

    }

    checkColumnNames(*table, table->cols[colNum].name, colNum);

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
                    if(toUpdate[j] == 1 && !compare(nameToCol(table, wheres[i].searchColName, NULL), j, wheres[i].comparison, wheres[i].searchValue))
                        toUpdate[j] = 0;
                    break;
                case '|':
                case 'o':
                case 'O':
                    toUpdate[j] = 1;
                case '~':
                    if(!compare(nameToCol(table, wheres[i].searchColName, NULL), j, wheres[i].comparison, wheres[i].searchValue))
                        toUpdate[j] = 0;
                    break;
                default:
                    printf("Error: Invalid where connective '%c' provided into update function.", conns[i]);
                    break;
            }

            if(toUpdate[j] == 1) {
                prevGoodJs = realloc(prevGoodJs, sizeof(int) * (++numPrevGoodJs));
                prevGoodJs[numPrevGoodJs - 1] = j;
            }

        }
        if((i == numWheres - 1 || conns[i + 1] == '|' || conns[i + 1] == 'o' || conns[i + 1] == 'O') && (numPrevGoodJs > 0 && numPrevGoodJs <= table->numRows)) {

            for(int l = 0; l < numPrevGoodJs; l++) {
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
                    else if(currCol.type == BOOL) {
                        currCol.values[prevGoodJs[l]].isNULL = 0;
                        currCol.values[prevGoodJs[l]].val.BOOL = *((int*)newValues[k]);
                    }
                    else if(currCol.type == DATE) {
                        printf("DATE datatype functionality coming soon.\n");
                    }
                }
            }
        }
        free(prevGoodJs);
    }

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
        if((i == numWheres - 1 || conns[i + 1] == '|' || conns[i + 1] == 'o' || conns[i + 1] == 'O') && (numPrevGoodJs > 0 && numPrevGoodJs <= table->numRows)) {
            for(int k = 0; k < numPrevGoodJs; k++) {
                for(int l = 0; l < table->numCols; l++) {
                    for(int m = prevGoodJs[k]; m < table->numRows - 1; m++) {
                        table->cols[l].values[m].isNULL = table->cols[l].values[m + 1].isNULL;

                        if(!table->cols[l].values[m].isNULL) {
                            if(table->cols[l].type == INTEGER)
                                table->cols[l].values[m].val.INTEGER = table->cols[l].values[m + 1].val.INTEGER;
                            else if(table->cols[l].type == DECIMAL)
                                table->cols[l].values[m].val.DECIMAL = table->cols[l].values[m + 1].val.DECIMAL;
                            else if(table->cols[l].type == CHAR)
                                table->cols[l].values[m].val.CHAR = strdup(table->cols[l].values[m + 1].val.CHAR);
                            else if(table->cols[l].type == BOOL)
                                table->cols[l].values[m].val.BOOL = table->cols[l].values[m + 1].val.BOOL;
                            else if(table->cols[l].type == DATE)
                                printf("DATE datatype functionality coming soon.\n");
                        }
                    }
                }
                table->numRows--;
                for(int l = k + 1; l < numPrevGoodJs; l++)
                    if(prevGoodJs[l] > prevGoodJs[k])
                        prevGoodJs[l]--;


            }
        }
        free(prevGoodJs);
    }

    if(numWheres <= 0)
        table->numRows = 0;
}

void freeTable(Table* table) {
    for(int i = 0; i < table->numCols; i++) {
        if(table->cols[i].type == CHAR)
            for(int j = 0; j < table->numRows; j++)
                if(table->cols[i].values[j].val.CHAR != NULL)
                    free(table->cols[i].values[j].val.CHAR);
        free(table->cols[i].values);
        free(table->cols[i].name);
    }

    free(table->cols);
    free(table->name);
}

void deleteColumn(Table* table, char* colName) {
    int colIndex;

    Column col = nameToCol(table, colName, &colIndex);

    if(colIndex > -1) {
        if(col.type == CHAR)
            for(int i = 0; i < table->numRows; i++)
                if(!col.values[i].isNULL)
                    free(col.values[i].val.CHAR);
        free(col.values);
        free(col.name);
        table->numCols--;
        for(int i = colIndex; i < table->numCols; i++)
            table->cols[i] = copyColumn(table->numRows, table->cols[i + 1]);

        table->cols = realloc(table->cols, sizeof(Column) * table->numCols);
    }
    else {
        printf("Error: The provided column '%s' does not exist. Deletion failed.\n", colName);
        return;
    }
}

void deleteRow(Table* table, int rowNum) {
    if(table->numRows <= 0) {
        printf("There are no rows to delete.\n");
        return;
    }
    for(int i = 0; i < table->numCols; i++) {
        for(int j = rowNum; j < table->numRows - 1; j++) {
            table->cols[i].values[j].isNULL = table->cols[i].values[j + 1].isNULL;

            if(!table->cols[i].values[j].isNULL) {
                if(table->cols[i].type == INTEGER)
                    table->cols[i].values[j].val.INTEGER = table->cols[i].values[j + 1].val.INTEGER;
                else if(table->cols[i].type == DECIMAL)
                    table->cols[i].values[j].val.DECIMAL = table->cols[i].values[j + 1].val.DECIMAL;
                else if(table->cols[i].type == CHAR)
                    table->cols[i].values[j].val.CHAR = strdup(table->cols[i].values[j + 1].val.CHAR);
                else if(table->cols[i].type == BOOL)
                    table->cols[i].values[j].val.BOOL = table->cols[i].values[j + 1].val.BOOL;
                else if(table->cols[i].type == DATE)
                    printf("DATE datatype functionality coming soon.\n");
            }
        }
    }

    table->numRows--;

    for(int i = 0; i < table->numCols; i++) {
        if(table->cols[i].type == CHAR)
            if(!table->cols[i].values[table->numRows].isNULL)
                free(table->cols[i].values[table->numRows].val.CHAR);

        table->cols[i].values = realloc(table->cols[i].values, sizeof(Value) * table->numRows);
    }
}

Table cql_select(Table table, Select sel, int numWheres, Where* wheres, char* conns) {

    Table tableCopy = copyTable(table);

    free(tableCopy.name);
    tableCopy.name = strdup(table.name);

    if(numWheres > 0)
        delete(&tableCopy, numWheres, notWheres(numWheres, wheres), notConnectives(numWheres - 1, conns));

    if(sel.distinct)
        deleteDuplicateValues(&tableCopy, sel.numCols, sel.colNames);

    Table selectedTable;

    // if(sel.numCols == table.numCols) {
    //     for(int i = 0; i < sel.numCols; i++)
    //         if(sel.colNames[i] != NULL)
    //             free(sel.colNames[i]);

    //     sel.numCols = tableCopy.numCols;

    //     for(int i = 0; i < tableCopy.numCols; i++) {
    //         sel.colNames[i] = strdup(tableCopy.cols[i].name);
    //     }
    // }
    selectedTable = selCreate(tableCopy, sel.numCols, sel.colNames);

    return selectedTable;
}

/**
 * A create() variant designed for internal use of the select function.
*/
Table selCreate(Table baseTable, int numCols, char** colNames) {

    Table newTable;

    newTable.name = malloc(sizeof(char) * MAX_LEN);

    strcpy(newTable.name, "Selected from ");

    strcat(newTable.name, baseTable.name);
    newTable.name = realloc(newTable.name, sizeof(char) * (strlen(newTable.name) + 1));
    newTable.cols = malloc(sizeof(Column) * numCols);

    newTable.numCols = numCols;
    newTable.numRows = baseTable.numRows;

    int allAggs = 1;

    // char* newName;

    for(int i = 0; i < numCols; i++) {
        if(!isAggregate(colNames[i])) {
            newTable.cols[i] = copyColumn(baseTable.numRows, nameToCol(&baseTable, colNames[i], NULL));
            allAggs = 0;
        }
        else {
            char* colName = getColNameFromAggregate(colNames[i]);

            newTable.cols[i].values = malloc(sizeof(Value) * newTable.numRows);
            newTable.cols[i].name = strdup(colNames[i]);
            newTable.cols[i].type = nameToCol(&baseTable, colName, NULL).type;

            char* aggregateName = getAggregateName(colNames[i]);

            if(strcmp(aggregateName, "COUNT") == 0) {
                newTable.cols[i].type = INTEGER;
                newTable.cols[i].values[0].val.INTEGER = newTable.numRows;
                newTable.cols[i].values[0].isNULL = 0;
            }
            else if(strcmp(aggregateName, "AVG") == 0) {
                double avg = 0;
                if(newTable.cols[i].type == DECIMAL) {
                    int count = 0;
                    double sum = 0;

                    for(int j = 0; j < newTable.numRows; j++) {
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL) {
                            sum += nameToCol(&baseTable, colName, NULL).values[j].val.DECIMAL;
                            count++;
                        }
                    }
                    if(count > 0) {
                        avg = sum / count;
                        newTable.cols[i].values[0].val.DECIMAL = avg;
                        newTable.cols[i].values[0].isNULL = 0;
                    }
                    else {
                        newTable.cols[i].values[0].isNULL = 0;
                    }
                }
                else if(newTable.cols[i].type == INTEGER) {
                    printf("INTEGER\n");
                    int count = 0;
                    int sum = 0;
                    for(int j = 0; j < newTable.numRows; j++) {
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL) {
                            sum += nameToCol(&baseTable, colName, NULL).values[j].val.INTEGER;
                            count++;
                        }
                    }
                    avg = (double)sum / count;
                    newTable.cols[i].type = DECIMAL;
                    newTable.cols[i].values[0].val.DECIMAL = avg;
                    newTable.cols[i].values[0].isNULL = 0;
                }
                else {
                    newTable.cols[i].values[0].isNULL = 1;
                }

            }
            else if(strcmp(aggregateName, "SUM") == 0) {
                if(newTable.cols[i].type == DECIMAL) {
                    double sum = 0;
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL)
                            sum += nameToCol(&baseTable, colName, NULL).values[j].val.DECIMAL;
                    newTable.cols[i].values[0].val.DECIMAL = sum;
                    newTable.cols[i].values[0].isNULL = 0;
                }
                else if(newTable.cols[i].type == INTEGER) {
                    int sum = 0;
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL)
                            sum += nameToCol(&baseTable, colName, NULL).values[j].val.INTEGER;
                    newTable.cols[i].values[0].val.INTEGER = sum;
                    newTable.cols[i].values[0].isNULL = 0;
                }
                else {
                    newTable.cols[i].values[0].isNULL = 1;
                }
            }
            else if(strcmp(aggregateName, "MAX") == 0) {
                if(newTable.cols[i].type == DECIMAL) {
                    double max = __DBL_MIN__;
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL && nameToCol(&baseTable, colName, NULL).values[j].val.DECIMAL > max)
                            max = nameToCol(&baseTable, colName, NULL).values[j].val.DECIMAL;
                    newTable.cols[i].values[0].val.DECIMAL = max;
                    newTable.cols[i].values[0].isNULL = 0;
                }
                else if(newTable.cols[i].type == INTEGER) {
                    int max = INT_MIN;
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL && nameToCol(&baseTable, colName, NULL).values[j].val.INTEGER > max)
                            max = nameToCol(&baseTable, colName, NULL).values[j].val.INTEGER;
                    newTable.cols[i].values[0].val.INTEGER = max;
                    newTable.cols[i].values[0].isNULL = 0;
                }
                else if(newTable.cols[i].type == CHAR) {
                    char* max = malloc(sizeof(char) * MAX_LEN);
                    strcpy(max, "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ");
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL && strcmp(nameToCol(&baseTable, colName, NULL).values[j].val.CHAR, max) < 0)
                            strcpy(max, nameToCol(&baseTable, colName, NULL).values[j].val.CHAR);
                    newTable.cols[i].values[0].val.CHAR = max;
                    newTable.cols[i].values[0].isNULL = 0;
                }
                else if(newTable.cols[i].type == DATE) {
                    printf("DATE datatype support yet to be implemented.\n");
                    newTable.cols[i].values[0].isNULL = 1;
                }
                else {
                    newTable.cols[i].values[0].isNULL = 1;
                }
            }
            else if(strcmp(aggregateName, "MIN") == 0) {
                if(newTable.cols[i].type == DECIMAL) {
                    double min = __DBL_MAX__;
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL && nameToCol(&baseTable, colName, NULL).values[j].val.DECIMAL < min)
                            min = nameToCol(&baseTable, colName, NULL).values[j].val.DECIMAL;
                    newTable.cols[i].values[0].val.DECIMAL = min;
                    newTable.cols[i].values[0].isNULL = 0;
                }
                else if(newTable.cols[i].type == INTEGER) {
                    int min = INT_MAX;
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL && nameToCol(&baseTable, colName, NULL).values[j].val.INTEGER < min)
                            min = nameToCol(&baseTable, colName, NULL).values[j].val.INTEGER;
                    newTable.cols[i].values[0].val.INTEGER = min;
                    newTable.cols[i].values[0].isNULL = 0;
                }
                else if(newTable.cols[i].type == CHAR) {
                    char* min = malloc(sizeof(char) * MAX_LEN);
                    strcpy(min, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL && strcmp(nameToCol(&baseTable, colName, NULL).values[j].val.CHAR, min) > 0)
                            strcpy(min, nameToCol(&baseTable, colName, NULL).values[j].val.CHAR);
                    newTable.cols[i].values[0].val.CHAR = min;
                    newTable.cols[i].values[0].isNULL = 0;
                }
                else if(newTable.cols[i].type == DATE) {
                    printf("DATE datatype support yet to be implemented.\n");
                    newTable.cols[i].values[0].isNULL = 1;
                }
                else {
                    newTable.cols[i].values[0].isNULL = 1;
                }
            }

            for(int j = 1; j < newTable.numRows; j++)
                newTable.cols[i].values[j].isNULL = 1;
        }
    }

    if(allAggs) {
        for(int i = 0; i < numCols; i++)
            newTable.cols[i].values = realloc(newTable.cols[i].values, sizeof(Value));
        newTable.numRows = 1;
    }

    for(int i = newTable.numCols - 1; i >= 0; i--) {
        checkColumnNames(newTable, newTable.cols[i].name, i);
    }

    newTable.selected = 1;

    return newTable;

}

void deleteDuplicateValues(Table* table, int numCols, char** colNames) {

    for(int i = 0; i < table->numCols; i++) {
        int nameFound = 0;
        for(int j = 0; j < numCols; j++) {
            if(strcmp(table->cols[i].name, getColNameFromAggregate(colNames[j])) == 0) {
                nameFound = 1;
                break;
            }
        }

        if(nameFound) {
            int numUniqueFound = 0;
            int found;
            if(table->cols[i].type == CHAR) {
                printf("CHAR\n");
                char** foundChars = NULL;

                for(int j = 0; j < table->numRows; j++) {
                    if(!table->cols[i].values[j].isNULL) {
                        if(foundChars) {
                            found = 0;
                            for(int k = 0; k < numUniqueFound; k++) {
                                if(strcmp(foundChars[k], table->cols[i].values[j].val.CHAR) == 0) {
                                    found = 1;
                                    break;
                                }
                            }
                            if(!found) {
                                numUniqueFound++;
                                foundChars = realloc(foundChars, sizeof(char*) * numUniqueFound);
                                foundChars[numUniqueFound - 1] = strdup(table->cols[i].values[j].val.CHAR);
                            }
                            else {
                                deleteRow(table, j);
                                j--;
                            }
                        }
                        else {
                            numUniqueFound++;
                            foundChars = malloc(sizeof(char*));
                            foundChars[numUniqueFound - 1] = strdup(table->cols[i].values[j].val.CHAR);
                        }
                    }
                }
            }
            else if(table->cols[i].type == INTEGER) {
                printf("INTEGER\n");

                int* foundInts = NULL;

                for(int j = 0; j < table->numRows; j++) {
                    if(!table->cols[i].values[j].isNULL) {
                        if(foundInts) {
                            found = 0;
                            for(int k = 0; k < numUniqueFound; k++) {
                                if(foundInts[k] == table->cols[i].values[j].val.INTEGER) {
                                    found = 1;
                                    break;
                                }
                            }
                            if(!found) {
                                numUniqueFound++;
                                foundInts = realloc(foundInts, sizeof(int) * numUniqueFound);
                                foundInts[numUniqueFound - 1] = table->cols[i].values[j].val.INTEGER;
                            }
                            else {
                                deleteRow(table, j);
                                j--;
                            }
                        }
                        else {
                            numUniqueFound++;
                            foundInts = malloc(sizeof(int));
                            foundInts[numUniqueFound - 1] = table->cols[i].values[j].val.INTEGER;
                        }
                    }
                }
            }
            else if(table->cols[i].type == DECIMAL) {
                printf("DECIMAL\n");

                double* foundDecs = NULL;

                for(int j = 0; j < table->numRows; j++) {
                    if(!table->cols[i].values[j].isNULL) {
                        if(foundDecs) {
                            found = 0;
                            for(int k = 0; k < numUniqueFound; k++) {
                                if(foundDecs[k] == table->cols[i].values[j].val.DECIMAL) {
                                    found = 1;
                                    break;
                                }
                            }
                            if(!found) {
                                numUniqueFound++;
                                foundDecs = realloc(foundDecs, sizeof(double) * numUniqueFound);
                                foundDecs[numUniqueFound - 1] = table->cols[i].values[j].val.DECIMAL;
                            }
                            else {
                                deleteRow(table, j);
                                j--;
                            }
                        }
                        else {
                            numUniqueFound++;
                            foundDecs = malloc(sizeof(double));
                            foundDecs[numUniqueFound - 1] = table->cols[i].values[j].val.DECIMAL;
                        }
                    }
                }
            }
            else if(table->cols[i].type == BOOL) {
                printf("BOOL\n");

                int* foundBools = NULL;

                for(int j = 0; j < table->numRows; j++) {
                    if(!table->cols[i].values[j].isNULL) {
                        if(foundBools) {
                            found = 0;
                            for(int k = 0; k < numUniqueFound; k++) {
                                if(foundBools[k] == table->cols[i].values[j].val.BOOL) {
                                    found = 1;
                                    break;
                                }
                            }
                            if(!found) {
                                numUniqueFound++;
                                foundBools = realloc(foundBools, sizeof(int) * numUniqueFound);
                                foundBools[numUniqueFound - 1] = table->cols[i].values[j].val.BOOL;
                            }
                            else {
                                deleteRow(table, j);
                                j--;
                            }
                        }
                        else {
                            numUniqueFound++;
                            foundBools = malloc(sizeof(int));
                            foundBools[numUniqueFound - 1] = table->cols[i].values[j].val.BOOL;
                        }
                    }
                }
            }
            else if(table->cols[i].type == DATE) {
                printf("DATE datatypes functionality to be implemented.\n");
            }
        }

    }

}

Table copyTable(Table table) {
    Table newTable;

    newTable.name = malloc(sizeof(char) * MAX_LEN);

    strcpy(newTable.name, "Copy of ");
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

    colCopy.name = strdup(col.name);
    colCopy.type = col.type;
    colCopy.values = malloc(sizeof(Value) * numVals);
    for(int i = 0; i < numVals; i++) {
        colCopy.values[i].isNULL = col.values[i].isNULL;
        if(!colCopy.values[i].isNULL) {
            if(colCopy.type == INTEGER)
                colCopy.values[i].val.INTEGER = col.values[i].val.INTEGER;
            else if(colCopy.type == CHAR)
                colCopy.values[i].val.CHAR = strdup(col.values[i].val.CHAR);
            else if(colCopy.type == DECIMAL)
                colCopy.values[i].val.DECIMAL = col.values[i].val.DECIMAL;
            else if(colCopy.type == BOOL)
                colCopy.values[i].val.BOOL = col.values[i].val.BOOL;
            else if(colCopy.type == DATE)
                printf("DATE datatype functionality coming soon.\n");
        }
    }

    return colCopy;
}

LoneValue* copyRow(Table* table, int rowNum) {

    LoneValue* rowCopy = malloc(sizeof(LoneValue) * table->numCols);
    for(int i = 0; i < table->numCols; i++) {
        rowCopy[i].value.isNULL = table->cols[i].values[rowNum].isNULL;
        rowCopy[i].type = table->cols[i].type;
        rowCopy[i].colName = strdup(table->cols[i].name);
        if(!rowCopy[i].value.isNULL) {
            if(table->cols[i].type == INTEGER)
                rowCopy[i].value.val.INTEGER = table->cols[i].values[rowNum].val.INTEGER;
            else if(table->cols[i].type == CHAR)
                rowCopy[i].value.val.CHAR = strdup(table->cols[i].values[rowNum].val.CHAR);
            else if(table->cols[i].type == DECIMAL)
                rowCopy[i].value.val.DECIMAL = table->cols[i].values[rowNum].val.DECIMAL;
            else if(table->cols[i].type == BOOL)
                rowCopy[i].value.val.BOOL = table->cols[i].values[rowNum].val.BOOL;
            else if(table->cols[i].type == DATE)
                printf("DATE datatype functionality coming soon.\n");
        }
    }

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

    return notConns;
}

Column nameToCol(Table* table, char* colName, int* colIndex) {

    if(colName != NULL) {
        for(int i = 0; i < table->numCols; i++) {
            if(strcmp(table->cols[i].name, colName) == 0) {
                if(colIndex != NULL)
                    *colIndex = i;
                return table->cols[i];
            }
        }
    }

    Column errCol;
    errCol.name = "COL NOT FOUND";
    errCol.type = -1;
    if(colIndex != NULL)
        *colIndex = -1;

    return errCol;
}

int containsCol(Table table, char* colName) {
    for(int i = 0; i < table.numCols; i++)
        if(strcmp(table.cols[i].name, colName) == 0)
            return 1;

    return 0;
}

int compare(Column column, int valIndex, char* comparison, void* value) {

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
            else if(column.type == BOOL)
                return 0;
            else if(column.type == DATE) {
                printf("DATE datatype functionality coming soon.\n");
                return 0;
            }
            else
                return 0;
        }
        else if(column.type == CHAR)
            return strcmp(column.values[valIndex].val.CHAR, (char*)value) == 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].val.INTEGER == *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].val.DECIMAL == *((double*)value);
        else if(column.type == BOOL)
            return column.values[valIndex].val.BOOL == *((int*)value);
        else if(column.type == DATE) {
            printf("DATE datatype functionality coming soon.\n");
            return 0;
        }
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
            else if(column.type == BOOL)
                return 0;
            else if(column.type == DATE) {
                printf("DATE datatype functionality coming soon.\n");
                return 0;
            }
            else
                return 0;
        }
        else if(column.type == CHAR)
            return strcmp(column.values[valIndex].val.CHAR, (char*)value) < 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].val.INTEGER < *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].val.DECIMAL < *((double*)value);
        else if(column.type == BOOL)
            return 1;
        else if(column.type == DATE) {
            printf("DATE datatype functionality coming soon.\n");
            return 0;
        }
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
            else if(column.type == BOOL)
                return 0;
            else if(column.type == DATE) {
                printf("DATE datatype functionality coming soon.\n");
                return 0;
            }
            else
                return 0;
        }
        else if(column.type == CHAR)
            return strcmp(column.values[valIndex].val.CHAR, (char*)value) <= 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].val.INTEGER <= *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].val.DECIMAL <= *((double*)value);
        else if(column.type == BOOL)
            return 1;
        else if(column.type == DATE) {
            printf("DATE datatype functionality coming soon.\n");
            return 0;
        }
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
            else if(column.type == BOOL)
                return 0;
            else if(column.type == DATE) {
                printf("DATE datatype functionality coming soon.\n");
                return 0;
            }
            else
                return 0;
        }
        else if(column.type == CHAR)
            return strcmp(column.values[valIndex].val.CHAR, (char*)value) > 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].val.INTEGER > *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].val.DECIMAL > *((double*)value);
        else if(column.type == BOOL)
            return 1;
        else if(column.type == DATE) {
            printf("DATE datatype functionality coming soon.\n");
            return 0;
        }
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
            else if(column.type == BOOL)
                return 0;
            else if(column.type == DATE) {
                printf("DATE datatype functionality coming soon.\n");
                return 0;
            }
            else
                return 0;
        }
        else if(column.type == CHAR)
            return strcmp(column.values[valIndex].val.CHAR, (char*)value) >= 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].val.INTEGER >= *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].val.DECIMAL >= *((double*)value);
        else if(column.type == BOOL)
            return 1;
        else if(column.type == DATE) {
            printf("DATE datatype functionality coming soon.\n");
            return 0;
        }
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
            else if(column.type == BOOL)
                return 1;
            else if(column.type == DATE) {
                printf("DATE datatype functionality coming soon.\n");
                return 0;
            }
            else
                return 0;
        }
        else if(column.type == CHAR)
            return strcmp(column.values[valIndex].val.CHAR, (char*)value) != 0;
        else if(column.type == INTEGER)
            return column.values[valIndex].val.INTEGER != *((int*)value);
        else if(column.type == DECIMAL)
            return column.values[valIndex].val.DECIMAL != *((double*)value);
        else if(column.type == BOOL)
            return column.values[valIndex].val.BOOL != *((int*)value);
        else if(column.type == DATE) {
            printf("DATE datatype functionality coming soon.\n");
            return 0;
        }
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
        return "MAX";
    else if(strstr(name, "MIN("))
        return "MIN";
    else
        return name;
}

char* getColNameFromAggregate(char* name) {
    char* colName = malloc(sizeof(char) * MAX_LEN);

    if(!isAggregate(name))
        return name;

    if(name != NULL && strchr(name, '('))
        strcpy(colName, strchr(name, '(') + 1);
    else
        return NULL;

    for(int i = 0; i < strlen(colName); i++) {
        if(colName[i] == ')') {
            colName[i] = '\0';
            break;
        }
    }

    colName = realloc(colName, sizeof(char) * (strlen(colName) + 1));

    return colName;
}

Where newWhere(char* searchColName, char* comparison, void* searchValue) {
    Where newWhere;
    newWhere.searchColName = strdup(searchColName);
    newWhere.comparison = strdup(comparison);
    newWhere.searchValue = malloc(max(sizeof(double), strlen(searchValue)));
    memcpy(newWhere.searchValue, searchValue, max(sizeof(double), strlen(searchValue)));

    return newWhere;
}
Select newSelect(int numCols, char** colNames, int distinct) {
    Select select;

    if(numCols < 0)
        select.numCols = 0;
    else
        select.numCols = numCols;
    select.colNames = colNames;
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
    static int boolVal;

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
        else if(types[i] == BOOL) {
            valueList[i] = malloc(sizeof(int));
            boolVal = va_arg(ap, int);
            memcpy(valueList[i], &boolVal, sizeof(int));
        }
        else if(types[i] == DATE) {
            printf("DATE datatype functionality to be implemented soon.\n");
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
                sprintf(printString, "NULL");

            else if(table.cols[j].type == CHAR) {
                sprintf(printString, "%s", table.cols[j].values[i].val.CHAR);
                if(strlen(printString) > 18) {
                    printString[18] = '\0';
                    printString[17] = ' ';
                    printString[16] = '.';
                    printString[15] = '.';
                    printString[14] = '.';
                }
            }
            else if(table.cols[j].type == INTEGER)
                sprintf(printString, "%d", table.cols[j].values[i].val.INTEGER);
            else if(table.cols[j].type == DECIMAL)
                sprintf(printString, "%.3lf", table.cols[j].values[i].val.DECIMAL);
            else if(table.cols[j].type == BOOL) {
                if(table.cols[j].values[i].val.BOOL == 1)
                    sprintf(printString, "TRUE");
                else
                    sprintf(printString, "FALSE");
            }
            else if(table.cols[j].type == DATE)
                sprintf(printString, "DATE");
            printf("| %-*s ", colWidth - 3, printString);
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
            if(table.cols[i].type == INTEGER)
                printf("%d", table.cols[i].values[rowIndex].val.INTEGER);
            else if(table.cols[i].type == CHAR)
                printf("%s", table.cols[i].values[rowIndex].val.CHAR);
            else if(table.cols[i].type == DECIMAL)
                printf("%lf", table.cols[i].values[rowIndex].val.DECIMAL);
            else if(table.cols[i].type == BOOL) {
                if(table.cols[i].values[rowIndex].val.BOOL == 1)
                    printf("TRUE");
                else
                    printf("FALSE");
            }
            else if(table.cols[i].type == DATE)
                printf("DATE datatype functionality coming soon.\n");
        }
    }

    printf(" | \n");
}

void printLoneRow(LoneValue* row, int numValues) {
    printf("\t");

    for(int i = 0; i < numValues; i++) {
        printf(" | ");
        printf("\e[1m%s\e[m", row[i].colName);
    }

    printf(" | \n\t");

    for(int i = 0; i < numValues; i++) {
        printf(" | ");
        if(row[i].value.isNULL) {
            printf("NULL");
        }
        else {
            if(row[i].type == INTEGER)
                printf("%d", row[i].value.val.INTEGER);
            else if(row[i].type == CHAR)
                printf("%s", row[i].value.val.CHAR);
            else if(row[i].type == DECIMAL)
                printf("%lf", row[i].value.val.DECIMAL);
            else if(row[i].type == BOOL) {
                if(row[i].value.val.BOOL == 1)
                    printf("TRUE");
                else
                    printf("FALSE");
            }
            else if(row[i].type == DATE)
                printf("DATE datatype functionality coming soon.\n");
        }
    }

    printf(" | \n");
}

void printColumn(Column col, int numValues) {

    printf("\t| \e[1m%s\e[m |\n", col.name);
    for(int i = 0; i < numValues; i++) {
        printf("\t| ");
        if(col.values[i].isNULL) {
            printf("NULL");
        }
        else {
            if(col.type == INTEGER)
                printf("%d", col.values[i].val.INTEGER);
            else if(col.type == CHAR)
                printf("%s", col.values[i].val.CHAR);
            else if(col.type == DECIMAL)
                printf("%lf", col.values[i].val.DECIMAL);
            else if(col.type == BOOL) {
                if(col.values[i].val.BOOL == 1)
                    printf("TRUE");
                else
                    printf("FALSE");
            }
            else if(col.type == DATE)
                printf("DATE datatype functionality coming soon.\n");

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
    char* stringOfLetters = malloc(sizeof(char) * MAX_LEN);

    int remainder = 1, quot = number, i = 0;
    char dummy;

    do {

        remainder = quot % 26;
        quot = quot / 26;
        stringOfLetters[i] = 65 + remainder;
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

void sortTableByCol(Table* table, char* colName, int ascending) {

    int colIndex;
    Column col = nameToCol(table, colName, &colIndex);
    int type = col.type;
    int isMixed;
    ElementUnion dummy;
    int nullDummy;

    if(ascending) {
        if(type == INTEGER) {
            do {
                isMixed = 0;
                for(int i = 0; i < table->numRows - 1;i++) {
                    if(table->cols[colIndex].values[i].isNULL)
                        table->cols[colIndex].values[i].val.INTEGER = INT_MAX;
                    if(table->cols[colIndex].values[i + 1].isNULL)
                        table->cols[colIndex].values[i + 1].val.INTEGER = INT_MAX;

                    if(table->cols[colIndex].values[i].val.INTEGER > table->cols[colIndex].values[i + 1].val.INTEGER) {
                        isMixed = 1;
                        for(int j = 0; j < table->numCols; j++) {
                            dummy = table->cols[j].values[i].val;
                            nullDummy = table->cols[j].values[i].isNULL;
                            table->cols[j].values[i].val = table->cols[j].values[i + 1].val;
                            table->cols[j].values[i].isNULL = table->cols[j].values[i + 1].isNULL;
                            table->cols[j].values[i + 1].val = dummy;
                            table->cols[j].values[i + 1].isNULL = nullDummy;
                        }
                    }
                }
            } while(isMixed);
        }
        else if(type == DECIMAL) {
            for(int i = 0; i < table->numRows;i++) {
                do {
                    isMixed = 0;
                    for(int i = 0; i < table->numRows - 1;i++) {
                        if(table->cols[colIndex].values[i].isNULL)
                            table->cols[colIndex].values[i].val.DECIMAL = __DBL_MAX__;
                        if(table->cols[colIndex].values[i + 1].isNULL)
                            table->cols[colIndex].values[i + 1].val.DECIMAL = __DBL_MAX__;

                        if(table->cols[colIndex].values[i].val.DECIMAL > table->cols[colIndex].values[i + 1].val.DECIMAL) {
                            isMixed = 1;
                            for(int j = 0; j < table->numCols; j++) {
                                dummy = table->cols[j].values[i].val;
                                nullDummy = table->cols[j].values[i].isNULL;
                                table->cols[j].values[i].val = table->cols[j].values[i + 1].val;
                                table->cols[j].values[i].isNULL = table->cols[j].values[i + 1].isNULL;
                                table->cols[j].values[i + 1].val = dummy;
                                table->cols[j].values[i + 1].isNULL = nullDummy;
                            }
                        }
                    }
                } while(isMixed);
            }
        }
        else if(type == CHAR) {
            for(int i = 0; i < table->numRows;i++) {
                do {
                    isMixed = 0;
                    for(int i = 0; i < table->numRows - 1;i++) {
                        if(table->cols[colIndex].values[i].isNULL)
                            table->cols[colIndex].values[i].val.CHAR = strdup("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ");
                        if(table->cols[colIndex].values[i + 1].isNULL)
                            table->cols[colIndex].values[i + 1].val.CHAR = strdup("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ");

                        if(strcmp(table->cols[colIndex].values[i].val.CHAR, table->cols[colIndex].values[i + 1].val.CHAR) > 0) {
                            isMixed = 1;
                            for(int j = 0; j < table->numCols; j++) {
                                dummy = table->cols[j].values[i].val;
                                nullDummy = table->cols[j].values[i].isNULL;
                                table->cols[j].values[i].val = table->cols[j].values[i + 1].val;
                                table->cols[j].values[i].isNULL = table->cols[j].values[i + 1].isNULL;
                                table->cols[j].values[i + 1].val = dummy;
                                table->cols[j].values[i + 1].isNULL = nullDummy;
                            }
                        }
                    }
                } while(isMixed);
            }
        }
        else if(type == BOOL) {
            do {
                isMixed = 0;
                for(int i = 0; i < table->numRows - 1;i++) {
                    if(table->cols[colIndex].values[i].isNULL)
                        table->cols[colIndex].values[i].val.BOOL = 2;
                    if(table->cols[colIndex].values[i + 1].isNULL)
                        table->cols[colIndex].values[i + 1].val.BOOL = 2;

                    if(table->cols[colIndex].values[i].val.BOOL > table->cols[colIndex].values[i + 1].val.BOOL) {
                        isMixed = 1;
                        for(int j = 0; j < table->numCols; j++) {
                            dummy = table->cols[j].values[i].val;
                            nullDummy = table->cols[j].values[i].isNULL;
                            table->cols[j].values[i].val = table->cols[j].values[i + 1].val;
                            table->cols[j].values[i].isNULL = table->cols[j].values[i + 1].isNULL;
                            table->cols[j].values[i + 1].val = dummy;
                            table->cols[j].values[i + 1].isNULL = nullDummy;
                        }
                    }
                }
            } while(isMixed);
        }
        else if(type == DATE) {
            printf("DATE datatype yet to be implemented.\n");
        }
    }
    else {
        if(type == INTEGER) {
            do {
                isMixed = 0;
                for(int i = 0; i < table->numRows - 1;i++) {
                    if(table->cols[colIndex].values[i].isNULL)
                        table->cols[colIndex].values[i].val.INTEGER = INT_MAX;
                    if(table->cols[colIndex].values[i + 1].isNULL)
                        table->cols[colIndex].values[i + 1].val.INTEGER = INT_MAX;

                    if(table->cols[colIndex].values[i].val.INTEGER < table->cols[colIndex].values[i + 1].val.INTEGER) {
                        isMixed = 1;
                        for(int j = 0; j < table->numCols; j++) {
                            dummy = table->cols[j].values[i].val;
                            nullDummy = table->cols[j].values[i].isNULL;
                            table->cols[j].values[i].val = table->cols[j].values[i + 1].val;
                            table->cols[j].values[i].isNULL = table->cols[j].values[i + 1].isNULL;
                            table->cols[j].values[i + 1].val = dummy;
                            table->cols[j].values[i + 1].isNULL = nullDummy;
                        }
                    }
                }
            } while(isMixed);
        }
        else if(type == DECIMAL) {
            for(int i = 0; i < table->numRows;i++) {
                do {
                    isMixed = 0;
                    for(int i = 0; i < table->numRows - 1;i++) {
                        if(table->cols[colIndex].values[i].isNULL)
                            table->cols[colIndex].values[i].val.DECIMAL = __DBL_MAX__;
                        if(table->cols[colIndex].values[i + 1].isNULL)
                            table->cols[colIndex].values[i + 1].val.DECIMAL = __DBL_MAX__;

                        if(table->cols[colIndex].values[i].val.DECIMAL < table->cols[colIndex].values[i + 1].val.DECIMAL) {
                            isMixed = 1;
                            for(int j = 0; j < table->numCols; j++) {
                                dummy = table->cols[j].values[i].val;
                                nullDummy = table->cols[j].values[i].isNULL;
                                table->cols[j].values[i].val = table->cols[j].values[i + 1].val;
                                table->cols[j].values[i].isNULL = table->cols[j].values[i + 1].isNULL;
                                table->cols[j].values[i + 1].val = dummy;
                                table->cols[j].values[i + 1].isNULL = nullDummy;
                            }
                        }
                    }
                } while(isMixed);
            }
        }
        else if(type == CHAR) {
            for(int i = 0; i < table->numRows;i++) {
                do {
                    isMixed = 0;
                    for(int i = 0; i < table->numRows - 1;i++) {
                        if(table->cols[colIndex].values[i].isNULL)
                            table->cols[colIndex].values[i].val.CHAR = strdup("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ");
                        if(table->cols[colIndex].values[i + 1].isNULL)
                            table->cols[colIndex].values[i + 1].val.CHAR = strdup("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ");

                        if(strcmp(table->cols[colIndex].values[i].val.CHAR, table->cols[colIndex].values[i + 1].val.CHAR) < 0) {
                            isMixed = 1;
                            for(int j = 0; j < table->numCols; j++) {
                                dummy = table->cols[j].values[i].val;
                                nullDummy = table->cols[j].values[i].isNULL;
                                table->cols[j].values[i].val = table->cols[j].values[i + 1].val;
                                table->cols[j].values[i].isNULL = table->cols[j].values[i + 1].isNULL;
                                table->cols[j].values[i + 1].val = dummy;
                                table->cols[j].values[i + 1].isNULL = nullDummy;
                            }
                        }
                    }
                } while(isMixed);
            }
        }
        else if(type == BOOL) {
            do {
                isMixed = 0;
                for(int i = 0; i < table->numRows - 1;i++) {
                    if(table->cols[colIndex].values[i].isNULL)
                        table->cols[colIndex].values[i].val.BOOL = 2;
                    if(table->cols[colIndex].values[i + 1].isNULL)
                        table->cols[colIndex].values[i + 1].val.BOOL = 2;

                    if(table->cols[colIndex].values[i].val.BOOL < table->cols[colIndex].values[i + 1].val.BOOL) {
                        isMixed = 1;
                        for(int j = 0; j < table->numCols; j++) {
                            dummy = table->cols[j].values[i].val;
                            nullDummy = table->cols[j].values[i].isNULL;
                            table->cols[j].values[i].val = table->cols[j].values[i + 1].val;
                            table->cols[j].values[i].isNULL = table->cols[j].values[i + 1].isNULL;
                            table->cols[j].values[i + 1].val = dummy;
                            table->cols[j].values[i + 1].isNULL = nullDummy;
                        }
                    }
                }
            } while(isMixed);
        }
        else if(type == DATE) {
            printf("DATE datatype yet to be implemented.\n");
        }
    }
}

Table* importTable(char* tableName, char* filename) {

    char* properName = addQuotesToString(tableName);

    Table* table = NULL;

    if(endsWith(filename, ".db")) {
        char* sql = malloc(sizeof(char) * 1000);
        sqlite3* db;
        char** errMessage = malloc(sizeof(char*));
        *errMessage = strdup("Error: SQL Execution Failed");
        strcpy(sql, "SELECT Name FROM SQLITE_MASTER WHERE Name = '");
        strcat(sql, tableName);
        strcat(sql, "'");

        sqlite3_open(filename, &db);
        int tableExists = -1;
        sqlite3_exec(db, sql, callbackCheckExists, &tableExists, errMessage);

        if(tableExists == 1) {
            strcpy(sql, "SELECT * FROM ");
            strcat(sql, properName);
            void** value = malloc(sizeof(void*));
            //*value goes in as char* and comes out as Table*
            *value = strdup(tableName);
            sqlite3_exec(db, sql, callbackCreateTable, value, errMessage);

            table = malloc(sizeof(Table));
            memcpy(table, (Table*)(*value), sizeof(Table));

            printTable(*table);

            strcpy(sql, "SELECT sql FROM SQLITE_MASTER WHERE Name = ");
            strcat(sql, "'My Table'");
            sqlite3_exec(db, sql, callbackGetAttributes, table, errMessage);

            strcpy(sql, "SELECT * FROM ");
            strcat(sql, properName);
            sqlite3_exec(db, sql, callbackInsertData, table, errMessage);
        }
        else {
            printf("Error: Table '%s' not found in file '%s'. Import failed.\n", tableName, filename);
        }
        sqlite3_close(db);

        free(*errMessage);
        free(errMessage);
        free(sql);
    }
    else {

        FILE* fp = fopen(filename, "r");
        if(fp) {
            char* tableCreateLine = malloc(sizeof(char) * 1000);
            strcpy(tableCreateLine, "CREATE TABLE ");
            strcat(tableCreateLine, properName);
            char* rowInsertLine = malloc(sizeof(char) * 1000);
            strcpy(rowInsertLine, "INSERT INTO ");
            strcat(rowInsertLine, properName);

            int creating = 0;
            int inserting = 0;

            char line[1000];
            char* createCmd = malloc(sizeof(char) * 10000);

            //LIMITATION: CREATE AND INSERT COMMANDS MUST BE ON SEPARATE LINES OF GIVEN FILE. FIX IN THE FUTURE!
            while(fgets(line, 1000, fp)) {
                printf("%s\n", createCmd);

                if(!creating && strstr(line, tableCreateLine)) {
                    creating = 1;
                }
                if(creating) {
                    if(strstr(line, ";")) {
                        char* lineCopy = strdup(line);
                        strcat(createCmd, strtok(lineCopy, ";"));
                        strcat(createCmd, ";\n");
                        creating = 0;
                        free(lineCopy);
                    }
                    else
                        strcat(createCmd, line);
                    printf("LINE: %s\n", line);
                }
                if(!inserting && strstr(line, rowInsertLine)) {
                    printf("LINE: %s\n", strstr(line, rowInsertLine));
                    inserting = 1;
                }
                if(inserting) {
                    if(strstr(line, ";")) {
                        char* lineCopy = strdup(line);
                        strcat(createCmd, strtok(lineCopy, ";"));
                        strcat(createCmd, ";\n");
                        inserting = 0;
                        free(lineCopy);
                    }
                    else
                        strcat(createCmd, line);
                }
            }
            fclose(fp);

            printf("%s\n", createCmd);
            sqlite3* db;
            char** errMessage = malloc(sizeof(char*));
            *errMessage = strdup("Error: SQL Execution Failed");

            truncate("load.db", 0);

            sqlite3_open("load.db", &db);
            sqlite3_exec(db, createCmd, NULL, NULL, errMessage);
            sqlite3_close(db);
            free(errMessage);
            free(createCmd);

            table = importTable(tableName, "load.db");

            remove("load.db");
        }
    }

    free(properName);

    return table;

}

int importDatabase(char* filename, Table** tables) {

    int numTables = 0;

    if(endsWith(filename, ".db")) {

        char* sql = malloc(sizeof(char) * 1000);
        sqlite3* db;
        char** errMessage = malloc(sizeof(char*));
        *errMessage = strdup("Error: SQL Execution Failed");

        strcpy(sql, "SELECT Name FROM SQLITE_MASTER");

        sqlite3_open(filename, &db);

        struct TableNames {
            char** names;
            int numNames;
        };

        struct TableNames* names = malloc(sizeof(struct TableNames));

        sqlite3_exec(db, sql, callbackGetTableNames, names, errMessage);

        sqlite3_close(db);

        numTables = names->numNames;

        if(numTables >= 1) {

            if(tables == NULL)
                tables = malloc(sizeof(Table*));

            for(int i = 0; i < numTables; i++) {
                if(i == 0)
                    *tables = malloc(sizeof(Table));
                else
                    *tables = realloc(*tables, sizeof(Table) * (i + 1));

                (*tables)[i] = *importTable(names->names[i], filename);
            }
        }
        else {
            printf("Error: No tables found in file '%s'. Import failed.\n", filename);
        }

        free(*errMessage);
        free(errMessage);
        free(sql);
    }
    else {

        FILE* fp = fopen(filename, "r");
        if(fp) {
            char* sql = malloc(sizeof(char) * 10000);
            char line[1000];
            strcpy(sql, "");

            while(fgets(line, 1000, fp))
                strcat(sql, line);

            printf("%s\n", sql);
            sqlite3* db;
            char** errMessage = malloc(sizeof(char*));
            *errMessage = strdup("Error: SQL Execution Failed");

            truncate("load.db", 0);

            sqlite3_open("load.db", &db);
            sqlite3_exec(db, sql, NULL, NULL, errMessage);
            sqlite3_close(db);
            free(errMessage);
            free(sql);

            numTables = importDatabase("load.db", tables);

            remove("load.db");

        }
        fclose(fp);
    }

    return numTables;
}

void exportTable(Table table, char* filename, int trunc) {

    char* sql = malloc(sizeof(char) * 1000);

    strcpy(sql, "CREATE TABLE ");
    char* tableName = addQuotesToString(table.name);

    strcat(sql, tableName);

    strcat(sql, "(");

    char* colName;
    for(int i = 0; i < table.numCols; i++) {
        colName = addQuotesToString(table.cols[i].name);
        strcat(sql, colName);
        strcat(sql, " ");

        if(table.cols[i].type != BOOL)
            strcat(sql, typeToString(table.cols[i].type));
        else
            strcat(sql, "BIT");

        if(i < table.numCols - 1)
            strcat(sql, ", ");

        free(colName);
    }

    strcat(sql, ");\n");

    for(int i = 0; i < table.numRows; i++) {
        strcat(sql, "INSERT INTO ");
        strcat(sql, tableName);
        strcat(sql, "(");

        for(int j = 0; j < table.numCols; j++) {
            colName = addQuotesToString(table.cols[j].name);
            strcat(sql, colName);
            if(j < table.numCols - 1)
                strcat(sql, ", ");

            free(colName);
        }

        strcat(sql, ")\n");

        strcat(sql, "VALUES(");
        for(int j = 0; j < table.numCols; j++) {
            if(table.cols[j].values[i].isNULL) {
                strcat(sql, "NULL");
            }
            else if(table.cols[j].type == INTEGER) {
                char intString[MAX_LEN];
                sprintf(intString, "%d", table.cols[j].values[i].val.INTEGER);
                strcat(sql, intString);
            }
            else if(table.cols[j].type == DECIMAL) {
                char decString[MAX_LEN];
                sprintf(decString, "%lf", table.cols[j].values[i].val.DECIMAL);
                strcat(sql, decString);
            }
            else if(table.cols[j].type == CHAR) {
                char chrString[MAX_LEN];
                sprintf(chrString, "'%s'", table.cols[j].values[i].val.CHAR);
                strcat(sql, chrString);
            }
            else if(table.cols[j].type == BOOL) {
                char boolString[MAX_LEN];
                sprintf(boolString, "%d", table.cols[j].values[i].val.BOOL);
                strcat(sql, boolString);
                // if(table.cols[j].values[i].val.BOOL == 1)
                //     strcat(sql, "TRUE");
                // else
                //     strcat(sql, "FALSE");
            }
            else if(table.cols[j].type == DATE) {
                printf("DATE datatype functionality coming soon.\n");
            }
            if(j < table.numCols - 1)
                strcat(sql, ", ");
        }

        strcat(sql, ");\n");

    }

    strcat(sql, "\n");

    if(trunc)
        truncate(filename, 0);

    if(endsWith(filename, ".db")) {
        sqlite3* db;
        char** errMessage = malloc(sizeof(char*));
        *errMessage = strdup("Error: SQL Execution Failed");

        char* delPrevTable = malloc(sizeof(char) * MAX_LEN);
        strcpy(delPrevTable, "DROP TABLE IF EXISTS ");
        strcat(delPrevTable, tableName);

        sqlite3_open(filename, &db);
        sqlite3_exec(db, delPrevTable, NULL, NULL, errMessage);
        sqlite3_exec(db, sql, NULL, NULL, errMessage);
        sqlite3_close(db);

        free(*errMessage);
        free(errMessage);
    }
    else {

        FILE* fp = fopen(filename, "r");
        if(fp) {
            char* tableCreateLine = malloc(sizeof(char) * 1000);
            strcpy(tableCreateLine, "CREATE TABLE ");
            strcat(tableCreateLine, tableName);

            int tableExists = 0;

            char line[1000];
            while(fgets(line, 1000, fp)) {
                if(!tableExists && strstr(line, tableCreateLine)) {
                    tableExists = 1;
                    fgets(line, 1000, fp);
                    if(!strstr(line, "INSERT INTO"))
                        tableExists = 0;
                }
                if(tableExists && strstr(line, "CREATE TABLE")) {
                    tableExists = 0;
                }
                if(!tableExists) {
                    strcat(sql, line);
                }
            }
        }
        fclose(fp);
        fp = fopen(filename, "w");
        fprintf(fp, "%s", sql);
        fclose(fp);
    }

    free(tableName);

    free(sql);
}

int callbackCheckExists(void* value, int numCols, char** values, char** columnNames) {
    *((int*)value) = numCols;
    return 0;
}

int callbackPrintData(void* value, int numCols, char** values, char** columnNames) {
    for(int i = 0; i < numCols; i++) {
        printf("%s: %s\n", columnNames[i], values[i]);
    }
    return 0;
}

int callbackCreateTable(void* value, int numCols, char** values, char** colNames) {
    char* tableName = strdup(*(void**)value);
    int* colTypes = malloc(sizeof(int) * numCols);
    for(int i = 0; i < numCols;i++)
        colTypes[i] = CHAR;
    Table* table = malloc(sizeof(Table));
    *table = create(tableName, numCols, colNames, colTypes);
    *((void**)value) = table;
    return 1;
}

int callbackInsertData(void* value, int numCols, char** values, char** colNames) {
    Table* table = ((Table*)value);

    printf("INSERT TIME\n");

    for(int i = 0; i < numCols; i++) {
        Column currCol = nameToCol(table, colNames[i], NULL);

        if(values[i] != NULL) {
            if(currCol.type == INTEGER) {
                printf("INTEGER\n");
                int* intVal = malloc(sizeof(int));
                sscanf(values[i], "%d", intVal);
                values[i] = (void*)intVal;
            }
            else if(currCol.type == DECIMAL) {
                printf("DECIMAL\n");
                double* decVal = malloc(sizeof(double));
                sscanf(values[i], "%lf", decVal);
                values[i] = (void*)decVal;
            }
            else if(currCol.type == BOOL) {
                printf("BOOL\n");
                int* boolVal = malloc(sizeof(int));
                sscanf(values[i], "%d", boolVal);
                values[i] = (void*)boolVal;
                // if(strcmp(values[i], "TRUE") == 0)
                //     *boolVal = 1;
                // else
                //     *boolVal = 0;
            }
            else if(currCol.type == DATE) {
                printf("DATE datatype functionality coming soon.\n");
            }
        }
    }
    insertRow(table, numCols, colNames, (void**)values);

    printf("DONE INSERTING\n");
    return 0;
}

int callbackGetTableNames(void* value, int numCols, char** values, char** colNames) {
    struct TableNames {
        char** names;
        int numNames;
    };
    if(++(((struct TableNames*)value)->numNames) == 1)
        ((struct TableNames*)value)->names = malloc(sizeof(char*));
    else
        ((struct TableNames*)value)->names = realloc(((struct TableNames*)value)->names, sizeof(char*) * ((struct TableNames*)value)->numNames);

    ((struct TableNames*)value)->names[((struct TableNames*)value)->numNames - 1] = strdup(values[0]);

    return 0;
}

int callbackGetAttributes(void* value, int numCols, char** values, char** colNames) {
    Table* table = ((Table*)value);
    char* currCol = malloc(sizeof(char) * (strlen(values[0]) + 1));

    for(int i = 0; i < table->numCols; i++) {
        printf("%s\n", table->cols[i].name);
        strcpy(currCol, strstr(values[0], addQuotesToString(table->cols[i].name)));
        printf("%s\n", currCol);
        if(currCol) {
            char* colAttrs;
            if(currCol[0] == '`') {
                currCol++;
                colAttrs = strstr(currCol, "`") + 2;
            }
            else {
                colAttrs = strstr(currCol, " ") + 1;
            }
            if(strstr(colAttrs, ","))
                strstr(colAttrs, ",")[0] = '\0';

            printf("%s\n", colAttrs);

            if(strstr(colAttrs, typeToString(INTEGER)))
                table->cols[i].type = INTEGER;
            else if(strstr(colAttrs, typeToString(CHAR)))
                table->cols[i].type = CHAR;
            else if(strstr(colAttrs, typeToString(DECIMAL)))
                table->cols[i].type = DECIMAL;
            else if(strstr(colAttrs, typeToString(DATE)))
                table->cols[i].type = DATE;
            else if(strstr(colAttrs, typeToString(BOOL)) || strstr(colAttrs, "BIT"))
                table->cols[i].type = BOOL;
            // if(strstr(colAttrs, "PRIMARY KEY")) {
            //     table->cols[i].primaryKey = 1;
            // }
            // if(strstr(colAttrs, "AUTOINCREMENT")) {
            //     table->cols[i].autoIncrement = 1;
            // }
            // if(strstr(colAttrs, "NOT NULL")) {
            //     table->cols[i].notNull = 1;
            // }
            // if(strstr(colAttrs, "FOREIGN KEY REFERENCES")) {
            //     table->cols[i].foreignKey = 1;
            //     //Code to get the foreign key column
            // }
            // if(strstr(colAttrs, "UNIQUE")) {
            //     table->cols[i].unique = 1;
            // }
            // if(strstr(colAttrs, "DEFAULT")) {
            //     table->cols[i].default = 1;
            //     //Code to get the default value
            // }
        }
    }
    printf("%s\n", values[0]);
    return 0;
}

int endsWith(char* str, char* ext) {
    int stringLength = strlen(str);
    int extLength = strlen(ext);

    if(stringLength >= extLength)
        if(!strcmp(str + stringLength - extLength, ext))
            return 1;

    return 0;
}

char* addQuotesToString(char* string) {

    char* newString = strdup(string);

    for(int i = 0; i < strlen(newString); i++) {
        if(!(isalpha(newString[i]) || isdigit(newString[i]) || newString[i] == '_')) {
            newString = realloc(newString, strlen(newString) + 3);

            strcat(newString, "`");
            for(int j = strlen(newString); j > 0; j--) {
                newString[j] = newString[j - 1];
            }
            newString[0] = '`';
            break;
        }
    }

    return newString;
}

char* removeQuotesFromString(char* string) {
    char* newString = strdup(string);

    for(int i = 0; i < strlen(newString) - 2; i++)
        newString[i] = newString[i + 1];
    newString[strlen(newString) - 2] = '\0';

    return newString;

}

Table* userTableOperator(int numTables, Table* tables) {

    Table* currentTable = NULL;

    int* menuChoices;
    int currTableIndex = -1;;

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

    LoneValue* rowCopy = NULL;
    int rowCopyLength;
    Column colCopy;
    colCopy.name = NULL;
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

                    case 3:
                        // "3. PRINT copied row"
                        if(rowCopy != NULL) {
                            printf("The row you currently have copied:\n");
                            printLoneRow(rowCopy, rowCopyLength);
                        }
                        else {
                            printf("You do not have a row copied at the moment.\n");
                        }
                        break;

                    case 4:
                        // "4. PRINT copied column"
                        if(colCopy.name != NULL) {
                            printf("The column you currently have copied:\n");
                            printColumn(colCopy, colCopyLength);
                        }
                        else {
                            printf("You do not have a column copied at the moment.\n");
                        }
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
                if(numTables <= 0) {
                    printf("There are no tables to choose from for renaming.\n");
                    break;
                }
                if(currentTable == NULL) {
                    printf("Which table would you like to choose from for renaming?\n");
                    currTableIndex = tableMenu(numTables, tables);
                    currentTable = &tables[currTableIndex];
                    printf("Here is your current table:\n");
                    printTable(*currentTable);
                }

                switch(menuChoices[1]) {
                    case 1:
                        // "1. RENAME column in current table"
                        if(currentTable->numCols == 0) {
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
                        }

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

                printf("How many columns would you like to select? (1-%d): ", currentTable->numCols);
                do {
                    scanfWell("%d", &sel.numCols);
                    if(sel.numCols <= 0)
                        printf("Please input a positive number: ");
                    else if(sel.numCols > currentTable->numCols)
                        printf("Your current table doesn't have that many columns. Try again: ");
                } while(sel.numCols <= 0 || sel.numCols > currentTable->numCols);

                sel.colNames = malloc(sizeof(char*) * sel.numCols);
                // if(sel.numCols < currentTable->numCols) {
                for(int i = 0; i < sel.numCols; i++) {
                    sel.colNames[i] = malloc(sizeof(char) * MAX_LEN);
                    printf("Name for select column #%d: ", i + 1);
                    do {
                        fgetsUntil(sel.colNames[i], MAX_LEN);
                        if(nameToCol(currentTable, sel.colNames[i], NULL).type == -1 && nameToCol(currentTable, getColNameFromAggregate(sel.colNames[i]), NULL).type == -1) {
                            printf("Please enter a column name that exists in your table: ");
                            continue;
                        }
                        else
                            break;
                    } while(1);
                    sel.colNames[i] = realloc(sel.colNames[i], sizeof(char) * (strlen(sel.colNames[i]) + 1));
                }
                // }
                // else {
                //     for(int i = 0; i < sel.numCols; i++) {
                //         sel.colNames[i] = NULL;
                //         //sel.colnames[0] = "*";
                //     }
                // }

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

                tables[numTables - 1] = cql_select(*currentTable, sel, numWheres, whereList, connectiveList);

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

                checkTableNames(tables, numTables, currentTable->name, currTableIndex);

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
                                        printf("Name for column to provide value for #%d: ", i + 1);
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
                                    else if(nameToCol(currentTable, nameList[i], NULL).type == BOOL) {
                                        valueList[i] = malloc(sizeof(int));

                                        char temp[MAX_LEN];
                                        do {
                                            fgetsUntil(temp, MAX_LEN);
                                            if(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0)
                                                printf("Please input 'TRUE' or 'FALSE': ");
                                        } while(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0);

                                        if(strcmp(temp, "TRUE") == 0)
                                            sscanf("1", "%d", (int*)valueList[i]);
                                        else
                                            sscanf("0", "%d", (int*)valueList[i]);
                                    }
                                    else if(nameToCol(currentTable, nameList[i], NULL).type == DATE) {
                                        printf("DATE datatype functionality coming soon.\n");
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
                                    else if(nameToCol(currentTable, nameList[i], NULL).type == BOOL) {
                                        valueList[i] = malloc(sizeof(int));

                                        char temp[MAX_LEN];
                                        do {
                                            fgetsUntil(temp, MAX_LEN);
                                            if(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0)
                                                printf("Please input 'TRUE' or 'FALSE': ");
                                        } while(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0);

                                        if(strcmp(temp, "TRUE") == 0)
                                            sscanf("1", "%d", (int*)valueList[i]);
                                        else
                                            sscanf("0", "%d", (int*)valueList[i]);
                                    }
                                    else if(nameToCol(currentTable, nameList[i], NULL).type == DATE) {
                                        printf("DATE datatype functionality coming soon.\n");
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

                        int colType;

                        printf("Please input the name of the new column: ");
                        fgetsUntil(colName, MAX_LEN);

                        printf("What type should this column be?:\n");
                        colType = typeInput();

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
                                    else if(colType == BOOL) {
                                        valueList[i] = malloc(sizeof(int));
                                        char temp[MAX_LEN];
                                        do {
                                            fgetsUntil(temp, MAX_LEN);
                                            if(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0)
                                                printf("Please input 'TRUE' or 'FALSE': ");
                                        } while(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0);

                                        if(strcmp(temp, "TRUE") == 0)
                                            sscanf("1", "%d", (int*)valueList[i]);
                                        else
                                            sscanf("0", "%d", (int*)valueList[i]);
                                    }
                                    else if(colType == DATE) {
                                        printf("DATE datatype functionality yet to be implemented.\n");
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
                                    else if(colType == BOOL) {
                                        valueList[i] = malloc(sizeof(int));
                                        char temp[MAX_LEN];
                                        do {
                                            fgetsUntil(temp, MAX_LEN);
                                            if(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0)
                                                printf("Please input 'TRUE' or 'FALSE': ");
                                        } while(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0);

                                        if(strcmp(temp, "TRUE") == 0)
                                            sscanf("1", "%d", (int*)valueList[i]);
                                        else
                                            sscanf("0", "%d", (int*)valueList[i]);
                                    }
                                    else if(colType == DATE) {
                                        printf("DATE datatype functionality yet to be implemented.\n");
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

                            insertIntoCol(currentTable, colName, colType, numThings, numList, valueList, colString);
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
                switch(menuChoices[1]) {
                    case 1:
                        // "1. UPDATE a existing values in current table"
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
                                printf("Please input the name of a column you would like to update the value(s) of: ");
                                if(numUpdCols == 1) {
                                    nameList = malloc(sizeof(char*) * 1);
                                    valueList = malloc(sizeof(void*) * 1);
                                }
                                else {
                                    nameList = realloc(nameList, sizeof(char*) * numUpdCols);
                                    valueList = realloc(valueList, sizeof(void*) * numUpdCols);
                                }

                                nameList[numUpdCols - 1] = malloc(sizeof(char) * MAX_LEN);

                                int colIndex;
                                do {
                                    fgetsUntil(nameList[numUpdCols - 1], MAX_LEN);
                                    nameToCol(currentTable, nameList[numUpdCols - 1], &colIndex);
                                    if(colIndex == -1)
                                        printf("Please try again: ");
                                } while(colIndex == -1);
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
                                else if(colType == BOOL) {
                                    valueList[numUpdCols - 1] = malloc(sizeof(int));

                                    char temp[MAX_LEN];
                                    do {
                                        fgetsUntil(temp, MAX_LEN);
                                        if(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0)
                                            printf("Please input 'TRUE' or 'FALSE': ");
                                    } while(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0);

                                    if(strcmp(temp, "TRUE") == 0)
                                        sscanf("1", "%d", (int*)valueList[numUpdCols - 1]);
                                    else
                                        sscanf("0", "%d", (int*)valueList[numUpdCols - 1]);
                                }
                                else if(colType == DATE) {
                                    printf("DATE datatype functionality coming soon.\n");
                                }

                                if(numUpdCols + 1 <= currentTable->numCols) {
                                    printf("Would you like to add another column to have its values updated? (yes/no): ");
                                    do {
                                        fgetsUntil(yesno, MAX_LEN);
                                        if(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0)
                                            printf("Please input 'yes' or 'no': ");
                                    } while(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0);
                                }

                            } while(strcmp(yesno, "yes") == 0 && numUpdCols + 1 <= currentTable->numCols);

                            numWheres = whereInput(currentTable, &whereList, &connectiveList);

                            update(currentTable, numUpdCols, nameList, valueList, numWheres, whereList, connectiveList);

                            for(int i = 0; i < numUpdCols; i++) {
                                free(nameList[i]);
                                free(valueList[i]);
                            }
                            free(nameList);
                            free(valueList);
                            nameList = NULL;
                            valueList = NULL;
                        }
                        else {
                            int* colNums = NULL;
                            int numColsChosen = 0;

                            numColsChosen = colPosInput(&colNums, currentTable->numCols);

                            int* rowNums = NULL;
                            int numRowsChosen = 0;

                            numRowsChosen = rowNumInput(&rowNums, currentTable->numRows);

                            int* intVal = NULL;
                            double* decVal = NULL;
                            char* charVal = NULL;
                            int* boolVal = NULL;
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
                                else if(currentTable->cols[colNums[i]].type == BOOL) {
                                    if(boolVal == NULL) {
                                        boolVal = malloc(sizeof(int));
                                        printf("Please input your new value for columns of type BOOL: ");
                                        char temp[MAX_LEN];
                                        do {
                                            fgetsUntil(temp, MAX_LEN);
                                            if(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0)
                                                printf("Please input 'TRUE' or 'FALSE': ");
                                        } while(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0);
                                        if(strcmp(temp, "TRUE") == 0)
                                            *boolVal = 1;
                                        else
                                            *boolVal = 0;
                                    }
                                    for(int j = 0; j < numRowsChosen; j++) {
                                        currentTable->cols[colNums[i]].values[rowNums[j]].isNULL = 0;
                                        currentTable->cols[colNums[i]].values[rowNums[j]].val.BOOL = *boolVal;
                                    }
                                }
                                else if(currentTable->cols[colNums[i]].type == DATE) {
                                    printf("DATE datatype functionality coming soon.\n");
                                }
                            }

                            if(colNums != NULL)
                                free(colNums);
                            if(rowNums != NULL)
                                free(rowNums);

                        }
                        break;
                    case 2:
                        //"2. UPDATE attributes of column in current table"
                        break;
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
                            int boolDummy;

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
                                            currentTable->cols[i].values[j].val.CHAR = strdup(currentTable->cols[i].values[j + 1].val.CHAR);
                                            currentTable->cols[i].values[j].isNULL = currentTable->cols[i].values[j + 1].isNULL;
                                        }
                                    }
                                    else {
                                        for(int j = rowNum; j > newPos; j--) {
                                            printf("%s into %s\n", currentTable->cols[i].values[j - 1].val.CHAR, currentTable->cols[i].values[j].val.CHAR);
                                            currentTable->cols[i].values[j].val.CHAR = strdup(currentTable->cols[i].values[j - 1].val.CHAR);
                                            currentTable->cols[i].values[j].isNULL = currentTable->cols[i].values[j - 1].isNULL;
                                        }
                                    }
                                    printf("%s into %s\n", charDummy, currentTable->cols[i].values[newPos].val.CHAR);
                                    currentTable->cols[i].values[newPos].val.CHAR = strdup(charDummy);

                                }
                                else if(currentTable->cols[i].type == BOOL) {
                                    boolDummy = currentTable->cols[i].values[rowNum].val.BOOL;

                                    if(newPos > rowNum) {
                                        for(int j = rowNum; j < newPos; j++) {
                                            currentTable->cols[i].values[j].val.BOOL = currentTable->cols[i].values[j + 1].val.BOOL;
                                            currentTable->cols[i].values[j].isNULL = currentTable->cols[i].values[j + 1].isNULL;
                                        }
                                    }
                                    else {
                                        for(int j = rowNum; j > newPos; j--) {
                                            currentTable->cols[i].values[j].val.BOOL = currentTable->cols[i].values[j - 1].val.BOOL;
                                            currentTable->cols[i].values[j].isNULL = currentTable->cols[i].values[j - 1].isNULL;
                                        }
                                    }

                                    currentTable->cols[i].values[newPos].val.BOOL = boolDummy;
                                }
                                else if(currentTable->cols[i].type == DATE) {
                                    printf("DATE datatype functionality coming soon.\n");
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
                //"9. SORT"

                if(numTables <= 0) {
                    printf("There are no tables to choose from.\n");
                    break;
                }
                if(currentTable == NULL) {
                    if(menuChoices[1] == 1)
                        printf("Which table would you like to paste a row into?\n");
                    else if(menuChoices[1] == 2)
                        printf("Which table would you like to paste a column into?\n");
                    currTableIndex = tableMenu(numTables, tables);
                    currentTable = &tables[currTableIndex];
                    printf("Here is your current table:\n");
                    printTable(*currentTable);
                }

                // "1. SORT rows by the values of a column"
                printf("Please input the name of the column you would like to sort by: ");

                int colIndex;
                do {
                    fgetsUntil(colName, MAX_LEN);
                    nameToCol(currentTable, colName, &colIndex);
                    if(colIndex == -1)
                        printf("Please try again: ");
                } while(colIndex == -1);

                char ascdesc[MAX_LEN];
                int ascending = 1;
                printf("Would you like the data to be ascending ('asc') or descending ('desc'): ");
                do {
                    fgetsUntil(ascdesc, MAX_LEN);
                    if(strcmp(ascdesc, "asc") != 0 && strcmp(ascdesc, "desc") != 0)
                        printf("Please input 'asc' or 'desc': ");
                } while(strcmp(ascdesc, "asc") != 0 && strcmp(ascdesc, "desc") != 0);

                if(strcmp(ascdesc, "desc") == 0)
                    ascending = 0;

                sortTableByCol(currentTable, colName, ascending);

                break;

            case 10:
                //"10. JOIN"
                break;

            case 11:
                //"11. COPY"
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
            case 12:
                //"12. PASTE"
                if(numTables <= 0) {
                    printf("There are no tables to choose from.\n");
                    break;
                }
                if(currentTable == NULL) {
                    if(menuChoices[1] == 1)
                        printf("Which table would you like to paste a row into?\n");
                    else if(menuChoices[1] == 2)
                        printf("Which table would you like to paste a column into?\n");
                    currTableIndex = tableMenu(numTables, tables);
                    currentTable = &tables[currTableIndex];
                    printf("Here is your current table:\n");
                    printTable(*currentTable);
                }

                switch(menuChoices[1]) {
                    case 1:
                        // "1. PASTE row in current table"
                        if(rowCopy != NULL) {
                            int typeMatch = 1;
                            int colNameMatch = 0;
                            int proceed = 0;

                            for(int i = 0; i < min(currentTable->numCols, rowCopyLength); i++) {
                                if(typeMatch && currentTable->cols[i].type != rowCopy[i].type)
                                    typeMatch = 0;
                                if(!colNameMatch && containsCol(*currentTable, rowCopy[i].colName))
                                    colNameMatch = 1;
                                if(!typeMatch && colNameMatch)
                                    break;
                            }

                            if(colNameMatch) {
                                printf("Your copied row shares at least one column name with your current table.\n"
                                    "Would you like to paste this row with respect to the column names?\n"
                                    "(You will otherwise paste with respect to the column types and the current ordering of the columns and your row)\n"
                                    "(yes / no): ");
                                do {
                                    fgetsUntil(yesno, MAX_LEN);
                                    if(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0)
                                        printf("Please input 'yes' or 'no': ");
                                } while(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0);

                                if(strcmp(yesno, "yes") == 0) {
                                    proceed = 1;

                                    int numCommonNames = 0;
                                    int includeMissing = 0;

                                    for(int i = 0; i < rowCopyLength; i++) {
                                        numCommonNames += containsCol(*currentTable, rowCopy[i].colName);
                                    }
                                    if(numCommonNames < rowCopyLength) {
                                        printf("Would you like to include the values that do not share a column name in your paste?\n"
                                            "(This will expand your table and insert the missing columns)\n"
                                            "(yes / no): ");
                                        do {
                                            fgetsUntil(yesno, MAX_LEN);
                                            if(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0)
                                                printf("Please input 'yes' or 'no': ");
                                        } while(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0);

                                        if(strcmp(yesno, "yes") == 0)
                                            includeMissing = 1;
                                    }

                                    nameList = malloc(sizeof(char*) * (numCommonNames + (rowCopyLength - numCommonNames) * includeMissing));
                                    valueList = malloc(sizeof(void*) * (numCommonNames + (rowCopyLength - numCommonNames) * includeMissing));
                                    int count = 0;

                                    for(int i = 0; i < rowCopyLength; i++) {
                                        if(includeMissing && !containsCol(*currentTable, rowCopy[i].colName)) {
                                            insertCol(currentTable, rowCopy[i].colName, rowCopy[i].type, 0, NULL, NULL);
                                        }
                                        if(containsCol(*currentTable, rowCopy[i].colName)) {
                                            nameList[count] = strdup(rowCopy[i].colName);
                                            if(!rowCopy[i].value.isNULL) {
                                                if(rowCopy[i].type == INTEGER) {
                                                    valueList[count] = malloc(sizeof(int));
                                                    memcpy(valueList[count], &rowCopy[i].value.val.INTEGER, sizeof(int));
                                                }
                                                else if(rowCopy[i].type == DECIMAL) {
                                                    valueList[count] = malloc(sizeof(double));
                                                    memcpy(valueList[count], &rowCopy[i].value.val.DECIMAL, sizeof(double));
                                                }
                                                else if(rowCopy[i].type == CHAR) {
                                                    valueList[count] = strdup(rowCopy[i].value.val.CHAR);
                                                }
                                                else if(rowCopy[i].type == BOOL) {
                                                    valueList[count] = malloc(sizeof(int));
                                                    memcpy(valueList[count], &rowCopy[i].value.val.BOOL, sizeof(int));
                                                }
                                                else if(rowCopy[i].type == DATE) {
                                                    printf("DATE datatype functionality coming soon.\n");
                                                }
                                            }
                                            else {
                                                valueList[count] = NULL;
                                            }
                                            count++;
                                        }
                                    }

                                }
                            }

                            if(!proceed && typeMatch) {

                                proceed = 1;

                                if(rowCopyLength >= currentTable->numCols) {
                                    valueList = malloc(sizeof(void*) * rowCopyLength);

                                    for(int i = 0; i < rowCopyLength; i++) {
                                        if(!rowCopy[i].value.isNULL) {
                                            if(rowCopy[i].type == INTEGER) {
                                                valueList[i] = malloc(sizeof(int));
                                                memcpy(valueList[i], &rowCopy[i].value.val.INTEGER, sizeof(int));
                                            }
                                            else if(rowCopy[i].type == DECIMAL) {
                                                valueList[i] = malloc(sizeof(double));
                                                memcpy(valueList[i], &rowCopy[i].value.val.DECIMAL, sizeof(double));
                                            }
                                            else if(rowCopy[i].type == CHAR) {
                                                valueList[i] = strdup(rowCopy[i].value.val.CHAR);
                                            }
                                            else if(rowCopy[i].type == BOOL) {
                                                valueList[i] = malloc(sizeof(int));
                                                memcpy(valueList[i], &rowCopy[i].value.val.BOOL, sizeof(int));
                                            }
                                            else if(rowCopy[i].type == DATE) {
                                                printf("DATE datatype functionality coming soon.\n");
                                            }
                                        }
                                        else {
                                            valueList[i] = NULL;
                                        }
                                    }
                                }
                                else {
                                    valueList = malloc(sizeof(void*) * currentTable->numCols);

                                    for(int i = 0; i < currentTable->numCols; i++) {
                                        if(i < rowCopyLength) {
                                            if(!rowCopy[i].value.isNULL) {
                                                if(rowCopy[i].type == INTEGER) {
                                                    valueList[i] = malloc(sizeof(int));
                                                    memcpy(valueList[i], &rowCopy[i].value.val.INTEGER, sizeof(int));
                                                }
                                                else if(rowCopy[i].type == DECIMAL) {
                                                    valueList[i] = malloc(sizeof(double));
                                                    memcpy(valueList[i], &rowCopy[i].value.val.DECIMAL, sizeof(double));
                                                }
                                                else if(rowCopy[i].type == CHAR) {
                                                    valueList[i] = strdup(rowCopy[i].value.val.CHAR);
                                                }
                                                else if(rowCopy[i].type == BOOL) {
                                                    valueList[i] = malloc(sizeof(int));
                                                    memcpy(valueList[i], &rowCopy[i].value.val.BOOL, sizeof(int));
                                                }
                                                else if(rowCopy[i].type == DATE) {
                                                    printf("DATE datatype functionality coming soon.\n");
                                                }
                                            }
                                            else {
                                                valueList[i] = NULL;
                                            }
                                        }
                                        else {
                                            valueList[i] = NULL;
                                        }
                                    }
                                }

                                if(currentTable->numCols < rowCopyLength) {
                                    printf("How would you like to paste?:\n");
                                    printf("1. Shrink row to fit table\n"
                                        "2. Grow table to fit row\n"
                                        "Your choice: ");

                                    do {
                                        scanfWell("%d", &menuChoices[1]);
                                        if(menuChoices[1] < 1 || menuChoices[1] > 2)
                                            printf("Please choose between 1 and %d: ", 2);
                                    } while(menuChoices[1] < 1 || menuChoices[1] > 2);

                                    if(menuChoices[1] == 2) {
                                        int numColsNeeded = rowCopyLength - currentTable->numCols;
                                        printf("You need %d extra columns.\n", numColsNeeded);

                                        for(int i = 0; i < numColsNeeded; i++)
                                            insertCol(currentTable, rowCopy[currentTable->numCols].colName, rowCopy[currentTable->numCols].type, 0, NULL, NULL);
                                    }
                                }

                                nameList = malloc(sizeof(char*) * currentTable->numCols);

                                for(int i = 0; i < currentTable->numCols;i++) {
                                    nameList[i] = strdup(currentTable->cols[i].name);
                                }
                            }

                            if(proceed) {
                                if(currentTable->numRows > 0) {
                                    printf("Which row would you like to paste into? (1-%d): ", currentTable->numRows + 1);
                                    do {
                                        scanfWell("%d", &rowNum);
                                        if(rowNum < 1 || rowNum > currentTable->numRows + 1)
                                            printf("Please input a valid row number. (1-%d): ", currentTable->numRows + 1);
                                    } while(rowNum < 1 || rowNum > currentTable->numRows + 1);

                                    insertIntoRow(currentTable, currentTable->numCols, nameList, valueList, rowNum);
                                }
                                else
                                    insertRow(currentTable, currentTable->numCols, nameList, valueList);
                            }

                            else
                                printf("The current ordering of datatypes in your copied row does not match the ordering of datatypes in your current table.\nPasting not possible.\n");

                            if(valueList != NULL) {
                                for(int i = 0; i < currentTable->numCols; i++)
                                    free(valueList[i]);
                                free(valueList);
                            }
                            valueList = NULL;
                        }
                        else
                            printf("You currently do not have a row copied.\n");
                        break;
                    case 2:
                        // "2. PASTE column in current table"
                        if(colCopy.name != NULL) {
                            if(colCopyLength > currentTable->numRows) {
                                printf("How would you like to paste?:\n");
                                printf("1. Shrink column to fit table\n"
                                    "2. Grow table to fit column\n"
                                    "Your choice: ");

                                do {
                                    scanfWell("%d", &menuChoices[1]);
                                    if(menuChoices[1] < 1 || menuChoices[1] > 2)
                                        printf("Please choose between 1 and %d: ", 2);
                                } while(menuChoices[1] < 1 || menuChoices[1] > 2);

                                if(menuChoices[1] == 2) {
                                    int numRowsMissing = colCopyLength - currentTable->numRows;
                                    for(int i = 0; i < numRowsMissing; i++)
                                        insertRow(currentTable, 0, NULL, NULL);
                                }
                            }

                            numThings = min(currentTable->numRows, colCopyLength);

                            numList = malloc(sizeof(int) * numThings);
                            valueList = malloc(sizeof(void*) * numThings);

                            for(int i = 0; i < numThings; i++) {
                                numList[i] = i;
                                if(!colCopy.values[i].isNULL) {
                                    if(colCopy.type == INTEGER) {
                                        valueList[i] = malloc(sizeof(int));
                                        memcpy(valueList[i], &colCopy.values[i].val.INTEGER, sizeof(int));
                                    }
                                    else if(colCopy.type == DECIMAL) {
                                        valueList[i] = malloc(sizeof(double));
                                        memcpy(valueList[i], &colCopy.values[i].val.DECIMAL, sizeof(double));
                                    }
                                    else if(colCopy.type == CHAR) {
                                        valueList[i] = strdup(colCopy.values[i].val.CHAR);
                                    }
                                    else if(colCopy.type == BOOL) {
                                        valueList[i] = malloc(sizeof(int));
                                        memcpy(valueList[i], &colCopy.values[i].val.BOOL, sizeof(int));
                                    }
                                    else if(colCopy.type == DATE) {
                                        printf("DATE datatype functionality to be implemented soon.\n");
                                    }

                                }
                                else
                                    valueList[i] = NULL;

                            }

                            char colString[MAX_LEN];
                            int colPos;

                            printf("Which column position would you like to insert into? (A-%s): ", intToLetter(currentTable->numCols));
                            do {
                                fgetsUntil(colString, MAX_LEN);
                                colPos = letterToInt(colString) - 1;
                                if(colPos < 0 || colPos > currentTable->numCols)
                                    printf("Please input a valid column position. (A-%s): ", intToLetter(currentTable->numCols));
                            } while(colPos < 0 || colPos > currentTable->numCols);

                            insertIntoCol(currentTable, colCopy.name, colCopy.type, numThings, numList, valueList, colString);

                            if(valueList != NULL) {
                                for(int i = 0; i < numThings; i++)
                                    free(valueList[i]);
                                free(valueList);
                                free(numList);
                            }
                            valueList = NULL;
                            numList = NULL;

                        }
                        else
                            printf("You currently do not have a column copied.\n");
                        break;
                }

                break;
            case 13:
                //"13. DELETE"

                if(numTables <= 0) {
                    printf("There are no tables to choose from.\n");
                    break;
                }
                if(currentTable == NULL) {
                    if(menuChoices[1] == 1)
                        printf("Which table would you like to delete rows from?\n");
                    else if(menuChoices[1] == 2)
                        printf("Which table would you like to delete columns from?\n");
                    else if(menuChoices[1] == 3)
                        printf("Which table would you like to delete values from?\n");
                    else if(menuChoices[1] == 4)
                        printf("Which table would you like to delete?\n");
                    if(menuChoices[1] != 5) {
                        currTableIndex = tableMenu(numTables, tables);
                        currentTable = &tables[currTableIndex];
                        printf("Here is your current table:\n");
                        printTable(*currentTable);
                    }
                }

                switch(menuChoices[1]) {
                    case 1:
                        // "1. DELETE row(s) from current table"
                        if(currentTable->numRows > 0) {
                            int* rowNums = NULL;
                            int numRowsChosen = 0;
                            printf("How would you like to select the values to be updated?\n");
                            printf("1. Using column names and a where statement\n");
                            printf("2. Using the coordinate system (row numbers)\n");
                            printf("Choice: ");
                            do {
                                scanfWell("%d", &menuChoices[1]);
                                if(menuChoices[1] < 1 || menuChoices[1] > 2)
                                    printf("Please input either 1 or 2: ");
                            } while(menuChoices[1] < 1 || menuChoices[1] > 2);

                            if(menuChoices[1] == 1) {
                                numWheres = whereInput(currentTable, &whereList, &connectiveList);

                                if(verifyDelete())
                                    delete(currentTable, numWheres, whereList, connectiveList);
                            }
                            else if(menuChoices[1] == 2) {

                                numRowsChosen = rowNumInput(&rowNums, currentTable->numRows);

                                if(verifyDelete()) {
                                    for(int i = 0; i < numRowsChosen; i++) {
                                        deleteRow(currentTable, rowNums[i]);
                                        for(int j = i + 1; j < numRowsChosen; j++)
                                            if(rowNums[j] > rowNums[i])
                                                rowNums[j]--;
                                    }
                                }
                            }

                        }
                        else
                            printf("Your current table has no rows in it to delete.\n");
                        break;
                    case 2:
                        // "2. DELETE column(s) from current table"
                        if(currentTable->numCols > 0) {

                            printf("How would you like to select the values to be updated?\n");
                            printf("1. Using a column name\n");
                            printf("2. Using the coordinate system (column letters)\n");
                            printf("Choice: ");
                            do {
                                scanfWell("%d", &menuChoices[1]);
                                if(menuChoices[1] < 1 || menuChoices[1] > 2)
                                    printf("Please input either 1 or 2: ");
                            } while(menuChoices[1] < 1 || menuChoices[1] > 2);

                            if(menuChoices[1] == 1) {

                                printf("Please input the name of the column you would like to delete: ");

                                int colIndex;
                                do {
                                    fgetsUntil(colName, MAX_LEN);
                                    nameToCol(currentTable, colName, &colIndex);
                                    if(colIndex == -1)
                                        printf("Please try again: ");
                                } while(colIndex == -1);

                                if(verifyDelete())
                                    deleteColumn(currentTable, colName);

                            }
                            else if(menuChoices[1] == 2) {
                                int* colNums = NULL;
                                int numColsChosen = 0;

                                numColsChosen = colPosInput(&colNums, currentTable->numCols);

                                if(verifyDelete()) {
                                    for(int i = 0; i < numColsChosen; i++) {
                                        deleteColumn(currentTable, currentTable->cols[colNums[i]].name);
                                        for(int j = i + 1; j < numColsChosen; j++)
                                            if(colNums[j] > colNums[i])
                                                colNums[j]--;
                                    }
                                }
                            }

                        }
                        else
                            printf("Your current table has no columns in it to delete.\n");

                        break;
                    case 3:
                        // "3. DELETE value(s) from current table"
                        if(currentTable->numCols > 0 && currentTable->numRows > 0) {

                            printf("How would you like to select the values to be deleted?\n");
                            printf("1. Using column names and a where statement\n");
                            printf("2. Using the coordinate system (column letters and row numbers)\n");
                            printf("Choice: ");
                            do {
                                scanfWell("%d", &menuChoices[1]);
                                if(menuChoices[1] < 1 || menuChoices[1] > 2)
                                    printf("Please input either 1 or 2: ");
                            } while(menuChoices[1] < 1 || menuChoices[1] > 2);

                            if(menuChoices[1] == 1) {
                                int numDelCols = 0;
                                do {
                                    numDelCols++;
                                    printf("Please input the name of a column you would like to delete the value(s) of: ");
                                    if(numDelCols == 1) {
                                        nameList = malloc(sizeof(char*) * 1);
                                        valueList = malloc(sizeof(void*) * 1);
                                    }
                                    else {
                                        nameList = realloc(nameList, sizeof(char*) * numDelCols);
                                        valueList = realloc(valueList, sizeof(void*) * numDelCols);
                                    }

                                    nameList[numDelCols - 1] = malloc(sizeof(char) * MAX_LEN);

                                    int colIndex;
                                    do {
                                        fgetsUntil(nameList[numDelCols - 1], MAX_LEN);
                                        nameToCol(currentTable, nameList[numDelCols - 1], &colIndex);
                                        if(colIndex == -1)
                                            printf("Please try again: ");
                                    } while(colIndex == -1);

                                    nameList[numDelCols - 1] = realloc(nameList[numDelCols - 1], sizeof(char) * (strlen(nameList[numDelCols - 1]) + 1));
                                    valueList[numDelCols - 1] = NULL;

                                    if(numDelCols + 1 <= currentTable->numCols) {

                                        printf("Would you like to add another column to have its values deleted? (yes/no): ");
                                        do {
                                            fgetsUntil(yesno, MAX_LEN);
                                            if(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0)
                                                printf("Please input 'yes' or 'no': ");
                                        } while(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0);
                                    }
                                } while(strcmp(yesno, "yes") == 0 && numDelCols + 1 <= currentTable->numCols);

                                numWheres = whereInput(currentTable, &whereList, &connectiveList);

                                update(currentTable, numDelCols, nameList, valueList, numWheres, whereList, connectiveList);

                                for(int i = 0; i < numDelCols; i++) {
                                    free(nameList[i]);
                                    free(valueList[i]);
                                }
                                free(nameList);
                                free(valueList);
                                nameList = NULL;
                                valueList = NULL;
                            }
                            else {
                                int* colNums = NULL;
                                int numColsChosen = 0;

                                numColsChosen = colPosInput(&colNums, currentTable->numCols);

                                int* rowNums = NULL;
                                int numRowsChosen = 0;

                                numRowsChosen = rowNumInput(&rowNums, currentTable->numRows);

                                for(int i = 0; i < numColsChosen; i++) {
                                    for(int j = 0; j < numRowsChosen; j++) {
                                        currentTable->cols[colNums[i]].values[rowNums[j]].isNULL = 1;
                                        if(currentTable->cols[colNums[i]].type == CHAR)
                                            free(currentTable->cols[colNums[i]].values[rowNums[j]].val.CHAR);
                                    }
                                }

                                if(colNums != NULL)
                                    free(colNums);
                                if(rowNums != NULL)
                                    free(rowNums);

                            }
                        }
                        else
                            printf("Your current table has no values to delete.\n");
                        break;
                    case 4:
                        // "4. DELETE current table"
                        if(verifyDelete()) {

                            freeTable(currentTable);

                            numTables--;
                            for(int i = currTableIndex; i < numTables;i++)
                                tables[i] = tables[i + 1];

                            currTableIndex = -1;
                            currentTable = NULL;
                        }
                        break;
                    case 5:
                        // "5. DELETE database"
                        if(verifyDelete()) {
                            for(int i = 0; i < numTables; i++)
                                freeTable(&tables[i]);

                            free(tables);

                            tables = NULL;

                            numTables = 0;

                            currentTable = NULL;
                            currTableIndex = -1;
                        }
                        break;
                }
                break;
            case 14: {
                //"14. IMPORT"
                switch(menuChoices[1]) {
                    case 1: {
                        // "1. IMPORT table from file"
                        char tableName[MAX_LEN];
                        char filename[MAX_LEN];

                        //Perhaps change this to a numbered menu of all tables found in given file?
                        printf("Please input the name of the table you would like to import: ");
                        fgetsUntil(tableName, MAX_LEN);

                        printf("Please input the name of the file you want to import the table '%s' from.\n(can be of any extension, including .db and .sql): ", tableName);
                        fgetsUntil(filename, MAX_LEN);

                        if(!fopen(filename, "r")) {
                            do {
                                printf("File with name '%s' not found. Please input an existing file's name, or type 'cancel' if you would like to cancel this save: ", filename);
                                fgetsUntil(filename, MAX_LEN);
                            } while(strcmp(filename, "cancel") != 0 && !fopen(filename, "r"));
                        }

                        if(strcmp(filename, "cancel") != 0) {
                            Table* importedTable = importTable(tableName, filename);
                            if(importedTable) {
                                numTables++;
                                if(numTables == 1)
                                    tables = malloc(sizeof(Table));
                                else
                                    tables = realloc(tables, sizeof(Table) * numTables);
                                tables[numTables - 1] = *importedTable;
                                checkTableNames(tables, numTables, tables[numTables - 1].name, numTables - 1);
                                currentTable = &tables[numTables - 1];
                                currTableIndex = numTables - 1;
                            }
                        }
                        break;
                    }
                    case 2: {
                        // "2. IMPORT database from file"
                        char filename[MAX_LEN];
                        printf("Please input the name of the file you want to import the database from.\n(can be of any extension, including .db and .sql): ");
                        fgetsUntil(filename, MAX_LEN);

                        if(!fopen(filename, "r")) {
                            do {
                                printf("File with name '%s' not found. Please input an existing file's name, or type 'cancel' if you would like to cancel this save: ", filename);
                                fgetsUntil(filename, MAX_LEN);
                            } while(strcmp(filename, "cancel") != 0 && !fopen(filename, "r"));
                        }

                        if(strcmp(filename, "cancel") != 0) {
                            printf("Are you sure you want to overwrite the current database? (yes/no): ");
                            do {
                                fgetsUntil(yesno, MAX_LEN);
                                if(strcmp(yesno, "yes") != 0 && strcmp(yesno, "no") != 0)
                                    printf("Please input 'yes' or 'no': ");
                            } while(strcmp(yesno, "yes") != 0 && strcmp(yesno, "no") != 0);

                            if(strcmp(yesno, "yes") == 0) {
                                Table* newTables;
                                int numTablesLoaded = importDatabase(filename, &newTables);

                                if(numTablesLoaded > 0) {
                                    for(int i = 0; i < numTables; i++)
                                        freeTable(&tables[i]);
                                    if(tables != NULL)
                                        free(tables);
                                    currentTable = NULL;
                                    currTableIndex = -1;
                                    numTables = numTablesLoaded;
                                    tables = newTables;
                                }
                            }
                        }
                        break;
                    }
                }

                break;
            }
            case 15:
                //"15. EXPORT"
                if(numTables <= 0) {
                    printf("There are no tables to export.\n");
                    break;
                }

                switch(menuChoices[1]) {
                    case 1: {
                        // "1. EXPORT current table to file"
                        if(currentTable == NULL) {
                            printf("Which table would you like to export?\n");
                            currTableIndex = tableMenu(numTables, tables);
                            currentTable = &tables[currTableIndex];
                            printf("Here is your current table:\n");
                            printTable(*currentTable);
                        }

                        int saveChoice;
                        char filename[MAX_LEN];
                        int trunc;
                        do {
                            saveChoice = 1;
                            trunc = 0;

                            printf("Please input the name of the file you want to save '%s' to.\n(can be of any extension, including .db and .sql): ", currentTable->name);
                            fgetsUntil(filename, MAX_LEN);

                            if(fopen(filename, "r")) {

                                printf("\nHow would you like to save your data?\n");
                                printf("1. Save current table along with the other contents of the given file.\n"
                                    "2. Delete all records in the given file and save your current table afterwards.\n"
                                    "3. Give a new file name.\n"
                                    "4. Cancel the save.\n"
                                    "Choice: ");

                                do {
                                    scanfWell("%d", &saveChoice);
                                    if(saveChoice < 1 || saveChoice > 4)
                                        printf("Please input a number between 1 & 4: ");
                                } while(saveChoice < 1 || saveChoice > 4);

                                if(saveChoice == 2)
                                    trunc = 1;
                            }
                        } while(saveChoice == 3);

                        if(saveChoice != 4) {
                            exportTable(*currentTable, filename, trunc);
                            printf("\n'%s' saved successfully to %s.\n", currentTable->name, filename);
                        }
                        break;
                    }
                    case  2: {
                        // "2. EXPORT full database to file"
                        char filename[MAX_LEN];
                        int saveChoice;
                        do {
                            saveChoice = 1;

                            printf("Please input the name of the file you want to save the database to.\n(can be of any extension, including .db and .sql): ");
                            fgetsUntil(filename, MAX_LEN);

                            if(fopen(filename, "r")) {

                                printf("\nHow would you like to save your data?\n");
                                printf("1. Save database along with the other contents of the given file.\n"
                                    "2. Delete all records in the given file and save your database afterwards.\n"
                                    "3. Give a new file name.\n"
                                    "4. Cancel the save.\n"
                                    "Choice: ");

                                do {
                                    scanfWell("%d", &saveChoice);
                                    if(saveChoice < 1 || saveChoice > 4)
                                        printf("Please input a number between 1 & 4: ");
                                } while(saveChoice < 1 || saveChoice > 4);

                                if(saveChoice == 2)
                                    truncate(filename, 0);

                            }

                        } while(saveChoice == 3);


                        for(int i = 0; i < numTables; i++)
                            exportTable(tables[i], filename, 0);

                        printf("\nDatabase saved successfully to %s.\n", filename);
                        break;
                    }
                }


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
                        printf("Saving");
                        for(int i = 0; i < 3; i++) {
                            cql_sleep(750);
                            printf(".");
                            fflush(stdout);
                        }
                        cql_sleep(750);
                        printf("\nDatabase Saved.\n");
                        cql_sleep(250);
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
            "9. SORT\n"
            "10. JOIN\n"
            "11. COPY\n"
            "12. PASTE\n"
            "13. DELETE\n"
            "14. IMPORT\n"
            "15. EXPORT\n"
            "0. EXIT\n"
            "Your choice: ");
        do {
            scanfWell("%d", &menuChoices[0]);
            if(menuChoices[0] < 0 || menuChoices[0] > 15)
                printf("Please choose between 0 and 15: ");
        } while(menuChoices[0] < 0 || menuChoices[0] > 15);

        switch(menuChoices[0]) {
            case 1:
                printf("1. CREATE a table\n");
                numOptions = 1;
                break;

            case 2:
                printf("1. PRINT the Master Table\n"
                    "2. PRINT a table\n"
                    "3. PRINT copied row\n"
                    "4. PRINT copied column\n");
                numOptions = 4;
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
                printf("1. UPDATE existing values in current table\n"
                    "2. UPDATE attributes of column in current table\n");
                numOptions = 2;
                break;

            case 8:
                printf("1. MOVE a row to new position in current table\n"
                    "2. MOVE a column to new position in current table\n");
                numOptions = 2;
                break;

            case 9:
                printf("1. SORT rows by the values of a column\n");
                numOptions = 1;
                break;

            case 10:
                printf("1. CROSS JOIN\n"
                    "2. INNER JOIN\n"
                    "3. OUTER JOIN\n"
                    "4. SELF JOIN\n");
                numOptions = 4;
                break;

            case 11:
                printf("1. COPY row in current table\n"
                    "2. COPY column in current table\n"
                    "3. Make a COPY of current table\n");
                numOptions = 3;
                break;

            case 12:
                printf("1. PASTE row into current table\n"
                    "2. PASTE column into current table\n");
                numOptions = 2;
                break;

            case 13:
                printf("1. DELETE row(s) from current table\n"
                    "2. DELETE column(s) from current table\n"
                    "3. DELETE value(s) from current table\n"
                    "4. DELETE current table\n"
                    "5. DELETE database\n");
                numOptions = 5;
                break;

            case 14:
                printf("1. IMPORT table from file\n"
                    "2. IMPORT database from file\n");
                numOptions = 2;
                break;

            case 15:
                printf("1. EXPORT current table to file\n"
                    "2. EXPORT full database to file\n");
                numOptions = 2;
                break;

            case 0:
                printf("1. SAVE & EXIT\n"
                    "2. EXIT WITHOUT SAVING\n");
                numOptions = 2;
                break;

        }
        printf("0. Back\n"
            "Your choice: ");
        do {
            scanfWell("%d", &menuChoices[1]);
            if(menuChoices[1] < 0 || menuChoices[1] > numOptions)
                printf("Please choose between 0 and %d: ", numOptions);
        } while(menuChoices[1] < 0 || menuChoices[1] > numOptions);
    } while(menuChoices[1] == 0);

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
            printf("Please input the integer value you are looking for (NULL = 0): ");
            (*whereList)[numWheres - 1].searchValue = malloc(sizeof(int));
            scanfWell("%d", (*whereList)[numWheres - 1].searchValue);
        }
        else if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName, NULL).type == CHAR) {
            printf("Please input the string value you are looking for: ");
            (*whereList)[numWheres - 1].searchValue = malloc(sizeof(char) * MAX_LEN);
            fgetsUntil((*whereList)[numWheres - 1].searchValue, MAX_LEN);
            (*whereList)[numWheres - 1].searchValue = realloc((*whereList)[numWheres - 1].searchValue, sizeof(char) * (strlen((*whereList)[numWheres - 1].searchValue) + 1));
        }
        else if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName, NULL).type == DECIMAL) {
            printf("Please input the decimal value you are looking for (NULL = 0): ");
            (*whereList)[numWheres - 1].searchValue = malloc(sizeof(double));
            scanfWell("%lf", (*whereList)[numWheres - 1].searchValue);
        }
        else if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName, NULL).type == BOOL) {
            printf("Please input the boolean value you are looking for: ");

            char temp[MAX_LEN];
            do {
                fgetsUntil(temp, MAX_LEN);
                if(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0 && strcmp(temp, "NULL") != 0)
                    printf("Please input 'TRUE' or 'FALSE': ");
            } while(strcmp(temp, "TRUE") != 0 && strcmp(temp, "FALSE") != 0 && strcmp(temp, "NULL") != 0);

            (*whereList)[numWheres - 1].searchValue = malloc(sizeof(double));

            if(strcmp(temp, "TRUE") == 0)
                sscanf("1", "%d", (int*)(*whereList)[numWheres - 1].searchValue);
            else if(strcmp(temp, "FALSE") == 0)
                sscanf("0", "%d", (int*)(*whereList)[numWheres - 1].searchValue);
            else if(strcmp(temp, "NULL") == 0)
                sscanf("-1", "%d", (int*)(*whereList)[numWheres - 1].searchValue);
        }

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
        "  4. DATE\n"
        "  5. BOOL (Boolean)\n");
    printf("Type for column: ");
    do {
        scanfWell("%d", &choice);
        choice--;
        if(choice < 0 || choice > 4)
            printf("Please input a valid type (1-5): ");
    } while(choice < 0 || choice > 4);

    return choice;

}

int colPosInput(int** colNums, int numCols) {

    int colPosI, colPosF, numColsChosen = 0;
    char* input = malloc(sizeof(char) * MAX_LEN);
    char* token;
    char* temp;
    char* colString = malloc(sizeof(char) * MAX_LEN);

    printf("Please input the column letter(s) you would like to choose\n(Eg. 'A' | 'A-E' | 'A, B, D'): ");

    do {
        colPosI = 0;
        colPosF = 1;
        fgetsUntil(input, MAX_LEN);
        token = strtok(input, ", \n");
        while(token != NULL) {
            temp = strstr(token, "-");
            if(temp != NULL) {

                strncpy(colString, token, temp - token);
                colString[++temp - token] = '\0';
                colPosI = letterToInt(colString);
                colPosF = letterToInt(temp);
                if(colPosI < 0 || colPosF > numCols || colPosF <= colPosI) {
                    printf("Invalid input. Please try again: ");
                    break;
                }
                if(numColsChosen == 0)
                    *colNums = malloc(sizeof(int) * (colPosF - colPosI));
                else
                    *colNums = realloc(*colNums, sizeof(int) * (numColsChosen + colPosF - colPosI));
                for(int i = colPosI - 1; i < colPosF; i++)
                    (*colNums)[numColsChosen++] = i;

            }
            else {
                if(numColsChosen == 0)
                    *colNums = malloc(sizeof(int));
                else
                    *colNums = realloc(*colNums, sizeof(int) * (numColsChosen + 1));

                (*colNums)[numColsChosen++] = letterToInt(token) - 1;
            }
            token = strtok(NULL, ", \n");
        }

    } while(colPosI < 0 || colPosF > numCols || colPosF <= colPosI);

    free(input);
    free(colString);

    return numColsChosen;
}

int rowNumInput(int** rowNums, int numRows) {

    int rowNumI, rowNumF, numRowsChosen = 0;
    char* input = malloc(sizeof(char) * MAX_LEN);
    char* token;
    char* temp;
    char* rowString = malloc(sizeof(char) * MAX_LEN);

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
                rowString[++temp - token] = '\0';
                rowNumI = atoi(rowString);
                rowNumF = atoi(temp);
                if(rowNumI < 0 || rowNumF > numRows || rowNumF <= rowNumI) {
                    printf("Invalid input. Please try again: ");
                    break;
                }
                if(numRowsChosen == 0)
                    *rowNums = malloc(sizeof(int) * (rowNumF - rowNumI));
                else
                    *rowNums = realloc(*rowNums, sizeof(int) * (numRowsChosen + rowNumF - rowNumI));
                for(int i = rowNumI - 1; i < rowNumF; i++)
                    (*rowNums)[numRowsChosen++] = i;

            }
            else {
                if(numRowsChosen == 0)
                    *rowNums = malloc(sizeof(int));
                else
                    *rowNums = realloc(*rowNums, sizeof(int) * (numRowsChosen + 1));

                (*rowNums)[numRowsChosen++] = atoi(token) - 1;
            }
            token = strtok(NULL, ", \n");
        }

    } while(rowNumI < 0 || rowNumF > numRows || rowNumF <= rowNumI);

    free(input);
    free(rowString);

    return numRowsChosen;
}

void printType(int type) {
    if(type == CHAR)
        printf("CHAR");
    else if(type == INTEGER)
        printf("INTEGER");
    else if(type == DECIMAL)
        printf("DECIMAL");
    else if(type == BOOL)
        printf("BOOL");
    else if(type == DATE)
        printf("DATE");
    else
        printf("UNKOWN TYPE");
}

char* typeToString(int type) {
    if(type == CHAR)
        return "CHAR";
    else if(type == INTEGER)
        return "INTEGER";
    else if(type == DECIMAL)
        return "DECIMAL";
    else if(type == BOOL)
        return "BOOL";
    else if(type == DATE)
        return "DATE";
    else if(type == -1)
        return "NULL";
    else
        return "UNKOWN TYPE";
}

int stringToType(char* type) {
    char* charTypes = "CHARACTER VARCHAR VARYING CHARACTER NCHAR NATIVE CHARACTER NVARCHAR TEXT CLOB";
    char* intTypes = "INT INTEGER TINYINT SMALLINT MEDIUMINT BIGINT UNSIGNED BIG INT INT2 INT8";
    char* decimalTypes = "REAL DOUBLE DOUBLE PRECISION FLOAT NUMERIC DECIMAL";
    char* boolTypes = "BOOLEAN BOOL BIT";
    char* dateTypes = "DATE DATETIME";

    for(int i = 0; i < strlen(type); i++)
        type[i] = toupper(type[i]);

    if(strstr(charTypes, type))
        return CHAR;
    else if(strstr(intTypes, type))
        return INTEGER;
    else if(strstr(decimalTypes, type))
        return DECIMAL;
    else if(strstr(boolTypes, type))
        return BOOL;
    else if(strstr(dateTypes, type))
        return DATE;
    else if(strcmp(type, "NULL") == 0)
        return -1;
    else
        return -2;
}

int verifyDelete(void) {

    printf("Are you sure you wish do delete this data? (yes/no): ");
    char yesno[MAX_LEN];
    do {
        fgetsUntil(yesno, MAX_LEN);
        if(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0)
            printf("Please input 'yes' or 'no': ");
    } while(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0);

    return strcmp(yesno, "yes") == 0;

}

void checkTableNames(Table* tables, int numTables, char* nameToCheck, int newNameIndex) {
    int numDupes = 0;
    char* nameSuffix;

    for(int i = 0; i < numTables; i++) {
        if(strcmp(nameToCheck, tables[i].name) == 0 && i != newNameIndex) {
            printf("DUPE FOUND\n");
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

void cql_sleep(int milliseconds) {
    struct timespec ts;

    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;

    nanosleep(&ts, &ts);
}

// remember SQLITE3 terminal command can also read .sql files.
// sqlite3_exec(sqlite3_open(demo.sql), "CREATE TABLE Mario", NULL, NULL, "Error: SQL Execution Failed");
