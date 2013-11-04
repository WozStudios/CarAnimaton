#version 400 core

uniform sampler2D renderedTexture;

uniform float saturation;
uniform float fade;

out vec4 fragColour;

in vec4 Colour;
in vec4 VColour ;
in vec2 TexCoord ;

vec4 desaturate(vec4 c)
{
	//float desaturated = (0.9 * c.r + 0.5 *c.g + 0.1 * c.b) / 3.0;
	float desaturated = (c.r + c.g + c.b) / 3.0;
	return vec4(desaturated, desaturated, desaturated, 1.0);
}

void blur()
{
	ivec2 ires = textureSize(renderedTexture, 0);
	float ResS = float(ires.s);
	float ResT = float(ires.t);
	vec3 irgb = texture(renderedTexture, TexCoord).rgb;

	vec2 stp0 = vec2(1.0 / ResS, 0.0);
	vec2 st0p = vec2(0.0, 1.0 / ResT);
	vec2 stpp = vec2(1.0 / ResS, 1.0 / ResT);
	vec2 stpm = vec2(1.0 / ResS, -1.0 / ResT);

	vec3 i00 = texture(renderedTexture, TexCoord).rgb;
	vec3 im1m1 = texture(renderedTexture, TexCoord - stpp).rgb;
	vec3 ip1p1 = texture(renderedTexture, TexCoord + stpp).rgb;
	vec3 im1p1 = texture(renderedTexture, TexCoord - stpm).rgb;
	vec3 ip1m1 = texture(renderedTexture, TexCoord + stpm).rgb;

	vec3 im10 = texture(renderedTexture, TexCoord - stp0).rgb;
	vec3 ip10 = texture(renderedTexture, TexCoord + stp0).rgb;
	vec3 i0m1 = texture(renderedTexture, TexCoord - st0p).rgb;
	vec3 i0p1 = texture(renderedTexture, TexCoord + st0p).rgb;

	vec3 target = vec3(0.0, 0.0, 0.0);
	target += 1.0 * (im1m1 + ip1m1 + ip1p1 + im1p1);
	target += 2.0 * (im10 + ip10 + i0m1 + i0p1);
	target += 4.0 * (i00);
	target /= 16.0;
	fragColour = vec4(target, 1.0);
}

void main(void)
{
	ivec2 resolution = textureSize(renderedTexture, 0);

	vec4 colour = texture(renderedTexture, TexCoord);
	vec4 desaturated = desaturate(colour);
	vec4 final = mix(desaturated, colour, saturation);
	vec4 black = vec4(0.0, 0.0, 0.0, 1.0);
	fragColour = mix(black, final, fade);
}