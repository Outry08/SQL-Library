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
Complete user-input table manipulator.
Add 'back' or 'cancel' option to nearly every stage of user input.
Add menu item to sort by a column (or by multiple columns).
Add DATE datatype functionality.
Include aggregate functions, distinct, order by, and group by into select function.
Add the ability to input '*' to indicate 'all' in many user input places.
Expand select statements to be able to refer to other tables.
Add the ability to import from and export to SQL or db files with given SQL table struct in C.
Add ability to edit properties of columns (autoincrement, primary key, datatype, etc.).
Allow for multiple master tables (databases) in user-table operator.
allow for the user to input Yes, yes, y, YES all for an input of yes. And the same for no.
Valgrind and fix all leaks.
Learn how to throw errors instead of just printing errors.
Add full library documentation.

## Project status
Ongoing.
