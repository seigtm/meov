#include "common.hpp"

#include "shaders_program.hpp"
#include "impl_factory.hpp"

namespace meov::core::shaders {

Program::Impl::Impl(const std::string &name, uint32_t id)
    : mName{ name }
    , mId{ id } {}

uint32_t Program::Impl::GetID() const {
    return mId;
}

const std::string &Program::Impl::GetName() const {
    return mName;
}

void Program::Initialize(const std::string &name) {
    mImpl = factories::ImplFactory::Instance()->MakeProgramImpl(name);
}
void Program::Destroy() {
    mImpl.reset();
}

bool Program::Attach(const std::shared_ptr<Shader> &shader) {
    if(!mImpl) return false;
    return mImpl->Attach(shader);
}
bool Program::Detach(const std::shared_ptr<Shader> &shader) {
    if(!mImpl) return false;
    return mImpl->Attach(shader);
}

void Program::Use() {
    if(!mImpl) return;
    return mImpl->Use();
}
void Program::UnUse() {
    if(!mImpl) return;
    return mImpl->UnUse();
}

bool Program::IsValid() const {
    return mImpl != nullptr && mImpl->IsValid();
}

uint32_t Program::GetID() const {
    if(!mImpl) return 0;
    return mImpl->GetID();
}

std::string Program::GetName() const {
    if(!mImpl) return "NO_NAME";
    return mImpl->GetName();
}

std::shared_ptr<Setter> Program::Get(const std::string_view &name) {
    if(!mImpl) return nullptr;
    return mImpl->Get(*this, name);
}


}  // namespace meov::core::shaders