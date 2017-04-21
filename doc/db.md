Rough overview:
- 4096B db header
- 4096/8192B table header
- N 4096B blocks per table
- N (schema)B blocks per table (within major blocks)
- Preallocate N blocks per

Database Header
---------------
1. u8 endian order (0x00 little or 0xff big)
2. 0x42
3. u16 header length in 4096B blocks (future limitation: 4194302 tables max)
4. u32 padding
5. u32 next table id
6. u32 table count
7. Table index [ u32 id, u32 block offset ]

Table Header
------------
1. u32 table ID
2. u8 field count
3. fields [ u8:type, u8:flags, i8[30]:label ]
	The first field is treated as the primary key for the table.
4. u32 entry count
5. Reserved
?. u32 entry size?
