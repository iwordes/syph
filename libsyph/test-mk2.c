#include <libsyph.h>

t_sytab	new_tab =
{
	"MyTab",
	1,
	{{ 0x02, SYF_UNIQ, ~0, 1 }},
	NULL,

	~0,
	~0
};

int		main()
{
	t_syph	sy;

	sy.port = 4243;
	sy.ip[0] = 127;
	sy.ip[1] = 0;
	sy.ip[2] = 0;
	sy.ip[3] = 1;
	sy_connect(&sy);
	new_tab.db = &sy;
	sy_create(&new_tab);
}
