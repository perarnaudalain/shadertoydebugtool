Xcode debugger for https://www.shadertoy.com/

Write or replace your shader between the comments in the file main.cpp

##First launch

Apple informs you some dylib has been downloaded from GitHub.

![](https://github.com/perarnaudalain/shadertoydebugtool/blob/master/image/image1.png?raw=true)

To continue, you need to allow dylib

![](https://github.com/perarnaudalain/shadertoydebugtool/blob/master/image/image2.png?raw=true)

##Add your own shader


```cpp
// Your shader
...
vec4 run(vec2 fragCoord) {
...
}
...
// Your shader
```

##Some warnings
Take care about the type 

```cpp
float variable = 0.2f;
clamp(variable, 0.0, 0.4); => ko
clamp(variable, 0.0f, 0.4f) => ok
```

Some glsl accessor don't exist in gym

```cpp
vec3 vector = vec3(0);
vector.xyy => ko
vec3(vector.x, vector.y, vector.y) => ok
```

parameter out not allow
```cpp
void myfunction(out vec3 vector) => ko
void myfunction(vec3& vector) => ok
```
