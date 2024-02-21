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

    for (int i = 0; i < numCols; i++) {
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

    if (numValues > table->numCols) {
        printf("Error: To many arguments provided. Insertion failed.\n");
        return;
    }

    va_list ap;
    table->numRows++;
    char* colName = "";
    int colFound = 0;

    va_start(ap, numValues);

    for (int i = 0; i < table->numCols; i++) {
        table->cols[i].values = realloc(table->cols[i].values, sizeof(Column) * table->numRows);
        if (table->cols[i].type == CHAR)
            table->cols[i].values[table->numRows - 1].CHAR = "NULL";
        else if (table->cols[i].type == INTEGER)
            table->cols[i].values[table->numRows - 1].INTEGER = 0;
        else if (table->cols[i].type == DECIMAL)
            table->cols[i].values[table->numRows - 1].DECIMAL = 0.0;
    }

    for (int i = 0; i < numValues; i++) {
        colName = strdup(va_arg(ap, char*));

        for (int j = 0; j < table->numCols; j++) {
            if (strcmp(table->cols[j].name, colName) == 0) {
                if (table->cols[j].type == CHAR)
                    table->cols[j].values[table->numRows - 1].CHAR = va_arg(ap, char*);
                else if (table->cols[j].type == INTEGER)
                    table->cols[j].values[table->numRows - 1].INTEGER = va_arg(ap, int);
                else if (table->cols[j].type == DECIMAL)
                    table->cols[j].values[table->numRows - 1].DECIMAL = va_arg(ap, double);
                colFound = 1;
                break;
            }
        }

        if (!colFound) {
            printf("Error: Nonexistent column name, \"%s\", provided.\n", colName);
            va_arg(ap, void*);
        }

        free(colName);

    }
    va_end(ap);
}

void printTable(Table table) {

    printf("\nTABLE: %s\nCOLUMNS:", table.name);

    for (int i = 0; i < table.numCols; i++)
        printf("\t%s", table.cols[i].name);

    for (int i = 0; i < table.numRows; i++) {
        printf("\n\t");
        for (int j = 0; j < table.numCols; j++) {
            if (table.cols[j].type == CHAR)
                printf("\t[ %s ]", table.cols[j].values[i].CHAR);
            else if (table.cols[j].type == INTEGER)
                printf("\t[ %d ]", table.cols[j].values[i].INTEGER);
            else if (table.cols[j].type == DECIMAL)
                printf("\t[ %.3lf ]", table.cols[j].values[i].DECIMAL);
        }
    }

    printf("\n");
}
