#pragma once

#include <fstream>

#include <LogUtils.hpp>

#include <rapidjson/rapidjson.h>
#include <rapidjson/error/en.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/pointer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace meov::utilities {

/// @brief Singleton application settings class.
class Settings {
public:
    /// @brief Static method to get singleton instance of Settings.
    /// @return Reference to the static Settings object.
    static Settings& Instance();

    /// @brief Writes the default settings congiguration to the JSON file.
    void WriteDefaults();
    /// @brief Save method which saves configuration to the JSON file.
    void Save();

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

    /// @brief Method that checks correctness of the JSON settings file structure.
    /// @return true is the structure correct and false otherwise.
    bool AreCorrect();

    rapidjson::Document mDocument;
    const fs::path mFilePath;
};

}  // namespace meov::utilities

/*

TODO:

1. Return and rethink Set(key, val) and Get(key, opt: defaultVal) methods.
    They will create key-val pair if it doesn't exist it mDocument.
    Maybe they should return std::optional or it will be hard-coded
        inside them (test: GetValueByPointerWithDefault()).
2. Remove AreCorrect() method.
3. Settings::Configurable, from which other objects will inhert,
    should (?) impelent something like OnLoad() method
    and write their settings blocks.
4. WriteDefaults() may not write anything at all.
    Just create the JSON file.
5. Remove [] operator implementation or change it to use Get() and Set() somehow.

@@ Possible problems with this:
-> Settings::instance()["Window"].value_or(default)["Width"].value_or(default);
-> Settings::instance()["Window"]["Width"] (HOW?!).

*/
