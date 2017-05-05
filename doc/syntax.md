Create
------
1. u8[] Label
2. u8   Schema len
3. []   Schema

Insert
------
1. u32  Table ID
2. u32  Limit (# entries)
3. u8   Field count
4. u8[] Fields
5. []   Entries

Select
------
1. u32  Table ID
2. u32  Limit
3. u8   Field count
4. u8[] Fields
5. u8   Comparison count
6. []   Comparisons
7. []   Values

Update
------
1. u32 Table ID
2. u8  Comparison count
3. u8  Assignment count
4. []  Comparisons
5. []  Values
6. []  Assignments
7. []  Values

Delete
------
1. u32 Table ID
2. u32 Limit
3. u8  Comparison count
4. []  Comparisons
5. []  Values
