#pragma once

#include <Windows.h>

#include "figure.h"

#define ESCAPE 27

namespace tua {

	struct MovementParameters;

	class KeyboardListener
	{
	public:
		explicit KeyboardListener() = default;
		KeyboardListener(const KeyboardListener & other) = delete;
		~KeyboardListener() = default;

		enum class ProcessStatus { ACTION_DONE, ACTION_MISSED, QUIT };
		ProcessStatus process_actions(Figure * figure, const MovementParameters & params);
	};

}
