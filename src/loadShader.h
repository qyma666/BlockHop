#ifndef LOADSHADER_H_INCLUDED
#define LOADSHADER_H_INCLUDED

#include <GL/glew.h>

//! \brief Loads a shader to display images on screen.
//! \param [in] vertPath A filepath of vertex shader
//! \param [in] fragPath A filepath of fragment shader
//! \param [in] layoutLocations A vector of the 'in' parameters for the shader. (Eg. "VertexPos")
//! \param [in] frameLocations A vector of the 'out' parameters for the shader. (Eg. "Colour")
GLuint loadShader(const char *, const char*);

//! \brief Loads a shader to display images on screen.
//! \param [in] vertPath A filepath of vertex shader
//! \param [in] fragPath A filepath of fragment shader
//! \param [in] geomPath A filepath of geometry shader
//! \param [in] layoutLocations A vector of the 'in' parameters for the shader. (Eg. "VertexPos")
//! \return GLuint ID for the shader. Can also be accessed through the global shaders[shaderName].
GLuint loadShaderG(const char *, const char*, const char*);

void deleteShader(GLuint);

#endif // LOADSHADER_H_INCLUDED
