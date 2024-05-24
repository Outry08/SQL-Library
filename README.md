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

- Incorporate column properties such as autoincrement, not null, primary key, and foreign key.
    - Add ability to edit properties of columns (Datatype, Default value, Foreign Key String).
    - Properly import and export column attributes.
- Group By in select statements.
- Expand select statements to be able to refer to other tables. (Including adding join statements).

- Add the ability to input '*' to indicate 'all' in many user input places.
- Allow user to type NULL for where condition of ANY datatype.
- Allow for the user to input Yes, yes, y, YES all for an input of yes. And the same for no.
- Prohibit name inputs with keyworks like 'COUNT' or 'AVG' or 'sqlite3_MASTER' or '*' or '.'
- Add 'back' or 'cancel' option to nearly every stage of user input.

- Valgrind and fix all leaks.
- Learn how to throw errors instead of just printing errors.
- Add full library documentation.

- COMPLETE.

## Potential Additions At A Later Date
- Multi-layered Sorting.
- Adding CHECK attribute to columns.
- Adding DATE datatype support.
- Adding BLOB datatype support.
- More in-depth auto increment settings.
- Foreign Key functionality instead of just recording.
- Undo feature.

## Limitations
- Upon importing SQL instructions, they cannot be all on one line.
- Program is slow with larger tables.

## Project status
Ongoing.
