#pragma once

#include <string>
#include <string_view>

namespace RE { class Actor; }

namespace slavetats_ng
{
	std::string resolve_texture_path(RE::Actor* a_target, std::string_view a_relative, std::string_view a_area);
	std::string resolve_texture_file_path(RE::Actor* a_target, std::string_view a_relative, std::string_view a_area);
	bool is_ube_actor(RE::Actor* a_target);
	bool is_cotr_actor(RE::Actor* a_target);
}
