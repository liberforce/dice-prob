#ifndef DIE_H
#define DIE_H

typedef struct die Die;

Die * die_new (unsigned char n_sides);

void die_free (Die *die);

int die_roll (Die *die);

int die_roll_with_modifier (Die *die,
		char modifier);

#endif // DIE_H

