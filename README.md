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
- Prohibit name inputs with keyworks like 'COUNT' or 'AVG' or 'sqlite3_MASTER' or '*' or '.'
- Add 'back' or 'cancel' option to nearly every stage of user input.
- Extra CHAR comparisons (Contains, starts with, ends with).
- Make SAVE & QUIT actually work.

- Valgrind and fix all leaks.
- Learn how to throw errors instead of just printing errors.
- Add full library documentation.

If I feel like it:
- Add join statements.
- Add DATE datatype functionality.

- COMPLETE.

## Potential Additions At A Later Date

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

## Limitations
- Upon importing SQL instructions, they cannot be all on one line.
- Program is slow with larger tables.
- Foreign Keys are not validated when inserting unless the 'setForeignKey' function is called after a foreign key is added/changed.

## Project status
Ongoing.
