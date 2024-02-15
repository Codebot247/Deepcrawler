#include <STDIO.h>
#include <STDLIB.h>
#include <time.h>
#include <conio.h>
#include <dos.h>


#define BOOL int
#define TRUE 1
#define FALSE 0


#define ITERATIONS 15
#define MAP_X 20
#define MAP_Y 20

/* Level generation and positional variables */
int level = 1; 
BOOL MAP [MAP_X][MAP_Y];
BOOL MAP_PREV [MAP_X][MAP_Y];
int ENCOUNTERS [MAP_X][MAP_Y];
BOOL isExit = FALSE;

int playerX; int playerY;
int prevX; int prevY;

/*int topTrend, leftTrend, rightTrend, bottomTrend;*/     /* UNUSED */


/* ------------------------------------------------------ */


/* Misc variables */
int i, j, x;

void clearScreen(BOOL clearMap, BOOL clearAll, BOOL clearCombat){	
	if(clearMap == TRUE){
		for(j = 0; j != MAP_Y; j++){
			gotoxy(35,j+1);
			cprintf("               ");
		}
	}
	
	textcolor(7);
	textbackground(0);
	
	if(clearAll == TRUE){
		for(j = 1; j != 27; j++){
			gotoxy(1,j);
			cprintf("                                                                 ");
		}
	}
	
	if(clearCombat == TRUE){
		for(j = 1; j != 7; j++){
			gotoxy(1,j);
			cprintf("                                                                                ");
		}
	}
	
	
	gotoxy(1,1);
}

void drawMap(int redrawMode){
	if (redrawMode == 0){
		clearScreen(0,1,0);
		/* Draw the map */
		for( i = 0; i != MAP_X; i++){
		  for (j = 0; j != MAP_Y; j++){
			  gotoxy(i+35,j+1);
			  
			  if(ENCOUNTERS[i][j] == 1){
				textcolor(6);
				textbackground(0);
				cprintf("<");
			  }
			  
			  if(ENCOUNTERS[i][j] == 3){
				textcolor(14);
				textbackground(0);
				cprintf("$");
			  }
			  
			  if(i == playerX && j == playerY){
				textcolor(15);
				textbackground(0);
				cprintf("\1");
			  }
			  
			  if (MAP[i][j] == TRUE){
				if (i != playerX || j != playerY){
					textcolor(0);
					textbackground(6);
					cprintf("%c", 176);
				}
			  }
			  
			  if (MAP[i][j] == FALSE){
				 textcolor(8);
				 textbackground(7);
				 cprintf("%c", 219);
			  }
		  }
		  printf("\n");
		}
	}
	
	else if (redrawMode == 1){
		gotoxy(playerX + 35,playerY + 1);
		textcolor(15);
		textbackground(0);
		cprintf("\1");
		
		
		gotoxy(prevX + 35,prevY + 1);
		if(ENCOUNTERS[prevX][prevY] == 1){
		 textcolor(6);
		 textbackground(0);
		 cprintf("<");
	    }
	  
	    if(ENCOUNTERS[prevX][prevY] == 3){
		  textcolor(14);
		  textbackground(0);
		  cprintf("$");
	    }

	    if (MAP[prevX][prevY] == TRUE){
			textcolor(0);
			textbackground(6);
			cprintf("%c", 176);
	    }
	  
	    if (MAP[prevX][prevY] == FALSE){
			textcolor(8);
			textbackground(7);
			cprintf("%c", 219);
	    }
		printf("\n");
	}
}


void musicFunc(int track){
	if( track == 1){
		sound(500); delay(200);
			
		sound(700); delay(200);
		
		sound(1000); delay(200);
				
		sound(1300); delay(200);
		 
		sound(500); delay(200);
		 
		sound(1300); delay(200);
		
		nosound();
	}
	
	/* Level up song */
	else if( track == 2 ){
		sound(1000); delay(200);	
				
		sound(1200); delay(400);
				
		sound(2000); delay(600);
		nosound();
	}
}

int main(){
	
 /* Player Variables */
 int hp = 100;
 int hpMax = 100;
 
 int ep = 100;
 int epMax = 100;
 
 int xp = 0;
 int xpLimit = 100;
 int playerLevel = 1;
 
 int playerStrength = 5; /* Determines attack damage */
 int playerDexterity = 2; /* Determines dodge */
 int playerFortitude = 5; /* Determines HP */
 int playerLuck = 5; /* Slight impact on everything */
 int playerRecovery = 5; /* HP recovery per turn */
 
 int healthRecovery = (playerRecovery * 1.5);
 int baseDamage = 5;
 
 int score = 0;
 /* ----------------------------------------------------------- */
 
 
 
 /* Enemy Variables */
 
 int enemyHealth;
 int enemyHealthMax;
 int enemyBaseDamage;
 
 char monsterName[70];
 
 
 /* Stats are stored as HP, ATTACK
 * 1 = Decaying Skeleton
 * 0 = Giant Spider */
 
 int enemyStats[2][2] = { {65,10},{35,30} };
 
 
 
  /* Monster Names
   * 0 = Decaying Skeleton
   * 1 = Giant Spider */
 char enemyNames[2][70] = { {"Decaying Skeleton"}, {"Giant Spider"}};
 
 
 /* -------------------------------------------------------- */
 
 

 
 
 /* Game state variables */
 BOOL gameState = TRUE; 
 BOOL isCombat = FALSE;
 BOOL gameStart = TRUE;
 int counter = 0;
  
 char userInput[100];
 int randInt; int randInt2; int randEnemy;
  /* ---------------------------------------------------- */
  
 clearScreen(0,1,0);
 

 musicFunc(1);
 
 textbackground(4);
 textcolor(4);
 
 for (i = 0; i != 70; i++){
	for (j = 0; j != 25; j++){
		gotoxy(i, j);
		putch(1);
	}
 }
 
 textbackground(0);
 textcolor(15);
 
 gotoxy(20,5);
 cprintf("DeepCrawler");
 gotoxy(15,8);
 cprintf("Press ENTER to begin...");
 
 getch();
 
 
 
 
 system("cls");
 
 /* Main game loop */ 
 while(gameState){
	 
	 
	 
	 /* Check and set player stats, level up, etc */
	 
	 if (xp >= xpLimit){
		playerLevel++;
		clearScreen(0,1,0);
		musicFunc(2);
		printf("YOU HAVE LEVELED UP!\n");
		printf("THIS IS CURRENTLY A PLACEHOLDER, STAY TUNED FOR MORE!\n");
		sleep(3);
		xp = xp - xpLimit;
		xpLimit = (xpLimit * 1.5);
		drawMap(0);
	 }
	 
	 hpMax = (100 + (playerFortitude*3));
	 hp += (playerRecovery*1.5);
	 if(hp > hpMax){
		hp = hpMax;
	 }
	 
	counter++;
	
	
	
	
   /* If the player encounters a staircase, move them to the next level */ 
  if(ENCOUNTERS[playerX][playerY] == 1 || counter == 1){
	 
	 /* Play the moving down sound */
	 sound(400);
	 delay(200);
	
	 sound(500);
	 delay(400);
	
	 sound(400);
	 delay(200);
	
	 nosound();
	 
	 
	 
	 
	 isExit = FALSE;
	 level++;
	 
	  for (i = 0; i != MAP_X; i++){
		  for(j = 0; j != MAP_Y; j++){
			  if (MAP[i][j] != MAP_PREV[i][j]){
				MAP_PREV[i][j] = MAP[i][j];
			  }
		  }
	  }

	/* Sets the MAP and ENCOUNTERS tables to be equal to zero */
	 for( i = 0; i != MAP_X; i++){
		  for (j = 0; j != MAP_Y; j++){
			 MAP[i][j] = FALSE;
			 ENCOUNTERS[i][j] = 0;
		  }
	 }
	  
	  
	 randInt = rand() % MAP_X;
	 randInt2 = rand() % MAP_Y;
	 MAP[randInt][randInt2] = TRUE; 
	 prevX = playerX = randInt;  prevY = playerY = randInt2;
	 
	 for ( x = 0; x != ITERATIONS; x++){
	  for( i = 0; i != MAP_X; i++){
		  for (j = 0; j != MAP_Y; j++){
			if (MAP[i][j] == TRUE){
				randInt = rand() % 100;
				if(randInt > 0 && randInt < 25){
					if(i-1 != -1){
						MAP[i-1][j] = TRUE;
					}
				}
				if(randInt > 24 && randInt < 50){
					if(i+1 != MAP_X){
						MAP[i+1][j] = TRUE;
					}
				}
				if(randInt > 49 && randInt < 75){
					if(j-1 != -1){
						MAP[i][j-1] = TRUE;
					}
				}
				if(randInt > 74){
					if(j+1 != MAP_Y){
						MAP[i][j+1] = TRUE;
					}
				}
			}
		  }
		}
	}
	
	/* Picks an empty spot in the MAP to create an exit staircase, leading further down */
	while (!isExit){
		  for (i = 0; i != MAP_X; i++){
			  for(j = 0; j != MAP_Y; j++){
				  if(MAP[i][j] == TRUE){
					randInt = rand() % 10;
					if (randInt > 7 && isExit == FALSE){
						ENCOUNTERS[i][j] = 1;
						isExit = TRUE;
						break;
					}
				  }
			  }
		  }
	 }	
	 
	 
	 for(i = 1; i != MAP_X-1; i++){
		for(j = 1; j != MAP_Y-1; j++){
			randInt = rand() % 100;
			if (randInt > 95 && MAP[i][j] == TRUE){
				if (ENCOUNTERS[i][j] != 1){
					ENCOUNTERS[i][j] = 3;
				}
			}
		}
	 }
	 drawMap(0);
  }
  
  
  /* --------------------------------------------------------------- */
  
  /* If the player encounters loot, remove it from the encounters array and add score to the player */ 
  gotoxy(1,5);
  printf("                             \n                         ");
 
 if(ENCOUNTERS[playerX][playerY] == 3){
	randInt = rand() % 100;
	
	sound(1500);
	delay(150);
	sound(2000);
	delay(150);
	nosound();
	
	nosound();
	if (randInt < 80 - (playerLuck*2)){
		score += 100;
		ENCOUNTERS[playerX][playerY] = 0;
	}
	else{
		gotoxy(1,5);
		printf("You got lucky and found extra\ngold!");
		score += 250;
		ENCOUNTERS[playerX][playerY] = 0;
	}
  }
   /* --------------------------------------------------------------- */
  
  
  randInt = rand() % 100;
  if(randInt > 95){
	isCombat = TRUE;
  }

  if(isCombat){ 
	clearScreen(0,1,0);
	
	randEnemy = rand() % 2;
	
	enemyHealth  = (enemyStats[randEnemy][0] + (-10 + rand() % 20) );
	enemyHealthMax = enemyHealth;
	
	
	enemyBaseDamage = (enemyStats[randEnemy][1] + rand() % 10);
	
	
	printf("You're attacked by the %s!", enemyNames[randEnemy]);
	/* Play the moving down sound */
	sound(500);
	delay(400);
	
	sound(350);
	delay(400);
	
	sound(20);
	delay(300);
	nosound();
	
	
	sleep(1);
	
	clearScreen(0,1,0);
  }
  
  while(isCombat){
	  clearScreen(0,0,1);
	  printf("HP [%d / %d]\n", hp, hpMax);
	  printf("Enemy HP [%d / %d]\n", enemyHealth, enemyHealthMax);
	  printf("[1] Attack\n");
	  printf("Enter command: ");
	  scanf("%s", userInput);
	  
	  if(!strcmp((userInput), "1")){
		randInt = rand() % ( 2 * playerLuck);
		textcolor(2);
		textbackground(0);
		gotoxy(1,5);
		cprintf("You strike the %s for %d  damage!\n", enemyNames[randEnemy], ( (  (baseDamage + randInt) * ( playerStrength  / 2))  )     ); 
		enemyHealth -= ((baseDamage + randInt) * ( playerStrength  / 2));
		sound(1400);
		delay(200);
		nosound();
		sleep(1);
	  }
	  
	  if (enemyHealth <= 0){
		textcolor(14);
		textbackground(0);
		
		gotoxy(1,6); cprintf("SUCCESS! YOU HAVE DEFEATED THE %s", enemyNames[randEnemy]); 
		gotoxy(1,7); cprintf("+%d GOLD!     +%d XP!", 500, 25);
		
		sound(500);
		delay(200);
		
		sound(700);
		delay(200);
		
		sound(1000);
		delay(200);
		
		sound(1300);
		delay(200);
		
		nosound();
		
		
		
		isCombat = FALSE;
		score += 500;
		xp += 25;
		sleep(2);
		drawMap(0);
		break;
	  }
	 
	  /* Being attacked by the enemy */ 
	  randInt = rand() % 100;
	  if (randInt > 30 + ((playerLuck/2) + playerDexterity)){
		  randInt = rand() % (15 - playerLuck);
		  textcolor(4);
		  textbackground(0);
		  gotoxy(1,6);
		  cprintf("The %s attacks you, dealing %d damage!\n", enemyNames[randEnemy] , (enemyBaseDamage + randInt) );
		  hp -= enemyBaseDamage + randInt;
		  sound(500);
		  delay(200);
		  nosound();
		  sleep(1);
	  }
	  /* Dexterity based auto-dodge chance to any attack */ 
	  else{
		textcolor(2);
		textbackground(0);
		gotoxy(1,6);
		cprintf("You successfully dodge the enemy attack!\n");
		sleep(1);
	  }
	  
	  /* GAME OVER! Killed by the enemy */ 
	  if (hp <= 0){
		  clearScreen(0,1,0);
		  textcolor(0);
		  textbackground(4);
		  gotoxy(1,1);
		  cprintf("Your adventure has come to an end! You've been defeated by the %s\n\n", enemyNames[randEnemy]); gotoxy(1,3);
		  cprintf("Your final score was: %d\n", score); gotoxy(1,4);
		  cprintf("You managed to reach the depth of: %d", level); gotoxy(1,7);
		  
		  cprintf("-- THANKS FOR PLAYING! Press Enter to Exit --");
		  getch();
		  
		  return 0;
	  }
	  
	  
	  
	  
	  
  }
  
  
  gotoxy(1,1);
  printf("Health [%d / %d]\n", hp, hpMax);
  printf("Energy [%d / %d]\n", ep, epMax);
  printf("Level [%d] [%d / %d]\n", playerLevel, xp, xpLimit);
  
  
  
	  
  
  gotoxy(35,MAP_Y+2);
  printf("Floor: %d", level);
  gotoxy(35,MAP_Y+3);
  printf("Score: %d", score);
  gotoxy(35,MAP_Y+4);
  printf("Turns taken: %d", counter);
  
  gotoxy(1,14);
  printf("                               ");
  
  /*
  gotoxy(1,15);
  printf("                                                            ");
  
  
  gotoxy(1,15);
  printf("X1, %d, Y1: %d,   X2: %d, Y2: %d \n", playerX, playerY, prevX, prevY);*/
  
  
  gotoxy(1,14);
  printf("Enter command: ");
  
  userInput[0] = getch();     
  
  if (userInput[0] == 'q'){
	clearScreen(0,1,0);
	printf("Are you sure? (y/n): ");
	userInput[0] = getch();   
	if (userInput[0] == 'y'){
		break;
		return 0;
	}
	clearScreen(0,1,0);
  }
  
  
  
  
  /* The following controls the user ability to move north, east, 
   * south, and west. It first checks for the user input and then
   * it determines if the direction would go over the array size, 
   * and if not it then checks if the position is a valid tile.
   * if all conditions are met, the player moves. */
  prevX = playerX;
  prevY = playerY;
  /* Move North */
  if (userInput[0] == 'w'){
	 if (playerY - 1 != -1){
		 if(MAP[playerX][playerY - 1] == TRUE){
			 playerY--;
			 sound(2000);
			 delay(20);
			 nosound();
		 }
	 }
  }
  
  /* Move East */
  if (userInput[0] == 'd'){
	 if (playerX + 1 != MAP_X){
		 if(MAP[playerX + 1][playerY] == TRUE){
			 playerX++;
			 sound(2000);
			 delay(20);
			 nosound();
		 }
	 }
  }
  
  /* Move South */
  if (userInput[0] == 's'){
	 if (playerY + 1 != MAP_Y){
		 if(MAP[playerX][playerY + 1] == TRUE){
			 playerY++;
			 sound(2000);
			 delay(20);
			 nosound();
		 }
	 }
  }
  
  /* Move West */
  if (userInput[0] == 'a'){
	 if (playerX - 1 != -1){
		 if(MAP[playerX - 1][playerY] == TRUE){
			 playerX--;
			 sound(2000);
			 delay(20);
			 nosound();
		 }
	 }
  }
  if (prevY != playerY || prevX != playerX){
	drawMap(1);
  }
 }
}