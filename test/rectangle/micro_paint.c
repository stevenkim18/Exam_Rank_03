#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int 	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (1);
}

int		main(int argc, char *argv[])
{
	FILE	*file;

	int 	b_width;
	int		b_height;
	char	b_char;

	char	*image;

	int		read;

	char	type;
	float	start_x;
	float	start_y;
	float	width;
	float	height;
	char	c_char;

	int 	x;
	int		y;

	if (argc != 2)
		return (ft_putstr("Error: argument\n"));
	if (!(file = fopen(argv[1], "r")))
		return (ft_putstr("Error: operation file\n"));
	if ((fscanf(file, "%d %d %c\n", &b_width, &b_height, &b_char)) != 3)
		return (ft_putstr("Error: operation file1\n"));
	if (!(b_width > 0 && b_width <= 300 && b_height > 0 && b_height <= 300))
		return (ft_putstr("Error: operation file2\n"));
	image = (char*)malloc(sizeof(char) * (b_width * b_height));
	memset(image, b_char, b_width * b_height);
	read = fscanf(file,"%c %f %f %f %f %c\n", &type, &start_x, &start_y, &width, &height, &c_char);
	while (read == 6)
	{
		if (!(width > 0 && height > 0) || !(type == 'r' || type == 'R'))
		{
			free(image);
			return (ft_putstr("Error: operation file3\n"));
		}
		y = 0;
		while (y < b_height)
		{
			x = 0;
			while (x < b_width)
			{
				if (type == 'r')
				{
					if (x - start_x < 1.0000000 || (start_x + width) - x < 1.0000000 || y - start_y < 1.0000000 || (start_y + height) - y < 1.0000000)
					{
						if ((float)x >= start_x && (float)x <= (start_x + width) && (float)y >= start_y && (float)y <= (start_y + height))
							image[y * b_width + x] = c_char;			
					}
				}
				else if (type == 'R')
				{
					if ((float)x >= start_x && (float)x <= (start_x + width) && (float)y >= start_y && (float)y <= (start_y + height))
						image[y * b_width + x] = c_char;			
				}
				x++;
			}
			y++;
		}
		read = fscanf(file,"%c %f %f %f %f %c\n", &type, &start_x, &start_y, &width, &height, &c_char);
	}
	if (read != -1)
	{
		free(image);
		return (ft_putstr("Error: operation file4\n"));
	}
	y = 0;
	while (y < b_height)
	{	
		write(1, image + y * b_width, b_width);
		write(1, "\n", 1);
		y++;
	}
	free(image);
	fclose(file);
	return (0);
}
