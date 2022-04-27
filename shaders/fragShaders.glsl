#version 330
in vec4 outColor;
out vec3 color;
void main(){
    color = outColor.xyz;
}