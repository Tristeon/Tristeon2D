#version 140
#include Includes/Actor.incl
#include Includes/Sprite.incl
#include Includes/Camera.incl
 
out vec2 texCoord;
out vec2 worldPos;

const float PI = 3.14159265;
const float toRAD = PI / 180.0f;

void main()
{
    float x = -1.0 + float((gl_VertexID & 1) << 2);
    float y = -1.0 + float((gl_VertexID & 2) << 1);
    texCoord.x = (x+1.0)*0.5;
    texCoord.y = (y+1.0)*0.5;

    x *= actor.scale.x * sprite.width;
    y *= actor.scale.y * sprite.height;

    float rad = actor.rotation * toRAD;
    float rotX = x * cos(rad) - y * sin(rad);
    float rotY = y * cos(rad) + x * sin(rad);
    x = rotX;
    y = rotY;

    x = x / float(camera.displayPixels.x / camera.zoom);
    y = y / float(camera.displayPixels.y / camera.zoom);

    x -= float(camera.position.x) / camera.displayPixels.x * camera.zoom * 2;
    y -= float(camera.position.y) / camera.displayPixels.y * camera.zoom * 2;

    x += actor.position.x / camera.displayPixels.x * camera.zoom * 2;
    y += actor.position.y / camera.displayPixels.y * camera.zoom * 2;

    gl_Position = vec4(x, y, 0, 1);

    worldPos = vec2(x, y) * camera.displayPixels / camera.zoom / 2 + camera.position;
}