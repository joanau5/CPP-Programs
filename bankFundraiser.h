/**
 * You should implement your solution in this file and submit it to gradescope.
 */

#ifndef __BANK_FUNDRAISER_H__
#define __BANK_FUNDRAISER_H__

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace ICS45C {
namespace BankFundraiser {

template <typename T>
struct RankedNode {
  std::string name;
  T value;
  bool ascending;
  struct RankedNode* next;
};

template <typename T>
class FundraiserRank {
 public:
  std::string name;
  bool ascending;
  RankedNode<T>* head = nullptr;
  RankedNode<T>* tail = nullptr;
  FundraiserRank(std::string name);
  FundraiserRank(std::string name, bool ascending);
  ~FundraiserRank();
  bool isAscending();
  unsigned int add(std::string name, T value);
  bool isEmpty();
  bool exists(T value);
  unsigned int length();
  RankedNode<T>* find(std::string name);
  RankedNode<T>* get(int pos);
  bool remove(std::string name);
  void reverse();
  std::string printTop(unsigned int N);
  RankedNode<T>* operator[](int index) {
    RankedNode<T>* temp = head;
    if (temp == nullptr) {
      return nullptr;
    }
    int i = 0;
    int l = length();
    if (index > (l - 1)) {
      return nullptr;
    }
    if (index < (l * -1)) {
      return nullptr;
    }
    if (index >= 0) {
      while (temp != nullptr) {
        if (i == index) {
          return temp;
        }
        i++;
        temp = temp->next;
      }
    } else {
      index = index + l;
      while (temp != nullptr) {
        if (i == index) {
          return temp;
        }
        i++;
        temp = temp->next;
      }
    }
    return nullptr;
  }

  void operator+(int add) {
    RankedNode<T>* temp = head;
    while (temp != nullptr) {
      temp->value = temp->value + add;
      temp = temp->next;
    }
  }
};

template <typename T>
FundraiserRank<T>::FundraiserRank(std::string name) : name(name) {
  ascending = true;
}

template <typename T>
FundraiserRank<T>::FundraiserRank(std::string name, bool ascending)
    : name(name), ascending(ascending) {}

template <typename T>
bool FundraiserRank<T>::isAscending() {
  return ascending;
}

template <typename T>
unsigned int FundraiserRank<T>::add(std::string name, T value) {
  unsigned int index = 0;
  RankedNode<T>* temp = head;
  temp = head;
  if (temp == nullptr) {
    RankedNode<T>* node = new RankedNode<T>;
    node->name = name;
    node->value = value;
    node->next = nullptr;
    head = node;
    return index;
  }
  if (ascending == false) {
    if (value > temp->value) {
      RankedNode<T>* node = new RankedNode<T>;
      node->name = name;
      node->value = value;
      node->next = head;
      head = node;
      return index;
    } else {
      while (temp->next != nullptr &&
             !(value > temp->next->value && value <= temp->value)) {
        temp = temp->next;
        index++;
      }
      if (temp->next == nullptr) {
        RankedNode<T>* node = new RankedNode<T>;
        node->name = name;
        node->value = value;
        node->next = nullptr;
        temp->next = node;
        index++;
      } else {
        RankedNode<T>* node = new RankedNode<T>;
        node->name = name;
        node->value = value;
        node->next = temp->next;
        temp->next = node;
        index++;
      }
    }
  } else {
    if (value < temp->value) {
      RankedNode<T>* node = new RankedNode<T>;
      node->name = name;
      node->value = value;
      node->next = head;
      head = node;
      return index;
    } else {
      while (temp->next != nullptr &&
             !(value < temp->next->value && value >= temp->value)) {
        temp = temp->next;
        index++;
      }
      if (temp->next == nullptr) {
        RankedNode<T>* node = new RankedNode<T>;
        node->name = name;
        node->value = value;
        node->next = nullptr;
        temp->next = node;
        index++;
      } else {
        RankedNode<T>* node = new RankedNode<T>;
        node->name = name;
        node->value = value;
        node->next = temp->next;
        temp->next = node;
        index++;
      }
    }
  }
  return index;
}

template <typename T>
FundraiserRank<T>::~FundraiserRank() {
  while (head) {
    tail = head->next;
    delete head;
    head = tail;
  }
  head = tail = nullptr;
}

template <typename T>
bool FundraiserRank<T>::isEmpty() {
  if (head == nullptr) {
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool FundraiserRank<T>::exists(T value) {
  RankedNode<T>* temp = head;
  while (temp != nullptr) {
    if (temp->value == value) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

template <typename T>
unsigned int FundraiserRank<T>::length() {
  unsigned int total = 0;
  RankedNode<T>* temp = head;
  while (temp != nullptr) {
    total++;
    temp = temp->next;
  }
  return total;
}

template <typename T>
RankedNode<T>* FundraiserRank<T>::find(std::string name) {
  RankedNode<T>* temp = head;
  while (temp != nullptr) {
    if (temp->name == name) {
      return temp;
    }
    temp = temp->next;
  }
  return nullptr;
}

template <typename T>
RankedNode<T>* FundraiserRank<T>::get(int pos) {
  RankedNode<T>* temp = head;
  if (temp == nullptr) {
    return nullptr;
  }
  int index = 0;
  int l = length();
  if (pos > (l - 1)) {
    return nullptr;
  }
  if (pos < (l * -1)) {
    return nullptr;
  }
  if (pos >= 0) {
    while (temp != nullptr) {
      if (index == pos) {
        return temp;
      }
      index++;
      temp = temp->next;
    }
  } else {
    pos = pos + l;
    while (temp != nullptr) {
      if (index == pos) {
        return temp;
      }
      index++;
      temp = temp->next;
    }
  }
  return nullptr;
}

template <typename T>
bool FundraiserRank<T>::remove(std::string name) {
  RankedNode<T>* temp = head;
  RankedNode<T>* before = nullptr;
  if (temp == nullptr) {
    return false;
  } else if (temp->name == name) {
    head = temp->next;
    delete temp;
    return true;
  } else {
    while (temp->next != nullptr && temp->name != name) {
      before = temp;
      temp = temp->next;
    }
    if (temp->name == name) {
      before->next = temp->next;
      delete temp;
      return true;
    } else {
      temp = temp->next;
    }
    if (temp != nullptr) {
      before->next = temp->next;
      delete temp;
      return true;
    }
  }
  return false;
}

template <typename T>
void FundraiserRank<T>::reverse() {
  RankedNode<T>* temp = head;
  RankedNode<T>* before = nullptr;
  RankedNode<T>* nextt = nullptr;
  if (temp != nullptr) {
    while (temp != nullptr) {
      nextt = temp->next;
      temp->next = before;
      before = temp;
      temp = nextt;
    }
    head = before;
  }
  if (ascending == true) {
    ascending = false;
  } else if (ascending == false) {
    ascending = true;
  }
}

template <typename T>
std::string FundraiserRank<T>::printTop(unsigned int N) {
  RankedNode<T>* temp = head;
  unsigned int counter = 0;
  std::stringstream output;
  if (temp == nullptr || N == 0) {
    output << "\n";
    return output.str();
  } else {
    while (temp != nullptr && counter < N) {
      counter++;
      output << std::fixed << std::setprecision(2) << temp->name << " ("
             << temp->value << ")"
             << " -> ";
      temp = temp->next;
    }
    if (counter == N || temp == nullptr) {
      output << "\n";
      return output.str();
    }
  }
  return output.str();
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const FundraiserRank<T>& t) {
  int counter = 1;
  RankedNode<T>* temp = t.head;
  os << "Results for "
     << "'" << t.name << "'\n"
     << "--------------------\n";
  while (temp != nullptr) {
    os << std::fixed << std::setprecision(2) << counter << ": " << temp->name
       << " (" << temp->value << ")\n";
    counter++;
    temp = temp->next;
  }
  os << "--------------------\n";
  return os;
}

}  // namespace BankFundraiser
}  // namespace ICS45C

#endif  // __BANK_FUNDRAISER_H__