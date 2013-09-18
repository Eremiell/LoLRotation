//(c) Jakub 'Eremiell' Marek, 2013
#include "hero.hpp"

std::string Hero::getName() {
	return name;
}

int Hero::getRole() {
	return role;
}

int Hero::getDifficulty() {
	return difficulty;
}

int Hero::getLastRotated() {
	return lastRotated;
}

bool Hero::operator==(Hero h) {
    return getName() == h.getName();
}

bool Hero::operator!=(Hero h) {
    return getName() != h.getName();
}

bool Hero::operator>(Hero h) {
    return getName() > h.getName();
}

bool Hero::operator<(Hero h) {
    return getName() < h.getName();
}

bool Hero::operator>=(Hero h) {
    return getName() >= h.getName();
}

bool Hero::operator<=(Hero h) {
    return getName() <= h.getName();
}

