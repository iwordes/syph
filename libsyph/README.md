libsyph
-------
Prototype C API for SyphDB.

Usage
-----
1. Configure a `t_syph` with an IP and port.
2. Run `sy_connect(&syph)` to initiate the connection.
3. For any table you wish to create or interact with, run `sy_create` first.
4. Use `sy_``insert|select|update|delete` as per `libsyph.h`!
4. ???
5. Profit!

See `README.c` for an example in action.
See `libsyph.h` for per-function documentation.

Issues
------
1. If you want to use nice structs to handle entries, be sure to account for C struct padding. That can really ruin your day.
	- Signed, The Developer
