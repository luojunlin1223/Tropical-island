# version 330 core

uniform sampler2D diffuseTex;
uniform vec3 cameraPos;
uniform vec4 lightColour;
uniform vec3 lightPos;

in Vertex {
vec3 colour;
vec2 texCoord;
vec3 normal;
vec3 worldPos;
} IN;

out vec4 fragColour ;
void main ( void ) {
vec3 incident = normalize ( lightPos - IN.worldPos );

vec4 diffuse = texture ( diffuseTex , IN.texCoord);
float lambert = max ( dot ( incident , IN.normal ) , 0.0f );

vec3 surface = ( diffuse . rgb * lightColour . rgb );
fragColour.rgb = surface * lambert;
fragColour.rgb += ( lightColour . rgb)*0.33;
fragColour.rgb += surface * 0.1f; // ambient !
fragColour.a = diffuse.a ;
 }