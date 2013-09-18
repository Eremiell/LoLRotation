//(c) Jakub 'Eremiell' Marek, 2013
#ifndef DB_HPP
#define DB_HPP

#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "hero.hpp"

class Database {
	public:
		Database();
		int getSize();
		Hero& getHero(int i);
	protected:
		std::vector<Hero> database;
};

#endif
