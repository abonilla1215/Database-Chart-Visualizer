// Bar Chart Animation
//
// This application uses BarChartAnimate (which uses BarChart, which uses Bar)
// to produce an animated bar chart.
//
// Once your three class/abstraction files are completed and tested, run with
// this application to see your final creation.
//
// TO DO: Nothing for the standard application, just compile and run! However,
// before submitting you need to add your creative component.
//
// Shanon Reckinger
// U. of Illinois, Chicago
// CS 251: Fall 2021
//

/*Alexus Bonilla
Project 3 - Animated Bar Chart
The purpose of of this program is to display data of in an animated 'bar
format'. Each inputed data will have its own category which is then assigned to
its own unique color. When the program is ran, it will display all the data in
an animated format. NOTE-- I did NOT add a creative component.
  */
#include "barchartanimate.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
using namespace std;

int main() {

  string filename = "Data Charts/cities.txt";
  ifstream inFile(filename);
  string title;
  getline(inFile, title);
  string xlabel;
  getline(inFile, xlabel);
  string source;
  getline(inFile, source);

  BarChartAnimate bca(title, xlabel, source);

  while (!inFile.eof()) {
    bca.addFrame(inFile);
  }

  bca.animate(cout, 12, -1);
  return 0;
}
