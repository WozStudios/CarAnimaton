#version 400 core

uniform sampler2D texture1 ;
uniform sampler2D texture2 ;
uniform sampler2D texture3 ;


uniform float time ;
uniform int useTex ;
uniform int useLighting ;


out vec4 fragColour;

in vec4 Colour;
in vec4 VColour ;
in vec2 TexCoord ;
in vec3 AmbientDiffuseIntensity ;
in vec3 SpecularIntensity ;


void main(void)
{

	
    vec4 texColour1 = texture(texture1,TexCoord);
    vec4 texColour2 = texture(texture2,TexCoord);
    vec4 texColour3 = texture(texture3,TexCoord);
    vec4 texColour ;
    
    switch( useTex ) {
        case 1: texColour = texColour1 ; break ;
        case 2: texColour = texColour2 ; break ;
        case 3: texColour = texColour3 ; break ;
        case 12: texColour = texColour1*texColour2 ; break ;
        case 13: texColour = texColour1*texColour3 ; break ;
        case 23: texColour = texColour2*texColour3 ; break ;
        case 123: texColour = texColour1*texColour2*texColour3 ; break ;
		case 100: texColour = VColour ;
        default: texColour = vec4(1.f) ; break;
    } ;
 
    if( useLighting == 1 ) fragColour = texColour*vec4(AmbientDiffuseIntensity,1.0)+vec4(SpecularIntensity,1.0f) ;
    else fragColour = texColour*Colour ;
 
    if( !gl_FrontFacing )
        fragColour = vec4(0,1.0,1.0,1.0) ;
}