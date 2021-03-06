#version 400 core

uniform sampler2D texture1 ;
uniform sampler2D texture2 ;
uniform sampler2D texture3 ;
uniform sampler2D texture4 ;
uniform sampler2D texture5 ;
uniform sampler2D texture6 ;
uniform sampler2D texture7 ;
uniform sampler2D texture8 ;
uniform sampler2D texture9 ;
uniform sampler2D texture10 ;
uniform sampler2D texture11 ;
uniform sampler2D texture12 ;
uniform sampler2D texture13 ;
uniform sampler2D texture14 ;
uniform sampler2D texture15 ;
uniform sampler2D texture16 ;
uniform sampler2D texture17 ;
uniform sampler2D texture18 ;

uniform float fade;

uniform float time ;
uniform int useTex ;
uniform int useLighting ;

layout(location = 0) out vec4 fragColour;

in vec4 Colour;
in vec4 VColour ;
in vec2 TexCoord ;
in vec3 AmbientDiffuseIntensity ;
in vec3 SpecularIntensity ;

bool isBlue(vec4 vector)
{
	float threshold = 0.2f;

	return  vector.z > threshold;
}

void main(void)
{
    vec4 texColour1 = texture(texture1,TexCoord);
    vec4 texColour2 = texture(texture2,TexCoord);
    vec4 texColour3 = texture(texture3,TexCoord);
    vec4 texColour4 = texture(texture4,TexCoord);
    vec4 texColour5 = texture(texture5,TexCoord);
    vec4 texColour6 = texture(texture6,TexCoord);
    vec4 texColour7 = texture(texture7,TexCoord);
    vec4 texColour8 = texture(texture8,TexCoord);
    vec4 texColour9 = texture(texture9,TexCoord);
    vec4 texColour10 = texture(texture10,TexCoord);
    vec4 texColour11 = texture(texture11,TexCoord);
    vec4 texColour12 = texture(texture12,TexCoord);
    vec4 texColour13 = texture(texture13,TexCoord);
    vec4 texColour14 = texture(texture14,TexCoord);
    vec4 texColour15 = texture(texture15,TexCoord);
    vec4 texColour16 = texture(texture16,TexCoord);
    vec4 texColour17 = texture(texture17,TexCoord);
    vec4 texColour18 = texture(texture18,TexCoord);

    vec4 texColour ;
    
    switch( useTex ) {
        case 1: texColour = texColour1 ; break ;
        case 2: texColour = texColour2 ; break ;
        case 3: texColour = texColour3 ; break ;
        case 4: texColour = texColour4 ; break ;
        case 5: texColour = texColour5 ; break ;
        case 6: texColour = texColour6 ; break ;
        case 7: texColour = texColour7 ; break ;
        case 8: texColour = texColour8 ; break ;
        case 9: texColour = texColour9 ; break ;
        case 10: texColour = texColour10 ; break ;
        case 11: texColour = texColour11 ; break ;
        case 12: texColour = texColour12 ; break ;
        case 13: texColour = texColour13 ; break ;
        case 14: texColour = texColour14 ; break ;
        case 15: texColour = texColour15 ; break ;
        case 16: texColour = texColour16 ; break ;
        case 17: texColour = texColour17 ; break ;
        case 18: texColour = texColour18 ; break ;

        default: texColour = vec4(1.f) ; break;
    } ;
	
	if (useTex == 8 || useTex == 13 ||  useTex == 16 || useTex == 17)
	{
		texColour.a = 1.0 - texColour.b;
		texColour.b = 0.0;
	}

	if (useTex == 17)
	{
		fragColour = vec4(1.0, 0.0, 0.0, 1.0);
	}

    if( useLighting == 1 ) fragColour = texColour*vec4(AmbientDiffuseIntensity,1.0)+vec4(SpecularIntensity,1.0f) ;
    else fragColour = texColour*Colour ;
 
    if( !gl_FrontFacing )
        fragColour = vec4(0,0.0,0.0,1.0) ;
		
	vec4 final = fragColour;
	float alpha = fragColour.a;
	vec4 black = vec4(0.0, 0.0, 0.0, 1.0);
	fragColour = mix(black, final, fade);
	fragColour.a = alpha;
}