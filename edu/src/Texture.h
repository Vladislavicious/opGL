#ifndef MY_TEXTURE_H_
#define MY_TEXTURE_H_

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h> // подключение GLFW
#include "stb_image.h"

class Texture
{
private:
	unsigned int m_TextureID;
	std::string m_FilePath;
	unsigned char* m_localBuffer;
	int m_Width, m_Height, m_BPP;
	std::string m_type;
public:
	Texture(const std::string& path, const std::string& type = "texture_specular");
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unBind() const;

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }
	inline std::string getType() { return m_type; }
};

#endif // MY_TEXTURE_H_
