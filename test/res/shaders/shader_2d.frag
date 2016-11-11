#version 100

#ifdef GL_ES

precision mediump float;
#define plf_in varying
#define plf_out
#define plf_texture texture2D
#define plf_fragColor gl_FragColor

#else

#define plf_in in
#define plf_out out
#define plf_texture texture
#define plf_fragColor fragColor

#endif

plf_in vec2 Texcoord;
uniform sampler2D tex;

void main()
{
  plf_fragColor = plf_texture(tex, Texcoord);
}
