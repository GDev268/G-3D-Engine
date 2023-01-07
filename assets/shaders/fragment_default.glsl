#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float alpha;

void main() {
	//FragColor = vec4(ourColor,1.0f);
	//FragColor = vec4(ourColor,1.0f) * texture(texture1,texCoord);
	FragColor = vec4(ourColor,1.0f) * mix(texture(texture1,texCoord),texture(texture2,texCoord),alpha);
}