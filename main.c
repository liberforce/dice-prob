#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <glib.h>
#include "die.h"

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		/* Valid: 1d6+4 */
		printf ("Usage: %s N_DICE d N_SIDES ± MODIFIER\n", argv[0]);
		return -1;
	}

	char *n_dice_str = argv[1];
	char *n_sides_str = NULL;
	char *modifier_str = NULL;

	char *ptr = argv[1];
	do
	{
		if (*ptr == 'd' || *ptr == 'D')
		{
			*ptr = '\0';
			n_sides_str = ++ptr;
		}
		else if (*ptr == '+' || *ptr == '-')
		{
			modifier_str = ptr;
		}
	}
	while (*ptr++);

	int n_dice = atoi (n_dice_str);
	int n_sides = (n_sides_str) ? atoi (n_sides_str) : 0;
	int modifier = (modifier_str) ? atoi (modifier_str) : 0;
	int result = 0;
	Die *die = die_new (n_sides);
	int i = 0;

	for (i = 0; i < n_dice; i++)
	{
		int roll = die_roll (die);
		result += roll;
	}

	result = MAX (0, result + modifier);
	printf ("%d\n", result);
	die_free (die);
	return 0;
}

