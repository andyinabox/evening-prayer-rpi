#version 120

varying vec2 texCoordVarying;

uniform float time;


void main()
{

    vec4 position = ftransform();

    // the sine wave travels along the x-axis (across the screen),
    // so we use the x coordinate of each vertex for the calculation,
    // but we displace all the vertex along the y axis (up the screen)/
    // float displacementHeight = 100.0;
    // float displacementY = sin((time + (position.x / 200))*percentX) * displacementHeight;
    // float displacementX = sin((time + (position.y / 200))*percentY) * displacementHeight;

    // vec4 modifiedPosition = position;
    // modifiedPosition.y += displacementY;
    // modifiedPosition.x += displacementX;
    gl_Position = position;

    texCoordVarying = gl_MultiTexCoord0.xy;
}