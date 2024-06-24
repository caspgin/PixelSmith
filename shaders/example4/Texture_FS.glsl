#version 330 core

in vec3 vertexColor;
in vec2 texCords;

uniform sampler2D mainTexture;
out vec4 FragColor;

void main(){
	FragColor = texture(mainTexture, texCords);
}
