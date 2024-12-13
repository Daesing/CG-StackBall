#version 330 core

in vec3 FragPos;       // 버텍스 셰이더에서 전달된 프래그먼트 위치
in vec3 Normal;        // 버텍스 셰이더에서 전달된 법선 벡터
in vec3 out_Color;     // 객체 색상

out vec4 FragColor;    // 최종 출력 색상

uniform vec3 lightPos;     // 광원의 위치
uniform vec3 lightColor;   // 광원의 색상
uniform vec3 viewPos;      // 카메라(관찰자)의 위치

void main()
{
    // 주변광
    float ambientLight = 0.3;
    vec3 ambient = ambientLight * lightColor;

    // 난반사 조명
    vec3 normalVector = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuseLight = max(dot(normalVector, lightDir), 0.0);
    vec3 diffuse = diffuseLight * lightColor;

    // 반사광
    int shininess = 128;
    vec3 viewDir = normalize(viewPos - FragPos); // 관찰자 방향
    vec3 reflectDir = reflect(-lightDir, normalVector); // 반사 방향
    float specularLight = max(dot(viewDir, reflectDir), 0.0);
    specularLight = pow(specularLight, shininess);
    vec3 specular = specularLight * lightColor;

    // 최종 색상 계산
    vec3 result = (ambient + diffuse + specular) * out_Color;
    FragColor = vec4(result, 1.0); // 출력
}
