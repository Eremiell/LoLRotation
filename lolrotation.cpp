//(c) Jakub 'Eremiell' Marek, 2013
#include "lolrotation.hpp"

int main(int args, char **argv) {
	std::cout << "LoL Rotation (c) Jakub 'Eremiell' Marek, 2013" << std::endl << std::endl;
	bool run = true;
	while (run) {
		bool dynamic = false;
		for (int i = 1; i < args; i++) {
			if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-?" || std::string(argv[i]) == "\\?" || std::string(argv[i]) == "/?" || std::string(argv[i]) == "-h" || std::string(argv[i]) == "--usage" || std::string(argv[i]) == "-u") {
				std::cout << "Usage:" << std::endl << std::endl << "To invoke this usage guide, simply run the program with any of --help, -h, --usage, -u, -?, /? or \\?." << std::endl << std::endl << "First put the db.csv in the same folder (or run Rotation from where that file is)." << std::endl << std::endl << "LoL Rotation can be run as is or with \"--dynamic\" argument. It normally runs static algorithm, the argument flips it to dynamic, which fallbacks to static anyway for certain cases (no champions with positive last rotations, try W0)." << std::endl << std::endl << "Whenever it runs, it writes the new state into dbnew.csv. It will first try to load dbnew.csv, if it's present, continuing where it stopped. If not found, it will use db.csv." << std::endl << std::endl << "So if you wanna play around, you can generate as many weeks as you want. You can experiment with switching methods, or you can even generate \"older\" db.csv and observe alternative history. (See LoL Data Create's README for How-To.)" << std::endl << std::endl << "If you ever get bored of what you got, just delete dbnew.csv and it will start anew from db.csv. You can anytime generate new db.csv by LoL Data Create." << std::endl << std::endl;
				return 0;
			}
			if (std::string(argv[i]) == "--dynamic") {
				dynamic = true;
			}
		}
		Database d;
		int fdif = 0, adif = 0, sdif = 0, anum = 0;
		double fmean = 0, amean = 0, mmean = 0, cmean = 0, smean = 0, tmean = 0;
		int fcount = 0, acount = 0, mcount = 0, ccount = 0, scount = 0, tcount = 0;
		for (int i = 0; i < d.getSize(); i++) {
			Hero &h = d.getHero(i);
			switch (h.getRole()) {
				case Fighter:
					fmean += h.getDifficulty();
					fcount++;
					if (h.getLastRotated() == 1 && h.getDifficulty() > fdif) {
						fdif = h.getDifficulty();
					}
					break;
				case Assassin:
					amean += h.getDifficulty();
					acount++;
					if (h.getLastRotated() == 1 && h.getDifficulty() > adif) {
						adif = h.getDifficulty();
					}
					if (!h.getLastRotated()) {
						anum++;
					}
					break;
				case Mage:
					mmean += h.getDifficulty();
					mcount++;
					break;
				case Carry:
					cmean += h.getDifficulty();
					ccount++;
					break;
				case Support:
					smean += h.getDifficulty();
					scount++;
					if (!h.getLastRotated() && h.getDifficulty() > sdif) {
						sdif = h.getDifficulty();
					}
					break;
				case Tank:
					tmean += h.getDifficulty();
					tcount++;
					break;
			}
		}
		if (!fdif) {
			fdif = 100;
		}
		if (!adif) {
			adif = 100;
		}
		if (!sdif) {
			sdif = 100;
		}
		fmean /= fcount;
		amean /= acount;
		mmean /= mcount;
		cmean /= ccount;
		smean /= scount;
		tmean /= tcount;
		Hero fe, fh, ae, ah, me, mh, ce, ch, se, sh, te, th;
		if (dynamic) {
			std::vector<Hero> fep, fhp, aep, ahp, mep, mhp, cep, chp, sep, shp, tep, thp;
			for (int i = 0; i < d.getSize(); i++) {
				Hero &h = d.getHero(i);
				switch (h.getRole()) {
					case Fighter:
						if (h.getDifficulty() < fmean && h.getLastRotated() > 0) {
							for (int j = 0; j < h.getLastRotated() * h.getLastRotated(); j++) {
								fep.push_back(h);
							}
						}
						else if (h.getDifficulty() > fmean && h.getLastRotated() > 0) {
							for (int j = 0; j < h.getLastRotated() * h.getLastRotated(); j++) {
								fhp.push_back(h);
							}
						}
						break;
					case Assassin:
						if (h.getDifficulty() < amean && h.getLastRotated() > 0) {
							for (int j = 0; j < h.getLastRotated() * h.getLastRotated(); j++) {
								aep.push_back(h);
							}
						}
						else if (h.getDifficulty() > amean && h.getLastRotated() > 0) {
							for (int j = 0; j < h.getLastRotated() * h.getLastRotated(); j++) {
								ahp.push_back(h);
							}
						}
						break;
					case Mage:
						if (h.getDifficulty() < mmean && h.getLastRotated() > 0) {
							for (int j = 0; j < h.getLastRotated() * h.getLastRotated(); j++) {
								mep.push_back(h);
							}
						}
						else if (h.getDifficulty() > mmean && h.getLastRotated() > 0) {
							for (int j = 0; j < h.getLastRotated() * h.getLastRotated(); j++) {
								mhp.push_back(h);
							}
						}
						break;
					case Carry:
						if (h.getDifficulty() < cmean && h.getLastRotated() > 0) {
							for (int j = 0; j < h.getLastRotated() * h.getLastRotated(); j++) {
								cep.push_back(h);
							}
						}
						else if (h.getDifficulty() > cmean && h.getLastRotated() > 0) {
							for (int j = 0; j < h.getLastRotated() * h.getLastRotated(); j++) {
								chp.push_back(h);
							}
						}
						break;
					case Support:
						if (h.getDifficulty() < smean && h.getLastRotated() > 0) {
							for (int j = 0; j < h.getLastRotated() * h.getLastRotated(); j++) {
								sep.push_back(h);
							}
						}
						else if (h.getDifficulty() > smean && h.getLastRotated() > 0) {
							for (int j = 0; j < h.getLastRotated() * h.getLastRotated(); j++) {
								shp.push_back(h);
							}
						}
						break;
					case Tank:
						if (h.getDifficulty() < tmean && h.getLastRotated() > 0) {
							for (int j = 0; j < h.getLastRotated() * h.getLastRotated(); j++) {
								tep.push_back(h);
							}
						}
						else if (h.getDifficulty() > tmean && h.getLastRotated() > 0) {
							for (int j = 0; j < h.getLastRotated() * h.getLastRotated(); j++) {
								thp.push_back(h);
							}
						}
						break;
				}
			}
			if (!fep.size() || !fhp.size() || !aep.size() || !ahp.size() || !mep.size() || !mhp.size() || !cep.size() || !chp.size() || !sep.size() || !shp.size() || !tep.size() || !thp.size()) {
				dynamic = false;
			}
			if (dynamic) {
				srand(time(NULL));
				fe = fep[rand() % fep.size()];
				fh = fhp[rand() % fhp.size()];
				ae = aep[rand() % aep.size()];
				ah = ahp[rand() % ahp.size()];
				me = mep[rand() % mep.size()];
				mh = mhp[rand() % mhp.size()];
				ce = cep[rand() % cep.size()];
				ch = chp[rand() % chp.size()];
				se = sep[rand() % sep.size()];
				sh = shp[rand() % shp.size()];
				te = tep[rand() % tep.size()];
				th = thp[rand() % thp.size()];
			}
		}
		if (!dynamic) {
			for (int i = 0; i < d.getSize(); i++) {
				Hero &h = d.getHero(i);
				switch (h.getRole()) {
					case Fighter:
						if (h.getDifficulty() < fmean && h.getLastRotated() > fe.getLastRotated()) {
							fe = h;
						}
						else if (h.getDifficulty() > fmean && h.getLastRotated() > fh.getLastRotated()) {
							fh = h;
						}
						break;
					case Assassin:
						if (h.getDifficulty() < amean && h.getLastRotated() > ae.getLastRotated()) {
							ae = h;
						}
						else if (h.getDifficulty() > amean && h.getLastRotated() > ah.getLastRotated()) {
							ah = h;
						}
						break;
					case Mage:
						if (h.getDifficulty() < mmean && h.getLastRotated() > me.getLastRotated()) {
							me = h;
						}
						else if (h.getDifficulty() > mmean && h.getLastRotated() > mh.getLastRotated()) {
							mh = h;
						}
						break;
					case Carry:
						if (h.getDifficulty() < cmean && h.getLastRotated() > ce.getLastRotated()) {
							ce = h;
						}
						else if (h.getDifficulty() > cmean && h.getLastRotated() > ch.getLastRotated()) {
							ch = h;
						}
						break;
					case Support:
						if (h.getDifficulty() < smean && h.getLastRotated() > se.getLastRotated()) {
							se = h;
						}
						else if (h.getDifficulty() > smean && h.getLastRotated() > sh.getLastRotated()) {
							sh = h;
						}
						break;
					case Tank:
						if (h.getDifficulty() < tmean && h.getLastRotated() > te.getLastRotated()) {
							te = h;
						}
						else if (h.getDifficulty() > tmean && h.getLastRotated() > th.getLastRotated()) {
							th = h;
						}
						break;
				}
			}
		}
		std::vector<Hero> rotation;
		std::vector<Hero>::iterator it;
		if (anum > 1 || fdif >= fmean) {
			rotation.push_back(fe);
		}
		if (anum > 1 || fdif < fmean) {
			if (!rotation.size()) {
				rotation.push_back(fh);
			}
			else {
				for (it = rotation.begin(); it != rotation.end() && fh > *it; it++) {}
				rotation.insert(it, fh);
			}
		}
		if (anum <= 1 || adif >= amean) {
			for (it = rotation.begin(); it != rotation.end() && ae > *it; it++) {}
			rotation.insert(it, ae);
		}
		if (anum <= 1 || adif < amean) {
			for (it = rotation.begin(); it != rotation.end() && ah > *it; it++) {}
			rotation.insert(it, ah);
		}
		for (it = rotation.begin(); it != rotation.end() && me > *it; it++) {}
		rotation.insert(it, me);
		for (it = rotation.begin(); it != rotation.end() && mh > *it; it++) {}
		rotation.insert(it, mh);
		for (it = rotation.begin(); it != rotation.end() && ce > *it; it++) {}
		rotation.insert(it, ce);
		for (it = rotation.begin(); it != rotation.end() && ch > *it; it++) {}
		rotation.insert(it, ch);
		if (sdif >= smean) {
			for (it = rotation.begin(); it != rotation.end() && se > *it; it++) {}
			rotation.insert(it, se);
		}
		else {
			for (it = rotation.begin(); it != rotation.end() && sh > *it; it++) {}
			rotation.insert(it, sh);
		}
		for (it = rotation.begin(); it != rotation.end() && te > *it; it++) {}
		rotation.insert(it, te);
		for (it = rotation.begin(); it != rotation.end() && th > *it; it++) {}
		rotation.insert(it, th);
		for (unsigned int i = 0u; i < rotation.size(); i++) {
			std::cout << rotation[i].getName() << " ";
			switch (rotation[i].getRole()) {
				case Fighter:
					std::cout << "Fighter";
					break;
				case Assassin:
					std::cout << "Assassin";
					break;
				case Mage:
					std::cout << "Mage";
					break;
				case Carry:
					std::cout << "Carry";
					break;
				case Support:
					std::cout << "Support";
					break;
				case Tank:
					std::cout << "Tank";
					break;
			}
			std::cout << " " << rotation[i].getDifficulty() << " " << rotation[i].getLastRotated() << std::endl;
		}

		std::ofstream dbfostr("dbnew.csv");
		it = rotation.begin();
		for (int i = 0; i < d.getSize(); i++) {
			Hero &h = d.getHero(i);
			dbfostr << h.getName() << ",";
			switch (h.getRole()) {
				case Fighter:
					dbfostr << "Fighter,";
					break;
				case Assassin:
					dbfostr << "Assassin,";
					break;
				case Mage:
					dbfostr << "Mage,";
					break;
				case Carry:
					dbfostr << "Carry,";
					break;
				case Support:
					dbfostr << "Support,";
					break;
				case Tank:
					dbfostr << "Tank,";
					break;
			}
			dbfostr << h.getDifficulty() << ",";
			if (it != rotation.end() && h == *it) {
				dbfostr << "0" << std::endl;
				it++;
			}
			else if (h.getLastRotated() == -1) {
				dbfostr << 1000 << std::endl;
			}
			else {
				dbfostr << h.getLastRotated() + 1 << std::endl;
			}
		}
		dbfostr.close();
		std::cout << std::endl << "Generate another week? y/[n] ";
		std::string s;
		std::getline(std::cin, s);
		std::cout << std::endl;
		if (s[0] != 'y' && s[0] != 'Y') {
			run = false;
		}
	}
	return 0;
}
