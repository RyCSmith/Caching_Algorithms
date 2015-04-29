/*
 * Direct.cpp
 *
 *  Created on: Apr 16, 2015
 *      Author: Ryan Smith
 */

#include "Cache.h"

/*
 * This function implements a direct-mapped cache.
 * Given the state of the cache, and the address, this function
 * returns true if there is a cache hit, and false on a cache miss.
 * It also updates the tag in the appropriate cache entry.
 */

bool Cache::lookup(unsigned int addr, unsigned int time) {

	unsigned int wordNumber = addr % blockSize;
	unsigned int blockNumber = (addr / blockSize) % cacheSize;
	unsigned int tagNumber = (addr / blockSize) / cacheSize;

	if (entries[(int)blockNumber].tag == tagNumber)
		return true;
	else{
		entries[(int)blockNumber].tag = tagNumber;
		entries[(int)blockNumber].time = time;
	}
	return false;

}


