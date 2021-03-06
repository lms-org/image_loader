# image_loader

The LMS image loader module loads images from a directory and provides them via a datachannel.

## Formats
- If PGM files are loaded they are provided as Format::GREY
- If PPM files are loaded they are provided as Format::RGB

## DataChannels
- **IMAGE** - where to put the loaded image

## Config
- **filePattern** - used to create the file names, patterns can use every
  placeholder supported by printf. Defaults to "%04i.pgm".
- **minCounter** - start counting the images from this number. Defaults to 0.
- **maxCounter** - end counting the images at this this number, set it to -1 if
  you want to load until an error during reading occurs. Defaults to -1.
- **loadSingleFile** - true/false, Set to true if just the file specified in
  _singleFile_ should be loaded. Defaults to false.
- **singleFile** - full absolute path to a single image file that should be loaded.

## Dependencies
- [imaging](https://github.com/syxolk/imaging)

## Recommended modules
- [image_converter](https://github.com/syxolk/image_converter) - to convert the read images to other formats
- [camera_renderer](https://github.com/Phibedy/camera_renderer) - to visualize the loaded images
