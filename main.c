#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <glib.h>
#include "die.h"

static gboolean is_probability_mode = FALSE;
static char **remaining_args = NULL;
static GOptionEntry entries[] = 
{
	{
		"stats",
		's',
		0,
		G_OPTION_ARG_NONE,
		&is_probability_mode,
		"Enables statistical study of the roll.",
		NULL,
	},
	{
		G_OPTION_REMAINING,
		0,
		0,
		G_OPTION_ARG_STRING_ARRAY,
		&remaining_args,
		"Roll format descriptor.",
		NULL,
	},
	{
		NULL
	}
};


void print_freq_table (unsigned int *freq,
		unsigned char n_freq,
		int n_rolls)
{
	assert (freq != NULL);

	unsigned char i;

	printf ("\nFrequencies\n");
	for (i = 0; i < n_freq; i++)
	{
		printf ("%d\t%d\n", i, freq[i]);
	}

	printf ("\nProbabilities\n");
	for (i = 0; i < n_freq; i++)
	{
		printf ("%d\t%g\n", i, (double)freq[i]/(double)n_rolls);
	}

	printf ("\nCumulated Probabilities\n");
	double cp = 0;
	for (i = 0; i < n_freq; i++)
	{
		cp += (double)freq[i]/(double)n_rolls;
		printf ("%d\t%g\n", i, cp);
	}
}

int main (int argc, char **argv)
{
	GError *error = NULL;
	GOptionContext *context = g_option_context_new ("ROLL_FORMAT_STRING\n");
	g_option_context_set_summary (context,
			"Rolls some dice or shows the odds to get a successful roll.\n"
			"ROLL_FORMAT_STRING may be for example 1d10+2 or 3d6-1.");
	g_option_context_add_main_entries (context,
			entries,
			NULL);
	if (! g_option_context_parse (context, &argc, &argv, &error))
	{
		g_print ("option parsing failed: %s\n", error->message);
		exit (1);
	}

	if (remaining_args == NULL)
	{
		char *help_str = g_option_context_get_help (context, TRUE, NULL);
		g_print ("%s", help_str);
		g_free (help_str);
		exit (2);
	}

	char *n_sides_str = NULL;
	char *modifier_str = NULL;
	char *roll_format_str = remaining_args[0];
	char *n_dice_str = roll_format_str;
	char *ptr = roll_format_str;
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
	int score = 0; // roll result, including modifiers
	int i;

	if (is_probability_mode)
	{
		/* For a roll result (which is 1-based) to be used as frequency array
		 * index (which is 0-based), the 0 value needs to be taken into
		 * account. It may in fact happen when using a negative modifier */
		int max_score = n_dice * n_sides + modifier;
		int n_freq = max_score + 1;
		unsigned int *freq = calloc (n_freq, sizeof (unsigned int));

		/* Enumerating all the possible rolls is like counting in the
		 * "n_sides" base with "n_dice" digits. */
		int n_rolls = pow (n_sides, n_dice);
		for (i = 0; i < n_rolls; i++)
		{
			score = 0;
			int roll = i;
			int die_index = n_dice;

			// for each die
			while (die_index-- > 0)
			{
				// get rightmost die value
				score += (roll % n_sides) + 1;
				// right-shift
				roll /= n_sides;
			}
			score += modifier;
			freq[score]++;
		}

		print_freq_table (freq, n_freq, n_rolls);
		free (freq);
	}
	else
	{
		/* Roll the dice */
		Die *die = die_new (n_sides);
		for (i = 0; i < n_dice; i++)
		{
			score += die_roll (die);
		}

		score = MAX (0, score + modifier);
		printf ("%d\n", score);
		die_free (die);
	}

	return 0;
}

