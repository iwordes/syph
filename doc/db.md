Rough overview:
- 4096B db header
- 4096/8192B table header
- N 4096B blocks per table
- N (schema)B blocks per table (within major blocks)
- Preallocate N blocks per

Database Header
---------------
1. Reserved

Table Header
------------
1. u32 table ID
2. u8 field count
2. u8[2][] field [ type, flags ]
4. i8[32][] field names
5. Reserved
