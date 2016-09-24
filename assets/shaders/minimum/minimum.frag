uniform sampler2D sceneTex;

void main()
{
        vec4 pixel = texture2D(sceneTex, gl_TexCoord[0].xy);


        gl_FragColor = gl_Color * pixel;
}