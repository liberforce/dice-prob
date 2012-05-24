all:
	gcc -Wall -lm main-dice-roll.c roll.c -o dice-roll 
	gcc -Wall -lm main-dice-prob.c roll.c -o dice-prob 
