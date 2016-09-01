#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in float tid;
layout (location = 3) in vec4 color;
layout (location = 4) in float staticObject;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix;
uniform mat4 ml_matrix = mat4(1.0);

out DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} vs_out;

void main() {
	gl_Position = position * ml_matrix * vw_matrix * pr_matrix; //invert because row major? Position * Model * View * Proj
	vs_out.position = position * ml_matrix;
	vs_out.uv = uv;
	vs_out.tid = tid;
	vs_out.color = color;
}
