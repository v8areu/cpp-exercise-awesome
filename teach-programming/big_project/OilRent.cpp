#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "OilRent.hpp"

// default constructor without file input
OilRent::OilRent() {

}

// constructor definition
OilRent::OilRent( std::string oilFileName, std::string rentFileName ) {
	// the constructor read from file (filename as parameter) and add that to
	// the variable	oilPotencyMap
	
	// PROCESS OIL POTENCY MAP
	std::ifstream inputFileStream;
	inputFileStream.open(oilFileName);

	if ( inputFileStream.is_open() ) {

		// first, add the size of oilMap fron firstLine
		std::string oilMapSizeString;
		std::getline(inputFileStream, oilMapSizeString);
		std::istringstream issOilMapSizeString(oilMapSizeString);
		issOilMapSizeString >> oilMapSize[0] >> oilMapSize[1];

		unsigned int oilMapRow = oilMapSize[0];
		unsigned int oilMapCol = oilMapSize[1];

		// resize the vector
		oilPotencyMap.resize(oilMapRow);
		mapRentData.resize(oilMapRow);
		for (size_t i = 0; i < oilPotencyMap.size(); i++) {
			oilPotencyMap[i].resize(oilMapCol);
			mapRentData[i].resize(oilMapCol);
		}

		// initialize mapRentData.companyName and companyType with NONE
		for (size_t i = 0; i < mapRentData.size(); i++) {
			for (size_t j = 0; j < mapRentData[i].size(); j++) {
				mapRentData[i][j].companyName = "NONE";
				mapRentData[i][j].companyType = "NONE";
			}
		}

		// read the oil potency map
		for (size_t i = 0; i < oilMapRow; i++) {
			std::string oilPotencyLine;
			std::getline(inputFileStream, oilPotencyLine);

			// use delimiter space for parse each string
			std::string delimiter = " ";
			size_t pos = 0;
			size_t j = 0;
			std::string token;
				
			while (( pos = oilPotencyLine.find(delimiter)) != 
					std::string::npos ) {

				token = oilPotencyLine.substr(0, pos);
				oilPotencyMap[i][j] = std::stoi(token);
				oilPotencyLine.erase(0, pos + delimiter.length());			

				j++;
			}

			// for last instance
			oilPotencyMap[i][j] = std::stoi(oilPotencyLine);

		}
	} else {
		std::cout << "Input filenameMap Wrong!" << std::endl;
	}

	inputFileStream.close();

	// PROCESS RENT INFORMATION
	inputFileStream.open(rentFileName);
	if ( inputFileStream.is_open() ) {

		std::string oilRentSizeString;
		std::getline(inputFileStream, oilRentSizeString);
		oilRentSize = std::stoi(oilRentSizeString);

		// read each company
		for (size_t i = 0; i < oilRentSize; i++) {
			std::string mapDataString;
			std::getline(inputFileStream, mapDataString);
			std::istringstream issRentData(mapDataString);

			unsigned int tempRow, tempCol, tempYear;
			std::string tempCompanyName, tempCompanyType;
			issRentData >> tempRow >> tempCol >> tempCompanyName >> tempCompanyType >> tempYear;

			mapRentData[tempRow][tempCol].mapRow = tempRow;
			mapRentData[tempRow][tempCol].mapCol = tempCol;
			mapRentData[tempRow][tempCol].companyName = tempCompanyName;
			mapRentData[tempRow][tempCol].companyType = tempCompanyType;
			mapRentData[tempRow][tempCol].yearLeft = tempYear;

		}

	} else {
		std::cout << "Input filenameRent wrong!" << std::endl;
	}

	inputFileStream.close();
}

// for add data to mapRentData
std::vector<std::vector<OilRent::RentData>> OilRent::addRentData(std::vector<std::vector<OilRent::RentData>> mapRentData) {

	std::cout << std::endl;
	std::cout << "-- Tambah Penyewaan --" << std::endl;
	
	// input from user
	std::string tempCompanyName, tempCompanyType;
	unsigned int tempYear, tempRow, tempCol;
	
	std::cout << "> Masukkan nama perusahaan : ";
	std::cin >> tempCompanyName;

	std::cout << "> Masukkan jenis perusahaan : ";
	std::cin >> tempCompanyType;

	std::cout << "> Masukkan jangka waktu penyewaan : ";
	std::cin >> tempYear;

	std::cout << "> Masukkan baris area : ";
	std::cin >> tempRow;

	std::cout << "> Masukkan kolom area : ";
	std::cin >> tempCol;

	// input to our mapRentData object
	// first, check if the col and row whether it exist already
	if ( mapRentData[tempRow][tempCol].companyName != "NONE" ) {

		std::cout << "Penyewaan gagal! Area sudah disewa!" << std::endl << std::endl;

	} else {

		mapRentData[tempRow][tempCol].mapRow = tempRow;
		mapRentData[tempRow][tempCol].mapCol = tempCol;
		mapRentData[tempRow][tempCol].companyName = tempCompanyName;
		mapRentData[tempRow][tempCol].companyType = tempCompanyType;
		mapRentData[tempRow][tempCol].yearLeft = tempYear;

		std::cout << "Penyewaan berhasil!" << std::endl << std::endl << std::endl;

	}

	return mapRentData;
}

// deleteRentData implementation
std::vector<std::vector<OilRent::RentData>> OilRent::deleteRentData(std::vector<std::vector<OilRent::RentData>> mapRentData) {
	
	std::cout << "-- Hapus Penyewaan --" << std::endl << std::endl;

	unsigned int tempRow, tempCol;
	std::cout << "Masukkan baris area : ";
	std::cin >> tempRow;

	std::cout << "Masukkan kolom area : ";
	std::cin >> tempCol;

	// delete according to tempRow and tempCol
	// first, check if the col and row whether it exist already
	if ( mapRentData[tempRow][tempCol].companyName == "NONE" ) {

		std::cout << "Penghapusan penyewaan gagal! Tidak ada penyewaan pada area ini" << std::endl << std::endl;

	} else {

		mapRentData[tempRow][tempCol].mapRow = 0;
		mapRentData[tempRow][tempCol].mapCol = 0;
		mapRentData[tempRow][tempCol].companyName = "NONE";
		mapRentData[tempRow][tempCol].companyType = "NONE";
		mapRentData[tempRow][tempCol].yearLeft= 0;

		std::cout << "Penghapusan berhasil!" << std::endl << std::endl << std::endl;

	}

	return mapRentData;
}

// changeOilPotency private implementation
std::vector<std::vector<unsigned int>> OilRent::changeOilPotency(std::vector<std::vector<unsigned int>> oilPotencyMap) {

	std::cout << "-- Ubah Tingkat Potensi Minyak --" << std::endl << std::endl;
	
	// user input
	unsigned int tempRow, tempCol, tempOilPotency;

	std::cout << "> Masukkan baris area : ";
	std::cin >> tempRow;

	std::cout << "> Masukkan kolom area : ";
	std::cin >> tempCol;

	std::cout << "> Masukkan tingkat potensi minyak baru : ";
	std::cin >> tempOilPotency;

	// change oilPotencyMap
	oilPotencyMap[tempRow][tempCol] = tempOilPotency;

	return oilPotencyMap;
}

// printData
void OilRent::printData(unsigned int row, unsigned int col) {

	std::cout << mapRentData[row][col].mapRow << " ";
	std::cout << mapRentData[row][col].mapCol << " ";
	std::cout << mapRentData[row][col].companyName << " ";
	std::cout << mapRentData[row][col].companyType << " ";
	std::cout << mapRentData[row][col].yearLeft << " ";
	std::cout << oilPotencyMap[row][col] << std::endl;

}

// printDetailArea
void OilRent::printDetailArea(unsigned int counter, unsigned int row, unsigned int col) {

	std::cout << "Area " << counter;
	std::cout << std::endl;

	std::cout << "Posisi " << mapRentData[row][col].mapRow;
	std::cout << "-" << mapRentData[row][col].mapCol;
	std::cout << std::endl;

	std::cout << "Nama Perusahaan : " << mapRentData[row][col].companyName;
	std::cout << std::endl;

	std::cout << "Jenis Perusahaan : " << mapRentData[row][col].companyType;
	std::cout << std::endl;

	std::cout << "Sisa Jangka Waktu Penyewaan : " << mapRentData[row][col].yearLeft;
	std::cout << std::endl;
	std::cout << std::endl;

}

// print function for map
void OilRent::printOilMap() {

	unsigned int unrentedMap = 0;
	for (size_t i = 0; i < oilPotencyMap.size(); i++) {
		for (size_t j = 0; j < oilPotencyMap[i].size(); j++) {

			std::cout << oilPotencyMap[i][j] << "," << mapRentData[i][j].companyName << " ";
			
			if ( mapRentData[i][j].companyName == "NONE" ) {
				
				// increase unrented map if NONE is appear in company name
				unrentedMap += 1;
			}
		
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Jumlah area belum disewa : " << unrentedMap << std::endl << std::endl;

}

// print function for rent info
void OilRent::printOilRent() {
	static const unsigned int INFOCOUNT = 4;
	std::array<std::string, INFOCOUNT> infoOilRent = {
		"Kembali ke Menu Utama",
		"Nama Perusahaan",
		"Sisa Jangka Waktu Penyewaan",
		"Tingkat Potensi Minyak"
	};

	bool EXIT_OPTION_4 = false;

	unsigned int countArea = 0;
	while (!EXIT_OPTION_4) {
		
		std::cout << "-- Tampilkan Informasi Penyewaan --";
		std::cout << std::endl << std::endl;
		std::cout << "Terurut Berdasarkan : ";
		std::cout << std::endl;

		for (size_t i = 1; i < INFOCOUNT; i++) {
			std::cout << i << ".\t" << infoOilRent[i] << std::endl;
		}
		std::cout << "0.\t" << infoOilRent[0] << std::endl;

		// input from user
		unsigned int userInputRent;
		std::cout << "Pilihan : ";
		std::cin >> userInputRent;
		
		if ( userInputRent == 0) {

			EXIT_OPTION_4 = true;

		} else if ( userInputRent == 1 ) {
			
			const unsigned int tempMapRow = oilMapSize[0];
			const unsigned int tempMapCol = oilMapSize[1];
			
			std::vector<int> tempRow;
			std::vector<int> tempCol;
			std::string tempString = "";
			
			for (size_t i = 0; i < tempMapRow; i++) {
				for (size_t j = 0; j < tempMapCol; j++) {
					if ( mapRentData[i][j].companyName != "NONE" ) {

						// add countArea by 1
						countArea++;

						// sort
						for (size_t k = 0; k < countArea; k++) {
							if ( mapRentData[i][j].companyName > tempString ) {
								tempRow.push_back(i);
								tempCol.push_back(j);
							
							}
						}

						printData(i, j);
						std::cout << std::endl;
						
					}
				}
			}
		
		} else if ( userInputRent == 2 ) {

		} else if ( userInputRent == 3 ) {

		} else {
			std::cout << "Input Wrong!" << std::endl;
		}
	}
}

// save function
void OilRent::saveOilInfo(std::string outputFileName) {

	std::ofstream outputFile(outputFileName);

	// save how many rent
	outputFile << oilRentSize << std::endl;

	// save everything
	const unsigned int tempMapRow = oilMapSize[0];
	const unsigned int tempMapCol = oilMapSize[1];

	for (size_t i = 0; i < tempMapRow; i++) {
		for (size_t j = 0; j < tempMapCol; j++) {
			if ( mapRentData[i][j].companyName != "NONE" ) {

				outputFile << mapRentData[i][j].mapRow << " ";
				outputFile << mapRentData[i][j].mapRow << " ";
				outputFile << mapRentData[i][j].companyName << " ";
				outputFile << mapRentData[i][j].companyType << " ";
				outputFile << mapRentData[i][j].yearLeft<< " ";
				outputFile << oilPotencyMap[i][j] << std::endl;

			}
		}
	}
}

// the public version of addRentData (this one get into main)
void OilRent::addRentData() {

	mapRentData = addRentData(mapRentData);

}

// delete data
void OilRent::deleteRentData() {

	mapRentData = deleteRentData(mapRentData);

}

// change oilPotencyMap
void OilRent::changeOilPotency() {

	oilPotencyMap = changeOilPotency(oilPotencyMap);
}

// findOilRent implementation
void OilRent::findOilRent() {

	static const unsigned int INFOCOUNT = 4;
	std::array<std::string, INFOCOUNT> infoOilRent = {
		"Kembali ke Menu Utama",
		"Nama Perusahaan",
		"Sisa Jangka Waktu Penyewaan",
		"Tingkat Potensi Minyak"
	};

	bool EXIT_OPTION_8 = false;

	// define temp oil map size
	unsigned int tempOilRow = oilMapSize[0];
	unsigned int tempOilCol = oilMapSize[1];

	while (!EXIT_OPTION_8) {
		
		std::cout << "-- Cari Informasi Penyewaan --";
		std::cout << std::endl << std::endl;
		std::cout << "Berdasarkan:";
		std::cout << std::endl;

		for (size_t i = 1; i < INFOCOUNT; i++) {
			std::cout << i << ".\t" << infoOilRent[i] << std::endl;
		}
		std::cout << "0.\t" << infoOilRent[0] << std::endl;

		// input from user
		unsigned int userInputRent;
		std::cout << "Pilihan : ";
		std::cin >> userInputRent;
		
		// find the vector where dwells the input of user
		
		unsigned int countArea = 0;
		if ( userInputRent == 0) {

			EXIT_OPTION_8 = true;

		} else if ( userInputRent == 1 ) {

			std::string inputCompanyName;
			std::cout << "Masukkan nama perusahaan : ";
			std::cin >> inputCompanyName;
			std::cout << std::endl;
		
			for (size_t i = 0; i < tempOilRow; i++) {
				for (size_t j = 0; j < tempOilCol; j++) {
					if ( mapRentData[i][j].companyName == inputCompanyName ) {

						// add countArea by 1
						countArea++;

						printData(i, j);
						std::cout << std::endl;

						printDetailArea(countArea, i, j);
						
					}
				}
			}

			if ( countArea == 0) {
				
				std::cout << "Nama perusahaan tidak ditemukan!";
				std::cout << std::endl << std::endl;
			
			}

		} else if ( userInputRent == 2 ) {

			std::string inputCompanyType;
			std::cout << "Masukkan jenis perusahaan : ";
			std::cin >> inputCompanyType;
			std::cout << std::endl;
		
			for (size_t i = 0; i < tempOilRow; i++) {
				for (size_t j = 0; j < tempOilCol; j++) {
					if ( mapRentData[i][j].companyType == inputCompanyType ) {

						// add countArea by 1
						countArea++;

						printData(i, j);
						std::cout << std::endl;

						printDetailArea(countArea, i, j);
						
					}
				}
			}

			if ( countArea == 0) {
				
				std::cout << "Jenis perusahaan tidak ditemukan!";
				std::cout << std::endl << std::endl;
			
			}

		} else if ( userInputRent == 3 ) {

			unsigned int inputOilPotency;
			std::cout << "Masukkan potensi minyak : ";
			std::cin >> inputOilPotency;
			std::cout << std::endl;
		
			for (size_t i = 0; i < tempOilRow; i++) {
				for (size_t j = 0; j < tempOilCol; j++) {
					if ( oilPotencyMap[i][j] == inputOilPotency ) {

						// add countArea by 1
						countArea++;

						printData(i, j);
						std::cout << std::endl;

						printDetailArea(countArea, i, j);
						
					}
				}
			}

			if ( countArea == 0) {
				
				std::cout << "Potensi minyak tidak ditemukan!";
				std::cout << std::endl << std::endl;
			
			}

		} else {

			std::cout << "Input Wrong!" << std::endl;

		}

	}
}

// decrease time (year) of rent
void OilRent::increaseYear() {

	std::cout << "-- Majukan Waktu --";
	std::cout << std::endl << std::endl;

	unsigned int tempAddYear;
	std::cout << "Majukan waktu (dalam tahun) : ";
	std::cin >> tempAddYear;

	unsigned int oilMapRow = oilMapSize[0];
	unsigned int oilMapCol = oilMapSize[1];

	for (size_t i = 0; i < oilMapRow; i++) {
		for (size_t j = 0; j < oilMapCol; j++) {

			// if yearLeft is equal to zero then the land is unrented
			if ( mapRentData[i][j].yearLeft != 0) {

				// check if the difference of year is zero or less, then delete the rent info
				// if not, just decrease the yearLeft value of mapRentData
				int diff = static_cast<int>(mapRentData[i][j].yearLeft) - static_cast<int>(tempAddYear);
				if ( diff > 0 ) {
					mapRentData[i][j].yearLeft = static_cast<unsigned int>(diff);
				} else {

					// initialize value to 0 and "NONE"
					mapRentData[i][j].mapCol = 0;
					mapRentData[i][j].mapRow = 0;
					mapRentData[i][j].companyName = "NONE";
					mapRentData[i][j].companyType = "NONE";
					mapRentData[i][j].yearLeft = 0;

				}
			} 
		}
	}
}
