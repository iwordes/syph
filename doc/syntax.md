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
5. u8   Order count
6. []   Orders
7. u8   Comparison count
8. []   Comparisons
9. []   Values

Update
------
1. u32 Table ID
2. u8  Comparison count
3. []  Comparisons
4. []  Values
5. u8  Assignment count
6. []  Assignments
7. []  Values

Delete
------
1. u32 Table ID
2. u32 Limit
3. u8  Comparison count
4. []  Comparisons
5. []  Values
