/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:01:05 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/24 16:42:05 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <cmath>
# include <iostream>

/*
generic vector class for 2d points and directions, 
plus methods for manipulation.
*/
template<typename T>
class vec2
{
public:
	vec2() : x(T(0)), y(T(0)) {}
	vec2(T xx) : x(xx), y(xx) {}
	vec2(T xx, T yy) : x(xx), y(yy) {}
	
	union {T x, r, s, u; };
	union {T y, g, t, v; };

	vec2 operator + (const vec2 &vector) const
	{ return (vec2(x + vector.x, y + vector.y)); }

	vec2 operator - (const vec2 &vector) const
	{ return (vec2(x - vector.x, y - vector.y)); }

	vec2 operator * (const T &num) const
	{ return (vec2(x * num , y * num)); }

	vec2 operator / (const T &num) const
	{ return (vec2(x / num , y / num)); }

	vec2 operator * (const vec2 &vector) const
	{ return (vec2(x * vector.x, y * vector.y)); }

	vec2& operator /= (const T &num) const
	{ x /= num, y /= num ;return (*this); }

	vec2& operator *= (const T &num) const
	{ x *= num, y *= num ;return (*this); }

	T norm() const 
	{ return (x * x + y * y); }

	T length() const
	{ return (sqrt(norm())); }

	vec2& normalize()
	{
		T norm = norm();
		if (norm > 0)
		{
			T factor = 1/ sqrt(norm);
			x *= factor, y *= factor;
		}
		return (*this);
	}

	friend vec2 operator * (const T &num, const vec2 &vector)
	{ return (vec2<T>(vector.x * num, vector.y * num, vector.z * num)); }

	friend vec2 operator / (const T &num, const vec2 &vector)
	{ return (vec2<T>(num / vector.x, num / vector.y, num / vector.z)); }

	friend vec2 operator / (const vec2 &vector, const T &num)
	{ return (vec2<T>(vector.x / num, vector.y / num, vector.z / num)); }

	// Accessors for use in loopes etc. Const and mutable.
	const T& operator [] (uint8_t index) const { return ((&x)[index]); }
	T& operator [] (uint8_t index) { return ((&x)[index]); }
};

/*
Typedefs for specialised classes. 
For example float vectors can be declared either vec2<float> a, or vec2f a.
*/
typedef vec2<double> vec2d;
typedef vec2<float> vec2f;
typedef vec2<int> vec2i;


/*
generic vector class for 3d points and directions, 
plus methods for manipulation.
*/
template<typename T>
class vec3
{
public:
	vec3() : x(T(0)), y(T(0)), z(T(0)) {}
	vec3(T xx) : x(xx), y(xx), z(xx) {}
	vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

	union {T x, r, s; };
	union {T y, g, t; };
	union {T z, b, p; };

	vec3 operator+(const vec3 &vector) const
	{ return (vec3(x + vector.x, y + vector.y, z + vector.z)); }

	vec3 operator-(const vec3 &vector) const
	{ return (vec3(x - vector.x, y - vector.y, z - vector.z)); }

	vec3 operator-() const
	{ return (vec3(-x,  -y, -z)); }

	vec3 operator-(const T &num) const
	{ return (vec3(x - num,  y - num, z - num)); }

	vec3 operator*(const T &num) const
	{ return (vec3(x * num , y * num, z - num)); }

	vec3 operator*(const vec3 &vector) const
	{ return (vec3(x * vector.x, y * vector.y, z * vector.z)); }

	vec3& operator/=(const T &num) const
	{ x /= num, y /= num, z /= num; return (*this); }

	vec3& operator*=(const T &r) const
	{ x *= r, y *= r, z *= r; return (*this); }


	T dot_product(const vec3<T> &vector) const
	{ return (x * vector.x + y * vector.y + z * vector.z); }

	vec3 cross_product(const vec3<T> &vector) const
	{
		return (vec3<T>(y * vector.z - z * vector.y,
						z * vector.x - x * vector.z,
						x * vector.y - y * vector.x));
	}

	T norm() const 
	{ return (x * x + y * y + z * z); }

	T length() const
	{ return (sqrt(norm())); }

	vec3& normalize()
	{
		T norm = this->norm();
		if (norm > 0)
		{
			T factor = 1 / sqrt(norm);
			x *= factor, y *= factor, z *=factor;
		}
		return (*this);
	}

	friend vec3 operator*(const T &num, const vec3 &vector)
	{ return (vec3<T>(vector.x * num, vector.y * num, vector.z * num)); };

	friend vec3 operator/(const T &num, const vec3 &vector)
	{ return (vec3<T>(num / vector.x, num / vector.y, num / vector.z)); };

	friend vec3 operator/(const vec3 &vector, const T &num)
	{ return (vec3<T>(vector.x / num, vector.y / num, vector.z / num)); };

	// Accessors for use in loopes etc. Const and mutable.
	const T& operator [] (uint8_t index) const { return ((&x)[index]); }
	T& operator [] (uint8_t index) { return ((&x)[index]); }
};


/*
Typedefs for specialised classes. 
For example float vectors can be declared either vec3<float> a, or vec3f a.
*/
typedef vec3<double> vec3d;
typedef vec3<float> vec3f;
typedef vec3<int> vec3i;
typedef vec3<unsigned int> vec3ui;


/*
generic vector class for 3d points and directions, with w element.
Plus methods for manipulation.
*/
template<typename T>
class vec4
{
public:
	vec4() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
	vec4(T xx) : x(xx), y(xx), z(xx), w(T(0)) {}
	vec4(T xx, T yy, T zz) : x(xx), y(yy), z(zz) , w(T(0)) {}
	vec4(T xx, T yy, T zz, T ww) : x(xx), y(yy), z(zz) , w(ww) {}

	union {T x, r, s; };
	union {T y, g, t; };
	union {T z, b, p; };
	union {T w, a, q; };

	vec4 operator + (const vec4 &vector) const
	{ return (vec4(x + vector.x, y + vector.y, z + vector.z, w + vector.w)); }

	vec4 operator - (const vec4 &vector) const
	{ return (vec4(x - vector.x, y - vector.y, z - vector.z, w + vector.w)); }

	vec4 operator - () const
	{ return (vec4(-x,  -y, -z, w)); }

	vec4 operator * (const T &num) const
	{ return (vec4(x * num , y * num, z * num, w * num)); }

	vec4 operator * (const vec4 &vector) const
	{ return (vec4(x * vector.x, y * vector.y, z * vector.z, w * vector.w)); }

	vec4& operator /= (const T &num) const
	{ x /= num, y /= num, z /= num; return (*this); }

	vec4& operator *= (const T &r) const
	{ x *= r, y *= r, z *= r; return (*this); }

	T dot_product(const vec4<T> &vector) const
	{ return (x * vector.x + y * vector.y + z * vector.z); }

	vec4 cross_product(const vec4<T> &vector) const
	{
		return (vec4<T>(y * vector.z - z * vector.y,
						z * vector.x - x * vector.z,
						x * vector.y - y * vector.x));
	}

	T norm() const 
	{ return (x * x + y * y + z * z); }

	T length() const
	{ return (sqrt(norm())); }

	vec4& normalize()
	{
		T norm = this->norm();
		if (norm > 0)
		{
			T factor = 1/ sqrt(norm);
			x *= factor, y *= factor, z *=factor;
		}
		return (*this);
	}

	friend vec4 operator * (const T &num, const vec4 &vector)
	{ return (vec4<T>(vector.x * num, vector.y * num, vector.z * num)); }

	friend vec4 operator / (const T &num, const vec4 &vector)
	{ return (vec4<T>(num / vector.x, num / vector.y, num / vector.z)); }

	friend vec4 operator / (const vec4 &vector, const T &num)
	{ return (vec4<T>(vector.x / num, vector.y / num, vector.z / num)); }

	// Accessors for use in loopes etc. Const and mutable.
	const T& operator [] (uint8_t index) const { return ((&x)[index]); }
	T& operator [] (uint8_t index) { return ((&x)[index]); }
};

/*
Typedefs for specialised classes. 
For example float vectors can be declared either vec4<float> a, or vec3f a.
*/
typedef vec4<double> vec4d;
typedef vec4<float> vec4f;

/*
Generic 4x4 matrix. Designed to be used with OpenGL.
Uses a template so we can declare it either as floats or doubles if necessary.
*/
template<typename T>
class mat4x4
{
public:
	union {T mat[4][4],	vec4[4];};

	mat4x4()
		: mat({{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}) {}

	mat4x4 (T a, T b, T c, T d, T e, T f, T g, T h, 
			T i, T j, T k, T l, T m, T n, T o, T p)
	{
		mat[0][0] = a;
		mat[0][1] = b;
		mat[0][2] = c;
		mat[0][3] = d;
		mat[1][0] = e;
		mat[1][1] = f;
		mat[1][2] = g;
		mat[1][3] = h;
		mat[2][0] = i;
		mat[2][1] = j;
		mat[2][2] = k;
		mat[2][3] = l;
		mat[3][0] = m;
		mat[3][1] = n;
		mat[3][2] = o;
		mat[3][3] = p;
	}

	// Creates an rthographic projection matrix for viewing 2d coordinates
	void ortho(T const &left, T const &right, T const &bottom, T const &top)
	{
		orthographic(left, right, bottom, top, (T)-1.0, (T)1.0);
	}

	// Creates an ortographic projection matrix for parallel viewing
	void orthographic(T const &left, T const &right, T const &bottom, 
						T const &top, T const &near, T const &far)
	{
		mat[0][0] = 2 / (right - left);
		mat[0][3] = -((right + left) / (right - left));
		mat[1][1] = 2 / (top - bottom);
		mat[1][3] = -((top + bottom) / (top - bottom));
		mat[2][2] = -2 / (far - near);
		mat[2][3] = -((far + near) / (far - near));
	}

	// Creates a perspective projection matrix
	void perspective(T const &window_height, T const &window_width, T const &near, T const &far, T const &fov)
	{
		//float	fovr = fov * (M_PI / 180);
		float	aspect_ratio = (float)window_height / (float)window_width;
		float	scale = 1.0f / tan((fov * 0.5f) * M_PI / 180.0f); // * near;
//		float	f = far;
//		float	n = near;
//		float	r = aspect_ratio * scale;
//		float	l = -r;
//		float	t = scale;
//		float	b = -t;
/*
		mat[0][0] = 2 * n / (r - 1);
		mat[1][1] = 2 * n / (t - b);
		mat[2][0] = (r + l) / (r - l);
		mat[2][1] = (t + b) / (t - b);
		mat[2][2] = -(f + b) / (f - n);
		mat[2][3] = -1.0f;
		mat[3][2] = -2 * f *n / (f - n);
		mat[3][3] = 0.0f;
*/		
		
		mat[0][0] = aspect_ratio * scale;
		mat[1][1] = scale;
		mat[2][2] = -far / (far - near);
		mat[2][3] = -far * near / (far - near);
		mat[3][2] = -1.0f;
		mat[3][3] = 0.0f;
		
	}

	void perspective_resize(T const &window_height, T const &window_width)
	{
		float aspect_ratio = (float)window_height / (float)window_width;
		mat[0][0] = aspect_ratio * mat[1][1];
	}

	// Create camera to world matrix using a "lookat" function
	void lookat(vec3<T> const &from, vec3<T> const &to, vec3<T> const &up)
	{
		vec3<T> forward = from - to;
		forward.normalize();
		vec3<T> right = up.cross_product(forward);
		right.normalize();
		vec3<T> new_up = forward.cross_product(right);
		mat[0][0] = right.x;
		mat[1][0] = new_up.x;
		mat[2][0] = forward.x;
		mat[3][0] = from.x;
		mat[0][1] = right.y;
		mat[1][1] = new_up.y;
		mat[2][1] = forward.y;
		mat[3][1] = from.y;
		mat[0][2] = right.z;
		mat[1][2] = new_up.z;
		mat[2][2] = forward.z;
		mat[3][2] = from.z;
	}

	void translate(vec3<T> const &vec)
	{
		mat[0][3] += vec.x;
		mat[1][3] += vec.y;
		mat[2][3] += vec.z;
	}

	// Accessors for use in loopes etc. Const and mutable.
	const T* operator [] (uint8_t index) const { return (mat[index]); }
	T* operator [] (uint8_t index) { return (mat[index]); }

	static void multiply(const mat4x4<T> &mat1, const mat4x4 &mat2, mat4x4 &out)
	{
		// We restrict the pointers so that they'll only be accessed in scope
		const	T * __restrict m1p = &mat1.mat[0][0];
		const	T * __restrict m2p = &mat2.mat[0][0];
				T * __restrict outp = &out.mat[0][0];

		T t0, t1, t2, t3;

		t0 = m1p[0];
		t1 = m1p[1];
		t2 = m1p[2];
		t3 = m1p[3];

		outp[0] = t0 * m2p[0] + t1 * m2p[4] + t2 * m2p[8]  + t3 * m2p[12];
		outp[1] = t0 * m2p[1] + t1 * m2p[5] + t2 * m2p[9]  + t3 * m2p[13];
		outp[2] = t0 * m2p[2] + t1 * m2p[6] + t2 * m2p[10] + t3 * m2p[14];
		outp[3] = t0 * m2p[3] + t1 * m2p[7] + t2 * m2p[11] + t3 * m2p[15];

		t0 = m1p[4];
		t1 = m1p[5];
		t2 = m1p[6];
		t3 = m1p[7];

		outp[4] = t0 * m2p[0] + t1 * m2p[4] + t2 * m2p[8]  + t3 * m2p[12];
		outp[5] = t0 * m2p[1] + t1 * m2p[5] + t2 * m2p[9]  + t3 * m2p[13];
		outp[6] = t0 * m2p[2] + t1 * m2p[6] + t2 * m2p[10] + t3 * m2p[14];
		outp[7] = t0 * m2p[3] + t1 * m2p[7] + t2 * m2p[11] + t3 * m2p[15];

		t0 = m1p[8];
		t1 = m1p[9];
		t2 = m1p[10];
		t3 = m1p[11];

		outp[8]  = t0 * m2p[0] + t1 * m2p[4] + t2 * m2p[8]  + t3 * m2p[12];
		outp[9]  = t0 * m2p[1] + t1 * m2p[5] + t2 * m2p[9]  + t3 * m2p[13];
		outp[10] = t0 * m2p[2] + t1 * m2p[6] + t2 * m2p[10] + t3 * m2p[14];
		outp[11] = t0 * m2p[3] + t1 * m2p[7] + t2 * m2p[11] + t3 * m2p[15];

		t0 = m1p[12];
		t1 = m1p[13];
		t2 = m1p[14];
		t3 = m1p[15];

		outp[12] = t0 * m2p[0] + t1 * m2p[4] + t2 * m2p[8]  + t3 * m2p[12];
		outp[13] = t0 * m2p[1] + t1 * m2p[5] + t2 * m2p[9]  + t3 * m2p[13];
		outp[14] = t0 * m2p[2] + t1 * m2p[6] + t2 * m2p[10] + t3 * m2p[14];
		outp[15] = t0 * m2p[3] + t1 * m2p[7] + t2 * m2p[11] + t3 * m2p[15];
	}

	// Return a transposed copy of the current matrix as new matrix
	mat4x4 transposed() const
	{
		mat4x4	temp(mat[0][0],
					 mat[1][0],
					 mat[2][0],
					 mat[3][0],
					 mat[0][1],
					 mat[1][1],
					 mat[2][1],
					 mat[3][1],
					 mat[0][2],
					 mat[1][2],
					 mat[2][2],
					 mat[3][2],
					 mat[0][3],
					 mat[1][3],
					 mat[2][3],
					 mat[3][3]);
		return (temp);
	}

	// Transpose the matrix itself
	mat4x4& transpose()
	{
		mat4x4	temp(mat[0][0],
					 mat[1][0],
					 mat[2][0],
					 mat[3][0],
					 mat[0][1],
					 mat[1][1],
					 mat[2][1],
					 mat[3][1],
					 mat[0][2],
					 mat[1][2],
					 mat[2][2],
					 mat[3][2],
					 mat[0][3],
					 mat[1][3],
					 mat[2][3],
					 mat[3][3]);
		*this = temp;
		return (*this);
	}
/*
	// Rotate along axis
	mat4x4& rotate(T angle, vec3<T> &v)
	{
		//float	fovr = fov * (M_PI / 180);
		// TODO make deg to rad function. Save M_PI / 180 as constant somewhere.

		T const a = angle * (M_PI / 180);
		T const c = cos(a);
		T const s = sin(a);

		vec3<T> axis = v.normalize();
		vec3<T> temp = (T(1) - c) * axis;

		mat4x4<T> Rotate;
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];

		mat4x4<T> Result;
		Result[0] = mat[0] * Rotate[0][0] + mat[1] * Rotate[0][1] + mat[2] * Rotate[0][2];
		Result[1] = mat[0] * Rotate[1][0] + mat[1] * Rotate[1][1] + mat[2] * Rotate[1][2];
		Result[2] = mat[0] * Rotate[2][0] + mat[1] * Rotate[2][1] + mat[2] * Rotate[2][2];
		Result[3] = mat[3];
		*this = Result;
		return (*this);
	}
*/
	// This method is for point-vector multiplication, we compute w.
	template<typename S>
	void mult_vec_matrix(const vec3<S> &src, vec3<S> &dst) const
	{
		S x, y, z, w;

		x = src[0] * mat[0][0] + src[1] * mat[1][0] + src[2] * mat[2][0] + mat[3][0];
		y = src[0] * mat[0][1] + src[1] * mat[1][1] + src[2] * mat[2][1] + mat[3][1];
		z = src[0] * mat[0][2] + src[1] * mat[1][2] + src[2] * mat[2][2] + mat[3][2];
		w = src[0] * mat[0][3] + src[1] * mat[1][3] + src[2] * mat[2][3] + mat[3][3];

		dst.x = x / w;
		dst.y = y / w;
		dst.z = z / w;
	}

	// This method is for direction-vector multiplication, we do not compute w.
	template<typename S>
	void mult_dir_matrix(const vec3<S> &src, vec3<S> &dst) const
	{
		S x, y, z;

		x = src[0] * mat[0][0] + src[1] * mat[1][0] + src[2] * mat[2][0];
		y = src[0] * mat[0][1] + src[1] * mat[1][1] + src[2] * mat[2][1];
		z = src[0] * mat[0][2] + src[1] * mat[1][2] + src[2] * mat[2][2];

		dst.x = x;
		dst.y = y;
		dst.z = z;
	}

	// Compute the inverse of the matrix using the Gauss-Jordan elimination method
	mat4x4 inverse() const
	{
		int index0, index1, index2;
		mat4x4 src;
		mat4x4 dst (*this);

		// Forward elimination
		for (index0 = 0 ; index0 < 3 ; index0++)
		{
			int pivot = index0;
			T pivotsize = dst[index0][index0];
			if (pivotsize < 0)
				pivotsize = -pivotsize;
			for (index1 = index0 + 1 ; index1 < 4; index1++)
			{
				T tmp = dst[index1][index0];
				if (tmp < 0)
				tmp = -tmp;
				if (tmp > pivotsize)
				{
					pivot = index1;
					pivotsize = tmp;
				}
			}
			if (pivotsize == 0)
			{
				// Cannot invert singular matrix
				return (mat4x4());
			}
			if (pivot != index0)
			{
				for ( index1 = 0 ; index1 < 4 ; index1++)
				{
					T tmp;
					tmp = dst[index0][index1];
					dst[index0][index1] = dst[pivot][index1];
					dst[pivot][index1] = tmp;

					tmp = src[index0][index1];
					src[index0][index1] = src[pivot][index1];
					src[pivot][index1] = tmp;
				}
			}
			for (index1 = index0 + 1 ; index1 < 4 ; index1++)
			{
				T f = dst[index1][index0] / dst[index0][index0];
				for (index2 = 0 ; index2 < 4 ; index2++)
				{
					dst[index1][index2] -= f * dst[index0][index2];
					src[index1][index2] -= f * src[index0][index2];
				}
			}
		}
		// Backward substitution
		for (index0 = 3 ; index0 >= 0 ; index0--)
		{
			T f;
			if ((f = dst[index0][index0]) == 0)
			{
				// Cannot invert singular matrix
				return (mat4x4());
			}
			for (index1 = 0 ; index1 < 4 ; index1++)
			{
				dst[index0][index1] /= f;
				src[index0][index1] /= f;
			}
			for (index1 = 0 ; index1 < index0 ; index1++)
			{
				f = dst[index1][index0];
				for (index2 = 0 ; index2 < 4 ; index2++)
				{
					dst[index1][index2] -= f * dst[index0][index2];
					src[index1][index2] -= f * src[index0][index2];
				}
			}
		}
		return (src);
	}

	// Set current matrix to its inverse
	const mat4x4<T>& invert()
	{
		*this = inverse();
		return (*this);
	}

	// Multiply current matrix with another matrix
	mat4x4<T> operator * (const mat4x4<T> &matrix) const
	{
		mat4x4<T> temp;
		multiply (*this, matrix, temp);

		return (temp);
	}
};

/*
Typedefs for specialised classes. 
For example float matrices can be declared either mat4x4<float> m, or mat4x4f m.
*/
typedef mat4x4<float> mat4x4f;
typedef mat4x4<double> mat4x4d;

#endif