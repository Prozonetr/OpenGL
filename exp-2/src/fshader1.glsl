#version 430

out vec4 fColor;
uniform float color_inc;

void main() {

	fColor = vec4( 1.0, 0.0+color_inc, 0.0+color_inc, 0.0 );

}
