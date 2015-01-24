#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>
#include <math.h>
//#include "color.h"

#define WIDTH  400
#define HEIGHT 240
#define SCREEN WIDTH*HEIGHT
///////////////////////////////////////////////////////////////////////////////
/*int current [WIDTH][HEIGHT];
int next [WIDTH][HEIGHT];
int alive_counts [WIDTH][HEIGHT];
int tmp[WIDTH][HEIGHT];

int ALIVE = 3;
int DEATH_1 = 2;
int DEAD = 0;

int cex,cey,nx,ny,col;

void StarWars(){// Star-Wars Cellular Automata //

	u8* fb6 = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	step();
	memset(fb6, 0, SCREEN * 3);

	draw_type(50,100, 100,100,100, 155);
	draw_type(2,49, 255,255,50, 100);
	draw_type(0,1, 100,100,255, 255);

	gfxFlushBuffers();
	gfxSwapBuffers();

}

void rndrule() {

	for (cex = 0; cex < WIDTH; cex++) {
		for (cey = 0; cey < HEIGHT; cey++) {

			current[cex][cey] = rand() % 5;
			alive_counts[cex][cey] = 0;

		}
	}
}

void symrule() {

	for (cex = 0; cex < WIDTH; cex++) {
		for (cey = 0; cey < HEIGHT; cey++) {

			current[cex][cey] = 0;
			alive_counts[cex][cey] = 0;

		}
	}

	current[199][120] = 3;
	current[200][120] = 3;
}

void step() {

	for (cex = 0; cex < WIDTH; cex++) {
		for (cey = 0; cey < HEIGHT; cey++) {

			int count = 0;
			int next_val;

			int mx = WIDTH-1;
			int my = HEIGHT-1;

			int self = current[cex][cey];

			for (nx = cex-1; nx <= cex+1; nx++) {
				for (ny = y-1; ny <= cey+1; ny++) {

					if (nx == cex && ny == cey) continue;
					if (current[wrap(nx, mx)][wrap(ny, my)] == ALIVE) count++;

				}
			}

			int neighbors = count;

			if (self == ALIVE) next_val = ((neighbors == 3) || (neighbors == 4) || (neighbors == 5)) ? ALIVE : DEATH_1;
			else if (self == DEAD) next_val = (neighbors == 2) ? ALIVE : DEAD;
			else next_val = self-1;

			next[cex][cey] = next_val;

			if (next_val == ALIVE) {
				if ((alive_counts[cex][cey]+1) <= 100) alive_counts[cex][cey] = (int)(alive_counts[cex][cey]+1);}
					else if (next_val == DEAD) alive_counts[cex][cey] = 0;
		}
	}

	for (cex = 0; cex < WIDTH; cex++) {
		for (cey = 0; cey < HEIGHT; cey++) {

			tmp[cex][cey] = current[cex][cey];
			current[cex][cey] = next[cex][cey];
			next[cex][cey] = tmp[cex][cey];

		}
	}
}

int wrap(int v, int m) {
	if (v < 0) return v + m;
	else if (v >= m) return v - m;
	else return v;
}


void draw_type(int min_alive, int max_alive, int r, int g, int b, int s) {

	for (cex = 0; cex < WIDTH; cex++) {
		for (cey = 0; cey < HEIGHT; cey++) {

			int self = current[cex][cey];

			if (self == DEAD) continue;

			int alive = alive_counts[cex][cey];

			if (alive < min_alive || alive > max_alive) continue;

			u8* fb6 = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);

			fb6[3*((cey)+(cex)*240)]   = s;
			fb6[3*((cey)+(cex)*240)+1] = s<<1;
			fb6[3*((cey)+(cex)*240)+2] = s<<2;

		}
	}

}*/
///////////////////////////////////////////////////////////////////////////////
float tex = -0.086f;
float tey = 0.85f;
float zoom = 1.0f;
void Mandelbrot(float x1, float y1, float x2, float y2);
void Mandelbrot(float x1, float y1, float x2, float y2) {// Mandelbrot Fractal Zoomer //

	unsigned int i,j;
	uint16_t iter;

	float sy = y2 - y1;
	float sx = x2 - x1;
	const int MAX = 512;


	for(i = 0; i < WIDTH; i++) {
		for(j = 0; j < HEIGHT; j++) {
			float cy = j * sy / HEIGHT + y1;
			float cx = i * sx / WIDTH + x1;
			float tex=0.0f, tey=0.0f, xx=0.0f, yy=0.0f;
			for(iter=0; iter <= MAX && xx+yy<4.0f; iter++) {
				xx = tex*tex;
				yy = tey*tey;
				tey = 2.0f*tex*tey + cy;
				tex = xx - yy + cx;
			}

			u8* fb5 = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);

			fb5[3*((j)+(i)*240)]   = iter << 1;
			fb5[3*((j)+(i)*240)+1] = iter << 2;
			fb5[3*((j)+(i)*240)+2] = iter << 3;

		}
	}
}
///////////////////////////////////////////////////////////////////////////////
#define width  WIDTH/2
#define height HEIGHT/2
float ayy [width][height][2];
float bee [width][height][2];
float cee [width][height][2];

int p = 0, q = 1;
int zex,yey,id,jay,lay;

void BZReaction(){// Belousov-Zabotinsky Reaction //
	u8* fb4 = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	//memset(fb, 0, SCREEN * 3);
	for (yey = 0; yey < height; yey++) {
		for (zex = 0; zex < width; zex++) {

			float c_a = 0;
			float c_b = 0;
			float c_c = 0;

			for (id = zex - 1; id <= zex+1; id++) {
				for (jay = yey - 1; jay <= yey+1; jay++) {

					c_a += ayy[(id+width)%width][(jay+height)%height][p];
					c_b += bee[(id+width)%width][(jay+height)%height][p];
					c_c += cee[(id+width)%width][(jay+height)%height][p];
				}
			}

			c_a /= 9.0;
			c_b /= 9.0;
			c_c /= 9.0;

			if (c_a + c_a * (c_b - c_c) <= 1) ayy[zex][yey][q] = c_a + c_a * (c_b - c_c);
			if (c_b + c_b * (c_c - c_a) <= 1) bee[zex][yey][q] = c_b + c_b * (c_c - c_a);
			if (c_c + c_c * (c_a - c_b) <= 1) cee[zex][yey][q] = c_c + c_c * (c_a - c_b);

			lay = 256*ayy[zex][yey][q];

			fb4[3*((2*yey)+(2*zex)*240)]   = lay;
			fb4[3*((2*yey)+(2*zex)*240)+1] = lay;
			fb4[3*((2*yey)+(2*zex)*240)+2] = lay;

		}
	}

	if (p == 0) { p = 1; q = 0; } else { p = 0; q = 1; }

	gfxFlushBuffers();
	gfxSwapBuffers();

}

///////////////////////////////////////////////////////////////////////////////
float a = 0.4;
float b = 0.9;
float rex = 1.5;
float sy = 1.5;

int colo,si;
int xx,yy;

void Hoopa(){// Hopalong Orbit Fractal //
	u8* fb3 = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	//memset(fb, 0, SCREEN * 3);

	colo = rand()%256;

	for (si=0;si<5000;si++) {

		float oldx = rex;

		rex = sy-(oldx)*sqrt(fabs(b*oldx));
		sy = a-oldx;

		xx = 205+(85*rex);
		yy = 98+(50*sy);

		if ((xx>=0)&(xx<=399)&(yy>=0)&(yy<=239)) {

			fb3[3*(yy+xx*240)]   = colo;
			fb3[3*(yy+xx*240)+1] = colo<<1;
			fb3[3*(yy+xx*240)+2] = colo<<2;

		}
	}

	gfxFlushBuffers();
	gfxSwapBuffers();
}

///////////////////////////////////////////////////////////////////////////////
int nex,yii,dex;
char kray;

void XORFractals(){// XOR Fractals //
	u8* fb2 = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	memset(fb2, 0, SCREEN * 3);


	for (yii=0;yii<HEIGHT;yii++) {
		for (nex=0;nex<WIDTH;nex++) {

			kray = (((nex+dex)^yii) % (nex^(yii+dex))) + dex;

			fb2[3*(yii+nex*240)]   = kray;
			fb2[3*(yii+nex*240)+1] = kray<<1;
			fb2[3*(yii+nex*240)+2] = kray<<2;

		}
	}

	dex++;
	// Flush and swap framebuffers
	gfxFlushBuffers();
	gfxSwapBuffers();
}

///////////////////////////////////////////////////////////////////////////////
int x,y,d,i;
bool k;
int state[WIDTH];

void Cell(){// Simple 1D Cellular Automata //
	u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	memset(fb, 0, SCREEN * 3);
	for (y=0;y<HEIGHT;y++) {
		for (x=0;x<WIDTH;x++) {
			k = k^state[x];
			state[x] = k;
			if (k == 1)  d = 255;
			else d = 0;
			fb[3*(y+x*240)]   = d;
			fb[3*(y+x*240)+1] = d;
			fb[3*(y+x*240)+2] = d;

		}
	}
	i = 30;
	while(i--) gspWaitForVBlank();
	gfxFlushBuffers();
	gfxSwapBuffers();

}
///////////////////////////////////////////////////////////////////////////////
int ex,why,dee;
char kay;

void mSquares(){//Munching Squares!//
		// Example rendering code that displays a white pixel
	// Please note that the 3DS screens are sideways (thus 240x400 and 240x320)
	u8* fb1 = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	memset(fb1, 0, SCREEN * 3);

	for (why=0;why<HEIGHT;why++) {
		for (ex=0;ex<WIDTH;ex++) {

			kay = ((ex^why)&255)+dee;

			fb1[3*(why+ex*240)]   = kay;
			fb1[3*(why+ex*240)+1] = kay<<1;
			fb1[3*(why+ex*240)+2] = kay<<2;

		}
	}
	dee++;
	// Flush and swap framebuffers
	gfxFlushBuffers();
	gfxSwapBuffers();
}
///////////////////////////////////////////////////////////////////////////////
int main(){
	// サービス初期化子
	srvInit();
	aptInit();
	gfxInitDefault();
	consoleInit(GFX_BOTTOM, NULL);
	hidInit(NULL);
	//gfxSet3D(true); // 立体鏡3D
	//SET_COLOR(X);
	printf("Hello World\n");
	printf("Hold A, B, R, L, X, or Y\n");
	printf("Press Start to exit");
	//Flushes the buffer
	gfxFlushBuffers();
	gfxSwapBuffers();

	/*if(hidKeysDown() & KEY_L){//STARWARS STUFF
		srand(svcGetSystemTick());
		rndrule();
	}*/

	while(aptMainLoop()){ //メインループ

		hidScanInput(); //どのボタンを押せる
		u32 button = hidKeysDown(); // Checks which keys are up and which ones are down

		if(button & KEY_START) break; //Start押すならメニューに戻る
		//if(button & KEY_SELECT) { gfxFlushBuffers(); gfxSwapBuffers(); }
		if(button & KEY_X){
			int one2 = 0;
			one2++;
			if(one2 == 1){
				Mandelbrot(-2.0f*zoom+tex, -1.5f*(0.8*zoom)+tey, 2.0f*zoom+tex, 1.5f*(0.8*zoom)+tey);
				zoom *= 0.7f;
				if(zoom <= 0.000003f) zoom = 1.0f;}
			else{printf("Restart and try again");}}
		/*if(button & KEY_DRIGHT){
			if (hidKeysDown() & KEY_A) rndrule();
			if (hidKeysDown() & KEY_B) symrule();
			StarWars();
		}*/
		if(button & KEY_A){
		int one = 0;
		one++;
		if(one == 1){
			for (i=0;i<WIDTH;i++) state[i] = rand()%2;
			Cell();
		}else{printf("Restart and try again...");}}
		if(button & KEY_R){mSquares();}
		if(button & KEY_Y){XORFractals();}
		if(button & KEY_B){Hoopa();}
		if(button & KEY_L){
			int one3 = 0;
			one3++;
			if(one3 == 1){
				for (yey = 0; yey < height; yey++) {
					for (zex = 0; zex < width; zex++) {
						ayy[zex][yey][p] = (rand()%10/10.0);
						bee[zex][yey][p] = (rand()%10/10.0);
						cee[zex][yey][p] = (rand()%10/10.0);
					}
				}
				BZReaction();
			}
			else{printf("Restart and try again...");}
			}
	}

	// サービス終了する
	aptExit();
	gfxExit();
	hidExit();
	srvExit();
	return 0;
}
