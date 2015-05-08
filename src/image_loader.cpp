#include "image_loader.h"
#include "lms/datamanager.h"
#include "lms/imaging/pnm.h"

bool ImageLoader::initialize() {
    config = getConfig();
    imagePtr = datamanager()->writeChannel<lms::imaging::Image>(this, "IMAGE");

    directory = config->get<std::string>("directory");
    imageCounter = config->get<int>("minCounter");
    return true;
}

bool ImageLoader::deinitialize() {
    return true;
}

bool ImageLoader::cycle() {
    std::string fullPath;
    bool loadSingleFile = config->get<bool>("loadSingleFile");

    if(! loadSingleFile) {
        std::string filePattern = config->get<std::string>("filePattern");
        std::string newDirectory = config->get<std::string>("directory");

        if(newDirectory != directory) {
            // reset imageCounter if directory changed
            imageCounter = 0;
            directory = newDirectory;
        }

        char name[50];
        std::snprintf(name, sizeof(name), filePattern.c_str(), imageCounter);
        fullPath = directory + "/" + name;
    } else {
        fullPath = config->get<std::string>("singleFile");
    }

    bool result = false;

    std::string format = config->get<std::string>("format");
    if(format == "pgm") {
        result = lms::imaging::readPGM(*imagePtr, fullPath);
    } else if(format == "ppm") {
        result = lms::imaging::readPPM(*imagePtr, fullPath);
    } else {
        logger.error("cycle") << "format is invalid, must be pgm or ppm";
        return false;
    }

    int maxCounter = config->get<int>("maxCounter");

    if(! result) {
        logger.warn("cycle") << "Could not read image";

        if(! loadSingleFile) {
            if(maxCounter == -1) {
                // reset to minCounter if image could not be read
                imageCounter = config->get<int>("minCounter");
            } else {
                imageCounter ++;
            }
        }
    } else {
        if(! loadSingleFile) {
            imageCounter++;
        }
    }

    if(!loadSingleFile && maxCounter != -1 && imageCounter > maxCounter) {
        imageCounter = config->get<int>("minCounter");
    }

    return true;
}
