#include "AnimationClip.h"

namespace Tristeon
{
	REGISTER_TYPE_CPP(AnimationClip)

	AnimationClip::AnimationClip(std::string const& texturePath, unsigned const& cols, unsigned const& rows,
		bool const& loops, int const& startIndex, int const& endIndex) : rows(rows), cols(cols), loops(loops), texturePath(texturePath)
	{
		this->startIndex = startIndex == -1 ? 0 : startIndex;
		this->endIndex = endIndex == -1 ? cols * rows : endIndex;
	}

	json AnimationClip::serialize()
	{
		json j;
		j["typeID"] = TRISTEON_TYPENAME(AnimationClip);
		j["rows"] = rows;
		j["cols"] = cols;
		j["startIndex"] = startIndex;
		j["endIndex"] = endIndex;
		j["loops"] = loops;
		j["texturePath"] = texturePath;
		return j;
	}

	void AnimationClip::deserialize(json j)
	{
		rows = j["rows"];
		cols = j["cols"];
		startIndex = j["startIndex"];
		endIndex = j["endIndex"];
		loops = j["loops"];
		texturePath = j["texturePath"].get<std::string>();
	}
}