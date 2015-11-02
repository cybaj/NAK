 
/***************************************************************************
 *            NaDbMaterial.h
 *
 ****************************************************************************/


#ifndef _GLMATERIAL_H
#define _GLMATERIAL_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "NaDbTypeEnums.h"
#include "NaDbColor.h"
#include <NaGeMMath.h>

class NAKGS_API NaDbMaterial
{
    public:
	NaDbMaterial();
	NaDbMaterial(const GsMaterialName& mat);
	void SetName(const GsMaterialName& mat);
	void SetAmbient(const NaDbColor&);
	void SetDiffuse(const NaDbColor&);
	void SetSpecular(const NaDbColor&);
	void SetAmbientCoeff(const float&);
	void SetDiffuseCoeff(const float&);
	void SetSpecularCoeff(const float&);
	void SetShininessCoeff(const float&);
	NaDbColor GetAmbient()	const;
	NaDbColor GetDiffuse()	const;
	NaDbColor GetSpecular()	const;
	float	 GetAmbientCoeff()	const;
	float	 GetDiffuseCoeff()	const;
	float	 GetSpecularCoeff()	const;
	float	 GetShininessCoeff()	const;
    private:
	void Init(const GsMaterialName& mat);
	GsMaterialName myMaterialName;
	NaDbColor myAmbient;
	NaDbColor myDiffuse;
	NaDbColor mySpecular;
	float myAmbientCoeff;
	float myDiffuseCoeff;
	float mySpecularCoeff;
	float myShininessCoeff;
};

#endif /* _GLMATERIAL_H */
