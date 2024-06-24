#version 330 core

in vec3 vertexColor;
in vec2 texCords;

uniform sampler2D texture1;
uniform sampler2D texture2;
out vec4 FragColor;

void main(){
	FragColor = mix(texture(texture1, texCords), texture(texture2, vec2(1-texCords.x,texCords.y)), 0.2);
}
