        ��  ��                  �      �� ���     0 
        #version 400

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec2 VertexTexCoord;

uniform mat4 MVP;
uniform mat4 ViewMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 ShadowMatrix;
uniform bool DrawSkybox;

out vec3 Position;
out vec3 Normal;
out vec4 ShadowCoord;
out vec2 TexCoord;

void main()
 {
   if(DrawSkybox)
   {
     Normal = vec3(1.0,0.0,0.0);
     TexCoord = vec2(0.0,0.0);
     gl_Position = vec4(VertexPosition,1.0);
     Position = vec3(MVP * gl_Position);
     Position = normalize(Position);
   }
   else
   {
     vec4 n4 = ModelViewMatrix*vec4(VertexNormal, 0.0);
     vec4 v4 = ModelViewMatrix*vec4(VertexPosition, 1.0);
     Normal = vec3(n4);
     Position = vec3(v4);
     TexCoord = VertexTexCoord;

     // Shader
     ShadowCoord = ShadowMatrix * vec4(VertexPosition, 1.0);

     gl_Position = MVP * vec4(VertexPosition, 1.0);
   }
 }Q      �� ���     0 
        #version 400

 in vec3 Position;
 in vec3 Normal;
 in vec2 TexCoord;
 in vec4 ShadowCoord;

 uniform sampler2D ShadowMap;
 uniform sampler2D BaseTex;
 uniform mat4 ViewMatrix;

 struct LightInfo {
	vec3 Ldir;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
 };
 uniform LightInfo Light;

 struct MaterialInfo{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
 };

 uniform MaterialInfo Material;

 vec3 ads(vec3 TexColor) {
   	vec4 s4 = ViewMatrix*vec4(Light.Ldir, 0.0);
	vec3 n = normalize(Normal);
	vec3 v = normalize(-Position);
	vec3 s = normalize(-vec3(s4));
	vec3 r = reflect(-s, n);
	float dRate = max(dot(s, n), 0.0);
	float sRate = pow(max(dot(r, v), 0.0), Material.Shininess);
	vec3 difusse = Light.Ld * Material.Kd * dRate;
	vec3 specular = Light.Ls * Material.Ks * sRate;
	return difusse*TexColor + specular;
 }

 out vec4 FragColor;
 uniform samplerCube CubemapTex;
 uniform bool DrawSkybox;

 subroutine void RenderPassType();
 subroutine uniform RenderPassType RenderPass;

 subroutine (RenderPassType)
 void shadeWithShadow()
 {
   if(DrawSkybox)
   {
     FragColor = texture(CubemapTex,Position);
   }
   else
   {
     vec4 TexColor = texture(BaseTex,TexCoord);
     vec3 ambient = Light.La * Material.Ka * TexColor.rgb;
     vec3 diffAndSpec = ads(TexColor.rgb);
     float ShadowCoordX = (ShadowCoord.x/ShadowCoord.w) * 0.5 + 0.5;
     float ShadowCoordY = (ShadowCoord.y/ShadowCoord.w) * 0.5 + 0.5;
     float ShadowCoordZ = (ShadowCoord.z/ShadowCoord.w) * 0.5 + 0.5;
     float shadowDepth = (texture(ShadowMap, vec2(ShadowCoordX,ShadowCoordY))).z;
     float shadow = 1.0;
     if(shadowDepth < ShadowCoordZ) shadow = 0;
     FragColor = vec4(shadow * diffAndSpec+ ambient, TexColor.a);
   }
 }

 subroutine (RenderPassType)
 void recordDepth()
 {
 }

 void main()
 {
   RenderPass();
 }
   