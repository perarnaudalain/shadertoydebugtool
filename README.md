Xcode debugger for https://www.shadertoy.com/

Write or replace your shader between the comments in the file main.cpp

```cpp
// Your shader
...
vec4 run(vec2 fragCoord) {
...
}
...
// Your shader
```

Warning :
Take care about the type 
For example :
```cpp
float variable = 0.2f;
clamp(variable, 0.0, 0.4); => ko
clamp(variable, 0.0f, 0.4f) => ok
```

```cpp
vec3 vector = vec3(0);
vector.xyy => ko
vec3(vector.x, vector.y, vector.y) => ok
```
