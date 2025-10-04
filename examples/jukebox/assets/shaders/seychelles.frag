#version 330 core

in vec2 v_uv;

out vec4 outColor;

vec3 blue = vec3(0, 47, 108) / 255.0;
vec3 yellow = vec3(254, 209, 65) / 255.0;
vec3 red = vec3(210, 39, 48) / 255.0;
vec3 white = vec3(1.0);
vec3 green = vec3(0, 122, 51) / 255.0;

void main()
{
    vec2 uv = v_uv;

    vec3 color = blue;
    color = mix(color, yellow, step(1.0, 3.0*uv.x/(1.0*uv.y)));
    color = mix(color, red,    step(1.0, 3.0*uv.x/(2.0*uv.y)));
    color = mix(color, white,  step(1.0, 2.0*uv.x/(3.0*uv.y)));
    color = mix(color, green,  step(1.0, 1.0*uv.x/(3.0*uv.y)));

    outColor = vec4(color, 1.0);
}