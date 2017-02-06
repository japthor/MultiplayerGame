#ifndef __ASSETS_H__
#define __ASSETS_H__

#include <string>

namespace ASSETS {
	/**
    * Get an specific image from the path: assets/image.
    * @param image The name of the image.
    * @return The path.
	*/
  std::string ImagePath(char *image);

	/**
	* Get an specific sound from the path: assets/sounds.
	* @param image The name of the sound.
	* @return The path.
	*/
  std::string SoundPath(char *sound);
}

#endif //__ASSETS_H__
