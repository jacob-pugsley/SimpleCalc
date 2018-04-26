#include "ui_calc.h"
#include "mainwindow.h"
#include <iostream>
#include <QtGui>
#include <cstdlib>

MainWindow::MainWindow(){
	//set up the interface defined in ui_calc.h
	setupUi(this);

	// connect buttons to slots
	// connect( digits[i], SIGNAL( clicked() ), this, SLOT( gotClicked() ));
	// number buttons first
	connect( zero, SIGNAL( clicked() ), this, SLOT( gotClicked() ));
	connect( one, SIGNAL( clicked() ), this, SLOT( gotClicked() ));
	connect( two, SIGNAL( clicked() ), this, SLOT( gotClicked() ));
	connect( three, SIGNAL( clicked() ), this, SLOT( gotClicked() ));
	connect( four, SIGNAL( clicked() ), this, SLOT( gotClicked() ));
	connect( five, SIGNAL( clicked() ), this, SLOT( gotClicked() ));
	connect( six, SIGNAL( clicked() ), this, SLOT( gotClicked() ));
	connect( seven, SIGNAL( clicked() ), this, SLOT( gotClicked() ));
	connect( eight, SIGNAL( clicked() ), this, SLOT( gotClicked() ));
	connect( nine, SIGNAL( clicked() ), this, SLOT( gotClicked() ));
	connect( decimalButton, SIGNAL( clicked() ), this, SLOT( gotClicked() ));
	//clear button
	connect( clearButton, SIGNAL( clicked() ), this, SLOT( clear() ));
	//equals button
	connect( equalsButton, SIGNAL( clicked() ), this, SLOT( convert() ));
	//operations
	connect( divideButton, SIGNAL( clicked() ), this, SLOT( opClicked() ));
	connect( multiplyButton, SIGNAL( clicked() ), this, SLOT( opClicked() ));
	connect( plusButton, SIGNAL( clicked() ), this, SLOT( opClicked() ));
	connect( minusButton, SIGNAL( clicked() ), this, SLOT( opClicked() ));
	//change sign
	connect( plusMinusButton, SIGNAL( clicked() ), this, SLOT( changeSign() ));

	position = 0;
	answer = 0.0;
}

void MainWindow::gotClicked(){
	// called when a number is pressed

	//add the text on the button which was clicked to what
	//  is already being displayed
	QPushButton *digit = qobject_cast<QPushButton*>( sender() );
	if( display->text() != "0" ){
		display->setText( display->text() + digit->text() );
		// put the char in the array
		input[position] = input[position] + digit->text().toAscii().data();
	}else{
		display->setText( digit->text() );
		// put the char in the array
		input[position] = input[position] + digit->text().toAscii().data();
	}
}

void MainWindow::clear(){
	// called when AC is pressed
	// reset everything

	// clear the array
	for( int i = 0; i < 30; i++ ){
		input[i] = "";
		inputAsDouble[i] = -9999;
		opPos[i] = 0;
	}
	//reset position
	position = 0;
	//reset the display
	display->setText("0");

}

double MainWindow::solve(){
	// perform math operations
	// look for multiplication or division first
	for( int i = 0; i < position; i++ ){
		if( opPos[i] == 4 ){
			//divide
			if( inputAsDouble[i+1] != 0 ){
				std::cout << "dividing...\n";
				double temp = inputAsDouble[i-1] / inputAsDouble[i+1];
				inputAsDouble[i+1] = temp;
				inputAsDouble[i-1] = -9999;
				opPos[i] = -1;
			}
		}else if( opPos[i] == 3 ){
			//multiply
			double temp = inputAsDouble[i-1] * inputAsDouble[i+1];
			inputAsDouble[i+1] = temp;
			inputAsDouble[i-1] = -9999;
			opPos[i] = -1;
		}
	}
	for( int i = 0; i < position; i++ ){
		if( opPos[i] == 2 ){
			//subtract
			double temp = inputAsDouble[i-1] - inputAsDouble[i+1];
			inputAsDouble[i+1] = temp;
			inputAsDouble[i-1] = -9999;
			opPos[i] = -1;
		}else if( opPos[i] == 1 ){
			//add
			std::cout << "adding...\n";
			double temp = inputAsDouble[i-1] + inputAsDouble[i+1];
			inputAsDouble[i+1] = temp;
			inputAsDouble[i-1] = -9999;
			opPos[i] = -1;
		}
	}

	for( int i = 0; i < position; i++ ){
		std::cout << opPos[i] << " ";
	}
	std::cout << '\n';

	return inputAsDouble[position];
}




void MainWindow::convert(){
	// convert the string array to a double array
	for( int i = 0; i <= position; i++ ){
		opPos[i] = 0;
		inputAsDouble[i] = -9999;
	}

	int i = 0;

	while( i <= position ){
		if( input[i] == "+" ){
			//1 represents addition
			opPos[i] = 1;
		}else if( input[i] == "-" ){
			//2 represents subtraction
			opPos[i] = 2;
		}else if( input[i] == "*" ){
			//3 represents multiplication
			opPos[i] = 3;
		}else if( input[i] == "/" ){
			//4 represents division
			opPos[i] = 4;
		}else{
			//this is a number
			inputAsDouble[i] = atof( input[i].c_str() );
		}
		i++;
	}
	std::cout << "position = " << position << '\n';
	std::cout << "opPos array:\n";
	for( int i = 0; i <= position; i++ ){
		std::cout << opPos[i] << " ";
	}
	std::cout << "\ninput array:\n";
	for( int i = 0; i <= position; i++ ){
		std::cout << inputAsDouble[i] << " ";
	}
	std::cout << "\n";

	answer = solve();
	std::cout << "ouput array:\n";
	for( int i = 0; i <= position; i++ ){
		std::cout << inputAsDouble[i] << " ";
	}
	std::cout << "\n";
	// put the solution on the screen
	display->setText( QString::number( answer ) );


}

void MainWindow::changeSign(){
	// called when +/- is pressed
	//answer *= -1;
	inputAsDouble[position] *= -1;
	display->setText( QString::number( inputAsDouble[position] ) );
}

void MainWindow::opClicked(){
	// get the text from the button
	QPushButton *digit = qobject_cast<QPushButton*>( sender() );
	// put the operation symbol in the next index
	position++;
	input[position] = digit->text().toAscii().data();
	// move to the next index for the next number
	position++;

	//put the symbol on the screen
	display->setText( display->text() + digit->text() );
}
