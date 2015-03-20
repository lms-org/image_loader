#include "image_loader.h"
#include "lms/datamanager.h"
#include "lms/imaging/pnm.h"

bool ImageLoader::initialize() {
    config = getConfig();

    std::string imageChannel = config->get<std::string>("image_channel");
    directory = config->get<std::string>("directory");
    imageCounter = 0;

    if(directory.empty()) {
        logger.error("init") << "directory is empty";
        return false;
    }

    if(imageChannel.empty()) {
        logger.error("init") << "image_channel is empty";
        return false;
    }

    imagePtr = datamanager()->writeChannel<lms::imaging::Image>(this, imageChannel);
    return true;
}

bool ImageLoader::deinitialize() {
    return true;
}

bool ImageLoader::cycle() {
    logger.time("read");
    bool result = lms::imaging::readPGM(*imagePtr,
                                        directory + "/image_" + std::to_string(imageCounter) + ".pgm");
    logger.timeEnd("read");

    if(! result) {
        logger.warn("cycle") << "Could not read image";
        imageCounter = 0;
    } else {
        imageCounter++;
    }

    return true;
}
