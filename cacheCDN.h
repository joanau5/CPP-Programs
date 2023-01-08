#ifndef __CACHECDN_H__
#define __CACHECDN_H__

/* Add any includes here! */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

using std::map;
namespace ICS45C {
namespace CDN {

/* Define your class here! */
class Cache {
 public:
  unsigned int freshnessCount;
  int purged = 0;
  unsigned int left = freshnessCount;
  unsigned int leftb = freshnessCount;
  unsigned int request = 0;
  int disk = 0;
  Cache(unsigned int freshnessCount);
  ~Cache();
  map<std::string, std::string> storedf;
  map<std::string, unsigned int> counters;
  map<std::string, unsigned int> disks;
  map<std::string, unsigned int> top;
  map<std::string, char*> storedb;
  map<std::string, unsigned int> countersb;
  std::string getText(std::string filepath);
  char* getBinary(std::string filepath);
  bool isCached(std::string filepath);
  unsigned int getFreshness(std::string filepath);
  void markFileFresh(std::string filepath);
  void purgeCache();
  std::string topFile();
  std::string getStats();
};

}  // namespace CDN
}  // namespace ICS45C

#endif  // __CACHECDN_H__