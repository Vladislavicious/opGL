#include "Texture.h"
#include "Renderer.h"

std::vector<Texture*> Texture::m_LoadedTextures = std::vector<Texture*>();

void Texture::Load()
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_localBuffer)
		stbi_image_free(m_localBuffer);
	v::Loadable::Load();
}

Texture* Texture::getTexture(const std::string &path, const std::string &type)
{
	for(unsigned int j = 0; j < Texture::m_LoadedTextures.size(); j++)
	{
		if(std::strcmp(Texture::m_LoadedTextures[j]->getPath().data(), path.c_str()) == 0)
		{
			return Texture::m_LoadedTextures[j];
		}
	}

	auto ptr = new Texture(path, type);
	Texture::m_LoadedTextures.push_back(ptr);
	return Texture::m_LoadedTextures.back();
}

void Texture::deleteTextures()
{
	for (const auto &texture : Texture::m_LoadedTextures)
		delete texture;
	m_LoadedTextures.clear();
}

Texture::Texture(const std::string &path, const std::string &type)
    : m_TextureID(0), m_FilePath(path), m_localBuffer(nullptr),
      m_Width(0), m_Height(0), m_BPP(0), m_type(type)
{
	//v::Loader::addToLoadQueue(this);
	Load();
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_TextureID));
	std::cout << "Texture " << m_FilePath << " deleted\n";
}

void Texture::bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}

void Texture::unBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
