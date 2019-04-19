/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 14:17:44 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/19 13:15:01 by lwyl-the         ###   ########.fr       */
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
# define UNITE 12
# define INTERSECT 13
# define DIFFERENCE 14
# define BLEND 15
# define MIX 16

# define POINT 1
# define DIRECTIONAL 2
# define AMBIENT 3
# define SPOT 4

# define O_RED "\033[0;31m"
# define O_NC "\033[0m"

# define NOISE_HEIGHT 128
# define NOISE_WIDTH 128
# define PIXELS_BLOCK 100.0

# define M_FILE O_RED "File not found"
# define E_FILE O_RED "Emty file"
# define USAGE O_RED "usage: ./RT [configuration_file]"

# define MEMORY O_RED "not enough sufficient memory"

# define OBJ O_RED "Objects:\n"
# define LIGHT O_RED "Lighting:\n"
# define CAMERA O_RED "Camera:\n"
# define PHYSICS O_RED "Camera:\n"

# define M_SHAPE O_RED "Shape identifier is missing!"
# define M_COLOR O_RED "Color identifier is missing!"
# define M_CENTER O_RED "Center coordinates are missing!"
# define M_DIR O_RED "Direction coordinates are missing!"
# define M_SIDES O_RED "Sides are missing!"
# define M_RADIUS O_RED "Radius is missing!"
# define M_IRADIUS O_RED "Inner radius is missing!"
# define M_ORADIUS O_RED "Outer radius is missing!"
# define M_BRADIUS O_RED "Box radius is missing!"
# define M_HEIGHT O_RED "Height is missing!"
# define M_SPEC O_RED "Specular field is missing!"
# define M_REFL O_RED "Reflection field is missing!"
# define M_REFR O_RED "Refraction coefficient is missing!"
# define M_TRANS O_RED "Transparency field is missing!"
# define M_LIGHT O_RED "Light type is missing!"
# define M_INT O_RED "Intensity field is missing!"
# define M_VANGLE O_RED "View angle is missing!"
# define M_DEPTH O_RED "reflection_depth is missing!"
# define M_PDIV O_RED "pixel_division is missing!"
# define M_MATCH O_RED "Matching bracket is missing!"
# define M_COMMA O_RED "Comma between objects is missing!"
# define M_ID O_RED "Id field is missing!"
# define M_CHILD O_RED "Child shape identifier is missing!"

# define V_CHILD "Not a valid child shape identifier"

# define U_SHAPE O_RED "Undefined shape!"
# define U_COLOR O_RED "Color vector has a range form 0 to 255"
# define U_SIDES O_RED "Sides cant be negative!"
# define U_RADIUS O_RED "Radius cant be negative!"
# define U_IRADIUS O_RED "Inner radius cant be negative!"
# define U_ORADIUS O_RED "Outer radius cant be negative!"
# define U_BRADIUS O_RED "Box radius cant be negative!"
# define U_HEIGHT O_RED "Height cant be negative!"
# define U_SPEC O_RED "Specular catnt be negative!"
# define U_REFL O_RED "Reflection cant be negative!"
# define U_REFR O_RED "Refraction cant be negative!"
# define U_TRANS O_RED "Transparency field is between 0.0 and 1.0!"
# define U_TEX O_RED "Cant read texture"
# define U_LIGHT O_RED "Undefined lightning type!"
# define U_INT O_RED "Light intensity is too big!"
# define U_VANGLE O_RED "View angle is between 0 and 90 degrees!"
# define U_DEPTH O_RED "Reflection depth is between 0 and 4!"
# define U_PDIV O_RED "Pixel division is between 0 and 8!"
# define U_VEC O_RED "Error in vector notation"
# define U_NUM O_RED "Undefined number detected!"
# define U_ID O_RED "ID can only be a positive number"
# define U_CHILD O_RED "Child shape identifier can only be a positive number"

# define PFCF O_NC "\nPlease fix config file"

# define TEXTURE_DIR "textures/"

#endif
