# Create table
??

# u32: id
?? ??

# str[8]: unique
?? { 00 00 00 08 } ??

# str[32]: no flags
?? { 00 00 00 ?? } 00

# End Request
00

# Schema name
#    4       U  s  e  r
00 00 00 04 55 73 65 72

# Field 1 name
#    2      i  d
00 00 00 02 69 64

# Field 2 name
#    4      n  a  m  e
00 00 00 04 6e 61 6d 65

# Field 3 name
#    4      p  a  s  s
00 00 00 04 70 61 73 73

