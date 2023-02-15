// bar.h
/*
Alexus Bonilla
Animated Bar Chart
The purpose of of this program is to display data of in an animated 'bar format'. Each inputed data will have its 
own category which is then assigned to its own unique color. When the program is ran, it will display all the 
data in an animated format.

'tests.cpp' is designed to test if my functions and other files are working correctly.
  */
#include <iostream>
#include "barchartanimate.h"
using namespace std;


bool testBarDefaultConstructor() {
	Bar b;
    if (b.getName() != "") {
    	cout << "testBarDefaultConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 0) {
    	cout << "testBarDefaultConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "") {
    	cout << "testBarDefaultConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarParamConstructor() {
	Bar b("Chicago", 9234324, "US");
    if (b.getName() != "Chicago") {
    	cout << "testBarParamConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 9234324) {
    	cout << "testBarParamConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "US") {
    	cout << "testBarParamConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarParamConstructor: all passed!" << endl;
    return true;
}

//My own tests
//Testing Milestone #1
bool testBarChartDefaultConstructor() {
	BarChart bc;
    if (bc.getSize() != 0) {
      cout << RED;
    	cout << "testBarChartDefaultConstructor: getSize failed" << endl;
    	return false;
    } else if (bc.getFrame() != "") {
      cout << RED;
      cout << "testBarChartDefaultConstructor: getFrame failed" << endl;
      return false;
    } else if (bc.addBar("Chicago", 1020, "US") != false) {
      cout << RED;
      cout << "testBarChartDefaultConstructor: addBar failed" << endl;
      return false;
    } 
  
    cout << GREEN;
    cout << "testBarDefaultConstructor: all passed!" << endl;
    return true;
}

//Testing MileStone #2
bool testBarChartParamConstructor() {
  BarChart bc(3);
  //BarChart bcCopy(bc);
  bc.setFrame("1950");
  
  if (bc.addBar("Chicago", 1020, "US") != true) {
      cout << RED;
      cout << "testBarChartDefaultConstructor: addBar failed" << endl;
      return false;
  } else if (bc.addBar("NYC", 1300, "US") != true) {
    cout << RED;
    cout << "testBarChartDefaultConstructor: addBar failed" << endl;
    return false;
  } else if (bc.addBar("Paris",1200,"France") != true) {
    cout << RED;
    cout << "testBarChartDefaultConstructor: addBar failed" << endl;
    return false;
  } else if (bc.addBar("TheProjekts",1,"US") != false) {  //Expected NOTHING to be added in
    cout << RED;
    cout << "testBarChartDefaultConstructor: addBar failed" << endl;
    return false;
  } else if (bc.getSize() != 3) {
    cout << RED;
    cout << "testBarChartDefaultConstructor: getSize failed" << endl;
     return false;
  } else if (bc.getFrame() != "1950") {
    cout << RED;
    cout << "testBarChartDefaultConstructor: getFrame failed" << endl;
    return false;
  }  
  for (int i = 0; i < bc.getSize(); i++) {
      cout << GOLD;
      cout << bc[i].getName() << " ";
      cout << bc[i].getValue() << " ";
      cout << bc[i].getCategory();
      cout << endl;
  }
  cout << RESET;
  bc.dump(cout);
  bc.clear();
  if (bc.getSize() != 0) {
      cout << RED;
    	cout << "testBarChartDefaultConstructor: clear failed" << endl;
    	return false;
  }
  cout << GREEN;
  cout << "testBarDefaultConstructor: all passed!" << endl;
  return true;
}

bool testBarChartCopyConstructor() {
  BarChart bc(3);
  bc.setFrame("MainTownship");
  bc.addBar("MainEast", 360, "US");
  bc.addBar("MainWest", 400, "US");
  bc.addBar("MainSouth", 250, "US");
  BarChart bcCopy(bc);
  if (bcCopy.getSize() != 3) {
    cout << RED;
    cout << "testBarChartCopyConstructor: getSize failed" << endl;
    return false;
  } else if (bc.getFrame() != "MainTownship") {
    cout << RED;
    cout << "testBarChartCopyConstructor: getFrame failed" << endl;
    return false;
  }  
  for (int i = 0; i < bcCopy.getSize(); i++) {
    cout << GOLD;
    cout << bc[i].getName() << " ";
    cout << bc[i].getValue() << " ";
    cout << bc[i].getCategory();
    cout << endl;
  }
  cout << RESET;
  bcCopy.dump(cout);
  bc.clear();
  bcCopy.clear();
  cout << GREEN;
  cout << "testBarChartCopyConstructor: all passed!" << endl;
  return true;
}

bool testBarChartCopyOperator() {
  BarChart bc1(3);
  bc1.setFrame("Games");
  bc1.addBar("FighterZ", 12, "US");
  bc1.addBar("League", 562, "US");
  bc1.addBar("Valorant", 784, "US");
  for (int i = 0; i < bc1.getSize(); i++) {
    cout << GOLD;
    cout << bc1[i].getName() << " ";
    cout << bc1[i].getValue() << " ";
    cout << bc1[i].getCategory();
    cout << endl;
  }
  BarChart bc2(2);
  bc2.setFrame("ActuallyGoodGame");
  bc2.addBar("CupHead", 2, "US");
  bc2.addBar("AmongUs", 10000, "US");
  bc1 = bc2;
  if (bc2.getSize() != 2) {
  cout << RED;
  cout << "testBarChartCopyOperator: getSize failed" << endl;
  return false;
  } else if (bc1.addBar("Overwatch", 12, "US") != false) {
    cout << RED;
    cout << "testBarChartCopyOperator: addbar failed" << endl;
    return false;
  }
  cout << RESET;
  bc1.dump(cout);
  cout << GREEN;
  cout << "testBarChartCopyOperator: all passed!" << endl;
  return true;
}

//Testing the graph function for:
//Case 1: A map is provided
//Case 2: No map is provided
//Case 3: A category is NOT in a map
void testGraph() {
  map<string,string> colorMap;
  // colorMap["East"] = BLUE;
  // colorMap["West"] = GOLD;
  // colorMap["South"] = RED;
  BarChart bc(3);
  bc.setFrame("MainTownship");
  bc.addBar("MainEast", 360, "East");
  bc.addBar("MainWest", 400, "West");
  bc.addBar("MainSouth", 250, "South");
  bc.graph(cout, colorMap, 3);
}

/*
I did not test 'barchartanimate.h' in this file, instead I just used the application.cpp because it was already set up for so it
made things a lot easier for me.
  */


int main() {
	testBarDefaultConstructor();
	testBarParamConstructor();
  testBarChartDefaultConstructor();
  testBarChartParamConstructor();
  testBarChartCopyConstructor();
  testBarChartCopyOperator();
	testGraph();
    return 0;
}