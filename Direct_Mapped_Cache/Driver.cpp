/*
 * Driver.cpp
 *
 *  Created on: Apr 16, 2015
 *      Author: Ryan Smith
 */

#include "Cache.h"
#include <iostream>
#include <stdlib.h>

/*
 * This is the driver for the cache programs.
 * You should not need to change this code.
 * Please contact a member of the instruction staff
 * if you feel that a change to the code is needed.
 */


int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "Usage: " << argv[0] << " [blockSize] [cacheSize]" << std::endl;
    return 0;
  }

  //creates a new Cache object
  int blockSize = atoi(argv[1]); // number of words per block
  int cacheSize = atoi(argv[2]); // number of blocks in the cache
  Cache cache(blockSize, cacheSize);

  std::cout << "block size = " << blockSize << std::endl;
  std::cout << "cache size = " << cacheSize << std::endl;

  int time = 0;

  int hits = 0;

  int size = 10;

  unsigned int addrs[] = { 0x0100, 0x0101, 0x1111, 0x2211, 0x2222, 0x222F, 0x010F, 0x212F, 0x2222, 0x221F };

  int i;

  for (i = 0; i < size; i++) {

    if (cache.lookup(addrs[i], i)) {
      std::cout << "Addr " << std::hex << addrs[i] << ": hit" << std::endl;
      hits++;
    }
    else {
      std::cout << "Addr " << std::hex << addrs[i] << ": miss" << std::endl;
    }

  }

  int hitrate = (hits*100)/size;

  std::cout << "Hit rate: " << std::dec << hitrate << "%" << std::endl;

  return 1;
}


