#include <bangtal.h>
#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include <string>

SceneID scene;

ObjectID startButton, puzzle[5][5],restartButton;

int puzzleLocation[5][5], key_value,start_time,end_time;

TimerID timer1;

using namespace std;





void initPuzzle() {


	puzzle[0][0] = createObject("./images/원본_001.png");
	puzzle[1][0] = createObject("./images/원본_002.png");
	puzzle[2][0] = createObject("./images/원본_003.png");
	puzzle[3][0] = createObject("./images/원본_004.png");
	puzzle[4][0] = createObject("./images/원본_005.png");

	puzzle[0][1] = createObject("./images/원본_006.png");
	puzzle[1][1] = createObject("./images/원본_007.png");
	puzzle[2][1] = createObject("./images/원본_008.png");
	puzzle[3][1] = createObject("./images/원본_009.png");
	puzzle[4][1] = createObject("./images/원본_010.png");

	puzzle[0][2] = createObject("./images/원본_011.png");
	puzzle[1][2] = createObject("./images/원본_012.png");
	puzzle[2][2] = createObject("./images/원본_013.png");
	puzzle[3][2] = createObject("./images/원본_014.png");
	puzzle[4][2] = createObject("./images/원본_015.png");


	puzzle[0][3] = createObject("./images/원본_016.png");
	puzzle[1][3] = createObject("./images/원본_017.png");
	puzzle[2][3] = createObject("./images/원본_018.png");
	puzzle[3][3] = createObject("./images/원본_019.png");
	puzzle[4][3] = createObject("./images/원본_020.png");

	puzzle[0][4] = createObject("./images/원본_021.png");
	puzzle[1][4] = createObject("./images/원본_022.png");
	puzzle[2][4] = createObject("./images/원본_023.png");
	puzzle[3][4] = createObject("./images/원본_024.png");
	puzzle[4][4] = createObject("./images/원본_025.png");


	int isin[25] = { 0, };



	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			int ra;
			while (true) {
				ra = rand() % 25;
				if (isin[ra] == 0) {
					isin[ra] = 1;
					break;
				}
			} 
			
			puzzleLocation[x][y] = ra;
			//puzzleLocation[x][y] = x+y*5;
		}
	}
	
	int item_x = puzzleLocation[3][3] % 5;
	int	item_y = puzzleLocation[3][3] / 5;

	puzzle[item_x][item_y] = createObject("images/white_image.png");
	key_value = puzzleLocation[3][3];
}
	
ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown)
{
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}

	return object;
}

string frontAppendMessage(string message, float data) {

	message += to_string(data);
	return message;

}

void endGame(bool success)
{


	if (true) {
		end_time = clock();
		for (int x = 0; x < 5; x++) {
			for (int y = 0; y < 5; y++) {
				hideObject(puzzle[x][y]);
			}
		}
		float res = (float)(end_time - start_time) / CLOCKS_PER_SEC;
		string message = frontAppendMessage("성공!  ", res) += "초 걸리셨습니다";
		showMessage(message.c_str());


		
		//setObjectImage(startButton, "Images/restart.png");

		restartButton = createObject("Images/restart.png", scene, 380, 70, true);

		//showObject(startButton);

	}
	


}

void puzzleLocate(){
	bool isSort = true;
	int before = -1;
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			if (before - puzzleLocation[y][x] != -1) {
				isSort = false;
			}else{
					before = puzzleLocation[y][x];
			}
			//locateObject(puzzle[x][y], scene, x * 179, y * 134);
			int item_x = puzzleLocation[x][y]%5;
			int	item_y = puzzleLocation[x][y]/5;
			
			

			locateObject(puzzle[item_x][item_y], scene, x * 179, (y *-1+4) * 134);
			showObject(puzzle[item_x][item_y]);
		}
	}
	
	if (isSort) {
		
		endGame(true);
	}



}

void startGame()
{
	initPuzzle();
	puzzleLocate();

	start_time = clock();
	hideObject(startButton);
	

}


void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{

	if (object == startButton || object == restartButton) {
		startGame();

	}
	
	else {
	

		for (int x = 0; x < 5; x++) {
			for (int y = 0; y < 5; y++) {

				int item_x = puzzleLocation[x][y] % 5;
				int	item_y = puzzleLocation[x][y] / 5;
				

				if (object == puzzle[item_x][item_y]) {

					//printf("%d\n", key_value);
					//printf("%d\n", key_value);
				

					if (x>0&&puzzleLocation[x - 1][y] == key_value) {
						
						int temp;
						temp = puzzleLocation[x-1][y];
						puzzleLocation[x - 1][y] = puzzleLocation[x][y];
						puzzleLocation[x][y] = temp;
						puzzleLocate();

						return;

					}

					else if (x<5&&puzzleLocation[x + 1][y] == key_value) {
					

						int temp;
						temp = puzzleLocation[x+1][y];
						puzzleLocation[x + 1][y] = puzzleLocation[x][y];
						puzzleLocation[x][y] = temp;
						puzzleLocate();

						return;

					}
					else if (y>0&&puzzleLocation[x][y-1] == key_value) {

						
						int temp;
						temp = puzzleLocation[x][y-1];
						puzzleLocation[x][y-1] = puzzleLocation[x][y];
						puzzleLocation[x][y] = temp;
						puzzleLocate();
						return;

						
					}
					else if (y<5&&puzzleLocation[x][y + 1] == key_value) {

						int temp;
						temp = puzzleLocation[x][y + 1];
						puzzleLocation[x][y + 1] = puzzleLocation[x][y];
						puzzleLocation[x][y] = temp;
						puzzleLocate();
						return;
						
					}

					
				}

			}
		}

	}
	
}

void timerCallback(TimerID timer)
{
	if (timer == timer1) {
		endGame(false);
	}
}






int main()
{
	srand(time(NULL));

	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	scene = createScene("Santa Race", "Images/원본.png");

	startButton = createObject("Images/start.png", scene, 380, 70, true);



	startGame(scene);
}