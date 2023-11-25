#ifndef MY_TEXTURE_H_
#define MY_TEXTURE_H_

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h> // подключение GLFW
#include "stb_image.h"
#include "loader.h"

class Texture: public v::Loadable
{
private:
	unsigned int m_TextureID;
	std::string m_FilePath;
	unsigned char* m_localBuffer;
	int m_Width, m_Height, m_BPP;
	std::string m_type;
	void Load() override;

public:
	explicit Texture(const std::string& path, const std::string& type = "texture_specular");
	static std::vector<Texture*> m_LoadedTextures;
	static Texture* getTexture(const std::string& path, const std::string& type = "texture_specular");
	static void deleteTextures();

	~Texture();

	void bind(unsigned int slot = 0) const;
	void unBind() const;

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }
	inline std::string getType() const { return m_type; }
	inline std::string getPath() const { return m_FilePath; }
};

#endif // MY_TEXTURE_H_
