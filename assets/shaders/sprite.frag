#version 330 core

in vec2 vUV;
in vec4 vColor;

uniform sampler2D uTextura;
uniform float     uAlpha;

out vec4 fragColor;

void main() {
    vec4 tex = texture(uTextura, vUV);
    fragColor = tex * vColor * vec4(1.0, 1.0, 1.0, uAlpha);
}
