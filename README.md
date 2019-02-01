Attempt to make database management system for practice.
You can use few tables at once, but they for now can have the only model: 2 char[20] fields, bool and int field for kind of people data storing.
You can print, sort and save table, insert in it, delete or select from it. You can perform several operations in one line, make query chains(such as selection and few sorts). You can select with many operations on fields: finding equal, non-equal, containing, starting with or many other operations on rows' fields. Selection doesn't change current table. It just selects rows from it and forms new table that returns.
Table methods is divided into two groups:
* That changes method's object
* That does not


### Aviable methods and their usage:
`Table(const char*)` - just struct constructor that takes file name, but you can init table empty, just as usual struct

`void print(bool)` - outputs table. Takes value that defines will function print field names or not

`Table select(const char*, const char*, bool comp(const char*, const char*))` - takes field name, char* value and comparison function that will be used in selection. Returns table with selected rows and doesn't alter current table

`Table select(const char*, const int, bool comp(const int, const int))` - does the same, but takes int value

`Table& del(const char*, const char*, bool comp(const char*, const char*))` - deletes selected rows and returns current table that you can continue work with table in one line. Takes same arguments as in select() function

`Table& del(const char*, const int, bool comp(const int, const int))` - same as previous, but takes int value

`Table& insert(char*, char*, bool, int)` - inserts one row in current table and returns current table object that you can continue work with table in one line. Takes field values for new row. In char[n] field you can place only n-1 symbols, cause last must be null-byte terminator for struct member separating

`Table& insert(Person*, const int)` - insert few rows and returns table object. Takes array of row structures and their length

`Table sort(const char*, const bool)` - doesn't change current table, it sorts their rows and returns sorted by any field new table. You can make sort chain. Takes field name and sort order(asc/desc): asc by default(or 1), 0 for desc

`void save(const char*)` - saves current table. Takes file name and writes into the file/rewrites if file exists


### Comparison functions:
Every single function have next syntax:  
`bool <comp> (<val>, <row field's val>)`, or, for string comparison,  
`bool <comp> (<substr>, <str>)`  
Functions:
1. eq - equality
2. ne - !eq
3. lt - less than
4. le - less or equal
5. gt - greater than
6. ge - greater or equal
7. sw - startswith
8. ew - endswith
9. in - is substring exists in string
10. ni - !in
1-6 applies for int, 1-10 applies for string(char*), 1-2 for bool(you can use 3-6 too, but this won't have any sense)
There no function check, so you can try to attach sw comp function for sorting by int field and get wrong or unexpected result, but you should not do this. It's on your own.

**You can not create model with other fields without code editing.** Maybe, I will add this function later. For now I implemented all needed for me functionality. This isn't real DBMS, it's just for practice. Continuous developing model creating is going to be too complicated, so I stopped on this point.


### Examples
`Table table("table");` - Initializes table from file "table"  
`table.print();` - Table output with field names  
`table.print(0);` - Table output without field names  
`table.select("fName", "Jo", in).print(1);` - Prints   table with field names and rows which fName field contains "Jo"  
`table.sort("fName", 0).sort("age").print(0);` - Sort chain and outputting. Remember, sort doesn't change current table, only returns sorted one  
`table.insert("Oleg", "Benedictoxygenipropanol", 1, 99);` - Insertion new row. Too long names/surnames will be cutted to 19 symbols  

Multiple row insertion:  
`Person list[] =`  
`{"John", "Watson", 1, 30},`  
`{"Sherlock", "Holmes", 1, 40},`  
`{"Qwerty", "Poiu", 0, 43}`  
`};`  
`table.insert(list, 3);`

`table.del("age", 16, gt);` - Every row which age field have value more 16 will be deleted  
`table.del("age", 14, eq).del("male", 0, eq);` - Chain deletion. You can chain any queries of aviable, but after save() you can not use any other Table methods  
`table.save("table");` - Save into "table" file


### Files in repository and their destiny
`utilities.h` - contains comp functions and other utilities  
`models.h` - contains structs such as table struct and it's method protos and table model struct  
`bundb.h` - constains main methods such as sort, del, select and others  
`dbms.cpp` - main DBMS file that contains main() function and performs calls to table struct and all it's methods  

This program needs thourough tests. I fixed bugs I found, but no one knows, how many left unfixed
