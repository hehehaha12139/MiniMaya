#version 150
// ^ Change this to version 130 if you have compatibility issues

//This is a vertex shader. While it is called a "shader" due to outdated conventions, this file
//is used to apply matrix transformations to the arrays of vertex data passed to it.
//Since this code is run on your GPU, each vertex is transformed simultaneously.
//If it were run on your CPU, each vertex would have to be processed in a FOR loop, one at a time.
//This simultaneous transformation allows your program to run much faster, especially when rendering
//geometry with millions of vertices.

uniform mat4 u_Model;       // The matrix that defines the transformation of the
                            // object we're rendering. In this assignment,
                            // this will be the result of traversing your scene graph.

uniform mat4 u_ModelInvTr;  // The inverse transpose of the model matrix.
                            // This allows us to transform the object's normals properly
                            // if the object has been non-uniformly scaled.

uniform mat4 u_ViewProj;    // The matrix that defines the camera's transformation.
                            // We've written a static matrix for you to use for HW2,
                            // but in HW3 you'll have to generate one yourself
uniform mat2x4 u_BindMatrices[100];

uniform mat2x4 u_TransformQuat[100];

uniform mat4 u_BindMatricesMat[100];

in vec4 vs_Pos;             // The array of vertex positions passed to the shader

in vec4 vs_Nor;             // The array of vertex normals passed to the shader

in vec4 vs_Col;             // The array of vertex colors passed to the shader.

in vec4 vs_Wgt;

in ivec4 vs_WgtIdx;

out vec3 fs_Pos;
out vec4 fs_Nor;            // The array of normals that has been transformed by u_ModelInvTr. This is implicitly passed to the fragment shader.
out vec4 fs_Col;            // The color of each vertex. This is implicitly passed to the fragment shader.
out vec4 fs_Wgt;

float FLT_EPSILON = 1.192092896e-07F;

vec4 quaternionMulti(vec4 q1, vec4 q2)
{
    float s = q1[0] * q2[0] + dot(vec3(q1[1], q1[2], q1[3]), vec3(q2[1], q2[2], q2[3]));
    vec3 v = q1[0] * vec3(q2[1], q2[2], q2[3]) + q2[0] * vec3(q1[1], q1[2], q1[3])
            + cross(vec3(q1[1], q1[2], q1[3]), vec3(q2[1], q2[2], q2[3]));
    return vec4(s, v[0], v[1], v[2]);
}

vec4 quaternionConj(vec4 q)
{
    return vec4(q[0], -q[1], -q[2],-q[3]);
}

mat2x4 dualQuaternionMulti(vec4 q1R, vec4 q1T, vec4 q2R, vec4 q2T)
{
    vec4 resultR = quaternionMulti(q1R, q2R);
    vec4 resultT = quaternionMulti(q1R, q2T) + quaternionMulti(q1T, q2R);
    return mat2x4(resultR, resultT);
}

mat2x4 dualQuaternionConjugation(mat2x4 dQ)
{
    vec4 dQR = dQ[0];
    vec4 dQT = dQ[1];
    return mat2x4(
                vec4(dQR[0], -dQR[1], -dQR[2], -dQR[3]),
                vec4(dQT[0], -dQT[1], -dQT[2], -dQT[3])
                );
}

float dualQuaternionLength(mat2x4 dQ)
{
    return length(dQ[0]);
}

mat4 dualQuaternionToMat4(mat2x4 dQ)
{
    // Rotation
    vec4 rot = vec4(dQ[0][0], dQ[0][1], dQ[0][2], dQ[0][3]);
    vec4 rotTrans = dQ[0];
    vec4 trans = dQ[1];
    mat3 rotMat = mat3(
                vec3(1 - 2 * pow(rot[2], 2) - 2 * pow(rot[3], 2),
                          2 * rot[1] * rot[2] - 2 * rot[0] * rot[3],
                          2 * rot[0] * rot[2] + 2 * rot[1] * rot[3]),
                vec3(2 * rot[0] * rot[3] + 2 * rot[1] * rot[2],
                          1 - 2 * pow(rot[1], 2) - 2 * pow(rot[3], 2),
                          2 * rot[2] * rot[3] - 2 * rot[0] * rot[1]),
                vec3(2 * rot[1] * rot[3] - 2 * rot[0] * rot[2],
                          2 * rot[0] * rot[1] + 2 * rot[2] * rot[3],
                          1 - 2 * pow(rot[1], 2) - 2 * pow(rot[2], 2))
                );
    float transX = 2 * (trans[0] * rotTrans[1] + trans[1] * rotTrans[0] - trans[2] * rotTrans[3] + trans[3] * rotTrans[2]);
    float transY = 2 * (trans[0] * rotTrans[2] + trans[1] * rotTrans[3] - trans[2] * rotTrans[0] + trans[3] * rotTrans[1]);
    float transZ = 2 * (trans[0] * rotTrans[3] + trans[1] * rotTrans[2] - trans[2] * rotTrans[1] + trans[3] * rotTrans[0]);
    return mat4(
                vec4(rotMat[0][0], rotMat[0][1], rotMat[0][2], transX),
                vec4(rotMat[1][0], rotMat[1][1], rotMat[1][2], transY),
                vec4(rotMat[2][0], rotMat[2][1], rotMat[2][2], transZ),
                vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

void main()
{
    bool isWeighted = true;
    fs_Col = vs_Col;                         // Pass the vertex colors to the fragment shader for interpolation

    mat3 invTranspose = mat3(u_ModelInvTr);
    fs_Nor = vec4(invTranspose * vec3(vs_Nor), 0);          // Pass the vertex normals to the fragment shader for interpolation.
                                                            // Transform the geometry's normals by the inverse transpose of the
                                                            // model matrix. This is necessary to ensure the normals remain
                                                            // perpendicular to the surface after the surface is transformed by
                                                            // the model matrix.


    mat2x4 qSum = mat2x4(
                vec4(1, 0, 0, 0),
                vec4(0, 0, 0, 0)
                );
    for(int i = 0; i < 2; i++)
    {
        int index = vs_WgtIdx[i];

        mat2x4 bindValue = mat2x4(
                        vec4(u_BindMatrices[index][0][3],
                             u_BindMatrices[index][0][0],
                             u_BindMatrices[index][0][1],
                             u_BindMatrices[index][0][2]),
                        vec4(u_BindMatrices[index][1][3],
                             u_BindMatrices[index][1][0],
                             u_BindMatrices[index][1][1],
                             u_BindMatrices[index][1][2])
                    );
//        if(dot(qSum[0], bindValue[0]) < 0)
//        {
//            bindValue[0] = vec4(-bindValue[0][0], bindValue[0][1], bindValue[0][2], bindValue[0][3]);
//        }
        qSum += vs_Wgt[i] * bindValue;
    }

    mat2x4 normalizedDq = qSum / dualQuaternionLength(qSum);
    vec4 modelposition = vec4(0.0f);
    modelposition = u_Model * vs_Pos;
    mat4 skeletonTransform = dualQuaternionToMat4(normalizedDq);
    modelposition = u_Model * skeletonTransform * vs_Pos;


    //fs_Col = vec4(skeletonTransform[0][0], skeletonTransform[0][1], skeletonTransform[0][2], skeletonTransform[0][3]);

     // Temporarily store the transformed vertex positions for use below
    fs_Pos = modelposition.xyz;

    gl_Position = u_ViewProj * modelposition;// gl_Position is a built-in variable of OpenGL which is
                                             // used to render the final positions of the geometry's vertices
}
