#version 400

uniform vec4 colour ;

in vec4 VertexPosition ;
in vec4 VertexColour;
in vec2 VertexTexCoord ;

out vec4 Colour;
out vec2 TexCoord ;

void main (void)
{
    Colour = VertexColour;
    TexCoord = VertexTexCoord;
    gl_Position = VertexPosition;
}