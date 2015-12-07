uniform sampler2D background;

const float PI = 3.14159265;

uniform vec2 center;
uniform float radius;
uniform float width;

void main(void)
{
	vec2 p = gl_FragCoord.xy;
	float r = distance(p, center);

	vec2 offs;

	if (r < radius - width || r > radius + width) {
		offs = vec2(0., 0.);
	} else {
		float d = cos((radius - r)*PI/width + .5*PI);
		offs = -d*.005*normalize(p - center);
	}

	vec4 color = texture2D(background, gl_TexCoord[0].st + offs);
	gl_FragColor = color;
}
