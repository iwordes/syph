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
4. u8   Comparison count
5. u8   Order count
6. u8[] Fields
7. []   Comparisons
8. []   Orders

Update
------
1. u32 Table ID
2. u8  Comparison count
3. u8  Assignment count
4. []  Comparisons
5. []  Assignments

Delete
------
1. u32 Table ID
2. u32 Limit
3. u8  Comparison count
4. []  Comparisons
