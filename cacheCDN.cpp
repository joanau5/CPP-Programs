#include "cacheCDN.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>

/* Implement any functions and methods here! */
using std::cout;
using std::getline;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::string;

namespace ICS45C {
namespace CDN {

Cache::Cache(unsigned int freshnessCount) : freshnessCount(freshnessCount) {}

Cache::~Cache() {
  for (auto &last : storedb) {
    delete[] last.second;
  }
  storedb.clear();
}

std::string Cache::getText(std::string filepath) {
  request++;
  std::stringstream output;
  auto search = storedf.find(filepath);
  auto search2 = counters.find(filepath);
  if (search == storedf.end() || freshnessCount < 2 ||
      search2 == counters.end()) {
    left = freshnessCount;
    ifstream inFile;
    string text;
    inFile.open(filepath);
    while (getline(inFile, text)) {
      output << text << "\n";
    }
    inFile.close();
    storedf[filepath] = output.str();
    left = left - 1;
    top[filepath]++;
    disks[filepath]++;
    counters[filepath] = left;
    return output.str();
  } else {
    left = counters[filepath];
    if (left > 0) {
      left = left - 1;
      top[filepath]++;
      disks[filepath]++;
      counters[filepath] = left;
      return search->second;
    } else {
      left = freshnessCount;
      ifstream inFile;
      string text;
      inFile.open(filepath);
      while (getline(inFile, text)) {
        output << text << "\n";
      }
      inFile.close();
      storedf[filepath] = output.str();
      left = left - 1;
      top[filepath]++;
      disks[filepath]++;
      return output.str();
    }
  }
}

char *Cache::getBinary(std::string filepath) {
  request++;
  auto search = storedb.find(filepath);
  auto search2 = countersb.find(filepath);
  if (search == storedb.end() || freshnessCount < 2 ||
      search2 == countersb.end()) {
    leftb = freshnessCount;
    std::streampos size;
    char *memblock;
    ifstream inBinFile(filepath, ios::in | ios::binary | ios::ate);
    if (inBinFile.is_open()) {
      size = inBinFile.tellg();
      memblock = new char[size];
      inBinFile.seekg(0, ios::beg);
      inBinFile.read(memblock, size);
      inBinFile.close();
      storedb[filepath] = memblock;
      leftb = leftb - 1;
      top[filepath]++;
      disks[filepath]++;
      countersb[filepath] = leftb;
      return memblock;
    }
  } else {
    leftb = countersb[filepath];
    if (leftb > 0) {
      leftb = leftb - 1;
      top[filepath]++;
      disks[filepath]++;
      countersb[filepath] = leftb;
      return search->second;
    } else {
      leftb = freshnessCount;
      std::streampos size;
      char *memblock;
      ifstream inBinFile(filepath, ios::in | ios::binary | ios::ate);
      if (inBinFile.is_open()) {
        size = inBinFile.tellg();
        memblock = new char[size];
        inBinFile.seekg(0, ios::beg);
        inBinFile.read(memblock, size);
        inBinFile.close();
        delete[] storedb[filepath];
        storedb[filepath] = memblock;
        leftb = leftb - 1;
        top[filepath]++;
        disks[filepath]++;
        countersb[filepath] = leftb;
        return memblock;
      }
    }
  }
  return nullptr;
}

bool Cache::isCached(std::string filepath) {
  auto search = storedf.find(filepath);
  auto search2 = storedb.find(filepath);
  if (search != storedf.end()) {
    return true;
  }
  if (search2 != storedb.end()) {
    return true;
  }
  return false;
}

unsigned int Cache::getFreshness(std::string filepath) {
  unsigned int val = 0;
  if (freshnessCount == 0) {
    return val;
  }
  auto search = counters.find(filepath);
  auto search2 = countersb.find(filepath);
  if (search != counters.end()) {
    return search->second;
  }
  if (search2 != countersb.end()) {
    return search2->second;
  }
  return val;
}

void Cache::markFileFresh(std::string filepath) {
  auto search = counters.find(filepath);
  auto search2 = countersb.find(filepath);
  if (search != counters.end()) {
    counters[filepath] = freshnessCount;
  }
  if (search2 != countersb.end()) {
    countersb[filepath] = freshnessCount;
  }
}

void Cache::purgeCache() {
  purged = purged + disks.size();
  disks.clear();
  counters.clear();
  countersb.clear();
}

template <typename K, typename V>
std::pair<K, V> getMaximumValue(const std::map<K, V> &map) {
  return *std::max_element(
      map.begin(), map.end(),
      [](std::pair<K, V> const &x, std::pair<K, V> const &y) {
        return x.second < y.second;
      });
}

std::string Cache::topFile() {
  if (top.size() == 0) {
    return "";
  }
  std::pair<std::string, int> pair = getMaximumValue(top);
  return pair.first;
}

std::string Cache::getStats() {
  std::stringstream output;
  if (storedf.size() == 0 && storedb.size() == 0) {
    output << "Cache Stats\n"
           << "----------\n"
           << "Total requests: 0\n"
           << "Total files requested: 0\n"
           << "Average requests per file: 0.00\n"
           << "Top file:  (0 requests)\n"
           << "Total times read from disk: 0\n"
           << "----------\n";
    return output.str();
  }

  for (std::pair<std::string, unsigned int> re : top) {
    if (((int)re.second % (int)freshnessCount) == 0) {
      disk = disk + ((int)re.second / (int)freshnessCount) - 1;
    } else {
      disk = disk + floor((int)re.second / (int)freshnessCount);
    }
  }
  int files = storedf.size() + storedb.size();
  disk = disk + disks.size() + purged;
  float avg = (float)request / (float)files;
  std::string tfile = topFile();
  int num = top[tfile];
  output << "Cache Stats\n"
         << std::fixed << std::setprecision(2) << "----------\n"
         << "Total requests: " << request << "\n"
         << "Total files requested: " << files << "\n"
         << "Average requests per file: " << avg << "\n"
         << "Top file: " << tfile << " (" << num << " requests)\n"
         << "Total times read from disk: " << disk << "\n"
         << "----------\n";
  return output.str();
}

}  // namespace CDN
}  // namespace ICS45C