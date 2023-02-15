// barchart.h
/*
Alexus Bonilla
Animated Bar Chart
The purpose of of this program is to display data of in an animated 'bar
format'. Each inputed data will have its own category which is then assigned to
its own unique color. When the program is ran, it will display all the data in
an animated format.

'barchart.h' is to take all the 'bars' that are created using the 'bar.h' file,
and put them all into a 'bar chart'. In the chart, they will be organized in
decending order and be assignable to color values. This will later be used for
'barchartanimate.h'.
  */

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#include "bar.h"
#include "myrandom.h"  // used in autograder, do not remove

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";

// Color codes for Mimir (light mode)
// const string RED("\033[1;36m");
// const string PURPLE("\033[1;32m");
// const string BLUE("\033[1;33m");
// const string CYAN("\033[1;31m");
// const string GREEN("\033[1;35m");
// const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
// const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for Replit (dark mode terminal)
const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};

//
// BarChart
//
class BarChart {
 private:
  //
  // Private member variables for the abstraction.
  // This implementation uses a low-level C array, bars, to store a list of
  // Bars.  As a result, you must also keep track of the number of elements
  // stored (size) and the capacity of the array (capacity).  This is not a
  // dynamic array, so it does not expand.
  //
  Bar* bars;  // pointer to a C-style array
  int capacity;
  int size;
  string frame;  // Added private member, will be used to store the 'frame' for
                 // each bar

 public:
  // default constructor: Set all varialbes to 'default' values
  BarChart() {
    bars = nullptr;
    this->capacity = 0;
    this->size = 0;
    this->frame = "";
  }

  // parameterized constructor: Creates a BarChart that can take in a parameter.
  // The parameter will determine how much 'bars' the bar chart can hold.
  // Parameter passed in determines memory allocated for bars.
  BarChart(int n) {
    Bar* newBar = new Bar[n];
    this->capacity = n;
    this->size = 0;
    this->frame = "";
    this->bars = newBar;
  }

  //
  // copy constructor:
  //
  // Called automatically by C++ to create an BarChart that contains
  // a copy of an existing BarChart.  Example: this occurs when passing
  // BarChart as a parameter by value.
  //
  BarChart(const BarChart& other) {
    this->bars = new Bar[other.capacity];
    this->size = other.size;
    this->capacity = other.capacity;
    this->frame = other.frame;
    for (int i = 0; i < other.size; ++i) {
      this->bars[i] = other.bars[i];
    }
  }
  //
  // copy operator=
  //
  // Called when you assign one BarChart into another, i.e. this = other;
  //
  BarChart& operator=(const BarChart& other) {
    //BarChart bc;
    if (this == &other) {
      return *this;
    }
    delete[] bars;
    this->bars = new Bar[other.capacity];
    this->size = other.size;
    this->capacity = other.capacity;
    this->frame = other.frame;
    for (int i = 0; i < other.size; ++i) {
      this->bars[i] = other.bars[i];
    }
    return *this;
  }

  // clear
  // frees memory and resets all private member variables to default values.
  void clear() {
    delete[] bars;
    bars = nullptr;
    this->capacity = 0;
    this->size = 0;
    this->frame = "";
  }

  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated by the
  // BarChart.
  //
  virtual ~BarChart() {
    if (bars != nullptr) {
      delete[] bars;
    }
  }

  // setFrame: Simply sets the 'frame' (think of it like a title)
  // for the BarChart.
  void setFrame(string frame) { this->frame = frame; }

  // getFrame()
  // Returns the frame of the BarChart oboject.
  string getFrame() { return frame; }

  // addBar
  // adds a Bar to the BarChart.
  // returns true if successful
  // returns false if there is not room
  bool addBar(string name, int value, string category) {
    // TO DO:  Write this function.
    Bar b(name, value, category);
    if (size == capacity) {
      return false;
    } else {
      this->bars[size] = b;
      size++;
    }
    return true;
  }

  // getSize()
  // Returns the size (number of bars) of the BarChart object.
  int getSize() { return size; }

  // operator[]
  // Returns Bar element in BarChart.
  // This gives public access to Bars stored in the Barchart.
  // If i is out of bounds, throw an out_of_range error message:
  // "BarChart: i out of bounds"
  Bar& operator[](int i) {
    Bar b;
    if (i < 0 || i >= size) {
      throw out_of_range("BarChart: i out of bounds");
    }
    return bars[i];
  }

  // dump
  // Used for printing the BarChart object.
  // Recommended for debugging purposes.  output is any stream (cout,
  // file stream, or string stream).
  // Format:
  // "frame: 1
  // aname 5 category1
  // bname 4 category2
  // cname 3 category3" <-newline here
  void dump(ostream& output) {
    bars->getValue();
    bars->getValue();
    sort(this->bars, this->bars + size);
    reverse(this->bars, this->bars + size);  // I guess that solves it
    output << "frame: " << frame << endl;
    for (int i = 0; i < size; i++) {
      output << this->bars[i].getName() << " ";
      output << this->bars[i].getValue() << " ";
      output << this->bars[i].getCategory() << endl;
      ;
    }
  }

  // graph
  // Used for printing out the bar.
  // output is any stream (cout, file stream, string stream)
  // colorMap maps category -> color
  // top is number of bars you'd like plotted on each frame (top 10? top 12?)
  // The graph must be organized in DECENDING order by value, if both data have
  // the same value, then it is done alphabetically
  void graph(ostream& output, map<string, string>& colorMap, int top) {
    int lenMax = 60;  // this is number of BOXs that should be printed
    string color;
    string barstr = "";
    int divisor;  // Set as an into so it can be rounded down if there is a
                  // decimal.
    sort(bars, bars + size, greater<Bar>());
    int big = bars[0].getValue();
    if (top > size) {
      top = size;
    }
    for (int i = 0; i < top; i++) {
      if (colorMap.empty() || colorMap.count(bars[i].getCategory()) == 0) {
        color = BLACK;
      } else {
        color = colorMap[bars[i].getCategory()];
      }
      divisor = ((double)bars[i].getValue() / (double)big) * lenMax;
      for (int a = 0; a < divisor; a++) {
        barstr += BOX;
      }
      output << color << barstr << " " << bars[i].getName();
      output << " " << bars[i].getValue() << endl;
      barstr.clear();
    }
  }
};