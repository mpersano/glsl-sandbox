uniform float level;

uniform sampler2D from;
uniform sampler2D to;

const float CELL_SIZE = 40;

void main(void)
{
	vec4 c0 = texture2D(from, gl_TexCoord[0].st);
	vec4 c1 = texture2D(to, gl_TexCoord[0].st);

	vec2 p = gl_FragCoord.xy;

	vec2 ps = mod(p, CELL_SIZE);

	vec2 pe = length(p - ps);
	float r = level*(2.*CELL_SIZE - .06*pe);

	float d = distance(ps, .5*vec2(CELL_SIZE, CELL_SIZE));
	float t = smoothstep(r, r + 1, d);

	gl_FragColor = mix(c0, c1, t);
}
