
#include "stdafx.h"

#include "NaDbColor.h"
#include "NaGeMMath.h"


NaDbColor::NaDbColor()
{
    itsRed = 0.5f;
    itsGreen = 0.5f;
    itsBlue = 0.5f;
}

NaDbColor::NaDbColor(const float& red, const float& green, const float& blue)
{
    itsRed =	(red < 0) ? 0 : ((red > 1) ? 1 : red);
    itsGreen =	(green < 0) ? 0 : ((green > 1) ? 1 : green);
    itsBlue =	(blue < 0) ? 0 : ((blue > 1) ? 1 : blue);
}

NaDbColor::~NaDbColor()
{
}

void NaDbColor::SetValues(const float& red, const float& green, const float& blue)
{
    itsRed =	(red < 0) ? 0 : ((red > 1) ? 1 : red);
    itsGreen =	(green < 0) ? 0 : ((green > 1) ? 1 : green);
    itsBlue =	(blue < 0) ? 0 : ((blue > 1) ? 1 : blue);
}

float NaDbColor::GetRed()   const
{
    return itsRed;
}

float NaDbColor::GetGreen() const
{
    return itsGreen;
}

float NaDbColor::GetBlue()  const
{
    return itsBlue;
}

