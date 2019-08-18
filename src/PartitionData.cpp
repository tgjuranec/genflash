/*
 * PartitionData.cpp
 *
 *  Created on: Aug 16, 2019
 *      Author: tgjuranec
 */

#include "PartitionData.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>

PartitionData::PartitionData():
partition_index(nullptr),
partition_name(nullptr),
file_name(nullptr),
is_download(false),
type(nullptr),
linear_start_addr(0),
physical_start_addr(0),
partition_size(0),
region(nullptr),
storage(nullptr),
boundary_check(false),
is_reserved(false),
operation_type(nullptr),
reserve(0)
{

}

PartitionData::PartitionData(const PartitionData & pd){
	partition_index = new char [strlen(pd.partition_index)+1];
	partition_index = strncpy(partition_index, pd.partition_index, strlen(pd.partition_index));
	partition_index[strlen(pd.partition_index)] = 0;
	partition_name = new char [strlen(pd.partition_name) + 1];
	partition_name = strncpy(partition_name, pd.partition_name, strlen(pd.partition_name));
	partition_name[strlen(pd.partition_name)] = 0;
	file_name = new char [strlen(pd.file_name)+1];
	file_name = strncpy(file_name, pd.file_name, strlen(pd.file_name));
	file_name[strlen(pd.file_name)] = 0;
	is_download = pd.is_download;
	type = new char [strlen(pd.type)+1];
	type = strncpy(type, pd.type, strlen(pd.type));
	type[strlen(pd.type)] = 0;
	linear_start_addr = pd.linear_start_addr;
	physical_start_addr = pd.physical_start_addr;
	partition_size = pd.partition_size;
	region = new char [strlen(pd.region)+1];
	region = strncpy(region, pd.region, strlen(pd.region));
	region[strlen(pd.region)] = 0;
	storage = new char [strlen(pd.storage)+1];
	storage = strncpy(storage, pd.storage, strlen(pd.storage));
	storage[strlen(pd.storage)] = 0;
	boundary_check = pd.boundary_check;
	is_reserved = pd.is_reserved;
	operation_type = new char [strlen(pd.operation_type)+1];
	operation_type = strncpy(operation_type, pd.operation_type, strlen(pd.operation_type));
	operation_type[strlen(pd.operation_type)] = 0;
	reserve = pd.reserve;
}


PartitionData::~PartitionData() {
	delete [] partition_index;
	delete [] partition_name;
	delete [] file_name;
	delete [] type;
	delete [] region;
	delete [] storage;
	delete [] operation_type;
}



unsigned int PartitionData::SetData(std::string line){
	//get item name from the line
	std::string::size_type colon = line.find(':',0);
	std::string item_name = line.substr(2, colon-2);
	std::string item_value = line.substr(colon+2, line.size()-colon);

	if(!item_name.compare("partition_index")){
		if(partition_index != nullptr){
			delete [] partition_index;
		}
		partition_index = new char[item_value.size()+1];
		strncpy(partition_index,item_value.c_str(),item_value.size());
		partition_index[item_value.size()] = 0;
	}
	else if(!item_name.compare("partition_name")){
		if(partition_name != nullptr){
			delete [] partition_name;
		}
		partition_name = new char[item_value.size()+1];
		strncpy(partition_name,item_value.c_str(),item_value.size());
		partition_name[item_value.size()] = 0;
	}
	else if(!item_name.compare("file_name")){
		if(file_name != nullptr){
			delete [] file_name;
		}
		file_name = new char[item_value.size()+1];
		strncpy(file_name,item_value.c_str(),item_value.size());
		file_name[item_value.size()] = 0;
	}
	else if(!item_name.compare("is_download")){
		if(!item_value.compare("true")){
			is_download = true;
		}
		else if(!item_value.compare("false")){
			is_download = false;
		}
		else{
			//TODO: error handling
		}
	}
	else if(!item_name.compare("type")){
		if(type != nullptr){
			delete [] type;
		}
		type = new char[item_value.size()+1];
		strncpy(type,item_value.c_str(),item_value.size());
		type[item_value.size()] = 0;
	}
	else if(!item_name.compare("linear_start_addr")){
		linear_start_addr = std::stoul(item_value, nullptr,0);
	}
	else if(!item_name.compare("physical_start_addr")){
		physical_start_addr = std::stoul(item_value, nullptr,0);
	}
	else if(!item_name.compare("partition_size")){
		partition_size = std::stoul(item_value, nullptr,0);
	}
	else if(!item_name.compare("region")){
		if(region != nullptr){
			delete [] region;
		}
		region = new char[item_value.size()+1];
		strncpy(region,item_value.c_str(),item_value.size());
		region[item_value.size()] = 0;
	}
	else if(!item_name.compare("storage")){
		if(storage != nullptr){
			delete [] storage;
		}
		storage = new char[item_value.size()+1];
		strncpy(storage,item_value.c_str(),item_value.size());
		storage[item_value.size()] = 0;
	}
	else if(!item_name.compare("boundary_check")){
		if(!item_value.compare("true")){
			boundary_check = true;
		}
		else if(!item_value.compare("false")){
			boundary_check = false;
		}
		else{
			//TODO: error handling
		}
	}
	else if(!item_name.compare("is_reserved")){
		if(!item_value.compare("true")){
			is_reserved = true;
		}
		else if(!item_value.compare("false")){
			is_reserved = false;
		}
		else{
			//TODO: error handling
		}
	}
	else if(!item_name.compare("operation_type")){
		if(operation_type != nullptr){
			delete [] operation_type;
		}
		operation_type = new char[item_value.size()+1];
		strncpy(operation_type,item_value.c_str(),item_value.size());
		operation_type[item_value.size()] = 0;
	}
	else if(!item_name.compare("reserve")){
		reserve = std::stoul(item_value, nullptr,0);
	}
	else{
		//TODO: something else
		std::cerr << "Not able to parse: " << item_name << ": " << item_value << std::endl;
		return PARTITION_DATA_ERROR;
	}

	return PARTITION_DATA_OK;
}

/*
 * Function provides all collected data about partition
 * Arguments:
 * char *buff - user must provide buffer
 * size_t nsize - size of allocated memory of the buff
 */



char *PartitionData::GetTSD(char *buff, size_t nsize){

	if(buff == nullptr){
		return nullptr;
	}

	char *str = new char [4096];
	uint64_t count = 0;
	strncpy(&str[count],partition_index, strlen(partition_index));
	count += strlen(partition_index);
	str[count] = '\t';
	count++;

	strncpy(&str[count],partition_name, strlen(partition_name));
	count += strlen(partition_name);
	str[count] = '\t';
	count++;

	strncpy(&str[count],file_name, strlen(file_name));
	count += strlen(file_name);
	str[count] = '\t';
	count++;


	if(is_download == true){
		strncpy(&str[count],"true", strlen("true"));
		count += strlen("true");
		str[count] = '\t';
		count++;
	}
	else{
		strncpy(&str[count],"false", strlen("false"));
		count += strlen("false");
		str[count] = '\t';
		count++;
	}


	strncpy(&str[count],type, strlen(type));
	count += strlen(type);
	str[count] = '\t';
	count++;

	char num[20];
	sprintf(num,"%lX",linear_start_addr);
	strncpy(&str[count],num, strlen(num));
	count += strlen(num);
	str[count] = '\t';
	count++;

	sprintf(num,"%lX",physical_start_addr);
	strncpy(&str[count],num, strlen(num));
	count += strlen(num);
	str[count] = '\t';
	count++;

	sprintf(num,"%lX",partition_size);
	strncpy(&str[count],num, strlen(num));
	count += strlen(num);
	str[count] = '\t';
	count++;

	strncpy(&str[count],region, strlen(region));
	count += strlen(region);
	str[count] = '\t';
	count++;

	strncpy(&str[count],storage, strlen(storage));
	count += strlen(storage);
	str[count] = '\t';
	count++;



	if(boundary_check == true){
		strncpy(&str[count],"true", strlen("true"));
		count += strlen("true");
		str[count] = '\t';
		count++;
	}
	else{
		strncpy(&str[count],"false", strlen("false"));
		count += strlen("false");
		str[count] = '\t';
		count++;
	}


	if(is_reserved == true){
		strncpy(&str[count],"true", strlen("true"));
		count += strlen("true");
		str[count] = '\t';
		count++;
	}
	else{
		strncpy(&str[count],"false", strlen("false"));
		count += strlen("false");
		str[count] = '\t';
		count++;
	}
	strncpy(&str[count],operation_type, strlen(operation_type));
	count += strlen(operation_type);
	str[count] = '\t';
	count++;

	sprintf(num,"%lX",reserve);
	strncpy(&str[count],num, strlen(num));
	count += strlen(num);
	str[count] = '\t';
	count++;
	str[count] = 0;



	if(strlen(str) >= nsize){
		return nullptr;
	}
	else{
		strcpy(buff,str);
		buff[strlen(str)] = 0;
	}
	delete str;
	return buff;
}
