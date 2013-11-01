#version 400 core

uniform sampler2D renderedTexture;

out vec4 fragColour;

in vec4 Colour;
in vec4 VColour ;
in vec2 TexCoord ;

vec4 desaturate()
{
	vec4 c = fragColour;
	
	float desaturated = (0.9 * c.r + 0.5 *c.g + 0.1 * c.b) / 3.0;
	return vec4(desaturated, desaturated, desaturated, 1.0);
}

void main(void)
{
    //vec4 texColour1 = texture(renderedTexture,TexCoord);
 

    //fragColour = texture(renderedTexture,TexCoord);


    fragColour = texture(renderedTexture,TexCoord);
	
	//desaturate();
}