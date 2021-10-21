#pragma once

#include <Windows.h>

#include "figure.h"

#define ESCAPE 27

namespace tua {

	class KeyboardListener
	{
	public:
		explicit KeyboardListener() = default;
		KeyboardListener(const KeyboardListener & other) = delete;
		~KeyboardListener() = default;

		enum class Key {
			FIGURE1,
			A, S, D, W, R, T,
			Q, E,
			Z, X,
			C, V, 
			F, G,

			FIGURE2,
			J, K, L, I, K9, K0,
			U, O,
			Y, H,
			B, N,
			M, P,

			ESC, 
			NONE,
		};

		Key get_active_key() const;
	};

}
