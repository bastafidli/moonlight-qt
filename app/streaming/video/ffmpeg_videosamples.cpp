#include "ffmpeg.h"

// 720p 60 FPS H.264 with 1 reference frame
const uint8_t FFmpegVideoDecoder::k_H264TestFrame[] = {
    0x00, 0x00, 0x00, 0x01, 0x67, 0x64, 0x00, 0x20, 0xac, 0x2b, 0x40, 0x28, 0x02, 0xdd, 0x80, 0xb5, 0x06, 0x06, 0x06, 0xa5, 0x00, 0x00, 0x03, 0x03, 0xe8, 0x00, 0x01, 0xd4, 0xc0, 0x8f, 0x4a, 0xa0,
    0x00, 0x00, 0x00, 0x01, 0x68, 0xee, 0x3c, 0xb0,
    0x00, 0x00, 0x00, 0x01, 0x65, 0xb8, 0x02, 0x01, 0x67, 0x25, 0x1b, 0xf4, 0xfa, 0x7d, 0x40, 0x1a, 0x78, 0xe5, 0x10, 0x52, 0xc2, 0xee, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0xc6, 0xef, 0xbb, 0x81, 0x85, 0x2d, 0x47, 0xda, 0xca, 0x4c, 0x00, 0x00, 0x03, 0x00, 0x02, 0x7b, 0xcf, 0x80, 0x00, 0x45, 0x40, 0x01, 0x8d, 0xa6, 0x00, 0x01, 0x64, 0x00, 0x0e, 0x03, 0xc8, 0x00, 0x0e, 0x10, 0x00, 0xbd, 0xc5, 0x00, 0x01, 0x11, 0x00, 0x0e, 0xa3, 0x80, 0x00, 0x38, 0xa0,
    0x00, 0x00, 0x01, 0x65, 0x00, 0x6e, 0x2e, 0x00, 0x83, 0x7f, 0xb4, 0x8e, 0x79, 0xa5, 0xff, 0x84, 0x3f, 0x7f, 0x34, 0x3f, 0x97, 0x1b, 0xaf, 0x31, 0x5f, 0x6e, 0xaa, 0xb6, 0xac, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x78, 0x36, 0x9d, 0xa4, 0x65, 0xf9, 0x1e, 0x5b, 0x3a, 0xb0, 0x40, 0x00, 0x00, 0x03, 0x00, 0x00, 0x41, 0x80, 0x00, 0xc5, 0xc8, 0x00, 0x00, 0xfa, 0x00, 0x03, 0x24, 0x00, 0x0e, 0x20, 0x00, 0x3f, 0x80, 0x01, 0x32, 0x00, 0x08, 0x68, 0x00, 0x3e, 0xc0, 0x03, 0x8a,
    0x00, 0x00, 0x01, 0x65, 0x00, 0x37, 0x0b, 0x80, 0x21, 0x7f, 0xe3, 0x85, 0x1c, 0xd9, 0xff, 0xe1, 0x1b, 0x01, 0xfa, 0xc0, 0x3e, 0x11, 0x7e, 0xfe, 0x45, 0x5c, 0x43, 0x69, 0x31, 0x4b, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x02, 0x24, 0xae, 0x1a, 0xbb, 0xae, 0x75, 0x9e, 0x35, 0xae, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x03, 0x64, 0x00, 0x09, 0x98, 0x00, 0x1e, 0xc0, 0x00, 0x64, 0x80, 0x01, 0xc4, 0x00, 0x07, 0xf0, 0x00, 0x42, 0xf0, 0x00, 0x00, 0xe1, 0x98, 0x00, 0x05, 0x4b, 0x28, 0x00, 0x06, 0x04,
    0x00, 0x00, 0x01, 0x65, 0x00, 0x14, 0xa2, 0xe0, 0x08, 0x5f, 0xe3, 0x85, 0x1c, 0xd9, 0xff, 0xe1, 0x1b, 0x01, 0xfa, 0xc0, 0x3e, 0x11, 0x7e, 0xfe, 0x45, 0x5c, 0x43, 0x69, 0x31, 0x4b, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x02, 0x24, 0xb9, 0x7d, 0xb4, 0x70, 0x4d, 0x15, 0xc5, 0x0a, 0x4e, 0x60, 0x00, 0x00, 0x03, 0x00, 0x00, 0x26, 0xa8, 0xb0, 0x00, 0x13, 0xcd, 0xcc, 0x00, 0x07, 0x48, 0x88, 0x00, 0x06, 0x29, 0x69, 0x00, 0x01, 0x16, 0xac, 0x80, 0x00, 0x9e, 0x4e, 0x80, 0x00, 0x3f, 0x84, 0x20, 0x00, 0x6f, 0x41, 0xa0, 0x00, 0x20, 0x00, 0x02, 0x16, 0xb8, 0x00, 0x08, 0x08
};

// 720p 60 FPS HEVC with 1 reference frame
const uint8_t FFmpegVideoDecoder::k_HEVCTestFrame[] = {
    0x00, 0x00, 0x00, 0x01, 0x40, 0x01, 0x0c, 0x01, 0xff, 0xff, 0x01, 0x40, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x78, 0xac, 0x09,
    0x00, 0x00, 0x00, 0x01, 0x42, 0x01, 0x01, 0x01, 0x40, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x78, 0xa0, 0x02, 0x80, 0x80, 0x2e, 0x1f, 0x13, 0x96, 0xb4, 0xa4, 0x25, 0x92, 0xe3, 0x01, 0x6a, 0x0c, 0x0c, 0x0d, 0x48, 0x20, 0x00, 0x00, 0x03, 0x00, 0x20, 0x00, 0x00, 0x07, 0x85, 0xf1, 0xa2, 0xd0,
    0x00, 0x00, 0x00, 0x01, 0x44, 0x01, 0xc0, 0xf7, 0xc0, 0xcc, 0x90,
    0x00, 0x00, 0x00, 0x01, 0x2a, 0x01, 0xac, 0x0c, 0xf0, 0xe6, 0xf6, 0x5e, 0xff, 0xd9, 0x97, 0xeb, 0x44, 0x7d, 0x1f, 0xa4, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x03, 0x52, 0x7c, 0x4e, 0x5b, 0xfe, 0xbe, 0xc2, 0x87, 0x20, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x2b, 0x60,
};
