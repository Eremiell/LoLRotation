//(c) Jakub 'Eremiell' Marek, 2013
#ifndef HERO_HPP
#define HERO_HPP

#include <string>
#include <climits>

enum Role {Fighter, Assassin, Mage, Carry, Support, Tank};

class Hero {
	public:
		Hero(std::string name = "", int role = -1, int difficulty = 0, int lastRotated = INT_MIN) : name(name), role(role), difficulty(difficulty), lastRotated(lastRotated) {};
		std::string getName();
		int getRole();
		int getDifficulty();
		int getLastRotated();
		bool operator==(Hero h);
		bool operator!=(Hero h);
		bool operator>(Hero h);
		bool operator<(Hero h);
		bool operator>=(Hero h);
		bool operator<=(Hero h);
		bool operator==(int i);
		bool operator!=(int i);
		bool operator>(int i);
		bool operator<(int i);
		bool operator>=(int i);
		bool operator<=(int i);
		friend bool operator==(int i, Hero h);
		friend bool operator!=(int i, Hero h);
		friend bool operator>(int i, Hero h);
		friend bool operator<(int i, Hero h);
		friend bool operator>=(int i, Hero h);
		friend bool operator<=(int i, Hero h);
		bool operator==(double d);
		bool operator!=(double d);
		bool operator>(double d);
		bool operator<(double d);
		bool operator>=(double d);
		bool operator<=(double d);
		friend bool operator==(double d, Hero h);
		friend bool operator!=(double d, Hero h);
		friend bool operator>(double d, Hero h);
		friend bool operator<(double d, Hero h);
		friend bool operator>=(double d, Hero h);
		friend bool operator<=(double d, Hero h);
	protected:
		std::string name;
		int role;
		int difficulty;
		int lastRotated;
};

#endif
