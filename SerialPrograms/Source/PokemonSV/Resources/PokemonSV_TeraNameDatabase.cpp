#include "PokemonSV_TeraNameDatabase.h"
#include "CommonFramework/Logging/Logger.h"
#include "Pokemon/Resources/Pokemon_PokemonNames.h"
#include "PokemonSV/Resources/PokemonSV_PokemonSprites.h"
#include "PokemonSV_NameDatabase.h"

namespace PokemonAutomation {
namespace NintendoSwitch {
namespace PokemonSV {

using namespace Pokemon;

StringSelectDatabase make_tera_name_database(const std::vector<std::string>& slugs){
    const SpriteDatabase& sprites = ALL_POKEMON_SPRITES();

    StringSelectDatabase database;
    for (const std::string& slug : slugs){
        const SpriteDatabase::Sprite* sprite = sprites.get_nothrow(slug);
        if (sprite){
            database.add_entry(StringSelectEntry(
                slug,
                slug,
                sprite->icon
            ));
        }else{
            global_logger_tagged().log("No sprite for: " + slug);
            database.add_entry(StringSelectEntry(
                slug,
                slug
            ));
        }
    }

    return database;
}
StringSelectDatabase make_ALL_POKEMON_TERA_NAMES(bool with_anything = false){
    // For now, use sprites to determine if it's in the game.
    const SpriteDatabase& sprites = ALL_POKEMON_SPRITES();

    std::vector<std::string> slugs;
    for (std::string& slug : load_pokemon_slug_json_list("PokemonSV/Pokedex.json")){
        const SpriteDatabase::Sprite* sprite = sprites.get_nothrow(slug);
        if (sprite != nullptr){
            slugs.emplace_back(std::move(slug));
        }
    }

    if (with_anything)
        slugs.emplace(slugs.begin(), "anything");

    return make_tera_name_database(slugs);
}

const StringSelectDatabase& ALL_POKEMON_TERA_NAMES(){
    static const StringSelectDatabase database = make_ALL_POKEMON_TERA_NAMES();
    return database;
}

const StringSelectDatabase& ALL_POKEMON_TERA_NAMES_WITH_ANYTHING(){
    static const StringSelectDatabase database = make_ALL_POKEMON_TERA_NAMES(true);
    return database;
}

} // namespace PokemonSV
} // namespace NintendoSwitch
} // namespace PokemonAutomation
