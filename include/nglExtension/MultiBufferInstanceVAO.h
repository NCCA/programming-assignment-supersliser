//
// Created by thoma on 07/04/2025.
//

#ifndef MULTIBUFFERINSTANCEVAO_H
#define MULTIBUFFERINSTANCEVAO_H

#include <ngl/AbstractVAO.h>
#include <ngl/MultiBufferVAO.h>

class MultiBufferInstanceVAO : public ngl::MultiBufferVAO
{
 public :

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief creator method for the factory
    /// @param _mode the mode to draw with.
    /// @returns a new AbstractVAO * object
    //----------------------------------------------------------------------------------------------------------------------
    static std::unique_ptr<ngl::AbstractVAO>create(GLenum _mode=GL_TRIANGLES) { return std::unique_ptr<AbstractVAO>(new MultiBufferInstanceVAO(_mode)); }
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief draw the VAO using glDrawArrays
    //----------------------------------------------------------------------------------------------------------------------
    virtual void draw() const override;
    void draw(int i_instanceCount) const ;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor don't do anything as the remove clears things
    //----------------------------------------------------------------------------------------------------------------------
    virtual ~MultiBufferInstanceVAO()=default;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief remove the VAO and buffers created
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    virtual void setData(const VertexData &_data) override;
    virtual void setData(const VertexData &_data, GLuint i_vboID);

    virtual GLuint getBufferID(GLuint i_vboID) const override;


  protected :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor calles parent ctor to allocate vao;
    //----------------------------------------------------------------------------------------------------------------------
    MultiBufferInstanceVAO(GLenum _mode)  : MultiBufferVAO(_mode)
    {

    }

};

#endif //MULTIBUFFERINSTANCEVAO_H
