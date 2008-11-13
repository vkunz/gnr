#include "Matrix4D.h"

#include <cmath>

Matrix4D::Matrix4D()
{
	loadID();
}

Matrix4D::Matrix4D(const Vertex& pos, const Vertex& s, const Vertex& rot)
{
	loadID();
	moveto(pos);
	scale(s);
	rotate(rot);
}

Matrix4D::Matrix4D(const Matrix4D& other)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_data[i][j] = other.m_data[i][j];
		}
	}
}

Matrix4D::~Matrix4D()
{
}


Matrix4D& Matrix4D::operator = (const Matrix4D& other)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_data[i][j] = other.m_data[i][j];
		}
	}
	return *this;
}

Matrix4D Matrix4D::operator * (const Matrix4D& other) const
{
	Matrix4D result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float s = 0.0f;
			for (int k = 0; k < 4; k++)
			{
				s += m_data[k][i] * other.m_data[j][k];
			}
			result.m_data[i][j] = s;
		}
	}
	return result;
}

Matrix4D& Matrix4D::operator *= (const Matrix4D& other)
{
	Matrix4D result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float s = 0.0f;
			for (int k = 0; k < 4; k++)
			{
				s += m_data[k][i] * other.m_data[j][k];
			}
			result.m_data[j][i] = s;
		}
	}
	*this = result;
	
	return *this;
}

Vertex Matrix4D::operator *(const Vertex& vec) const
{
	float tmp[4], res[4];
	vec.getAll(tmp[0], tmp[1], tmp[2], tmp[3]);
	
	for (int i = 0; i < 4; i++)
	{
		float s = 0.0f;
		for (int j = 0; j < 4; j++)
		{
			s += m_data[j][i] * tmp[j];
		}
		res[i] = s;
	}
	
	Vertex result(res[0], res[1], res[2], res[3]);
	
	return result;
}

Matrix4D Matrix4D::operator !() const
{
	Matrix4D result;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result.m_data[j][i] = m_data[i][j];
		}
	}
	return result;
}

void Matrix4D::loadID()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_data[i][j] = 0.0f;
		}
	}
	m_data[0][0] = m_data[1][1] = m_data[2][2] = m_data[3][3] = 1.0f;
}

void Matrix4D::moveto(const Vertex& pos)
{
	Matrix4D tmp;
	float x, y, z;
	pos.getAll(x, y, z);
	
	tmp.m_data[3][0] = x;
	tmp.m_data[3][1] = y;
	tmp.m_data[3][2] = z;
	
	(*this) *= tmp;
}

void Matrix4D::scale(const Vertex& s)
{
	Matrix4D tmp;
	float x, y, z;
	s.getAll(x, y, z);
	
	tmp.m_data[0][0] = x;
	tmp.m_data[1][1] = y;
	tmp.m_data[2][2] = z;
	(*this) *= tmp;
}

void Matrix4D::rotate(const Vertex& rot)
{
	float x, y, z;
	rot.getAll(x, y, z);
	
	rotateX(x);
	rotateY(y);
	rotateZ(z);
}

void Matrix4D::rotateX(float alpha)
{
	Matrix4D tmp;
	alpha *= M_PI / 180.0f;
	float sa = sin(alpha), ca = cos(alpha);
	tmp.m_data[1][1] = ca;
	
	tmp.m_data[2][1] = -sa;
	tmp.m_data[1][2] = sa;
	
	tmp.m_data[2][2] = ca;
	
	(*this) *= tmp;
}

void Matrix4D::rotateY(float beta)
{
	Matrix4D tmp;
	beta *= M_PI / 180.0f;
	float sb = sin(beta), cb = cos(beta);
	tmp.m_data[0][0] = cb;
	
	tmp.m_data[2][0] = sb;
	tmp.m_data[0][2] = -sb;
	
	tmp.m_data[2][2] = cb;
	
	(*this) *= tmp;
}

void Matrix4D::rotateZ(float gamma)
{
	Matrix4D tmp;
	gamma *= M_PI / 180.0f;
	float sg = sin(gamma), cg = cos(gamma);
	tmp.m_data[0][0] = cg;
	tmp.m_data[1][0] = -sg;
	tmp.m_data[0][1] = sg;
	tmp.m_data[1][1] = cg;
	
	(*this) *= tmp;
}

void Matrix4D::print() const
{
	float *tmp = (float*) m_data;
	for (int i = 0; i < 4; i++)
	{
		printf("%4.2f %4.2f %4.2f %4.2f\n", tmp[4*i], tmp[4*i+1], tmp[4*i+2], tmp[4*i+3]);
	}
}

