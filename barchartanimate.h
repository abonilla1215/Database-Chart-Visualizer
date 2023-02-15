// barchartanimate.h
/*
Alexus Bonilla
'barchartanimate.h' is to take all the 'bar charts' and animate them in the
console. In the application, the file containing the data will be read and
during that process, 'barchartanimate.h' will parse through every line, assign
the data to a bar, take those bars and put into a chart, color code the bar
chart, and finally animate them.
*/

#include <unistd.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "barchart.h"
#include "myrandom.h"  // used in autograder, do not remove

using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
 private:
  //
  // Private member variables for the abstraction.
  // This implementation uses a low-level C array, bars, to store a list of
  // BarCharts.  As a result, you must also keep track of the number of
  // elements stored (size) and the capacity of the array (capacity).
  // This IS dynamic array, so it must expand automatically, as needed.
  //
  BarChart* barcharts;  // pointer to a C-style array
  int size;
  int capacity;
  map<string, string> colorMap;
  // Added private members to help set up the animate function
  string title;
  string xlabel;
  string source;
  int colorIndex;

 public:
  // a parameterized constructor:
  // Like the ourvector, the barcharts C-array should be constructed here
  // with a capacity of 4.
  BarChartAnimate(string title, string xlabel, string source) {
    barcharts = new BarChart[4];  // we start with a capacity of 4:
    size = 0;
    capacity = 4;
    this->title = title;
    this->xlabel = xlabel;
    this->source = source;
    this->colorIndex = 0;
  }

  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated
  // by BarChartAnimate.
  //
  virtual ~BarChartAnimate() {
    if (barcharts != nullptr) {
      delete[] barcharts;
    }
  }

  // addFrame:
  // adds a new BarChart to the BarChartAnimate object from the file stream.
  // if the barcharts has run out of space, double the capacity (see
  // ourvector.h for how to double the capacity).
  // See application.cpp and handout for pre and post conditions.
  void addFrame(ifstream& file) {
    int barMax;
    //int colorMapLenght = 0;
    string test;
    string line;
    string name;
    string frame;
    int value;
    string catagory;
    int flag = 0;
    int flag2 = 0;
    // Will find the 'name' + 'value' + 'catagory' along with the 'capicity'
    file >> barMax;
    ws(file);
    BarChart bc(barMax);
    flag++;
    // The parameter is designed to accommodate the extra space in the file
    while (flag != barMax + 2) {
      getline(file, line, '\n');
      stringstream ss(line);
      while (ss.good()) {
        getline(ss, test, ',');
        if (test != "") {
          flag2++;
        }
        // Gets this line: 1500->(flag 1),Beijing->(flag 2),China,672->(flag
        // 4),East Asia->(flag 5)
        if (flag2 == 1) {
          frame = test;
        } else if (flag2 == 2) {
          name = test;
        } else if (flag2 == 4) {
          value = stoi(test);
        } else if (flag2 == 5) {
          catagory = test;
          bc.addBar(name, value, catagory);
          if (colorMap.count(catagory) == 0) {
            colorMap[catagory] = COLORS[colorIndex];
            colorIndex++;
            if (colorIndex == COLORS.size()) {
              colorIndex = 0;
            }
          }
          flag2 = 0;
        }
      }
      flag++;
    }
    bc.setFrame(frame);
    // If the array becomes full, copy over and make a new one
    // with a larger capacity.
    if (size == capacity) {
      int newCapacity = capacity * 2;
      BarChart* newBarChart = new BarChart[newCapacity];
      for (int i = 0; i < size; ++i) {
        newBarChart[i] = barcharts[i];
      }
      delete[] this->barcharts;
      barcharts = newBarChart;
      capacity = newCapacity;
    }
    this->barcharts[size] = bc;
    size++;
  }

  // animate:
  // this function plays each frame stored in barcharts.  In order to see the
  // animation in the terminal, you must pause between each frame.  To do so,
  // type:  usleep(3 * microsecond);
  // Additionally, in order for each frame to print in the same spot in the
  // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
  // in between each frame.
  void animate(ostream& output, int top, int endIter) {
    unsigned int microsecond = 50000;
    int fps = 0;
    if (endIter == -1) {
      fps = size;
    } else {
      fps = endIter;
    }
    for (int i = 0; i < fps; i++) {
      usleep(3 * microsecond);
      output << CLEARCONSOLE;
      output << BLACK;
      output << title << endl;
      output << BLACK;
      output << source << endl;
      this->barcharts[i].graph(output, colorMap, top);
      output << BLACK;
      output << xlabel << endl;
      output << BLACK;
      output << "Frame: " << this->barcharts[i].getFrame() << endl;
    }
  }

  //
  // Public member function.
  // Returns the size of the BarChartAnimate object.
  //
  int getSize() { return size; }

  //
  // Public member function.
  // Returns BarChart element in BarChartAnimate.
  // This gives public access to BarChart stored in the BarChartAnimate.
  // If i is out of bounds, throw an out_of_range error message:
  // "BarChartAnimate: i out of bounds"
  //
  BarChart& operator[](int i) {
    BarChart bc;
    if (i < 0 || i >= size) {
      throw out_of_range("BarChart: i out of bounds");
    }
    return barcharts[i];
  }
};
