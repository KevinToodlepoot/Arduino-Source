/*  Kernels Tests
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *  
 *  
 */


#ifndef PokemonAutomation_Tests_Kernels_Tests_H
#define PokemonAutomation_Tests_Kernels_Tests_H

namespace PokemonAutomation{

class ImageViewRGB32;

int test_kernels_ImageScaleBrightness(const ImageViewRGB32& image);

int test_kernels_BinaryMatrix(const ImageViewRGB32& image);

int test_kernels_FilterRGB32(const ImageViewRGB32& image);


int test_kernels_Waterfill(const ImageViewRGB32& image);


}

#endif
