//
//  test.hpp
//  lib
//
//  Created by Alain Perarnaud on 07/04/2021.
//

#ifndef test_hpp
#define test_hpp

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

#define FPS
#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

#include <time.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>
#include <ctime>
#include <syslog.h>
#include <stdarg.h>
#include <zlib.h>
#include <CoreFoundation/CoreFoundation.h>
#include <unistd.h>
#include <libgen.h>
#include <thread>

#include <glm/gtx/transform.hpp>
#include <vector>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace glm;

class Base {
    public:
        static void intialization(int _widthTexture, int _heighTexture, void(*_time)(float));
        static int displayShader(void(*f)(vec4&,vec2));

    private:
        static int widthTexture;
    
        static int heightTexture;
    
        static void(*setTime)(float);
        
        static float iTime;
        
        static unsigned num_cpus;

        static std::chrono::time_point<std::chrono::system_clock> previousTime;

        static int stateKey;

        static void Update();
    
        static void errorCallback(int error, const char* description);
        
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static void frameBufferResizeCallback(GLFWwindow* window, int width, int height);

        static void task1(int posy, char* buffer, void (*f)(vec4&,vec2));
};

#endif /* test_hpp */
