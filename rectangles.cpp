#include <iostream>
#include <math.h>
#include <conio.h>
#include "rectangles.h"
#include "myconsole.h"
#include "mygraphics.h"
using namespace std;


void rectangles::split(rectangles& r1, rectangles& r2)
{
	bool horizontal = (rand() % 2 == 1);
	int ratio = 5;
	int xcoord = 0, ycoord = 0;
	r1.topLeft = topLeft;
	r2.bottomRight = bottomRight;
	points p;

	//select a random splitting point
	ratio = rand() % 10 + 1;
	xcoord = topLeft.getX();
	xcoord = xcoord + (bottomRight.getX() - topLeft.getX()) * ratio / 10;
	ycoord = topLeft.getY();
	ycoord = ycoord + (bottomRight.getY() - topLeft.getY()) * ratio / 10;

	//set the coordinates
	if (horizontal)   //horizontal split
	{
		r1.bottomRight.set(bottomRight.getX(), ycoord);
		r2.topLeft.set(topLeft.getX(), ycoord);
	}
	else
	{
		r1.bottomRight.set(xcoord, bottomRight.getY());
		r2.topLeft.set(xcoord, topLeft.getY());
	}
}

//draw a line between two points
void rectangles::drawLine(points p1, points p2, char sym/*='-'*/)
{
	int i, x = p1.getX();
	int y = p1.getY();
	bool horizontal = false;
	char symbol[2];
	symbol[1] = 0;
	symbol[0] = '|';
	int initial = p1.getY();
	int final = p2.getY();
	if (p1.getY() == p2.getY())
	{
		horizontal = true;
		initial = p1.getX();
		final = p2.getX();
		symbol[0] = sym;

	}
	for (i = initial; i <= final; ++i)
	{
		OutputString(x, y, symbol);
		if (horizontal)
			x++;
		else y++;

	}
}

void rectangles::drawWhite() {
	COLORREF red = RGB(255, 0, 0);
	COLORREF white = RGB(255, 255, 255);
	//int x1, int y1, int x2, int y2, COLORREF lineColor, COLORREF fillColor
	myRect(topLeft.getX() * 8, topLeft.getY() * 8, bottomRight.getX() * 8, bottomRight.getY() * 8, red, white);
}

void rectangles::draw(char symbol/*='-'*/) {
	COLORREF red = RGB(255, 0, 0);
	COLORREF blue = RGB(0, 0, 255);
	//int x1, int y1, int x2, int y2, COLORREF lineColor, COLORREF fillColor
	myRect(topLeft.getX() * 8, topLeft.getY() * 8, bottomRight.getX() * 8, bottomRight.getY() * 8, red, blue);
}

void rectangles::DrawShrinkedRectangle(int x, int y, char symbol/*='-'*/) {
	COLORREF red = RGB(255, 0, 0);
	COLORREF blue = RGB(0, 0, 255);
	//int x1, int y1, int x2, int y2, COLORREF lineColor, COLORREF fillColor
	myRect(topLeft.getX() * 8, topLeft.getY() * 8, bottomRight.getX() * 8, bottomRight.getY() * 8, red, blue);
}

//void rectangles::draw(char symbol/*='-'*/)
//{
//	drawLine(topLeft,points(bottomRight.getX(),topLeft.getY()),symbol);
//	drawLine(topLeft,points(topLeft.getX(),bottomRight.getY()),symbol);
//	drawLine(points(bottomRight.getX(),topLeft.getY()),bottomRight,symbol);
//	drawLine(points(topLeft.getX(),bottomRight.getY()),bottomRight,symbol);
//}
//
//void rectangles::DrawShrinkedRectangle(int x /*=5*/,int y/*=5*/,char sym/*='-'*/)
//{
//	rectangles r;
//	r.topLeft = topLeft + points(x,y);
//	r.bottomRight = bottomRight - points(x,y);
//	r.draw(sym);
//}
