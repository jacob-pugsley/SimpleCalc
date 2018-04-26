#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_calc.h"

class MainWindow:public QMainWindow, private Ui::MainWindow{
	Q_OBJECT
public:
	MainWindow();

private slots:
	void gotClicked();	// called when any button is clicked
	double solve(); 		// compute the operation when equals is clicked
	void changeSign();  // change the sign when +/- is clicked
	void clear();		// reset label text when AC is clicked
	void opClicked();   // called when an operation is clicked
	void convert(); // convert the string array to a double array for math

private:
	int position; //store the position in the array
	std::string input[30]; // will contain the calculator's input

	double inputAsDouble[30]; // will contain the array as doubles
	int opPos[30]; //store the position and type of operation
	double answer; //store the previous answer
};



#endif