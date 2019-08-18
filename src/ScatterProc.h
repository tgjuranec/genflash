/*
 * ScatterProc.h
 *
 *  Created on: Aug 16, 2019
 *      Author: tgjuranec
 */


#ifndef SCATTERPROC_H_
#define SCATTERPROC_H_



#define SCATTER_PROC_OK 1
#define SCATTER_PROC_ERROR 0

#include <vector>
#include "PartitionData.h"

class ScatterProc {
public:
	std::vector <PartitionData> partition;
	int readScatterFile(char *scattername);
	ScatterProc();
	~ScatterProc();
};

#endif /* SCATTERPROC_H_ */
