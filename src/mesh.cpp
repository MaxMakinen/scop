/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:04:47 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/22 11:06:56 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.hpp"
#include "vector.hpp"
#include <vector>
#include <fstream>
#include <sstream>

mesh::mesh()
{
    //ctor
}

mesh::~mesh()
{
    //dtor
}

bool mesh::load_obj_file(std::string file_path)
{
		std::ifstream file(file_path);
		if (!file.is_open())
			return false;

		// Local cache of verts
		std::vector<vec3f> verts;

		while (!file.eof())
		{
			char line[128];
			file.getline(line, 128);

			std::stringstream str;
			str << line;

			char junk;

			if (line[0] == 'v')
			{
				vec3f v;
				str >> junk >> v.x >> v.y >> v.z;
				verts.push_back(v);
			}

			if (line[0] == 'f')
			{
				vec3i face;
				str >> junk >> face.x >> face.y >> face.z;
				faces.push_back(face);
				//int f[3];
				//str >> junk >> f[0] >> f[1] >> f[2];
				//this->tris.push_back((triangle){ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
			}
		}

		return true;
}
