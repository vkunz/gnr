#ifndef _GNRMOUSE_H_
#define _GNRMOUSE_H_

class GNRMouse
{
private:
	bool m_LMousePressed, m_MMousePressed, m_RMousePressed;
	
	int	m_mouse_x, m_mouse_y;
	int window_w, window_h;
	int zcoord;
	
	float posx, posy, posz;
	float phix, phiy, phiz, angle;
	float phix_old, phiy_old;
	float zfar, znear;
	
	GNRMouse();
	virtual ~GNRMouse();
	
protected:

	void ObjectRotate(int m_x, int m_y);
	void ObjectMoveXY(int m_x, int m_y);
	void ObjectMoveXZ(int m_x, int m_y);
	
public:


};

#endif // _GNRMOUSE_H_
