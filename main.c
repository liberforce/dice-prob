#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "roll.h"

void print_roll (Roll *roll)
{
	assert (roll != NULL);

	unsigned char n_dice = roll_get_n_dice (roll);
	unsigned char n;

	for (n = 0; n < n_dice; n++)
	{
		unsigned char die = roll_get_die (roll, n);
		printf ("%d;", die);
	}

	char modifier = roll_get_modifier (roll);
	printf ("%d;", modifier);

	int value = roll_get_value (roll);
	printf ("%d\n", value);
}

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		printf ("Usage: dice-prob N_DICE\n");
		return -1;
	}

	char *str_n_dice = argv[1];
	char *ptr = argv[1];

	do
	{
		if  (*ptr == 'd' || *ptr == 'D')
		{
			*ptr = '\0';
		}
	}
	while (*ptr++);

	char *str_modifier = ptr;
	int n_dice = atoi (str_n_dice);
	int modifier = atoi (str_modifier);

	Roll *roll = roll_new (n_dice);
	roll_set_modifier (roll, modifier);

	int maxval = pow (6, n_dice);
	int i;

	for (i = 0; i < maxval ; i++)
	{
		roll_set_id (roll, i);
		print_roll (roll);
	}

	roll_free (roll);
	return 0;
}

