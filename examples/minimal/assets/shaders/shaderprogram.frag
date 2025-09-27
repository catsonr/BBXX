#version 330 core

in vec2 v_uv;

out vec4 outColor;

void main()
{
    vec2 uv = v_uv; // [0, 1]^2
    uv -= 0.5; // [-0.5, 0.5]^2
    uv *= 2.0; // [-1, 1]^2
    
    uv = ceil(uv);

    outColor = vec4(uv.x, uv.y, 0.0, 1.0);
}