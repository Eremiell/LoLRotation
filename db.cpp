//(c) Jakub 'Eremiell' Marek, 2013
#include "db.hpp"

Database::Database() {
	std::ifstream dbfstr("dbnew.csv");
	if (!dbfstr) {
		dbfstr.open("db.csv");
	}
	std::string line;
	for (std::getline(dbfstr, line); !dbfstr.eof() && !line.empty(); std::getline(dbfstr, line)) {
		int posend = line.find(",");
		std::string name = line.substr(0, posend);
		int posbeg = posend + 1;
		posend = line.find(",", posbeg);
		char roleenum = line.substr(posbeg, posend - posbeg).c_str()[0];
		int role;
		switch (roleenum) {
			case 'F':
			case 'f':
				role = Fighter;
				break;
			case 'A':
			case 'a':
				role = Assassin;
				break;
			case 'M':
			case 'm':
				role = Mage;
				break;
			case 'C':
			case 'c':
				role = Carry;
				break;
			case 'S':
			case 's':
				role = Support;
				break;
			case 'T':
			case 't':
				role = Tank;
				break;
			default:
				role = -1;
				break;
		}
		posbeg = posend + 1;
		posend = line.find(",", posbeg);
		int difficulty = std::strtol(line.substr(posbeg, posend - posbeg).c_str(), NULL, 10);
		posbeg = posend + 1;
		int lastRotated = std::strtol(line.substr(posbeg, std::string::npos).c_str(), NULL, 10);
		database.push_back(Hero(name, role, difficulty, lastRotated));
	}
	dbfstr.close();
}

int Database::getSize() {
    return database.size();
}

Hero& Database::getHero(int i) {
	return database[i];
}
