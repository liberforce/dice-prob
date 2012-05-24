#include <stdlib.h>   /* for calloc */
#include <assert.h>   /* for assert */
#include <sys/time.h> /* for gettimeofday */
#include <math.h>     /* for pow */
#include <stdio.h>    /* for printf */
#include "dice.h"

#define MAX(x, y) ((x > y) ? (x) : (y))

struct dice
{
	char * roll;
	unsigned char n_dice;
	unsigned char is_prob_mode;
	char modifier;
};

Dice * dice_new (unsigned char n_dice,
		unsigned char is_prob_mode)
{
	Dice * dice = calloc (1, sizeof (Dice));
	dice->roll = calloc (n_dice, sizeof (char));
	dice->n_dice = n_dice;
	dice->is_prob_mode = is_prob_mode;
	return dice;
}

void dice_free (Dice *dice)
{
	if (dice != NULL)
	{
		free (dice->roll);
		free (dice);
	}
}

static void dice_set_roll (Dice *dice,
		unsigned int roll)
{
	assert (dice != NULL);
	unsigned char n_dice = dice->n_dice;
	static const int base = 6;

	while (n_dice-- > 0)
	{
		/* Each digit extracted is in the [0;base-1] range 
		   but possibles values for a die are in the [1;base] range */
		int digit = (roll % base) + 1;
		dice->roll[n_dice] = digit;

		roll /= base;
	}
}

unsigned char dice_get_n_dice (const Dice *dice)
{
	assert (dice != NULL);
	return dice->n_dice;
}

char dice_get_roll_modifier (const Dice *dice)
{
	assert (dice != NULL);
	return dice->modifier;
}

void dice_set_roll_modifier (Dice *dice,
		char modifier)
{
	assert (dice != NULL);
	dice->modifier = modifier;
}

char dice_get_die (const Dice *dice,
		unsigned char nth_die)
{
	assert (dice != NULL);
	assert (nth_die >= 0);
	assert (nth_die < dice->n_dice);

	return dice->roll[nth_die];
}

void dice_set_die (const Dice *dice,
		unsigned char nth_die,
		char value)
{
	assert (dice != NULL);
	assert (nth_die >= 0);
	assert (nth_die < dice->n_dice);

	dice->roll[nth_die] = value;
}

int dice_get_roll_result (const Dice *dice)
{
	assert (dice != NULL);
	assert (dice->n_dice);

	unsigned char n;
	int sum = 0;
	int penalty = 0;
	int needs_reroll = FALSE;

	/* Wild die is always at index 0 */
	if (dice_get_die (dice, 0) == 6)
	{
		if (dice->is_prob_mode)
		{
			needs_reroll = FALSE;

			/* Give minimum bonus to have finite values */
			dice_set_die (dice, 0, 7);
		}
		else
		{
			/* Re-roll wild die as long as it gives a 6 */
			needs_reroll = TRUE;
		}
	}
	else if (dice_get_die (dice, 0) == 1)
	{
		for (n = 1; n < dice->n_dice; n++)
		{
			penalty = MAX (penalty, dice_get_die (dice, n));
		}
		dice_set_die (dice, 0, - penalty);
	}

	while (needs_reroll)
	{
		int n_possible_rolls = pow (6, dice->n_dice);
		int roll = (rand () % n_possible_rolls) + 1;
		needs_reroll = (roll == 6);
		dice_set_die (dice, 0, roll + dice_get_die (dice, 0));
	}

	for (n = 0; n < dice->n_dice; n++)
	{
		sum += dice_get_die (dice, n);
	}

	sum += dice_get_roll_modifier (dice);

	return MAX (sum, 0);
}

unsigned int dice_get_roll_result_from_int (Dice *dice,
		unsigned int roll)
{
	dice_set_roll (dice, roll);
	return dice_get_roll_result (dice);
}

unsigned int dice_roll (Dice *dice)
{
	assert (dice != NULL);
	assert (dice->n_dice > 0);

	int n_possible_rolls = pow (6, dice->n_dice);

	/* Init random numbers generator */
	struct timeval tv;
	gettimeofday (&tv, NULL);
	srand (tv.tv_usec);

	unsigned int roll = rand () % n_possible_rolls;
	return dice_get_roll_result_from_int (dice, roll);
}

void dice_debug (const Dice *dice)
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
	printf ("modifier %+-d = ;", modifier);

	int value = dice_get_roll_result (dice);
	printf ("result = %d\n", value);
}

