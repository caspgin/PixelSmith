#version 330 core

in vec3 vertexColor;
in vec2 texCords;

uniform sampler2D texture1;
uniform sampler2D texture2;
out vec4 FragColor;

void main(){
	vec2 newtex = texCords - vec2(0.5f,0.5f);
	FragColor = mix(texture(texture1, texCords), texture(texture2, newtex), 0.2);
}
