# TinySQL – Build Your Own In-Memory Database in C++

Documenting my progress:
First of all after getting the details about the assignment I started by reading all the instructions
and understanding the requirements.
Then i visited each one of the suggested learning sources.
After exploting each one of the links I decided to start with the third one that teaches how to build a
SQLite.

So I started implementing. first by creating a git repository named TinySQL and inside it I created the suggested
arranging of the folders.
By following the instructions in the third link I completed the first 4 stages in the link.
After completing the first 4 stages it blocked the learning option and asked for a membership so
I decided to leave this approach and delete all the code that was written and started the git repository
again from scratch.

From that link i reached a couple of conclusions about the staructure of how I want to implement storing the data.
I will have two classes:
**Column**:
This class will store all thats needed in a column.
size, data, name and type.
The type can only be 0 or 1, if its 0 then the value stored is an int and if its 1 then its a string.
The data stores all the values of the COLUMN, and its a vector of pairs. Each column can only have one type of values 
which will be stored in the corresponding palcement in the pair, pair.first for int and pair.second for string.

**Table**:
This class will store all thats needed in a Table.
size, data, name and identifier.
Name is the name of the table.
Size is the amount of columns the table has.
The data is a vector of Column* which stores all the columns the table has.
The identifier is a map<string, int> which stors {name_column, index_in_data} this way it easier to access a specific column.

After reaching these conclusions I decided to continue to the second link and see what I can learn from it.
I watched the first 3 videos and decided that I want to follow his steps and using his guiding videos
to implement my Command-line interface for queries.

Unfortunately after investing a lot of time in watching the videos and trying to implement the code I couldn't reach
a satisfactory result. So I reached out to the number provided and asked if I could use a file input instead of implementing
a command line interface. I was told that it is acceptable to do so.

Following this I decided to delete all the code of the repository and start from scratch again. This time by using file input.
The input should only be in the input.txt file located at "tiny_sql\Input-output\Input\input.txt".
in this file you can write all of the commands you want to be executed.

The only commands that will be handled need to be in the following structure:
**CREATE TABLE** *table_name* (*name* INT, *name* TEXT, ...);

**INSERT INTO** *table_name* (*name_column_1*, *name_column_2*, ...) **VALUES** *value_1*, *value_2*, ...;
**INSERT INTO** *table_name* **VALUES** *value_1*, *value_2*, ...;

**SELECT** *selection_of_columns* **FROM** *table_name* **WHERE** *condition_AND*;
**SELECT** *selection_of_columns* **FROM** *table_name*;

**DELETE FROM** *table_name* **WHERE** *condition_OR*;
**DELETE FROM** *table_name*;

**clarifications about these commands:**
1. In the CREATE command the only types allowed for columns are: INT, TEXT. Each table name should be different.
2. In the INSERT command you list the names of the columns after stating the name of the table or you can go straight into the values.
3. In the SELECT command the selection of columns should only be in the following format: name_column_1, name_column_2, ...
   or if you want to select all of the columns you can just use *.
   in addition if you want to use a condition you can only use it in the following format: name_column *condition_mark* value AND name_column *condition_mark* value AND ...
   when condition_mark id each of the following marks: < > = != <= >=.
   **important to notice** you can not use OR in the condition for the SELECT command;
4. In the DELETE command if you dont add the condition it will delete all of the contents of the table stated, it won't delete the table entirely.
   In addition if you want to use a condition you can only use it in the following format: name_column *condition_mark* value OR name_column *condition_mark* value OR ...
   when condition_mark id each of the marks stated above.
   **important to notice** you can not use AND in the condition for the DELETE command;


**clarification about the outputs**
All the outputs should appear in the three text files inside the Output folder located at: "tiny_sql\Input-output\Output".
It's very important to check that they have the right names:
*tiny_sql\Input-output\Output\CurrentTables.txt* - this file consists of the tables that are stored after each command.
*tiny_sql\Input-output\Output\SelectOutput.txt* - this file consists of the select output after each select command.
*tiny_sql\Input-output\Output\Unsuccessful.txt* - this file consists all the errors that may accured during the execution of the commands.