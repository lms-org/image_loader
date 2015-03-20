# image_loader

The LMS image loader module loads images from a directory and provides them via a datachannel.

The image file names should have the format "image_%i.pgm".

## Config
- **image_channel** - Loaded images will be written into the this data channel.
- **directory** - Images will be loaded from this directory

## Dependencies
- [imaging](https://github.com/syxolk/imaging)

## Recommended modules
- [image_converter](https://github.com/syxolk/image_converter) - to convert the read images to other formats
