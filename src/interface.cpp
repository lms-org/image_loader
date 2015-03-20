#include <image_loader.h>

extern "C" {
void* getInstance () {
    return new ImageLoader();
}
}
