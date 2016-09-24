#ifndef		ITEXTINPUT_HPP_
# define	ITEXTINPUT_HPP_

class ITextInput
{
public:
	virtual ~ITextInput() {}

	virtual void setSelected(bool) = 0;
};

#endif /* !ITEXTINPUT_HPP_ */
