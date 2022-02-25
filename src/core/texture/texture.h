#pragma once

namespace meov::core {

class Texture {
public:
    explicit Texture(const std::string &path);
    ~Texture();

    void bind();
    bool valid() const;

    unsigned getID() const;

private:
    unsigned mId;
    bool mValid;
};

} // namespace meov::core