#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "dice.h"

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		printf ("Usage: %s N_DICE\n", argv[0]);
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

	Dice *dice = dice_new (n_dice);
	dice_set_roll_modifier (dice, modifier);
	int result = dice_roll (dice);
	dice_debug (dice);
	printf ("%d\n", result);
	dice_free (dice);
	return 0;
}

