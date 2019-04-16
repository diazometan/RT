/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 14:17:44 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/16 11:44:24 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define PLANE 1
# define SPHERE 2
# define CYLINDER 3
# define CONE 4
# define INF_CYLINDER 5
# define INF_CONE 6
# define TORUS 7
# define BOX 8
# define CAPSULE 9
# define ELIPSIOD 10
# define FRACTAL 11

# define POINT 1
# define DIRECTIONAL 2
# define AMBIENT 3
# define SPOT 4

# define RED 0xFF0000
# define GREEN 0x008000
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define WHITE 0xFFFFFF
# define PURPLE 0x800080

# define O_RED "\033[0;31m"
# define O_NC "\033[0m"

# define M_FILE O_RED "File not found"
# define E_FILE O_RED "Emty file"
# define USAGE O_RED "usage: ./RT [configuration_file]"

# define MEMORY O_RED "not enough sufficient memory"

# define M_SHAPE O_RED "Shape identifier is missing!"
# define M_COLOR O_RED "Color identifier is missing!"
# define M_SPEC O_RED "Specular field is missing!"
# define M_REFL O_RED "Reflection field is missing!"
# define M_RADIUS O_RED "Radius is missing!"
# define M_IRADIUS O_RED "Inner radius is missing!"
# define M_ORADIUS O_RED "Outer radius is missing!"
# define M_ANGLE O_RED "Angle is missing!"
# define M_HEIGHT O_RED "Height is missing!"
# define M_CENTER O_RED "Center coordinates are missing!"
# define M_SIDES O_RED "Box sides are missing!"
# define M_DIR O_RED "Direction coordinates are missing!"
# define M_DEPTH O_RED "Reflection depth is missing!"
# define M_PDIV O_RED "Pixel division is missing!"
# define M_VERTEX O_RED "Triangle vertex is missing!"
# define M_REFRACT O_RED "Refraction coefficient is missing!"

# define U_SHAPE O_RED "Undefined shape detected!"
# define U_COLOR O_RED "Color vector has a range form 0 to 255"
# define U_LIGHT O_RED "Undefined lightning detected!"
# define U_INTENS O_RED "Light intensity is too big!"
# define U_DEPTH O_RED "Reflection depth is too big!"
# define U_PDIV O_RED "Pixel divison is too big!"
# define U_VEC O_RED "Error in vector notation"
# define U_NUM O_RED "Undefined number detected!"
# define U_REFRACT O_RED "Refraction coefficient cant be less than 1!"

# define PFCF  O_NC "\nPlease fix config file"

# define TEXTURE_DIR "textures/"

#endif
