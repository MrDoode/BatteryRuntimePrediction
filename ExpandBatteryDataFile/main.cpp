#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>

int main(int argc, char **argv){
	std::ifstream File;
	std::string sBatteryEnergy;
	const char* sBatteryReadFilePath = argv[1];
	const char* sBatteryWriteFilePath = argv[2];
	
 	File.open(sBatteryReadFilePath, std::ios::in);
	if(File) File >> sBatteryEnergy;
	File.close();
	
	__uint32_t EnergyValue = strtoul(sBatteryEnergy.c_str(), nullptr, 10);
	__uint32_t* ptr = &EnergyValue;
	__uint8_t b[4] = { 0, 0, 0, 0};
	memcpy(&b, ptr, sizeof(b));

	std::ofstream WriteFile;
	WriteFile.open(sBatteryWriteFilePath, std::ios::binary | std::ios::app);
	if(WriteFile){
		WriteFile.put(b[0]);
		WriteFile.put(b[1]);
		WriteFile.put(b[2]);
		WriteFile.put(b[3]);
	}
	WriteFile.close();
	return 0; 
}