precision highp float;

uniform sampler2D video;

varying vec2 texCoordVarying;

uniform float period;
uniform float time;

void main()
{
    vec4 color = texture2D(video, texCoordVarying);

    if((color.r + color.g + color.b)/3.0 > 0.1) {
 	   color.a = (cos(time/period) + 1.0) / 2.0;
    }
    color.r = color.r * ((sin(time) + 1.0) / 2.0);
    color.b = color.b * ((cos(time) + 1.0) / 2.0);

    gl_FragColor = color;
}
