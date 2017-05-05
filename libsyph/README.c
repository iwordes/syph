#include <libsyph.h>
#include <stdio.h>

typedef struct	User
{
	uint32_t	id;
	uint8_t		name[11];
	uint8_t		pass[65];
}				User;

t_sytab			tab_user =
{
	"Users",
	3,
	{
		{ 0x02, SYF_UNIQ, ~0, 1 },
		{ 0x0d, SYF_UNIQ, ~0, 11 },
		{ 0x00, SYF_NONE, ~0, 65 }
	},
	NULL,

	0,
	0
};

User			Users[] =
{
	{ ~0, "iwordes", "19ad3616216eea07d6f1adb48a774dd61c822a5ae800ef43b65766372ee4869b" },
	{ ~0, "kdavis",  "45df23dc5bfe30ec2e2bf012f00bc9b3f7e15f715498bc8f268ce3c352ee83ed" },
	{ ~0, "kyork",   "0282644cb535bd49babdbbbb5100c3c8380e4a00fa24ea2bd0a6a87262d8bdd9" }
};

int				main()
{
	t_syasn	asn;
	t_sycmp	cmp;
	t_sysel	sel;
	t_syph	sy;

	sy.port = 4243;
	sy.ip[0] = 127;
	sy.ip[1] = 0;
	sy.ip[2] = 0;
	sy.ip[3] = 1;
	if (!sy_connect(&sy))
		return (1);

	tab_user.db = &sy;
	if (!sy_create(&tab_user))
		return (2);

	printf("ent_size: %u\n", tab_user.ent_size);
	printf("Insert:\n");
	for (int i = 0; i < 3; i++)
		printf("~0\t'%-8s'\t'%-s'\n", Users[i].name, Users[i].pass);
	printf("\n");

	if (!sy_insert(&tab_user, 3, Users))
		return (3);

	bzero(&sel, sizeof(sel));
	sel.limit = 3;
	sel.data = Users;
	sel.tab = &tab_user;
	if (!sy_select(&sel))
		return (4);

	printf("Select:\n");
	for (int i = 0; i < 3; i++)
		printf("%.2u\t'%-8s'\t'%-s'\n", Users[i].id, Users[i].name, Users[i].pass);
	printf("\n");

	bzero(&asn, sizeof(asn));
	bzero(&cmp, sizeof(cmp));

	cmp.len = 0;
	cmp.data_len = 0;

	asn.len = 1;
	asn.data_len = 11;
	asn.data = "Who?\0\0\0\0\0\0";
	asn.asn[0].id = 1;
	asn.asn[0].op = SYA_SET;
	if (!sy_update(&tab_user, &cmp, &asn))
		return (5);

	if (!sy_select(&sel))
		return (6);

	printf("Update:\n");
	for (int i = 0; i < 3; i++)
		printf("%.2d\t'%-8s'\t'%-s'\n", Users[i].id, Users[i].name, Users[i].pass);

	if (!sy_delete(&tab_user, &cmp, 3))
		return (6);

	return (0);
}
