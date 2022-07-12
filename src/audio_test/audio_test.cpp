#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <AL/efx-creative.h>
#include <AL/efx-presets.h>
#include <AL/efx.h>

#include <tuple>
#include <cmath>
#include <vector>
#include <string>
#include <cstdint>
#include <numbers>
#include <iostream>

//namespace consts = std::numbers;

std::tuple<std::vector<std::int16_t>, std::uint32_t> create_buffer_data(int resolution)
{
	std::vector<std::int16_t> samples;
	for (int i = 0; i < 2 * resolution; i++) {
		samples.push_back(1000 * std::sin(2000 * std::numbers::pi / resolution * i));
	}
	return std::make_tuple(std::move(samples), resolution);
}

int main(int argc, char *argv[])
{
	ALCdevice *device = alcOpenDevice(nullptr);
	if (!device) {
		std::cerr << "We're fucked! Device!" << std::endl;
		return 1;
	}

	ALCcontext *context = alcCreateContext(device, nullptr);
	if (!context) {
		std::cerr << "We're fucked! Context!" << std::endl;
		return 1;
	}

	if (!alcMakeContextCurrent(context)) {
		std::cerr << "We're fucked! Current!" << std::endl;
		return 1;
	}

	ALenum format = AL_FORMAT_MONO16;
	auto [data, sample_rate] = create_buffer_data(41000);

	std::cout << data.size() << " " << sample_rate << std::endl;

	ALuint buffer;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, data.data(), data.size(), sample_rate);

	ALuint source;
	alGenSources(1, &source);
	alSourcei(source, AL_LOOPING, AL_TRUE);
	alSourcei(source, AL_BUFFER, buffer);

	alSourcePlay(source);

	ALint state = AL_PLAYING;
	while(state == AL_PLAYING) {
		alGetSourcei(source, AL_SOURCE_STATE, &state);
	}

	// deinit
	if (!alcMakeContextCurrent(nullptr)) {
		std::cerr << "We're fucked! Context is not reset!" << std::endl;
		return 1;
	}

	alcDestroyContext(context);

	ALCboolean closed = alcCloseDevice(device);
 
	std::cout << "Seems good!" << std::endl;

	return 0;
}