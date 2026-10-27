#include "PCH.h"
#include "ube_texture_resolver.h"
#include "constants.h"
#include "jcontainers_wrapper.h"

using namespace slavetats_ng::jcwrapper;

namespace slavetats_ng
{
	bool texture_exists(std::string_view a_path)
	{
		// JContainers::fileExistsAtPath only sees loose files, so tattoos packed
		// into BSA archives were rejected.  Ask the game's resource system
		// instead; it resolves paths relative to Data and looks into archives.
		std::string path{ a_path };
		if (path.size() > 5 && _strnicmp(path.c_str(), "Data\\", 5) == 0)
			path.erase(0, 5);
		std::string key = path;
		std::ranges::transform(key, key.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

		static std::mutex cache_lock;
		static std::unordered_map<std::string, bool> cache;
		{
			std::scoped_lock lock(cache_lock);
			if (auto it = cache.find(key); it != cache.end())
				return it->second;
		}

		RE::BSResourceNiBinaryStream stream(path);
		const bool found = stream.good();
		if (!found)
			logger::info("texture not found: {}", path);

		std::scoped_lock lock(cache_lock);
		cache.emplace(std::move(key), found);
		return found;
	}

	bool is_ube_actor(RE::Actor* a_target)
	{
		if (!a_target) return false;
		const auto has_ube = [](const RE::TESRace* race) {
			if (!race) return false;
			const auto* id = race->GetFormEditorID();
			return id && std::string_view(id).find("UBE") != std::string_view::npos;
		};
		return has_ube(a_target->GetRace()) ||
			(a_target->GetActorBase() && has_ube(a_target->GetActorBase()->GetRace()));
	}

	bool is_cotr_actor(RE::Actor* a_target)
	{
		const auto* base = a_target ? a_target->GetActorBase() : nullptr;
		return base && base->HasKeywordString("COTR");
	}

	std::string resolve_texture_path(RE::Actor* a_target, std::string_view relative, std::string_view area)
	{
		const std::string rel{ relative };
		// UBE races use UBE textures for every overlay area. COtR actors retain
		// their 3BA body, hands, and feet, but need UBE-compatible face overlays.
		const bool use_ube = is_ube_actor(a_target) ||
			(area == "Face" && is_cotr_actor(a_target));
		if (use_ube) {
			const std::string ube = "UBE\\" + rel;
			if (texture_exists(std::string(ROOT()) + std::string(PREFIX()) + ube))
				return std::string(PREFIX()) + ube;
		}
		return std::string(PREFIX()) + rel;
	}

	std::string resolve_texture_file_path(RE::Actor* a_target, std::string_view relative, std::string_view area)
	{
		return std::string(ROOT()) + resolve_texture_path(a_target, relative, area);
	}
}
