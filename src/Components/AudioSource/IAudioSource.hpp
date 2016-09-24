#ifndef IAUDIOSOURCE_HPP_
#define IAUDIOSOURCE_HPP_

class IAudioSource
{
public:
	virtual ~IAudioSource() {}

	virtual void playSound(const std::string& sound, float volume) const = 0;
};

#endif // IAUDIOSOURCE_HPP_
