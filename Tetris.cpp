#include "iGraphics.h"
string tetrisDesign[]={"Data\\Tetris_1.txt","Data\\Tetris_2.txt","Data\\Tetris_3.txt","Data\\Tetris_4.txt","Data\\Tetris_5.txt","Data\\Tetris_6.txt","Data\\Tetris_7.txt"};
void Generate();
void CheckBottom();
void CheckLeft();
void CheckRight();
class Block {
public:
	static const int Height = 40, Width = 40, TotalR = 25, TotalC = 19;
};

class Window {
public:
	static const int Height = 1000, Width = 760, X = 1000, Y = 0;
	static constexpr char* Title = "Block";
};

class Color {
public:
	int R, G, B;
	bool Show;
	Color()
	{
		R = G = B = 255;
		Show = false;
	}
} Cube[25][30];



class Structure {
public:
	Color Cube[4][3];
	int R, C;
	int Dir;
	bool Active;
	Structure()
	{
		int a=rand()%256,b=rand()%256,c=rand()%256;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				C = Block::TotalC / 2;
				R = Block::TotalR;

				Cube[i][j].R=a;
				Cube[i][j].G=b;
				Cube[i][j].B=c;
			}
		}
		Cube[1][1].Show = Cube[2][1].Show = true;
		Dir = 0;
		Active = false;
	}
} Tetris;



void iDraw(void)
{
	iClear();
	int i, j;

	if (Tetris.Active)
	{
		iSetTransparentColor(Tetris.Cube[0][0].R,Tetris.Cube[0][0].G,Tetris.Cube[0][0].B, .3);
		iFilledRectangle((Tetris.C)*Block::Width, (Tetris.R)*Block::Height, Block::Width, Block::Height);
		iFilledRectangle((Tetris.C + 1)*Block::Width, (Tetris.R)*Block::Height, Block::Width, Block::Height);
		if (Tetris.Cube[3][1].Show)
			iFilledRectangle((Tetris.C + 2)*Block::Width, Tetris.R * Block::Height, Block::Width, Block::Height);
		if (Tetris.Cube[1][0].Show)
			iFilledRectangle((Tetris.C)*Block::Width, (Tetris.R + 1)*Block::Height, Block::Width, Block::Height);
		if (Tetris.Cube[0][0].Show)
			iFilledRectangle((Tetris.C - 1)*Block::Width, (Tetris.R + 1)*Block::Height, Block::Width, Block::Height);
		if (Tetris.Cube[0][1].Show)
			iFilledRectangle((Tetris.C - 1)*Block::Width, (Tetris.R)*Block::Height, Block::Width, Block::Height);
		if (Tetris.Cube[2][0].Show)
			iFilledRectangle((Tetris.C + 1)*Block::Width, (Tetris.R + 1)*Block::Height, Block::Width, Block::Height);
		if (Tetris.Cube[1][2].Show)
			iFilledRectangle((Tetris.C )*Block::Width, (Tetris.R - 1)*Block::Height, Block::Width, Block::Height);
		if (Tetris.Cube[2][2].Show)
			iFilledRectangle((Tetris.C + 1)*Block::Width, (Tetris.R - 1)*Block::Height, Block::Width, Block::Height);
	}
	else Generate();

	
	for (i = 0; i < Block::TotalC; i++)
	{
		for (j = 0; j < Block::TotalR; j++)
		{
			if (Cube[i][j].Show)
			{
				iSetTransparentColor(Cube[i][j].R,Cube[i][j].G,Cube[i][j].B, .5);
				iFilledRectangle(i * Block::Width, j * Block::Height, Block::Width, Block::Height);
			}
		}
	}

	iSetTransparentColor(255, 255, 255, .2);
	for (i = 0; i < Block::TotalC; i++)
	{
		iLine(Block::Width * i, 0, Block::Width * i, Window::Height);
	}

	for (i = 0; i < Block::TotalR; i++)
	{
		iLine(0, Block::Height * i, Window::Width, Block::Height * i);
	}
}

void iMouseClick(int button, int state, int mx, int my)
{
}

void iMouseDrag(int mx, int my)
{

}

void iMouseMove(int mx, int my)
{

}

void iMouseWheel(int button, int dir, int mx, int my)
{

}

void iKeyboard(unsigned char key)
{

}

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_END) exit(0);
	else if (key == GLUT_KEY_RIGHT)
	{
		if (Tetris.C < Block::TotalC - 1)
		{
			Tetris.C++;
		}
	}
	else if (key == GLUT_KEY_LEFT)
	{
		if (Tetris.C > 0)
		{
			Tetris.C--;
		}
	}
	// else if(key == GLUT_KEY_UP)
	// {
	// 	if(Tetris.R<Block::TotalR-1)
	// 	{
	// 		Tetris.R++;
	// 	}
	// }
	else if (key == GLUT_KEY_DOWN)
	{
		if (Tetris.R > 0)
		{
			CheckBottom();
			Tetris.R--;
		}
	}
}

void Generate()
{
	Structure Temp;
	Tetris = Temp;
	Tetris.Active = true;
	int Count = 0;

	while (Count < 2)
	{
		if (rand() % 2)
		{
			Tetris.Cube[1][0].Show = true;
			Count++;
			if (rand() % 2)
			{
				Tetris.Cube[0][0].Show = true;
				Count++;
				if (Count == 2) return;
			}
			if (rand() % 2)
			{
				Tetris.Cube[0][1].Show = true;
				Count++;
				if (Count == 2) return;
			}
			if (rand() % 2)
			{
				Tetris.Cube[1][2].Show = true;
				Count++;
				if (Count == 2) return;
			}
			Tetris.Cube[2][0].Show = true;
			Count++; if (Count == 2) return;
		}

		else if (rand() % 2)
		{
			Tetris.Cube[0][1].Show = true;
			Count++;
			if (Count == 2) return;
			if (rand() % 2)
			{
				Tetris.Cube[0][0].Show = true;
				Count++;
				if (Count == 2) return;
			}
			if (rand() % 2)
			{
				Tetris.Cube[1][0].Show = true;
				Count++;
				if (Count == 2) return;
			}
			if (rand() % 2)
			{
				Tetris.Cube[2][2].Show = true;
				Count++;
				if (Count == 2) return;
			}
			Tetris.Cube[3][1].Show = true;
			Count++; if (Count == 2) return;
		}
	}
	Tetris.Dir = rand() % 5;
}

void Fix()
{
	Tetris.Active = false;
	Cube[Tetris.C][Tetris.R].Show = true,Cube[Tetris.C][Tetris.R].R=Tetris.Cube[0][0].R, Cube[Tetris.C][Tetris.R].G=Tetris.Cube[0][0].G, Cube[Tetris.C][Tetris.R].B=Tetris.Cube[0][0].B;

	Cube[Tetris.C + 1][Tetris.R].Show = true,Cube[Tetris.C + 1][Tetris.R].R=Tetris.Cube[0][0].R, Cube[Tetris.C + 1][Tetris.R].G=Tetris.Cube[0][0].G,Cube[Tetris.C + 1][Tetris.R].B=Tetris.Cube[0][0].B;
	if (Tetris.Cube[3][1].Show)	Cube[Tetris.C + 2][Tetris.R].Show = true , Cube[Tetris.C + 2][Tetris.R].R=Tetris.Cube[0][0].R, Cube[Tetris.C + 2][Tetris.R].G=Tetris.Cube[0][0].G, Cube[Tetris.C + 2][Tetris.R].B=Tetris.Cube[0][0].B;

	if (Tetris.Cube[1][0].Show)	Cube[Tetris.C][Tetris.R + 1].Show = true,Cube[Tetris.C][Tetris.R + 1].R=Tetris.Cube[0][0].R, Cube[Tetris.C][Tetris.R + 1].G=Tetris.Cube[0][0].G, Cube[Tetris.C][Tetris.R + 1].B=Tetris.Cube[0][0].B;

	if (Tetris.Cube[0][0].Show)	Cube[Tetris.C - 1][Tetris.R + 1].Show = true,Cube[Tetris.C - 1][Tetris.R + 1].R=Tetris.Cube[0][0].R, Cube[Tetris.C - 1][Tetris.R + 1].G=Tetris.Cube[0][0].G, Cube[Tetris.C - 1][Tetris.R + 1].B=Tetris.Cube[0][0].B;
	if (Tetris.Cube[0][1].Show)	Cube[Tetris.C - 1][Tetris.R].Show = true,Cube[Tetris.C - 1][Tetris.R].R=Tetris.Cube[0][0].R, Cube[Tetris.C - 1][Tetris.R].G=Tetris.Cube[0][0].G, Cube[Tetris.C - 1][Tetris.R].B=Tetris.Cube[0][0].B;

	if (Tetris.Cube[2][0].Show)	Cube[Tetris.C + 1][Tetris.R + 1].Show = true,Cube[Tetris.C + 1][Tetris.R + 1].R=Tetris.Cube[0][0].R, Cube[Tetris.C + 1][Tetris.R + 1].G=Tetris.Cube[0][0].G, Cube[Tetris.C + 1][Tetris.R + 1].B=Tetris.Cube[0][0].B;

	if (Tetris.Cube[1][2].Show)	Cube[Tetris.C ][Tetris.R - 1].Show = true,Cube[Tetris.C ][Tetris.R - 1].R=Tetris.Cube[0][0].R, Cube[Tetris.C ][Tetris.R - 1].G=Tetris.Cube[0][0].G, Cube[Tetris.C ][Tetris.R - 1].B=Tetris.Cube[0][0].B;

	if (Tetris.Cube[2][2].Show)	Cube[Tetris.C + 1][Tetris.R - 1].Show = true,Cube[Tetris.C + 1][Tetris.R - 1].R=Tetris.Cube[0][0].R, Cube[Tetris.C + 1][Tetris.R - 1].G=Tetris.Cube[0][0].G, Cube[Tetris.C + 1][Tetris.R - 1].B=Tetris.Cube[0][0].B;


}

void CheckBottom()
{
	if (Cube[Tetris.C][Tetris.R - 1].Show)   Fix();
	else if (Cube[Tetris.C + 1][Tetris.R - 1].Show)   Fix();
	else if (Tetris.Cube[3][1].Show && Cube[Tetris.C + 2][Tetris.R - 1].Show)	Fix();
	else if (Tetris.Cube[1][0].Show && Cube[Tetris.C][Tetris.R].Show)	Fix();
	else if (Tetris.Cube[0][0].Show && Cube[Tetris.C - 1][Tetris.R].Show)	  Fix();
	else if (Tetris.Cube[0][1].Show && Cube[Tetris.C - 1][Tetris.R - 1].Show)	Fix();
	else if (Tetris.Cube[2][0].Show && Cube[Tetris.C + 1][Tetris.R].Show)   Fix();
	else if (Tetris.Cube[1][2].Show && Cube[Tetris.C][Tetris.R-2].Show)   Fix();
	else if (Tetris.Cube[2][2].Show && Cube[Tetris.C + 1][Tetris.R-2].Show)   Fix();
}
void Fall()
{
	if (!Tetris.R)
	{
		Fix();
		return;
	}

	CheckBottom();

	Tetris.R--;
}

void Match()
{
	int i, j;
	for (i = 0; i < Block::TotalR; i++)
	{
		for (j = 0; j < Block::TotalC; j++)
		{
			if (!Cube[j][i].Show) break;
		}
		if (j == Block::TotalC)
		{
			for(int k = i; k < Block::TotalR; k++)
			{
				for (int l = 0; l < Block::TotalC; l++)
				{
					Cube[l][k].Show=Cube[l][k+1].Show;
				}
			}
			i--;
		}
	}
}
int main(int argc, char *argv[])
{
	srand(time(NULL));
	iSetTimer(300, Fall);
	iSetTimer(0, Match);
	glutInit(&argc, argv);
	iInitialize(Window::Width, Window::Height, Window::Title, Window::X, Window::Y);
	// glutFullScreen();
	glutMainLoop();
}
