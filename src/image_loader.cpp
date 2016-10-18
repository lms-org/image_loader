#include "image_loader.h"
#include "lms/imaging/pnm.h"

bool ImageLoader::initialize() {
    if(!isEnableLoad()) {
        logger.error() << "Command line option --enable-load was not specified";
        return false;
    }

    imagePtr = writeChannel<lms::imaging::Image>("IMAGE");

    directory = loadLogDir("images");
    imageCounter = config().get<int>("minCounter", 0);
    manualNavigation = false;
    return true;
}

bool ImageLoader::deinitialize() {
    return true;
}

bool ImageLoader::cycle() {
    std::string commandNavigation = config()
            .get<std::string>("commandNavigation", "image_loader");
    /*TODO
    for(const std::string &content : messaging()->receive(commandNavigation)) {
        if(content == "manual") {
            manualNavigation = ! manualNavigation;
        }
    }
    */

    std::string fullPath;
    bool loadSingleFile = config().get<bool>("loadSingleFile", false);

    if(! loadSingleFile) {
        std::string filePattern = config().get<std::string>("filePattern", "%04i.pgm");

        char name[50];
        std::snprintf(name, sizeof(name), filePattern.c_str(), imageCounter);
        fullPath = directory + name;
    } else {
        fullPath = config().get<std::string>("singleFile");
    }

    bool result = lms::imaging::readPNM(*imagePtr, fullPath);

    int minCounter = config().get<int>("minCounter", 0);
    int maxCounter = config().get<int>("maxCounter", -1);
    /*TODO
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
    } else*/ if(! result) {
        if(loadSingleFile) {
            logger.warn("cycle") << "Could not read single - image: "<<fullPath;
        }else{
            if(maxCounter == -1) {
                // reset to minCounter if image could not be read
                if(minCounter == imageCounter){
                    logger.info("cycle") << "Could not read image, start from beginning: "<<fullPath;
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
        imageCounter = config().get<int>("minCounter", 0);
    }

    return true;
}
