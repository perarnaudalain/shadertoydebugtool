#include <glm/glm.hpp>
#include <Base.hpp>

using namespace glm;

static int widthTexture = 200;
static int heightTexture = 200;
static float iTime = 0.0;
static vec2 iResolution = vec2(widthTexture, heightTexture);

// Your shader

float pointToSegmentDistance(vec3 m, vec3 A, vec3 B) {
    vec3 AB = B-A;
    float ratio = glm::clamp(dot(AB, m-A) / dot(AB, AB), 0.0f, 1.0f);
    vec3 testPoint = A + AB * ratio;
    return length(m - testPoint);
}

float map(vec3 m) {
    float anim = iTime;
    vec3 A = vec3(cos(anim)*5.f, 0.f, 20.0f+sin(anim)*5.f);
    vec3 B = A + (vec3(0.f, 0.f, 20.f)- A)*2.f;
    float radius = 3.0f;
    return pointToSegmentDistance(m, A, B) - radius;
}

vec3 pal( float t, vec3 a, vec3 b, vec3 c, vec3 d ) {
    return a + b*cos( 6.28318f*(c*t+d) );
}

vec3 spectrum(float n) {
    return pal( n, vec3(0.5,0.5,0.5),vec3(0.5,0.5,0.5),vec3(1.0,1.0,1.0),vec3(0.0,0.33,0.67) );
}

vec4 iridescent(vec3 ray, vec3 m, vec3 normal) {
    vec3 pos = m;
    vec3 ref = reflect(ray, normal);
    vec3 lig = normalize(vec3(.5,1,-.5));
    vec3 dome = vec3(0,1,0);
    vec3 eye = vec3(0,0,-1);

    vec3 perturb = sin(pos * 1.f);
    vec3 color = spectrum( dot(normal + perturb * .05f, eye) * 2.f);

    float specular = clamp(dot(ref, lig), 0.f, 1.f);
    specular = pow((sin(specular * 20.f - 3.f) * .5f + .5f) + .1f, 32.f) * specular;
    specular *= .1f;
    specular += pow(clamp(dot(ref, lig), 0.f, 1.f) + .3f, 8.f) * .1f;

    float shadow = pow(clamp(dot(normal, dome) * .5f + 1.2f, 0.f, 1.f), 3.f);
    color = color * shadow + specular;

    return vec4(color, 1.0f);
}

vec4 computeColor(vec3 ray, vec3 p, vec3 normal, vec3 lightSource) {
    vec3 light = normalize(p-lightSource);
    vec3 light2 = normalize(vec3(-1,1,-8));
    
    float distorsion = -0.6;
    float diffuse = clamp(dot(normal, light2), 0.0f, 1.0f) * 1.;
    vec3 outlight = normalize(light2 + normal * distorsion);
    float scatter = clamp(dot(-ray, outlight), 0.0f, 1.0f) * 0.5;

    vec4 outter_color = vec4(121, 179, 255, 255)/255.f;
    vec4 inner_color  = vec4(0, 179, 255, 255)/255.f;

    vec3 cp = (p - vec3(0.f, 0.0f, +20.0f)) / 20.0f;
    outter_color = vec4(normalize(vec3(cp.x, 1.0-cp.z, cp.x)), 1.0);
    
    outter_color = vec4(normalize(vec3(1.0+cp.x, cp.y*10.0, -cp.z*10.)), 1.0);
    inner_color = outter_color;
    
    vec4 solid_color = outter_color * (0.15f+diffuse) + inner_color * scatter;
    
    vec3 ref = reflect(light2, normal);
    float specular = pow(clamp(dot(ref, ray), 0.0f, 1.0f), 60.0f);
    
    vec4 irri = iridescent(ray, p, normal);

    return mix(solid_color, irri, 0.75f);
}

bool rayMarching(vec3 origin, vec3 ray, vec3& m) {
    const float zFar  = 40.0;

    float marchingDist = 0.0;
    float nbIter          = 0.0;
    for(int i = 0; i<200; i++) {
        m = origin + ray * marchingDist;
        float dist = map(m);
        if(dist < 0.001) {
            return true;
        }
        else {
            marchingDist += dist * 0.75;
            if(marchingDist >= zFar) {
                break;
            }
        }
    }
    return false;
}

vec3 computeNormal(vec3 pos)
{
    vec3 eps = vec3( 0.01, 0.0, 0.0 );
    vec3 nor = vec3(
         map(pos+vec3(eps.x, eps.y, eps.y)) - map(pos-vec3(eps.x, eps.y, eps.y)),
         map(pos+vec3(eps.y, eps.x, eps.y)) - map(pos-vec3(eps.y, eps.x, eps.y)),
         map(pos+vec3(eps.y, eps.y, eps.x)) - map(pos-vec3(eps.y, eps.y, eps.x)));
    return normalize(nor);
}

void mainImage(vec4& fragColor, vec2 fragCoord ) {
    float     ratio             = iResolution.x/iResolution.y;
    vec3     viewportCoord     = vec3(fragCoord/iResolution.y - vec2(ratio/2.0f, 0.5f), 1.f);
    vec3    eye                = vec3(0.0f, 1.25f, -20.185f);
    vec3    ray                = normalize(viewportCoord);
    vec3    p;
    
    vec3    lightSource        = vec3(-20.0, 0.0, 40.0);
    
    if(rayMarching(eye, ray, p)) {
        vec3 normal = computeNormal(p);
        fragColor = computeColor(ray, p, normal, lightSource);
    }
    else {
        fragColor = vec4(0.5, 0, 1.0, 1.0);
    }
}

// Your shader

vec4 run(vec2 fragCoord) {
    vec4 fragColor;
    mainImage(fragColor, fragCoord);
    return fragColor;
}

int main(int argc, char **argv)
{
    Base::intialization(widthTexture, heightTexture, [](float _iTime) {iTime = _iTime;});
    
    int result = Base::displayShader(run);
    if (result != 0) {
        return result;
    }

	return EXIT_SUCCESS;
}

