#include <iostream>
#define PROGRAMMER_DAY 256

class Calendar {
	
	public:
		int year;
		int month;
		int day;

		void calcDate(Calendar &, int &, int, bool &);

};

int main() {

	Calendar prog;
	std::cin >> prog.year;

	// calculate date
	prog.day = 0;
	prog.month = 0;

	int tempDay = PROGRAMMER_DAY;
	bool checkMonth = true;
	for (auto countMonth = 1; countMonth <= 12; countMonth++) {
		
		if (!checkMonth) {
			break;
		}
		int monthlyDay;
		switch (countMonth) {
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				monthlyDay = 31;
				prog.calcDate(prog, tempDay, monthlyDay, checkMonth);
			case 4:
			case 6:
			case 9:
			case 11:
				monthlyDay = 30;
				prog.calcDate(prog, tempDay, monthlyDay, checkMonth);
			case 2:
				if (prog.year >= 1700 || prog.year <= 1917) {

					if (prog.year % 4 == 0) {
						monthlyDay = 29;
					} else {
						monthlyDay = 28;
					}
				
				} else if (prog.year == 1918) {

					monthlyDay = 15; // because it started at 14th february
				
				} else if (prog.year >= 1919 || prog.year <= 2700) {
					if (prog.year % 400 == 0 || (prog.year % 4 == 0 && prog.year % 100 != 0)) {
						monthlyDay = 29;
					} else {
						monthlyDay = 28;
					}
				} else {
					std::cout << "wrong!\n";
				}
				prog.calcDate(prog, tempDay, monthlyDay, checkMonth);
		}
	}

	return 0;
}

void Calendar::calcDate(Calendar &prog, int &tempDay, 
		const int monthlyDay, bool &checkMonth) {

	if (tempDay < monthlyDay) {
		checkMonth = false;
		prog.day = tempDay;
	} else {
		tempDay -= monthlyDay;
		prog.month += 1;
	}

}
