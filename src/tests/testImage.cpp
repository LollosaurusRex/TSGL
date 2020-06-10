/*
 * testImage.cpp
 *
 * Usage: ./testImage <width> <height>
 */

#include <tsgl.h>

using namespace tsgl;

/*!
 * \brief Draws various images on a Canvas.
 * \details Very basic test function showcasing image drawing capabilities.
 * - The first 6 images are drawn opaque.
 * - The 7th image is drawn across the entire Canvas with alpha transparency.
 * .
 * \param can Reference to the Canvas being drawn to.
 */
void imageFunction(Canvas& can) {
    int ww = can.getWindowWidth()/3, hh = can.getWindowHeight()/2;
    // Square * s = new Square(5,0,0,50,0,0,0,RED);
    // can.add(s);

    // Pyramid * p = new Pyramid(-5,0,0,5,100,50,0,0,0,BLUE);
    // can.add(p);

    // Image * image = new Image(0,0,0,"./assets/pics/Messier51.jpg", 4,3, 0,0,0);
    // can.add(image);

    // Image * image = new Image(-ww,0.5 * hh,0,"./assets/pics/test.png", ww,hh, 0,0,0);
    // can.add(image);
    // Image * image2 = new Image(0,0.5 * hh,0,"./assets/pics/ship.bmp", ww,hh, 0,0,0);
    // can.add(image2);
    // Image * image3 = new Image(ww,0.5 * hh,0,"./assets/pics/shiprgb.bmp", ww,hh, 0,0,0);
    // can.add(image3);
    // Image * image4 = new Image(-ww,-0.5 * hh,0,"./assets/pics/sky_main.jpg", ww,hh, 0,0,0);
    // can.add(image4);
    // Image * image5 = new Image(0,-0.5 * hh,0,"./assets/pics/colorfulKeyboard.jpg", ww,hh, 0,0,0);
    // can.add(image5);
    // Image * image6 = new Image(ww,-0.5 * hh,0,"./assets/pics/cow.jpg", ww,hh, 0,0,0);
    // can.add(image6);

    Image * image = new Image(-ww,0.5 * hh,0,"./assets/pics/launch.bmp", ww,hh, 0,0,0);
    can.add(image);
    Image * image2 = new Image(0,0.5 * hh,0,"./assets/pics/launch.bmp", ww,hh, 0,0,0);
    can.add(image2);
    Image * image3 = new Image(ww,0.5 * hh,0,"./assets/pics/launch.bmp", ww,hh, 0,0,0);
    can.add(image3);
    Image * image4 = new Image(-ww,-0.5 * hh,0,"./assets/pics/launch.bmp", ww,hh, 0,0,0);
    can.add(image4);
    Image * image5 = new Image(0,-0.5 * hh,0,"./assets/pics/launch.bmp", ww,hh, 0,0,0);
    can.add(image5);
    Image * image6 = new Image(ww,-0.5 * hh,0,"./assets/pics/launch.bmp", ww,hh, 0,0,0);
    can.add(image6);

    // Image * image7 = new Image(0,0,0,"./assets/pics/cow.jpg", 960,480,0,0,0,th);
    // can.add(image7);

    // image->setHeight((GLfloat)image->getPixelHeight() / 100);
    // image->setWidth((GLfloat)image->getPixelWidth() / 100);

    float floatVal = 0.0f;
    GLfloat delta = 0.05;
    bool ss = false;
    while (can.isOpen()) {
        can.sleep();
        // image->setCenterX(sin(floatVal/90));
        // printf("%f\n", image->getCenterX());
        // image->setCenterY(sin(floatVal/90));
        // image->setCenterZ(sin(floatVal/90));
        // image->setYaw(floatVal);
        // image->setPitch(floatVal);
        // image->setRoll(floatVal);
        // image->setWidth(sin(floatVal/90) + 4);
        // image->setHeight(sin(floatVal/90) + 4);
        // if (image->getWidth() > 5 || image->getWidth() < 3) {
        //     delta *= -1;
        // }
        // image->changeWidthBy(delta);
        // if (image->getHeight() > 5 || image->getHeight() < 3) {
        //     delta *= -1;
        // }
        // image->changeHeightBy(delta);
        // printf("%d\n", can.getFrameNumber());
        // if (can.getFrameNumber() > 50 && !ss) {
        //     can.takeScreenShot();
        //     ss = true;
        // }
        // ColorInt blah = can.getPoint(can.getWindowWidth()/2,can.getWindowHeight()/2);
        // printf("%d, %d, %d, %d\n", blah.R, blah.G, blah.B, blah.A);
        floatVal += 1;
    }
    // int ww = can.getWindowWidth()/3, hh = can.getWindowHeight()/2;
    // can.drawImage("../assets/pics/test.png", 0, 0, ww, hh);
    // can.drawImage("../assets/pics/ship.bmp", ww, 0, ww, hh); // possibly lost
    // can.drawImage("../assets/pics/shiprgb.bmp", ww*2, 0, ww, hh); // definitely lost
    // can.drawImage("../assets/pics/sky_main.jpg", 0, hh, ww, hh);
    // can.drawImage("../assets/pics/colorfulKeyboard.jpg", ww, hh, ww, hh);
    // can.drawImage("../assets/pics/cow.jpg", ww*2, hh, ww, hh);

    // can.drawImage("../assets/pics/background.jpg", ww/2, 0, ww*2, hh*2, 0.25f); //Overlay

    delete image;
    delete image2;
    delete image3;
    delete image4;
    delete image5;
    delete image6;
    // delete image7;
}

//Takes command-line arguments for the width and height of the screen
int main(int argc, char * argv[]) {
    int w = (argc > 1) ? atoi(argv[1]) : 1.2*Canvas::getDisplayHeight();
    int h = (argc > 2) ? atoi(argv[2]) : 0.5*w;
    if(w <= 0 || h <= 0) { //Check width and height validity
      w = 1.2*Canvas::getDisplayHeight(); h = 0.5*w;
    }
    Canvas c(-1, -1, w, h ,"Images");
    c.run(imageFunction);
}
