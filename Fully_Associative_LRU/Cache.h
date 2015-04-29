/*
 * Cache.h
 *
 *  Created on: Apr 16, 2015
 *      Author: Ryan Smith
 */

class CacheEntry {
 public:
  int tag;
  int time;
  CacheEntry() {
    tag = -1;
    time = -1;
  }
};

class Cache {
 public:
  int blockSize; // number of words per block
  int cacheSize; // number of blocks in the cache
  CacheEntry* entries; // the entries in the cache

  Cache(int b, int c) {
    blockSize = b;
    cacheSize = c;
    entries = new CacheEntry[c];
  }

  ~Cache() {
    delete[] entries;
  }
  unsigned int calcBits(unsigned int);
  bool lookup(unsigned int, unsigned int);
};




