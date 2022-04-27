#version 330
layout(location = 0) in vec3 pos;

out vec4 outColor;

uniform vec4 inputColor;
void main(){
	outColor=inputColor;
	gl_Position=vec4(pos.x,pos.y,pos.z,1.0);	
}