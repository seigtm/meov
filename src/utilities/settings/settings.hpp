#pragma once

#include <fstream>

#include <LogUtils.hpp>

#include <rapidjson/rapidjson.h>
#include <rapidjson/error/en.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace meov::utilities {

/// @brief Singleton application settings class.
class Settings {
public:
    /// @brief Static method to get singleton instance of Settings.
    /// @return Reference to the static Settings object.
    static Settings& Instance();

    /// @brief Wrapper around rapidjson::Document::operator[]().
    /// @param key member's key.
    /// @return rapidjson::Value reference, that can be used later.
    rapidjson::Value& operator[](std::string const& key);

    /* Note about deleted functions:
        Scott Meyers mentions in his Effective Modern
        C++ book, that deleted functions should generally
        be public as it results in better error messages
        due to the compilers behavior to check accessibility
        before deleted status.
    */
    /// @brief Copy constructor.
    /// @details Deleted method because of Singleton ideoma.
    Settings(Settings const&) = delete;
    /// @brief Assign operator.
    /// @details Deleted method because of Singleton ideoma.
    void operator=(Settings const&) = delete;

private:
    /// @brief Default constructor.
    /// @details Private method because of Singleton ideoma.
    Settings();

    /// @brief Writes the default settings congiguration to the JSON file.
    void WriteDefaults();
    /// @brief Method that checks correctness of the JSON settings file structure.
    /// @return true is the structure correct and false otherwise.
    bool AreCorrect();

    rapidjson::Document mDocument;
    const fs::path mFilePath;
};

}  // namespace meov::utilities
