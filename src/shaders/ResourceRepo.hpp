#pragma once

#include <string>

class ResourceRepo
{
public:
	static std::string ResourcesDirectory()
	{
		return "resources";	
	}
	
	static std::string ShadersDirectory(){
		return ResourcesDirectory() + "/shaders";
	}
	
	static std::string FragmentShader(){
		return ShadersDirectory() + "/fragment.glsl";
	}
	
	static std::string VertexShader(){
		return ShadersDirectory() + "/vertex.glsl";
	}
};