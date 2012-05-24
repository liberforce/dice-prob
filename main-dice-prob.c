#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "dice.h"

void print_dice (Dice *dice, unsigned int result)
{
	assert (dice != NULL);

	unsigned char n_dice = dice_get_n_dice (dice);
	unsigned char n;

	for (n = 0; n < n_dice; n++)
	{
		unsigned char die = dice_get_die (dice, n);
		printf ("%d;", die);
	}

	char modifier = dice_get_roll_modifier (dice);
	printf ("%d;", modifier);
	printf ("%d\n", result);
}

void print_freq_table (unsigned int *freq,
		unsigned char n_freq,
		int n_rolls)
{
	assert (freq != NULL);

	unsigned char i;

	printf ("\nFrequencies\n");
	printf ("n_freq = %d\n", n_freq);
	for (i = 0; i < n_freq; i++)
	{
		printf ("%d %d\n", i, freq[i]);
	}

	printf ("\nProbabilities\n");
	for (i = 0; i < n_freq; i++)
	{
		printf ("%d %g\n", i, (double)freq[i]/(double)n_rolls);
	}

	printf ("\nCumulated Probabilities\n");
	double cp = 0;
	for (i = 0; i < n_freq; i++)
	{
		cp += (double)freq[i]/(double)n_rolls;
		printf ("%d %g\n", i, cp);
	}
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

	Dice *dice = dice_new (n_dice);
	dice_set_roll_modifier (dice, modifier);

	int n_rolls = pow (6, n_dice);

	/* The 0 value, the wild die bonus, need to be taken into account */
	unsigned char n_freq = 1 + n_dice * 6 + modifier + 1;
	unsigned int *freq = calloc (n_freq, sizeof (unsigned int));
	int i;

	for (i = 0; i < n_rolls ; i++)
	{
		unsigned int result = dice_get_roll_result_from_int (dice, i);
		print_dice (dice, result);
		freq[result]++;
	}

	print_freq_table (freq, n_freq, n_rolls);
	dice_free (dice);
	return 0;
}

