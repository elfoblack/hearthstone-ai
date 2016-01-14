#ifndef _CARD_H
#define _CARD_H

class Card
{
	public:
		Card() : id(0) {}
		Card(int id) : id(id) {}

	public:
		int id;

		enum Type {
			MINION, SPELL, WEAPON, SECRET
		} type;

		struct Minion {
			int cost;
			int attack;
			int hp;
			int hp_max;
		};

		struct Spell {
			// TODO
		};

		struct Weapon {
			int cost;
			int attack;
			int durability;
		};

		struct Secret {
			// TODO
		};

		union {
			Minion minion;
			Spell spell;
			Weapon weapon;
			Secret secret;
		};
};

#endif
