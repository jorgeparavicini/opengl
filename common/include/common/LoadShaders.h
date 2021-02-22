//
// Created by jorge on 31/01/2021.
//

#ifndef OPENGL_LOADSHADERS_H
#define OPENGL_LOADSHADERS_H

#include <GL/glew.h>

typedef struct {
    GLenum type;
    const char* filename;
    GLuint shader;
} ShaderInfo;

GLuint LoadShaders(ShaderInfo*);

#endif //OPENGL_LOADSHADERS_H
