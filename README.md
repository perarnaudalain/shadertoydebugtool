Xcode debugger for https://www.shadertoy.com/

[This shader](https://www.shadertoy.com/view/7s23Dm) has been embedded easily in the tool

 [![](http://img.youtube.com/vi/5C6I1v9yP5c/0.jpg)](http://www.youtube.com/watch?v=5C6I1v9yP5c "")

## First launch
- Open *.xcodeproj with Xcode
- Start the solution
- Use breakpoints

## How to use it

Replace your shader between the comments "// Your shader" in the file main.cpp

```cpp
// Your shader
...
void mainImage(vec4& fragColor, vec2 fragCoord) {
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
