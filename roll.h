typedef struct roll Roll;

Roll * roll_new (unsigned char n_dice);

void roll_free (Roll *roll);

void roll_set_id (Roll *roll,
		unsigned int id);

unsigned char roll_get_n_dice (const Roll *roll);

void roll_set_bonus (Roll *roll,
		char bonus);

unsigned char roll_get_die (const Roll *roll,
		unsigned char die);

unsigned int roll_get_sum (const Roll *roll);

