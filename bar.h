// bar.h
/*
Alexus Bonilla
Animated Bar Chart
The purpose of of this program is to display data of in an animated 'bar
format'. Each inputed data will have its own category which is then assigned to
its own unique color. When the program is ran, it will display all the data in
an animated format.

'bar.h' is designed to 'set up' a single individual bar. This bar will contain a
name, value, and category. This file will later be used for 'barchart.h' and
'barchartanimate.h'.
  */

#include <iostream>
#include <string>

#include "myrandom.h"  // used in autograder, do not remove
using namespace std;

//
// Bar
//
class Bar {
 private:
  // Private member variables for a Bar object
  string name;
  int value;
  string catagory;

 public:
  // default constructor:
  // name, value, and catagory are set 'default' values
  Bar() {
    this->name = "";
    this->value = 0;
    this->catagory = "";
  }

  //
  // a second constructor:
  //
  // Parameter passed in constructor Bar object.
  //
  Bar(string name, int value, string category) {
    this->name = name;
    this->value = value;
    this->catagory = category;
  }

  // destructor:
  virtual ~Bar() {
    // Not needed.
  }

  // getName: Simply returns the 'name' of the bar
  string getName() { return name; }

  // getValue: Simply returns the 'value' of the bar
  int getValue() { return value; }

  // getCategory: Simply returns the 'category' of the bar
  string getCategory() { return catagory; }

  // operators
  // Basically compares 2 bars depending on the operator used
  bool operator<(const Bar &other) const { return this->value < other.value; }

  bool operator<=(const Bar &other) const { return this->value <= other.value; }

  bool operator>(const Bar &other) const { return this->value > other.value; }

  bool operator>=(const Bar &other) const { return this->value >= other.value; }
};