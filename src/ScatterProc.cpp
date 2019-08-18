/*
 * ScatterProc.cpp
 *
 *  Created on: Aug 16, 2019
 *      Author: tgjuranec
 */

#include "ScatterProc.h"
#include <iostream>
#include <fstream>
#include <string>


int ScatterProc::readScatterFile(char *scattername){
	std::ifstream scatterfile(scattername);
	if(!scatterfile.is_open()){
		std::cerr << "Error in opening file " << scattername << std::endl;
		return SCATTER_PROC_ERROR;
	}
	std::string line;
	PartitionData *pd = nullptr;
	/*
	 * OK let's read through file line by line
	 */
	while(std::getline(scatterfile,line)){
		//IGNORED LINES
		if(line[0] == '#' || line[0] == '\n' || line.empty()){
			continue;
		}
		//START OF THE ENTRY
		if(line[0] == '-'){
			//PARTITION SETTINGS
			if(line.find("partition_index", 0) != std::string::npos){
				if(pd != nullptr){
					partition.push_back(*pd);
					delete pd;
				}
				else{

				}
				pd = new PartitionData;
			}
			//GENERAL SETTINGS
			else{
				//TODO: possibly header
			}
		}

		//PARTITION DATA
		if(pd){
			pd->SetData(line);
		}
		//GENERAL DATA
		else{
			//TODO: process general data
		}
	}
	if(pd != nullptr){
		partition.push_back(*pd);
		delete pd;
	}
	return SCATTER_PROC_OK;
}

void ScatterProc::analyzePartitions(){

	/*
	 * CHECK FOR OVERLAPPING
	 * Every pair is checked
	 * n*(n-1)/2
	 *
	 * Only two combinations are permitted
	 * AS     AE
	 * |-------|
	 *         |--------|          -> (AS <= BS) AND (AE <= BS)
	 *         BS       BE
	 *
	 *         AS           AE
	 *         |-------------|
	 * |----|                      -> (AS >= BE) AND (AE >= BE)
	 * BS   BE
	 *
	 */
	for(auto it = partition.cbegin(); it != (partition.cend()-1); ++it){
		for (auto itfor = it+1; itfor != partition.cend(); itfor++){
			uint64_t itStart = it->linear_start_addr;
			uint64_t itEnd = itStart + it->partition_size;
			uint64_t itforStart = itfor->linear_start_addr;
			uint64_t itforEnd = itforStart + itfor->partition_size;
			//implemented idea from above
			if(((itStart <= itforStart) && (itEnd <= itforStart)) ||
					((itStart >= itforEnd) && (itEnd >= itforEnd))){
				//NO OVELAPPING

			}
			else{
				//OVERLAPPING
				std::cout << "Partition overlapping: " << std::endl;
				std::cout << std::hex << itStart << " " << itEnd << " "<< it->partition_index << " "<< it->partition_name << std::endl;
				std::cout << std::hex << itforStart << " " << itforEnd << " "<< itfor->partition_index << " "<< itfor->partition_name << std::endl;
			}

			if(!strcmp(it->partition_name, itfor->partition_name)){
				std::cout << "Partition name collision: " << it->partition_index << " <-> "<< itfor->partition_index << " " << it->partition_name << std::endl;
			}

			if(strcmp(it->file_name,"NONE")){
				if(!strcmp(it->file_name, itfor->file_name)){
					std::cout << "File name collision: " << it->partition_index << " <-> "<< itfor->partition_index << " " << it->file_name <<  std::endl;
				}
			}
		}
	}
}



ScatterProc::ScatterProc() {

}

ScatterProc::~ScatterProc() {
	// TODO Auto-generated destructor stub
}

