#include <iostream>

/*
Assignment:		3
Author:			Haakon Skaug Ingbrigtsen
Student ID:		40105722
Date:			28th October, 2018
*/


/*
DISCLAIMER!:
I did not feel that the assignment was completely clear about how certain functions would work: Escpecially the "Replay"-function.
After reading the assignment again, I see that you may have wanted a different way commanding the objects:
	i.e: up(n), down(n), left(n). I do not feel that changes much however.
I could have improved this code in several way. Specially when it comes to statements. I could've transformed the char value of the objects
to integer instead, to make some statements more "automatic", without having to specify what object one is using.
*/

using namespace std;
int moveNumber = 0, movesA = 0, movesB = 0;		//Variables to keep track of moves
int xA = 0, yA = 0;			//Object A coordinates
int xB = 9, yB = 9;			//Object B coordinates

int xyHistory[2][20][2];	//Variable used to store previous coordinates. Can store 20 coordinates
// xyHistory: 1st index: 0 = Object A, 1 = Object B
//			  2nd index: number of moves
//			  3rd index: 0 = x-coordinate, 1 = y-coordinate

void moveY(char object, int y);
void moveX(char object, int x);

//Function to intuitively move an object to a desired coordination
void moveObject(char object, int x, int y) {
	if (object == 'A') {
		xA = x;
		yA = y;
	}
	else {
		xB = x;
		yB = y;
	}
	printf("\nObject %c was moved to (%d, %d)\n", object, x, y);
}
//Function that prints out graphical interface of the grid.
void showGrid() {
	int i = 0, j = 0;
	printf("\n\t  0   1   2   3   4   5   6   7   8   9\n");
	for (i = 0; i <= 9; i++) {
		if (i == 0) {
			cout << "\n\t_________________________________________\n";
		}
		else {
			printf("\n\t|___|___|___|___|___|___|___|___|___|___|\n");
		}
		//IF Object A is in this coordinate: type 'A'
		for (j = 0; j <= 9; j++) {
			if (j == 0) {
				printf("%d\t|", i);
			}
			if (xA == j && yA == i) {
				printf(" A |");
			}
			else { //Else if object B is in this coordinate: type 'B'
				if (xB == j && yB == i) {
					printf(" B |");
				}
				else {
					printf("   |");
				}
			}
		}
	}
	printf("\n\t|___|___|___|___|___|___|___|___|___|___|\n");
	printf("\n");
}
//Function that checks if a move is valid. 
//ie: will it stay within the grid, and not collide with another object
bool collision(char object, int moveX, int moveY) {
	//Check if the current objects move is valid
	int x, y;
	if (object == 'A') {
		x = xA;
		y = yA;
		if (((x + moveX <= 9) && (y + moveY <= 9)) && ((x + moveX >= 0) && (y + moveY >= 0))) {
			if (x == xB && y == yB) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			return false;
		}
	}
	else {
		x = xB;
		y = yB;
		if ((x + moveX <= 9) && (y + moveY <= 9)) {
			if (x == xA && y == yA) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			return false;
		}
	}
}
//Function that logs the moves that are made
void moveTrack(char object, int n) {
	int objectIndex, x, y;
	if (object == 'A') {
		objectIndex = 0;
		x = xA;
		y = yA;
	}
	else {
		objectIndex = 1;
		x = xB;
		y = yB;
	}
	//First coordinate should be (0, 0)
	xyHistory[objectIndex][n+1][0] = x;								//Current x is stored in index 0.
	xyHistory[objectIndex][n+1][1] = y;								//y is stored in index 1.
}

int main() {
	int choice = 1;													//Variable for menu choices
	int move = 0;													//Variable that reads how many steps to move
	char currentObject = 'A';										//Variable for choosing object to move

	cout << "MENU:\n----------------------------\n";
	cout << "Current Object: " << currentObject;
	cout << "\n 1) Up.\n 2) Down.\n 3) Right.\n 4) Left.\n 5) Reboot.\n 6) Show Grid.";
	cout << "\n 7) Switch object.\n 8) Cancel n moves.\n 9) Replay n cancelled moves.\n";
	cout << " 10) Show position.\n 99) Show MENU\n\n 0) Exit"; 
	cout << "\n----------------------------\n";
	
	while (choice) {
		cin >> choice;
		switch (choice) {
		case 1:
			//UP
			cout << "UP:\nHow many steps?\n>>";
			cin >> move;
			move = -(abs(move));
			moveY(currentObject, move);
			break;
		case 2:
			//DOWN
			cout << "DOWN:\nHow many steps?\n>>";
			cin >> move;
			move = abs(move);
			moveY(currentObject, move);
			break;
		case 3:
			//RIGHT
			cout << "RIGHT:\nHow many steps?\n>>";
			cin >> move;
			move = abs(move);
			moveX(currentObject, move);
			break;
		case 4:
			//LEFT
			cout << "LEFT:\nHow many steps?\n>>";
			cin >> move;
			move = -(abs(move));
			moveX(currentObject, move);
			break;
		case 5:
			//Reboot
			if (currentObject == 'A') {
				moveObject(currentObject, 0, 0);
				movesA++;
			}
			else {
				moveObject(currentObject, 9, 9);
				movesB++;
			}
			moveNumber++;
			break;
		case 6:
			//Show Grid
			showGrid();
			break;
		case 7:
			//Switch Object
			if (currentObject == 'A') {
				currentObject = 'B';
			}
			else {
				currentObject = 'A';
			}
			cout << "Changed object to " << currentObject << endl;
			break;
		case 8:
			//CANCEL
			cout << "You have pressed that you would like to cancel x moves.\nHow many moves would you like to go back?";
			cin >> move;
			if (currentObject == 'A') {
				movesA -= move;
				moveObject(currentObject, xyHistory[0][movesA][0], xyHistory[0][movesA][1]);
			}
			else {
				movesB -= move;
				moveObject(currentObject, xyHistory[1][movesB][0], xyHistory[1][movesB][1]);
			}
			break;
		case 9:
			//REPLAY
			cout << "You have pressed that you would like to replay some of the cancelled moves.\nHow many moves would you like to go forth?";
			cin >> move;
			if (currentObject == 'A') {
				//If there exists a coordinate where we would like to move forth to
				//i.e: we don't want to cancel more moves than we've made.
				if ((xyHistory[0][(movesA + move)][0] != NULL) || (xyHistory[0][(movesA + move)][1] != NULL)) {
						moveObject(currentObject, xyHistory[0][movesA + move][0], xyHistory[0][movesA + move][1]);
				}
			}
			else {
				if (xyHistory[1][movesB + move][0] != NULL && xyHistory[1][movesB + move][1] != NULL) {
					moveObject(currentObject, xyHistory[1][movesB + move][0], xyHistory[1][movesB + move][1]);
				}
			}
			break;
		case 10:
			//POSITION
			printf("\n--------------------------------------------\n");
			printf("Move#: %d|\tX\tY\nA:%d \t%d\t%d\nB: %d\t\t%d\t%d", moveNumber, movesA, xA, yA, movesB, xB, yB);
			printf("\n--------------------------------------------\n");
			break;
		case 99:
			cout << "MENU:\n----------------------------\n";
			cout << "Current Object: " << currentObject;
			cout << "\n 1) Up.\n 2) Down.\n 3) Right.\n 4) Left.\n 5) Reboot.\n 6) Show Grid.";
			cout << "\n 7) Switch object.\n 8) Cancel n moves.\n 9) Replay n cancelled moves.\n";
			cout << " 10) Show position.\n 99) Show MENU\n\n 0) Exit";
			cout << "\n----------------------------\n";
			break;
		}
	}
}

void moveY(char object, int y) {
	//Check if move is valid:

	if (collision(object, 0, y) == false) {
		//FALSE MOVE
		cout << "\nFalse move! Try again..\n";
	}
	else {
		if (object == 'A') {
			yA += y;
			moveTrack(object, movesA);
			movesA++;
			printf("\nObject %c moved %d steps vertically", object, y);
		}
		else {
			yB += y;
			moveTrack(object, movesB);
			movesB++;
			printf("\nObject %c moved %d steps vertically", object, y);
		}
		moveNumber++;
	}
}
void moveX(char object, int x) {

	if (collision(object, x, 0) == false) {
		//FALSE MOVE
		cout << "\nFalse move! Try again..\n";
	}
	else {
		if (object == 'A') {
			xA += x;
			moveTrack(object, movesA);
			movesA++;
			printf("\nObject %c moved %d steps up", object, x);
		}
		else {
			xB += x;
			moveTrack(object, movesB);
			movesB++;
			printf("\nObject %c moved %d steps up", object, x);
		}
		moveNumber++;
	}
}
