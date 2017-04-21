Insert
------
1. 0x30 Query: Insert
2. u32  Table ID
3. u8   Field count
4. u8[] Fields
5. u32  Entry count
<!-- Necessary? Maybe not, but what about for consistency? -->
6. 0x00 EOR

Payload: Entries

Select
------
1. 0x31 Query: Select
2. u32  Table ID
3. u8   Field count
4. u8[] Fields
5.      Comparison operations
6. 0x00 EOR

Update
------
1. 0x32 Query: Update
2. u32  Table ID
4.      Comparison operations
6.      Assignment operations

Delete
------
0x33 Query: Delete
