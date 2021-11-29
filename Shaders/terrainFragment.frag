#version 330 core

uniform sampler2D diffuseTex ;//贴图用的是sampler2D 一个着色器可以使用多于一个纹理
uniform samplerCube cubeTex ;
uniform sampler2D waterTex;
uniform sampler2D bumpTex ;
uniform sampler2D beachTex;

uniform vec3 cameraPos ;
uniform vec4 lightColour ;
uniform vec3 lightPos ;
uniform float lightRadius ;

in Vertex {
vec4 colour;
vec2 texCoord_water ;
vec2 texCoord_terrain;
vec3 normal ;
vec3 tangent;
vec3 binormal;
vec3 worldPos ;
vec3 position;
} IN ;

out vec4 fragColour ;
void main ( void ) {
	vec3 incident = normalize ( lightPos - IN . worldPos );
	vec3 viewDir = normalize ( cameraPos - IN . worldPos );
	vec3 halfDir = normalize ( incident + viewDir );
	mat3 TBN = mat3 ( normalize ( IN . tangent ) ,
	normalize ( IN . binormal ) , normalize ( IN . normal )); 
	vec3 bumpNormal = texture ( bumpTex , IN . texCoord_terrain ). rgb ;
	bumpNormal = normalize ( TBN * normalize ( bumpNormal * 2.0 - 1.0));

	float lambert = max ( dot ( incident , bumpNormal ) , 0.0f );//把bump map使用上了
	float distance = length ( lightPos - IN . worldPos );
	float attenuation = 1.0f - clamp ( distance / lightRadius ,0.0 ,1.0);

	float specFactor = clamp ( dot ( halfDir , bumpNormal ) ,0.0 ,1.0);
	specFactor = pow ( specFactor , 60.0 ); 

	float height=IN.position.y;

	if(height==0){
		vec4 diffuse = texture ( waterTex, IN . texCoord_water);
		vec3 viewDir = normalize ( cameraPos - IN . worldPos );

		vec3 reflectDir = reflect ( - viewDir , normalize ( IN . normal ));
		vec4 reflectTex = texture ( cubeTex , reflectDir );

		fragColour = reflectTex + ( diffuse * 0.25f );


	}else{
		if(height<40){

			vec4 diffuse =mix(texture ( diffuseTex, IN . texCoord_terrain ),texture ( beachTex, IN . texCoord_terrain ),0.5);
			vec3 surface = ( diffuse . rgb * lightColour . rgb );
			fragColour . rgb = surface * lambert * attenuation ;
			fragColour . rgb += ( lightColour . rgb * specFactor )* attenuation *0.33;
			fragColour . rgb += surface * 0.1f ;
			fragColour . a = diffuse . a ;
		}

		else{
			vec4 diffuse =texture ( diffuseTex, IN . texCoord_terrain);

			vec3 surface = ( diffuse . rgb * lightColour . rgb );
			fragColour . rgb = surface * lambert * attenuation ;
			fragColour . rgb += ( lightColour . rgb * specFactor )* attenuation *0.33;
			fragColour . rgb += surface * 0.1f ;
			fragColour . a = diffuse . a ;
		}
	}

}
