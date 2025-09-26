#version 330 core

layout(location = 0) in vec3 a_pos; // 3d vertex positions

uniform mat4 u_mModel;
uniform mat4 u_mVP;

out vec2 v_uv;

void main()
{
    gl_Position = u_mVP * u_mModel * vec4(a_pos, 1.0);
    
    v_uv = (a_pos.xy * 0.5) + 0.5; // map from [-1, +1] to [0, 1]
}