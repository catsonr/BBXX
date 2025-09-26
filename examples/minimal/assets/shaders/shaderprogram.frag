#version 330 core

in vec2 v_uv;

out vec4 outColor;

uniform vec2 u_iResolution;

void main()
{
    vec2 throwaway = u_iResolution;

    //vec2 uv = gl_FragCoord.xy / u_iResolution.xy; // screenspace shading
    vec2 uv = v_uv; // objectspace shading

    outColor = vec4(uv, 0.0, 1.0);
}