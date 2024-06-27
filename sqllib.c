#include "sqllib.h"

int main(int argc, char const* argv[]) {

    Table* tables = malloc(sizeof(Table) * 2);

    printTable(tables[0]);
    char** names = nameList(3, "Char Col", "Decimal Col", "Integer Col");
    int* types = typeList(3, CHAR, DECIMAL, INTEGER);
    tables[0] = create("My Table", 3, names, types, NULL, NULL, NULL);
    freeList(names, 3);
    free(types);

    names = nameList(2, "Decimal Col", "Char Col");
    types = typeList(2, DECIMAL, CHAR);
    void** values = valueList(2, types, 44.55, "Luigi");
    insertRow(&tables[0], 2, names, values);
    freeList(names, 2);
    free(types);
    freeList(values, 2);

    printTable(tables[0]);

    names = nameList(1, "Char Col");
    types = typeList(1, CHAR);
    values = valueList(1, types, "Mario");
    insertRow(&tables[0], 1, names, values);
    printTable(tables[0]);
    freeList(names, 1);
    free(types);
    freeList(values, 1);

    names = nameList(1, "Integer Col");
    types = typeList(1, INTEGER);
    values = valueList(1, types, 4);
    insertRow(&tables[0], 1, names, values);
    freeList(names, 1);
    free(types);
    freeList(values, 1);

    names = nameList(3, "Integer Col", "Decimal Col", "Char Col");
    types = typeList(3, INTEGER, DECIMAL, CHAR);
    values = valueList(3, types, 44, 88.77, "WAHHLUIGI");
    insertRow(&tables[0], 3, names, values);
    freeList(names, 3);
    free(types);
    freeList(values, 3);
    printTable(tables[0]);

    Where where1 = newWhere("Char Col", "==", "Luigi");
    double newNum = 9999.999;

    names = nameList(1, "Decimal Col");
    types = typeList(1, DECIMAL);
    values = valueList(1, types, 9999.999);
    Where* wheres = whereList(1, where1);
    update(&tables[0], 1, names, values, 1, wheres, NULL);
    freeList(names, 1);
    free(types);
    freeList(values, 1);
    free(wheres);
    printTable(tables[0]);

    newNum = 0;
    Where where2 = newWhere("Decimal Col", "==", &newNum);

    int newInt = 1735;

    names = nameList(2, "Integer Col", "Decimal Col");
    types = typeList(2, INTEGER, DECIMAL);
    values = valueList(2, types, 1738, 22.5);
    wheres = whereList(2, where1, where2);
    char* conns = connectiveList(1, '|');
    update(&tables[0], 2, names, values, 2, wheres, conns);
    freeList(names, 2);
    free(types);
    freeList(values, 2);
    free(wheres);
    free(conns);
    printTable(tables[0]);

    Where where3 = newWhere("Char Col", "==", "NULL");

    names = nameList(1, "Char Col");
    types = typeList(1, CHAR);
    values = valueList(1, types, "WAAAAARIOOOOOOO");
    wheres = whereList(1, where3);
    update(&tables[0], 1, names, values, 1, wheres, NULL);
    freeList(names, 1);
    free(types);
    freeList(values, 1);
    free(wheres);
    printTable(tables[0]);

    names = nameList(1, "Decimal Col");
    types = typeList(1, DECIMAL);
    values = valueList(1, types, 444.0);
    insertRow(&tables[0], 1, names, values);
    freeList(names, 1);
    free(types);
    freeList(values, 1);

    printTable(tables[0]);
    newInt = 666;

    names = nameList(1, "Integer Col");
    types = typeList(1, INTEGER);
    values = valueList(1, types, newInt);
    wheres = whereList(3, where3, where2, where1);
    conns = connectiveList(2, '&', '|');
    update(&tables[0], 1, names, values, 3, wheres, conns);
    freeList(names, 1);
    free(types);
    freeList(values, 1);
    free(wheres);
    free(conns);
    printTable(tables[0]);

    names = nameList(1, "Char Col");
    types = typeList(1, CHAR);
    values = valueList(1, types, "WAAAAAAAAAAAAAAARIOOOOOO");
    Where where4 = newWhere("Integer Col", "==", &newInt);
    wheres = whereList(2, where3, where4);
    conns = connectiveList(1, '&');

    update(&tables[0], 1, names, values, 2, wheres, conns);
    freeList(names, 1);
    free(types);
    freeList(values, 1);
    free(wheres);
    free(conns);

    printTable(tables[0]);

    names = nameList(1, "Char Col");
    types = typeList(1, CHAR);
    values = valueList(1, types, "Princess Peach");
    wheres = whereList(1, where3);

    update(&tables[0], 1, names, values, 1, wheres, NULL);
    freeList(names, 1);
    free(types);
    freeList(values, 1);
    free(wheres);

    printTable(tables[0]);

    double dec = 444.0;

    Where where5 = newWhere("Char Col", "==", "WAAAAAAAAAAAAAAARIOOOOOO");
    Where where6 = newWhere("Decimal Col", ">", &dec);
    Where where7 = newWhere("Decimal Col", "==", &dec);
    Where where8 = newWhere("Integer Col", "==", &newNum);
    where1.comparison = "!=";
    wheres = whereList(7, where5, where3, where6, where4, where1, where7, where8);
    conns = connectiveList(6, '|', '&', '|', '|', '&', '&');
    delete(&tables[0], 7, wheres, conns);
    free(wheres);
    free(conns);

    printTable(tables[0]);

    where3.comparison = "!=";
    wheres = whereList(2, where5, where3);
    conns = connectiveList(1, '&');
    delete(&tables[0], 2, wheres, conns);
    free(wheres);
    free(conns);
    printTable(tables[0]);

    printf("\n\n\n");
    where3.searchValue = "Mario";
    where3.comparison = "==";

    names = nameList(2, "Decimal Col", "Char Col");
    Select select1 = newSelect(2, names, 0);
    freeList(names, 1);

    wheres = whereList(2, where5, where3);
    conns = connectiveList(1, '|');
    tables[1] = cql_select(tables[0], select1, 2, wheres, conns);
    free(wheres);
    free(conns);

    names = nameList(1, "Char Col");
    Select select2 = newSelect(1, names, 0);
    freeList(names, 1);
    Where where9 = newWhere("Char Col", "=", "WAHHLUIGI");

    wheres = whereList(2, where3, where9);
    conns = connectiveList(1, '|');
    tables[1] = cql_select(tables[0], select2, 2, wheres, conns);
    free(wheres);
    free(conns);

    names = nameList(3, "Char Col", "Integer Col", "Decimal Col");
    types = typeList(3, CHAR, INTEGER, DECIMAL);
    values = valueList(3, types, "Princess Peach", 777, 19.64);
    insertIntoRow(tables, 3, names, values, 3);
    freeList(names, 3);
    free(types);
    freeList(values, 3);

    int* rows = typeList(4, 0, 1, 2, 3);
    types = typeList(4, BOOL, BOOL, BOOL, BOOL);
    values = valueList(4, types, 1, 0, 0, 1);
    insertCol(&tables[0], "Bool Col", BOOL, 4, rows, values, NULL, NULL, NULL);
    free(rows);
    free(types);
    freeList(values, 4);

    int numTables = userTableOperator(2, &tables);

    freeDatabase(tables, numTables);

    return 0;
}

/**
 * Creates a table with provided number of columns, column names, datatypes, and attributes. The parameter lists pertain to the ordering of the column name list. I.e. datatype 2 is applied to column 2.
 * @param tableName - The name of the table you are creating.
 * @param numCols - The number of columns in the new table.
 * @param colNames - A list of the names of the columns of the new table.
 * @param colTypes - A list of the datatypes of the columns of the new table.
 * @param colAttrs - A list of the attributes of the columns of the new table. Can have NULL values if not needed.
 * @param defaultValues - A list of default values of the columns of the new table. Can have NULL values if not needed.
 * @param foreignKeyNames - A list of foreignKeyNames of the columns of the new table. Can have NULL values if not needed.
 * @return - The newly created table.
**/
Table create(char* tableName, int numCols, char** colNames, int* colTypes, char** colAttrs, void** defaultValues, char** foreignKeyNames) {

    Table table;

    if(!checkInvalidName(tableName)) {
        printf("INVALID TABLE NAME\n");
        return table;
    }
    printf("%s\n", *colNames);

    table.name = strdup(tableName);
    table.numCols = numCols;
    table.numRows = 0;

    if(numCols > 0)
        table.cols = malloc(sizeof(Column) * numCols);

    //Creating the columns
    for(int i = 0; i < numCols; i++) {
        if(!checkInvalidName(colNames[i]))
            continue;
        table.cols[i].name = strdup(colNames[i]);
        table.cols[i].type = colTypes[i];
        table.cols[i].numRows = 0;
        initColAttrs(&table.cols[i]);
        if(colAttrs && colAttrs[i]) {
            if(defaultValues && foreignKeyNames)
                assignColAttrs(&table.cols[i], colAttrs[i], defaultValues[i], foreignKeyNames[i]);
            else if(defaultValues)
                assignColAttrs(&table.cols[i], colAttrs[i], defaultValues[i], NULL);
            else if(foreignKeyNames)
                assignColAttrs(&table.cols[i], colAttrs[i], NULL, foreignKeyNames[i]);
            else
                assignColAttrs(&table.cols[i], colAttrs[i], NULL, NULL);
        }
    }

    return table;
}

/**
 * Inserts a new row at the bottom of a table.
 * @param table - The table to have the row added to.
 * @param numValues - The number of values that will be provided for the inserted row.
 * @param colNames - The list of column names that the provided values will be for.
 * @param values - The list of values to initialize the new row with.
**/
void insertRow(Table* table, int numValues, char** colNames, void** values) {

    if(numValues > table->numCols) {
        printf("Error: To many arguments provided. Insertion failed.\n");
        return;
    }

    table->numRows++;
    char* colName = "";
    Column currCol;

    //The initial row insertion, setting the new row to have NULL values
    for(int i = 0; i < table->numCols; i++) {
        table->cols[i].numRows++;
        if(table->numRows == 1)
            table->cols[i].values = malloc(sizeof(Value) * table->numRows);
        else
            table->cols[i].values = realloc(table->cols[i].values, sizeof(Value) * table->numRows);

        if(!table->cols[i].notNull && !table->cols[i].autoIncrement)
            table->cols[i].values[table->numRows - 1].isNULL = 1;
        //Default value/Auto increment value applied here
        else {
            table->cols[i].values[table->numRows - 1].isNULL = 0;
            if(table->cols[i].type == CHAR) {
                table->cols[i].values[table->numRows - 1].val.CHAR = strdup(table->cols[i].defaultValue.val.CHAR);
                if(table->cols[i].autoIncrement)
                    table->cols[i].defaultValue.val.CHAR = intToLetter(letterToInt(table->cols[i].defaultValue.val.CHAR) + 1);
            }
            else if(table->cols[i].type == INTEGER) {
                table->cols[i].values[table->numRows - 1].val.INTEGER = table->cols[i].defaultValue.val.INTEGER;
                if(table->cols[i].autoIncrement)
                    table->cols[i].defaultValue.val.INTEGER++;
            }
            else if(table->cols[i].type == DECIMAL) {
                table->cols[i].values[table->numRows - 1].val.DECIMAL = table->cols[i].defaultValue.val.DECIMAL;
                if(table->cols[i].autoIncrement)
                    table->cols[i].defaultValue.val.DECIMAL += 0.1;
            }
            else if(table->cols[i].type == BOOL)
                table->cols[i].values[table->numRows - 1].val.BOOL = table->cols[i].defaultValue.val.BOOL;
            else if(table->cols[i].type == DATE)
                printf("DATE datatype functionality coming soon.\n");
        }
    }

    //Applying provided specified values
    for(int i = 0; i < numValues; i++) {
        colName = strdup(colNames[i]);
        currCol = nameToCol(table, colName, NULL);

        if(values[i] != NULL) {
            currCol.values[table->numRows - 1].isNULL = 0;
            if(currCol.type == CHAR) {
                currCol.values[table->numRows - 1].val.CHAR = strdup((char*)values[i]);

                //Checking for duplicate values
                if(currCol.isPrimaryKey) {
                    for(int j = 0; j < table->numRows - 1; j++) {
                        if(!currCol.values[j].isNULL && strcmp(currCol.values[j].val.CHAR, currCol.values[table->numRows - 1].val.CHAR) == 0) {
                            printf("Value in column %s, '%s' is already taken.\n", currCol.name, currCol.values[table->numRows - 1].val.CHAR);
                            free(currCol.values[table->numRows - 1].val.CHAR);
                            values[i] = NULL;
                            i--;
                            break;
                        }
                    }
                }

                //Foreign key validation
                if(values[i] != NULL && currCol.hasForeignKey && currCol.fKeyPointer && currCol.fKeyIndex >= 0) {
                    int valid = 0;
                    for(int j = 0; j < (*currCol.fKeyPointer)[currCol.fKeyIndex].numRows; j++) {
                        if(!(*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].isNULL && strcmp((*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].val.CHAR, currCol.values[table->numRows - 1].val.CHAR) == 0) {
                            valid = 1;
                            break;
                        }
                    }
                    if(!valid) {
                        printf("Value '%s' does not exist in foreign key '%s'.\n", currCol.values[table->numRows - 1].val.CHAR, currCol.fKeyName);
                        free(currCol.values[table->numRows - 1].val.CHAR);
                        values[i] = NULL;
                        i--;
                    }
                }

            }
            else if(currCol.type == INTEGER) {
                currCol.values[table->numRows - 1].val.INTEGER = *(int*)values[i];
                //Checking for duplicate values
                if(currCol.isPrimaryKey) {
                    for(int j = 0; j < table->numRows - 1; j++) {
                        if(!currCol.values[j].isNULL && currCol.values[j].val.INTEGER == currCol.values[table->numRows - 1].val.INTEGER) {
                            printf("Value in column %s, '%d' is already taken.\n", currCol.name, currCol.values[table->numRows - 1].val.INTEGER);
                            values[i] = NULL;
                            i--;
                        }
                    }
                }

                //Foreign key validation
                if(values[i] != NULL && currCol.hasForeignKey && currCol.fKeyPointer && currCol.fKeyIndex >= 0) {
                    int valid = 0;
                    for(int j = 0; j < (*currCol.fKeyPointer)[currCol.fKeyIndex].numRows; j++) {
                        if(!(*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].isNULL && (*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].val.INTEGER == currCol.values[table->numRows - 1].val.INTEGER) {
                            valid = 1;
                            break;
                        }
                    }
                    if(!valid) {
                        printf("Value '%d' does not exist in foreign key '%s'.\n", currCol.values[table->numRows - 1].val.INTEGER, currCol.fKeyName);
                        values[i] = NULL;
                        i--;
                    }
                }

            }
            else if(currCol.type == DECIMAL) {
                currCol.values[table->numRows - 1].val.DECIMAL = *(double*)values[i];

                //Checking for duplicate values
                if(currCol.isPrimaryKey) {
                    for(int j = 0; j < table->numRows - 1; j++) {
                        if(!currCol.values[j].isNULL && currCol.values[j].val.DECIMAL == currCol.values[table->numRows - 1].val.DECIMAL) {
                            printf("Value in column %s, '%lf' is already taken.\n", currCol.name, currCol.values[table->numRows - 1].val.DECIMAL);
                            values[i] = NULL;
                            i--;
                        }
                    }
                }

                //Foreign key validation
                if(values[i] != NULL && currCol.hasForeignKey && currCol.fKeyPointer && currCol.fKeyIndex >= 0) {
                    int valid = 0;
                    for(int j = 0; j < (*currCol.fKeyPointer)[currCol.fKeyIndex].numRows; j++) {
                        if(!(*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].isNULL && (*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].val.DECIMAL == currCol.values[table->numRows - 1].val.DECIMAL) {
                            valid = 1;
                            break;
                        }
                    }
                    if(!valid) {
                        printf("Value '%lf' does not exist in foreign key '%s'.\n", currCol.values[table->numRows - 1].val.DECIMAL, currCol.fKeyName);
                        values[i] = NULL;
                        i--;
                    }
                }

            }
            else if(currCol.type == BOOL) {
                currCol.values[table->numRows - 1].val.BOOL = *(int*)values[i];

                //Checking for duplicate values
                if(currCol.isPrimaryKey) {
                    for(int j = 0; j < table->numRows - 1; j++) {
                        if(!currCol.values[j].isNULL && currCol.values[j].val.BOOL == currCol.values[table->numRows - 1].val.BOOL) {
                            printf("Value in column %s, '%d' is already taken.\n", currCol.name, currCol.values[table->numRows - 1].val.BOOL);
                            values[i] = NULL;
                            i--;
                        }
                    }
                }

                //Foreign key validation
                if(values[i] != NULL && currCol.hasForeignKey && currCol.fKeyPointer && currCol.fKeyIndex >= 0) {
                    int valid = 0;
                    for(int j = 0; j < (*currCol.fKeyPointer)[currCol.fKeyIndex].numRows; j++) {
                        if(!(*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].isNULL && (*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].val.BOOL == currCol.values[table->numRows - 1].val.BOOL) {
                            valid = 1;
                            break;
                        }
                    }
                    if(!valid) {
                        printf("Value '%d' does not exist in foreign key '%s'.\n", currCol.values[table->numRows - 1].val.BOOL, currCol.fKeyName);
                        values[i] = NULL;
                        i--;
                    }
                }

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

/**
 * Inserts a new row in the provided row position.
 * @param table - The table to have the row added to.
 * @param numValues - The number of values that will be provided for the inserted row.
 * @param colNames - The list of column names that the provided values will be for.
 * @param values - The list of values to initialize the new row with.
 * @param rowNum - The numerical row position that the new row will be inserted into. (1 indexed)
**/
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

    //The initial row insertion, setting the new row to have NULL values
    for(int i = 0; i < table->numCols; i++) {
        table->cols[i].numRows++;
        table->cols[i].values = realloc(table->cols[i].values, sizeof(Value) * table->numRows);

        //Shifting rows over for the new one
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
        if(!table->cols[i].notNull && !table->cols[i].autoIncrement)
            table->cols[i].values[rowNum].isNULL = 1;
        //Default value/Auto increment value applied here
        else {
            table->cols[i].values[rowNum].isNULL = 0;
            if(table->cols[i].type == CHAR) {
                table->cols[i].values[rowNum].val.CHAR = strdup(table->cols[i].defaultValue.val.CHAR);
                if(table->cols[i].autoIncrement) {
                    // printf("YEET %s -> %d -> %s\n", table->cols[i].defaultValue.val.CHAR, letterToInt(table->cols[i].defaultValue.val.CHAR) + 1, intToLetter(letterToInt(table->cols[i].defaultValue.val.CHAR) + 1));
                    table->cols[i].defaultValue.val.CHAR = intToLetter(letterToInt(table->cols[i].defaultValue.val.CHAR) + 1);
                }
            }
            else if(table->cols[i].type == INTEGER) {
                table->cols[i].values[rowNum].val.INTEGER = table->cols[i].defaultValue.val.INTEGER;
                if(table->cols[i].autoIncrement)
                    table->cols[i].defaultValue.val.INTEGER++;
            }
            else if(table->cols[i].type == DECIMAL) {
                table->cols[i].values[rowNum].val.DECIMAL = table->cols[i].defaultValue.val.DECIMAL;
                if(table->cols[i].autoIncrement)
                    table->cols[i].defaultValue.val.DECIMAL += 0.1;
            }
            else if(table->cols[i].type == BOOL)
                table->cols[i].values[rowNum].val.BOOL = table->cols[i].defaultValue.val.BOOL;
            else if(table->cols[i].type == DATE)
                printf("DATE datatype functionality coming soon.\n");
        }
    }

    //Applying provided specified values
    for(int i = 0; i < numValues; i++) {
        colName = strdup(colNames[i]);
        currCol = nameToCol(table, colName, NULL);
        if(values[i] == NULL) {
            if(!currCol.notNull && !currCol.autoIncrement)
                currCol.values[rowNum].isNULL = 1;
            else {
                currCol.values[rowNum].isNULL = 0;
                if(currCol.type == CHAR) {
                    currCol.values[rowNum].val.CHAR = strdup(currCol.defaultValue.val.CHAR);
                    if(currCol.autoIncrement)
                        strcpy(currCol.defaultValue.val.CHAR, intToLetter(letterToInt(currCol.defaultValue.val.CHAR) + 1));
                }
                else if(currCol.type == INTEGER) {
                    currCol.values[rowNum].val.INTEGER = currCol.defaultValue.val.INTEGER;
                    if(currCol.autoIncrement)
                        currCol.defaultValue.val.INTEGER++;
                }
                else if(currCol.type == DECIMAL) {
                    currCol.values[rowNum].val.DECIMAL = currCol.defaultValue.val.DECIMAL;
                    if(currCol.autoIncrement)
                        currCol.defaultValue.val.DECIMAL += 0.1;
                }
                else if(currCol.type == BOOL)
                    currCol.values[rowNum].val.BOOL = currCol.defaultValue.val.BOOL;
                else if(currCol.type == DATE)
                    printf("DATE datatype functionality coming soon.\n");

            }
        }
        else {
            currCol.values[rowNum].isNULL = 0;
            if(currCol.type == CHAR) {
                currCol.values[rowNum].val.CHAR = strdup((char*)values[i]);

                //Checking for duplicate values
                if(currCol.isPrimaryKey) {
                    for(int j = 0; j < table->numRows; j++) {
                        if(j != rowNum && !currCol.values[j].isNULL && strcmp(currCol.values[j].val.CHAR, currCol.values[rowNum].val.CHAR) == 0) {
                            printf("Value in column %s, '%s' is already taken.\n", currCol.name, currCol.values[rowNum].val.CHAR);
                            free(currCol.values[rowNum].val.CHAR);
                            values[i] = NULL;
                            i--;
                        }
                    }
                }

                //Foreign key validation
                if(values[i] != NULL && currCol.hasForeignKey) {
                    int valid = 0;
                    for(int j = 0; j < (*currCol.fKeyPointer)[currCol.fKeyIndex].numRows; j++) {
                        if(!(*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].isNULL && strcmp((*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].val.CHAR, currCol.values[rowNum].val.CHAR) == 0) {
                            valid = 1;
                            break;
                        }
                    }
                    if(!valid) {
                        printf("Value '%s' does not exist in foreign key '%s'.\n", currCol.values[rowNum].val.CHAR, currCol.fKeyName);
                        free(currCol.values[rowNum].val.CHAR);
                        values[i] = NULL;
                        i--;
                    }
                }

            }
            else if(currCol.type == INTEGER) {
                currCol.values[rowNum].val.INTEGER = *(int*)values[i];

                //Checking for duplicate values
                if(currCol.isPrimaryKey) {
                    for(int j = 0; j < table->numRows; j++) {
                        if(j != rowNum && !currCol.values[j].isNULL && currCol.values[j].val.INTEGER == currCol.values[rowNum].val.INTEGER) {
                            printf("Value in column %s, '%d' is already taken.\n", currCol.name, currCol.values[rowNum].val.INTEGER);
                            values[i] = NULL;
                            i--;
                        }
                    }
                }

                //Foreign key validation
                if(values[i] != NULL && currCol.hasForeignKey) {
                    int valid = 0;
                    for(int j = 0; j < (*currCol.fKeyPointer)[currCol.fKeyIndex].numRows; j++) {
                        if(!(*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].isNULL && (*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].val.INTEGER == currCol.values[rowNum].val.INTEGER) {
                            valid = 1;
                            break;
                        }
                    }
                    if(!valid) {
                        printf("Value '%d' does not exist in foreign key '%s'.\n", currCol.values[rowNum].val.INTEGER, currCol.fKeyName);
                        values[i] = NULL;
                        i--;
                    }
                }

            }
            else if(currCol.type == DECIMAL) {
                currCol.values[rowNum].val.DECIMAL = *(double*)values[i];

                //Checking for duplicate values
                if(currCol.isPrimaryKey) {
                    for(int j = 0; j < table->numRows; j++) {
                        if(j != rowNum && !currCol.values[j].isNULL && currCol.values[j].val.DECIMAL == currCol.values[rowNum].val.DECIMAL) {
                            printf("Value in column %s, '%lf' is already taken.\n", currCol.name, currCol.values[rowNum].val.DECIMAL);
                            values[i] = NULL;
                            i--;
                        }
                    }
                }

                //Foreign key validation
                if(values[i] != NULL && currCol.hasForeignKey) {
                    int valid = 0;
                    for(int j = 0; j < (*currCol.fKeyPointer)[currCol.fKeyIndex].numRows; j++) {
                        if(!(*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].isNULL && (*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].val.DECIMAL == currCol.values[rowNum].val.DECIMAL) {
                            valid = 1;
                            break;
                        }
                    }
                    if(!valid) {
                        printf("Value '%lf' does not exist in foreign key '%s'.\n", currCol.values[rowNum].val.DECIMAL, currCol.fKeyName);
                        values[i] = NULL;
                        i--;
                    }
                }

            }
            else if(currCol.type == BOOL) {
                currCol.values[rowNum].val.BOOL = *(int*)values[i];

                //Checking for duplicate values
                if(currCol.isPrimaryKey) {
                    for(int j = 0; j < table->numRows; j++) {
                        if(j != rowNum && !currCol.values[j].isNULL && currCol.values[j].val.BOOL == currCol.values[rowNum].val.BOOL) {
                            printf("Value in column %s, '%d' is already taken.\n", currCol.name, currCol.values[rowNum].val.BOOL);
                            values[i] = NULL;
                            i--;
                        }
                    }
                }

                //Foreign key validation
                if(values[i] != NULL && currCol.hasForeignKey) {
                    int valid = 0;
                    for(int j = 0; j < (*currCol.fKeyPointer)[currCol.fKeyIndex].numRows; j++) {
                        if(!(*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].isNULL && (*currCol.fKeyPointer)[currCol.fKeyIndex].values[j].val.BOOL == currCol.values[rowNum].val.BOOL) {
                            valid = 1;
                            break;
                        }
                    }
                    if(!valid) {
                        printf("Value '%d' does not exist in foreign key '%s'.\n", currCol.values[rowNum].val.BOOL, currCol.fKeyName);
                        values[i] = NULL;
                        i--;
                    }
                }

            }
            else if(currCol.type == DATE)
                printf("DATE datatype functionality coming soon.\n");
            else
                printf("Error: Nonexistent column name, \"%s\", provided.\n", colName);

        }

        free(colName);
    }
}

/**
 * Inserts a new column at the end of a table.
 * @param table - The table to have the column added to.
 * @param colName - The name of the new column.
 * @param colType - The datatype of the new column.
 * @param numValues - The number of values that will be provided for the inserted column.
 * @param rowNums - The list of row numbers that the provided values will be for. (0 indexed)
 * @param values - The list of values to initialize the new column with.
 * @param colAttrs - The attribute(s) of the new column. (Optional)
 * @param defaultValue - The default value for the new column. (Optional)
 * @param foreignKeyName - The name of the foreign key of the new column. (Optional)
**/
void insertCol(Table* table, char* colName, int colType, int numValues, int* rowNums, void** values, char* colAttrs, void* defaultValue, char* foreignKeyName) {

    if(!checkInvalidName(colName)) {
        printf("Error: Invalid character/string in provided column name.\n");
        return;
    }

    table->numCols++;
    if(table->numCols > 1)
        table->cols = realloc(table->cols, sizeof(Column) * table->numCols);
    else
        table->cols = malloc(sizeof(Column));
    table->cols[table->numCols - 1].type = colType;
    table->cols[table->numCols - 1].name = strdup(colName);
    table->cols[table->numCols - 1].values = malloc(sizeof(Value) * table->numRows);
    table->cols[table->numCols - 1].numRows = table->numRows;

    //Initializing the column values to NULL
    for(int i = 0; i < table->numRows; i++)
        table->cols[table->numCols - 1].values[i].isNULL = 1;

    initColAttrs(&table->cols[table->numCols - 1]);
    assignColAttrs(&table->cols[table->numCols - 1], colAttrs, defaultValue, foreignKeyName);

    //Setting the provided values
    for(int i = 0; i < numValues; i++) {
        if(values[i] != NULL) {
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

    if(table->cols[table->numCols - 1].isPrimaryKey)
        deleteDuplicateValues(&table->cols[table->numCols - 1]);
    checkDupColumnNames(*table, table->cols[table->numCols - 1].name, table->numCols - 1);

}

/**
 * Inserts a new column into the desired position.
 * @param table - The table to have the column added to.
 * @param colName - The name of the new column.
 * @param colType - The datatype of the new column.
 * @param numValues - The number of values that will be provided for the inserted column.
 * @param rowNums - The list of row numbers that the provided values will be for. (0 indexed)
 * @param values - The list of values to initialize the new column with.
 * @param colAttrs - The attribute(s) of the new column. (Optional)
 * @param defaultValue - The default value for the new column. (Optional)
 * @param foreignKeyName - The name of the foreign key of the new column. (Optional)
 * @param colPos - The string of the desired position of the new column. (Eg. "A", "AC", "DC")
**/
void insertIntoCol(Table* table, char* colName, int colType, int numValues, int* rowNums, void** values, char* colAttrs, void* defaultValue, char* foreignKeyName, char* colPos) {

    if(!checkInvalidName(colName)) {
        printf("Error: Invalid character/string in provided column name.\n");
        return;
    }

    int colNum = letterToInt(colPos) - 1;
    if(colNum < 0 || colNum > table->numCols) {
        printf("Error: Invalid column position provided. Inserting into the end of table.\n");
        insertCol(table, colName, colType, numValues, rowNums, values, colAttrs, defaultValue, foreignKeyName);
        return;
    }
    table->numCols++;

    if(table->numCols > 1)
        table->cols = realloc(table->cols, sizeof(Column) * table->numCols);
    else
        table->cols = malloc(sizeof(Column));

    table->cols[table->numCols - 1].values = malloc(sizeof(Value) * table->numRows);

    //Shifting columns over to make way for the new one
    for(int i = table->numCols - 1; i > colNum; i--)
        table->cols[i] = copyColumn(table->cols[i - 1]);

    table->cols[colNum].type = colType;
    table->cols[colNum].name = strdup(colName);
    table->cols[colNum].values = malloc(sizeof(Value) * table->numRows);
    table->cols[colNum].numRows = table->numRows;

    //Initializing the column values to NULL
    for(int i = 0; i < table->numRows; i++)
        table->cols[colNum].values[i].isNULL = 1;

    initColAttrs(&table->cols[colNum]);
    assignColAttrs(&table->cols[colNum], colAttrs, defaultValue, foreignKeyName);

    //Setting the provided values
    for(int i = 0; i < numValues; i++) {
        if(values[i] != NULL) {
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

    if(table->cols[colNum].isPrimaryKey)
        deleteDuplicateValues(&table->cols[colNum]);
    checkDupColumnNames(*table, table->cols[colNum].name, colNum);

}

/**
 * Initializes attributes of a column to their base values. This is an important function to call to ensure your column works correctly.
 * @param col - The column whose attributes are getting initialized.
**/
void initColAttrs(Column* col) {
    col->notNull = 0;
    col->defaultValue.isNULL = 1;
    col->hasForeignKey = 0;
    col->fKeyName = NULL;
    col->isPrimaryKey = 0;
    col->autoIncrement = 0;
}

/**
 * Takes a string of letters representing attributes to assign to a column, and ensures the column adheres to these attributes up to this point. String example: "APF" = AutoIncrement, Primary Key, Foreign Key
 * @param col - The column having the attributes assigned to it.
 * @param attrs - The attribute string.
 * @param defaultVal - A default value to take the place of NULL for the column. (Optional)
 * @param foreignKeyName - The name of the foreign key column this column will refer to if F is in the attrs string. Of the format 'TableName.ColumnName'. (Only needed if F is in the attr string)
**/
void assignColAttrs(Column* col, char* attrs, void* defaultVal, char* foreignKeyName) {

    if(attrs != NULL) {
        //Default Value
        if(defaultVal != NULL) {
            col->defaultValue.isNULL = 0;
            if(col->type == INTEGER)
                col->defaultValue.val.INTEGER = *((int*)defaultVal);
            else if(col->type == DECIMAL)
                col->defaultValue.val.DECIMAL = *((double*)defaultVal);
            else if(col->type == CHAR)
                col->defaultValue.val.CHAR = strdup((char*)defaultVal);
            else if(col->type == BOOL)
                col->defaultValue.val.BOOL = *((int*)defaultVal);
            else if(col->type == DATE)
                printf("DATE datatype yet to be implemented.\n");
        }
        //Not Null
        if(strchr(attrs, 'N')) {
            col->notNull = 1;
            if(!defaultVal && col->defaultValue.isNULL) {
                col->defaultValue.isNULL = 0;
                if(col->type == INTEGER)
                    col->defaultValue.val.INTEGER = 0;
                else if(col->type == DECIMAL)
                    col->defaultValue.val.DECIMAL = 0;
                else if(col->type == CHAR)
                    col->defaultValue.val.CHAR = strdup("Empty");
                else if(col->type == BOOL)
                    col->defaultValue.val.BOOL = 0;
                else if(col->type == DATE)
                    printf("DATE datatype yet to be implemented.\n");
            }

            for(int i = 0; i < col->numRows; i++) {
                if(col->values[i].isNULL) {
                    col->values[i].isNULL = 0;

                    if(col->type == INTEGER)
                        col->values[i].val.INTEGER = col->defaultValue.val.INTEGER;
                    else if(col->type == DECIMAL)
                        col->values[i].val.DECIMAL = col->defaultValue.val.DECIMAL;
                    else if(col->type == CHAR)
                        col->values[i].val.CHAR = strdup(col->defaultValue.val.CHAR);
                    else if(col->type == BOOL)
                        col->values[i].val.BOOL = col->defaultValue.val.BOOL;
                    else if(col->type == DATE)
                        printf("DATE datatype yet to be implemented.\n");

                }
            }
        }
        //Primary Key
        if(strchr(attrs, 'P')) {
            col->isPrimaryKey = 1;
            if(col->numRows > 0)
                deleteDuplicateValues(col);
        }
        //Foreign Key
        if(strchr(attrs, 'F') && foreignKeyName) {
            col->hasForeignKey = 1;
            if(foreignKeyName)
                col->fKeyName = strdup(foreignKeyName);
            else
                col->fKeyName = NULL;
        }
        //Auto Increment
        if(strchr(attrs, 'A')) {
            if(col->type == INTEGER || col->type == DECIMAL || col->type == CHAR) {

                col->autoIncrement = 1;
                col->defaultValue.isNULL = 0;

                if(!defaultVal) {
                    if(col->type == INTEGER) {
                        int maxVal = -1;

                        for(int i = 0; i < col->numRows; i++)
                            if(!col->values[i].isNULL && col->values[i].val.INTEGER > maxVal)
                                maxVal = col->values[i].val.INTEGER;

                        col->defaultValue.val.INTEGER = maxVal + 1;
                    }
                    else if(col->type == DECIMAL) {
                        double maxVal = -0.1;

                        for(int i = 0; i < col->numRows; i++)
                            if(!col->values[i].isNULL && col->values[i].val.DECIMAL > maxVal)
                                maxVal = col->values[i].val.DECIMAL;

                        col->defaultValue.val.DECIMAL = maxVal + 0.1;
                    }
                    else if(col->type == CHAR) {

                        int maxVal = letterToInt("A") - 1;

                        for(int i = 0; i < col->numRows; i++) {
                            if(!col->values[i].isNULL) {
                                int temp = letterToInt(col->values[i].val.CHAR);
                                if(temp > maxVal)
                                    maxVal = temp;
                            }
                        }

                        col->defaultValue.val.CHAR = intToLetter(maxVal + 1);
                    }
                }

                for(int i = 0; i < col->numRows;i++) {
                    if(col->values[i].isNULL) {
                        col->values[i].isNULL = 0;

                        if(col->type == INTEGER)
                            col->values[i].val.INTEGER = col->defaultValue.val.INTEGER++;
                        else if(col->type == DECIMAL) {
                            col->values[i].val.DECIMAL = col->defaultValue.val.DECIMAL;
                            col->defaultValue.val.DECIMAL += 0.1;
                        }
                        else if(col->type == CHAR) {
                            col->values[i].val.CHAR = strdup(col->defaultValue.val.CHAR);
                            col->defaultValue.val.CHAR = intToLetter(letterToInt(col->defaultValue.val.CHAR) + 1);
                        }
                        else if(col->type == BOOL)
                            col->values[i].val.BOOL = col->defaultValue.val.BOOL;
                        else if(col->type == DATE)
                            printf("DATE datatype yet to be implemented.\n");

                    }
                }

            }

        }
    }
}

/**
 * Required to set a new foreign key pointer, as when the attribute is first assigned, the other table was not accessible.
 * @param col - The column that needs its foreign key pointer set.
 * @param numTables - The number of tables in the array of tables that is the next parameter.
 * @param tables - The array of tables, containing within it the table that the column's foreign key will point to.
 * @return - Success or failure of setting the pointer. 1 = success, 0 = failure.
**/
int setForeignKeyPointer(Column* col, int numTables, Table* tables) {
    if(!col || !tables)
        return 0;

    if(!col->hasForeignKey || strchr(col->fKeyName, '.') == NULL)
        return 0;

    char tableName[MAX_LEN * 2];
    strcpy(tableName, col->fKeyName);
    char colName[MAX_LEN];
    strcpy(colName, strchr(tableName, '.') + 1);
    *strchr(tableName, '.') = '\0';

    Table* foreignTable = NULL;

    //Finding the matching table
    for(int i = 0; i < numTables; i++) {
        if(strcmp(tableName, tables[i].name) == 0) {
            foreignTable = &tables[i];
            break;
        }
    }

    if(foreignTable == NULL)
        return 0;

    col->fKeyPointer = NULL;
    col->fKeyIndex = -1;

    //Finding the matching column
    for(int i = 0; i < foreignTable->numCols; i++) {
        if(strcmp(colName, foreignTable->cols[i].name) == 0 && foreignTable->cols[i].isPrimaryKey && col->type == foreignTable->cols[i].type) {
            col->fKeyPointer = &foreignTable->cols;
            col->fKeyIndex = i;
            break;
        }
    }

    if(col->fKeyPointer == NULL)
        return 0;

    //Ensuring adherance to this new foreign key relationship
    deleteInvalidFKeyVals(col);

    return 1;
}

/**
 * Looks into the given column and deletes any rows that violates its foreign key relationship. A violation occurs when the column contains values that the column it is referencing does not.
 * @param col - The column being evaluated.
 * @return - Success or failure of the validation of foreign key rules. Failure means there is some discrepancy with the foreign key name, pointer, or index.
**/
int deleteInvalidFKeyVals(Column* col) {

    //Error checks
    if(!col->hasForeignKey || col->fKeyIndex < 0 || col->fKeyName == NULL || strchr(col->fKeyName, '.') == NULL || col->fKeyPointer == NULL)
        return 0;
    if(!(*col->fKeyPointer)[col->fKeyIndex].isPrimaryKey || col->type != (*col->fKeyPointer)[col->fKeyIndex].type) {
        col->hasForeignKey = 0;
        col->fKeyIndex = -1;
        if(col->fKeyName != NULL) {
            free(col->fKeyName);
            col->fKeyName = NULL;
        }
        col->fKeyPointer = NULL;
        return 0;
    }

    //Looping through and comparing the values of the given column with its foreign key to find any mismatches
    if(col->type == CHAR) {
        for(int i = 0; i < col->numRows; i++) {
            int valid = 0;
            for(int j = 0; j < (*col->fKeyPointer)[col->fKeyIndex].numRows; j++) {
                if(!col->values[i].isNULL && !(*col->fKeyPointer)[col->fKeyIndex].values[j].isNULL) {
                    if(strcmp(col->values[i].val.CHAR, (*col->fKeyPointer)[col->fKeyIndex].values[j].val.CHAR) == 0) {
                        valid = 1;
                        break;
                    }
                }
            }
            if(!valid) {
                free(col->values[i].val.CHAR);
                col->values[i].val.CHAR = NULL;
                col->values[i].isNULL = 1;
            }
        }
    }
    else if(col->type == INTEGER) {
        for(int i = 0; i < col->numRows; i++) {
            int valid = 0;
            for(int j = 0; j < (*col->fKeyPointer)[col->fKeyIndex].numRows; j++) {
                if(!col->values[i].isNULL && !(*col->fKeyPointer)[col->fKeyIndex].values[j].isNULL) {
                    if(col->values[i].val.INTEGER == (*col->fKeyPointer)[col->fKeyIndex].values[j].val.INTEGER) {
                        valid = 1;
                        break;
                    }
                }
            }
            if(!valid)
                col->values[i].isNULL = 1;
        }
    }
    else if(col->type == DECIMAL) {
        for(int i = 0; i < col->numRows; i++) {
            int valid = 0;
            for(int j = 0; j < (*col->fKeyPointer)[col->fKeyIndex].numRows; j++) {
                if(!col->values[i].isNULL && !(*col->fKeyPointer)[col->fKeyIndex].values[j].isNULL) {
                    if(col->values[i].val.DECIMAL != (*col->fKeyPointer)[col->fKeyIndex].values[j].val.DECIMAL) {
                        valid = 1;
                        break;
                    }
                }
            }
            if(!valid)
                col->values[i].isNULL = 1;
        }
    }
    else if(col->type == BOOL) {
        for(int i = 0; i < col->numRows; i++) {
            int valid = 0;
            for(int j = 0; j < (*col->fKeyPointer)[col->fKeyIndex].numRows; j++) {
                if(!col->values[i].isNULL && !(*col->fKeyPointer)[col->fKeyIndex].values[j].isNULL) {
                    if(col->values[i].val.BOOL != (*col->fKeyPointer)[col->fKeyIndex].values[j].val.BOOL) {
                        valid = 1;
                        break;
                    }
                }
            }
            if(!valid)
                col->values[i].isNULL = 1;
        }
    }
    else if(col->type == DATE)
        printf("DATE datatype yet to be implemented.\n");

    return 1;
}

/**
 * Takes a table and WHERE statement(s) to update existing values in the table with the provided new value(s).
 * @param table - The table that is being updated.
 * @param numUpdCols - The number of cols that are going to have their values updated.
 * @param colNames - The array of names of columns that will have their values updated.
 * @param newValues - The array of values that will replace the values that satisfy the where conditions. Each value aligns with the colNames array.
 * @param numWheres - The number of WHERE statements provided to this update.
 * @param wheres - The array of where statements.
 * @param conns - The array of logical connectives that string the WHERE statements together. (Can consist of '~', '&', and '|'). Only required if there is more than one WHERE statement. Ensure your connective array begins with '~'. If not your WHERE statements may not be connected how you like.
**/
void update(Table* table, int numUpdCols, char** colNames, void** newValues, int numWheres, Where* wheres, char* conns) {

    Column currCol;
    int* prevGoodJs;
    int numPrevGoodJs;
    int toUpdate[table->numRows];

    if(conns == NULL)
        conns = "~";
    else if(conns[0] != '~') {
        conns = realloc(conns, sizeof(char) * MAX_LEN);
        for(int i = strlen(conns); i > 0; i++)
            conns[i + 1] = conns[i];
        conns[0] = '~';
    }

    for(int i = 0; i < table->numRows; i++)
        toUpdate[i] = 1;

    //Looping through AND/OR logic for the number of WHERE statements
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
        //Each set of WHERE statements are broken up by ORs. Once an OR shows up, the values that have met the first OR condition are updated.
        if((i == numWheres - 1 || conns[i + 1] == '|' || conns[i + 1] == 'o' || conns[i + 1] == 'O') && (numPrevGoodJs > 0 && numPrevGoodJs <= table->numRows)) {

            for(int l = 0; l < numPrevGoodJs; l++) {
                for(int k = 0; k < numUpdCols; k++) {
                    currCol = nameToCol(table, colNames[k], NULL);
                    if(newValues[k] == NULL || strcmp(newValues[k], "NULL") == 0) {
                        if(!currCol.notNull && !currCol.autoIncrement)
                            currCol.values[prevGoodJs[l]].isNULL = 1;
                        else {

                            if(currCol.type == CHAR) {
                                if(!currCol.values[prevGoodJs[l]].isNULL && currCol.values[prevGoodJs[l]].val.CHAR)
                                    free(currCol.values[prevGoodJs[l]].val.CHAR);
                                currCol.values[prevGoodJs[l]].val.CHAR = strdup(currCol.defaultValue.val.CHAR);
                                if(currCol.autoIncrement)
                                    currCol.defaultValue.val.CHAR = intToLetter(letterToInt(currCol.defaultValue.val.CHAR) + 1);
                            }
                            else if(currCol.type == INTEGER) {
                                currCol.values[prevGoodJs[l]].val.INTEGER = currCol.defaultValue.val.INTEGER;
                                if(currCol.autoIncrement)
                                    currCol.defaultValue.val.INTEGER++;
                            }
                            else if(currCol.type == DECIMAL) {
                                currCol.values[prevGoodJs[l]].val.DECIMAL = currCol.defaultValue.val.DECIMAL;
                                if(currCol.autoIncrement)
                                    currCol.defaultValue.val.DECIMAL += 0.1;
                            }
                            else if(currCol.type == BOOL)
                                currCol.values[prevGoodJs[l]].val.BOOL = currCol.defaultValue.val.BOOL;
                            else if(currCol.type == DATE)
                                printf("DATE datatype functionality coming soon.\n");
                            currCol.values[prevGoodJs[l]].isNULL = 0;
                        }
                    }
                    else if(currCol.type == CHAR) {

                        if(!currCol.values[prevGoodJs[l]].isNULL && currCol.values[prevGoodJs[l]].val.CHAR)
                            free(currCol.values[prevGoodJs[l]].val.CHAR);
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

    //Ensuring adherance to the column's attributes after an update
    for(int i = 0; i < table->numCols; i++) {
        if(table->cols[i].isPrimaryKey)
            deleteDuplicateValues(&table->cols[i]);
        if(table->cols[i].hasForeignKey)
            deleteInvalidFKeyVals(&table->cols[i]);
    }

}

/**
 * Takes a table and WHERE statement(s) to delete rows in the table that meet the WHERE statement conditions.
 * @param table - The table that is having rows deleted.
 * @param numWheres - The number of WHERE statements provided to this deletion.
 * @param wheres - The array of where statements.
 * @param conns - The array of logical connectives that string the WHERE statements together. (Can consist of '~', '&', and '|'). Only required if there is more than one WHERE statement. Ensure your connective array begins with '~'. If not your WHERE statements may not be connected how you like.
**/
void delete(Table* table, int numWheres, Where* wheres, char* conns) {
    int* prevGoodJs;
    int numPrevGoodJs;
    int toDelete[table->numRows];

    if(conns == NULL)
        conns = "~";
    else if(conns[0] != '~') {
        conns = realloc(conns, sizeof(char) * MAX_LEN);
        for(int i = strlen(conns); i > 0; i++)
            conns[i + 1] = conns[i];
        conns[0] = '~';
    }

    for(int i = 0; i < table->numRows; i++)
        toDelete[i] = 1;

    //Looping through AND/OR logic for the number of WHERE statements
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
                            else if(table->cols[l].type == CHAR) {
                                if(table->cols[l].values[m].val.CHAR)
                                    free(table->cols[l].values[m].val.CHAR);
                                table->cols[l].values[m].val.CHAR = strdup(table->cols[l].values[m + 1].val.CHAR);
                            }
                            else if(table->cols[l].type == BOOL)
                                table->cols[l].values[m].val.BOOL = table->cols[l].values[m + 1].val.BOOL;
                            else if(table->cols[l].type == DATE)
                                printf("DATE datatype functionality coming soon.\n");
                        }
                    }
                }

                table->numRows--;
                if(table->cols[table->numRows].type == CHAR)
                    for(int l = 0; l < table->numRows + 1; l++)
                        if(!table->cols[table->numRows].values[l].isNULL && table->cols[table->numRows].values[l].val.CHAR)
                            free(table->cols[table->numRows].values[l].val.CHAR);

                for(int l = k + 1; l < numPrevGoodJs; l++)
                    if(prevGoodJs[l] > prevGoodJs[k])
                        prevGoodJs[l]--;

            }
        }
        free(prevGoodJs);
    }

    if(numWheres <= 0)
        table->numRows = 0;

    for(int i = 0; i < table->numCols; i++) {
        table->cols[i].values = realloc(table->cols[i].values, sizeof(Value) * table->numRows);
        table->cols[i].numRows = table->numRows;
    }
}

/**
 * A function to free all aspects of a table. This includes its string values, rows, columns, and its name.
 * @param table - The table to have all its aspects freed.
**/
void freeTable(Table* table) {
    //Freeing string values
    for(int i = 0; i < table->numCols; i++) {
        if(table->cols[i].type == CHAR) {
            for(int j = 0; j < table->numRows; j++)
                if(!table->cols[i].values[j].isNULL && table->cols[i].values[j].val.CHAR != NULL)
                    free(table->cols[i].values[j].val.CHAR);
            //Freeing string default value
            if(!table->cols[i].defaultValue.isNULL && table->cols[i].defaultValue.val.CHAR != NULL)
                free(table->cols[i].defaultValue.val.CHAR);
        }
        //Freeing foreign key name
        if(table->cols[i].fKeyName != NULL)
            free(table->cols[i].fKeyName);
        //Freeing rows
        free(table->cols[i].values);
        free(table->cols[i].name);
    }

    //Freeing columns
    free(table->cols);
    free(table->name);
}

/**
 * A function to free a database of tables. Calls freeTable for each table.
 * @param tables - The array of tables to be freed.
 * @param numTables - The number of tables in the array.
 */
void freeDatabase(Table* tables, int numTables) {
    for(int i = 0; i < numTables; i++)
        freeTable(&tables[i]);

    free(tables);
}

/**
 * Deletes a column based on the given column name in the given table.
 * @param table - The table to have a column deleted from.
 * @param colName - The name of the column to be deleted.
**/
void deleteColumn(Table* table, char* colName) {
    int colIndex;

    Column col = nameToCol(table, colName, &colIndex);

    if(colIndex > -1) {
        if(col.type == CHAR)
            for(int i = 0; i < table->numRows; i++)
                if(!col.values[i].isNULL)
                    free(col.values[i].val.CHAR);
        if(!col.defaultValue.isNULL && col.defaultValue.val.CHAR)
            free(col.defaultValue.val.CHAR);
        if(col.fKeyName)
            free(col.fKeyName);
        free(col.values);
        free(col.name);
        table->numCols--;
        for(int i = colIndex; i < table->numCols; i++)
            table->cols[i] = copyColumn(table->cols[i + 1]);

        table->cols = realloc(table->cols, sizeof(Column) * table->numCols);
    }
    else {
        printf("Error: The provided column '%s' does not exist. Deletion failed.\n", colName);
        return;
    }
}

/**
 * Deletes a row based on the given row number in the given table.
 * @param table - The table to have a row deleted from.
 * @param rowNum - The number of the row to be deleted. (0 indexed)
**/
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
                else if(table->cols[i].type == CHAR) {
                    if(!table->cols[i].values[j].isNULL && table->cols[i].values[j].val.CHAR)
                        free(table->cols[i].values[j].val.CHAR);
                    table->cols[i].values[j].val.CHAR = strdup(table->cols[i].values[j + 1].val.CHAR);
                }
                else if(table->cols[i].type == BOOL)
                    table->cols[i].values[j].val.BOOL = table->cols[i].values[j + 1].val.BOOL;
                else if(table->cols[i].type == DATE)
                    printf("DATE datatype functionality coming soon.\n");
            }
        }
    }

    table->numRows--;

    for(int i = 0; i < table->numCols; i++) {
        table->cols[i].numRows--;
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

    Table selectedTable;

    selectedTable = selCreate(tableCopy, sel.numCols, sel.colNames);

    if(sel.distinct)
        deleteDuplicateValRows(&selectedTable, sel.numCols, sel.colNames);

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

    int extraOffset = 0;

    for(int i = 0; i < numCols; i++) {
        if(!isAggregate(colNames[i])) {
            if(strcmp(colNames[i], "*") == 0) {
                newTable.numCols += baseTable.numCols - 1;
                newTable.cols = realloc(newTable.cols, sizeof(Column) * newTable.numCols);
                for(int j = 0; j < baseTable.numCols; j++)
                    newTable.cols[i + j + extraOffset] = copyColumn(baseTable.cols[j]);

                extraOffset += baseTable.numCols - 1;
            }
            else
                newTable.cols[i + extraOffset] = copyColumn(nameToCol(&baseTable, colNames[i], NULL));
            allAggs = 0;
        }
        else {
            char* colName = getColNameFromAggregate(colNames[i]);

            newTable.cols[i + extraOffset].values = malloc(sizeof(Value) * newTable.numRows);
            newTable.cols[i + extraOffset].name = malloc(sizeof(char) * MAX_LEN);
            strcpy(newTable.cols[i + extraOffset].name, getAggregateName(colNames[i]));
            strcat(newTable.cols[i + extraOffset].name, " of ");
            strcat(newTable.cols[i + extraOffset].name, colName);

            newTable.cols[i + extraOffset].type = nameToCol(&baseTable, colName, NULL).type;

            char* aggregateName = getAggregateName(colNames[i]);

            if(strcmp(aggregateName, "COUNT") == 0) {
                newTable.cols[i + extraOffset].type = INTEGER;
                newTable.cols[i + extraOffset].values[0].val.INTEGER = newTable.numRows;
                newTable.cols[i + extraOffset].values[0].isNULL = 0;
            }
            else if(strcmp(aggregateName, "AVG") == 0) {
                double avg = 0;
                if(newTable.cols[i + extraOffset].type == DECIMAL) {
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
                        newTable.cols[i + extraOffset].values[0].val.DECIMAL = avg;
                        newTable.cols[i + extraOffset].values[0].isNULL = 0;
                    }
                    else {
                        newTable.cols[i + extraOffset].values[0].isNULL = 0;
                    }
                }
                else if(newTable.cols[i + extraOffset].type == INTEGER) {
                    // printf("INTEGER\n");
                    int count = 0;
                    int sum = 0;
                    for(int j = 0; j < newTable.numRows; j++) {
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL) {
                            sum += nameToCol(&baseTable, colName, NULL).values[j].val.INTEGER;
                            count++;
                        }
                    }
                    avg = (double)sum / count;
                    newTable.cols[i + extraOffset].type = DECIMAL;
                    newTable.cols[i + extraOffset].values[0].val.DECIMAL = avg;
                    newTable.cols[i + extraOffset].values[0].isNULL = 0;
                }
                else {
                    newTable.cols[i + extraOffset].values[0].isNULL = 1;
                }

            }
            else if(strcmp(aggregateName, "SUM") == 0) {
                if(newTable.cols[i + extraOffset].type == DECIMAL) {
                    double sum = 0;
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL)
                            sum += nameToCol(&baseTable, colName, NULL).values[j].val.DECIMAL;
                    newTable.cols[i + extraOffset].values[0].val.DECIMAL = sum;
                    newTable.cols[i + extraOffset].values[0].isNULL = 0;
                }
                else if(newTable.cols[i + extraOffset].type == INTEGER) {
                    int sum = 0;
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL)
                            sum += nameToCol(&baseTable, colName, NULL).values[j].val.INTEGER;
                    newTable.cols[i + extraOffset].values[0].val.INTEGER = sum;
                    newTable.cols[i + extraOffset].values[0].isNULL = 0;
                }
                else {
                    newTable.cols[i + extraOffset].values[0].isNULL = 1;
                }
            }
            else if(strcmp(aggregateName, "MAX") == 0) {
                if(newTable.cols[i + extraOffset].type == DECIMAL) {
                    double max = __DBL_MIN__;
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL && nameToCol(&baseTable, colName, NULL).values[j].val.DECIMAL > max)
                            max = nameToCol(&baseTable, colName, NULL).values[j].val.DECIMAL;
                    newTable.cols[i + extraOffset].values[0].val.DECIMAL = max;
                    newTable.cols[i + extraOffset].values[0].isNULL = 0;
                }
                else if(newTable.cols[i + extraOffset].type == INTEGER) {
                    int max = INT_MIN;
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL && nameToCol(&baseTable, colName, NULL).values[j].val.INTEGER > max)
                            max = nameToCol(&baseTable, colName, NULL).values[j].val.INTEGER;
                    newTable.cols[i + extraOffset].values[0].val.INTEGER = max;
                    newTable.cols[i + extraOffset].values[0].isNULL = 0;
                }
                else if(newTable.cols[i + extraOffset].type == CHAR) {
                    char* max = malloc(sizeof(char) * MAX_LEN);
                    strcpy(max, "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ");
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL && strcmp(nameToCol(&baseTable, colName, NULL).values[j].val.CHAR, max) < 0)
                            strcpy(max, nameToCol(&baseTable, colName, NULL).values[j].val.CHAR);
                    newTable.cols[i + extraOffset].values[0].val.CHAR = max;
                    newTable.cols[i + extraOffset].values[0].isNULL = 0;
                }
                else if(newTable.cols[i + extraOffset].type == DATE) {
                    printf("DATE datatype support yet to be implemented.\n");
                    newTable.cols[i + extraOffset].values[0].isNULL = 1;
                }
                else {
                    newTable.cols[i + extraOffset].values[0].isNULL = 1;
                }
            }
            else if(strcmp(aggregateName, "MIN") == 0) {
                if(newTable.cols[i + extraOffset].type == DECIMAL) {
                    double min = __DBL_MAX__;
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL && nameToCol(&baseTable, colName, NULL).values[j].val.DECIMAL < min)
                            min = nameToCol(&baseTable, colName, NULL).values[j].val.DECIMAL;
                    newTable.cols[i + extraOffset].values[0].val.DECIMAL = min;
                    newTable.cols[i + extraOffset].values[0].isNULL = 0;
                }
                else if(newTable.cols[i + extraOffset].type == INTEGER) {
                    int min = INT_MAX;
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL && nameToCol(&baseTable, colName, NULL).values[j].val.INTEGER < min)
                            min = nameToCol(&baseTable, colName, NULL).values[j].val.INTEGER;
                    newTable.cols[i + extraOffset].values[0].val.INTEGER = min;
                    newTable.cols[i + extraOffset].values[0].isNULL = 0;
                }
                else if(newTable.cols[i + extraOffset].type == CHAR) {
                    char* min = malloc(sizeof(char) * MAX_LEN);
                    strcpy(min, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
                    for(int j = 0; j < newTable.numRows; j++)
                        if(!nameToCol(&baseTable, colName, NULL).values[j].isNULL && strcmp(nameToCol(&baseTable, colName, NULL).values[j].val.CHAR, min) > 0)
                            strcpy(min, nameToCol(&baseTable, colName, NULL).values[j].val.CHAR);
                    newTable.cols[i + extraOffset].values[0].val.CHAR = min;
                    newTable.cols[i + extraOffset].values[0].isNULL = 0;
                }
                else if(newTable.cols[i + extraOffset].type == DATE) {
                    printf("DATE datatype support yet to be implemented.\n");
                    newTable.cols[i + extraOffset].values[0].isNULL = 1;
                }
                else {
                    newTable.cols[i + extraOffset].values[0].isNULL = 1;
                }
            }

            for(int j = 1; j < newTable.numRows; j++)
                newTable.cols[i + extraOffset].values[j].isNULL = 1;
        }
    }

    if(allAggs) {
        for(int i = 0; i < numCols; i++) {
            newTable.cols[i].numRows = 1;
            newTable.cols[i].values = realloc(newTable.cols[i].values, sizeof(Value));
        }
        newTable.numRows = 1;
    }

    for(int i = newTable.numCols - 1; i >= 0; i--) {
        checkDupColumnNames(newTable, newTable.cols[i].name, i);
    }

    return newTable;

}

void deleteDuplicateValues(Column* col) {
    int numUniqueFound = 0;
    int found;
    if(col->type == CHAR) {
        // printf("CHAR\n");
        char** foundChars = NULL;

        for(int j = 0; j < col->numRows; j++) {
            if(!col->values[j].isNULL) {
                if(foundChars != NULL) {
                    found = 0;
                    for(int k = 0; k < numUniqueFound; k++) {
                        if(strcmp(foundChars[k], col->values[j].val.CHAR) == 0) {
                            found = 1;
                            break;
                        }
                    }
                    if(!found) {
                        numUniqueFound++;
                        foundChars = realloc(foundChars, sizeof(char*) * numUniqueFound);
                        foundChars[numUniqueFound - 1] = strdup(col->values[j].val.CHAR);
                    }
                    else {
                        // printf("NONO\n");
                        free(col->values[j].val.CHAR);
                        if(!col->notNull && !col->autoIncrement) {
                            col->values[j].isNULL = 1;
                        }
                        else {
                            col->values[j].val.CHAR = strdup(col->defaultValue.val.CHAR);
                            if(col->autoIncrement)
                                strcpy(col->defaultValue.val.CHAR, intToLetter(letterToInt(col->defaultValue.val.CHAR) + 1));

                        }
                    }
                }
                else {
                    numUniqueFound++;
                    foundChars = malloc(sizeof(char*));
                    foundChars[numUniqueFound - 1] = strdup(col->values[j].val.CHAR);
                }
            }
        }
    }
    else if(col->type == INTEGER) {
        // printf("INTEGER\n");

        int* foundInts = NULL;

        for(int j = 0; j < col->numRows; j++) {
            if(!col->values[j].isNULL) {
                if(foundInts) {
                    found = 0;
                    for(int k = 0; k < numUniqueFound; k++) {
                        if(foundInts[k] == col->values[j].val.INTEGER) {
                            found = 1;
                            break;
                        }
                    }
                    if(!found) {
                        numUniqueFound++;
                        foundInts = realloc(foundInts, sizeof(int) * numUniqueFound);
                        foundInts[numUniqueFound - 1] = col->values[j].val.INTEGER;
                    }
                    else {
                        if(!col->notNull && !col->autoIncrement) {
                            col->values[j].isNULL = 1;
                        }
                        else {
                            col->values[j].val.INTEGER = col->defaultValue.val.INTEGER;
                            if(col->autoIncrement)
                                col->defaultValue.val.INTEGER++;
                        }
                    }
                }
                else {
                    numUniqueFound++;
                    foundInts = malloc(sizeof(int));
                    foundInts[numUniqueFound - 1] = col->values[j].val.INTEGER;
                }
            }
        }
    }
    else if(col->type == DECIMAL) {
        // printf("DECIMAL\n");

        double* foundDecs = NULL;

        for(int j = 0; j < col->numRows; j++) {
            if(!col->values[j].isNULL) {
                if(foundDecs) {
                    found = 0;
                    for(int k = 0; k < numUniqueFound; k++) {
                        if(foundDecs[k] == col->values[j].val.DECIMAL) {
                            found = 1;
                            break;
                        }
                    }
                    if(!found) {
                        numUniqueFound++;
                        foundDecs = realloc(foundDecs, sizeof(double) * numUniqueFound);
                        foundDecs[numUniqueFound - 1] = col->values[j].val.DECIMAL;
                    }
                    else {
                        if(!col->notNull && !col->autoIncrement) {
                            col->values[j].isNULL = 1;
                        }
                        else {
                            col->values[j].val.DECIMAL = col->defaultValue.val.DECIMAL;
                            if(col->autoIncrement)
                                col->defaultValue.val.DECIMAL += 0.1;
                        }
                    }
                }
                else {
                    numUniqueFound++;
                    foundDecs = malloc(sizeof(double));
                    foundDecs[numUniqueFound - 1] = col->values[j].val.DECIMAL;
                }
            }
        }
    }
    else if(col->type == BOOL) {
        // printf("BOOL\n");

        int* foundBools = NULL;

        for(int j = 0; j < col->numRows; j++) {
            if(!col->values[j].isNULL) {
                if(foundBools) {
                    found = 0;
                    for(int k = 0; k < numUniqueFound; k++) {
                        if(foundBools[k] == col->values[j].val.BOOL) {
                            found = 1;
                            break;
                        }
                    }
                    if(!found) {
                        numUniqueFound++;
                        foundBools = realloc(foundBools, sizeof(int) * numUniqueFound);
                        foundBools[numUniqueFound - 1] = col->values[j].val.BOOL;
                    }
                    else {
                        if(!col->notNull) {
                            col->values[j].isNULL = 1;
                        }
                        else {
                            col->values[j].val.BOOL = col->defaultValue.val.BOOL;
                        }
                    }
                }
                else {
                    numUniqueFound++;
                    foundBools = malloc(sizeof(int));
                    foundBools[numUniqueFound - 1] = col->values[j].val.BOOL;
                }
            }
        }
    }
    else if(col->type == DATE) {
        printf("DATE datatypes functionality to be implemented.\n");
    }
}

void deleteDuplicateValRows(Table* table, int numCols, char** colNames) {
    int containsStar = 0;
    for(int i = 0; i < numCols; i++)
        if(strcmp(colNames[i], "*") == 0)
            containsStar = 1;

    for(int i = 0; i < table->numCols; i++) {
        int nameFound = 0;

        if(!containsStar) {
            for(int j = 0; j < numCols; j++) {
                if(strcmp(table->cols[i].name, getColNameFromAggregate(colNames[j])) == 0) {
                    nameFound = 1;
                    break;
                }
            }
        }

        if(nameFound || containsStar) {
            int numUniqueFound = 0;
            int found;
            if(table->cols[i].type == CHAR) {
                // printf("CHAR\n");
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
                // printf("INTEGER\n");

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
                // printf("DECIMAL\n");

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
                // printf("BOOL\n");

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

    for(int i = 0; i < newTable.numCols; i++) {
        // printf("COPY COPY %d %d\n", table.cols[i].defaultValue.isNULL, nameToCol(&table, table.cols[i].name, NULL).defaultValue.isNULL);
        newTable.cols[i] = copyColumn(table.cols[i]);
        // printf("DONE COPYING\n");
    }

    return newTable;
}

Column copyColumn(Column col) {
    Column colCopy;

    colCopy.name = strdup(col.name);
    colCopy.type = col.type;
    colCopy.numRows = col.numRows;

    colCopy.autoIncrement = col.autoIncrement;
    if(col.fKeyName)
        colCopy.fKeyName = strdup(col.fKeyName);
    else
        colCopy.fKeyName = NULL;
    colCopy.fKeyPointer = col.fKeyPointer;
    colCopy.fKeyIndex = col.fKeyIndex;
    colCopy.hasForeignKey = col.hasForeignKey;
    colCopy.isPrimaryKey = col.isPrimaryKey;
    colCopy.notNull = col.notNull;

    // printf("DEFAULT VALUE TIME\n");

    colCopy.defaultValue.isNULL = col.defaultValue.isNULL;
    // printf("%d %d\n", col.defaultValue.isNULL, colCopy.defaultValue.isNULL);
    if(!colCopy.defaultValue.isNULL) {
        // printf("NOT IS NULL\n");
        if(colCopy.type == INTEGER)
            colCopy.defaultValue.val.INTEGER = col.defaultValue.val.INTEGER;
        else if(colCopy.type == CHAR)
            colCopy.defaultValue.val.CHAR = strdup(col.defaultValue.val.CHAR);
        else if(colCopy.type == DECIMAL)
            colCopy.defaultValue.val.DECIMAL = col.defaultValue.val.DECIMAL;
        else if(colCopy.type == BOOL)
            colCopy.defaultValue.val.BOOL = col.defaultValue.val.BOOL;
        else if(colCopy.type == DATE)
            printf("DATE datatype functionality coming soon.\n");
    }

    // printf("DONE WITH DEFAULT DANCING\n");

    colCopy.values = malloc(sizeof(Value) * colCopy.numRows);
    for(int i = 0; i < colCopy.numRows; i++) {
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
        else if(value == NULL)
            return 0;
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
        else if(value == NULL)
            return 1;
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
    else if(value == NULL)
        return 0;
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
        else if(value == NULL)
            return 1;
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
        else if(value == NULL)
            return 0;
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
        else if(value == NULL)
            return 1;
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
    return strstr(name, "COUNT(") || strstr(name, "SUM(") || strstr(name, "AVG(") || strstr(name, "MAX(") || strstr(name, "MIN(");
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

    select.colNames = malloc(sizeof(char*) * numCols);
    for(int i = 0; i < numCols; i++)
        select.colNames[i] = strdup(colNames[i]);
    select.distinct = distinct;

    return select;
}
char** nameList(int numNames, ...) {
    if(numNames <= 100) {
        va_list ap;
        va_start(ap, numNames);

        char** nameList = malloc(sizeof(char*) * numNames);

        for(int i = 0; i < numNames; i++)
            nameList[i] = strdup(va_arg(ap, char*));

        va_end(ap);

        return nameList;
    }
    else
        return NULL;
}
void freeList(void** nameList, int numNames) {
    if(nameList) {
        for(int i = 0; i < numNames; i++)
            if(nameList[i])
                free(nameList[i]);
        free(nameList);
    }
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
    Table masterTable = create("MASTER", 3, nameList(3, "Name", "Num Cols", "Num Rows"), typeList(3, CHAR, INTEGER, INTEGER), NULL, NULL, NULL);
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
        printf("%s", intToLetter(i + 1));
        printf("\e[1m%-*s\e[m", (int)(colWidth / 2 - strlen(intToLetter(i)) + 1), " ");
    }

    printSeparatorLine(table.numCols, 0);

    for(int i = 0; i < table.numCols; i++)
        printf("| \e[1m%-*s\e[m", colWidth - 2, table.cols[i].name);
    printf("|");

    for(int i = 0; i < table.numRows; i++) {

        if(i <= 9 || table.numRows - i <= 9) {
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
        else if(i == 10) {
            printSeparatorLine(table.numCols, 0);
            printf("\n\t");
            for(int i = 0; i < table.numCols * 23 + 1; i++) {
                printf(".");
            }
            printf("\n");
        }
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

    // printf("YEET\n");

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

void printColumn(Column col) {

    printf("\t| \e[1m%s\e[m |\n", col.name);
    for(int i = 0; i < col.numRows; i++) {
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
 * A=1
 * Z=26
 * AA=27
 * AZ=52
*/
char* intToLetter(int number) {
    char* stringOfLetters = malloc(sizeof(char) * MAX_LEN);

    number--;

    printf("YEET\n");

    int remainder = 1, quot = number, i = 0;
    char dummy;

    // printf("BEFORE\n");
    do {
        remainder = quot % 26;
        quot = quot / 26;
        stringOfLetters[i] = 65 + remainder;
        i++;
    } while(quot > 0);

    // printf("AFTER\n");

    if(i > 1)
        stringOfLetters[i - 1] -= 1;

    // printf("HEYO\n");
    stringOfLetters[i] = '\0';
    // printf("HIYA %s\n", stringOfLetters);

    for(int j = 0; j < strlen(stringOfLetters) / 2; j++) {
        dummy = stringOfLetters[j];
        stringOfLetters[j] = stringOfLetters[strlen(stringOfLetters) - j - 1];
        stringOfLetters[strlen(stringOfLetters) - j - 1] = dummy;
    }

    printf("I LIVE FIRST\n");

    return stringOfLetters;
}

int letterToInt(char* stringOfLetters) {

    char* realString = strdup(stringOfLetters);

    int number = 0;
    int j = 0;

    for(int i = strlen(realString) - 1; i >= 0; i--) {
        if(isalpha(realString[i])) {
            realString[i] = toupper(realString[i]);
            number += (realString[i] - 64) * pow(26, j);
            j++;
        }
    }

    free(realString);

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
            for(int i = 0; i < table->numRows; i++) {
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
                for(int i = 0; i < table->numRows - 1; i++) {
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
            // printf("CREATEY MATEY\n");
            sqlite3_exec(db, sql, callbackCreateTable, value, errMessage);

            printTable(*((Table*)(*value)));

            table = malloc(sizeof(Table));
            memcpy(table, (Table*)(*value), sizeof(Table));

            printTable(*table);

            strcpy(sql, "SELECT sql FROM SQLITE_MASTER WHERE Name = '");
            strcat(sql, tableName);
            strcat(sql, "'");
            printf("ATTR GET!\n");
            sqlite3_exec(db, sql, callbackGetAttributes, table, errMessage);

            strcpy(sql, "SELECT * FROM ");
            strcat(sql, properName);
            printf("INSERTY\n");
            sqlite3_exec(db, sql, callbackInsertData, table, errMessage);
            for(int i = 0; i < table->numCols; i++)
                if(table->cols[i].autoIncrement)
                    assignColAttrs(&table->cols[i], "A", NULL, NULL);

        }
        else {
            printf("Error: Table '%s' not found in file '%s'. Import failed.\n", tableName, filename);
        }

        // printf("HUZZAH!\n");
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
            char* createCmd = NULL;
            char** insertCmds = malloc(sizeof(char*));

            int numInserts = 0;

            //LIMITATION: CREATE AND INSERT COMMANDS MUST BE ON SEPARATE LINES OF GIVEN FILE. FIX IN THE FUTURE!
            while(fgets(line, 1000, fp)) {
                // printf("%s\n", createCmd);

                // printf("%d ", numInserts);

                if(!creating && strstr(line, tableCreateLine)) {
                    creating = 1;
                }
                if(creating) {
                    if(strstr(line, ";")) {
                        char* lineCopy = strdup(line);
                        if(!createCmd) {
                            createCmd = malloc(1000);
                            strcpy(createCmd, strtok(lineCopy, ";"));
                        }
                        else {
                            createCmd = realloc(createCmd, strlen(createCmd + 1000));
                            strcat(createCmd, lineCopy);
                        }
                        strcat(createCmd, ";\n");
                        creating = 0;
                        free(lineCopy);
                    }
                    else {
                        if(!createCmd) {
                            createCmd = malloc(1000);
                            strcpy(createCmd, line);
                        }
                        else {
                            createCmd = realloc(createCmd, strlen(createCmd + 1000));
                            strcat(createCmd, line);
                        }
                    }
                    // printf("LINE: %s\n", line);
                }
                if(!inserting && strstr(line, rowInsertLine)) {
                    // printf("LINE: %s\n", strstr(line, rowInsertLine));
                    inserting = 1;
                    numInserts++;
                    if(numInserts > 1)
                        insertCmds = realloc(insertCmds, sizeof(char*) * numInserts);
                    insertCmds[numInserts - 1] = malloc(1000);
                    strcpy(insertCmds[numInserts - 1], "");
                }
                if(inserting) {

                    if(!insertCmds[numInserts - 1]) {
                        insertCmds[numInserts - 1] = malloc(1000);
                        strcpy(insertCmds[numInserts - 1], "");
                    }
                    else
                        insertCmds[numInserts - 1] = realloc(insertCmds[numInserts - 1], strlen(insertCmds[numInserts - 1]) + 1000);

                    if(strstr(line, ";")) {

                        char* lineCopy = strdup(line);
                        strcat(insertCmds[numInserts - 1], strtok(lineCopy, ";"));
                        strcat(insertCmds[numInserts - 1], ";\n");
                        inserting = 0;
                        free(lineCopy);
                    }
                    else
                        strcat(insertCmds[numInserts - 1], line);
                }
            }
            fclose(fp);

            char* sql = malloc(1000 * numInserts + strlen(createCmd));
            strcpy(sql, createCmd);
            free(createCmd);
            for(int i = 0; i < numInserts; i++) {
                // printf("%d ", i);
                strcat(sql, insertCmds[i]);
                free(insertCmds[i]);
            }

            free(insertCmds);

            // printf("%s\n", sql);
            sqlite3* db;
            char** errMessage = malloc(sizeof(char*));
            *errMessage = strdup("Error: SQL Execution Failed");

            truncate("load.db", 0);

            sqlite3_open("load.db", &db);
            sqlite3_exec(db, sql, NULL, NULL, errMessage);
            sqlite3_close(db);
            free(errMessage);
            free(sql);

            table = importTable(tableName, "load.db");

            remove("load.db");
        }
    }

    free(properName);

    // printf("HUZZAH TRULY\n");

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

        for(int i = 0; i < names->numNames; i++) {
            printf("%d %s\n", i, names->names[i]);
        }

        sqlite3_close(db);

        numTables = names->numNames;

        if(numTables >= 1) {

            if(tables == NULL)
                tables = malloc(sizeof(Table*));

            for(int i = 0; i < numTables; i++) {
                // printf("YEETUS\n");
                if(!strstr(names->names[i], "sqlite_")) {
                    if(i == 0)
                        *tables = malloc(sizeof(Table));
                    else
                        *tables = realloc(*tables, sizeof(Table) * (i + 1));

                    // printf("5 %s\n", names->names[i]);

                    (*tables)[i] = *importTable(names->names[i], filename);
                    // printf("I DID IT\n");
                }
                else
                    numTables--;
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

            //Don't make this a static size no more
            char* sql = malloc(sizeof(char) * 10000);
            char line[1000];
            int numLines = 0;
            strcpy(sql, "");

            while(fgets(line, 1000, fp)) {
                numLines++;
                // printf("%d\n", numLines);
                if(numLines > 10)
                    sql = realloc(sql, (numLines + 10) * 1000);
                strcat(sql, line);
            }

            // printf("%s\n", sql);
            sqlite3* db;
            char** errMessage = malloc(sizeof(char*));
            *errMessage = strdup("Error: SQL Execution Failed");

            printf("%s\n", sql);

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

    // printf("4 REAL?\n");

    return numTables;
}

void exportTable(Table table, char* filename, int trunc) {

    char* tableName = addQuotesToString(table.name);

    // printf("1\n");

    char* sql = malloc(16 + strlen(tableName) + (MAX_LEN + 15) * table.numCols);
    strcpy(sql, "CREATE TABLE ");
    strcat(sql, tableName);
    strcat(sql, "(");

    char* colName;
    for(int i = 0; i < table.numCols; i++) {

        // sql = realloc(sql, strlen(sql) + MAX_LEN + 15);

        colName = addQuotesToString(table.cols[i].name);
        // sql = realloc(sql, strlen(sql) + strlen(colName) + 2);
        strcat(sql, colName);
        strcat(sql, " ");

        if(table.cols[i].type != BOOL) {
            // sql = realloc(sql, strlen(sql) + strlen(typeToString(table.cols[i].type)) + 1);
            strcat(sql, typeToString(table.cols[i].type));
        }
        else {
            // sql = realloc(sql, strlen(sql) + strlen("BIT") + 1);
            strcat(sql, "BIT");
        }

        if(table.cols[i].autoIncrement)
            strcat(sql, " AUTO_INCREMENT");
        if(!table.cols[i].defaultValue.isNULL) {
            strcat(sql, " DEFAULT ");
            if(table.cols[i].type == INTEGER) {
                char intString[MAX_LEN];
                sprintf(intString, "%d", table.cols[i].defaultValue.val.INTEGER);
                strcat(sql, intString);
            }
            else if(table.cols[i].type == DECIMAL) {
                char decString[MAX_LEN];
                sprintf(decString, "%lf", table.cols[i].defaultValue.val.DECIMAL);
                strcat(sql, decString);
            }
            else if(table.cols[i].type == CHAR) {
                char chrString[MAX_LEN];
                sprintf(chrString, "'%s'", table.cols[i].defaultValue.val.CHAR);
                strcat(sql, chrString);
            }
            else if(table.cols[i].type == BOOL) {
                char boolString[MAX_LEN];
                sprintf(boolString, "%d", table.cols[i].defaultValue.val.BOOL);
                strcat(sql, boolString);
            }
            else if(table.cols[i].type == DATE) {
                printf("DATE datatype functionality coming soon.\n");
            }
        }
        if(table.cols[i].isPrimaryKey)
            strcat(sql, " PRIMARY KEY");
        if(table.cols[i].hasForeignKey) {
            strcat(sql, " REFERENCES ");
            char tableName[MAX_LEN];
            strcpy(tableName, table.cols[i].fKeyName);
            *strchr(tableName, '.') = '\0';
            strcpy(tableName, addQuotesToString(tableName));
            strcat(sql, tableName);
            strcat(sql, "(");
            strcat(sql, addQuotesToString(strchr(table.cols[i].fKeyName, '.') + 1));
            strcat(sql, ")");
        }
        if(table.cols[i].notNull)
            strcat(sql, " NOT NULL");

        if(i < table.numCols - 1) {
            // sql = realloc(sql, strlen(sql) + 3);
            strcat(sql, ", ");
        }

        free(colName);
    }

    // sql = realloc(sql, strlen(sql) + 4);
    strcat(sql, ");\n");

    char** insertSQL = malloc(sizeof(char*) * table.numRows);

    for(int i = 0; i < table.numRows; i++) {

        insertSQL[i] = malloc(table.numCols * MAX_LEN * 2 + MAX_LEN);
        strcpy(insertSQL[i], "");

        // printf("%d ", i);

        // sql = realloc(sql, strlen(sql) + table.numCols * MAX_LEN * 2 + 50);
        strcat(insertSQL[i], "INSERT INTO ");
        strcat(insertSQL[i], tableName);
        strcat(insertSQL[i], "(");

        for(int j = 0; j < table.numCols; j++) {
            // printf(" %d ", j);
            colName = addQuotesToString(table.cols[j].name);
            // sql = realloc(sql, strlen(sql) + strlen(colName) + 1);
            strcat(insertSQL[i], colName);
            if(j < table.numCols - 1) {
                // sql = realloc(sql, strlen(sql) + 3);
                strcat(insertSQL[i], ", ");
            }

            free(colName);
        }

        // printf("VALUES\n");
        // sql = realloc(sql, strlen(sql) + 11);
        strcat(insertSQL[i], ")\n");
        strcat(insertSQL[i], "VALUES(");

        for(int j = 0; j < table.numCols; j++) {
            // printf(" %d ", j);
            if(table.cols[j].values[i].isNULL) {
                // sql = realloc(sql, strlen(sql) + 5);
                strcat(insertSQL[i], "NULL");
            }
            else if(table.cols[j].type == INTEGER) {
                char intString[MAX_LEN];
                sprintf(intString, "%d", table.cols[j].values[i].val.INTEGER);
                // sql = realloc(sql, strlen(sql) + strlen(intString) + 1);
                strcat(insertSQL[i], intString);
            }
            else if(table.cols[j].type == DECIMAL) {
                char decString[MAX_LEN];
                sprintf(decString, "%lf", table.cols[j].values[i].val.DECIMAL);
                // sql = realloc(sql, strlen(sql) + strlen(decString) + 1);
                strcat(insertSQL[i], decString);
            }
            else if(table.cols[j].type == CHAR) {
                char chrString[MAX_LEN];
                sprintf(chrString, "'%s'", table.cols[j].values[i].val.CHAR);
                // sql = realloc(sql, strlen(sql) + strlen(chrString) + 1);
                strcat(insertSQL[i], chrString);
            }
            else if(table.cols[j].type == BOOL) {
                char boolString[MAX_LEN];
                sprintf(boolString, "%d", table.cols[j].values[i].val.BOOL);
                // sql = realloc(sql, strlen(sql) + strlen(boolString) + 1);
                strcat(insertSQL[i], boolString);
                // if(table.cols[j].values[i].val.BOOL == 1)
                //     strcat(sql, "TRUE");
                // else
                //     strcat(sql, "FALSE");
            }
            else if(table.cols[j].type == DATE) {
                printf("DATE datatype functionality coming soon.\n");
            }
            if(j < table.numCols - 1) {
                // sql = realloc(sql, strlen(sql) + 3);
                strcat(insertSQL[i], ", ");
            }
        }

        // sql = realloc(sql, strlen(sql) + 4);

        strcat(insertSQL[i], ");\n");

    }

    // printf("I DID IT\n");

    sql = realloc(sql, strlen(sql) + (strlen(insertSQL[0]) * table.numRows) * 2);
    for(int i = 0; i < table.numRows; i++) {
        // printf("%d ", i);
        strcat(sql, insertSQL[i]);
    }

    // printf("TRUNCING\n");

    if(trunc)
        truncate(filename, 0);

    // printf("Trunc Done\n");

    if(endsWith(filename, ".db")) {

        // printf(".DB\n");

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

        // printf("NO .DB\n");

        FILE* fp = fopen(filename, "r");
        if(fp) {
            char* tableCreateLine = malloc(sizeof(char) * 1000);
            strcpy(tableCreateLine, "CREATE TABLE ");
            strcat(tableCreateLine, tableName);

            int tableExists = 0;

            char** lines;
            int numLines = 0;

            //This is very inefficient. Make it better.

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
                    numLines++;
                    if(numLines == 1)
                        lines = malloc(sizeof(char*));
                    else
                        lines = realloc(lines, sizeof(char*) * numLines);
                    lines[numLines - 1] = strdup(line);
                }
            }

            sql = realloc(sql, strlen(sql) + 1000 * numLines);

            for(int i = 0; i < numLines; i++) {
                strcat(sql, lines[i]);
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
    *table = create(tableName, numCols, colNames, colTypes, NULL, NULL, NULL);
    *((void**)value) = table;
    return 1;
}

int callbackInsertData(void* value, int numCols, char** values, char** colNames) {
    Table* table = ((Table*)value);

    // printf("INSERT TIME\n");

    for(int i = 0; i < numCols; i++) {
        Column currCol = nameToCol(table, colNames[i], NULL);

        if(values[i] != NULL) {
            if(currCol.type == INTEGER) {
                // printf("INTEGER\n");
                int* intVal = malloc(sizeof(int));
                sscanf(values[i], "%d", intVal);
                values[i] = (void*)intVal;
            }
            else if(currCol.type == DECIMAL) {
                // printf("DECIMAL\n");
                double* decVal = malloc(sizeof(double));
                sscanf(values[i], "%lf", decVal);
                values[i] = (void*)decVal;
            }
            else if(currCol.type == BOOL) {
                // printf("BOOL\n");
                int* boolVal = malloc(sizeof(int));
                sscanf(values[i], "%d", boolVal);
                values[i] = (void*)boolVal;
                // if(strcmp(values[i], "TRUE") == 0)
                //     *boolVal = 1;
                // else
                //     *boolVal = 0;
            }
            else if(currCol.type == CHAR) {
                // printf("CHAR %s\n", values[i]);
            }
            else if(currCol.type == DATE) {
                printf("DATE datatype functionality coming soon.\n");
            }
        }
        else {
            // printf("NULL\n");
        }
    }
    // printf("INSERT ROWWWW\n");
    insertRow(table, numCols, colNames, (void**)values);

    // printf("DONE INSERTING\n");
    return 0;
}

int callbackGetTableNames(void* value, int numCols, char** values, char** colNames) {
    struct TableNames {
        char** names;
        int numNames;
    };

    if(strstr(values[0], "sqlite") == NULL) {
        if(++(((struct TableNames*)value)->numNames) == 1)
            ((struct TableNames*)value)->names = malloc(sizeof(char*));
        else
            ((struct TableNames*)value)->names = realloc(((struct TableNames*)value)->names, sizeof(char*) * ((struct TableNames*)value)->numNames);

        ((struct TableNames*)value)->names[((struct TableNames*)value)->numNames - 1] = strdup(values[0]);
    }

    return 0;
}

int callbackGetAttributes(void* value, int numCols, char** values, char** colNames) {
    Table* table = ((Table*)value);
    char* currCol = malloc(sizeof(char) * (strlen(values[0]) + MAX_LEN));

    printf("YEETUS: %s\n", values[0]);

    shrinkSpaces(&values[0]);

    printTable(*table);

    for(int i = 0; i < table->numCols; i++) {
        printf("HELP\n");
        printf("%s\n", table->cols[i].name);
        char nameCheck[MAX_LEN];
        char* temp;
        strcpy(nameCheck, ", ");
        strcat(nameCheck, addQuotesToString(table->cols[i].name));
        temp = strstr(values[0], nameCheck);
        if(temp)
            strcpy(currCol, temp);
        else {
            strcpy(nameCheck, "(");
            strcat(nameCheck, addQuotesToString(table->cols[i].name));
            temp = strstr(values[0], nameCheck);
            if(temp)
                strcpy(currCol, temp);
            else
                if(currCol[strlen(nameCheck)] == ')')
                    temp = NULL;
        }
        if(temp != NULL) {
            currCol++;
            if(currCol[0] == ' ')
                currCol++;
        }
        printf("%s\n", currCol);

        if(temp != NULL) {
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

            if(strstr(colAttrs, "PRIMARY KEY") || strstr(colAttrs, "UNIQUE")) {
                // printf("PRIMARY KEY\n");
                assignColAttrs(&table->cols[i], "P", NULL, NULL);
            }
            if(strstr(colAttrs, "AUTO_INCREMENT") || strstr(colAttrs, "AUTO INCREMENT") || strstr(colAttrs, "AUTOINCREMENT")) {
                // printf("AUTO INCREMENT\n");
                assignColAttrs(&table->cols[i], "A", NULL, NULL);
            }
            if(strstr(colAttrs, "NOT NULL")) {
                // printf("NOT NULL\n");
                assignColAttrs(&table->cols[i], "N", NULL, NULL);
            }
            if(strstr(colAttrs, "REFERENCES")) {
                // printf("FOREIGN KEY\n");
                table->cols[i].hasForeignKey = 1;

                char tableName[MAX_LEN * 2];
                strcpy(tableName, strstr(colAttrs, "REFERENCES ") + 11);
                char colName[MAX_LEN];
                strcpy(colName, strchr(tableName, '(') + 1);
                *strchr(tableName, '(') = '\0';
                *strchr(colName, ')') = '\0';

                char* fKeyName = malloc(sizeof(char) * MAX_LEN * 2);
                strcpy(fKeyName, removeQuotesFromString(tableName));
                strcat(fKeyName, ".");
                strcat(fKeyName, removeQuotesFromString(colName));

                assignColAttrs(&table->cols[i], "F", NULL, fKeyName);
                free(fKeyName);
            }
            if(strstr(colAttrs, "DEFAULT")) {
                // printf("DEFAULT DANCE\n");
                table->cols[i].defaultValue.isNULL = 0;
                char* defaultTemp = malloc(sizeof(char) * MAX_LEN);
                strcpy(defaultTemp, strstr(colAttrs, "DEFAULT ") + 8);
                if(table->cols[i].type == CHAR) {
                    *(strchr(defaultTemp + 1, '\'') + 1) = '\0';
                    // printf("DEFAULT TEMP BEFORE: %s\n", defaultTemp);
                    defaultTemp = removeQuotesFromString(defaultTemp);
                    // printf("DEFAULT TEMP AFTER: %s\n", defaultTemp);
                    table->cols[i].defaultValue.val.CHAR = strdup(defaultTemp);
                }
                else {
                    if(strchr(defaultTemp, ' ') && strchr(defaultTemp, ',')) {
                        if(strchr(defaultTemp, ' ') < strchr(defaultTemp, ','))
                            *strchr(defaultTemp, ' ') = '\0';
                        else if(strchr(defaultTemp, ' ') > strchr(defaultTemp, ','))
                            *strchr(defaultTemp, ',') = '\0';
                    }
                    else if(strchr(defaultTemp, ' '))
                        *strchr(defaultTemp, ' ') = '\0';
                    else if(strchr(defaultTemp, ','))
                        *strchr(defaultTemp, ',') = '\0';
                    else if(strchr(defaultTemp, ')'))
                        *strchr(defaultTemp, ')') = '\0';
                    if(table->cols[i].type == INTEGER) {
                        sscanf(defaultTemp, "%d", &table->cols[i].defaultValue.val.INTEGER);
                    }
                    else if(table->cols[i].type == DECIMAL) {
                        sscanf(defaultTemp, "%lf", &table->cols[i].defaultValue.val.DECIMAL);
                    }
                    else if(table->cols[i].type == BOOL) {
                        if(equalsIgnoreCase(defaultTemp, "TRUE"))
                            strcpy(defaultTemp, "1");
                        else if(equalsIgnoreCase(defaultTemp, "FALSE"))
                            strcpy(defaultTemp, "0");

                        sscanf(defaultTemp, "%d", &table->cols[i].defaultValue.val.BOOL);
                    }
                    else if(table->cols[i].type == DATE) {
                        printf("DATE datatype yet to be implemented.\n");
                    }
                }
            }
        }
    }

    printf("TIME FOR BADNESS\n");
    char* temp;
    do {
        temp = strstr(values[0], ", PRIMARY KEY(");
        printf("%s\n", temp);
        if(!temp) {
            temp = strstr(values[0], ", FOREIGN KEY(");
            if(temp) {
                printf("%s\n", temp);
                char* colName = strdup(strstr(temp, "(") + 1);
                *strchr(colName, ')') = '\0';
                strcpy(colName, removeQuotesFromString(colName));

                int fColInd = 0;
                Column fCol = nameToCol(table, colName, &fColInd);

                if(strstr(temp, "REFERENCES")) {

                    char tableName[MAX_LEN * 2];
                    strcpy(tableName, strstr(temp, "REFERENCES ") + 11);
                    printf("%s\n", tableName);
                    char fColName[MAX_LEN];
                    if(strchr(tableName, '(')) {
                        strcpy(fColName, strchr(tableName, '(') + 1);
                        *strchr(fColName, ')') = '\0';
                    }
                    else
                        strcpy(fColName, fCol.name);

                    if(strchr(tableName, '('))
                        *strchr(tableName, '(') = '\0';
                    else if(strchr(tableName, ')'))
                        *strchr(tableName, ')') = '\0';
                    else if(strchr(tableName, ','))
                        *strchr(tableName, ',') = '\0';

                    printf("%s\n", fColName);

                    char* fKeyName = malloc(sizeof(char) * MAX_LEN * 2);
                    strcpy(fKeyName, removeQuotesFromString(tableName));
                    strcat(fKeyName, ".");
                    strcat(fKeyName, removeQuotesFromString(fColName));

                    printf("%s\n", fKeyName);

                    assignColAttrs(&table->cols[fColInd], "F", NULL, fKeyName);
                    free(fKeyName);
                }
                else {
                    assignColAttrs(&table->cols[fColInd], "F", NULL, NULL);
                }
                values[0] = temp + 1;
            }
        }
        else {
            char* colName = strdup(strstr(temp, "(") + 1);
            *strchr(colName, ')') = '\0';
            strcpy(colName, removeQuotesFromString(colName));
            Column pCol = nameToCol(table, colName, NULL);
            assignColAttrs(&pCol, "P", NULL, NULL);
            values[0] = temp + 1;
        }
        if(strchr(values[0], ','))
            values[0] = strchr(values[0], ',');
        else if(strchr(values[0], ')'))
            values[0] = strchr(values[0], ')');

    } while(temp != NULL);
    // printf("i didit\n");
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

    if(!string)
        return NULL;

    char* newString = strdup(string);

    if(string[0] != '\'' && string[0] != '`')
        return newString;

    for(int i = 0; i < strlen(newString) - 2; i++)
        newString[i] = newString[i + 1];
    newString[strlen(newString) - 2] = '\0';

    return newString;

}

void shrinkSpaces(char** string) {

    char* newString = malloc(sizeof(char) * (strlen(*string) + 1));
    int spaceCount = 0;
    int charCount = 0;
    for(int i = 0; i < strlen(*string); i++) {
        if((*string)[i] != ' ' && (*string)[i] != '\n') {
            spaceCount = 0;
            newString[charCount++] = (*string)[i];
        }
        else {
            if(spaceCount == 0)
                newString[charCount++] = ' ';
            spaceCount++;
        }
    }

    *string = newString;

}

int userTableOperator(int numTables, Table** tables) {

    Table* currentTable = NULL;

    int* menuChoices;
    int currTableIndex = -1;;

    char tableName[MAX_LEN];
    char colName[MAX_LEN];
    int numThings;
    int rowNum;

    char** nameList = NULL;
    int* typeList = NULL;
    void** valueList = NULL;
    char** attrList = NULL;
    void** defaultValList = NULL;
    char** foreignKeyList = NULL;

    Where* whereList = NULL;
    int numWheres = 0;
    char* connectiveList = NULL;
    int* numList;

    Select sel;

    void* valCopy = NULL;
    int valCopyType = -1;
    LoneValue* rowCopy = NULL;
    int rowCopyLength;
    Column colCopy;
    colCopy.name = NULL;

    printf("\t\t-- Welcome to CQL! --\n");

    //ADD QUESTION FOR SELECTED TABLE IF THE USER WANTS TO APPLY THE CHANGES TO THE BASE TABLE!
    do {
        numWheres = 0;

        menuChoices = actionMenu(currentTable);

        switch(menuChoices[0]) {
            case 1:
                //"1. CREATE"
                // "1. CREATE a table"

                printf("What is the name of your new table? ('\\x' = cancel): ");
                do {
                    fgetsUntil(tableName, MAX_LEN);
                    if(strcmp(tableName, "\\x") != 0 && !checkInvalidName(tableName))
                        printf("Please input a name without prohibited characters/words: ");
                } while(strcmp(tableName, "\\x") != 0 && !checkInvalidName(tableName));

                if(strcmp(tableName, "\\x") == 0)
                    break;

                checkDupTableNames(*tables, numTables, tableName, numTables);

                printf("How many columns would you like to have? (numbers < 0 = cancel): ");
                scanfWell("%d", &numThings);

                if(numThings < 0)
                    break;
                else if(numThings > 0) {
                    nameList = malloc(sizeof(char*) * numThings);
                    typeList = malloc(sizeof(int) * numThings);
                    attrList = malloc(sizeof(char*) * numThings);
                    defaultValList = malloc(sizeof(void*) * numThings);
                    foreignKeyList = malloc(sizeof(char*) * numThings);

                    for(int i = 0; i < numThings; i++) {
                        printf("Name for column #%d: ", i + 1);
                        nameList[i] = malloc(sizeof(char) * MAX_LEN);
                        do {
                            fgetsUntil(nameList[i], MAX_LEN);
                            if(!checkInvalidName(nameList[i]))
                                printf("Please input a name without prohibited characters/words: ");
                        } while(!checkInvalidName(nameList[i]));
                        nameList[i] = realloc(nameList[i], sizeof(char) * (strlen(nameList[i]) + 1));
                        typeList[i] = typeInput();
                        attrList[i] = strdup(attrInputByType(typeList[i], &defaultValList[i], &foreignKeyList[i]));
                    }

                    numTables++;
                    if(numTables == 1)
                        *tables = malloc(sizeof(Table));
                    else
                        *tables = realloc(*tables, sizeof(Table) * numTables);

                    (*tables)[numTables - 1] = create(tableName, numThings, nameList, typeList, attrList, defaultValList, foreignKeyList);

                    currentTable = &(*tables)[numTables - 1];
                    currTableIndex = numTables - 1;

                    for(int i = 0; i < currentTable->numCols; i++)
                        if(currentTable->cols[i].hasForeignKey)
                            setForeignKeyPointer(&currentTable->cols[i], numTables, *tables);

                    for(int i = 0; i < numThings; i++) {
                        free(nameList[i]);
                        free(attrList[i]);
                        if(defaultValList[i] != NULL)
                            free(defaultValList[i]);
                        if(foreignKeyList[i] != NULL)
                            free(foreignKeyList[i]);
                    }
                    free(nameList);
                    free(typeList);
                    free(attrList);
                    free(defaultValList);
                    free(foreignKeyList);
                    nameList = NULL;
                    typeList = NULL;
                    attrList = NULL;
                    defaultValList = NULL;
                    foreignKeyList = NULL;
                }
                else {
                    (*tables)[numTables - 1] = create(tableName, numThings, NULL, NULL, NULL, NULL, NULL);
                    currentTable = &(*tables)[numTables - 1];
                    currTableIndex = numTables - 1;
                }

                for(int i = 0; i < numTables; i++)
                    for(int j = 0; j < (*tables)[i].numCols; j++)
                        if((*tables)[i].cols[j].hasForeignKey && (*tables)[i].cols[j].fKeyPointer == NULL)
                            setForeignKeyPointer(&(*tables)[i].cols[j], numTables, (*tables));

                break;
            case 2:
                //"2. PRINT"
                switch(menuChoices[1]) {
                    case 1:
                        //PRINT the Master Table
                        printTable(createMasterTable(*tables, numTables));
                        break;
                    case 2:
                        // "2. PRINT a table"
                        if(numTables > 0) {
                            printf("Which table would you like to print?\n");
                            int tableIndex = tableMenu(numTables, *tables);
                            if(tableIndex > -1)
                                printTable((*tables)[tableIndex]);
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
                            printColumn(colCopy);
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

                    int tempIndex = tableMenu(numTables, *tables);
                    if(tempIndex > -1) {
                        currTableIndex = tempIndex;
                        currentTable = &(*tables)[currTableIndex];
                    }
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
                    int tempIndex = tableMenu(numTables, *tables);
                    if(tempIndex > -1) {
                        currTableIndex = tempIndex;
                        currentTable = &(*tables)[currTableIndex];
                        printf("Here is your current table:\n");
                        printTable(*currentTable);
                    }
                    else
                        break;
                }

                switch(menuChoices[1]) {
                    case 1:
                        // "1. RENAME column in current table"
                        if(currentTable->numCols > 0) {
                            printf("Name of column you wish to rename ('\\x' = cancel): ");

                            Column column;
                            int colIndex;

                            do {
                                fgetsUntil(colName, MAX_LEN);
                                if(strcmp(colName, "\\x") != 0) {
                                    column = nameToCol(currentTable, colName, &colIndex);
                                    if(column.type == -1)
                                        printf("That column does not exist. Please try again: ");
                                }
                            } while(strcmp(colName, "\\x") != 0 && column.type == -1);

                            if(strcmp(colName, "\\x") == 0)
                                break;

                            printf("New name for column '%s': ", colName);
                            do {
                                fgetsUntil(column.name, MAX_LEN);
                                if(!checkInvalidName(column.name))
                                    printf("Please input a name without prohibited characters/words: ");
                            } while(!checkInvalidName(column.name));

                            checkDupColumnNames(*currentTable, column.name, colIndex);
                            break;
                        }
                        else {
                            printf("There are no columns in the current table to rename.\n");
                        }

                    case 2:
                        // "2. RENAME current table"
                        printf("New name for table '%s' ('\\x' = cancel): ", currentTable->name);
                        char tempName[MAX_LEN];
                        do {
                            fgetsUntil(tempName, MAX_LEN);
                            if(strcmp(tempName, "\\x") != 0) {
                                if(!checkInvalidName(tempName))
                                    printf("Please input a name without prohibited characters/words: ");
                            }
                        } while(strcmp(tempName, "\\x") != 0 && !checkInvalidName(tempName));

                        if(strcmp(tempName, "\\x") == 0)
                            break;

                        if(currentTable->name != NULL)
                            free(currentTable->name);
                        currentTable->name = strdup(tempName);
                        checkDupTableNames(*tables, numTables, currentTable->name, currTableIndex);
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
                    int tempIndex = tableMenu(numTables, *tables);
                    if(tempIndex > -1) {
                        currTableIndex = tempIndex;
                        currentTable = &(*tables)[currTableIndex];
                        printf("Here is your current table:\n");
                        printTable(*currentTable);
                    }
                    else
                        break;
                }

                char* input;
                sel.numCols = 0;
                int breakTime = 0;
                do {

                    if(sel.numCols == 0)
                        sel.colNames = malloc(sizeof(char*) * (sel.numCols + 1));
                    else
                        sel.colNames = realloc(sel.colNames, sizeof(char*) * (sel.numCols + 1));

                    printf("0\n");
                    input = malloc(sizeof(char) * MAX_LEN);

                    printf("Name for select column #%d", sel.numCols + 1);
                    if(sel.numCols > 0)
                        printf(" (Input '\\f' when finished entering names)");
                    printf(" ('\\x' = cancel)");
                    printf(": ");

                    do {
                        fgetsUntil(input, MAX_LEN);
                        if(strcmp(input, "\\x") != 0 && ((sel.numCols == 0 && strcmp(input, "\\f") == 0) || (strcmp(input, "\\f") != 0 && strcmp(input, "*") != 0 && nameToCol(currentTable, input, NULL).type == -1 && nameToCol(currentTable, getColNameFromAggregate(input), NULL).type == -1))) {
                            printf("Please enter a column name that exists in your table");
                            if(sel.numCols > 0)
                                printf("\n(Or input '\\f' if finished entering names)");
                            printf(": ");
                            continue;
                        }
                        else
                            break;
                    } while(1);

                    if(strcmp(input, "\\x") == 0) {
                        free(sel.colNames);
                        breakTime = 1;
                        break;
                    }

                    printf("1\n");

                    if(strcmp(input, "\\f") != 0) {
                        sel.colNames[sel.numCols++] = strdup(input);
                        printf("3\n");

                        free(input);
                        printf("4\n");
                        continue;
                    }
                    printf("2\n");

                } while(strcmp(input, "\\f") != 0);

                free(input);

                if(breakTime)
                    break;

                // printf("How many columns would you like to select? (1-%d): ", currentTable->numCols);
                // do {
                //     scanfWell("%d", &sel.numCols);
                //     if(sel.numCols <= 0)
                //         printf("Please input a positive number: ");
                //     else if(sel.numCols > currentTable->numCols)
                //         printf("Your current table doesn't have that many columns. Try again: ");
                // } while(sel.numCols <= 0 || sel.numCols > currentTable->numCols);

                // sel.colNames = malloc(sizeof(char*) * sel.numCols);
                // // if(sel.numCols < currentTable->numCols) {
                // for(int i = 0; i < sel.numCols; i++) {

                // }
                // // }
                // // else {
                // //     for(int i = 0; i < sel.numCols; i++) {
                // //         sel.colNames[i] = NULL;
                // //         //sel.colnames[0] = "*";
                // //     }
                // // }

                printf("Would you like to filter your result with a where statement? (yes/no): ");

                if(isYes(yesnoInput()))
                    numWheres = whereInput(currentTable, &whereList, &connectiveList);

                /*
                group by stuff
                */

                /*
                order by stuff
                */

                printf("Do you want to omit duplicate values in this select? (yes/no): ");

                if(isYes(yesnoInput()))
                    sel.distinct = 1;
                else
                    sel.distinct = 0;

                numTables++;

                *tables = realloc(*tables, sizeof(Table) * numTables);
                currentTable = &((*tables)[currTableIndex]);

                (*tables)[numTables - 1] = cql_select(*currentTable, sel, numWheres, whereList, connectiveList);

                currentTable = &(*tables)[numTables - 1];
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

                checkDupTableNames(*tables, numTables, currentTable->name, currTableIndex);

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
                            int tempIndex = tableMenu(numTables, *tables);
                            if(tempIndex > -1) {
                                currTableIndex = tempIndex;
                                currentTable = &(*tables)[currTableIndex];
                                printf("Here is your current table:\n");
                                printTable(*currentTable);
                            }
                            else
                                break;
                        }

                        printf("How many columns would you like to provide values for? (0-%d) (numbers < 0 = cancel): ", currentTable->numCols);
                        do {
                            scanfWell("%d", &numThings);
                            if(numThings > currentTable->numCols)
                                printf("Your current table doesn't have that many columns. Try again: ");
                        } while(numThings > currentTable->numCols);

                        if(numThings < 0)
                            break;
                        else {
                            nameList = malloc(sizeof(char*) * numThings);
                            valueList = malloc(sizeof(void*) * numThings);
                            if(numThings < currentTable->numCols) {

                                int breakTime = 0;
                                int i;

                                for(i = 0; i < numThings; i++) {
                                    nameList[i] = malloc(sizeof(char) * MAX_LEN);

                                    do {
                                        printf("Name for column to provide value for #%d ('\\x' = cancel): ", i + 1);
                                        fgetsUntil(nameList[i], MAX_LEN);
                                        if(strcmp(nameList[i], "\\x") != 0 && nameToCol(currentTable, nameList[i], NULL).type == -1)
                                            continue;
                                        else
                                            break;
                                    } while(1);

                                    if(strcmp(nameList[i], "\\x") == 0) {
                                        breakTime = 1;
                                        break;
                                    }

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
                                            if(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"))
                                                printf("Please input 'TRUE' or 'FALSE': ");
                                        } while(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"));

                                        if(equalsIgnoreCase(temp, "TRUE") || equalsIgnoreCase(temp, "T"))
                                            sscanf("1", "%d", (int*)valueList[i]);
                                        else
                                            sscanf("0", "%d", (int*)valueList[i]);
                                    }
                                    else if(nameToCol(currentTable, nameList[i], NULL).type == DATE) {
                                        printf("DATE datatype functionality coming soon.\n");
                                    }
                                }
                                if(breakTime) {
                                    for(int j = 0; j < i; j++) {
                                        free(nameList[j]);
                                        free(valueList[j]);
                                    }
                                    free(nameList);
                                    free(valueList);
                                    nameList = NULL;
                                    valueList = NULL;
                                    break;
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
                                            if(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"))
                                                printf("Please input 'TRUE' or 'FALSE': ");
                                        } while(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"));

                                        if(equalsIgnoreCase(temp, "TRUE") || equalsIgnoreCase(temp, "T"))
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
                            printf("Which row would you like to insert into? (1-%d) (0 = cancel): ", currentTable->numRows + 1);
                            do {
                                scanfWell("%d", &rowNum);
                                if(rowNum < 0 || rowNum > currentTable->numRows + 1)
                                    printf("Please input a valid row number. (1-%d) (0 = cancel): ", currentTable->numRows + 1);
                            } while(rowNum < 0 || rowNum > currentTable->numRows + 1);

                            if(rowNum > 0)
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
                            int tempIndex = tableMenu(numTables, *tables);
                            if(tempIndex > -1) {
                                currTableIndex = tempIndex;
                                currentTable = &(*tables)[currTableIndex];
                                printf("Here is your current table:\n");
                                printTable(*currentTable);
                            }
                            else
                                break;
                        }

                        int colType;

                        printf("Please input the name of the new column ('\\x' = cancel): ");
                        do {
                            fgetsUntil(colName, MAX_LEN);
                            if(strcmp(colName, "\\x") != 0 && !checkInvalidName(colName))
                                printf("Please input a name without prohibited characters/words: ");
                        } while(strcmp(colName, "\\x") != 0 && !checkInvalidName(colName));

                        if(strcmp(colName, "\\x") == 0)
                            break;

                        printf("What type should this column be?:\n");
                        colType = typeInput();

                        void* defaultVal;
                        char* foreignKeyName;
                        char* attrs = attrInputByType(colType, &defaultVal, &foreignKeyName);

                        printf("How many rows would you like to provide values for? (0-%d) (numbers < 0 = cancel): ", currentTable->numRows);
                        do {
                            scanfWell("%d", &numThings);
                            if(numThings > currentTable->numRows)
                                printf("Your current table doesn't have that many rows. Try again: ");
                        } while(numThings > currentTable->numRows);

                        if(numThings < 0)
                            break;
                        else if(numThings > 0) {
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
                                            if(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"))
                                                printf("Please input 'TRUE' or 'FALSE': ");
                                        } while(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"));

                                        if(equalsIgnoreCase(temp, "TRUE") || equalsIgnoreCase(temp, "T"))
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
                                            if(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"))
                                                printf("Please input 'TRUE' or 'FALSE': ");
                                        } while(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"));

                                        if(equalsIgnoreCase(temp, "TRUE") || equalsIgnoreCase(temp, "T"))
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
                            printf("Which column position would you like to insert into? (A-%s): ", intToLetter(currentTable->numCols + 1));
                            do {
                                fgetsUntil(colString, MAX_LEN);
                                colPos = letterToInt(colString) - 1;
                                if(colPos < 0 || colPos > currentTable->numCols)
                                    printf("Please input a valid column position. (A-%s): ", intToLetter(currentTable->numCols + 1));
                            } while(colPos < 0 || colPos > currentTable->numCols);

                            insertIntoCol(currentTable, colName, colType, numThings, numList, valueList, attrs, defaultVal, foreignKeyName, colString);
                            setForeignKeyPointer(&currentTable->cols[colPos], numTables, *tables);
                        }
                        else {
                            insertCol(currentTable, colName, colType, numThings, numList, valueList, attrs, defaultVal, foreignKeyName);
                            setForeignKeyPointer(&currentTable->cols[currentTable->numCols - 1], numTables, *tables);
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
                if(numTables <= 0) {
                    printf("There are no tables to update.\n");
                    break;
                }
                if(currentTable == NULL) {
                    printf("Which table would you like to update?\n");
                    int tempIndex = tableMenu(numTables, *tables);
                    if(tempIndex > -1) {
                        currTableIndex = tempIndex;
                        currentTable = &(*tables)[currTableIndex];
                        printf("Here is your current table:\n");
                        printTable(*currentTable);
                    }
                    else
                        break;
                }

                switch(menuChoices[1]) {
                    case 1:
                        // "1. UPDATE a existing values in current table"
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
                            int breakTime = 0;
                            do {
                                numUpdCols++;
                                printf("Please input the name of a column you would like to update the value(s) of ('\\x' = cancel): ");
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
                                    if(strcmp(nameList[numUpdCols - 1], "\\x") != 0) {
                                        nameToCol(currentTable, nameList[numUpdCols - 1], &colIndex);
                                        if(colIndex == -1)
                                            printf("That column does not exist. Please try again: ");
                                    }
                                } while(colIndex == -1);
                                if(strcmp(nameList[numUpdCols - 1], "\\x") == 0) {
                                    breakTime = 1;
                                    break;
                                }
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
                                        if(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"))
                                            printf("Please input 'TRUE' or 'FALSE': ");
                                    } while(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"));

                                    if(equalsIgnoreCase(temp, "TRUE") || equalsIgnoreCase(temp, "T"))
                                        sscanf("1", "%d", (int*)valueList[numUpdCols - 1]);
                                    else
                                        sscanf("0", "%d", (int*)valueList[numUpdCols - 1]);
                                }
                                else if(colType == DATE) {
                                    printf("DATE datatype functionality coming soon.\n");
                                }

                                if(numUpdCols + 1 <= currentTable->numCols) {
                                    printf("Would you like to add another column to have its values updated? (yes/no): ");
                                }

                            } while(isYes(yesnoInput()) && numUpdCols + 1 <= currentTable->numCols);

                            if(breakTime == 0) {
                                numWheres = whereInput(currentTable, &whereList, &connectiveList);

                                update(currentTable, numUpdCols, nameList, valueList, numWheres, whereList, connectiveList);
                            }

                            for(int i = 0; i < numUpdCols; i++) {
                                if(nameList && nameList[i])
                                    free(nameList[i]);
                                if(valueList && valueList[i])
                                    free(valueList[i]);
                            }
                            if(nameList)
                                free(nameList);
                            if(valueList)
                                free(valueList);
                            nameList = NULL;
                            valueList = NULL;
                        }
                        else {
                            int* colNums = NULL;
                            int numColsChosen = 0;

                            numColsChosen = colPosInput(&colNums, currentTable->numCols);

                            if(numColsChosen < 0)
                                break;

                            int* rowNums = NULL;
                            int numRowsChosen = 0;

                            numRowsChosen = rowNumInput(&rowNums, currentTable->numRows);

                            if(numRowsChosen < 0)
                                break;

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
                                            if(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"))
                                                printf("Please input 'TRUE' or 'FALSE': ");
                                        } while(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"));
                                        if(equalsIgnoreCase(temp, "TRUE") == 0 || equalsIgnoreCase(temp, "T"))
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

                                if(currentTable->cols[colNums[i]].isPrimaryKey)
                                    deleteDuplicateValues(&currentTable->cols[colNums[i]]);
                                if(currentTable->cols[colNums[i]].hasForeignKey)
                                    deleteInvalidFKeyVals(&currentTable->cols[colNums[i]]);

                            }

                            if(colNums != NULL)
                                free(colNums);
                            if(rowNums != NULL)
                                free(rowNums);

                        }
                        break;
                    case 2:
                        //"2. UPDATE attributes of column in current table"
                        printf("Please input the name of a column you would like to update the attributes of ('\\x' = cancel): ");
                        char* colName = malloc(sizeof(char) * MAX_LEN);
                        int colIndex;
                        do {
                            fgetsUntil(colName, MAX_LEN);
                            if(strcmp(colName, "\\x") != 0) {
                                nameToCol(currentTable, colName, &colIndex);
                                if(colIndex == -1)
                                    printf("That column does not exist. Please try again: ");
                            }
                        } while(strcmp(colName, "\\x") != 0 && colIndex == -1);

                        if(strcmp(colName, "\\x") == 0) {
                            free(colName);
                            break;
                        }
                        nameToCol(currentTable, colName, &colIndex);
                        free(colName);
                        attrInputByCol(&currentTable->cols[colIndex]);
                        printf("HI\n");
                        setForeignKeyPointer(&currentTable->cols[colIndex], numTables, *tables);
                        printf("BYE\n");
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

                    int tempIndex = tableMenu(numTables, *tables);
                    if(tempIndex > -1) {
                        currTableIndex = tempIndex;
                        currentTable = &(*tables)[currTableIndex];
                        printf("Here is your current table:\n");
                        printTable(*currentTable);
                    }
                    else
                        break;
                }

                switch(menuChoices[1]) {
                    case 1:
                        // "1. MOVE a row to new position in current table"
                        printf("Please input the number of the row you would like to move (1-%d) (0 = cancel): ", currentTable->numRows);
                        do {
                            scanfWell("%d", &rowNum);
                            if(--rowNum < -1 || rowNum > currentTable->numRows - 1)
                                printf("Please input a number between 1 and %d (0 = cancel): ", currentTable->numRows);
                        } while(rowNum < -1 || rowNum > currentTable->numRows - 1);

                        if(rowNum == -1)
                            break;

                        if(currentTable->numRows > 1) {

                            int newPos;

                            printf("Which position would you like to insert this row into? (1-%d): ", currentTable->numRows);
                            do {
                                scanfWell("%d", &newPos);
                                if(--newPos < 0 || newPos > currentTable->numRows - 1)
                                    printf("Please input a number between 1 and %d (0 = cancel): ", currentTable->numRows);
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
                                            currentTable->cols[i].values[j].val.CHAR = strdup(currentTable->cols[i].values[j + 1].val.CHAR);
                                            currentTable->cols[i].values[j].isNULL = currentTable->cols[i].values[j + 1].isNULL;
                                        }
                                    }
                                    else {
                                        for(int j = rowNum; j > newPos; j--) {
                                            currentTable->cols[i].values[j].val.CHAR = strdup(currentTable->cols[i].values[j - 1].val.CHAR);
                                            currentTable->cols[i].values[j].isNULL = currentTable->cols[i].values[j - 1].isNULL;
                                        }
                                    }
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
                            printf("Please input the position of the column you would like to move (A-%s) ('\\x' = cancel): ", intToLetter(currentTable->numCols));
                            do {
                                fgetsUntil(colString, MAX_LEN);
                                if(strcmp(colString, "\\x") != 0) {
                                    colPos = letterToInt(colString) - 1;
                                    if(colPos < 0 || colPos >= currentTable->numCols)
                                        printf("Please input a valid column position. (A-%s): ", intToLetter(currentTable->numCols));
                                }
                                else
                                    break;
                            } while(colPos < 0 || colPos >= currentTable->numCols);

                            if(strcmp(colString, "\\x") == 0) {
                                free(colString);
                                break;
                            }

                            int newPos;

                            printf("Which position would you like to insert this column into? (A-%s): ", intToLetter(currentTable->numCols));
                            do {
                                fgetsUntil(colString, MAX_LEN);
                                newPos = letterToInt(colString) - 1;
                                if(newPos < 0 || newPos >= currentTable->numCols)
                                    printf("Please input a valid column position. (A-%s): ", intToLetter(currentTable->numCols));
                            } while(newPos < 0 || newPos >= currentTable->numCols);

                            Column dummyCol = copyColumn(currentTable->cols[colPos]);

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
                    printf("Which table would you like to sort?\n");

                    int tempIndex = tableMenu(numTables, *tables);
                    if(tempIndex > -1) {
                        currTableIndex = tempIndex;
                        currentTable = &(*tables)[currTableIndex];
                        printf("Here is your current table:\n");
                        printTable(*currentTable);
                    }
                    else
                        break;
                }

                // "1. SORT rows by the values of a column"
                printf("Please input the name of the column you would like to sort by ('\\x' == cancel): ");

                int colIndex;
                do {
                    fgetsUntil(colName, MAX_LEN);
                    if(strcmp(colName, "\\x") != 0) {
                        nameToCol(currentTable, colName, &colIndex);
                        if(colIndex == -1)
                            printf("That column does not exist. Please try again: ");
                    }
                    else
                        break;
                } while(colIndex == -1);

                if(strcmp(colName, "\\x") == 0)
                    break;

                char ascdesc[MAX_LEN];
                int ascending = 1;
                printf("Would you like the data to be ascending ('asc') or descending ('desc'): ");
                do {
                    fgetsUntil(ascdesc, MAX_LEN);
                    if(!equalsIgnoreCase(ascdesc, "asc") && !equalsIgnoreCase(ascdesc, "desc") && !equalsIgnoreCase(ascdesc, "a") && !equalsIgnoreCase(ascdesc, "d"))
                        printf("Please input 'asc' or 'desc': ");
                } while(!equalsIgnoreCase(ascdesc, "asc") && !equalsIgnoreCase(ascdesc, "desc") && !equalsIgnoreCase(ascdesc, "a") && !equalsIgnoreCase(ascdesc, "d"));

                if(equalsIgnoreCase(ascdesc, "desc") || equalsIgnoreCase(ascdesc, "d"))
                    ascending = 0;

                sortTableByCol(currentTable, colName, ascending);
                break;

            case 10:
                //"10. JOIN"
                printf("JOIN functionality not yet implemented.\n");
                break;

            case 11:
                //"11. COPY"
                if(numTables <= 0) {
                    printf("There are no tables to choose from.\n");
                    break;
                }
                if(currentTable == NULL) {
                    if(menuChoices[1] == 1)
                        printf("Which table would you like to copy a value from?\n");
                    else if(menuChoices[1] == 2)
                        printf("Which table would you like to copy a row from?\n");
                    else if(menuChoices[1] == 3)
                        printf("Which table would you like to copy a column from?\n");
                    else if(menuChoices[1] == 4)
                        printf("Which table would you like to copy?\n");

                    int tempIndex = tableMenu(numTables, *tables);
                    if(tempIndex > -1) {
                        currTableIndex = tempIndex;
                        currentTable = &(*tables)[currTableIndex];
                        printf("Here is your current table:\n");
                        printTable(*currentTable);
                    }
                    else
                        break;
                }

                switch(menuChoices[1]) {

                    case 1: {
                        // "1. COPY a value in current table"
                        char* colString = malloc(sizeof(char) * MAX_LEN);
                        int colPos;
                        printf("Please input the column position of the value you would like to copy. (A-%s) ('\\x' = cancel): ", intToLetter(currentTable->numCols));
                        do {
                            fgetsUntil(colString, MAX_LEN);
                            if(strcmp(colString, "\\x") != 0) {
                                colPos = letterToInt(colString) - 1;
                                if(colPos < 0 || colPos >= currentTable->numCols)
                                    printf("Please input a valid column position. (A-%s): ", intToLetter(currentTable->numCols));
                            }
                            else
                                break;
                        } while(colPos < 0 || colPos >= currentTable->numCols);

                        if(strcmp(colString, "\\x") == 0) {
                            free(colString);
                            break;
                        }

                        printf("Please input the row number of the value you would like to copy. (1-%d) (0 = cancel): ", currentTable->numRows);
                        do {
                            scanfWell("%d", &rowNum);
                            if(--rowNum < -1 || rowNum > currentTable->numRows - 1)
                                printf("Please input a number between 1 and %d (0 = cancel): ", currentTable->numRows);
                        } while(rowNum < -1 || rowNum > currentTable->numRows - 1);

                        if(rowNum == -1) {
                            free(colString);
                            break;
                        }

                        if(valCopy != NULL) {
                            free(valCopy);
                            valCopy = NULL;
                        }

                        printf("Successfully copied value '");

                        if(!currentTable->cols[colPos].values[rowNum].isNULL) {
                            valCopyType = currentTable->cols[colPos].type;
                            if(currentTable->cols[colPos].type == INTEGER) {
                                valCopy = malloc(sizeof(int));
                                memcpy(valCopy, &currentTable->cols[colPos].values[rowNum].val.INTEGER, sizeof(int));
                                printf("%d", *(int*)valCopy);
                            }
                            else if(currentTable->cols[colPos].type == DECIMAL) {
                                valCopy = malloc(sizeof(double));
                                memcpy(valCopy, &currentTable->cols[colPos].values[rowNum].val.DECIMAL, sizeof(double));
                                printf("%lf", *(double*)valCopy);
                            }
                            else if(currentTable->cols[colPos].type == CHAR) {
                                valCopy = strdup(currentTable->cols[colPos].values[rowNum].val.CHAR);
                                printf("%s", (char*)valCopy);
                            }
                            else if(currentTable->cols[colPos].type == BOOL) {
                                valCopy = malloc(sizeof(int));
                                memcpy(valCopy, &currentTable->cols[colPos].values[rowNum].val.BOOL, sizeof(int));
                                if(*(int*)valCopy == 1)
                                    printf("TRUE");
                                else
                                    printf("FALSE");
                            }
                            else if(currentTable->cols[colPos].type == DATE) {
                                printf("DATE datatype not fully implemented yet.\n");
                            }
                        }
                        else {
                            valCopyType = -1;
                            printf("NULL");
                        }

                        printf("'\n");
                        break;
                    }

                    case 2:
                        // "2. COPY row in current table"
                        printf("Which row would you like to copy? (1-%d) (0 = cancel): ", currentTable->numRows);
                        do {
                            scanfWell("%d", &rowNum);
                            if(--rowNum < -1 || rowNum > currentTable->numRows - 1)
                                printf("Please input a number between 1 and %d (0 = cancel): ", currentTable->numRows);
                        } while(rowNum < -1 || rowNum > currentTable->numRows - 1);

                        if(rowNum == -1)
                            break;

                        rowCopy = copyRow(currentTable, rowNum);
                        rowCopyLength = currentTable->numCols;
                        printf("Row #%d copied:\n", rowNum + 1);

                        printLoneRow(rowCopy, rowCopyLength);

                        break;

                    case 3: {
                        // "3. COPY column in current table"
                        char* colString = malloc(sizeof(char) * MAX_LEN);
                        int colPos;
                        printf("Please input the position of the column you would like to copy. (A-%s) ('\\x' = cancel): ", intToLetter(currentTable->numCols));
                        do {
                            fgetsUntil(colString, MAX_LEN);
                            if(strcmp(colString, "\\x") != 0) {
                                colPos = letterToInt(colString) - 1;
                                if(colPos < 0 || colPos >= currentTable->numCols)
                                    printf("Please input a valid column position. (A-%s): ", intToLetter(currentTable->numCols));
                            }
                            else
                                break;
                        } while(colPos < 0 || colPos >= currentTable->numCols);

                        if(strcmp(colString, "\\x") == 0) {
                            free(colString);
                            break;
                        }

                        colCopy = copyColumn(currentTable->cols[colPos]);

                        printf("Column %s copied:\n", colString);

                        printColumn(colCopy);

                        free(colString);

                        break;
                    }
                    case 4:
                        // "4. Make a COPY of current table"
                        numTables++;
                        *tables = realloc(*tables, sizeof(Table) * numTables);
                        currentTable = &(*tables)[currTableIndex];
                        (*tables)[numTables - 1] = copyTable(*currentTable);

                        printf("Table '%s' copied.\n", currentTable->name);

                        currentTable = &(*tables)[numTables - 1];
                        currTableIndex = numTables - 1;

                        checkDupTableNames(*tables, numTables, currentTable->name, currTableIndex);
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
                        printf("Which table would you like to paste a value into?\n");
                    else if(menuChoices[1] == 2)
                        printf("Which table would you like to paste a row into?\n");
                    else if(menuChoices[1] == 3)
                        printf("Which table would you like to paste a column into?\n");

                    int tempIndex = tableMenu(numTables, *tables);
                    if(tempIndex > -1) {
                        currTableIndex = tempIndex;
                        currentTable = &(*tables)[currTableIndex];
                        printf("Here is your current table:\n");
                        printTable(*currentTable);
                    }
                    else
                        break;
                }

                switch(menuChoices[1]) {

                    case 1:
                        // "1. PASTE copied value into current table"
                        if(valCopy != NULL) {
                            printf("How would you like to select the positions to be pasted into?\n");
                            printf("1. Using column names and a where statement\n");
                            printf("2. Using the coordinate system (column letters and row numbers)\n");
                            printf("0. Cancel\n");
                            printf("Choice: ");
                            do {
                                scanfWell("%d", &menuChoices[1]);
                                if(menuChoices[1] < 0 || menuChoices[1] > 2)
                                    printf("Please input either 1 or 2 (or 0 to cancel): ");
                            } while(menuChoices[1] < 0 || menuChoices[1] > 2);

                            if(menuChoices[1] == 0)
                                break;
                            else if(menuChoices[1] == 1) {
                                int numUpdCols = 0;
                                int breakTime = 0;
                                do {
                                    numUpdCols++;
                                    printf("Please input the name of a column you would like to update the value(s) of ('\\x' = cancel): ");
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

                                    Column tempCol;
                                    do {
                                        fgetsUntil(nameList[numUpdCols - 1], MAX_LEN);
                                        if(strcmp(nameList[numUpdCols - 1], "\\x") != 0) {
                                            tempCol = nameToCol(currentTable, nameList[numUpdCols - 1], &colIndex);
                                            if(colIndex == -1)
                                                printf("That column does not exist. Please try again: ");
                                            else if(tempCol.type != valCopyType) {
                                                printf("That column does not match the type of your copied value. Please enter columns of type '");
                                                printType(valCopyType);
                                                printf("': ");
                                            }
                                        }
                                        else
                                            break;
                                    } while(colIndex == -1 || tempCol.type != valCopyType);

                                    if(strcmp(nameList[numUpdCols - 1], "\\x") == 0) {
                                        for(int i = 0; i < numUpdCols; i++) {
                                            if(nameList[i] != NULL)
                                                free(nameList[i]);
                                            if(valueList[i] != NULL)
                                                free(valueList[i]);
                                        }
                                        free(nameList);
                                        free(valueList);
                                        nameList = NULL;
                                        valueList = NULL;
                                        breakTime = 1;
                                        break;
                                    }

                                    nameList[numUpdCols - 1] = realloc(nameList[numUpdCols - 1], sizeof(char) * (strlen(nameList[numUpdCols - 1]) + 1));

                                    if(valCopyType == INTEGER || valCopyType == BOOL) {
                                        valueList[numUpdCols - 1] = malloc(sizeof(int));
                                        memcpy(valueList[numUpdCols - 1], valCopy, sizeof(int));
                                    }
                                    else if(valCopyType == CHAR) {
                                        valueList[numUpdCols - 1] = strdup(valCopy);
                                    }
                                    else if(valCopyType == DECIMAL) {
                                        valueList[numUpdCols - 1] = malloc(sizeof(double));
                                        memcpy(valueList[numUpdCols - 1], valCopy, sizeof(double));
                                    }
                                    else if(valCopyType == DATE) {
                                        printf("DATE datatype functionality coming soon.\n");
                                    }
                                    else {
                                        valueList[numUpdCols - 1] = NULL;
                                    }

                                    if(numUpdCols + 1 <= currentTable->numCols) {
                                        printf("Would you like to add another column to have its values updated? (yes/no): ");
                                    }

                                } while(isYes(yesnoInput()) && numUpdCols + 1 <= currentTable->numCols);

                                if(breakTime)
                                    break;

                                numWheres = whereInput(currentTable, &whereList, &connectiveList);

                                update(currentTable, numUpdCols, nameList, valueList, numWheres, whereList, connectiveList);

                                for(int i = 0; i < numUpdCols; i++) {
                                    if(nameList[i] != NULL)
                                        free(nameList[i]);
                                    if(valueList[i] != NULL)
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
                                if(numColsChosen == -1) {
                                    if(colNums != NULL)
                                        free(colNums);
                                    break;
                                }

                                int* rowNums = NULL;
                                int numRowsChosen = 0;

                                numRowsChosen = rowNumInput(&rowNums, currentTable->numRows);
                                for(int i = 0; i < numColsChosen; i++) {
                                    if(valCopyType == INTEGER && currentTable->cols[colNums[i]].type == INTEGER) {
                                        for(int j = 0; j < numRowsChosen; j++) {
                                            currentTable->cols[colNums[i]].values[rowNums[j]].isNULL = 0;
                                            currentTable->cols[colNums[i]].values[rowNums[j]].val.INTEGER = *(int*)valCopy;
                                        }
                                    }
                                    else if(valCopyType == CHAR && currentTable->cols[colNums[i]].type == CHAR) {
                                        for(int j = 0; j < numRowsChosen; j++) {
                                            if(currentTable->cols[colNums[i]].values[rowNums[j]].val.CHAR != NULL)
                                                free(currentTable->cols[colNums[i]].values[rowNums[j]].val.CHAR);
                                            currentTable->cols[colNums[i]].values[rowNums[j]].isNULL = 0;
                                            currentTable->cols[colNums[i]].values[rowNums[j]].val.CHAR = strdup((char*)valCopy);
                                        }
                                    }
                                    else if(valCopyType == DECIMAL && currentTable->cols[colNums[i]].type == DECIMAL) {
                                        for(int j = 0; j < numRowsChosen; j++) {
                                            currentTable->cols[colNums[i]].values[rowNums[j]].isNULL = 0;
                                            currentTable->cols[colNums[i]].values[rowNums[j]].val.DECIMAL = *(double*)valCopy;
                                        }
                                    }
                                    else if(valCopyType == BOOL && currentTable->cols[colNums[i]].type == BOOL) {
                                        for(int j = 0; j < numRowsChosen; j++) {
                                            currentTable->cols[colNums[i]].values[rowNums[j]].isNULL = 0;
                                            currentTable->cols[colNums[i]].values[rowNums[j]].val.BOOL = *(int*)valCopy;
                                        }
                                    }
                                    else if(valCopyType == DATE && currentTable->cols[colNums[i]].type == DATE) {
                                        printf("DATE datatype functionality coming soon.\n");
                                    }
                                    else if(valCopyType == -1) {
                                        for(int j = 0; j < numRowsChosen; j++) {
                                            currentTable->cols[colNums[i]].values[rowNums[j]].isNULL = 1;
                                        }
                                    }

                                    if(currentTable->cols[colNums[i]].isPrimaryKey)
                                        deleteDuplicateValues(&currentTable->cols[colNums[i]]);
                                    if(currentTable->cols[colNums[i]].hasForeignKey)
                                        deleteInvalidFKeyVals(&currentTable->cols[colNums[i]]);

                                }

                                if(colNums != NULL)
                                    free(colNums);
                                if(rowNums != NULL)
                                    free(rowNums);

                            }
                        }
                        else
                            printf("You currently do not have a value copied.\n");
                        break;

                    case 2:
                        // "2. PASTE copied row into current table"
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

                                if(isYes(yesnoInput())) {
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

                                        if(isYes(yesnoInput()))
                                            includeMissing = 1;
                                    }

                                    nameList = malloc(sizeof(char*) * (numCommonNames + (rowCopyLength - numCommonNames) * includeMissing));
                                    valueList = malloc(sizeof(void*) * (numCommonNames + (rowCopyLength - numCommonNames) * includeMissing));
                                    int count = 0;

                                    for(int i = 0; i < rowCopyLength; i++) {
                                        if(includeMissing && !containsCol(*currentTable, rowCopy[i].colName)) {
                                            insertCol(currentTable, rowCopy[i].colName, rowCopy[i].type, 0, NULL, NULL, NULL, NULL, NULL);
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
                                        "0. Cancel pasting\n"
                                        "Your choice: ");

                                    do {
                                        scanfWell("%d", &menuChoices[1]);
                                        if(menuChoices[1] < 0 || menuChoices[1] > 2)
                                            printf("Please choose between 1 and %d: ", 2);
                                    } while(menuChoices[1] < 0 || menuChoices[1] > 2);

                                    if(menuChoices[1] == 0) {
                                        if(valueList != NULL) {
                                            for(int i = 0; i < currentTable->numCols; i++)
                                                free(valueList[i]);
                                            free(valueList);
                                        }
                                        valueList = NULL;
                                        break;
                                    }
                                    else if(menuChoices[1] == 2) {
                                        int numColsNeeded = rowCopyLength - currentTable->numCols;
                                        printf("You need %d extra columns.\n", numColsNeeded);

                                        for(int i = 0; i < numColsNeeded; i++)
                                            insertCol(currentTable, rowCopy[currentTable->numCols].colName, rowCopy[currentTable->numCols].type, 0, NULL, NULL, NULL, NULL, NULL);
                                    }
                                }

                                nameList = malloc(sizeof(char*) * currentTable->numCols);

                                for(int i = 0; i < currentTable->numCols;i++) {
                                    nameList[i] = strdup(currentTable->cols[i].name);
                                }
                            }

                            if(proceed) {
                                if(currentTable->numRows > 0) {
                                    printf("Which row would you like to paste into? (1-%d) (0 = cancel): ", currentTable->numRows + 1);
                                    do {
                                        scanfWell("%d", &rowNum);
                                        if(rowNum < 0 || rowNum > currentTable->numRows + 1)
                                            printf("Please input a valid row number. (1-%d) (0 = cancel): ", currentTable->numRows + 1);
                                    } while(rowNum < 0 || rowNum > currentTable->numRows + 1);

                                    if(rowNum > 0)
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
                    case 3:
                        // "3. PASTE copied column into current table"
                        if(colCopy.name != NULL) {
                            if(colCopy.numRows > currentTable->numRows) {
                                printf("How would you like to paste?:\n");
                                printf("1. Shrink column to fit table\n"
                                    "2. Grow table to fit column\n"
                                    "0. Cancel"
                                    "Your choice: ");

                                do {
                                    scanfWell("%d", &menuChoices[1]);
                                    if(menuChoices[1] < 0 || menuChoices[1] > 2)
                                        printf("Please choose between 1 and %d: ", 2);
                                } while(menuChoices[1] < 0 || menuChoices[1] > 2);

                                if(menuChoices[1] == 0)
                                    break;
                                else if(menuChoices[1] == 2) {
                                    int numRowsMissing = colCopy.numRows - currentTable->numRows;
                                    for(int i = 0; i < numRowsMissing; i++)
                                        insertRow(currentTable, 0, NULL, NULL);
                                }
                            }

                            numThings = min(currentTable->numRows, colCopy.numRows);

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

                            char* attrs = malloc(sizeof(char) * 5);
                            void* defaultVal = NULL;
                            char* foreignKeyName;
                            strcpy(attrs, "");
                            if(colCopy.autoIncrement) {
                                strcat(attrs, "A");
                            }
                            if(colCopy.hasForeignKey) {
                                strcat(attrs, "F");
                                foreignKeyName = strdup(colCopy.fKeyName);
                            }
                            if(colCopy.isPrimaryKey) {
                                strcat(attrs, "P");
                            }
                            if(colCopy.notNull) {
                                strcat(attrs, "N");
                            }

                            if(!colCopy.defaultValue.isNULL) {
                                if(colCopy.type == INTEGER) {
                                    defaultVal = malloc(sizeof(int));
                                    memcpy(defaultVal, &colCopy.defaultValue.val.INTEGER, sizeof(int));
                                }
                                else if(colCopy.type == DECIMAL) {
                                    defaultVal = malloc(sizeof(double));
                                    memcpy(defaultVal, &colCopy.defaultValue.val.DECIMAL, sizeof(double));
                                }
                                else if(colCopy.type == CHAR) {
                                    defaultVal = strdup(colCopy.defaultValue.val.CHAR);
                                }
                                else if(colCopy.type == BOOL) {
                                    defaultVal = malloc(sizeof(int));
                                    memcpy(defaultVal, &colCopy.defaultValue.val.BOOL, sizeof(int));
                                }
                                else if(colCopy.type == DATE) {
                                    printf("DATE datatype functionality to be implemented soon.\n");
                                }
                            }

                            char colString[MAX_LEN];
                            int colPos;

                            printf("Which column position would you like to insert into? (A-%s) ('\\x' = cancel): ", intToLetter(currentTable->numCols + 1));
                            do {
                                fgetsUntil(colString, MAX_LEN);
                                if(strcmp(colString, "\\x") != 0) {
                                    colPos = letterToInt(colString) - 1;
                                    if(colPos < 0 || colPos > currentTable->numCols)
                                        printf("Please input a valid column position. (A-%s): ", intToLetter(currentTable->numCols + 1));
                                }
                                else
                                    break;
                            } while(colPos < 0 || colPos > currentTable->numCols);

                            if(strcmp(colString, "\\x") != 0)
                                insertIntoCol(currentTable, colCopy.name, colCopy.type, numThings, numList, valueList, attrs, defaultVal, foreignKeyName, colString);

                            if(valueList != NULL) {
                                for(int i = 0; i < numThings; i++)
                                    free(valueList[i]);
                                free(valueList);
                                free(numList);
                            }
                            valueList = NULL;
                            numList = NULL;
                            free(attrs);
                            if(defaultVal != NULL)
                                free(defaultVal);
                            if(foreignKeyName != NULL)
                                free(foreignKeyName);

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
                    if(menuChoices[1] < 5 && menuChoices[1] > 0) {
                        int tempIndex = tableMenu(numTables, *tables);
                        if(tempIndex > -1) {
                            currTableIndex = tempIndex;
                            currentTable = &(*tables)[currTableIndex];
                            printf("Here is your current table:\n");
                            printTable(*currentTable);
                        }
                        else
                            break;
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
                            printf("0. Cancel\n");
                            printf("Choice: ");
                            do {
                                scanfWell("%d", &menuChoices[1]);
                                if(menuChoices[1] < 0 || menuChoices[1] > 2)
                                    printf("Please input either 0, 1, or 2: ");
                            } while(menuChoices[1] < 0 || menuChoices[1] > 2);

                            if(menuChoices[1] == 0)
                                break;
                            else if(menuChoices[1] == 1) {
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
                            printf("0. Cancel\n");
                            printf("Choice: ");
                            do {
                                scanfWell("%d", &menuChoices[1]);
                                if(menuChoices[1] < 0 || menuChoices[1] > 2)
                                    printf("Please input either 0, 1, or 2: ");
                            } while(menuChoices[1] < 0 || menuChoices[1] > 2);

                            if(menuChoices[1] == 0)
                                break;
                            else if(menuChoices[1] == 1) {

                                printf("Please input the name of the column you would like to delete: ");

                                int colIndex;
                                do {
                                    fgetsUntil(colName, MAX_LEN);
                                    nameToCol(currentTable, colName, &colIndex);
                                    if(colIndex == -1)
                                        printf("That column does not exist. Please try again: ");
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
                            printf("0. Cancel\n");
                            printf("Choice: ");
                            do {
                                scanfWell("%d", &menuChoices[1]);
                                if(menuChoices[1] < 0 || menuChoices[1] > 2)
                                    printf("Please input either 0, 1, or 2: ");
                            } while(menuChoices[1] < 0 || menuChoices[1] > 2);

                            if(menuChoices[1] == 0)
                                break;
                            else if(menuChoices[1] == 1) {
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
                                            printf("That column does not exist. Please try again: ");
                                    } while(colIndex == -1);

                                    nameList[numDelCols - 1] = realloc(nameList[numDelCols - 1], sizeof(char) * (strlen(nameList[numDelCols - 1]) + 1));
                                    valueList[numDelCols - 1] = NULL;

                                    if(numDelCols + 1 <= currentTable->numCols) {
                                        printf("Would you like to add another column to have its values deleted? (yes/no): ");
                                    }

                                } while(isYes(yesnoInput()) && numDelCols + 1 <= currentTable->numCols);

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
                            for(int i = currTableIndex; i < numTables; i++)
                                (*tables)[i] = (*tables)[i + 1];

                            currTableIndex = -1;
                            currentTable = NULL;
                        }
                        break;
                    case 5: {
                        // "5. DELETE all tables with 'Selected from' in their name"
                        int verified = 0;
                        int found = 0;
                        for(int i = 0; i < numTables; i++) {
                            if(strstr((*tables)[i].name, "Selected from")) {
                                found = 1;
                                if(verified == 1 || verifyDelete()) {
                                    verified = 1;
                                    freeTable(&(*tables)[i]);

                                    for(int j = i; j < numTables; j++)
                                        (*tables)[j] = (*tables)[j + 1];

                                    if(currTableIndex == i) {
                                        currTableIndex = -1;
                                        currentTable = NULL;
                                    }
                                    numTables--;
                                    i--;
                                }
                                else {
                                    verified = -1;
                                }
                            }
                        }

                        if(!found)
                            printf("There are no tables in your database containing 'Selected from' in its name.\nNothing was deleted.\n");

                        break;
                    }
                    case 6: {
                        // "6. DELETE all tables with 'Copy of' in their name"
                        int verified = 0;
                        int found = 0;
                        for(int i = 0; i < numTables; i++) {
                            if(strstr((*tables)[i].name, "Copy of")) {
                                found = 1;
                                if(verified == 1 || verifyDelete()) {
                                    verified = 1;
                                    freeTable(&(*tables)[i]);

                                    for(int j = i; j < numTables; j++)
                                        (*tables)[j] = (*tables)[j + 1];

                                    if(currTableIndex == i) {
                                        currTableIndex = -1;
                                        currentTable = NULL;
                                    }
                                    numTables--;
                                    i--;
                                }
                                else {
                                    verified = -1;
                                }
                            }
                        }

                        if(!found)
                            printf("There are no tables in your database containing 'Copy of' in its name.\nNothing was deleted.\n");

                        break;
                    }
                    case 7:
                        // "7. DELETE database"
                        if(verifyDelete()) {
                            for(int i = 0; i < numTables; i++)
                                freeTable(&(*tables)[i]);

                            free(*tables);

                            *tables = NULL;

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
                        do {
                            printf("Please input the name of the table you would like to import ('\\x' = cancel): ");
                            fgetsUntil(tableName, MAX_LEN);
                            if(strcmp(tableName, "\\x") == 0)
                                break;

                            printf("Please input the name of the file you want to import the table '%s' from.\n(can be of any extension, including .db and .sql)\n('\\b' = back, '\\x' = cancel): ", tableName);
                            fgetsUntil(filename, MAX_LEN);
                        } while(strcmp(filename, "\\b") == 0);

                        if(strcmp(filename, "\\x") == 0)
                            break;

                        if(!fopen(filename, "r")) {
                            do {
                                printf("File with name '%s' not found. Please input an existing file's name, or type '\\x' to cancel.", filename);
                                fgetsUntil(filename, MAX_LEN);
                            } while(strcmp(filename, "\\x") != 0 && !fopen(filename, "r"));
                        }

                        if(strcmp(filename, "\\x") != 0) {
                            printf("YEET\n");
                            Table* importedTable = importTable(tableName, filename);
                            printf("HEHE\n");
                            if(importedTable) {
                                numTables++;
                                if(numTables == 1)
                                    *tables = malloc(sizeof(Table));
                                else
                                    *tables = realloc(*tables, sizeof(Table) * numTables);
                                (*tables)[numTables - 1] = *importedTable;
                                checkDupTableNames(*tables, numTables, (*tables)[numTables - 1].name, numTables - 1);
                                currentTable = &(*tables)[numTables - 1];
                                currTableIndex = numTables - 1;
                                for(int i = 0; i < numTables; i++)
                                    for(int j = 0; j < (*tables)[i].numCols; j++)
                                        if((*tables)[i].cols[j].hasForeignKey && (*tables)[i].cols[j].fKeyPointer == NULL)
                                            setForeignKeyPointer(&(*tables)[i].cols[j], numTables, *tables);
                            }
                        }
                        break;
                    }
                    case 2: {
                        // "2. IMPORT database from file"
                        char filename[MAX_LEN];
                        printf("Please input the name of the file you want to import the database from.\n(can be of any extension, including .db and .sql)\n('\\x' = cancel): ");
                        fgetsUntil(filename, MAX_LEN);
                        if(strcmp(filename, "\\x") == 0)
                            break;

                        if(!fopen(filename, "r")) {
                            do {
                                printf("File with name '%s' not found. Please input an existing file's name, or type '\\x' to cancel: ", filename);
                                fgetsUntil(filename, MAX_LEN);
                            } while(strcmp(filename, "\\x") != 0 && !fopen(filename, "r"));
                        }

                        if(strcmp(filename, "\\x") != 0) {
                            printf("Are you sure you want to overwrite the current database? (yes/no): ");

                            if(isYes(yesnoInput())) {
                                Table* newTables;
                                int numTablesLoaded = importDatabase(filename, &newTables);

                                if(numTablesLoaded > 0) {
                                    for(int i = 0; i < numTables; i++)
                                        freeTable(&(*tables)[i]);
                                    if(*tables != NULL)
                                        free(*tables);
                                    currentTable = NULL;
                                    currTableIndex = -1;
                                    numTables = numTablesLoaded;
                                    *tables = newTables;
                                    for(int i = 0; i < numTables; i++)
                                        for(int j = 0; j < (*tables)[i].numCols; j++)
                                            if((*tables)[i].cols[j].hasForeignKey && (*tables)[i].cols[j].fKeyPointer == NULL)
                                                setForeignKeyPointer(&(*tables)[i].cols[j], numTables, *tables);
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
                            int tempIndex = tableMenu(numTables, *tables);
                            if(tempIndex > -1) {
                                currTableIndex = tempIndex;
                                currentTable = &(*tables)[currTableIndex];
                                printf("Here is your current table:\n");
                                printTable(*currentTable);
                            }
                            else
                                break;
                        }

                        int saveChoice;
                        char filename[MAX_LEN];
                        int trunc;
                        do {
                            saveChoice = 1;
                            trunc = 0;

                            printf("Please input the name of the file you want to save '%s' to.\n(can be of any extension, including .db and .sql)\n('\\x' = cancel): ", currentTable->name);
                            fgetsUntil(filename, MAX_LEN);
                            if(strcmp(filename, "\\x") == 0) {
                                saveChoice = 0;
                                break;
                            }

                            if(fopen(filename, "r")) {

                                printf("\nHow would you like to save your data?\n");
                                printf("1. Save current table along with the other contents of the given file\n"
                                    "2. Delete all records in the given file and save your current table afterwards\n"
                                    "3. Give a new file name\n"
                                    "0. Cancel\n"
                                    "Choice: ");

                                do {
                                    scanfWell("%d", &saveChoice);
                                    if(saveChoice < 0 || saveChoice > 3)
                                        printf("Please input a number between 0 & 3: ");
                                } while(saveChoice < 0 || saveChoice > 3);

                                if(saveChoice == 2)
                                    trunc = 1;
                            }
                        } while(saveChoice == 3);

                        if(saveChoice != 0) {
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

                            printf("Please input the name of the file you want to save the database to.\n(can be of any extension, including .db and .sql)\n('\\x' = cancel): ");
                            fgetsUntil(filename, MAX_LEN);
                            if(strcmp(filename, "\\x") == 0) {
                                saveChoice = 0;
                                break;
                            }

                            if(fopen(filename, "r")) {

                                printf("\nHow would you like to save your data?\n");
                                printf("1. Save database along with the other contents of the given file.\n"
                                    "2. Delete all records in the given file and save your database afterwards.\n"
                                    "3. Give a new file name.\n"
                                    "0. Cancel.\n"
                                    "Choice: ");

                                do {
                                    scanfWell("%d", &saveChoice);
                                    if(saveChoice < 0 || saveChoice > 3)
                                        printf("Please input a number between 0 & 3: ");
                                } while(saveChoice < 0 || saveChoice > 3);

                                if(saveChoice == 2)
                                    truncate(filename, 0);

                            }

                        } while(saveChoice == 3);

                        if(saveChoice != 0)
                            for(int i = 0; i < numTables; i++)
                                exportTable((*tables)[i], filename, 0);

                        printf("\nDatabase saved successfully to %s.\n", filename);
                        break;
                    }
                }
                break;

                /*
                perhaps incorporate a where or select saving system, allowing the user to swiftly use frequently used where or select statements.
                I would save these in a separate.cql file separate from the.sql file that can be converted to.db.
                I could add other useful CQL specific saves later on.
                    */

            case 0:
                //"0. EXIT"
                switch(menuChoices[1]) {
                    case 1: {
                        // "1. SAVE & EXIT"
                        char filename[MAX_LEN];
                        int saveChoice;
                        do {
                            saveChoice = 1;

                            printf("Please input the name of the file you want to save the database to.\n(can be of any extension, including .db and .sql)\n('\\x' = cancel): ");
                            fgetsUntil(filename, MAX_LEN);
                            if(strcmp(filename, "\\x") == 0) {
                                saveChoice = 0;
                                break;
                            }

                            if(fopen(filename, "r")) {

                                printf("\nHow would you like to save your data?\n");
                                printf("1. Save database along with the other contents of the given file.\n"
                                    "2. Delete all records in the given file and save your database afterwards.\n"
                                    "3. Give a new file name.\n"
                                    "0. Cancel.\n"
                                    "Choice: ");

                                do {
                                    scanfWell("%d", &saveChoice);
                                    if(saveChoice < 0 || saveChoice > 3)
                                        printf("Please input a number between 0 & 3: ");
                                } while(saveChoice < 0 || saveChoice > 3);

                                if(saveChoice == 2)
                                    truncate(filename, 0);

                            }

                        } while(saveChoice == 3);

                        if(saveChoice != 0) {
                            for(int i = 0; i < numTables; i++)
                                exportTable((*tables)[i], filename, 0);

                            printf("Saving");
                            for(int i = 0; i < 3; i++) {
                                cql_sleep(750);
                                printf(".");
                                fflush(stdout);
                            }
                            cql_sleep(750);
                            printf("\nDatabase saved successfully to %s.\n", filename);
                            cql_sleep(250);
                        }
                        else
                            menuChoices[0] = 1;
                        break;
                    }
                    case 2:
                        // "2. EXIT WITHOUT SAVING"
                        printf("Exiting Program.\n");
                        printf("Are you sure you want to exit and lose your changes? (yes/no): ");
                        if(isNo(yesnoInput()))
                            menuChoices[0] = 1;
                        break;
                }
                break;

        }

    } while(menuChoices[0] > 0);

    if(menuChoices)
        free(menuChoices);


    // char** nameList = NULL;
    // int* typeList = NULL;
    // void** valueList = NULL;
    // char** attrList = NULL;
    // void** defaultValList = NULL;
    // char** foreignKeyList = NULL;

    // Where* whereList = NULL;
    // int numWheres = 0;
    // char* connectiveList = NULL;
    // int* numList;

    // Select sel;

    // void* valCopy = NULL;
    // int valCopyType = -1;
    // LoneValue* rowCopy = NULL;
    // int rowCopyLength;
    // colCopy.name = NULL;


    return numTables;

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
                printf("1. COPY a value in current table\n"
                    "2. COPY row in current table\n"
                    "3. COPY column in current table\n"
                    "4. Make a COPY of current table\n");
                numOptions = 4;
                break;

            case 12:
                printf("1. PASTE copied value into current table\n"
                    "2. PASTE copied row into current table\n"
                    "3. PASTE copied column into current table\n");
                numOptions = 3;
                break;

            case 13:
                printf("1. DELETE row(s) from current table\n"
                    "2. DELETE column(s) from current table\n"
                    "3. DELETE value(s) from current table\n"
                    "4. DELETE current table\n"
                    "5. DELETE all tables with 'Selected From' in their name\n"
                    "6. DELETE all tables with 'Copy Of' in their name\n"
                    "7. DELETE database\n");
                numOptions = 7;
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
    printf("0. Cancel\n");
    printf("Your choice: ");
    do {
        scanfWell("%d", &tableChoice);
        tableChoice--;
        if(tableChoice < -1 || tableChoice >= numTables)
            printf("Please input a valid table. (1-%d) (0 = cancel): ", numTables);
    } while(tableChoice < -1 || tableChoice >= numTables);

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
            scanfWellNull("%d", (*whereList)[numWheres - 1].searchValue);
        }
        else if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName, NULL).type == CHAR) {
            printf("Please input the string value you are looking for: ");
            (*whereList)[numWheres - 1].searchValue = malloc(sizeof(char) * MAX_LEN);
            fgetsUntil((*whereList)[numWheres - 1].searchValue, MAX_LEN);
            (*whereList)[numWheres - 1].searchValue = realloc((*whereList)[numWheres - 1].searchValue, sizeof(char) * (strlen((*whereList)[numWheres - 1].searchValue) + 1));
        }
        else if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName, NULL).type == DECIMAL) {
            printf("Please input the decimal value you are looking for: ");
            (*whereList)[numWheres - 1].searchValue = malloc(sizeof(double));
            scanfWellNull("%lf", (*whereList)[numWheres - 1].searchValue);
        }
        else if(nameToCol(currentTable, (*whereList)[numWheres - 1].searchColName, NULL).type == BOOL) {
            printf("Please input the boolean value you are looking for: ");

            char temp[MAX_LEN];
            do {
                fgetsUntil(temp, MAX_LEN);
                if(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F") && !equalsIgnoreCase(temp, "NULL"))
                    printf("Please input 'TRUE', 'FALSE', or 'NULL': ");
            } while(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F") && !equalsIgnoreCase(temp, "NULL"));

            if(equalsIgnoreCase(temp, "NULL"))
                (*whereList)[numWheres - 1].searchValue = NULL;
            else {
                (*whereList)[numWheres - 1].searchValue = malloc(sizeof(double));

                if(equalsIgnoreCase(temp, "TRUE") || equalsIgnoreCase(temp, "T"))
                    sscanf("1", "%d", (int*)(*whereList)[numWheres - 1].searchValue);
                else if(equalsIgnoreCase(temp, "FALSE") || equalsIgnoreCase(temp, "F"))
                    sscanf("0", "%d", (int*)(*whereList)[numWheres - 1].searchValue);
                else if(equalsIgnoreCase(temp, "NULL"))
                    sscanf("-1", "%d", (int*)(*whereList)[numWheres - 1].searchValue);
            }
        }

        printf("Would you like to add another where statement? (yes/no): ");

        strcpy(yesno, yesnoInput());

        if(isYes(yesno)) {
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
    } while(isYes(yesno));

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

    int tempPos, colPosI, colPosF, numColsChosen = 0;
    char* input = malloc(sizeof(char) * MAX_LEN);
    char* token;
    char* temp;
    char* colString = malloc(sizeof(char) * MAX_LEN);

    printf("Please input the column letter(s) you would like to choose\n(Eg. 'A' | 'A-E' | 'A, B, D') ('\\x' = cancel): ");

    do {
        colPosI = 0;
        colPosF = 1;
        tempPos = 0;
        fgetsUntil(input, MAX_LEN);

        if(strcmp(input, "\\x") == 0) {
            free(input);
            return -1;
        }

        token = strtok(input, ", \n");
        while(token != NULL) {
            temp = strstr(token, "-");
            if(temp != NULL) {

                strncpy(colString, token, temp - token);
                colString[++temp - token] = '\0';
                colPosI = letterToInt(colString);
                colPosF = letterToInt(temp);
                if(colPosI < 0 || colPosF > numCols || colPosF <= colPosI || colPosI > numCols || colPosF < 0) {
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
                tempPos = letterToInt(token) - 1;
                if(tempPos < 0 || tempPos >= numCols) {
                    printf("Invalid input. Please try again: ");
                    break;
                }
                if(numColsChosen == 0)
                    *colNums = malloc(sizeof(int));
                else
                    *colNums = realloc(*colNums, sizeof(int) * (numColsChosen + 1));

                (*colNums)[numColsChosen++] = tempPos;
            }
            token = strtok(NULL, ", \n");
        }

    } while(colPosI < 0 || colPosF > numCols || colPosF <= colPosI || tempPos < 0 || tempPos >= numCols);

    free(input);
    free(colString);

    return numColsChosen;
}

int rowNumInput(int** rowNums, int numRows) {

    int tempNum, rowNumI, rowNumF, numRowsChosen = 0;
    char* input = malloc(sizeof(char) * MAX_LEN);
    char* token;
    char* temp;
    char* rowString = malloc(sizeof(char) * MAX_LEN);

    printf("Please input the row number(s) you would like to choose\n(Eg. '1' | '2-5' | '1, 3, 6') ('\\x' = cancel): ");

    do {
        tempNum = 0;
        rowNumI = 0;
        rowNumF = 1;
        fgetsUntil(input, MAX_LEN);

        if(strcmp(input, "\\x") == 0) {
            free(input);
            return -1;
        }

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
                tempNum = atoi(token) - 1;
                if(tempNum < 0 || tempNum >= numRows) {
                    printf("Invalid input. Please try again: ");
                    break;
                }
                if(numRowsChosen == 0)
                    *rowNums = malloc(sizeof(int));
                else
                    *rowNums = realloc(*rowNums, sizeof(int) * (numRowsChosen + 1));

                (*rowNums)[numRowsChosen++] = tempNum;
            }
            token = strtok(NULL, ", \n");
        }

    } while(rowNumI < 0 || rowNumF > numRows || rowNumF <= rowNumI || tempNum < 0 || tempNum >= numRows);

    free(input);
    free(rowString);

    return numRowsChosen;
}

void attrInputByCol(Column* col) {
    int input;
    void* defaultVal = NULL;
    char* foreignKeyName = NULL;

    do {
        printf("\nColumn attributes to toggle:\n");
        printf("1. Column Type (Currently: ");
        printType(col->type);
        printf(")\n");
        printf("2. Auto Increment");
        if(col->autoIncrement)
            printf(" (ACTIVE)");
        else
            printf(" (INACTIVE)");
        printf("\n");
        printf("3. Not NULL");
        if(col->notNull)
            printf(" (ACTIVE)");
        else
            printf(" (INACTIVE)");
        printf("\n");
        printf("4. Primary Key");
        if(col->isPrimaryKey)
            printf(" (ACTIVE)");
        else
            printf(" (INACTIVE)");
        printf("\n");
        printf("5. Foreign Key");
        if(col->hasForeignKey)
            printf(" (ACTIVE)");
        else
            printf(" (INACTIVE)");
        printf("\n");
        printf("6. Default Value (Currently '");
        if(col->defaultValue.isNULL)
            printf("NULL");
        else if(col->type == INTEGER)
            printf("%d", col->defaultValue.val.INTEGER);
        else if(col->type == DECIMAL)
            printf("%lf", col->defaultValue.val.DECIMAL);
        else if(col->type == CHAR)
            printf("%s", col->defaultValue.val.CHAR);
        else if(col->type == BOOL)
            printf("%d", col->defaultValue.val.BOOL);
        else if(col->type == DATE)
            printf("DATE datatype support not yet implemented.");
        printf("')\n");
        printf("7. Foreign Key Name (Currently '");
        printValue(col->fKeyName, CHAR);
        printf("')\n");
        printf("0. Done\n"
            "Choice: ");
        do {
            scanfWell("%d", &input);
            if(input < 0 || input > 7)
                printf("Please input a number between 0 & 7: ");
        } while(input < 0 || input > 7);

        if(input == 1) {
            changeColType(col, typeInput());
        }

        else if(input == 2) {
            if(!(col->type == INTEGER || col->type == DECIMAL || col->type == CHAR)) {
                printf("Invalid column type for property 'Auto Increment'\n");
                continue;
            }
            if(!col->autoIncrement) {
                printf("Auto Increment attribute added.\n");
                assignColAttrs(col, "A", NULL, NULL);
            }
            else {
                printf("Auto Increment attribute removed.\n");
                col->autoIncrement = 0;
            }
        }

        else if(input == 3) {

            if(!col->notNull) {

                printf("Not Null attribute added.\n");

                if(col->defaultValue.isNULL) {

                    col->defaultValue.isNULL = 0;

                    printf("Please input a default value (of type ");
                    printType(col->type);
                    printf("): ");

                    if(col->type == INTEGER) {
                        defaultVal = malloc(sizeof(int));
                        scanfWell("%d", defaultVal);
                    }
                    else if(col->type == CHAR) {
                        defaultVal = malloc(sizeof(char) * MAX_LEN);
                        fgetsUntil(defaultVal, MAX_LEN);
                        defaultVal = realloc(defaultVal, sizeof(char) * (strlen(defaultVal) + 1));
                    }
                    else if(col->type == DECIMAL) {
                        defaultVal = malloc(sizeof(double));
                        scanfWell("%lf", defaultVal);
                    }
                    else if(col->type == BOOL) {
                        defaultVal = malloc(sizeof(int));

                        char temp[MAX_LEN];
                        do {
                            fgetsUntil(temp, MAX_LEN);
                            if(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"))
                                printf("Please input 'TRUE' or 'FALSE': ");
                        } while(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"));

                        if(equalsIgnoreCase(temp, "TRUE") || equalsIgnoreCase(temp, "T"))
                            sscanf("1", "%d", (int*)defaultVal);
                        else
                            sscanf("0", "%d", (int*)defaultVal);
                    }
                    else if(col->type == DATE) {
                        printf("DATE datatype functionality coming soon.\n");
                    }

                }
                else {
                    defaultVal = NULL;
                }

                assignColAttrs(col, "N", defaultVal, NULL);

            }
            else {
                printf("Not Null attribute removed.\n");
                col->notNull = 0;
            }

        }
        else if(input == 4) {
            if(!col->isPrimaryKey) {
                printf("Primary Key attribute added.\n");
                assignColAttrs(col, "P", NULL, NULL);
            }
            else {
                col->isPrimaryKey = 0;
                printf("Primary Key attribute removed.\n");
            }
        }
        else if(input == 5) {

            if(!col->hasForeignKey) {
                printf("Foreign Key attribute added.\n");
                if(!col->fKeyName) {
                    printf("Please input the name of the column you would like to be the foreign key (of the form 'TableName.ColumnName'): ");

                    foreignKeyName = malloc(sizeof(char) * MAX_LEN);
                    do {
                        fgetsUntil(foreignKeyName, MAX_LEN);
                        if(!strchr(foreignKeyName, '.'))
                            printf("Please input the name with the formate 'TableName.ColumnName': ");
                    } while(!strchr(foreignKeyName, '.'));
                    foreignKeyName = realloc(foreignKeyName, sizeof(char) * (strlen(foreignKeyName) + 1));
                }

                assignColAttrs(col, "F", NULL, foreignKeyName);

                free(foreignKeyName);

            }
            else {
                col->hasForeignKey = 0;
                if(col->fKeyName)
                    free(col->fKeyName);
                col->fKeyName = NULL;
                printf("Foreign Key attribute removed.\n");
            }

        }
        else if(input == 6) {

            printf("Please input a default value (of type ");
            printType(col->type);
            printf("): ");

            col->defaultValue.isNULL = 0;

            if(col->type == INTEGER) {
                scanfWell("%d", &col->defaultValue.val.INTEGER);
            }
            else if(col->type == CHAR) {
                if(col->defaultValue.val.CHAR) {
                    free(col->defaultValue.val.CHAR);
                    col->defaultValue.val.CHAR = malloc(sizeof(char) * MAX_LEN);
                }
                fgetsUntil(col->defaultValue.val.CHAR, MAX_LEN);
                col->defaultValue.val.CHAR = realloc(col->defaultValue.val.CHAR, sizeof(char) * (strlen(col->defaultValue.val.CHAR) + 1));
            }
            else if(col->type == DECIMAL) {
                scanfWell("%lf", &col->defaultValue.val.DECIMAL);
            }
            else if(col->type == BOOL) {

                char temp[MAX_LEN];
                do {
                    fgetsUntil(temp, MAX_LEN);
                    if(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"))
                        printf("Please input 'TRUE' or 'FALSE': ");
                } while(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"));

                if(equalsIgnoreCase(temp, "TRUE") || equalsIgnoreCase(temp, "T"))
                    sscanf("1", "%d", &col->defaultValue.val.BOOL);
                else
                    sscanf("0", "%d", &col->defaultValue.val.BOOL);
            }
            else if(col->type == DATE) {
                printf("DATE datatype functionality coming soon.\n");
            }

        }
        if(input == 7) {
            if(!col->fKeyName)
                free(col->fKeyName);
            printf("Please input the name of the column you would like to be the foreign key (of the form 'TableName.ColumnName'): ");

            col->fKeyName = malloc(sizeof(char) * MAX_LEN);
            do {
                fgetsUntil(col->fKeyName, MAX_LEN);
                if(!strchr(col->fKeyName, '.'))
                    printf("Please input the name with the formate 'TableName.ColumnName': ");
            } while(!strchr(col->fKeyName, '.'));
            col->fKeyName = realloc(col->fKeyName, sizeof(char) * (strlen(col->fKeyName) + 1));
        }

    } while(input > 0);

    if(defaultVal != NULL)
        free(defaultVal);

}

char* attrInputByType(int colType, void** defaultVal, char** foreignKeyName) {
    int input;

    char* attrList = malloc(sizeof(char) * MAX_LEN);
    strcpy(attrList, "");
    if(defaultVal)
        *defaultVal = NULL;
    if(foreignKeyName)
        *foreignKeyName = NULL;

    do {
        printf("\nColumn attributes to toggle:\n");
        printf("1. Auto Increment");
        if(strchr(attrList, 'A'))
            printf(" (ACTIVE)");
        else
            printf(" (INACTIVE)");
        printf("\n");
        printf("2. Not NULL");
        if(strchr(attrList, 'N'))
            printf(" (ACTIVE)");
        else
            printf(" (INACTIVE)");
        printf("\n");
        printf("3. Primary Key");
        if(strchr(attrList, 'P'))
            printf(" (ACTIVE)");
        else
            printf(" (INACTIVE)");
        printf("\n");
        printf("4. Foreign Key");
        if(strchr(attrList, 'F'))
            printf(" (ACTIVE)");
        else
            printf(" (INACTIVE)");
        printf("\n");
        printf("5. Default Value (Currently '");
        printValue(*defaultVal, colType);
        printf("')\n");
        printf("6. Foreign Key Name (Currently '");
        printValue(*foreignKeyName, CHAR);
        printf("')\n");
        printf("0. Done\n"
            "Choice: ");
        do {
            scanfWell("%d", &input);
            if(input < 0 || input > 6)
                printf("Please input a number between 0 & 6: ");
        } while(input < 0 || input > 6);

        if(input == 1) {
            if(!(colType == INTEGER || colType == DECIMAL || colType == CHAR)) {
                printf("Invalid column type for property 'Auto Increment'\n");
                continue;
            }
            if(!strchr(attrList, 'A')) {
                printf("Auto Increment attribute added.\n");
                strcat(attrList, "A");
            }
            else {
                printf("Auto Increment attribute removed.\n");
                for(int i = 0; i < strlen(attrList); i++)
                    if(attrList[i] == 'A')
                        attrList[i] = '0';
            }
        }

        else if(input == 2) {

            if(!defaultVal) {
                printf("Error: No default value pointer given.\n");
                continue;
            }

            if(!strchr(attrList, 'N')) {
                printf("Not Null attribute added.\n");
                strcat(attrList, "N");
                if(!*defaultVal) {
                    input = 5;
                }
            }
            else {
                printf("Not Null attribute removed.\n");
                for(int i = 0; i < strlen(attrList); i++)
                    if(attrList[i] == 'N')
                        attrList[i] = '0';
            }
        }
        else if(input == 3) {
            if(!strchr(attrList, 'P')) {
                printf("Primary Key attribute added.\n");
                strcat(attrList, "P");
            }
            else {
                printf("Primary Key attribute removed.\n");
                for(int i = 0; i < strlen(attrList); i++)
                    if(attrList[i] == 'P')
                        attrList[i] = '0';
            }
        }
        else if(input == 4) {
            if(!foreignKeyName) {
                printf("Error: No foreign key name pointer given.\n");
                continue;
            }

            if(!strchr(attrList, 'F')) {
                printf("Foreign Key attribute added.\n");
                strcat(attrList, "F");

                if(!*foreignKeyName) {
                    input = 6;
                }
            }
            else {
                printf("Foreign Key attribute removed.\n");
                for(int i = 0; i < strlen(attrList); i++)
                    if(attrList[i] == 'F')
                        attrList[i] = '0';
            }
        }
        if(input == 5) {

            if(!defaultVal) {
                printf("Error: No default value pointer given.\n");
                continue;
            }
            if(*defaultVal)
                free(defaultVal);

            printf("Please input a default value (of type ");
            printType(colType);
            printf("): ");

            if(colType == INTEGER) {
                *defaultVal = malloc(sizeof(int));
                scanfWell("%d", *defaultVal);
            }
            else if(colType == CHAR) {
                *defaultVal = malloc(sizeof(char) * MAX_LEN);
                fgetsUntil(*defaultVal, MAX_LEN);
                *defaultVal = realloc(*defaultVal, sizeof(char) * (strlen(*defaultVal) + 1));
            }
            else if(colType == DECIMAL) {
                *defaultVal = malloc(sizeof(double));
                scanfWell("%lf", *defaultVal);
            }
            else if(colType == BOOL) {
                *defaultVal = malloc(sizeof(int));

                char temp[MAX_LEN];
                do {
                    fgetsUntil(temp, MAX_LEN);
                    if(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"))
                        printf("Please input 'TRUE' or 'FALSE': ");
                } while(!equalsIgnoreCase(temp, "TRUE") && !equalsIgnoreCase(temp, "FALSE") && !equalsIgnoreCase(temp, "T") && !equalsIgnoreCase(temp, "F"));

                if(equalsIgnoreCase(temp, "TRUE") || equalsIgnoreCase(temp, "T"))
                    sscanf("1", "%d", (int*)*defaultVal);
                else
                    sscanf("0", "%d", (int*)*defaultVal);
            }
            else if(colType == DATE) {
                printf("DATE datatype functionality coming soon.\n");
            }
        }
        if(input == 6) {
            if(!foreignKeyName) {
                printf("Error: No foreign key name pointer given.\n");
                continue;
            }
            if(*foreignKeyName)
                free(foreignKeyName);

            printf("Please input the name of the column you would like to be the foreign key (of the form 'TableName.ColumnName'): ");

            *foreignKeyName = malloc(sizeof(char) * MAX_LEN);
            do {
                fgetsUntil(*foreignKeyName, MAX_LEN);
                if(!strchr(*foreignKeyName, '.'))
                    printf("Please input the foreign key column name in the for of 'TableName.ColumnName': ");
            } while(!strchr(*foreignKeyName, '.'));
            *foreignKeyName = realloc(*foreignKeyName, sizeof(char) * (strlen(*foreignKeyName) + 1));
        }
    } while(input > 0);

    return attrList;

}

int changeColType(Column* col, int newType) {
    if(newType == CHAR) {
        if(col->type == DECIMAL) {
            for(int i = 0; i < col->numRows; i++) {
                if(!col->values[i].isNULL) {
                    char* charVal = malloc(sizeof(char) * MAX_LEN);
                    sprintf(charVal, "%lf", col->values[i].val.DECIMAL);
                    col->values[i].val.CHAR = strdup(charVal);
                    free(charVal);
                }
            }
            if(!col->defaultValue.isNULL) {
                char* charVal = malloc(sizeof(char) * MAX_LEN);
                sprintf(charVal, "%lf", col->defaultValue.val.DECIMAL);
                col->defaultValue.val.CHAR = strdup(charVal);
                free(charVal);
            }
        }
        else if(col->type == INTEGER) {
            for(int i = 0; i < col->numRows; i++) {
                if(!col->values[i].isNULL) {
                    char* charVal = malloc(sizeof(char) * MAX_LEN);
                    sprintf(charVal, "%d", col->values[i].val.INTEGER);
                    col->values[i].val.CHAR = strdup(charVal);
                    free(charVal);
                }
            }
            if(!col->defaultValue.isNULL) {
                char* charVal = malloc(sizeof(char) * MAX_LEN);
                sprintf(charVal, "%d", col->defaultValue.val.INTEGER);
                col->defaultValue.val.CHAR = strdup(charVal);
                free(charVal);
            }
        }
        else if(col->type == BOOL) {
            for(int i = 0; i < col->numRows; i++) {
                if(!col->values[i].isNULL) {
                    if(col->values[i].val.BOOL == 1)
                        col->values[i].val.CHAR = strdup("TRUE");
                    else
                        col->values[i].val.CHAR = strdup("FALSE");
                }
            }
            if(!col->defaultValue.isNULL) {
                if(col->defaultValue.val.BOOL == 1)
                    col->defaultValue.val.CHAR = strdup("TRUE");
                else
                    col->defaultValue.val.CHAR = strdup("FALSE");
            }
        }
        col->type = CHAR;
        return 1;
    }
    else if(newType == INTEGER) {
        if(col->type == DECIMAL) {
            for(int i = 0; i < col->numRows; i++)
                if(!col->values[i].isNULL)
                    col->values[i].val.INTEGER = (int)round(col->values[i].val.DECIMAL);
            col->type = INTEGER;
            return 1;
        }
        else if(col->type == CHAR) {
            int validTransfer = 1;

            int* intValues = malloc(sizeof(int) * col->numRows);

            for(int i = 0; i < col->numRows && validTransfer; i++) {
                if(!col->values[i].isNULL) {
                    int success;
                    int temp;
                    success = sscanf(col->values[i].val.CHAR, "%d", &temp);
                    if(success)
                        intValues[i] = temp;
                    else {
                        double tempD;
                        success = sscanf(col->values[i].val.CHAR, "%lf", &tempD);
                        if(success)
                            intValues[i] = (int)tempD;
                        else
                            validTransfer = 0;
                    }
                }
            }

            if(validTransfer) {
                for(int i = 0; i < col->numRows; i++) {
                    if(!col->values[i].isNULL) {
                        free(col->values[i].val.CHAR);
                        col->values[i].val.INTEGER = intValues[i];
                    }
                }

                free(intValues);
                col->type = INTEGER;
                return 1;
            }
            free(intValues);
            return 0;
        }
        else if(col->type == BOOL) {
            col->type = INTEGER;
            return 1;
        }
    }
    else if(newType == DECIMAL) {
        if(col->type == INTEGER) {
            for(int i = 0; i < col->numRows; i++)
                if(!col->values[i].isNULL)
                    col->values[i].val.DECIMAL = (double)round(col->values[i].val.INTEGER);
            col->type = DECIMAL;
            return 1;
        }
        else if(col->type == CHAR) {
            int validTransfer = 1;

            double* doubValues = malloc(sizeof(double) * col->numRows);

            for(int i = 0; i < col->numRows && validTransfer; i++) {
                if(!col->values[i].isNULL) {
                    int success;
                    double temp;
                    success = sscanf(col->values[i].val.CHAR, "%lf", &temp);
                    if(success)
                        doubValues[i] = temp;
                    else
                        validTransfer = 0;
                }
            }

            if(validTransfer) {
                for(int i = 0; i < col->numRows; i++) {
                    if(!col->values[i].isNULL) {
                        free(col->values[i].val.CHAR);
                        col->values[i].val.DECIMAL = doubValues[i];
                    }
                }

                free(doubValues);
                col->type = DECIMAL;
                return 1;
            }
            free(doubValues);
            return 0;
        }
        else if(col->type == BOOL) {
            for(int i = 0; i < col->numRows; i++)
                if(!col->values[i].isNULL)
                    col->values[i].val.DECIMAL = (double)col->values[i].val.BOOL;
            col->type = DECIMAL;
            return 1;
        }
    }
    else if(newType == BOOL) {
        if(col->type == DECIMAL) {
            for(int i = 0; i < col->numRows; i++) {
                if(!col->values[i].isNULL) {
                    if(col->values[i].val.DECIMAL > 0)
                        col->values[i].val.BOOL = 1;
                    else
                        col->values[i].val.BOOL = 0;
                }
            }
            col->type = BOOL;
            return 1;
        }
        else if(col->type == CHAR) {
            int validTransfer = 1;
            int* boolValues = malloc(sizeof(int) * col->numRows);

            for(int i = 0; i < col->numRows && validTransfer; i++) {
                if(!col->values[i].isNULL) {
                    if(equalsIgnoreCase(col->values[i].val.CHAR, "TRUE") || equalsIgnoreCase(col->values[i].val.CHAR, "T"))
                        boolValues[i] = 1;
                    else if(equalsIgnoreCase(col->values[i].val.CHAR, "FALSE") || equalsIgnoreCase(col->values[i].val.CHAR, "F"))
                        boolValues[i] = 0;
                    else
                        validTransfer = 0;
                }
            }

            if(validTransfer) {
                for(int i = 0; i < col->numRows; i++) {
                    if(!col->values[i].isNULL) {
                        free(col->values[i].val.CHAR);
                        col->values[i].val.BOOL = boolValues[i];
                    }
                }

                free(boolValues);
                col->type = BOOL;
                return 1;
            }
            free(boolValues);
            return 0;
        }
        else if(col->type == INTEGER) {
            for(int i = 0; i < col->numRows; i++) {
                if(!col->values[i].isNULL) {
                    if(col->values[i].val.INTEGER > 0)
                        col->values[i].val.BOOL = 1;
                    else
                        col->values[i].val.BOOL = 0;
                }
            }
            col->type = BOOL;
            return 1;
        }
    }
    else if(newType == DATE) {
        printf("DATE datatype yet to be implemented.\n");
        return 0;
    }
    return 0;
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

void printValue(void* value, int type) {
    if(value == NULL)
        printf("NULL");
    else if(type == INTEGER) {
        printf("%d", *((int*)value));
    }
    else if(type == DECIMAL) {
        printf("%lf", *((double*)value));
    }
    else if(type == CHAR) {
        printf("%s", (char*)value);
    }
    else if(type == BOOL) {
        if(*((int*)value) == 1)
            printf("TRUE");
        else
            printf("FALSE");
    }
    else if(type == DATE) {
        printf("DATE datatype yet to be implemented.");
    }
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
    else if(equalsIgnoreCase(type, "NULL"))
        return -1;
    else
        return -2;
}

int verifyDelete(void) {

    printf("Are you sure you wish do delete this data? (yes/no): ");

    return isYes(yesnoInput());

}

void checkDupTableNames(Table* tables, int numTables, char* nameToCheck, int newNameIndex) {
    int numDupes = 0;
    char* nameSuffix;

    for(int i = 0; i < numTables; i++) {
        if(strcmp(nameToCheck, tables[i].name) == 0 && i != newNameIndex) {
            // printf("DUPE FOUND\n");
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

void checkDupColumnNames(Table table, char* nameToCheck, int newNameIndex) {
    int numDupes = 0;
    char* nameSuffix;

    for(int i = 0; i < table.numCols; i++) {
        if(strcmp(nameToCheck, table.cols[i].name) == 0 && i != newNameIndex) {
            // printf("DUPE FOUND\n");
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

int checkInvalidName(char* name) {

    printf("YEET, %s\n", name);

    int numBadStrings = 8;

    char** invalidStrings = malloc(sizeof(char*) * numBadStrings);
    invalidStrings[0] = "count(";
    invalidStrings[1] = "sum(";
    invalidStrings[2] = "avg(";
    invalidStrings[3] = "min(";
    invalidStrings[4] = "max(";
    invalidStrings[5] = "sqlite";
    invalidStrings[6] = "*";
    invalidStrings[7] = ".";

    for(int i = 0; i < numBadStrings; i++) {
        if(containsIgnoreCase(name, invalidStrings[i])) {
            free(invalidStrings);
            return 0;
        }
    }

    free(invalidStrings);
    return 1;
}

int equalsIgnoreCase(char* string1, char* string2) {
    char temp1[MAX_LEN];
    char temp2[MAX_LEN];

    strcpy(temp1, string1);
    strcpy(temp2, string2);

    for(int i = 0; i < strlen(temp1); i++) {
        temp1[i] = tolower(temp1[i]);
    }
    for(int i = 0; i < strlen(temp2); i++) {
        temp2[i] = tolower(temp2[i]);
    }

    return strcmp(temp1, temp2) == 0;

}

int containsIgnoreCase(char* big, char* small) {
    char tempBig[MAX_LEN];
    char tempSmall[MAX_LEN];

    strcpy(tempBig, big);
    strcpy(tempSmall, small);

    for(int i = 0; i < strlen(tempBig); i++) {
        tempBig[i] = tolower(tempBig[i]);
    }
    for(int i = 0; i < strlen(tempSmall); i++) {
        tempSmall[i] = tolower(tempSmall[i]);
    }

    return strstr(tempBig, tempSmall) != NULL;
}

char* yesnoInput(void) {
    static char yesno[MAX_LEN];

    do {
        fgetsUntil(yesno, MAX_LEN);
        if(!isYes(yesno) && !isNo(yesno))
            printf("Please input 'yes' or 'no': ");
    } while(!isYes(yesno) && !isNo(yesno));

    return yesno;
}

int isYes(char* yesno) {
    for(int i = 0; i < strlen(yesno); i++)
        yesno[i] = tolower(yesno[i]);

    if(equalsIgnoreCase(yesno, "yes") || equalsIgnoreCase(yesno, "y"))
        return 1;

    return 0;
}

int isNo(char* yesno) {
    for(int i = 0; i < strlen(yesno); i++)
        yesno[i] = tolower(yesno[i]);

    if(equalsIgnoreCase(yesno, "no") || equalsIgnoreCase(yesno, "n"))
        return 1;

    return 0;
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

void scanfWellNull(char* formSpec, void* val) {
    char buffer[MAX_LEN];
    int success;

    do {
        fgetsUntil(buffer, MAX_LEN);
        if(strcmp(buffer, "NULL") == 0) {
            success = 1;
            val = NULL;
        }
        else
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
