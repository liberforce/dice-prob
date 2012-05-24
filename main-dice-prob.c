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

	Roll *roll = roll_new (n_dice);
	roll_set_modifier (roll, modifier);

	int n_rolls = pow (6, n_dice);
	/* The 0 value, the wild die bonus, need to be taken into account */
	unsigned char n_freq = 1 + n_dice * 6 + modifier + 1;
	unsigned int *freq = calloc (n_freq, sizeof (unsigned int));
	int i;

	for (i = 0; i < n_rolls ; i++)
	{
		roll_set_id (roll, i);
		print_roll (roll);
		freq[roll_get_value (roll)]++;
	}

	print_freq_table (freq, n_freq, n_rolls);
	roll_free (roll);
	return 0;
}

