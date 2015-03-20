#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "lms/module.h"
#include "lms/imaging/image.h"

class ImageLoader : public lms::Module {
public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;
private:
    const lms::type::ModuleConfig *config;

    lms::imaging::Image *imagePtr;

    std::string directory;
    int imageCounter;
};

#endif /* IMAGE_LOADER_H */
