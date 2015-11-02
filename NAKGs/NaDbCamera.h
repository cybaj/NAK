 
/***************************************************************************
 *            NaDbCamera.h
 *
 ****************************************************************************/
#ifndef _GLCAMERA_H
#define _GLCAMERA_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <NaGeMMath.h>

#define PIdiv180 PI/180.0

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

struct NAKGS_API SF3dVector  //Float 3d-vect, normally used
{
    GLdouble x,y,z;
};
struct NAKGS_API SF2dVector
{
    GLdouble x,y;
};

class NAKGS_API NaDbCamera
{
    public:
	NaDbCamera();			//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	void Render ( void );	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render
	void Move ( SF3dVector Direction );
	void RotateX ( GLdouble Angle );
	void RotateY ( GLdouble Angle );
	void RotateZ ( GLdouble Angle );
	void RotateXYZ ( SF3dVector Angles );
	void MoveForwards ( GLdouble Distance );
	void StrafeRight ( GLdouble Distance );

	//Added By N.Sharjith
	void ResetCamera();
	void SetPosition(SF3dVector pos);
	SF3dVector GetPosition() const { return Position; }
	//Added

    private:
	SF3dVector Position;
	SF3dVector ViewDir;		/*Not used for rendering the camera, but for "moveforwards"
					  So it is not necessary to "actualize" it always. It is only
					  actualized when ViewDirChanged is true and moveforwards is called*/
	bool ViewDirChanged;
	GLdouble RotatedX, RotatedY, RotatedZ;	
	void GetViewDir ( void );
};


NAKGS_API SF3dVector F3dVector ( GLdouble x, GLdouble y, GLdouble z );
NAKGS_API SF3dVector AddF3dVectors ( SF3dVector * u, SF3dVector * v);
NAKGS_API void AddF3dVectorToVector ( SF3dVector * Dst, SF3dVector * V2);

#endif /* _GLCAMERA_H */
