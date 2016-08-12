#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;

in DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D textures[32];

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	vec4 texColor = fs_in.color;
	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);

		//texColor = fs_in.color * texture(textures[tid], fs_in.uv);
		if(tid == 0) texColor = texture(textures[0], fs_in.uv); //fs_in.color *
		if(tid == 1) texColor = texture(textures[1], fs_in.uv); //fs_in.color *
		if(tid == 2) texColor = texture(textures[2], fs_in.uv); //fs_in.color *
		if(tid == 3) texColor = texture(textures[3], fs_in.uv); //fs_in.color *
		if(tid == 4) texColor = texture(textures[4], fs_in.uv); //fs_in.color *
		if(tid == 5) texColor = texture(textures[5], fs_in.uv); //fs_in.color *
		if(tid == 6) texColor = texture(textures[6], fs_in.uv); //fs_in.color *
		if(tid == 7) texColor = texture(textures[7], fs_in.uv); //fs_in.color *
		if(tid == 8) texColor = texture(textures[8], fs_in.uv); //fs_in.color *
		if(tid == 9) texColor = texture(textures[9], fs_in.uv); //fs_in.color *
	}
	color = texColor;// * intensity;
}
