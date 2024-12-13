#version 330 core

//--- in_Position: attribute index 0
//--- in_Color: attribute index 1

layout (location = 0) in vec3 in_Position;	//---위치 변수: attribute position 0
layout (location = 1) in vec3 vNormal;		
layout (location = 2) in vec3 in_Color;		//---컬러 변수: attribute position 2


out vec3 FragPos;
out vec3 out_Color;
out vec3 Normal;

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4 (in_Position.x, in_Position.y, in_Position.z, 1.0);	
	
	FragPos = vec3(modelTransform * vec4(in_Position, 1.0));

	out_Color = in_Color;						

	Normal = vNormal;
}