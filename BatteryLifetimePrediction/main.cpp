#include <stdio.h>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>

#define BatteryLogPath "/home/janosch/BatLog"
#define EnergyNowPath "/sys/class/power_supply/BAT0/energy_now"
#define EnergyFullPath "/sys/class/power_supply/BAT0/energy_full"
#define DEBUG

std::vector<std::tuple<int, int>> vecStateList;
std::vector<__uint32_t> vecBatteryLogEntrys;
__uint32_t	ulCompare = 0;
int 		change = 0;
long nMinutesLeft = 0;

void changeChange(int state, int listEntry){
	if (state == change) return;
	change = state;
	vecStateList.push_back(std::make_tuple(listEntry, state));
	vecBatteryLogEntrys.clear();
}

bool readBatteryInformation(){
	bool writeTruncatedBatLog = false;
	__uint32_t last = 0;
	int iterator = 0;

		// Read File, determine difference between next and last Datapoint, prolong ChangeList.
	std::fstream BatteryLog;
	BatteryLog.open("/home/janosch/BatLog", std::ios::in | std::ios::binary);
	while(BatteryLog && !BatteryLog.eof()){
		__uint32_t next = 0;
				// Read next 4 Bytes and cast into uLong
		BatteryLog.read(reinterpret_cast<char*>(&next), 4);
				//  Determine Change and prolong List
		if (next != 0){
			if (next > last) changeChange(1, iterator);
			if (next == last) changeChange(0, iterator);
			if (next < last) changeChange(-1, iterator);
		}
		iterator++;
				// Prolong List
		vecBatteryLogEntrys.push_back(last);
		last=next;
	}
	BatteryLog.close();
	
			// erase first elements - its caused by the change from Null to the first element
	vecStateList.erase(vecStateList.begin());

		// Print the statechanges to Console
#ifdef DEBUG
	int size = vecStateList.size();
	int i = 0;
	std::cout << "State list:\n";
	while(i < size){
		std::cout << "\t" << std::get<0>(vecStateList.at(i)) << ":" << std::get<1>(vecStateList.at(i)) << "\n";
		i++;
	}
#endif
	if (vecStateList.size() > 1) writeTruncatedBatLog = true;
	return writeTruncatedBatLog;
}

void writeByteToFile(__uint32_t* ptr, std::ofstream &File){
	__uint8_t b[4] = { 0, 0, 0, 0};
	memcpy(&b, ptr, sizeof(b));
	if(!File) return;

	File.put(b[0]);
	File.put(b[1]);
	File.put(b[2]);
	File.put(b[3]);
}
void writePurgedBatteryLog(){
	std::ofstream writeFileStream;
	writeFileStream.open(BatteryLogPath, std::ios::binary);
	for (__uint32_t i : vecBatteryLogEntrys)
		writeByteToFile(&i, writeFileStream);
	writeFileStream.close();
}
std::string makePrediction(int state){
	int x=0, SumX=0, AvgX=0, Sxx=0, Sxy=0;
	long SumY=0, AvgY=0, Syy=0; 
	
	// make Sums
	for (__uint32_t y : vecBatteryLogEntrys){
		SumX += ++x;
		SumY += y;
	}	

	//Averages
	AvgX = SumX/x;
	AvgY = SumY/x;

	//Schwerpunkte
	x=0;
	for (__uint32_t y : vecBatteryLogEntrys){
		Sxx=Sxx+(x-AvgX)*(x-AvgX);
		Syy=Syy+(y-AvgY)*(y-AvgY);
		Sxy=Sxy+(y-AvgY)*(x-AvgX);
		x++;
	}

	// Calc Function

	int a=Sxy/Sxx;
	int b=AvgY-a*AvgX;
	
	std::string function = 	"Y=" +
							std::to_string(a) +
							"*x +" +
							std::to_string(b);
#ifdef DEBUG
//	printf("Function: Y=%d+%d*x\n", b, a);
#endif
	
	// Calc Time left
	if (state == -1){
		nMinutesLeft = (-b/a)-x;
//	printf("\t%ld Minutes left, till Battery depletion\n", nMinutesLeft);
	}
	if (state == 1){
		std::fstream EnergyFull;
		std::string tmp;
		EnergyFull.open(EnergyFullPath, std::ios::in);
		EnergyFull >> tmp;
		EnergyFull.close();
		unsigned long ulEnergyFull = strtoul(tmp.c_str(), nullptr, 10);
		nMinutesLeft = ((ulEnergyFull-b)/a)-x;
//	printf("\t%ld Minutes left, till Battery fully charged\n", nMinutesLeft);
	}
	return function;

}

int main(int argc, char **argv)
{
	bool writeBatLog = readBatteryInformation();
//	std::cout << "Cleanup necessary?: " << (writeBatLog ? "TRUE" : "FALSE" )<< "\n";
	int nState = std::get<1>(vecStateList.back());
	std::string function = makePrediction(nState);
	
	// stop if no cleanup necessary
	std::cout << nMinutesLeft << "\t" << (writeBatLog ? "TRUE" : "FALSE" ) << "\t" << nState << "\t" <<  function << "\n";
 	if (!writeBatLog) return 0;
	writePurgedBatteryLog();
}
