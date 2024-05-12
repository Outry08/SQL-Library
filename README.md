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
- Add the ability to import from and export to SQL or db files with given SQL table struct in C.
    - Potentially add ability to export to html to make a visual version of the tabl(s).
- Add 'back' or 'cancel' option to nearly every stage of user input.
- Add DATE datatype functionality.
- Include aggregate functions, distinct, order by, and group by into select function.
- Incorporate column properties such as autoincrement, not null, primary key, and foreign key.
- Add the ability to input '*' to indicate 'all' in many user input places.
- Expand select statements to be able to refer to other tables. (Including adding join statements).
- Add .cql file for each table saved to save attributes such as column types, not null, autoincrement, primary key, and foreign key. Or alternatively learn how to retrieve this information from the sql document.
- Add ability to edit properties of columns (autoincrement, primary key, datatype, etc.).
- Allow for multiple master tables (databases) in user-table operator.
- allow for the user to input Yes, yes, y, YES all for an input of yes. And the same for no.
- Valgrind and fix all leaks.
- Learn how to throw errors instead of just printing errors.
- Add full library documentation.
- COMPLETE.

## Project status
Ongoing.
