#version 330

in vec4 vPosition1;
uniform vec3 theta;
uniform float scale;
uniform vec2 xy;

mat4 scaleByHalf(){
	return mat4(scale,0.0,0.0,0.0,
							0.0,scale,0.0,0.0,
							0.0,0.0,scale,0.0,
							0.0,0.0,0.0,1.0 );
}

mat4 translation(){
	return mat4(1,0,0,0,
							0,1,0,0,
							0,0,1,0,
							xy.x,xy.y,0,1 );
}

void main() {

	vec3 angles = radians( theta );
	vec3 c = cos( angles );
	vec3 s = sin( angles );

	mat4 rz = mat4( c.z, -s.z, 0.0, 0.0,
	s.z, c.z, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0 );

	rz[2][2] = 1.0;


	gl_Position = translation() * rz * scaleByHalf() * vPosition1 ;

}
