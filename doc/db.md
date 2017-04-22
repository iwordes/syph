Rough overview:
- 4096B db header
- 4096/8192B table header
- N 4096B blocks per table
- N (schema)B blocks per table (within major blocks)
- Preallocate N blocks per

Database Header
---------------
1. u8 endian order (0x00 little or 0xff big)
2. 0x2a
3. u16 header length in 4096B blocks
4. u32 next table id
5. u32 next table block-offset
6. u32 table count
7. Table index [ u32 id, u32 block offset ]

Table Header
------------
1. u32 table ID
2. u32 entry count
3. u64 next entry ID
4. u32 body length in blocks
4. u16 header length in blocks
5. u8[33] label
6. u8 field count
7. fields [ u8:type, u8:flags ]
	The first field is treated as the primary key for the table.
	Additionally, it must be an unsigned integer of some size.
	That field is automatically managed for the user, but can be overridden,
	provided one does not try to insert a value already used.
