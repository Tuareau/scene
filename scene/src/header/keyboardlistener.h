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
			A, S, D, W, R, T,
			J, K, L, I, K9, K0,
			Q, E,
			U, O,
			Z, X,
			C, V, 
			F, G,
			Y, H,
			B, N,
			M, P,
			ESC, NONE,
		};

		Key get_active_key() const;
	};

}
