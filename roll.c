#include <stdlib.h>   /* for calloc */
#include <assert.h>   /* for assert */
#include "roll.h"

struct roll
{
	char * dice;
	unsigned char n_dice;
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

