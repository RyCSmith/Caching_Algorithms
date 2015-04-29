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
  char LFUindex;
  CacheEntry() {
    tag = -1;
    time = -1;
    LFUindex = 0b00000000;
  }
};

class Cache {
 public:
  int blockSize; // number of words per block
  int cacheSize; // number of blocks in the cache
  CacheEntry* entries; // the entries in the cache
  //this stuff will keep track of what data was accessed in the last 8 accesses

  Cache(int b, int c) {
    blockSize = b;
    cacheSize = c;
    entries = new CacheEntry[c];
  }

  ~Cache() {
    delete[] entries;
  }
  void recordAccess();
  unsigned int evict(unsigned int);
  void add(unsigned int, unsigned int);
  bool lookup(unsigned int, unsigned int);
  unsigned int calcBits(unsigned int);
};




