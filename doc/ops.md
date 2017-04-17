 hex | effect
 ----|-----------------------------------------------------------------------------
  00 | ???
 --- | Database operations.
  10 | List databases.
  11 | Create database.
  1? | Select database.
  1f | Delete database.
 --- | Table operations.
  20 | List tables.
  21 | Create table.
  2? | Show table.
  21 | Select from table. (u8:id, u8[]:fields, subops)
  22 |

  2f | Delete table.
 --- | Range reserved.
  30 |
  3f |
 --- | ...
  40 |
 --- | ...
  50 |
 --- | Special operations.
  ff | Ping.
