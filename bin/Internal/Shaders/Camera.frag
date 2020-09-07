#version 330
in vec2 texCoord;
uniform sampler2D screenTexture;

out vec4 FragColor;

void main()
{
    if (texCoord.x > 1 || texCoord.y > 1 || texCoord.x < 0 || texCoord.y < 0)
        discard;

    FragColor = texture2D(screenTexture, texCoord);
}