/*
 * PartitionData.h
 *
 *  Created on: Aug 16, 2019
 *      Author: tgjuranec
 */

#ifndef PARTITIONDATA_H_
#define PARTITIONDATA_H_
#include <string>
#include <cstdint>
#include <cstring>

#define PARTITION_DATA_OK 1
#define PARTITION_DATA_ERROR 0

class PartitionData{
public:
	char *partition_index;
	char *partition_name;
	char *file_name;
	bool is_download;
	char *type;
	uint64_t linear_start_addr;
	uint64_t physical_start_addr;
	uint64_t partition_size;
	char *region;
	char *storage;
	bool boundary_check;
	bool is_reserved;
	char *operation_type;
	uint64_t reserve;
	//TODO: track filling data
	char *GetTSD(char *buff, size_t nsize);
	unsigned int SetData(std::string line);
	PartitionData();
	PartitionData(const PartitionData &pd);
	~PartitionData();
};

#endif /* PARTITIONDATA_H_ */
