#version 120

varying vec2 texCoordVarying;

void main()
{

    vec4 position = ftransform();
    gl_Position = ftransform();

    texCoordVarying = gl_MultiTexCoord0.xy;
}