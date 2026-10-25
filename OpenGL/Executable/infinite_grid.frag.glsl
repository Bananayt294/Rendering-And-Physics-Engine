#version 330 core

in vec3 worldPos;
out vec4 FragColor;

void main()
{
    vec2 coord = worldPos.xz;

    vec2 derivative = max(fwidth(coord), vec2(0.0001));

    vec2 gridDist =
        abs(fract(coord - 0.5) - 0.5) / derivative;

    float line = 1.0 - min(
        min(gridDist.x, gridDist.y),
        1.0
    );

    if (line < 0.05) {
        discard;
    }

    FragColor = vec4(vec3(0.45), line);
}