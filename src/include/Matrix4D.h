/**
 * Matrix4D
 * @name        Matrix4D.cpp
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _MATRIX4D_H_
#define _MATRIX4D_H_

class Vertex;

class Matrix4D
{
public:
	Matrix4D();
	Matrix4D(const Matrix4D& other);
	Matrix4D(const Vertex& pos, const Vertex& scale, const Vertex& rot);

	virtual ~Matrix4D();

	Matrix4D& operator = (const Matrix4D& other);
	Matrix4D& operator *= (const Matrix4D& other);
	Matrix4D operator * (const Matrix4D& other) const;
	// currently -- transpose
	Matrix4D operator !() const;
	Vertex operator * (const Vertex& vec) const;

	void loadID();
	void moveto(const Vertex& pos);
	void scale(const Vertex& s);
	// rotate along the X-, Y- eventually Z-Axis
	void rotate(const Vertex& rot);

	void rotateX(float alpha);
	void rotateY(float beta);
	void rotateZ(float gamma);

	void print() const;

private:
	float m_data[4][4];
};

#endif //_MATRIX4D_H_
