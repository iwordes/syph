Insert
------
1. 0x30 Query: Insert
2. u32  Table ID
3. u8   Field count
4. u8[] Fields
5. u32  Entry count

Payload: Entries

Select
------
1. 0x31 Query: Select
2. u32  Table ID
3. u8   Field count
4. u8[] Fields
5.      Comparison operations

Update
------
1. 0x32 Query: Update
2. u32  Table ID
4.      Comparison operations
6.      Assignment operations

Delete
------
0x33 Query: Delete

