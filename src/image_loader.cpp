#include "image_loader.h"
#include "lms/datamanager.h"
#include "lms/imaging/pnm.h"

bool ImageLoader::initialize() {
    config = getConfig();

    std::string imageChannel = config->get<std::string>("image_channel");
    directory = config->get<std::string>("directory");
    format = config->get<std::string>("format");
    filepattern = config->get<std::string>("filepattern");
    imageCounter = 0;

    if(directory.empty()) {
        logger.error("init") << "directory is empty";
        return false;
    }

    if(imageChannel.empty()) {
        logger.error("init") << "image_channel is empty";
        return false;
    }

    if(format.empty()) {
        logger.error("init") << "format was not specified";
        return false;
    } else if(format != "pgm" && format != "ppm") {
        logger.error("init") << "format must be either pgm or ppm";
        return false;
    }

    if(filepattern.empty()) {
        logger.error("init") << "filepattern was not specified";
        return false;
    }

    imagePtr = datamanager()->writeChannel<lms::imaging::Image>(this, imageChannel);
    return true;
}

bool ImageLoader::deinitialize() {
    return true;
}

bool ImageLoader::cycle() {
    char name[50];
    std::snprintf(name, sizeof(name), filepattern.c_str(), imageCounter);
    std::string fullPath = directory + "/" + name;

    bool result = false;

    logger.time("read");
    if(format == "pgm") {
        result = lms::imaging::readPGM(*imagePtr, fullPath);
    } else if(format == "ppm") {
        result = lms::imaging::readPPM(*imagePtr, fullPath);
    }
    logger.timeEnd("read");

    if(! result) {
        logger.warn("cycle") << "Could not read image";
        imageCounter = 0;
    } else {
        imageCounter++;
    }

    return true;
}
