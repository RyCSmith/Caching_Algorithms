/*
 * LFU.cpp
 *
 *  Created on: Apr 22, 2015
 *      Author: ryancsmith
 */
#include "Cache.h"
#include <iostream>
#include <stdlib.h>
#include <tgmath.h>
#include <vector>

/*
 * Recursively calculates how many bits are occupied by the word number.
 */
unsigned int Cache::calcBits(unsigned int num){
	if (num <= 2)
		return 1;
	else
		return 1 + Cache::calcBits(num / 2);
}

/*
 * Shifts all CacheEntries over by 1 bit. This automatically adds a 0 on right.
 */
void Cache::recordAccess(){
	for (int i = 0; i < cacheSize; i++){
		entries[i].LFUindex = entries[i].LFUindex << 1;
	}
}

/*
 * Searches the current cache and returns the index of the item that should be evicted. This is the item that was LFU.
 * If there are 2 items that have been equally LFU, return the item of those that was LRU.
 */
unsigned int Cache::evict(unsigned int time){
	//if cacheSize is less than 9 it's possible every item was accessed in last 8 accesses
	if (cacheSize < 9){
		unsigned int minUses = 9; //attainably high
		unsigned int evictIndex;

		for(int i = 0; i < cacheSize; i++){
			//count number of times each entry has been accessed
			int accesses = 0;
		    unsigned char my_char = entries[i].LFUindex;
		    for (int z = 0; z < 8; z++) {
			  if (my_char & 0x01) {
				  accesses++;
			  }
			my_char = my_char >> 1;
		    }
		    //if this entry has been accessed less than the current minimum - replace minimum
		    if (accesses < minUses){
		    	minUses = accesses;
		    	evictIndex = i;
		    }
		    //if this entry has been accessed an equal number of times as the current minimum but was accessed less recently - replace minimum
		    else if (accesses == minUses){
		    	if (entries[i].time < entries[evictIndex].time)
		    		evictIndex = i;
		    }
		}
		return evictIndex;
	}
	//otherwise, we will have at least 1 cachEntry that has not been accessed in the last 8 accesses
	else {
		//loop through and add all that have not been accessed to a vector
		std::vector<unsigned int> possibleEvictions;
		for (int i = 0; i < cacheSize; i++){
			if (entries[i].LFUindex == 0b00000001)
				possibleEvictions.push_back(i);
		}
		//determine which has been LRU
		int LRUIndex = 0;
		int LRUTime = time;
		for (int z = 0; z < possibleEvictions.size(); z++){
			if (entries[possibleEvictions[z]].time < LRUTime){
				LRUIndex = possibleEvictions[z];
				LRUTime = entries[possibleEvictions[z]].time;
			}
		}
		return LRUIndex;
	}
}

/*
 * Adds the given piece of data to the cache.
 */
void Cache::add(unsigned int tagNumber, unsigned int time){
	//look for an empty space to add the new info
	for (int i = 0; i < cacheSize; i++){
		if (entries[i].tag == -1){
			entries[i].tag = tagNumber;
			entries[i].time = time;
			entries[i].LFUindex = 0b00000001;
			return;
		}
	}
	//no empty space found - determine who to evict and add there
	unsigned int addIndex = evict(time);
	entries[addIndex].tag = tagNumber;
	entries[addIndex].time = time;
	entries[addIndex].LFUindex = 0b00000001;
}

/*
 * This function implements an LFU cache. Updates access bits counters. Searches for the given piece of data in the cache
 * and reports a hit(true) where applicable. Adds the data to the cache and reports miss(false) if not found.
 */
bool Cache::lookup(unsigned int addr, unsigned int time) {
	unsigned int blocksToShift = calcBits(blockSize);
	unsigned int tagNumber = addr >> blocksToShift;
	//shifts all LFUindexes one bit to the left
	recordAccess();
	for (int i = 0; i < cacheSize; i++){
		//if this CacheEntry == tagNumber - report hit/update LFU
		if (entries[i].tag == tagNumber){
			entries[i].time = time;
			entries[i].LFUindex |= 1 << 0;
			return true;
		}
	}
	// not found in cache - add it
	add(tagNumber, time);
	return false;
}


