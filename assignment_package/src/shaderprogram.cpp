#include "shaderprogram.h"
#include <QFile>
#include <QStringBuilder>
#include <iostream>
#include "mesh.h"


ShaderProgram::ShaderProgram(OpenGLContext *context)
    : vertShader(), fragShader(), prog(),
      attrPos(-1), attrNor(-1), attrCol(-1),
      attrWgt(-1), attrWgtIdx(-1),
      unifModel(-1), unifModelInvTr(-1), unifViewProj(-1), unifCamPos(-1),
      unifBindMat(-1), unifJointTrans(-1), unifBindMat4(-1),
      context(context)
{}

void ShaderProgram::create(const char *vertfile, const char *fragfile)
{
    // Allocate space on our GPU for a vertex shader and a fragment shader and a shader program to manage the two
    vertShader = context->glCreateShader(GL_VERTEX_SHADER);
    fragShader = context->glCreateShader(GL_FRAGMENT_SHADER);
    prog = context->glCreateProgram();
    // Get the body of text stored in our two .glsl files
    QString qVertSource = qTextFileRead(vertfile);
    QString qFragSource = qTextFileRead(fragfile);

    char* vertSource = new char[qVertSource.size()+1];
    strcpy(vertSource, qVertSource.toStdString().c_str());
    char* fragSource = new char[qFragSource.size()+1];
    strcpy(fragSource, qFragSource.toStdString().c_str());


    // Send the shader text to OpenGL and store it in the shaders specified by the handles vertShader and fragShader
    context->glShaderSource(vertShader, 1, &vertSource, 0);
    context->glShaderSource(fragShader, 1, &fragSource, 0);
    // Tell OpenGL to compile the shader text stored above
    context->glCompileShader(vertShader);
    context->glCompileShader(fragShader);
    // Check if everything compiled OK
    GLint compiled;
    context->glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        printShaderInfoLog(vertShader);
    }
    context->glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        printShaderInfoLog(fragShader);
    }

    // Tell prog that it manages these particular vertex and fragment shaders
    context->glAttachShader(prog, vertShader);
    context->glAttachShader(prog, fragShader);
    context->glLinkProgram(prog);

    // Check for linking success
    GLint linked;
    context->glGetProgramiv(prog, GL_LINK_STATUS, &linked);
    if (!linked) {
        printLinkInfoLog(prog);
    }

    // Get the handles to the variables stored in our shaders
    // See shaderprogram.h for more information about these variables

    attrPos = context->glGetAttribLocation(prog, "vs_Pos");
    attrNor = context->glGetAttribLocation(prog, "vs_Nor");
    attrCol = context->glGetAttribLocation(prog, "vs_Col");
    attrWgt = context->glGetAttribLocation(prog, "vs_Wgt");
    attrWgtIdx = context->glGetAttribLocation(prog, "vs_WgtIdx");

    unifModel      = context->glGetUniformLocation(prog, "u_Model");
    unifModelInvTr = context->glGetUniformLocation(prog, "u_ModelInvTr");
    unifViewProj   = context->glGetUniformLocation(prog, "u_ViewProj");
    unifCamPos      = context->glGetUniformLocation(prog, "u_CamPos");
    unifJointTrans = context->glGetUniformLocation(prog, "u_TransformQuat");
    unifBindMat = context->glGetUniformLocation(prog, "u_BindMatrices");
    unifBindMat4 = context->glGetUniformLocation(prog, "u_BindMatricesMat");
    std::cout<<std::endl;
}

void ShaderProgram::useMe()
{
    context->glUseProgram(prog);
}

void ShaderProgram::setModelMatrix(const glm::mat4 &model)
{
    useMe();

    if (unifModel != -1) {
        // Pass a 4x4 matrix into a uniform variable in our shader
                        // Handle to the matrix variable on the GPU
        context->glUniformMatrix4fv(unifModel,
                        // How many matrices to pass
                           1,
                        // Transpose the matrix? OpenGL uses column-major, so no.
                           GL_FALSE,
                        // Pointer to the first element of the matrix
                           &model[0][0]);
    }

    if (unifModelInvTr != -1) {
        glm::mat4 modelinvtr = glm::inverse(glm::transpose(model));
        // Pass a 4x4 matrix into a uniform variable in our shader
                        // Handle to the matrix variable on the GPU
        context->glUniformMatrix4fv(unifModelInvTr,
                        // How many matrices to pass
                           1,
                        // Transpose the matrix? OpenGL uses column-major, so no.
                           GL_FALSE,
                        // Pointer to the first element of the matrix
                           &modelinvtr[0][0]);
    }
}

void ShaderProgram::setViewProjMatrix(const glm::mat4 &vp)
{
    // Tell OpenGL to use this shader program for subsequent function calls
    useMe();

    if(unifViewProj != -1) {
    // Pass a 4x4 matrix into a uniform variable in our shader
                    // Handle to the matrix variable on the GPU
    context->glUniformMatrix4fv(unifViewProj,
                    // How many matrices to pass
                       1,
                    // Transpose the matrix? OpenGL uses column-major, so no.
                       GL_FALSE,
                    // Pointer to the first element of the matrix
                       &vp[0][0]);
    }
}

void ShaderProgram::setCamPos(glm::vec3 pos)
{
    useMe();

    if(unifCamPos != -1)
    {
        context->glUniform3fv(unifCamPos, 1, &pos[0]);
    }
}

void ShaderProgram::setBindMatrices(const std::vector<glm::mat2x4> bind)
{
    useMe();
    glm::mat2x4 bindArray[bind.size()];
    for(int i = 0; i < bind.size(); i++)
    {
        bindArray[i] = bind[i];
    }
    if(unifBindMat != -1)
    {
        int len = sizeof(bindArray) / sizeof(glm::mat2x4);
        context->glUniformMatrix2x4fv(unifBindMat, len, GL_FALSE, glm::value_ptr(bindArray[0]));
    }
}

void ShaderProgram::setJointTrans(const std::vector<glm::mat2x4> transQ)
{
    useMe();
    glm::mat2x4 transQArray[transQ.size()];
    for(int i = 0; i < transQ.size(); i++)
    {
        transQArray[i] = transQ[i];
    }

    if(unifJointTrans != -1)
    {
        int len = sizeof(transQArray) / sizeof(glm::mat2x4);
        context->glUniformMatrix2x4fv(unifJointTrans, len, GL_FALSE, glm::value_ptr(transQArray[0]));
    }
}

void ShaderProgram::setBindMatricesMat(const std::vector<glm::mat4> bind)
{
    useMe();
    glm::mat4 bindArray[bind.size()];
    for(int i = 0; i < bind.size(); i++)
    {
        bindArray[i] = bind[i];
    }
    if(unifBindMat4 != -1)
    {
        int len = sizeof(bindArray) / sizeof(glm::mat4);
        context->glUniformMatrix4fv(unifBindMat4, len, GL_FALSE, glm::value_ptr(bindArray[0]));
    }
}

//This function, as its name implies, uses the passed in GL widget
void ShaderProgram::draw(Drawable &d)
{
        useMe();

    // Each of the following blocks checks that:
    //   * This shader has this attribute, and
    //   * This Drawable has a vertex buffer for this attribute.
    // If so, it binds the appropriate buffers to each attribute.

        // Remember, by calling bindPos(), we call
        // glBindBuffer on the Drawable's VBO for vertex position,
        // meaning that glVertexAttribPointer associates vs_Pos
        // (referred to by attrPos) with that VBO
    if (attrPos != -1 && d.bindPos()) {
        context->glEnableVertexAttribArray(attrPos);
        context->glVertexAttribPointer(attrPos, 4, GL_FLOAT, false, 0, nullptr);
    }

    if (attrNor != -1 && d.bindNor()) {
        context->glEnableVertexAttribArray(attrNor);
        context->glVertexAttribPointer(attrNor, 4, GL_FLOAT, false, 0, nullptr);
    }

    if (attrCol != -1 && d.bindCol()) {
        context->glEnableVertexAttribArray(attrCol);
        context->glVertexAttribPointer(attrCol, 4, GL_FLOAT, false, 0, nullptr);
    }

    // Set weight and index for mesh skeleton
    if(typeid(d) == typeid(Mesh))
    {
        Mesh* curMesh = dynamic_cast<Mesh*>(&d);
        if(attrWgt != -1 && curMesh->bindWeight())
        {
            context->glEnableVertexAttribArray(attrWgt);
            context->glVertexAttribPointer(attrWgt, 4, GL_FLOAT, false, 0, nullptr);
        }

        if(attrWgtIdx != -1 && curMesh->bindWeightIdx())
        {
            context->glEnableVertexAttribArray(attrWgtIdx);
            context->glVertexAttribIPointer(attrWgtIdx, 4, GL_INT, 0, nullptr);
        }
    }

    // Bind the index buffer and then draw shapes from it.
    // This invokes the shader program, which accesses the vertex buffers.
    d.bindIdx();
    context->glDrawElements(d.drawMode(), d.elemCount(), GL_UNSIGNED_INT, 0);
    std::cout << glGetError() << std::endl;

    if (attrPos != -1) context->glDisableVertexAttribArray(attrPos);
    if (attrNor != -1) context->glDisableVertexAttribArray(attrNor);
    if (attrCol != -1) context->glDisableVertexAttribArray(attrCol);

    context->printGLErrorLog();
}

char* ShaderProgram::textFileRead(const char* fileName) {
    char* text;

    if (fileName != NULL) {
        FILE *file = fopen(fileName, "rt");

        if (file != NULL) {
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);

            if (count > 0) {
                text = (char*)malloc(sizeof(char) * (count + 1));
                count = fread(text, sizeof(char), count, file);
                text[count] = '\0';	//cap off the string with a terminal symbol, fixed by Cory
            }
            fclose(file);
        }
    }
    return text;
}

QString ShaderProgram::qTextFileRead(const char *fileName)
{
    QString text;
    QFile file(fileName);
    if(file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        text = in.readAll();
        text.append('\0');
    }
    return text;
}

void ShaderProgram::printShaderInfoLog(int shader)
{
    int infoLogLen = 0;
    int charsWritten = 0;
    GLchar *infoLog;

    context->glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

    // should additionally check for OpenGL errors here

    if (infoLogLen > 0)
    {
        infoLog = new GLchar[infoLogLen];
        // error check for fail to allocate memory omitted
        context->glGetShaderInfoLog(shader,infoLogLen, &charsWritten, infoLog);
        qDebug() << "ShaderInfoLog:" << endl << infoLog << endl;
        delete [] infoLog;
    }

    // should additionally check for OpenGL errors here
}

void ShaderProgram::printLinkInfoLog(int prog)
{
    int infoLogLen = 0;
    int charsWritten = 0;
    GLchar *infoLog;

    context->glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLogLen);

    // should additionally check for OpenGL errors here

    if (infoLogLen > 0) {
        infoLog = new GLchar[infoLogLen];
        // error check for fail to allocate memory omitted
        context->glGetProgramInfoLog(prog, infoLogLen, &charsWritten, infoLog);
        qDebug() << "LinkInfoLog:" << endl << infoLog << endl;
        delete [] infoLog;
    }
}
