#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Too little arguments!\nCorrect usage: ./executable input output\n");
        return -1;
    }

    FILE *fptr = fopen(argv[1], "rb");
    if (fptr == NULL)
    {
        printf("Error opening input file!\n");
        return -1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Error opening output file!\n");
        fclose(fptr);
        return -1;
    }

    char buffer;
    int num = 0;  // Initialize charnum to 0

    while ((buffer = fgetc(fptr)) != EOF)
    {
        num++;
    }

	int charnum = num / 3;

    printf("Type in the resolution of generated image: <height> <width>\n");
    printf("The input file has %d pixels\n", charnum);

    int width;
    int height;
    scanf("%d %d", &height, &width);

    putc(0, output);                         // idlength - 0(id is just additional description for an image)
    putc(0, output);                         // colourmaptype - No colour map type
    putc(2, output);                         // datatypecode - RGB Uncompressed
    putc(0, output); putc(0, output);       // colourmaporigin - No colour map used
    putc(0, output); putc(0, output);       // colourmaplength - No colour map used
    putc(0, output);                         // colourmapdepth - No colour map used
    putc(0, output); putc(0, output);       // x_origin - image starts from the left
    putc(0, output); putc(0, output);       // y_origin - image starts from the bottom
    putc((width & 0x00FF), output);          // width
    putc((width & 0xFF00) >> 8, output);     // width
    putc((height & 0x00FF), output);         // height
    putc((height & 0xFF00) >> 8, output);    // height
    putc(24, output);                        // bitsperpixel
    putc(0 | 0x20, output);                         // imagedescriptor

    fseek(fptr, 0, SEEK_SET);

    int pixelCount = width * height * 3;

    for (int i = 0; i < pixelCount; i++)
    {
        int byte = fgetc(fptr);
        if (byte == EOF)
        {
            while (i < pixelCount)
            {
                putc(255, output);  // R = 255
                putc(255, output);  // G = 255
                putc(255, output);  // B = 255
                i += 3;
            }
            break;
        }

        putc(byte, output);
    }

    fclose(fptr);
    fclose(output);

    printf("Successfully generated TARGA file!\n");

    return 0;
}
