#ifndef ITEXTRENDERER_HPP_
#define ITEXTRENDERER_HPP_

class ITextRenderer
{
public:
	virtual ~ITextRenderer() {}

	virtual void setText(const std::string& text) = 0;
	virtual const std::string &getText() const = 0;
};

#endif // ITEXTRENDERER_HPP_
