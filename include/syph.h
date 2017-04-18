#ifndef SYPH_H
# define SYPH_H

// ...

typedef struct	s_field
{
	uint8_t		id;
	uint8_t		type;

	uint16_t	f_id: 1;
	uint16_t	f_null: 1;
	uint16_t	f_unique: 1;

	char		*name;
}				t_field;

typedef struct	s_table
{
	uint32_t	id;
	t_field		*schema;

	// ...
}				t_table;

typedef struct	s_db
{
	char		*loc;
	int			fd;

	// ...
}				t_db;

// Are request/response types even necessary on the server side?

typedef struct	s_req
{
	// ...
}				t_req;

typedef struct	s_res
{
	// ...
}				t_res;

// ...

#endif
