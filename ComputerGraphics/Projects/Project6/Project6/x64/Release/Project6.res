        ��  ��                  /      �� ���     0 
        #version 400

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;

uniform mat4 MVP;
uniform mat4 ViewMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 ShadowMatrix;

out vec3 Position;
out vec3 Normal;
out vec4 ShadowCoord;

void main()
{
  vec4 n4 = ModelViewMatrix*vec4(VertexNormal, 0.0);
  vec4 v4 = ModelViewMatrix*vec4(VertexPosition, 1.0);
  Normal = vec3(n4);
  Position = vec3(v4);
  ShadowCoord = ShadowMatrix * vec4(VertexPosition, 1.0);
  gl_Position = MVP * vec4(VertexPosition, 1.0);
} �      �� ���     0 
        #version 400

in vec3 Position;
in vec3 Normal;
in vec4 ShadowCoord;

uniform sampler2D ShadowMap;
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

out vec4 FragColor;

vec3 ads()
{
  vec4 s4 = ViewMatrix*vec4(Light.Ldir, 0.0);
  vec3 n = normalize(Normal);
  vec3 v = normalize(-Position);
  vec3 s = normalize(-vec3(s4));
  vec3 r = reflect(-s, n);
  float dRate = max(dot(s, n), 0.0);
  float sRate = pow(max(dot(r, v), 0.0), Material.Shininess);
  vec3 difusse = Light.Ld * Material.Kd * dRate;
  vec3 specular = Light.Ls * Material.Ks * sRate;
  return difusse + specular;
}

subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;

subroutine (RenderPassType)
void shadeWithShadow()
{
  vec3 ambient = Light.La * Material.Ka;
  vec3 diffAndSpec = ads();
  float ShadowCoordX = (ShadowCoord.x/ShadowCoord.w) * 0.5 + 0.5;
  float ShadowCoordY = (ShadowCoord.y/ShadowCoord.w) * 0.5 + 0.5;
  float ShadowCoordZ = (ShadowCoord.z/ShadowCoord.w) * 0.5 + 0.5;
  float shadowDepth = (texture(ShadowMap, vec2(ShadowCoordX,ShadowCoordY))).z;
  float shadow = 1.0;
  if(shadowDepth < ShadowCoordZ) shadow = 0;
  FragColor = vec4(shadow * diffAndSpec+ ambient, 1.0);
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