# image_loader

The LMS image loader module loads images from a directory and provides them via a datachannel.

## Formats
- If PGM files are loaded they are provided as Format::GREY
- If PPM files are loaded they are provided as Format::RGB

## DataChannels
- **IMAGE** - where to put the loaded image

## Config
- **directory** - Images will be loaded from this directory
- **format** - image file format to load, either pgm or ppm
- **filepattern** - used to create the file names, patterns can use every placeholder supported by printf

## Dependencies
- [imaging](https://github.com/syxolk/imaging)

## Recommended modules
- [image_converter](https://github.com/syxolk/image_converter) - to convert the read images to other formats
- [camera_renderer](https://github.com/Phibedy/camera_renderer) - to visualize the loaded images
