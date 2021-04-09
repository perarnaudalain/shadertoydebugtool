Xcode debugger for https://www.shadertoy.com/

Write or replace your shader between the comments in the file main.cpp

## First launch
Open *.xcodeproj with Xcode

Start the solution

Apple informs you some dylib has been downloaded from GitHub.

<img src="https://github.com/perarnaudalain/shadertoydebugtool/blob/master/image/image1.png?raw=true" width="250" height="250">

To continue, you need to allow dylib

<img src="https://github.com/perarnaudalain/shadertoydebugtool/blob/master/image/image2.png?raw=true" width="400" height="400">

## Add your own shader


```cpp
// Your shader
...
vec4 run(vec2 fragCoord) {
...
}
...
// Your shader
```

## Some warnings
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

Parameter out not allow
```cpp
void myfunction(out vec3 vector) => ko
void myfunction(vec3& vector) => ok
```
