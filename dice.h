typedef struct dice Dice;

Dice * dice_new (unsigned char n_dice);

void dice_free (Dice *dice);

unsigned int dice_get_roll_result_from_int (Dice *dice,
		unsigned int roll);

unsigned int dice_get_roll_result (const Dice *dice);

unsigned char dice_get_n_dice (const Dice *dice);

void dice_set_roll_modifier (Dice *dice,
		char modifier);

char dice_get_roll_modifier (const Dice *dice);

unsigned char dice_get_die (const Dice *dice,
		unsigned char die);

unsigned int dice_roll (Dice *dice);

void dice_debug (const Dice *dice);

