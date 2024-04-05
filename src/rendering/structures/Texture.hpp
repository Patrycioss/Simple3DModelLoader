#pragma once
#include <string>

class Texture
{
private:
	unsigned int textureHandle{};
	bool cleaned = false;
	std::string type;
	std::string path;

public:
	Texture(Texture& texture);
	Texture();
	void Bind() const;
	const unsigned int& GetID() const;
	static Texture Load(const std::string& path);
	void Cleanup();
};
