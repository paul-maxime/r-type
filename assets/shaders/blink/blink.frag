uniform sampler2D sceneTex;
uniform float blink_alpha;

void main()
{
    vec4 pixel = gl_Color;
    pixel.a = blink_alpha;
    gl_FragColor = pixel;
}