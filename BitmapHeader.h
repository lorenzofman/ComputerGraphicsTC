#pragma once

#pragma pack (push, 1)
struct BitmapHeader
{
    ushort type;                    /* Magic identifier */
    uint fileSize;                  /* File size in bytes */
    ushort reserved1, reserved2;
    uint offset;                    /* Offset to image data em bytes */

    uint headerSize;                /* Header size in bytes */
    int width, height;              /* Width and height of image */
    ushort planes;                  /* Number of colour planes */
    ushort bits;                    /* Bits per pixel */
    uint compression;               /* Compression type */
    uint imgSize;                   /* Image size in bytes */
    int xResolution, yYesolution;   /* Pixels per meter */
    uint nColours;                  /* Number of colours */
    uint impColours;                /* Important colours */
};
#pragma pack(pop)
