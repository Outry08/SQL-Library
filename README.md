## Author
Ryan McKinnon

## Name
SQL Library

## Description
A C-library to mimic SQL functions, as well as add some new ones. The plan is to add the ability to import and export between C and SQL files.

## Running The Program
Run the makefile with 'make' command
Execute the program with ./sql

## Visuals

## Roadmap
- Add DATE datatype functionality.
- Look into BLOB datatype support.
- Include aggregate functions, distinct, & group by into select function.
- Incorporate column properties such as autoincrement, not null, primary key, and foreign key.
    - Look into adding support for CHECK property.
- Add the ability to input '*' to indicate 'all' in many user input places.
- Allow user to type NULL for where condition of ANY datatype.
- Expand select statements to be able to refer to other tables. (Including adding join statements).
- Allow for multiple layers of sorting.
- Add ability to edit properties of columns (autoincrement, primary key, datatype, etc.).
- Possibly add in settings to reduce repeated inputs in certain fields.
- allow for the user to input Yes, yes, y, YES all for an input of yes. And the same for no.
- Prohibit name inputs with keyworks like 'COUNT' or 'AVG' or 'sqlite3_MASTER' or '*' or '.'
- Add ellipses for printing of huge tables.
- Add 'back' or 'cancel' option to nearly every stage of user input.
- Potentially add ability to export to html to make a visual version of the table(s).
- Valgrind and fix all leaks.
- Learn how to throw errors instead of just printing errors.
- Add full library documentation.
- COMPLETE.

## Project status
Ongoing.
