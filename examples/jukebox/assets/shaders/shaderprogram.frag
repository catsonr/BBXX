#version 330 core

in vec2 v_uv;

out vec4 outColor;

uniform float u_t;

void main()
{
    vec2 uv = v_uv; // [0, 1]^2
    uv -= 0.5; // [-0.5, 0.5]^2
    uv *= 2.0; // [-1, 1]^2
    
    float a = (0.0 - u_t) * (3.1415925 / 180.0);
    mat2 A = mat2(
        cos(a), -sin(a),
        sin(a), cos(a)
    );
    uv *= A;
    
    uv = ceil(uv);

    outColor = vec4(uv.x, uv.y, 0.0, 1.0);
}