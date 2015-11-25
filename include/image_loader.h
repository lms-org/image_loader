#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "lms/module.h"
#include "lms/imaging/image.h"
#include "lms/module_config.h"

/**
 * @brief The ImageLoader loads images from a folder or only a single file
 * and provides them as an image in a datachannel.
 */
class ImageLoader : public lms::Module {
public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;
private:
    lms::WriteDataChannel<lms::imaging::Image> imagePtr;

    std::string directory;
    int imageCounter;

    bool manualNavigation;
};

#endif /* IMAGE_LOADER_H */
