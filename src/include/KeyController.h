/**
 * KeyController
 * @name        KeyController.h
 * @date        2008-11-12
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _KEYCONTROLLER_H_
#define _KEYCONTROLLER_H_

class GLCamera;
class GLKeyEvent;
class Scene;

class KeyController
{
public:
	KeyController();
	virtual ~KeyController();
	void KeyPressed(GLKeyEvent& event);
protected:
private:
	void MoveCamera(GLKeyEvent& event);
	Scene*    m_Scene;
	GLCamera* m_Camera;

	float m_fx, m_fz, m_rx, m_rz;
};

#endif // _KEYCONTROLLER_H_
