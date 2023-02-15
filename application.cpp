/*Alexus Bonilla
The purpose of of this program is to display data of an animated 'bar
visualizer'. Each inputed data will have its own category which is then assigned to
its own unique color. When the program is ran, it will display all the data in
an animated format.
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
