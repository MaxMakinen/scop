/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:30:36 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/28 18:34:56 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_HPP
# define QUATERNION_HPP
# include "vector.hpp"
# include <cmath>

template<typename T>
struct	quat
{
	quat() : w(1), x(0), y(0), z(0) {}
	quat(T ww, T xx, T yy, T zz) : w(ww), x(xx), y(yy), z(zz) {}
	T	w, x, y, z;
};

template<typename T>
class quaternion
{
private:
    quat<T> q;
    mat4x4<T> mat;

public:
    quaternion() {};
    ~quaternion() {};

    quat<T>	conjugate();
    quat<T>	normalized(quat<T> qu);
    void	normalize();
	quat<T> local_rotation( vec3<T> &axis, T &angle );
	quat<T>	multiply( quat<T> &q1, quat<T> &q2 );
	vec3<T>	rotate( vec3<T> &point );
	mat4x4<T>	rotation_matrix( vec3<T> &axis, T &angle );

    inline T	get_len() { return(sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z)); }

	void operator=(quat<T> input) { q = input; }
};

template<typename T>
quat<T>	quaternion<T>::conjugate()
{
	return (quat<T>(-q.x, -q.y, -q.z, q.w));
}

/* Return normalized version of current quaternion */
template<typename T>
quat<T>	quaternion<T>::normalized(quat<T> qu)
{
	float	len;

	len = get_len();
	len = 1 / len;
	return (quat<T>(qu.x * len, qu.y * len, qu.z * len, \
	qu.w * len));
}

/* Normalize current quaternion */
template<typename T>
void	quaternion<T>::normalize()
{
	q = normalized(q);
}

/* Create local rotaion quaternion from axis & angle*/
template<typename T>
quat<T>	quaternion<T>::local_rotation(vec3<T> &axis, T &angle)
{
	float	half_angle = angle * 0.5f;
	float	temp = sin(half_angle);
	q.w = cos(half_angle);
	q.x = axis.x * temp;
	q.y = axis.y * temp;
	q.z = axis.z * temp;
	normalize();
	return (q);
}

template<typename T>
quat<T>	quaternion<T>::multiply(quat<T> &q1, quat<T> &q2)
{
	quat<T> output;
	
	output.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	output.x = q1.x * q2.w + q1.w * q2.x + q1.y * q2.z - q1.z * q2.y;
	output.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	output.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	
	return(output);
}

template<typename T>
vec3<T>	quaternion<T>::rotate(vec3<T> &point)
{
	double	temp[10];
	vec3<T>	output;

//	quat_rot_prep(quat, temp);
	temp[0] = q.w * q.w;
	temp[1] = q.x * q.x;
	temp[2] = q.y * q.y;
	temp[3] = q.z * q.z;
	temp[4] = q.w * q.x;
	temp[5] = q.w * q.y;
	temp[6] = q.w * q.z;
	temp[7] = q.x * q.y;
	temp[8] = q.x * q.z;
	temp[9] = q.y * q.z;

	output.x = temp[0] * point.x + 2 * temp[5] * point.z - 2 * temp[6] * \
	point.y + temp[1] * point.x + 2 * temp[7] * point.y + 2 * temp[8] * \
	point.z - temp[3] * point.x - temp[2] * point.x;
	output.y = 2 * temp[7] * point.x + temp[2] * point.y + 2 * temp[9] * \
	point.z + 2 * temp[6] * point.x - temp[3] * point.y + temp[0] * \
	point.y - 2 * temp[4] * point.z - temp[1] * point.y;
	output.z = 2 * temp[8] * point.x + 2 * temp[9] * point.y + temp[3] * \
	point.z - 2 * temp[5] * point.x - temp[2] * point.z + 2 * temp[4] * \
	point.y - temp[1] * point.z + temp[0] * point.z;

	return (output);
}

/* Create rotation matrix from vec3 axis and angle in radians*/
template<typename T>
mat4x4<T>	quaternion<T>::rotation_matrix(vec3<T> &axis, T &angle)
{
	axis.normalize();
	quat<T> temp = local_rotation(axis, angle);
	temp = normalized(temp);
	mat4x4<T>	rot(1 - 2 * (temp.y * temp.y) - 2 * (temp.z * temp.z),
					2 * temp.x * temp.y - 2 * temp.w * temp.z,
					2 * temp.x * temp.z + 2 * temp.w * temp.y,
					0,
					2 * temp.x * temp.y + 2 * temp.w * temp.z,
					1 - 2 * (temp.x * temp.x) - 2 * (temp.z * temp.z),
					2 * temp.y * temp.z + 2 * temp.w * temp.x,
					0,
					2 * temp.x * temp.z - 2 * temp.w * temp.y,
					2 * temp.y * temp.z - 2 * temp.w * temp.x,
					1 - 2 * (temp.x * temp.x) - 2 * (temp.y * temp.y),
					0,
					0,
					0,
					0,
					1);

	return (rot);
}

/*
Typedefs for declaring most likely forms.
A float quaternion can be declared either quaternion<float> q, or quatf q
*/
typedef quaternion<float> quatf;
typedef quaternion<double> quatd;

#endif