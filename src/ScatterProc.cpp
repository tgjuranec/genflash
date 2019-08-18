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



ScatterProc::ScatterProc() {

}

ScatterProc::~ScatterProc() {
	// TODO Auto-generated destructor stub
}

