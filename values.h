#include <stdlib.h>


unsigned char red_arr[256u] = {179, 164, 182, 246, 232, 157, 188, 164, 118, 134, 142, 113, 208, 203, 220, 103,
 194, 123, 223, 201, 190, 241, 217, 125, 149, 221, 233, 220, 208, 254, 199, 198, 133, 111, 203, 110, 116, 178,
  209, 132, 223, 157, 163, 134, 138, 125, 241, 228, 164, 238, 111, 100, 230, 124, 124, 253, 246, 161, 235, 213,
   238, 102, 175, 226, 228, 186, 175, 243, 236, 101, 164, 200, 193, 216, 221, 111, 152, 240, 233, 231, 103, 174,
    130, 164, 186, 239, 151, 173, 242, 230, 182, 196, 191, 198, 175, 170, 233, 156, 204, 174, 101, 120, 233, 127,
     114, 135, 164, 159, 152, 131, 132, 214, 163, 151, 245, 199, 246, 155, 176, 171, 244, 204, 162, 149, 105, 208,
      127, 209, 112, 106, 181, 231, 215, 106, 122, 145, 108, 252, 225, 241, 192, 199, 198, 205, 181, 190, 155, 176,
       232, 170, 245, 106, 240, 144, 251, 147, 166, 250, 165, 139, 208, 255, 126, 116, 174, 163, 246, 114, 138, 189,
        211, 173, 213, 206, 250, 160, 186, 181, 127, 129, 204, 110, 128, 129, 214, 152, 153, 129, 163, 118, 238, 222,
         211, 206, 221, 242, 177, 135, 125, 150, 173, 126, 170, 251, 203, 238, 145, 144, 125, 202, 230, 102, 107, 110,
          207, 148, 103, 211, 112, 135, 153, 216, 148, 231, 215, 241, 251, 131, 237, 252, 171, 200, 200, 209, 182, 244, 
          130, 141, 122, 126, 190, 164, 140, 213, 175, 190, 231, 205, 225, 149, 167, 159, 149, 218, 134, 125};

unsigned char green_arr[256u] = {24, 23, 25, 23, 25, 20, 25, 24, 24, 25, 23, 21, 25, 22, 22, 23, 20, 25, 23,
 24, 25, 25, 24, 22, 25, 24, 25, 25, 23, 21, 20, 23, 21, 22, 20, 21, 21, 22, 21, 24, 21, 25, 24, 25, 22, 23,
  20, 21, 22, 22, 21, 24, 24, 24, 20, 20, 25, 24, 20, 25, 22, 25, 22, 20, 25, 21, 24, 22, 25, 24, 20, 24, 22,
   21, 21, 25, 21, 24, 25, 25, 21, 22, 22, 22, 25, 20, 25, 20, 24, 22, 22, 22, 25, 24, 24, 24, 25, 22, 23, 23,
    25, 25, 23, 20, 24, 21, 21, 25, 25, 25, 23, 22, 25, 20, 22, 25, 20, 20, 25, 23, 20, 22, 23, 25, 24, 20, 22,
     21, 23, 25, 23, 22, 20, 25, 23, 25, 25, 21, 25, 22, 23, 25, 24, 20, 21, 22, 21, 25, 25, 20, 21, 23, 25, 23,
      23, 25, 25, 21, 24, 24, 25, 22, 25, 24, 25, 20, 21, 20, 20, 22, 22, 24, 22, 24, 22, 22, 23, 20, 25, 22, 23,
       21, 23, 22, 24, 20, 24, 24, 25, 21, 24, 25, 24, 21, 23, 23, 21, 21, 23, 21, 21, 24, 22, 22, 23, 21, 22, 20,
        24, 22, 22, 24, 23, 24, 21, 25, 20, 23, 21, 20, 25, 24, 23, 23, 20, 22, 22, 23, 23, 20, 23, 20, 24, 25, 21,
         24, 24, 24, 20, 21, 23, 21, 21, 24, 24, 24, 25, 24, 22, 23, 24, 22, 24, 24, 20, 21};

unsigned char blu_arr[256u] = {2, 3, 4, 4, 1, 0, 4, 4, 1, 4, 0, 1, 5, 0, 0, 0, 3, 4, 4, 0, 2, 5, 3, 4, 5, 1, 4, 5, 0, 4,
 0, 3, 2, 1, 4, 4, 2, 0, 5, 0, 1, 4, 1, 3, 2, 3, 2, 1, 5, 0, 5, 5, 3, 3, 4, 5, 2, 5, 2, 5, 0, 0, 1, 3, 3, 2, 1, 1, 1, 3,
  4, 4, 3, 4, 1, 0, 0, 0, 4, 0, 1, 0, 5, 0, 4, 3, 2, 5, 1, 0, 1, 1, 0, 2, 1, 1, 5, 2, 1, 1, 2, 1, 0, 4, 5, 0, 0, 3, 4, 0,
   3, 0, 0, 3, 4, 3, 3, 5, 4, 3, 0, 4, 2, 2, 0, 2, 0, 5, 0, 2, 1, 2, 0, 4, 3, 1, 0, 4, 0, 4, 2, 1, 3, 2, 5, 0, 4, 0, 2, 5,
    5, 1, 5, 0, 2, 1, 3, 4, 1, 0, 2, 3, 3, 5, 2, 3, 4, 1, 5, 5, 5, 5, 5, 0, 0, 4, 3, 5, 5, 3, 0, 1, 1, 3, 2, 2, 4, 2, 5,
     0, 2, 1, 5, 1, 1, 4, 0, 5, 1, 3, 1, 0, 2, 3, 5, 5, 5, 4, 2, 5, 5, 0, 3, 4, 0, 5, 4, 4, 5, 2, 0, 1, 1, 2, 0, 2, 4, 0,
      5, 4, 4, 0, 5, 3, 2, 5, 0, 2, 5, 2, 3, 1, 0, 0, 1, 0, 3, 2, 0, 3, 2, 0, 1, 3, 0, 1};