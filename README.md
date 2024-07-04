## Author
Ryan McKinnon

## Name
SQL Library

## Description
A C-library to mimic SQL functions, as well as add some new ones. Is fully capable of loading existing .db and .sql files, as well as exporting tables into these file formats.

## Running The Program
Run the makefile with 'make' command
Execute the program with ./cql

## Visuals

## Roadmap
- Valgrind and fix most leaks.
- COMPLETE.

## Potential Additions At A Later Date
- Add join statements.
- Add DATE datatype functionality.
- Group By in select statements.
- Expand select statements to be able to refer to other tables.
- Multi-layered Sorting.
- Adding CHECK attribute to columns.
- Adding DATE datatype support.
- Adding BLOB datatype support.
- More in-depth auto increment settings.
- More WHERE comparisons.
- More Aggregate Functions.
- Foreign Key functionality.
- Undo feature.
- Extra CHAR comparisons (Contains, starts with, ends with).
- Saving and loading select and where statements for quick repeated usage.
- Add question on a selected table to ask if updates want to be applied to the base table.

## Limitations
- Upon importing SQL instructions, they cannot be all on one line.
- Program is slow with larger tables.
- Foreign Keys are not validated when inserting unless the 'setForeignKey' function is called after a foreign key is added/changed.
- Faulters if imported string table values are more than 100 characters long.

## Project status
Ongoing.
