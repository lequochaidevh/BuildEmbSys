#include"pch.h"

namespace ViSolEngine {
	UUID getUUID() {
		static std::random_device randomize;
		static std::mt19937_64 generator(randomize());
		static std::uniform_int_distribution<UUID> distribution;

		UUID uuid = INVALID_ID;
		do {
			uuid = distribution(generator);
            std::cout << "get uuid: " << uuid << std::endl;
		} while (uuid == INVALID_ID);

		return uuid;
	}
}