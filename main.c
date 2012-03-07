#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* val is a number in base 6 */
void print_roll (int val, int n_dice)
{
	int sum = 0;

	while (n_dice-- > 0)
	{
		int digit;

		if (val >= 6)
		{
			digit = val / 6;
			val -= digit * 6;
		}
		else
		{
			digit = val;
		}

		/* Dice rolls are in the [1;6] range */
		digit += 1;
		sum += digit;
		printf ("%d;", digit);
	}
	printf ("%d\n", sum);
}

int main (int argc, char **argv)
{
	int n_dice;
	
	if (argc != 2)
	{
		printf ("Usage: dice-prob N_DICE\n");
		return -1;
	}

	n_dice = atoi (argv[1]);

	int counter = 0;
	int i;
	int maxval = pow (6, n_dice);

	for (i = 0; i < maxval ; i ++)
	{
		print_roll (counter++, n_dice);
	}

	return 0;
}

