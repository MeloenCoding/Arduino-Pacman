// main setup
#include <RGBmatrixPanel.h>

#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

// creates the map for the player to move in and stores all
// information about everything the player can interact with 
byte matrixMap[64][32];// 0=pad 1=muur 2=eten 3=portaal

byte enemyMap[64][32]; // 0=pad 1=muur 2=kruispunt


int mapDelay = 50;
int clockCount = 0;

//player info
int playerLocationX = 1;
int playerLocationY = 1;
int playerFoodCount = 0;

int gametype = 0; // 0 easy 1 hard 
bool gameStarted = false;

  //enemy info
  int enemyLocationX = 0;
  int enemyLocationY = 0;
  int enemyDir = 0; // 0 up 1 right 2 down 3 left

  int enemyLocationX2 = 0;
  int enemyLocationY2 = 0;
  int enemyDir2 = 2; // 0 up 1 right 2 down 3 left

  int enemyLocationX3 = 0;
  int enemyLocationY3 = 0;
  int enemyDir3 = 1; // 0 up 1 right 2 down 3 left

  int enemyLocationX4 = 0;
  int enemyLocationY4 = 0;
  int enemyDir4 = 2; // 0 up 1 right 2 down 3 left


void drawPortal1(int x, int y){// portal creating
  matrixMap[x][y] = 3; // sets the location of the pixel in the matrixMap to 3
  enemyMap[x][y] = 1; // sets the location of the pixel in the enemyMap to 1
  matrix.drawPixel(x, y, matrix.Color333(7, 7, 7));// draws line onbaord
}
void drawPortal2(int x, int y){// portal creating
  matrixMap[x][y] = 4; // sets the location of the pixel in the matrixMap to 3
  enemyMap[x][y] = 1; // sets the location of the pixel in the enemyMap to 1
  matrix.drawPixel(x, y, matrix.Color333(7, 7, 7));// draws line onbaord
}

bool nextMovePossible(int x, int y) { // checks if player is on an active pixel
  if (matrixMap[x][y] == 1) { // is pixel free?
    return false; // no
  }
  return true; // yes
}

void drawFood(int x, int y) { // draws pixel ( food ) on location x y
  matrixMap[x][y] = 2; // sets the location of the pixel in the matrixMap to 2
  matrix.drawPixel(x, y, matrix.Color333(7, 0, 7)); // draws the pixel
}

void drawlineH(int x1, int x2, int y) { // draws horizontal line
  int len = x2 - x1 + 1; // calculate length of line
  for (int i = 0; i < len; i++) { // puts the index in var matrixMap equal to 1
    matrixMap[x1 + i][y] = 1; // sets the location of the pixel in the matrixMap to 1
    enemyMap[x1 + i][y] = 1; // sets the location of the pixel in the enemyMap to 1
  }
  matrix.drawLine(x1, y, x2, y, matrix.Color333(0, 0, 7));// draws line onbaord
}

void drawlineV(int y1, int y2, int x) { // draws vertical line
  int len = y2 - y1 + 1; // calculate length of line
  for (int i = 0; i < len; i++) { // puts the index in var matrixMap equal to 1
    matrixMap[x][y1 + i] = 1; // sets the location of the pixel in the matrixMap to 1
    enemyMap[x][y1 + i] = 1; // sets the location of the pixel in the enemyMap to 1
  }
  matrix.drawLine(x, y1, x, y2, matrix.Color333(0, 0, 7));// draws line onbaord
}

bool isOnFood(int x, int y) { // checks if player is on an food pixel
  if (matrixMap[x][y] == 2) { // is pixel food?
    return true; // yes
  }
  return false; // no
}

void drawScoreLine(int totalScore){// score handler
  if (totalScore == 30)
  {
    gameStarted = false;
  }
  else{
    if(totalScore > 0){
      matrix.drawLine(62, 30, 62, 30-totalScore+1, matrix.Color333(7, 0, 7));// draws line onbaord
    }
  }
}

void drawMap1(){ // draw outer map

    // left
    drawlineV(0,31,0);
      delay(mapDelay);
    drawlineH(0,6,0);
    drawlineH(0,6,31);
    delay(mapDelay);
    drawlineV(0,4,6);
    drawlineV(27,31,6);
  delay(mapDelay);
    drawlineH(6,10,5);
    drawlineH(6,10,26);
  delay(mapDelay);
    drawlineV(0,4,10);
    drawlineV(27,31,10);
  delay(mapDelay);
    drawlineH(10,16,0);
    drawlineH(10,16,31);
  delay(mapDelay);
    drawlineV(0,6,16);
    drawlineV(25,31,16);
  delay(mapDelay);
    drawlineH(16,24,6);
    drawlineH(16,24, 25);
  delay(mapDelay);
    drawlineH(24,28,7);
    drawlineH(24,28, 24);

  delay(mapDelay);

    // right
    drawlineV(0,31,61);
  delay(mapDelay);
    drawlineH(55,61,0);
    drawlineH(55,61,31);
  delay(mapDelay);
    drawlineV(0,5,55);
    drawlineV(26,31,55);
  delay(mapDelay); // vertical lines of line 59
    drawlineV(2,12,59);
    drawlineV(19,29,59);
  delay(mapDelay);
    drawlineH(51,55,5);
    drawlineH(51,55,26);
  delay(mapDelay);
    drawlineV(0,5,51);
    drawlineV(26,31,51);
  delay(mapDelay);
    drawlineH(45,50,0);
    drawlineH(45,50,31);
  delay(mapDelay);
    drawlineV(0,6,45);
    drawlineV(25,31,45);
  delay(mapDelay);
    drawlineH(37,44,6);
    drawlineH(37,44,25);
  delay(mapDelay);
    drawlineH(51,59,19);
    drawlineH(51,59,12);
  delay(mapDelay);
    drawlineV(7,12,51);
    drawlineV(19,24,51);
  delay(mapDelay);
    drawlineH(51,57, 7);
    drawlineH(51,57,24);

  delay(mapDelay);
    drawlineV(0,31,63);
    drawlineH(61,62,31);
    drawlineH(61,62,0);

    //inside left
  delay(mapDelay);
    drawlineV(2,12,2);
    drawlineV(19,29,2);
  delay(mapDelay);
    drawlineH(2,10,12);
    drawlineH(2,10,19);
  delay(mapDelay);
    drawlineV(7,12,10);
    drawlineV(19,24,10);
  delay(mapDelay);
    drawlineH(4,10,7);
    drawlineH(4,10,24);
  delay(mapDelay);
    drawlineV(2,7,4);
    drawlineV(24,29,4);
  delay(mapDelay);
    drawlineH(2,4,2);
    drawlineH(2,4,29);
  delay(mapDelay);
    drawlineH(2,12,14);
    drawlineH(2,12,17);
  delay(mapDelay);
    drawlineV(2,14,12);
    drawlineV(17,29,12);
  delay(mapDelay);
    drawlineH(12,14,2);
    drawlineH(12,14,29);

  // inside right

  delay(mapDelay);
    drawlineH(32,37,7);
    drawlineH(32,37,24);
  delay(mapDelay);
    drawlineV(2,29,14);
    drawlineV(14,17,2);
  delay(mapDelay);
    drawlineH(57,59,2);
    drawlineH(57,59,29);
  delay(mapDelay);
    drawlineV(2,7,57);
    drawlineV(24,29,57);
  delay(mapDelay);
    drawlineV(7,12,59);
    drawlineV(19,24,59);
  delay(mapDelay);
    drawlineH(4,10,7);
    drawlineH(4,10,24);
  delay(mapDelay);
    drawlineV(2,14,49);
    drawlineV(17,29,49);
  delay(mapDelay);
    drawlineV(2,29,47);
  delay(mapDelay);
    drawlineH(49,59,14);
    drawlineH(49,59,17);
  delay(mapDelay);
    drawlineH(47,49,2);
    drawlineH(47,49,29);
  delay(mapDelay);
    drawlineV(14,17,59);



  // middle
    drawlineV(0,7,32);
    drawlineV(24,31,32);
  delay(mapDelay);
    drawlineV(0,7,29);
    drawlineV(24,31,29);
  delay(mapDelay);
    drawlineH(29,32,0);
    drawlineH(29,32,31);
    drawPortal1(30,1);
    drawPortal1(31,1);
    drawPortal2(30,30);
    drawPortal2(31,30);
}

void enemyCross(int x, int y){// add pathCrossing to map
  enemyMap[x][y] = 2;
}

void drawMap2(){ // draw middle of map
    drawlineH(16,22, 8);
    drawlineH(16,22, 12);
    drawlineH(16,22, 19);
    drawlineH(16,22, 23);
  delay(mapDelay);
    drawlineH(39,45, 8);
    drawlineH(39,45, 12);
    drawlineH(39,45, 19);
    drawlineH(39,45, 23);
  delay(mapDelay);
    drawlineV(8,12,16);
    drawlineV(14,17,16);
    drawlineV(19,23,16);
  delay(mapDelay);
    drawlineV(8,12,45);
    drawlineV(14,17,45);
    drawlineV(19,23,45);
  delay(mapDelay);
    drawlineV(8,12,22);
    drawlineV(19,23,22);
    drawlineV(8,12,39);
    drawlineV(19,23,39);
  delay(mapDelay);
    drawlineV(14,17,19);
    drawlineV(14,17,42);
  delay(mapDelay);
    drawlineH(16,19,14);
    drawlineH(16,19,17);
    drawlineH(42,45,14);
    drawlineH(42,45,17);
  delay(mapDelay);
    matrix.drawRect(26, 11, 10, 10, matrix.Color333(7, 7, 7));
    drawlineH(24,37,9);
    drawlineH(24,37,22);
    drawlineV(9,14,24);
    drawlineV(17,22,24);
    drawlineV(9,14,37);
    drawlineV(17,22,37);
    drawlineH(21,24,14);
    drawlineH(21,24,17);
    drawlineH(37,40,14);
    drawlineH(37,40,17);
    
    drawlineV(14,17,21);
    drawlineV(14,17,40);

    enemyCross(1,1);
    enemyCross(1,13);
    enemyCross(1,18);
    enemyCross(1,30);

    enemyCross(5,1);
    enemyCross(5,6);
    enemyCross(5,25);
    enemyCross(5,30);

    enemyCross(11,1);
    enemyCross(11,6);
    enemyCross(11,13);
    enemyCross(11,18);
    enemyCross(11,25);
    enemyCross(11,30); 

    enemyCross(15,1);
    enemyCross(15,7);
    enemyCross(15,13);
    enemyCross(15,18);
    enemyCross(15,24);
    enemyCross(15,30);

    enemyCross(20,13);
    enemyCross(20,18);

    enemyCross(23,7);
    enemyCross(23,8);
    enemyCross(23,13);
    enemyCross(23,18);
    enemyCross(23,24);

    enemyCross(23,23);


    enemyCross(60,1);
    enemyCross(60,13);
    enemyCross(60,18);
    enemyCross(60,30);

    enemyCross(56,1);
    enemyCross(56,6);
    enemyCross(56,25);
    enemyCross(56,30);

    enemyCross(50,1);
    enemyCross(50,6);
    enemyCross(50,13);
    enemyCross(50,18);
    enemyCross(50,25);
    enemyCross(50,30); 

    enemyCross(46,1);
    enemyCross(46,7);
    enemyCross(46,13);
    enemyCross(46,18);
    enemyCross(46,24);
    enemyCross(46,30);

    enemyCross(41,13);
    enemyCross(41,18);

    enemyCross(38,7);
    enemyCross(38,13);
    enemyCross(38,18);
    enemyCross(38,24);
    enemyCross(38,8);
    enemyCross(38,23);
    
          
}

void handlePortal(int id){// handles portal movement

      if (id == 1)
      {
        // down
        playerLocationX = 30;
        playerLocationY = 29;
      }
      else if (id == 2) {
        playerLocationX = 30;
        playerLocationY = 2;
      }
      else if (id == 3) {
        playerLocationX = 31;
        playerLocationY = 29;
      }
      else if (id == 4) {
        playerLocationX = 31;
        playerLocationY = 2;
      }
      
    }

void wave(int number){// food / enemy / speed / difficulty increase

  switch (number)
  {
  case 0:
    drawFood(15,4);
    drawFood(31,5);
    drawFood(46,6);
    drawFood(60,23);
    drawFood(17,7);
    break;
  
  case 1:
    drawFood(20,16);
    drawFood(31,23);
    drawFood(50,26);
    drawFood(60,5);
    drawFood(33,8);
    break;

  case 2:
    drawFood(20,24);
    drawFood(38,19);
    drawFood(54,13);
    drawFood(1,16);
    drawFood(40,7);
    break;

  case 3:
    drawFood(23,10);
    drawFood(39,13);
    drawFood(54,6);
    drawFood(11,22);
    drawFood(46,21);
    break;
  case 4:
    drawFood(26,8);
    drawFood(42,24);
    drawFood(55,18);
    drawFood(15,17);
    drawFood(50,20);
    break;
  
  case 5:
    drawFood(15,4);
    drawFood(31,23);
    drawFood(54,13);
    drawFood(11,22);
    drawFood(50,20);
    break;
  
  default:
    break;
  }
}

bool nextMoveEnemy(int x, int y){// enemy handler
  if (enemyMap[x][y] == 2 || matrixMap[x][y] != 1)
  {
    return true;
  }
  else{
    return false;
  }
}

void handleEnemyMovement1(){
  if(enemyDir == 0) { // enemy up
    if (nextMoveEnemy(enemyLocationX, enemyLocationY - 1))
    {
      matrix.drawPixel(enemyLocationX, enemyLocationY, matrix.Color333(0,0,0));
      if (matrixMap[enemyLocationX][enemyLocationY] == 2)
      {
        drawFood(enemyLocationX,enemyLocationY);
      }
      enemyLocationY--;
    }
  }
  else if(enemyDir == 1) { // enemy right
    if (nextMoveEnemy(enemyLocationX + 1, enemyLocationY))
    {
      matrix.drawPixel(enemyLocationX, enemyLocationY, matrix.Color333(0,0,0));
      if (matrixMap[enemyLocationX][enemyLocationY] == 2)
      {
        drawFood(enemyLocationX,enemyLocationY);
      }
      enemyLocationX++;
    }
  }
  else if(enemyDir == 2) { // enemy down
    if (nextMoveEnemy(enemyLocationX, enemyLocationY + 1))
    {
      matrix.drawPixel(enemyLocationX, enemyLocationY, matrix.Color333(0,0,0));
      if (matrixMap[enemyLocationX][enemyLocationY] == 2)
      {
        drawFood(enemyLocationX,enemyLocationY);
      }
      enemyLocationY++;
    }
  }
  else if(enemyDir == 3) { // enemy left
    if (nextMoveEnemy(enemyLocationX - 1, enemyLocationY))
    {
      matrix.drawPixel(enemyLocationX, enemyLocationY, matrix.Color333(0,0,0));
      if (matrixMap[enemyLocationX][enemyLocationY] == 2)
      {
        drawFood(enemyLocationX,enemyLocationY);
      }
      enemyLocationX--;
    }
  }
  
  if (enemyMap[enemyLocationX][enemyLocationY] == 2)
  {
    long randomNumb = random(0,4);//random number between 0-3
    if (randomNumb == 0 ) {enemyDir = 0;}
    else if (randomNumb == 1) {enemyDir = 1;}
    else if (randomNumb == 2) {enemyDir = 2;}
    else if (randomNumb == 3) {enemyDir = 3;}
  }
}

void handleEnemyMovement2(){
  if(enemyDir2 == 0) { // enemy up
        if (nextMoveEnemy(enemyLocationX2, enemyLocationY2 - 1))
        {
          matrix.drawPixel(enemyLocationX2, enemyLocationY2, matrix.Color333(0,0,0));
          if (matrixMap[enemyLocationX2][enemyLocationY2] == 2)
          {
            drawFood(enemyLocationX2,enemyLocationY2);
          }
          enemyLocationY2--;
        }
      }
      else if(enemyDir2 == 1) { // enemy right
        if (nextMoveEnemy(enemyLocationX2 + 1, enemyLocationY2))
        {
          matrix.drawPixel(enemyLocationX2, enemyLocationY2, matrix.Color333(0,0,0));
          if (matrixMap[enemyLocationX2][enemyLocationY2] == 2)
          {
            drawFood(enemyLocationX2,enemyLocationY2);
          }
          enemyLocationX2++;
        }
      }
      else if(enemyDir2 == 2) { // enemy down
        if (nextMoveEnemy(enemyLocationX2, enemyLocationY2 + 1))
        {
          matrix.drawPixel(enemyLocationX2, enemyLocationY2, matrix.Color333(0,0,0));
          if (matrixMap[enemyLocationX2][enemyLocationY2] == 2)
          {
            drawFood(enemyLocationX2,enemyLocationY2);
          }
          enemyLocationY2++;
        }
      }
      else if(enemyDir2 == 3) { // enemy left
        if (nextMoveEnemy(enemyLocationX2 - 1, enemyLocationY2))
        {
          matrix.drawPixel(enemyLocationX2, enemyLocationY2, matrix.Color333(0,0,0));
          if (matrixMap[enemyLocationX2][enemyLocationY2] == 2)
          {
            drawFood(enemyLocationX2,enemyLocationY2);
          }
          enemyLocationX2--;
        }
      }
      if (enemyMap[enemyLocationX2][enemyLocationY2] == 2)
      {
        long randomNumb = random(0,4);//random number between 0-3
        if (randomNumb == 0 ) {enemyDir2 = 0;}
        else if (randomNumb == 1) {enemyDir2 = 1;}
        else if (randomNumb == 2) {enemyDir2 = 2;}
        else if (randomNumb == 3) {enemyDir2 = 3;}
      }
}

void handleEnemyMovement3(){
    if(enemyDir3 == 0) { // enemy up
        if (nextMoveEnemy(enemyLocationX3, enemyLocationY3 - 1))
        {
          matrix.drawPixel(enemyLocationX3, enemyLocationY3, matrix.Color333(0,0,0));
          if (matrixMap[enemyLocationX3][enemyLocationY3] == 2)
          {
            drawFood(enemyLocationX3,enemyLocationY3);
          }
          enemyLocationY3--;
        }
      }
      else if(enemyDir3 == 1) { // enemy right
        if (nextMoveEnemy(enemyLocationX3 + 1, enemyLocationY3))
        {
          matrix.drawPixel(enemyLocationX3, enemyLocationY3, matrix.Color333(0,0,0));
          if (matrixMap[enemyLocationX3][enemyLocationY3] == 2)
          {
            drawFood(enemyLocationX3,enemyLocationY3);
          }
          enemyLocationX3++;
        }
      }
      else if(enemyDir3 == 2) { // enemy down
        if (nextMoveEnemy(enemyLocationX3, enemyLocationY3 + 1))
        {
          matrix.drawPixel(enemyLocationX3, enemyLocationY3, matrix.Color333(0,0,0));
          if (matrixMap[enemyLocationX3][enemyLocationY3] == 2)
          {
            drawFood(enemyLocationX3,enemyLocationY3);
          }
          enemyLocationY3++;
        }
      }
      else if(enemyDir3 == 3) { // enemy left
        if (nextMoveEnemy(enemyLocationX3 - 1, enemyLocationY3))
        {
          matrix.drawPixel(enemyLocationX3, enemyLocationY3, matrix.Color333(0,0,0));
          if (matrixMap[enemyLocationX3][enemyLocationY3] == 2)
          {
            drawFood(enemyLocationX3,enemyLocationY3);
          }
          enemyLocationX3--;
        }
      }
      if (enemyMap[enemyLocationX3][enemyLocationY3] == 2)
      {
        long randomNumb = random(0,4);//random number between 0-3
        if (randomNumb == 0 ) {enemyDir3 = 0;}
        else if (randomNumb == 1) {enemyDir3 = 1;}
        else if (randomNumb == 2) {enemyDir3 = 2;}
        else if (randomNumb == 3) {enemyDir3 = 3;}
      }
}

void handleEnemyMovement4(){
    if(enemyDir4 == 0) { // enemy up
        if (nextMoveEnemy(enemyLocationX4, enemyLocationY4 - 1))
        {
          matrix.drawPixel(enemyLocationX4, enemyLocationY4, matrix.Color333(0,0,0));
          if (matrixMap[enemyLocationX4][enemyLocationY4] == 2)
          {
            drawFood(enemyLocationX4,enemyLocationY4);
          }
          enemyLocationY4--;
        }
      }
      else if(enemyDir4 == 1) { // enemy right
        if (nextMoveEnemy(enemyLocationX4 + 1, enemyLocationY4))
        {
          matrix.drawPixel(enemyLocationX4, enemyLocationY4, matrix.Color333(0,0,0));
          if (matrixMap[enemyLocationX4][enemyLocationY4] == 2)
          {
            drawFood(enemyLocationX4,enemyLocationY4);
          }
          enemyLocationX4++;
        }
      }
      else if(enemyDir4 == 2) { // enemy down
        if (nextMoveEnemy(enemyLocationX4, enemyLocationY4 + 1))
        {
          matrix.drawPixel(enemyLocationX4, enemyLocationY4, matrix.Color333(0,0,0));
          if (matrixMap[enemyLocationX4][enemyLocationY4] == 2)
          {
            drawFood(enemyLocationX4,enemyLocationY4);
          }
          enemyLocationY4++;
        }
      }
      else if(enemyDir4 == 3) { // enemy left
        if (nextMoveEnemy(enemyLocationX4 - 1, enemyLocationY4))
        {
          matrix.drawPixel(enemyLocationX4, enemyLocationY4, matrix.Color333(0,0,0));
          if (matrixMap[enemyLocationX4][enemyLocationY4] == 2)
          {
            drawFood(enemyLocationX4,enemyLocationY4);
          }
          enemyLocationX4--;
        }
      }
      if (enemyMap[enemyLocationX4][enemyLocationY4] == 2)
      {
        long randomNumb = random(0,4);//random number between 0-3
        if (randomNumb == 0 ) {enemyDir4 = 0;}
        else if (randomNumb == 1) {enemyDir4 = 1;}
        else if (randomNumb == 2) {enemyDir4 = 2;}
        else if (randomNumb == 3) {enemyDir4 = 3;}
      }
}

void handleEnemyKill(){
  if (enemyLocationX == playerLocationX)
  {
    if (enemyLocationY == playerLocationY)
    {
      matrix.fillScreen(matrix.Color333(0, 0, 0));
        gameStarted = false;
    }
  }
  else if (enemyLocationX2 == playerLocationX)
  {
    if (enemyLocationY2 == playerLocationY)
    {
      matrix.fillScreen(matrix.Color333(0, 0, 0));
        gameStarted = false;
    }
  }
  else if (enemyLocationX3 == playerLocationX)
  {
    if (enemyLocationY3 == playerLocationY)
    {
      matrix.fillScreen(matrix.Color333(0, 0, 0));
        gameStarted = false;
    }
  }
  else if (enemyLocationX4 == playerLocationX)
  {
    if (enemyLocationY4 == playerLocationY)
    {
      matrix.fillScreen(matrix.Color333(0, 0, 0));
        gameStarted = false;
    }
  }
  
}

void handleWin(){
  gameStarted = false;
}

void setup() {
  // board setup
    pinMode(2, INPUT); // input left
    pinMode(3, INPUT); // input down
    pinMode(4, INPUT); // input right
    pinMode(5, INPUT); // input up

    Serial.begin(9600);
    
    matrix.begin();
}


void loop() {
  //enemy info
  enemyLocationX = 15;
  enemyLocationY = 29;
  enemyDir = 0;

  enemyLocationX2 = 11;
  enemyLocationY2 = 13;
  enemyDir2 = 2;

    //drawline(x1,y1,x2,y2)
    //drawrect(x1,y1,x2,y2)
    //drawlineH(x1,x2,y)
    //drawlineV(y1,y2,x)
    
    //drawPixel(20,20); //draw pixel
    //drawlineH(3, 10, 7); //horizontal line draw
    //drawlineV(5, 10, 10); //vertical line draw

    //matrix.drawRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(0, 0, 7));
    drawMap1();
    byte menuCycle = 1;
    byte clockCountMenu = 0;
    bool menuDone = false;
    //LED rectangle around the board
    //matrix.drawLine(7, 3, 7, 10, matrix.Color333(7, 0, 7));
    
    delay(1000); //setup time


    while(!menuDone){// in menu

      matrix.setCursor(28,12);
      matrix.setTextSize(.5);
      matrix.setTextWrap(false);
      matrix.setTextColor(matrix.Color333(7,0,7));
      
      
      if (digitalRead(2)== HIGH)//left/scroll left
      {
        if(menuCycle > 0){
          menuCycle= menuCycle - 1;
        }
        if (menuCycle == 0){
          matrix.fillRect(25, 10, 10, 10, matrix.Color333(0, 0, 0));
          matrix.print('Q');
        }
        else if (menuCycle == 1){
          matrix.fillRect(25, 10, 10, 10, matrix.Color333(0, 0, 0));
          matrix.print('E');
        }
        else if (menuCycle == 2){
          matrix.fillRect(25, 10, 10, 10, matrix.Color333(0, 0, 0));
          matrix.print('H');
        }
      }
      if (digitalRead(3)== HIGH)//down/select
      {
        
        if(menuCycle == 0){
          matrix.fillScreen(matrix.Color333(0, 0, 0));
          menuDone = true;
        }
        else if(menuCycle == 1){
          gametype = 0;
          gameStarted = true;
          matrix.fillScreen(matrix.Color333(0, 0, 0));
          menuDone = true;
        }
        else if(menuCycle == 2){
          gametype = 1;
          gameStarted = true;
          matrix.fillScreen(matrix.Color333(0, 0, 0));
          menuDone = true;
        }
      }
      
      if (digitalRead(4) == HIGH)//right/ scroll right
      {
        if (menuCycle < 2)
        {
          menuCycle = menuCycle + 1;
        }
        if (menuCycle == 0){
          matrix.fillRect(25, 10, 10, 10, matrix.Color333(0, 0, 0));
          matrix.print('Q');
        }
        else if (menuCycle == 1){
          matrix.fillRect(25, 10, 10, 10, matrix.Color333(0, 0, 0));
          matrix.print('E');
        }
        else if (menuCycle == 2){
          matrix.fillRect(25, 10, 10, 10, matrix.Color333(0, 0, 0));
          matrix.print('H');
        }
      }
      if (clockCountMenu < 1)
      {
        matrix.print('E');
      }
      
      clockCountMenu++;
      delay(200);
    }
        
    // draw everything
    drawMap1();
    drawMap2();      
    drawPortal1(30,1);
    drawPortal1(31,1);
    drawPortal2(30,30);
    drawPortal2(31,30);
    matrix.drawPixel(playerLocationX, playerLocationY, matrix.Color333(7, 7, 0));

    // enemy setup
    if (gametype == 1)
      {
        enemyLocationX3 = 34;
        enemyLocationY3 = 23;
        enemyDir3 = 1;

        enemyLocationX4 = 50;
        enemyLocationY4 = 1;
        enemyDir4 = 2;
      }
  // game loop 
    while(gameStarted) {
      if(digitalRead(2) == HIGH) { // input left
        if(playerLocationX - 1 > 0 && nextMovePossible(playerLocationX - 1, playerLocationY)) { // is player on the board and is the next move possible?
          matrix.drawPixel(playerLocationX, playerLocationY, matrix.Color333(0, 0, 0)); // remove last placed pixel
          playerLocationX--; // update location left
        }
      }
      else if(digitalRead(3) == HIGH) { // input down
        if(playerLocationY + 1 < 31 && nextMovePossible(playerLocationX, playerLocationY + 1)) { // is player on the board and is the next move possible?
          matrix.drawPixel(playerLocationX, playerLocationY, matrix.Color333(0, 0, 0)); // remove last placed pixel
          playerLocationY++;// update location down
        }
      }
      else if(digitalRead(4) == HIGH) { // input right
        if(playerLocationX + 1 < 61 && nextMovePossible(playerLocationX + 1, playerLocationY)) { // is player on the board and is the next move possible?
          matrix.drawPixel(playerLocationX, playerLocationY, matrix.Color333(0, 0, 0)); // remove last placed pixel
          playerLocationX++;// update location right
        }
      }
      else if(digitalRead(5) == HIGH) { // input up
        if(playerLocationY - 1 > 0 && nextMovePossible(playerLocationX, playerLocationY -1)) { // is player on the board and is the next move possible?
          matrix.drawPixel(playerLocationX, playerLocationY, matrix.Color333(0, 0, 0));// remove last placed pixel
          playerLocationY--; // update location up
        }
      }

      if (isOnFood(playerLocationX, playerLocationY)) { // is player on food?
        matrixMap[playerLocationX][playerLocationY] = 0; // remove food from matrix
        playerFoodCount++; // update food counter
      }
      
      if (matrixMap[playerLocationX][playerLocationY] == 3)
      {
        if(playerLocationX == 30 && playerLocationY == 1){handlePortal(1);}
        else if(playerLocationX == 31 && playerLocationY == 1){handlePortal(3);}

      }
      else if (matrixMap[playerLocationX][playerLocationY] == 4)
      {
        if(playerLocationX == 30 && playerLocationY == 30){handlePortal(2);}
        else if(playerLocationX == 31 && playerLocationY == 30){handlePortal(4);}
      }
      
      matrix.drawPixel(playerLocationX, playerLocationY, matrix.Color333(7, 7, 0)); // draw player
      //enemy handeling
      handleEnemyMovement1();
      handleEnemyMovement2();
      matrix.drawPixel(enemyLocationX, enemyLocationY, matrix.Color333(7,0,0));// draw enemy 1
      matrix.drawPixel(enemyLocationX2, enemyLocationY2, matrix.Color333(7,0,0));// draw enemy 2
      if (gametype == 1)
      {
        handleEnemyMovement3();
        handleEnemyMovement4();
        matrix.drawPixel(enemyLocationX3, enemyLocationY3, matrix.Color333(7,0,0));// draw enemy 3
        matrix.drawPixel(enemyLocationX4, enemyLocationY4, matrix.Color333(7,0,0));// draw enemy 4
      }
      
      drawScoreLine(playerFoodCount);
  
      handleEnemyKill();

      if (clockCount == 50){wave(0);};
      if (playerFoodCount == 5){wave(1);};
      if (playerFoodCount == 10){wave(2);};
      if (playerFoodCount == 15){wave(3);};
      if (playerFoodCount == 20){wave(4);};
      if (playerFoodCount == 25){wave(5);};
      if (playerFoodCount == 30){handleWin();};
      delay(80);
      clockCount++;
    }  
}
