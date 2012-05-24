typedef struct roll Roll;

Roll * roll_new (unsigned char n_dice);

void roll_free (Roll *roll);

void roll_set_id (Roll *roll,
		unsigned int id);

unsigned char roll_get_n_dice (const Roll *roll);

void roll_set_modifier (Roll *roll,
		char modifier);

char roll_get_modifier (const Roll *roll);

unsigned char roll_get_die (const Roll *roll,
		unsigned char die);

unsigned int roll_get_value (const Roll *roll);

unsigned int roll_roll (Roll *roll);

