#include "Common.hpp"

#include "model.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"

namespace meov::core {

Model::Model(const MeshPtr &mesh, const ShaderPtr &shader, const TexturePtr &texture)
    : mMesh{ mesh }, mShader{ shader }, mTexture{ texture } {
    if(nullptr == mShader) {
        return;
    }
    if(nullptr == mTexture || !mTexture->Valid()) {
        return;
    }
    mShader->Get("useTexture").Set(true);
    mShader->Get("defTexture").Set(mTexture->GetID());
}

Model &Model::mesh(const MeshPtr &Mesh) {
    mMesh = Mesh;
    return *this;
}

Model &Model::shader(const ShaderPtr &shader) {
    mShader = shader;
    return *this;
}

Model &Model::texture(const TexturePtr &texture) {
    mTexture = texture;
    return *this;
}

const MeshPtr Model::mesh() const {
    return mMesh;
}

const ShaderPtr Model::shader() const {
    return mShader;
}

const TexturePtr Model::texture() const {
    return mTexture;
}

void Model::draw() {
    Bind();
    if(mMesh->HasIndices()) {
        glDrawElements(GL_TRIANGLES, mMesh->IndicesCount(), GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, mMesh->VerticesCount());
    }
}

void Model::Bind() const {
    if(mShader) mShader->Use();
    if(mTexture) mTexture->Bind();
    mMesh->Draw(mShader);
}

}  // namespace meov::core
