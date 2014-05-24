precision highp float;

uniform sampler2DRect camera;

varying vec2 texCoordVarying;

uniform float period;
uniform float time;

void main()
{
    vec4 color = texture2DRect(camera, texCoordVarying);

    color.a = (cos(time/period) + 1) / 2;
    color.r = color.r * ((sin(time) + 1) / 2);
    color.b = color.b * ((cos(time) + 1) / 2);

    gl_FragColor = color;
}