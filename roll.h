typedef struct roll Roll;

Roll * roll_new (unsigned char n_dice);

void roll_free (Roll *roll);

void roll_set_id (Roll *roll,
		unsigned int id);

