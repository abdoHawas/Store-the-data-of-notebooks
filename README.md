# Store-the-data-of-notebooks
Simple C++ application that allow the user to store the data in a file , delete and update a record , search for a record 

 functionalities :
 1-Add new record, always add new records in the end of file. 
 2-Delete a record, just marks the record by * exactly after records length.
 3-Update a record given the ID, if the new record is the same size, then insert in the same place, if size is changed,  perform delete then add operations.
 4-Search for a record given an ID, if found print its data, if not tell user that this device is not found.
 5-CompactFile : due to the delete and the add operations, a lot of records’ space should be reclaimed, After calling this function,      the file should has no deleted records.
 6-VisualizeFile: this function prints a visual representation of a file.

 Requirments :
 C++ IDE.
 C++ compiler.
