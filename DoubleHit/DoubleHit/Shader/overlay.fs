#version 330

in vec2 fragTexCoord;

out vec4 finalColor;

uniform sampler2D texture0; // Source texture
uniform sampler2D texture1; // Destination texture

vec3 OverlayBlend(vec3 src, vec3 dst) {
    return mix(2.0 * src * dst, 1.0 - 2.0 * (1.0 - src) * (1.0 - dst), step(0.5, dst));
}

void main() {
    vec4 srcColor = texture(texture0, fragTexCoord);
    vec4 dstColor = texture(texture1, fragTexCoord);

    vec3 blendedColor = OverlayBlend(srcColor.rgb, dstColor.rgb);

    finalColor = vec4(blendedColor, 1.0);
}