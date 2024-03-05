#include "sqllib.h"

int main(int argc, char const* argv[]) {

    Table* tables = userTableOperator();
    // Table table = create("My Table", 3, nameList(3, "Char Col", "Decimal Col", "IntegerCol"), typeList(3, CHAR, DECIMAL, INTEGER));
    // printTable(table);

    // insert(&table, 2, "Decimal Col", 44.55, "Char Col", "Luigi");
    // printTable(table);
    // insert(&table, 1, "Char Col", "Mario");
    // printTable(table);

    // insert(&table, 1, "Integer Col", 4);
    // insert(&table, 3, "Integer Col", 44, "Decimal Col", 88.77, "Char Col", "WAHHLUIGI");
    // printTable(table);

    // Where where1 = newWhere("Char Col", "==", "Luigi");
    // double newNum = 9999.999;


    // update(&table, "Decimal Col", &newNum, 1, whereList(1, where1), connectiveList(0));
    // printTable(table);

    // newNum = 0;
    // Where where2 = newWhere("Decimal Col", "==", &newNum);

    // int newInt = 1735;

    // update(&table, "Integer Col", &newInt, 2, whereList(2, where1, where2), connectiveList(1, '|'));
    // printTable(table);

    // Where where3 = newWhere("Char Col", "==", "NULL");
    // update(&table, "Char Col", "WAAAAARIOOOOOOO", 1, whereList(1, where3), connectiveList(0));
    // printTable(table);

    // insert(&table, 1, "Decimal Col", 444.0);

    // printTable(table);
    // newInt = 666;

    // update(&table, "Integer Col", &newInt, 3, whereList(3, where3, where2, where1), connectiveList(2, '&', '|'));
    // printTable(table);

    // Where where4 = newWhere("Integer Col", "==", &newInt);
    // update(&table, "Char Col", "WAAAAAAAAAAAAAAARIOOOOOO", 2, whereList(2, where3, where4), connectiveList(1, '&'));
    // printTable(table);

    // where3.comparison = "==";

    // update(&table, "Char Col", "Peach", 1, whereList(1, where3), connectiveList(0));
    // printTable(table);

    // double dec = 444.0;

    // Where where5 = newWhere("Char Col", "==", "WAAAAAAAAAAAAAAARIOOOOOO");
    // Where where6 = newWhere("Decimal Col", ">", &dec);
    // Where where7 = newWhere("Decimal Col", "==", &dec);
    // Where where8 = newWhere("Integer Col", "==", &newNum);
    // where1.comparison = "!=";
    // delete(&table, 7, whereList(7, where5, where3, where6, where4, where1, where7, where8), connectiveList(6, '|', '&', '|', '|', '&', '&'));
    // where3.comparison = "!=";
    // delete(&table, 2, whereList(2, where5, where3), connectiveList(1, '&'));

    // // deleteAll(&table);
    // printTable(table);

    // printf("\n\n\n");
    // where3.searchValue = "Mario";

    // Select select1 = newSelect(2, nameList(2, "Decimal Col", "Char Col"), NULL, NULL, 0);

    // // where3.comparison = "==";
    // // where5.comparison = "!=";
    // // delete(&table, 2, whereList(2, where5, where3), connectiveList(1, '&'));
    // // printTable(table);

    // printTable(select(table, select1, 2, whereList(2, where5, where3), connectiveList(1, '|')));

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

    if(select.numCols == 1 && strcmp(select.colNames[0], "*") == 0) {
        for(int i = 0; i < select.numCols; i++)
            free(select.colNames[i]);

        select.numCols = table.numCols;
        free(select.colNames);
        select.colNames = malloc(sizeof(char*) * table.numCols);
        for(int i = 0; i < table.numCols; i++) {
            select.colNames[i] = strdup(table.cols[i].name);
        }
    }
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
    strcat(newTable.name, " Select");
    newTable.cols = malloc(sizeof(Column) * numCols);

    newTable.numCols = numCols;
    newTable.numRows = baseTable.numRows;

    int allAggs = 1;

    char* newName;

    for(int i = 0; i < numCols; i++) {
        if(!isAggregate(colNames[i])) {
            newTable.cols[i] = nameToCol(&baseTable, colNames[i]);
            newTable.cols[i].name = strdup(colNames[i]);
            newTable.cols[i].type = nameToCol(&baseTable, colNames[i]).type;
            allAggs = 0;
        }
        else {
            newName = &(strchr(colNames[i], '(')[1]);
            for(int j = 0; j < strlen(newName); j++)
                if(newName[j] == ')')
                    newName[j] = '\0';
            newTable.cols[i].values = malloc(sizeof(newTable.numRows));
            newTable.cols[i].name = getAggregateName(colNames[i]);
            newTable.cols[i].type = nameToCol(&baseTable, newName).type;
        }
    }

    if(allAggs) {
        for(int i = 0; i < numCols; i++)
            newTable.cols[i].values = realloc(newTable.cols[i].values, 1);
        newTable.numRows = 1;
    }

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

    char* conns = malloc(sizeof(char) * (numConns + 2));
    conns[0] = '~';

    for(int i = 1; i < numConns + 1; i++)
        conns[i] = va_arg(ap, int);

    va_end(ap);

    conns[numConns + 1] = '\0';

    return conns;

}


void printTable(Table table) {

    int colWidth = 23;

    printf("\n");
    for(int i = 0; i < colWidth * table.numCols / 2; i++) {
        printf(" ");
    }
    printf("TABLE: %s", table.name);
    char printString[50];

    printTableRow(table.numCols);

    for(int i = 0; i < table.numCols; i++)
        printf("| \e[1m%-*s\e[m", colWidth - 2, table.cols[i].name);
    printf("|");

    for(int i = 0; i < table.numRows; i++) {
        printTableRow(table.numCols);
        for(int j = 0; j < table.numCols; j++) {
            if(table.cols[j].type == CHAR) {
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

    printTableRow(table.numCols);
    printf("\n");
}

void printTableRow(int numCols) {
    printf("\n\t+");
    for(int j = 0; j < numCols; j++) {
        for(int k = 0; k < 22; k++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n\t");
}

Table* userTableOperator(void) {

    Table* tables;
    Table* currentTable;
    int numTables = 0;

    int menuChoice = 1;
    int tableChoice;

    char yesno[5];

    char tableName[50];
    int numThings;

    char** nameList;
    int* typeList;
    void** valueList;
    Where* whereList = NULL;
    int numWheres = 0;
    char* connectiveList = NULL;

    Select sel;

    printf("\t\t-- Welcome to CQL! --\n");

    while(menuChoice) {
        numWheres = 0;
        if(connectiveList != NULL)
            free(connectiveList);
        if(whereList != NULL)
            free(whereList);

        menuChoice = printActionMenu(currentTable);

        switch(menuChoice) {
            case 1:
                numTables++;
                if(numTables == 1)
                    tables = malloc(sizeof(Table));
                else
                    tables = realloc(tables, sizeof(Table) * numTables);

                printf("What is the name of your new table?: ");
                // scanf("%s", tableName);
                do {
                    fgets(tableName, 50, stdin);
                } while(strcmp(tableName, "\n") == 0);
                tableName[strlen(tableName) - 1] = '\0';
                // gets(tableName);
                // gets(tableName);
                printf("How many columns would you like to have?: ");
                do {
                    scanf("%d", &numThings);
                    if(numThings <= 0)
                        printf("Please input a positive number: ");
                } while(numThings <= 0);
                nameList = malloc(sizeof(char*) * numThings);
                typeList = malloc(sizeof(int) * numThings);
                for(int i = 0; i < numThings; i++) {
                    printf("Name for column #%d: ", i + 1);
                    nameList[i] = malloc(sizeof(char) * 50);
                    scanf("%s", nameList[i]);
                    printf("Type Chart:\n"
                        "  1. CHAR (String)\n"
                        "  2. INTEGER (Int)\n"
                        "  3. DECIMAL (Double)\n"
                        "  4. DATE\n");
                    printf("Type for column #%d: ", i + 1);
                    do {
                        scanf("%d", &typeList[i]);
                        typeList[i]--;
                        if(typeList[i] < 0 || typeList[i] > 3)
                            printf("Please input a valid type (1-4): ");
                    } while(typeList[i] < 0 || typeList[i] > 3);
                }
                tables[numTables - 1] = create(tableName, numThings, nameList, typeList);
                currentTable = &tables[numTables - 1];
                break;
            case 2:
                if(numTables > 0) {
                    printf("Which table would you like to print?\n");
                    tableChoice = printTableMenu(numTables, tables);
                    printTable(tables[tableChoice]);
                }
                else
                    printf("There are no tables to print.\n");
                break;
            case 3:

                break;
            case 4:
                // if(numTables > 0) {
                //     printf("Which table would you like to select from?\n");
                //     for(int i = 0; i < numTables; i++)
                //         printf("Table %d. %s\n", i + 1, tables[i].name);
                //     printf("Your choice: ");
                //     do {
                //         scanf("%d", &tableChoice);
                //         tableChoice--;
                //         if(tableChoice < 0 || tableChoice >= numTables)
                //             printf("Please input a valid table (1-%d): ", numTables);
                //     } while(tableChoice < 0 || tableChoice >= numTables);
                // }
                if(numTables <= 0) {
                    printf("There are no tables to select from.\n");
                    break;
                }

                printf("How many columns would you like to select?: ");
                do {
                    scanf("%d", &sel.numCols);
                    if(sel.numCols <= 0)
                        printf("Please input a positive number: ");
                } while(sel.numCols <= 0);
                sel.colNames = malloc(sizeof(char*) * sel.numCols);
                for(int i = 0; i < sel.numCols; i++) {
                    sel.colNames[i] = malloc(sizeof(char) * 50);
                    printf("Name for select column #%d: ", i + 1);
                    do {
                        fgets(sel.colNames[i], 50, stdin);
                    } while(strcmp(sel.colNames[i], "\n") == 0);
                    sel.colNames[i][strlen(sel.colNames[i]) - 1] = '\0';
                }

                printf("Would you like to filter your result with a where statement? (yes/no): ");
                do {
                    do {
                        fgets(yesno, 5, stdin);
                    } while(strcmp(yesno, "\n") == 0);
                    yesno[strlen(yesno) - 1] = '\0';
                    if(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0)
                        printf("Please input 'yes' or 'no': ");
                } while(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0);

                numWheres = whereInput(currentTable, whereList, connectiveList);

                /*
                group by stuff
                */

                /*
                order by stuff
                */

                printf("Do you want duplicate values in this select? (yes/no): ");
                do {
                    do {
                        fgets(yesno, 5, stdin);
                    } while(strcmp(yesno, "\n") == 0);
                    yesno[strlen(yesno) - 1] = '\0';
                    if(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0)
                        printf("Please input 'yes' or 'no': ");
                } while(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0);

                if(strcmp(yesno, "no") == 0)
                    sel.distinct = 1;
                else
                    sel.distinct = 0;

                numTables++;
                tables[numTables - 1] = select(*currentTable, sel, numWheres, whereList, connectiveList);
                currentTable = &tables[numTables - 1];
                break;

            case 5:

                break;
            case 6:

                break;
            case 7:

                break;
            case 8:

                break;
            case 9:

                break;
            case 10:

                break;
            case 11:

                break;
            case 12:

                break;
            case 0:
                printf("Saving\n");
                for(int i = 0; i < 3; i++) {
                    sleep(750);
                    printf(".\n");
                }
                sleep(1000);
                printf("Database Saved.\n");
            default:
                printf("Exiting Program.\n");
                break;
        }

    }

    return tables;

}

int printActionMenu(Table* table) {

    int menuChoice;

    printf("\n\nWhat would you like to do?\n");
    if(table != NULL)
        printf("Your current table is: %s\n", table->name);
    printf("1. Create a table\n"
        "2. Print a table\n"
        "3. Choose new current table\n"
        "4. Select from current table\n"
        "5. Insert a new row into current table\n"
        "6. Insert a new column into current table\n"
        "7. Update an existing value in current table\n"
        "8. Delete records from current table\n"
        "9. Delete current table\n"
        "10. Import Table(s) from .sql File\n"
        "11. Import Table(s) from .db File\n"
        "12. Export Table(s) to .SQL File\n"
        "13. Export Table(s) to .db File\n"
        "0. Save & Exit\n"
        "0.0 Exit Without Saving\n"
        "Your choice : ");
    scanf("%d", &menuChoice);
    printf("\n");

    return menuChoice;
}
int printTableMenu(int numTables, Table* tableList) {

    int tableChoice;

    for(int i = 0; i < numTables; i++)
        printf("Table %d. %s\n", i + 1, tableList[i].name);
    printf("Your choice: ");
    do {
        scanf("%d", &tableChoice);
        tableChoice--;
        if(tableChoice < 0 || tableChoice >= numTables)
            printf("Please input a valid table (1-%d): ", numTables);
    } while(tableChoice < 0 || tableChoice >= numTables);

    return tableChoice;
}
int whereInput(Table* currentTable, Where* whereList, char* connectiveList) {

    char yesno[5];
    int numWheres = 0;
    do {
        numWheres++;
        if(numWheres == 1)
            whereList = malloc(sizeof(Where));
        else
            whereList = realloc(whereList, sizeof(Where) * numWheres);

        printf("Please input the column name for your where statement: ");
        whereList[numWheres - 1].searchColName = malloc(sizeof(char) * 50);
        do {
            fgets(whereList[numWheres - 1].searchColName, 50, stdin);
        } while(strcmp(whereList[numWheres - 1].searchColName, "\n") == 0);

        printf("Please enter the comparison you will use (=, <, >, etc.): ");
        whereList[numWheres - 1].comparison = malloc(sizeof(char) * 5);
        do {
            do {
                fgets(whereList[numWheres - 1].comparison, 5, stdin);
            } while(strcmp(whereList[numWheres - 1].comparison, "\n") == 0);
            if(!isValidComp(whereList[numWheres - 1].comparison))
                printf("Invalid comparison. Try again: ");
        } while(!isValidComp(whereList[numWheres - 1].comparison));

        if(nameToCol(currentTable, whereList[numWheres].searchColName).type == INTEGER) {
            printf("Please input the integer value you are looking for: ");
            scanf("%d", whereList[numWheres - 1].searchValue);
        }
        else if(nameToCol(currentTable, whereList[numWheres].searchColName).type == CHAR) {
            printf("Please input the string value you are looking for: ");
            scanf("%s", whereList[numWheres - 1].searchValue);
        }
        else if(nameToCol(currentTable, whereList[numWheres].searchColName).type == DECIMAL) {
            printf("Please input the decimal value you are looking for: ");
            scanf("%lf", whereList[numWheres - 1].searchValue);
        }

        printf("Would you like to add another where statement? (yes/no): ");
        do {
            do {
                fgets(yesno, 5, stdin);
            } while(strcmp(yesno, "\n") == 0);
            yesno[strlen(yesno) - 1] = '\0';
            if(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0)
                printf("Please input 'yes' or 'no': ");
        } while(strcmp(yesno, "no") != 0 && strcmp(yesno, "yes") != 0);

        if(strcmp(yesno, "yes") == 0) {
            if(numWheres == 1)
                connectiveList = malloc(sizeof(Where));
            else
                connectiveList = realloc(connectiveList, sizeof(Where) * numWheres);
            printf("Please input the connective to connect the where statement\nyou just made with the new one you're going to make. ('&' or '|'): ");
            do {
                do {
                    scanf("%c", &connectiveList[numWheres - 1]);
                } while(connectiveList[numWheres - 1] == '\n');
                if(connectiveList[numWheres - 1] != '&' && connectiveList[numWheres - 1] != '|')
                    printf("Invalid connective, try again: ");
            } while(connectiveList[numWheres - 1] != '&' && connectiveList[numWheres - 1] != '|');
        }
    } while(strcmp(yesno, "yes") == 0);

    return numWheres;
}

void sleep(int milliseconds) {
    struct timespec ts;

    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;

    nanosleep(&ts, &ts);
}

// remember SQLITE3 terminal command can also read .sql files.
// sqlite3_exec(sqlite3_open(demo.sql), "CREATE TABLE Mario", NULL, NULL, "Error: SQL Execution Failed");
