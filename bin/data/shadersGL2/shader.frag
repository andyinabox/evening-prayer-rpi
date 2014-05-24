#version 120

uniform sampler2DRect camera;

varying vec2 texCoordVarying;

uniform float period;
uniform float time;

void main()
{
    vec4 color = texture2DRect(camera, texCoordVarying);
        
    float alpha = (sin(time/period) + 1) / 2;

    color.a = alpha;

    gl_FragColor = color;
}