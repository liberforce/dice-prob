#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "roll.h"

/* val is a number in base 6 */
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

	int sum = roll_get_sum (roll);
	printf ("%d\n", sum);
}

int main (int argc, char **argv)
{
	int n_dice;
	
	if (argc != 2)
	{
		printf ("Usage: dice-prob N_DICE\n");
		return -1;
	}

	n_dice = atoi (argv[1]);

	Roll *roll = roll_new (n_dice);
	int counter = 0;
	int i;
	int maxval = pow (6, n_dice);

	for (i = 0; i < maxval ; i ++)
	{
		roll_set_id (roll, counter++);
		print_roll (roll);
	}

	roll_free (roll);
	return 0;
}

