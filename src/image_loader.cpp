#include "image_loader.h"
#include "lms/datamanager.h"
#include "lms/imaging/pnm.h"

bool ImageLoader::initialize() {
    imagePtr = writeChannel<lms::imaging::Image>("IMAGE");

    directory = config().get<std::string>("directory");
    imageCounter = config().get<int>("minCounter");
    manualNavigation = false;
    return true;
}

bool ImageLoader::deinitialize() {
    return true;
}

bool ImageLoader::cycle() {
    std::string commandNavigation = config()
            .get<std::string>("commandNavigation", "image_loader");

    for(const std::string &content : messaging()->receive(commandNavigation)) {
        if(content == "manual") {
            manualNavigation = ! manualNavigation;
        }
    }

    std::string fullPath;
    bool loadSingleFile = config().get<bool>("loadSingleFile");

    if(! loadSingleFile) {
        std::string filePattern = config().get<std::string>("filePattern");
        std::string newDirectory = config().get<std::string>("directory");

        if(newDirectory != directory) {
            // reset imageCounter if directory changed
            imageCounter = 0;
            directory = newDirectory;
        }

        char name[50];
        std::snprintf(name, sizeof(name), filePattern.c_str(), imageCounter);
        fullPath = directory + "/" + name;
    } else {
        fullPath = config().get<std::string>("singleFile");
    }

    bool result = lms::imaging::readPNM(*imagePtr, fullPath);

    int minCounter = config().get<int>("minCounter");
    int maxCounter = config().get<int>("maxCounter");

    if(manualNavigation) {
        for(const std::string &content :
            messaging()->receive(commandNavigation)) {
            if(content == "next") {
                imageCounter ++;

                if(maxCounter != -1 && imageCounter > maxCounter) {
                    imageCounter = maxCounter;
                }
            } else if(content == "previous") {
                imageCounter --;

                if(imageCounter < minCounter) {
                    imageCounter = minCounter;
                }
            }
        }
    } else if(! result) {
        if(loadSingleFile) {
            logger.warn("cycle") << "Could not read image";
        }else{
            if(maxCounter == -1) {
                // reset to minCounter if image could not be read
                if(minCounter == imageCounter){
                    logger.error("cycle") << "Could not read image";
                }
                imageCounter = minCounter;
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
        imageCounter = config().get<int>("minCounter");
    }

    return true;
}
