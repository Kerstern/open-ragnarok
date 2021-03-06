/* $Id$ */
#ifndef __TEXTUREMANAGER_H
#define __TEXTUREMANAGER_H

#include "file_manager.h"
#include "ro_object_cache.h"
#include "sdle/image.h"
#include "sdle/texture.h"

#include <string>
#include <map>
#include <list>

class TextureManager {
protected:
	typedef std::map<std::string, sdle::Texture> tex_t;
	tex_t textures;
public:
	TextureManager();
	~TextureManager();

	void Clear();

	sdle::Texture Register(FileManager&, const std::string& name);
	sdle::Texture RegisterPNG(FileManager&, const std::string& name);
	sdle::Texture RegisterJPEG(FileManager&, const std::string& name);
	sdle::Texture RegisterTGA(FileManager&, const std::string& name);
	sdle::Texture Register(const std::string& name, const sdle::Image& img);
	sdle::Texture Register(const std::string& name, const sdle::Texture& t);
	bool UnRegister(const std::string& name);
	bool IsRegistered(const std::string& name) const;
	bool Activate(const std::string& name) const;

	sdle::Texture operator [](const std::string& name) const;
};

#endif /* __TEXTUREMANAGER_H */
