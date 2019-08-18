//============================================================================
// Name        : genflash.cpp
// Author      : Tomislav Gjuranec
// Version     :
// Copyright   : GLPv2
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdint>

#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "ScatterProc.h"

#define BUFF_SIZE 4096

int main(int argc, char **argv) {
	int opt;
	char *imgfn, *scatterfn;
	imgfn = nullptr;
	scatterfn = nullptr;
	while((opt = getopt(argc, argv, "i:s:")) != -1){
		size_t len;
		switch(opt){
		case 'i':
			len = strlen(optarg);
			imgfn = new char[len+1];
			strncpy(imgfn, optarg, len);
			break;
		case 's':
			len = strlen(optarg);
			scatterfn = new char[len+1];
			strncpy(scatterfn, optarg,len);
			break;
		default:
			//TODO: error handling
			std::cerr << "Usage: genflash -i imagefile  -s scatterfile" << std::endl;
			return 1;
		}
	}

	//CHECK WHETHER THE SCATTER FILE IS PROVIDED
	if(scatterfn == nullptr){
		//TODO: error handling
		std::cerr << "Usage: genflash -i imagefile  -s scatterfile" << std::endl;
		return 1;
	}
	//PROCESS SCATTER FILE
	ScatterProc sp;
	if(sp.readScatterFile(scatterfn) == SCATTER_PROC_ERROR){
		return 3;
	}
	//PRINT COLLECTED DATA
	char *b = new char[4096];
	for(auto it = sp.partition.begin(); it != sp.partition.end(); ++it){
		it->GetTSD(&b[0],4096);
		std::cout << b << std::endl;
	}
	delete [] b;



	//CHECK WHETHER THE LARGE IMAGE FILE IS PROVIDED
	if(imgfn == nullptr){
		//TODO: error handling
		std::cerr << "Usage: genflash -i imagefile  -s scatterfile" << std::endl;
		return 1;
	}
	//OPEN LARGE IMAGE FILE
	std::ifstream imgfile(imgfn);
	if(!imgfile.is_open()){
		std::cerr << "Error in opening file " << imgfn << std::endl;
		return 2;
	}

	//SCATTERING IMAGE
	/*
	 * For creating particular images we need following data:
	 * - region
	 * - file_name
	 * - physical_start_addr
	 * - partition_size
	 */
	for(auto it=sp.partition.cbegin(); it != sp.partition.cend(); ++it){
		if(strcmp(it->file_name,"NONE") && strcmp(it->file_name,"")){
			if(!strcmp(it->region,"EMMC_USER")){
				//TODO: check whether there is enough space on the hard drive
				std::ofstream fout(it->file_name,std::ofstream::binary | std::ofstream::out | std::ofstream::trunc);
				if(!fout.is_open()){
					std::cerr << "Error in opening file: " << it->file_name << std::endl;
					continue;
				}
				imgfile.seekg(it->physical_start_addr);
				static char buff[BUFF_SIZE];
				uint64_t count = 0;
				while(count < it->partition_size){
					count += BUFF_SIZE;
					imgfile.read(buff, BUFF_SIZE);
					fout.write(buff, BUFF_SIZE);
				}
				fout.close();
			}
		}
	}
	delete [] imgfn;
	delete [] scatterfn;
	imgfile.close();
	return 0;
}
