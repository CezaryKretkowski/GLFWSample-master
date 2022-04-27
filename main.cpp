#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "dependeces/Common/Initialize.h"
#include <glm/glm.hpp>

using namespace glm;

#include "dependeces/Common/objloader.hpp"
#include "dependeces/Common/shader.hpp"

float vertices[] = {1.0f, -1.0f, 0.0f,
                    -1.0f, -1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f};

float normals[] = {0.0f, 1.0f, 0.0f,
                   0.0f, 1.0f, 0.0f,
                   0.0f, 1.0f, 0.0f};

int main()
{ // inicjalizacja okna{
    GLFWwindow *okno = initGLFW(800, 600, "Tytul", NULL, NULL);

    if (okno)
        initGLEW();
    //}
    // wczytywanie shaderów{
    GLuint programid = LoadShaders("../../shaders/verShader.glsl", "../../shaders/fragShaders.glsl");
    GLuint colorId = glGetUniformLocation(programid, "inputColor");
    unsigned int verid;
    glGenVertexArrays(1, &verid);
    glBindVertexArray(verid);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        // główna pętla
    printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
    do
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programid);
        glUniform4f(colorId, 0.0f, 1.0f, 1.0f, 1.0f);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)0 // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

        glDisableVertexAttribArray(0);

        glfwSwapBuffers(okno);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(okno, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(okno) == 0);

    glDeleteShader(programid);
    glfwTerminate();

    return 0;
}
