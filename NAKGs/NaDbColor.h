/***************************************************************************
 *            NaDbColor.h
 *
 ****************************************************************************/


#ifndef _GLCOLOR_H
#define _GLCOLOR_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

class NAKGS_API NaDbColor
{
    public:
	NaDbColor();
	NaDbColor(const float& red, const float& green, const float& blue);
	~NaDbColor();
	void SetValues(const float& red, const float& green, const float& blue);
	float GetRed()   const;
	float GetGreen() const;
	float GetBlue()  const;
    private:
	float itsRed;
	float itsGreen;
	float itsBlue;
};

#endif /* _GLCOLOR_H */
