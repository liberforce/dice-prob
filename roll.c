#include <stdlib.h>   /* for calloc */
#include <assert.h>   /* for assert */
#include <sys/time.h> /* for gettimeofday */
#include <math.h>     /* for pow */
#include <stdio.h>    /* for printf */
#include "roll.h"

#define MAX(x, y) ((x > y) ? (x) : (y))

struct roll
{
	char * dice;
	unsigned char n_dice;
	char modifier;
};

Roll * roll_new (unsigned char n_dice)
{
	Roll * roll = calloc (1, sizeof (Roll));
	roll->dice = calloc (n_dice, sizeof (char));
	roll->n_dice = n_dice;
	return roll;
}

void roll_free (Roll *roll)
{
	if (roll != NULL)
	{
		free (roll->dice);
		free (roll);
	}
}

void roll_set_id (Roll *roll,
		unsigned int id)
{
	assert (roll != NULL);
	unsigned char n_dice = roll->n_dice;

	while (n_dice-- > 0)
	{
		/* id is in the [0;5] range */
		int digit = id % 6;

		/* A die roll is in the [1;6] range */
		digit += 1;

		id /= 6;

		roll->dice[n_dice] = digit;
	}
}

unsigned char roll_get_n_dice (const Roll *roll)
{
	assert (roll != NULL);
	return roll->n_dice;
}

char roll_get_modifier (const Roll *roll)
{
	assert (roll != NULL);
	return roll->modifier;
}

void roll_set_modifier (Roll *roll,
		char modifier)
{
	assert (roll != NULL);
	roll->modifier = modifier;
}

unsigned char roll_get_die (const Roll *roll,
		unsigned char nth_die)
{
	assert (roll != NULL);
	assert (nth_die >= 0);
	assert (nth_die < roll->n_dice);

	return roll->dice[nth_die];
}

unsigned int roll_get_value (const Roll *roll)
{
	assert (roll != NULL);
	assert (roll->n_dice);

	unsigned char n;
	int sum = 0;
	int penalty = 0;

	/* Wild die will always be at index 0 */
	for (n = 0; n < roll->n_dice; n++)
	{
		sum += roll_get_die (roll, n);
	}

	if (roll_get_die (roll, 0) == 6)
	{
		sum += 1; /* Give minimum bonus to have finite values */
	}
	else if (roll_get_die (roll, 0) == 1)
	{
		for (n = 1; n < roll->n_dice; n++)
		{
			penalty = MAX (penalty, roll_get_die (roll, n));
		}
		sum = sum - penalty - 1;
	}

	sum += roll_get_modifier (roll);

	return MAX (sum, 0);
}

unsigned int roll_roll (Roll *roll)
{
	assert (roll != NULL);
	assert (roll->n_dice > 0);

	int n_rolls = pow (6, roll->n_dice);

	/* Init random numbers generator */
	struct timeval tv;
	gettimeofday (&tv, NULL);
	srand (tv.tv_usec);

	unsigned int faces = rand () % n_rolls;
	roll_set_id (roll, faces);
	return roll_get_value (roll);
}

void roll_debug (const Roll *roll)
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
	printf ("%d = ", modifier);

	int value = roll_get_value (roll);
	printf ("%d\n", value);
}

