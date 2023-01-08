#include "bankManagementSystem.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using std::cin;
using std::cout;
using namespace ICS45C::BankManagementSystem;

static int x = 0;

Record* ICS45C::BankManagementSystem::openAccount(Record* accounts,
                                                  std::string fname,
                                                  std::string lname,
                                                  std::string email,
                                                  std::string phone) {
  Record test1;
  test1.locked = false;
  test1.balance = 0.0;
  test1.phone = phone;
  test1.email = email;
  test1.fname = fname;
  test1.lname = lname;
  test1.id = x;
  Record* node = new Record();
  node->locked = false;
  node->balance = 0.0;
  node->phone = phone;
  node->email = email;
  node->fname = fname;
  node->lname = lname;
  node->id = x;
  node->next = nullptr;
  x++;
  if (accounts == nullptr) {
    accounts = node;
    return accounts;
  } else {
    Record* now = accounts;
    while (now->next != nullptr) {
      now = now->next;
    }
    now->next = node;
    return accounts;
  }
}

void ICS45C::BankManagementSystem::lockAccount(Record* account) {
  if (account != nullptr) {
    account->locked = true;
  }
}

void ICS45C::BankManagementSystem::unlockAccount(Record* account) {
  if (account != nullptr) {
    account->locked = false;
  }
}

Record* ICS45C::BankManagementSystem::searchAccount(Record* accounts,
                                                    std::string field,
                                                    std::string keyword) {
  if (accounts == nullptr) {
    return nullptr;
  }
  if (field == "ID") {
    unsigned int x = stoi(keyword);
    while (accounts != nullptr) {
      if ((accounts->locked == false) && (accounts->id == x)) {
        return accounts;
      } else {
        accounts = accounts->next;
      }
    }
    return nullptr;
  } else if (field == "FIRST") {
    while (accounts != nullptr) {
      if ((accounts->locked == false) && (accounts->fname == keyword)) {
        return accounts;
      } else {
        accounts = accounts->next;
      }
    }
    return nullptr;
  } else if (field == "LAST") {
    while (accounts != nullptr) {
      if ((accounts->locked == false) && (accounts->lname == keyword)) {
        return accounts;
      } else {
        accounts = accounts->next;
      }
    }
    return nullptr;
  } else if (field == "EMAIL") {
    while (accounts != nullptr) {
      if ((accounts->locked == false) && (accounts->email == keyword)) {
        return accounts;
      } else {
        accounts = accounts->next;
      }
    }
    return nullptr;
  } else if (field == "PHONE") {
    while (accounts != nullptr) {
      if ((accounts->locked == false) && (accounts->phone == keyword)) {
        return accounts;
      } else {
        accounts = accounts->next;
      }
    }
    return nullptr;
  } else {
    return nullptr;
  }
}

std::string ICS45C::BankManagementSystem::printDetails(Record* account) {
  std::stringstream output;
  if (account == nullptr) {
    output << "------\n"
           << "Account UNKNOWN" << std::endl
           << "------\n"
           << "Sorry, this account does not exist.\n"
           << "------\n";
    return output.str();
  } else if (account->locked == true) {
    output << "------\n"
           << "Account #" << account->id << std::endl
           << "------\n"
           << "Sorry, this account has been locked.\n"
           << "------\n";
    return output.str();

  } else if (account->locked == false) {
    output << "------\n"
           << "Account #" << account->id << std::endl
           << "------\n"
           << "Status: OPEN\n"
           << "Account holder: " << account->fname << " " << account->lname
           << std::endl
           << "Contact: " << account->phone << " / " << account->email << "\n"
           << std::fixed << std::setprecision(2)
           << "Balance: " << account->balance << std::endl
           << "------\n";
    return output.str();
  } else {
    return output.str();
  }
}

std::string ICS45C::BankManagementSystem::printDetails(Record* accounts,
                                                       unsigned int id) {
  std::stringstream output;
  while (accounts != nullptr) {
    if (id == accounts->id) {
      if (accounts->locked == true) {
        output << "------\n"
               << "Account #" << accounts->id << std::endl
               << "------\n"
               << "Sorry, this account has been locked.\n"
               << "------\n";
        return output.str();
      } else if (accounts->locked == false) {
        output << "------\n"
               << "Account #" << accounts->id << std::endl
               << "------\n"
               << "Status: OPEN\n"
               << "Account holder: " << accounts->fname << " "
               << accounts->lname << std::endl
               << "Contact: " << accounts->phone << " / " << accounts->email
               << "\n"
               << std::fixed << std::setprecision(2)
               << "Balance: " << accounts->balance << std::endl
               << "------\n";
        return output.str();
      }
    } else {
      accounts = accounts->next;
    }
  }
  output << "------\n"
         << "Account UNKNOWN" << std::endl
         << "------\n"
         << "Sorry, this account does not exist.\n"
         << "------\n";
  return output.str();
}

void ICS45C::BankManagementSystem::updateAccount(
    Record* account, std::string firstName, std::string lastName,
    std::string phone, std::string email, bool locked) {
  if (account != nullptr) {
    account->fname = firstName;
    account->lname = lastName;
    account->phone = phone;
    account->email = email;
    account->locked = locked;
  }
}

void ICS45C::BankManagementSystem::updateAccount(
    Record* accounts, unsigned int id, std::string firstName,
    std::string lastName, std::string phone, std::string email, bool locked) {
  while (accounts != nullptr) {
    if (id == accounts->id) {
      accounts->fname = firstName;
      accounts->lname = lastName;
      accounts->phone = phone;
      accounts->email = email;
      accounts->locked = locked;
      break;
    } else {
      accounts = accounts->next;
    }
  }
}

double ICS45C::BankManagementSystem::deposit(Record* account, double value) {
  if (account == nullptr) {
    return -123.45;
  } else {
    if (account->locked == false) {
      if (value > 0) {
        account->balance = account->balance + value;
        return account->balance;
      } else {
        return account->balance;
      }
    } else {
      return -123.45;
    }
  }
  return -123.45;
}

double ICS45C::BankManagementSystem::deposit(Record* accounts, unsigned int id,
                                             double value) {
  while (accounts != nullptr) {
    if (id == accounts->id) {
      if (accounts->locked == true) {
        return -123.45;
      } else {
        if (value > 0) {
          accounts->balance = accounts->balance + value;
          return accounts->balance;
        } else {
          return accounts->balance;
        }
      }
    } else {
      accounts = accounts->next;
    }
  }
  return -123.45;
}

double ICS45C::BankManagementSystem::withdrawal(Record* account, double value) {
  if (account == nullptr) {
    return -123.45;
  } else {
    if (account->locked == false) {
      if (value > 0) {
        account->balance = account->balance - value;
        return account->balance;
      } else {
        return account->balance;
      }
    } else {
      return -123.45;
    }
  }
  return -123.45;
}

double ICS45C::BankManagementSystem::withdrawal(Record* accounts,
                                                unsigned int id, double value) {
  while (accounts != nullptr) {
    if (id == accounts->id) {
      if (accounts->locked == true) {
        return -123.45;
      } else {
        if (value > 0) {
          accounts->balance = accounts->balance - value;
          return accounts->balance;
        } else {
          return accounts->balance;
        }
      }
    } else {
      accounts = accounts->next;
    }
  }
  return -123.45;
}

Record* ICS45C::BankManagementSystem::deleteAccount(Record* accounts,
                                                    unsigned int id) {
  if (accounts == nullptr) {
    return accounts;
  }
  if (accounts->id == id) {
    Record* copy = accounts;
    free(copy);
    accounts = accounts->next;
    return accounts;
  } else {
    Record* current = accounts->next;
    Record* prev = accounts;
    while (current && (current->id != id)) {
      prev = current;
      current = current->next;
    }
    if (current) {
      free(current);
      prev->next = current->next;
    }
    return accounts;
  }
}

unsigned int ICS45C::BankManagementSystem::countUnlockedAccounts(
    Record* accounts) {
  unsigned int total = 0;
  if (accounts == nullptr) {
    return total;
  } else {
    while (accounts != nullptr) {
      if (accounts->locked == false) {
        total = total + 1;
      }
      accounts = accounts->next;
    }
    return total;
  }
}

unsigned int ICS45C::BankManagementSystem::countLockedAccounts(
    Record* accounts) {
  unsigned int total = 0;
  if (accounts == nullptr) {
    return total;
  } else {
    while (accounts != nullptr) {
      if (accounts->locked == true) {
        total = total + 1;
      }
      accounts = accounts->next;
    }
    return total;
  }
}

unsigned int ICS45C::BankManagementSystem::countAllAccounts(Record* accounts) {
  unsigned int total = 0;
  if (accounts == nullptr) {
    return total;
  } else {
    while (accounts != nullptr) {
      total = total + 1;
      accounts = accounts->next;
    }
    return total;
  }
}

long double ICS45C::BankManagementSystem::getAverageBalance(Record* accounts) {
  long double avg = 0;
  if (accounts == nullptr) {
    return avg;
  }
  int tc = countLockedAccounts(accounts);
  int all = countAllAccounts(accounts);
  int length = countUnlockedAccounts(accounts);
  long double sum = getBankFunds(accounts);
  if (tc == all) {
    return avg;
  }
  avg = sum / (double)length;
  return avg;
}

long double ICS45C::BankManagementSystem::getBankFunds(Record* accounts) {
  long double sum = 0;
  if (accounts == nullptr) {
    return sum;
  } else {
    while (accounts != nullptr) {
      if (accounts->locked == false) {
        sum += accounts->balance;
      }
      accounts = accounts->next;
    }
    return sum;
  }
}

void ICS45C::BankManagementSystem::closeBank(Record* accounts) {
  Record* next;
  while (accounts) {
    next = accounts->next;
    delete accounts;
    accounts = next;
  }
}