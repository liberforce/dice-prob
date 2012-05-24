all:
	gcc -Wall -lm main-dice-roll.c dice.c -o dice-roll 
	gcc -Wall -lm main-dice-prob.c dice.c -o dice-prob 
