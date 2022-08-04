#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
//in vec4 fragColor;
in vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;

uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

struct MaterialProperty {
    vec3 color;
    int useSampler;
    sampler2D sampler;
};

struct Light {
    vec3 position;
    vec4 color;
    vec4 ambientStrength;
};

// Input lighting values
uniform Light sun;
uniform vec3 viewPos;

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord);
    vec3 lightDot = vec3(0.0);
    float diff = 0.0f;
    vec3 normal = normalize(fragNormal);
    vec3 viewD = normalize(viewPos - fragPosition);
    vec4 specular = vec4(0.0);

    vec3 lightDir = normalize(sun.position - fragPosition);

    diff = max(dot(normal, lightDir), 0.0);
    lightDot =  diff * sun.color.rgb;
      
    specular = vec4(pow(max(0.0, dot(viewD, reflect(-(lightDir), normal))), 2.0));

    finalColor = (texelColor * ((colDiffuse + specular)  * vec4(lightDot, 1.0)));
    finalColor += texelColor * sun.ambientStrength * colDiffuse;

    // Gamma correction
    finalColor = pow(finalColor, vec4(1.0/2.2));
}
