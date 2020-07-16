#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int     ft_strlen(char *str)
{
    int     i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int     str_error(char *str)
{
    write(1, str, ft_strlen(str));
    return (1);
}

int     main(int argc, char *argv[])
{
    FILE    *file;
    char    *image;
    int     read;
    
    // 배경
    int     b_width;
    int     b_height;
    char    b_char;
    int     x;
    int     y;

    // 도형
    char    type;
    float   center_x;
    float   center_y;
    float   r;
    char    c_char;
    float   distance;

    // 파일 매개변수 확인
    if (argc != 2)
        return (str_error("Error: argument\n"));
    // 파일 열기
    if (!(file = fopen(argv[1], "r")))
        return (str_error("Error: Operation file corrupted\n"));
    // 배경색 파싱하기
    if (fscanf(file, "%d %d %c\n", &b_width, &b_height, &b_char) != 3)
        return (str_error("Error: Operation file corrupted\n"));
    // 배경 에러 처리
    if (!(b_width > 0 && b_width <= 300 && b_height > 0 && b_height <= 300))
        return (str_error("Error: Operation file corrupted\n"));
    // 배경의 가로 x 세로 크기 만큼 할당 하기
    image = (char*)malloc(sizeof(char) * (b_width * b_height));
    // 배경 색 칠하기
    memset(image, b_char, b_width * b_height);
    // 원 값 파싱해오기
    read = fscanf(file, "%c %f %f %f %c\n", &type, &center_x, &center_y, &r, &c_char);
    while (read == 5)
    {   
        // 원 타입과 가로 세로 에러 처리
        if (!(r > 0) || !(type == 'c' || type == 'C'))
        {
            free(image);
            return (str_error("Error: Operation file corrupted\n"));
        }
        // 원 그리기
        y = 0;
        while (y < b_height)
        {
            x = 0;
            while (x < b_width)
            {
                distance = sqrtf(powf(x - center_x, 2.) + powf(y - center_y, 2.));
                if (distance <= r)
                {
                    if (type == 'c')
                    {
                        // 테두리인지 확인하기
                        if (r - distance < 1.0000000)
                            image[y * b_width + x] = c_char;
                    }
                    else if (type == 'C')
                        image[y * b_width + x] = c_char;
                }
                x++;
            }
            y++;
        }
        read = fscanf(file, "%c %f %f %f %c\n", &type, &center_x, &center_y, &r, &c_char);
    }
    // EOF이 아닐 때
    if (read != -1) 
	{
		free(image);
		return (str_error("Error: Operation file corrupted\n"));
	}
    // 그리기
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
