uniform vec2 resolution;
uniform float level;

uniform sampler2D from;
uniform sampler2D to;

const vec2 origin = vec2(-500, -100);
const float feather = 400;
const float cell_size = 40;

void main(void)
{
	float l0 = length(origin) - feather;
	float l1 = length(origin) + length(resolution);

	float lm = mix(l0, l1, level);

	vec4 c0 = texture2D(from, gl_TexCoord[0].st);
	vec4 c1 = texture2D(to, gl_TexCoord[0].st);

	vec2 p = gl_FragCoord.xy;

	vec2 ps = mod(p, cell_size);

	float r = cell_size*smoothstep(lm, lm + feather, distance(p - ps, origin));

	float d = distance(ps, .5*vec2(cell_size, cell_size));
	float t = smoothstep(r - 1, r, d);

	gl_FragColor = mix(c0, c1, t);
}
