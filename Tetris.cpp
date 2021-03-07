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
#define FontTriangle_Height 1
#define FontWidth 1
#define FontHeight 5
void VerticalSegment(int X, int Y, int dx, int dy, int size)
{
	int triangleHeight = FontTriangle_Height * size;
	double  x[6] = { X , X - dx / 2 , X - dx / 2 , X , X + dx / 2 , X + dx / 2 },
	               y[6] = { Y , Y + triangleHeight , Y + dy + triangleHeight , Y + dy + 2 * triangleHeight , Y + dy + triangleHeight , Y + triangleHeight };

	iFilledPolygon(x, y, 6);
}
void HorizontalSegment(int X, int Y, int dx, int dy, int size)
{
	int triangleHeight = FontTriangle_Height * size;
	double  x[6] = { X , X + triangleHeight , X + dx + triangleHeight , X + dx + 2 * triangleHeight , X + dx + triangleHeight , X + triangleHeight },
	               y[6] = { Y , Y + dy / 2 , Y + dy / 2 , Y , Y - dy / 2 , Y - dy / 2 };

	iFilledPolygon(x, y, 6);
}
void iDrawDigit(int x, int y, int digit, int size)
{
	if (digit == 0 || digit == 2 || digit == 6 || digit == 8)
		VerticalSegment(x, y, FontWidth * size, FontHeight * size, size);
	if (digit == 0 || digit == 4 || digit == 5 || digit == 6 || digit == 8 || digit == 9)
		VerticalSegment(x, y + FontHeight * size + 2 * FontTriangle_Height * size, FontWidth * size, FontHeight * size, size);
	if (digit == 0 || digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 7 || digit == 8 || digit == 9)
		HorizontalSegment(x, y + 2 * FontHeight * size + 4 * FontTriangle_Height * size, FontHeight * size, FontWidth * size, size);
	if (digit == 2 || digit == 3 || digit == 4 || digit == 5 || digit == 6 || digit == 8 || digit == 9)
		HorizontalSegment(x, y + FontHeight * size + 2 * FontTriangle_Height * size, FontHeight * size, FontWidth * size, size);
	if (digit == 0 || digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 8 || digit == 9)
		HorizontalSegment(x, y, FontHeight * size, FontWidth * size, size);
	if (digit == 0 || digit == 1 || digit == 3 || digit == 4 || digit == 5 || digit == 6 || digit == 7 || digit == 8 || digit == 9)
		VerticalSegment(x + FontHeight * size + 2 * FontTriangle_Height * size, y, FontWidth * size, FontHeight * size, size);
	if (digit == 0 || digit == 1 || digit == 2 || digit == 3 || digit == 4 || digit == 7 || digit == 8 || digit == 9)
		VerticalSegment(x + FontHeight * size + 2 * FontTriangle_Height * size, y + FontHeight * size + 2 * FontTriangle_Height * size, FontWidth * size, FontHeight * size, size);
}

void iDrawScore(int S, int size, int x, int y)
{
	if (!S) iDrawDigit(x, y, S, size);
	for (int i = 0; S; i++)
	{
		iDrawDigit(x - i * size * 10, y, S % 10, size);
		S /= 10;
	}
}

int Score = 0,HighScore;
void Generate();
bool CheckBottom();
bool CheckLeft();
bool CheckRight();
class Block {
public:
	static const int Height = 50, Width = 50, TotalR = 20, TotalC = 10;
};

class Window {
public:
	static const int Height = Block::Height * Block::TotalR, Width = Block::Width * Block::TotalC + Block::Width * 6, X = 1000, Y = 0;
	static constexpr char* Title = "Tetris";
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
		int a = 20 + rand() % 236, b = 20 + rand() % 236, c = 20 + rand() % 236;
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
		design = -1;
		Dir = 0;
		Active = false;
	}
	void Reset()
	{
		int a = 20 + rand() % 236, b = 20 + rand() % 236, c = 20 + rand() % 236;
		// int a = rand() % 256, b = rand() % 256, c = rand() % 256;
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
} Tetris, nextTetris;


void iDrawBlock(int x, int y, int R, int G, int B)
{
	iSetColor(R + 15, G + 15, B + 15);
	double a[] = {x, x, x + Block::Width};
	double b[] = {y, y + Block::Height, y + Block::Height};
	double c[] = {x, x + Block::Width, x + Block::Width};
	double d[] = {y, y, y + Block::Height};
	iFilledPolygon(a, b, 3);
	iSetColor(R - 15, G - 15, B - 15);
	iFilledPolygon(c, d, 3);
	iSetColor(R, G, B);
	iFilledRectangle(x + 12, y + 12, Block::Width - 24, Block::Height - 24);
	iSetColor(5, 5, 5);
	iRectangle(x, y, Block::Width, Block::Height);
}

void iDraw(void)
{
	iClear();
	int i, j;

	if (Tetris.Active)
	{
		for (int i = 0; i < Tetris.col; i++)
		{
			for (int j = 0; j < Tetris.row; j++)
			{
				if (Tetris.Cube[i][j].Show)
				{
					iDrawBlock((Tetris.C + i)*Block::Width, (Tetris.R + j) * Block::Height, Tetris.Cube[0][0].R, Tetris.Cube[0][0].G, Tetris.Cube[0][0].B);
				}
			}
		}

		for (int i = 0; i < Tetris.col; i++)
		{
			for (int j = 0; j < Tetris.row; j++)
			{
				if (nextTetris.Cube[i][j].Show)
				{
					iDrawBlock(Block::Width * (Block::TotalC + 1 + i), Block::Height * (8 + j), nextTetris.Cube[0][0].R, nextTetris.Cube[0][0].G, nextTetris.Cube[0][0].B);
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
				// iSetTransparentColor(Cube[i][j].R, Cube[i][j].G, Cube[i][j].B, .5);
				iDrawBlock(i * Block::Width, j * Block::Height, Cube[i][j].R, Cube[i][j].G, Cube[i][j].B);
				// iFilledRectangle(i * Block::Width, j * Block::Height, Block::Width, Block::Height);
			}
		}
	}

	iSetTransparentColor(255, 255, 255, .2);
	for (i = 0; i <= Block::TotalC; i++)
	{
		iLine(Block::Width * i, 0, Block::Width * i,  Block::Height * Block::TotalR);
	}

	for (i = 0; i <= Block::TotalR; i++)
	{
		iLine(0, Block::Height * i, Block::Width * Block::TotalC, Block::Height * i);
	}


	// iBigText(Block::Width*Block::TotalC+20, Window::Height - 130, temp);

	iSetColor(255, 255, 255);
	iDrawScore(HighScore, 2, Window::Width - 60, Window::Height - 40);

	iSetColor(255, 255, 0);
	iDrawScore(Score, 6, Window::Width - 80, Window::Height - 150);
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
	else if (key == GLUT_KEY_UP)
	{
		Tetris.Dir = (Tetris.Dir + 1) % 4;
		ifstream in;
		in.open(tetrisDesign[Tetris.design], ios::in);

		for (int i = 0; i < Tetris.row; i++)
		{
			for (int j = 0; j < Tetris.col; j++)
			{
				int temp;
				in >> temp;
				if (Tetris.Dir == 0)
				{
					Tetris.Cube[j][Tetris.row - i - 1].Show = temp;
					if (temp && Tetris.C + j >= Block::TotalC)
					{
						Tetris.C -= (Tetris.C + j - Block::TotalC + 1);
					}
				}
			}
		}

		for (int i = 0; i < Tetris.row; i++)
		{
			for (int j = 0; j < Tetris.col; j++)
			{
				int temp;
				in >> temp;
				if (Tetris.Dir == 1)
				{
					Tetris.Cube[j][Tetris.row - i - 1].Show = temp;
					if (temp && Tetris.C + j >= Block::TotalC)
					{
						Tetris.C -= (Tetris.C + j - Block::TotalC + 1);
					}
				}
			}
		}

		for (int i = 0; i < Tetris.row; i++)
		{
			for (int j = 0; j < Tetris.col; j++)
			{
				int temp;
				in >> temp;
				if (Tetris.Dir == 2)
				{
					Tetris.Cube[j][Tetris.row - i - 1].Show = temp;
					if (temp && Tetris.C + j >= Block::TotalC)
					{
						Tetris.C -= (Tetris.C + j - Block::TotalC + 1);
					}
				}
			}
		}

		for (int i = 0; i < Tetris.row; i++)
		{
			for (int j = 0; j < Tetris.col; j++)
			{
				int temp;
				in >> temp;
				if (Tetris.Dir == 3)
				{
					Tetris.Cube[j][Tetris.row - i - 1].Show = temp;
					if (temp && Tetris.C + j >= Block::TotalC)
					{
						Tetris.C -= (Tetris.C + j - Block::TotalC + 1);
					}
				}
			}
		}
		in.close();
	}
}

void Generate()
{
	if (nextTetris.design == -1)
	{
		nextTetris.design = rand() % 7;
		ifstream in;
		in.open(tetrisDesign[nextTetris.design], ios::in);

		for (int i = 0; i < nextTetris.row; i++)
		{
			for (int j = 0; j < nextTetris.col; j++)
			{
				in >> nextTetris.Cube[j][Tetris.row - i - 1].Show;
			}
		}
		in.close();
	}
	else
	{
		Tetris = nextTetris;
		Tetris.Active = true;

		nextTetris.Reset();
		nextTetris.design = rand() % 7;
		ifstream in;
		in.open(tetrisDesign[nextTetris.design], ios::in);

		for (int i = 0; i < nextTetris.row; i++)
		{
			for (int j = 0; j < nextTetris.col; j++)
			{
				in >> nextTetris.Cube[j][Tetris.row - i - 1].Show;
			}
		}
		in.close();
	}
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
					if (Tetris.R + j >= Block::TotalR)
					{
						ofstream out;
						out.open("Data\\HighScore.txt", ios::out);
						out << Score;
						out.close();
						exit(0);
					}
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
			Score += 10;

			ifstream in;
			in.open("Data\\HighScore.txt", ios::in);
			int temp;
			in >> HighScore;
			in.close();
			if (Score > HighScore)
			{
				ofstream out;
				out.open("Data\\HighScore.txt", ios::out);
				out << Score;
				out.close();
				HighScore=Score;
			}
		}
	}
}
int main(int argc, char *argv[])
{
	ifstream in;
	in.open("Data\\HighScore.txt", ios::in);
	int temp;
	in >> HighScore;
	in.close();
	srand(time(NULL));
	iSetTimer(300, Fall);
	iSetTimer(0, Match);
	glutInit(&argc, argv);
	iInitialize(Window::Width, Window::Height, Window::Title, Window::X, Window::Y);
	// glutFullScreen();
	glutMainLoop();
}
