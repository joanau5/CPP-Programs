#include <cmath>
#include <iostream>

using namespace std;

int main() {
  cout << "----------\n";
  cout << "Hello! Welcome to the ieee food calculator.\n";
  cout << "I'll help you calculate how much food you should order for an "
          "event!\n";
  cout << "----------\n";

  cout << "\nFirst, we will find out how many people should show up.\n";
  cout << "1. How many people have RSVP'd?\n";
  int rsvp, organizers;
  float show_up_ratio;
  cin >> rsvp;
  cout << "2. What's the ratio of people that usually show up?\n";
  cin >> show_up_ratio;
  cout << "3. How many people are helping organize this event?\n";
  cin >> organizers;
  int attendence = 1 + floor(show_up_ratio * rsvp);
  int expected_guests = max(attendence, organizers);
  cout << "\nGot it! From this info, we expect " << expected_guests
       << " people to attend.\n";
  int diet;
  char beverage;
  cout << "\n4. How many people requested vegetarian options?\n";
  cin >> diet;
  cout << "5. What type of beverage will be available? ([W]ater, [S]oda, "
          "[N]one)\n";
  cin >> beverage;

  int large_p = expected_guests / 7;
  int med_p = expected_guests % 7;

  switch (beverage) {
    case 'w':
      large_p = floor(large_p * 0.9);
      med_p = floor(med_p * 0.9);
      break;
    case 'W':
      large_p = floor(large_p * 0.9);
      med_p = floor(med_p * 0.9);
      break;
    case 's':
      large_p = floor(large_p * 0.75);
      med_p = floor(med_p * 0.75);
      break;
    case 'S':
      large_p = floor(large_p * 0.75);
      med_p = floor(med_p * 0.75);
      break;
  }

  cout << "\nI think you should order " << large_p << " large and " << med_p
       << " medium pizzas.\n";
  float v = diet / double(expected_guests);
  float d_ratio;
  if (0.2 < v) {
    d_ratio = v;
  } else {
    d_ratio = 0.20;
  }
  int VG_LG, VG_MD, HW_LG, HW_MD;
  VG_LG = ceil(large_p * d_ratio);
  VG_MD = ceil(med_p * d_ratio);
  HW_LG = large_p - VG_LG;
  HW_MD = med_p - VG_MD;

  cout << "From the options you entered, I think you should order:\n";
  cout << "    " << HW_LG << " large Hawaiian pizzas\n";
  cout << "    " << HW_MD << " medium Hawaiian pizzas\n";
  cout << "    " << VG_LG << " large vegetarian pizzas\n";
  cout << "    " << VG_MD << " medium vegetarian pizzas\n\n";
  cout << "\nHope this helps!";
  return 0;
}