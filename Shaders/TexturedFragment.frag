#version 330 core

uniform sampler2D diffuseTex ;//贴图用的是sampler2D 一个着色器可以使用多于一个纹理
uniform sampler2D bumpTex;

uniform vec3 cameraPos ;
uniform vec4 lightColour ;
uniform vec3 lightPos ;
uniform float lightRadius ;

in Vertex {
vec2 texCoord ;
vec3 normal ;
vec3 tangent;
vec3 binormal;
vec3 worldPos ;
} IN ;

out vec4 fragColour ;
void main ( void ) {
	float gamma=2.2;

	vec3 incident = normalize ( lightPos - IN . worldPos );
	vec3 viewDir = normalize ( cameraPos - IN . worldPos );
	vec3 halfDir = normalize ( incident + viewDir );
	mat3 TBN = mat3 ( normalize ( IN . tangent ) ,normalize ( IN . binormal ) , normalize ( IN . normal )); 
	vec3 bumpNormal = texture ( bumpTex , IN . texCoord). rgb ;
	bumpNormal = normalize ( TBN * normalize ( bumpNormal * 2.0 - 1.0));
	float lambert = max ( dot ( incident , bumpNormal ) , 0.0f );//把bump map使用上了
	float distance = length ( lightPos - IN . worldPos );
	float attenuation = 1.0f - clamp ( distance / lightRadius ,0.0 ,1.0);
	float specFactor = clamp ( dot ( halfDir , bumpNormal ) ,0.0 ,1.0);
	specFactor = pow ( specFactor , 60.0 ); 
	vec4 diffuse =pow(texture ( diffuseTex, IN . texCoord), vec4(gamma));

	vec3 surface = ( diffuse . rgb * lightColour . rgb );
	fragColour . rgb = surface * lambert * attenuation ;
	fragColour . rgb += ( lightColour . rgb * specFactor )* attenuation *0.33;
	fragColour . rgb += surface * 0.1f ;
	fragColour . rgb = pow(fragColour.rgb , vec3(1.0/gamma));
	fragColour . a = diffuse . a ;
	if(fragColour.a<0.1){
			discard;
		}
}
