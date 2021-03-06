#include "iGraphics.h"
#include <fstream>
string tetrisDesign[] = {
	"Data\\Tetris_1.txt",
	"Data\\Tetris_2.txt",
	"Data\\Tetris_3.txt",
	"Data\\Tetris_4.txt",
	"Data\\Tetris_5.txt",
	"Data\\Tetris_6.txt",
	"Data\\Tetris_7.txt"
};

int Score=0;
void Generate();
bool CheckBottom();
bool CheckLeft();
bool CheckRight();
class Block {
public:
	static const int Height = 40, Width = 40, TotalR = 20, TotalC = 10;
};

class Window {
public:
	static const int Height = 850, Width = 400, X = 1000, Y = 0;
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
	Color Cube[4][4];
	int R, C, row, col;
	int Dir;
	bool Active;
	int design;
	Structure()
	{
		int a = rand() % 256, b = rand() % 256, c = rand() % 256;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				row = col = 4;
				C = Block::TotalC / 3;
				R = Block::TotalR;
				Cube[i][j].Show = false;
				Cube[i][j].R = a;
				Cube[i][j].G = b;
				Cube[i][j].B = c;
			}
		}
		Dir = 0;
		Active = false;
	}
	void Reset()
	{
		int a = 56 + rand() % 200, b = 56 + rand() % 200, c = 56 + rand() % 200;
		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < row; j++)
			{
				C = Block::TotalC / 3;
				R = Block::TotalR;
				Cube[i][j].Show = false;
				Cube[i][j].R = a;
				Cube[i][j].G = b;
				Cube[i][j].B = c;
			}
		}
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
		iSetTransparentColor(Tetris.Cube[0][0].R, Tetris.Cube[0][0].G, Tetris.Cube[0][0].B, .3);
		ifstream in;
		in.open(tetrisDesign[Tetris.design], ios::in);


		for (int i = 0; i < Tetris.col; i++)
		{
			for (int j = 0; j < Tetris.row; j++)
			{
				if (Tetris.Cube[i][j].Show)
				{
					iFilledRectangle((Tetris.C + i)*Block::Width, (Tetris.R + j) * Block::Height, Block::Width, Block::Height);
				}
			}
		}


	}
	else
	{
		Generate();
	}


	for (i = 0; i < Block::TotalC; i++)
	{
		for (j = 0; j < Block::TotalR; j++)
		{
			if (Cube[i][j].Show)
			{
				iSetTransparentColor(Cube[i][j].R, Cube[i][j].G, Cube[i][j].B, .5);
				iFilledRectangle(i * Block::Width, j * Block::Height, Block::Width, Block::Height);
			}
		}
	}

	iSetTransparentColor(255, 255, 255, .2);
	for (i = 0; i <=Block::TotalC; i++)
	{
		iLine(Block::Width * i, 0, Block::Width * i,  Block::Height*Block::TotalR);
	}

	for (i = 0; i <=Block::TotalR; i++)
	{
		iLine(0, Block::Height * i, Block::Width*Block::TotalC, Block::Height * i);
	}

	iSetColor(255,255,255);
	char temp[10];
	itoa(Score,temp,10);
	iText(10,Window::Height-30,temp);
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
	if (key == ' ')
	{
		Tetris.Dir = (Tetris.Dir + 1) % 4;
		ifstream in;
		in.open(tetrisDesign[Tetris.design], ios::in);


		for (int i = 0; i < Tetris.col; i++)
		{
			for (int j = 0; j < Tetris.row; j++)
			{
				int temp;
				in >> temp;
				if (Tetris.Dir == 0)
				{
					Tetris.Cube[i][j].Show = temp;
				}
			}
		}

		for (int i = 0; i < Tetris.col; i++)
		{
			for (int j = 0; j < Tetris.row; j++)
			{
				int temp;
				in >> temp;
				if (Tetris.Dir == 1)
				{
					Tetris.Cube[i][j].Show = temp;
				}
			}
		}

		for (int i = 0; i < Tetris.col; i++)
		{
			for (int j = 0; j < Tetris.row; j++)
			{
				int temp;
				in >> temp;
				if (Tetris.Dir == 2)
				{
					Tetris.Cube[i][j].Show = temp;
				}
			}
		}

		for (int i = 0; i < Tetris.col; i++)
		{
			for (int j = 0; j < Tetris.row; j++)
			{
				int temp;
				in >> temp;
				if (Tetris.Dir == 3)
				{
					Tetris.Cube[i][j].Show = temp;
				}
			}
		}
		in.close();
	}
}

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_END) exit(0);
	else if (key == GLUT_KEY_RIGHT)
	{
		if (CheckRight())
		{
			Tetris.C++;
		}
	}
	else if (key == GLUT_KEY_LEFT)
	{
		if (CheckLeft())
		{
			Tetris.C--;
		}
	}
	else if (key == GLUT_KEY_DOWN)
	{
		if (CheckBottom())
		{
			Tetris.R--;
		}
	}
}

void Generate()
{
	Tetris.Reset();
	Tetris.Active = true;
	Tetris.design = rand() % 7;
	ifstream in;
	in.open(tetrisDesign[Tetris.design], ios::in);

	for (int i = 0; i < Tetris.col; i++)
	{
		for (int j = 0; j < Tetris.row; j++)
		{
			in >> Tetris.Cube[i][j].Show;
		}
	}
	in.close();
}

void Fix()
{
	Tetris.Active = false;

	for (int i = 0; i < Tetris.col; i++)
	{
		for (int j = 0; j < Tetris.row; j++)
		{
			if (Tetris.Cube[i][j].Show)
			{
				Cube[Tetris.C + i][Tetris.R + j].Show = true;
				Cube[Tetris.C + i][Tetris.R + j].R = Tetris.Cube[0][0].R;
				Cube[Tetris.C + i][Tetris.R + j].G = Tetris.Cube[0][0].G;
				Cube[Tetris.C + i][Tetris.R + j].B = Tetris.Cube[0][0].B;
			}
		}
	}
}

bool CheckBottom()
{
	for (int i = 0; i < Tetris.col; i++)
	{
		for (int j = 0; j < Tetris.row; j++)
		{
			if (Tetris.Cube[i][j].Show)
			{
				if (Tetris.R + j - 1 < 0)
				{
					return false;
				}
				else if (Cube[Tetris.C + i][Tetris.R + j - 1].Show)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool CheckLeft()
{
	for (int i = 0; i < Tetris.col; i++)
	{
		for (int j = 0; j < Tetris.row; j++)
		{
			if (Tetris.Cube[i][j].Show)
			{
				if (Tetris.C + i - 1 < 0)
				{
					return false;
				}
				else if (Cube[Tetris.C + i - 1][Tetris.R + j].Show)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool CheckRight()
{
	for (int i = 0; i < Tetris.col; i++)
	{
		for (int j = 0; j < Tetris.row; j++)
		{
			if (Tetris.Cube[i][j].Show)
			{
				if (Tetris.C + i + 1 >= Block::TotalC)
				{
					return false;
				}
				else if (Cube[Tetris.C + i + 1][Tetris.R + j].Show)
				{
					return false;
				}
			}
		}
	}
	return true;
}

void Fall()
{
	if (!Tetris.R)
	{
		Fix();
		return;
	}
	if (CheckBottom())
	{
		Tetris.R--;
	}
	else
	{
		Fix();
	}
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
			for (int k = i; k < Block::TotalR; k++)
			{
				for (int l = 0; l < Block::TotalC; l++)
				{
					Cube[l][k].Show = Cube[l][k + 1].Show;
				}
			}
			i--;
			Score+=10;
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
