#include <stdlib.h>   /* for calloc */
#include <assert.h>   /* for assert */
#include <sys/time.h> /* for gettimeofday */
#include <math.h>     /* for pow */
#include <stdio.h>    /* for printf */
#include <glib.h>     /* for MAX */
#include "die.h"

struct die
{
	char n_sides;
};

Die * die_new (unsigned char n_sides)
{
	Die * die = calloc (1, sizeof (Die));
	die->n_sides = n_sides;
	return die;
}

void die_free (Die *die)
{
	if (die != NULL)
	{
		free (die);
	}
}

int die_roll (Die *die)
{
	assert (die != NULL);

	/* Init random numbers generator */
	struct timeval tv;
	gettimeofday (&tv, NULL);
	srand (tv.tv_usec);

	/* result is in the [0;n-1] range, so we need to add 1 for [1;n] */  
	return (rand () % die->n_sides + 1);
}

int die_roll_with_modifier (Die *die,
		char modifier)
{
	return MAX (0, (int) die_roll (die) + modifier);
}

