#pragma once

enum GrowState : int{ //I normally would only use `enum class` but implicit casting to/from int is useful here
	Small = 0,
	Normal = 1,
	Big = 2
};