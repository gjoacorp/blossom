#version 430

layout (location=0) in vec3 position;
uniform mat4 v_matrix;
uniform mat4 m_matrix;
uniform mat4 proj_matrix;
uniform float tf;

out vec4 varying_color;

mat4 buildRotateX(float rad);
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);

mat4 buildTranslate(float x, float y, float z)
{ 
   mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
         0.0, 1.0, 0.0, 0.0,
         0.0, 0.0, 1.0, 0.0,
         x, y, z, 1.0 );
   return trans;
}

mat4 buildRotateX(float rad)
{ 
   mat4 xrot = mat4(1.0, 0.0, 0.0, 0.0,
         0.0, cos(rad), -sin(rad), 0.0,
         0.0, sin(rad), cos(rad), 0.0,
         0.0, 0.0, 0.0, 1.0 );
   return xrot;
}

mat4 buildRotateY(float rad)
{ 
   mat4 yrot = mat4(cos(rad), 0.0, sin(rad), 0.0,
         0.0, 1.0, 0.0, 0.0,
         -sin(rad), 0.0, cos(rad), 0.0,
         0.0, 0.0, 0.0, 1.0 );
   return yrot;
}
mat4 buildRotateZ(float rad)
{ 
   mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
         sin(rad), cos(rad), 0.0, 0.0,
         0.0, 0.0, 1.0, 0.0,
         0.0, 0.0, 0.0, 1.0 );
   return zrot;
}

void main(void)
{ 
   float i = gl_InstanceID + tf;
   float a = sin(203.0 * i/8000.0) * 2003.0;
   float b = sin(301.0 * i/4001.0) * 2001.0;
   float c = sin(400.0 * i/6003.0) * 2005.0;

   mat4 localRotX = buildRotateX(0.1 * tf);
   mat4 localRotY = buildRotateY(0.1 * tf);
   mat4 localRotZ = buildRotateZ(0.1 * tf);
   mat4 localTrans = buildTranslate(a,b,c);

   mat4 newM_matrix = m_matrix * localTrans * localRotX * localRotY * localRotZ;
   mat4 mv_matrix = v_matrix * newM_matrix;

   gl_Position = proj_matrix * mv_matrix * 50.0 * vec4(position, 1.0);
   varying_color = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);


}
