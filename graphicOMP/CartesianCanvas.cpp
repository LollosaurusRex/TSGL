#include "CartesianCanvas.h"

/*
 * Default constructor for the CartesianCanvas class
 * Parameter:
 * 		b, the buffer size for the Shapes
 * Returns: a new 800x600 CartesianCanvas with 1-1 pixel correspondence and central origin
 */
CartesianCanvas::CartesianCanvas(unsigned int b) : Canvas(b) {
	recomputeDimensions(-400,-300,400,300);
}

/*
 * Explicit constructor for the CartesianCanvas class
 * Parameters:
 * 		xx, the x position of the CartesianCanvas window
 * 		yy, the y position of the CartesianCanvas window
 * 		w, the x dimension of the CartesianCanvas window
 * 		h, the y dimension of the CartesianCanvas window
 * 		xMin, the real number corresponding to the left edge of the CartesianCanvas
 * 		YMin, the real number corresponding to the top edge of the CartesianCanvas
 * 		xMax, the real number corresponding to the right edge of the CartesianCanvas
 * 		xMax, the real number corresponding to the bottom edge of the CartesianCanvas
 * 		b, the buffer size for the Shapes
 * 		t, the title of the window (optional)
 * Returns: a new CartesianCanvas with the specified positional/scaling data and title
 */
CartesianCanvas::CartesianCanvas(int xx, int yy, int w, int h,
			Decimal xMin, Decimal yMin, Decimal xMax, Decimal yMax, unsigned int b, std::string t) :
			Canvas(xx, yy, w, h, b, t) {
	recomputeDimensions(xMin, yMin, xMax, yMax);
}

/*
 * drawAxes draws axes on the screen
 * Parameters:
 * 		x, the x location for the y-axis
 * 		y, the y location for the x-axis
 * 		dx, the distance between marks on the x-axis
 * 		dy, the distance between marks on the y-axis
 */
void CartesianCanvas::drawAxes(Decimal x, Decimal y, Decimal dx = 0, Decimal dy = 0) {
	drawLine(maxX, y, minX, y);								// Make the two axes
	drawLine(x, maxY, x, minY);
	if (dx != 0 && dy != 0) {
		for (int x = dx; x < maxX; x += dx) {
			drawLine(x, y + 4*pixelHeight, x, y - 4*pixelHeight);
		}
		for (int x = -dx; x > minX; x -= dx) {
			drawLine(x, y + 4*pixelHeight, x, y - 4*pixelHeight);
		}
		for (int y = dy; y < maxY; y += dy) {
			drawLine(x + 4*pixelWidth, y, x - 4*pixelWidth, y);
		}
		for (int y = -dy; y > minY; y -= dy) {
			drawLine(x + 4*pixelWidth, y, x - 4*pixelWidth, y);
		}
	}
}

/*
 * drawFunction draws the Function on the screen
 * Parameters:
 * 		f, a Function type extending Function
 */
void CartesianCanvas::drawFunction(const Function* f) {
	int screenX = 0, screenY = 0;
	Polyline *p = new Polyline(1 + (maxX-minX) / pixelWidth);
	for (Decimal x = minX; x <= maxX; x += pixelWidth) {
		getScreenCoordinates(x, f->valueAt(x), screenX, screenY);
		p->addVertex(screenX, screenY);
	}
	std::unique_lock<std::mutex> mlock(buffer);
	myBuffer->push(p);										// Push it onto our drawing buffer
	mlock.unlock();
}

/*
 * drawImage draws an image with the given coordinates  dimensions
 * Parameters:
 * 		x, the x coordinate of the Image's left edge
 *		y, the y coordinate of the Image's top edge
 * 		w, the width of the Image
 *		h, the height of the Image
 */
void CartesianCanvas::drawImage(GLuint &texture, Decimal x, Decimal y, Decimal w, Decimal h) {
//	int actualX1, actualY1, actualX2, actualY2;
//	getScreenCoordinates(x, y, actualX1, actualY1);
//	getScreenCoordinates(x+w, y+h, actualX2, actualY2);
//	Image* im = new Image(texture, actualX1, actualY1, actualX2-actualX1, actualY2-actualY1);	// Creates the Rectangle with the specified coordinates and color
//	std::unique_lock<std::mutex> mlock(buffer);
//	myBuffer->push(im);								// Push it onto our drawing buffer
//	mlock.unlock();
}

/*
 * drawLine draws a line at the given coordinates with the given color
 * Parameters:
 * 		x1, the x position of the start of the line
 * 		y1, the y position of the start of the line
 *		x2, the x position of the end of the line
 * 		y2, the y position of the end of the line
 * 		color, the RGB color (optional)
 */
void CartesianCanvas::drawLine(Decimal x1, Decimal y1, Decimal x2, Decimal y2, RGBfloatType color) {
	int actualX1, actualY1, actualX2, actualY2;
	getScreenCoordinates(x1, y1,actualX1, actualY1);
	getScreenCoordinates(x2, y2, actualX2, actualY2);
	Line* l = new Line(actualX1, actualY1, actualX2, actualY2, color);	// Creates the Line with the specified coordinates and color
	std::unique_lock<std::mutex> mlock(buffer);
	myBuffer->push(l);													// Push it onto our drawing buffer
	mlock.unlock();
}

/*
 * drawPoint draws a point at the given coordinates with the given color
 * Parameters:
 * 		x, the x position of the point
 * 		y, the y position of the point
 * 		color, the RGB color (optional)
 */
void CartesianCanvas::drawPoint(Decimal x, Decimal y, RGBfloatType color) {
	int actualX, actualY;
	getScreenCoordinates(x, y, actualX, actualY);
	Point* p = new Point(actualX, actualY, color);		// Creates the Point with the specified coordinates and color
	std::unique_lock<std::mutex> mlock(buffer);
	myBuffer->push(p);									// Push it onto our drawing buffer
	mlock.unlock();
}

/*
 * drawRectangle draws a rectangle with the given coordinates, dimensions, and color
 * Parameters:
 * 		x, the x coordinate of the Rectangle's left edge
 *		y, the y coordinate of the Rectangle's top edge
 * 		w, the width of the Rectangle
 *		h, the height of the Rectangle
 * 		color, the RGB color (optional)
 */
void CartesianCanvas::drawRectangle(Decimal x, Decimal y, Decimal w, Decimal h, RGBfloatType color) {
	int actualX1, actualY1, actualX2, actualY2;
	getScreenCoordinates(x, y, actualX1, actualY1);
	getScreenCoordinates(x+w, y+h, actualX2, actualY2);
	Rectangle* rec = new Rectangle(actualX1, actualY1, actualX2-actualX1, actualY2-actualY1, color);	// Creates the Rectangle with the specified coordinates and color
	std::unique_lock<std::mutex> mlock(buffer);
	myBuffer->push(rec);								// Push it onto our drawing buffer
	mlock.unlock();
}

/*
 * drawShinyPolygon draws a ShinyPolygon with the given vertex data
 * Parameters:
 * 		size, the number of vertices in the polygon
 * 		x, an array of x positions of the vertices
 * 		y, an array of y positions of the vertices
 * 		color, the RGB color array (optional)
 */
void CartesianCanvas::drawShinyPolygon(int size, int x[], int y[], RGBfloatType color[]) {
	int actualX, actualY;
	ShinyPolygon* p = new ShinyPolygon(size);
	for (int i = 0; i < size; i++) {
		getScreenCoordinates(x[i], y[i], actualX, actualY);
		p->addVertex(actualX, actualY, color[i]);
	}
	std::unique_lock<std::mutex> mlock(buffer);
	myBuffer->push(p);									// Push it onto our drawing buffer
	mlock.unlock();
}

/*
 * drawTriangle draws a Triangle with the given vertices
 * Parameters:
 * 		x1, the x position of the first vertex of the triangle
 * 		y1, the y position of the first vertex of the triangle
 *		x2, the x position of the second vertex of the triangle
 * 		y2, the y position of the second vertex of the triangle
 * 		x3, the x position of the third vertex of the triangle
 * 		y3, the y position of the third vertex of the triangle
 * 		color, the RGB color (optional)
 */
void CartesianCanvas::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, RGBfloatType color) {
	int actualX1, actualY1, actualX2, actualY2, actualX3, actualY3;
	getScreenCoordinates(x1, y1, actualX1, actualY1);
	getScreenCoordinates(x2, y2, actualX2, actualY2);
	getScreenCoordinates(x3, y3, actualX3, actualY3);
	Triangle* t = new Triangle(actualX1, actualY1, actualX2, actualY2,
								actualX3, actualY3, color);			// Creates the Triangle with the specified vertices and color
	std::unique_lock<std::mutex> mlock(buffer);
	myBuffer->push(t);												// Push it onto our drawing buffer
	mlock.unlock();
}

/*
 * getCartesianCoordinates takes a pair of on-screen coordinates and translates them to Cartesian coordinates
 * Parameters:
 * 		screenX, the window's x coordinate
 * 		screenY, the window's y coordinate
 * 		cartX, a reference variable to be filled with screenX's Cartesian position
 * 		cartY, a reference variable to be filled with screenY's Cartesian position
 */
void CartesianCanvas::getCartesianCoordinates(int screenX, int screenY, Decimal &cartX, Decimal &cartY) {
	cartX = (screenX * cartWidth) / winWidth + minX;
	cartY = minY-(screenY - winHeight)*cartHeight/winHeight;
}

/*
 * getScreenCoordinates takes a pair of Cartesian coordinates and translates them to on-screen coordinates
 * Parameters:
 * 		cartX, the Cartesian x coordinate
 * 		cartY, the Cartesian y coordinate
 * 		screenX, a reference variable to be filled with cartX's window position
 * 		screenY, a reference variable to be filled with cartY's window position
 */
void CartesianCanvas::getScreenCoordinates(Decimal cartX, Decimal cartY, int &screenX, int &screenY) {
	screenX = ceil((cartX - minX) / cartWidth * winWidth);
	screenY = ceil(winHeight - (cartY - minY) / cartHeight * winHeight);
}

/*
 * recomputeDimensions recomputes the size variables of CartesianCanvas according to new bounds
 * Parameters:
 * 		xMin, a real number corresponding to the new left edge of the CartesianCanvas
 * 		YMin, a real number corresponding to the new top edge of the CartesianCanvas
 * 		xMax, a real number corresponding to the new right edge of the CartesianCanvas
 * 		xMax, a real number corresponding to the new bottom edge of the CartesianCanvas
 */
void CartesianCanvas::recomputeDimensions(Decimal xMin, Decimal yMin, Decimal xMax, Decimal yMax) {
	minX = xMin;
	minY = yMin;
	maxX = xMax;
	maxY = yMax;
	cartWidth = maxX - minX;
	cartHeight = maxY - minY;
	Decimal xError = cartWidth / winWidth;
	Decimal yError = cartHeight / winHeight;
	pixelWidth = (cartWidth - xError) / (winWidth + xError);
	pixelHeight = (cartHeight  - yError) / (winHeight + yError);
}

void CartesianCanvas::zoom(Decimal x, Decimal y, Decimal scale) {
	Decimal newWidth = cartWidth * scale;
	Decimal newHeight = cartHeight * scale;
	recomputeDimensions(x - .5 * newWidth, y - .5 * newHeight, x + .5 * newWidth, y + .5 * newHeight);
}

void CartesianCanvas::zoom(Decimal x1, Decimal y1, Decimal x2, Decimal y2) {
	Decimal scale = (std::abs(x2 - x1) / cartWidth + std::abs(y2 - y1) / cartHeight) / 2.0;
	zoom((x2 + x1)/2, (y2 + y1)/2, scale);
}
