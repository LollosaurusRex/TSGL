/*
 * testUnits.cpp runs the unit tests for the TSGL library.
 *
 *  Created on: Jun 4, 2015
 *      Author: cpd5
 */

#include "tsgl.h"

using namespace tsgl;

int main() {
   Canvas::runTests();
   TextureHandler::runTests();
}
