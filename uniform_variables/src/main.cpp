//
// Created by jorge on 17/02/2021.
//

#include <GL/glew.h>
#include <iostream>
#include <common/LoadShaders.h>

/* Helper function to convert GLSL types to storage sizes */
size_t TypeSize(GLenum type) {
    size_t size;

#define CASE(Enum, Count, Type) \
                                case Enum: size = Count * sizeof(Type); break
    switch (type) {
        CASE(GL_FLOAT, 1, GLfloat);
        CASE(GL_FLOAT_VEC2, 2, GLfloat);
        CASE(GL_FLOAT_VEC3, 3, GLfloat);
        CASE(GL_FLOAT_VEC4, 4, GLfloat);
        CASE(GL_INT, 1, GLint);
        CASE(GL_INT_VEC2, 2, GLint);
        CASE(GL_INT_VEC3, 3, GLint);
        CASE(GL_INT_VEC4, 4, GLint);
        CASE(GL_UNSIGNED_INT, 1, GLuint);
        CASE(GL_UNSIGNED_INT_VEC2, 2, GLuint);
        CASE(GL_UNSIGNED_INT_VEC3, 3, GLuint);
        CASE(GL_UNSIGNED_INT_VEC4, 4, GLuint);
        CASE(GL_BOOL, 1, GLboolean);
        CASE(GL_BOOL_VEC2, 2, GLboolean);
        CASE(GL_BOOL_VEC3, 3, GLboolean);
        CASE(GL_BOOL_VEC4, 4, GLboolean);
        CASE(GL_FLOAT_MAT2, 4, GLfloat);
        CASE(GL_FLOAT_MAT2x3, 6, GLfloat);
        CASE(GL_FLOAT_MAT2x4, 8, GLfloat);
        CASE(GL_FLOAT_MAT3, 9, GLfloat);
        CASE(GL_FLOAT_MAT3x2, 6, GLfloat);
        CASE(GL_FLOAT_MAT3x4, 12, GLfloat);
        CASE(GL_FLOAT_MAT4, 16, GLfloat);
        CASE(GL_FLOAT_MAT4x2, 8, GLfloat);
        CASE(GL_FLOAT_MAT4x3, 12, GLfloat);
#undef CASE
        default:
            std::cerr << "Unknown type: 0x" << type << std::endl;
            exit(EXIT_FAILURE);
    }
    return size;
}

void init() {
    glClearColor(1, 0, 0, 1);

    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER,   "shaders/shader.vert"},
            {GL_FRAGMENT_SHADER, "shaders/shader.frag"},
            {GL_NONE,            nullptr}
    };

    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    /* Initialize uniform values in uniform block "Uniforms" */
    GLuint uboIndex;
    GLint uboSize;
    GLuint ubo;
    GLvoid *buffer;

    /* Find the uniform buffer index for "Uniforms", and determine the block's sizes */
    uboIndex = glGetUniformBlockIndex(program, "Uniforms");

    glGetActiveUniformBlockiv(program, uboIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);

    buffer = malloc(uboSize);

    if (buffer == nullptr) {
        std::cerr << "Unable to allocate buffer" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        enum {
            Translation, Scale, Rotation, Enabled, NumUniforms
        };

        /* Values to be stored in the buffer object */
        GLfloat translation[] = {0.1f, 0.1f, 0.0f};
        GLfloat scale = 0.5;
        GLfloat rotation[] = {90, 0.0, 0.0, 1.0};
        GLboolean enabled = GL_TRUE;

        /* Since we know the names of the uniforms in our block, make an array of those values */
        const char *names[NumUniforms] = {
                "translation", "scale", "rotation", "enabled"
        };

        /* Query the necessary attributes to determine where in the buffer we should write the values */
        GLuint indices[NumUniforms];
        GLint size[NumUniforms];
        GLint offset[NumUniforms];
        GLint type[NumUniforms];

        glGetUniformIndices(program, NumUniforms, names, indices);
        glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_OFFSET, offset);
        glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_SIZE, size);
        glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_TYPE, type);

        //memcpy(buffer + offset[Scale], &scale, size[Scale] * TypeSize(type[Scale]));
    }
}

int main(int argc, char **argv) {
    std::cerr << "Not implemented" << std::endl;
    return -1;
}