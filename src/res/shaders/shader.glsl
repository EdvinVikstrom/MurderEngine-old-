/*
  in location[0, 1, 2, 3]: vertex
  uniform location {
    0: projection,
    1: view,
    2: model,
    3: diffuseSampler,
    4: specularSampler,
    5: lightPositions,
    6: lightColors
  }
*/

/*
  [0]: type,     { MAP, COLOR, FLOAT }

  *| _______________________________________  |*
  *| TYPE: |   ~MAP~   | ~COLOR~ | ~FLOAT~    |*
  *| [--------------------------------------] |*
  *| [1]:  |  sampler  |  RED    |  float   ] |*
  *| [2]:  | --------- |  GREEN  |  -----   ] |*
  *| [3]:  | --------- |  BLUE   |  -----   ] |*
  *| [4]:  | --------- |  ALPHA  |  -----   ] |*
  *| [--------------------------------------] |*

*/

#vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 color;

layout(location = 0) uniform mat4 projection;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;

out vec3 f_normal;
out vec2 f_texCoord;
out vec4 f_color;
out vec3 f_camera;

void main()
{
  vec4 worldVec = model * position;
  gl_Position = projection * view * model * position;
  f_normal = normal;
  f_texCoord = texCoord;
  f_color = color;
  f_camera = vec3(inverse(view) * vec4(0.0F, 0.0F, 0.0F, 1.0F)) - vec3(worldVec);
}

#fragment
#version 460 core

in vec3 f_normal;
in vec2 f_texCoord;
in vec4 f_color;
in vec3 f_camera;

struct light {
  vec3 position;
  vec3 color;
};

/* diffuse */
layout(location = 3) uniform int diffuseType;
layout(location = 4) uniform sampler2D diffuseSampler;
layout(location = 5) uniform vec4 diffuseColor;

/* specular */
layout(location = 6) uniform int specularType;
layout(location = 7) uniform sampler2D specularSampler;
layout(location = 8) uniform vec4 specularColor;

/* emission */
layout(location = 9) uniform int emissionType;
layout(location = 10) uniform sampler2D emissionSampler;
layout(location = 11) uniform vec4 emissionColor;

/* gloss */
layout(location = 12) uniform int glossType;
layout(location = 13) uniform sampler2D glossSampler;
layout(location = 14) uniform vec4 glossColor;

/* ior */
layout(location = 15) uniform int iorType;
layout(location = 16) uniform sampler2D iorSampler;
layout(location = 17) uniform vec4 iorColor;

layout(location = 18) uniform light lights[8];

layout(location = 0) out vec4 outColor;

vec3 mixColor(vec3 color1, vec3 color2, float fac)
{
  return mix(color1, color2, fac);
}

void main()
{
  vec4 finalDiffuseLight = vec4(0.0F, 0.0F, 0.0F, 1.0F);
  vec4 finalSpecular = vec4(0.0F, 0.0F, 0.0F, 1.0F);

  vec4 specularAmount = specularType == 0 ? texture(specularSampler, f_texCoord) : (specularType == 1 ? specularColor : vec4(0.0F));

  vec3 nNormal = normalize(f_normal);
  vec3 nCamera = normalize(f_camera);

  bool affLight = f_color.x >= 0.0F;

  for (unsigned int i = 0; i < 8 && affLight; i++)
  {
    light lamp = lights[i];
    if (lamp.color.x < 0) continue;
    vec3 nLightDir = normalize(lamp.position);

    float lightPower = max(max(lamp.color.x, lamp.color.y), lamp.color.z);

    float ldot = max(dot(f_normal, nLightDir), 0.05F);
    float dist = abs(distance(lamp.position, f_normal) * 4);
    vec3 diffuseResult = (lamp.color / lightPower) * ldot;

    finalDiffuseLight+=vec4(diffuseResult, 0.0F);

    /* specular */
    vec3 ref = reflect(lamp.position, f_normal);
    float specFac = max(dot(ref, nCamera), 0.0F);
    float damped = pow(specFac, 1.0F);
    finalSpecular+=vec4(lamp.color, 0.0F) * damped;

  }
  if (diffuseType==0)
    outColor = (affLight ? finalDiffuseLight : vec4(1.0F)) * texture(diffuseSampler, f_texCoord);
  else if (diffuseType==1)
    outColor = (affLight ? finalDiffuseLight : vec4(1.0F)) * diffuseColor;
}
#end
