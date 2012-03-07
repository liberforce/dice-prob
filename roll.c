#include <stdlib.h>   /* for calloc */
#include <assert.h>   /* for assert */
#include "roll.h"

#define MAX(x, y) ((x > y) ? (x) : (y))

struct roll
{
	char * dice;
	unsigned char n_dice;
	char bonus;
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

unsigned char roll_get_bonus (const Roll *roll)
{
	assert (roll != NULL);
	return roll->bonus;
}

void roll_set_bonus (Roll *roll,
		char bonus)
{
	assert (roll != NULL);
	roll->bonus = bonus;
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
	unsigned char n;
	assert (roll != NULL);
	int sum = 0;

	for (n = 0; n < roll->n_dice; n++)
	{
		sum += roll_get_die (roll, n);
	}

	sum += roll_get_bonus (roll);

	return MAX (sum, 0);
}

