#pragma once

//currently holding one program at a time and will likely break easily (MUST UPDATE LATER)
//
//will currently use manual linking in order to allow some trickery by using multiple shader managers at once
// 
// idea for later is to make all loaded shaders manageable under one shaderManager object (currently one program requires one object)
// 
// Also currently a lot of wasteful calls are being made when changing shaders, needs optimising later but that means later
//
class shaderManager
{
private:

public:
	unsigned int vs, fs, program;

	//can load both types ('F' for fragment, 'V' for vertex)
	void LoadShader(const char* location, const char& type);
	//attatch and link
	void CreateProgram();

	shaderManager();
	~shaderManager();

	//automatically loads and creates a shader program using the base shaders (add some functionality later for different base shaders)
	void UseBaseShaders();
	void UseProgram() const;
	void Destroy();
};