#include "Shader.hpp"

Shader::Shader(const char* vertexShaderPath,const char* fragmentShaderPath){
	GLuint vertexShader = compileShader(vertexShaderPath,GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentShaderPath,GL_FRAGMENT_SHADER);
	
	id = glCreateProgram();
	glAttachShader(id,vertexShader);
	glAttachShader(id,fragmentShader);
	glLinkProgram(id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{

}

void Shader::activate(){
    glUseProgram(id);
}

std::string Shader::loadShaderSrc(const char *filepath)
{
	std::ifstream file;
	std::stringstream buf;

	std::string ret = "";

	file.open(filepath);

	if (file.is_open())
	{
		buf << file.rdbuf();
		ret = buf.str();
	}
	else
	{
		std::cout << "Could not open " << filepath << std::endl;
	}

	file.close();

	return ret;
}

GLuint Shader::compileShader(const char* filepath,GLenum type){
	GLuint curShader = glCreateShader(type);
	std::string shaderSrc = loadShaderSrc(filepath);
	const GLchar* shader = shaderSrc.c_str();
	glShaderSource(curShader,1,&shader,NULL);
	glCompileShader(curShader);

	checkCompilation(curShader);
	return curShader;
}

void Shader::checkCompilation(GLuint shader){
    int success;
	char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Error with vertex shader comp.:" << std::endl
				  << infoLog << std::endl;
	}
}

void Shader::setValue(const std::string &name, bool value)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()),(int)value);
}

void Shader::setValue(const std::string &name, int value)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()),value);
}

void Shader::setValue(const std::string &name, float value)
{
	glUniform1f(glGetUniformLocation(id, name.c_str()),value);
}

void Shader::setValue(const std::string &name, float value1, float value2, float value3, float value4)
{
	glUniform4f(glGetUniformLocation(id, name.c_str()),value1,value2,value3,value4);
}

void Shader::setValue(const std::string &name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
