/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:04:46 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/22 11:04:57 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_HPP
# define MESH_HPP
# include "vector.hpp"
# include <vector>

struct triangle
{
	vec3f p[3];

	wchar_t sym;
	short col;
	triangle(vec3f a, vec3f b, vec3f c)
	{
        p[0] = a;
        p[1] = b;
        p[2] = c;
	}
};

class mesh
{
    public:
        /** Default constructor */
        mesh();
        /** Default destructor */
        ~mesh();
        bool load_obj_file(std::string file_path);
        std::vector<vec3f> get_verts() { return(verts); }
        std::vector<vec3i> get_faces() { return(faces); }

    protected:

    private:

    	std::vector<vec3f> verts;
		std::vector<vec3i> faces;
        std::vector<triangle> tris;

};

#endif // MESH_HPP
