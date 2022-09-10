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


unsigned char red_arr_breathing[] = {255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239,
 238, 237, 236, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 
 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, 193, 192,                  //64
 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217,
  218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242,  
  243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,                                                              //128
  255, 253, 251, 249, 247, 245, 243, 241, 239, 237, 235, 233, 231, 229, 227, 225,
  225, 227, 229, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255,                                               //160
  255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240,
  240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,                                               //192
  185, 186, 239, 176, 159, 199, 169, 245, 170, 122, 179, 167, 151, 238, 238, 134, 177, 186, 195, 227, 198, 232, 175, 155, 189, 
  138, 177, 248, 251, 206, 195, 160,                                                                                            //224 random
  255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240,
  240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 255};                                         //256

  unsigned char red_arr_breathing_2[] = {255, 252, 249, 246, 243, 240, 237, 234, 231, 228, 225, 222, 219, 216, 213, 210, 207,
   204, 201, 198, 195, 192, 189, 186, 183, 180, 177, 174, 171, 168, 165, 162, 159, 156, 153, 150, 147, 144, 141, 138, 135,
    132, 129, 126, 123, 120, 117, 114, 111, 108, 105, 102, 99, 96, 93, 90, 87, 84, 81, 78, 75, 72, 69, 66,                      //64
 66, 69, 72, 75, 78, 81, 84, 87, 90, 93, 96, 99, 102, 105, 108, 111, 114, 117, 120, 123, 126, 129, 132, 135, 138, 141, 144,
  147, 150, 153, 156, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 189, 192, 195, 198, 201, 204, 207, 210, 213, 216,
   219, 222, 225, 228, 231, 234, 237, 240, 243, 246, 249, 252, 255,                                                             //128
  255, 247, 239, 231, 223, 215, 207, 199, 191, 183, 175, 167, 159, 151, 143, 135,
  135, 143, 151, 159, 167, 175, 183, 191, 199, 207, 215, 223, 231, 239, 247, 255,                                               //160
  255, 240, 225, 210, 195, 180, 165, 150, 135, 120, 105, 90, 75, 60, 45, 30,
  30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255,                                                    //192
  185, 186, 239, 176, 159, 199, 169, 245, 170, 122, 179, 167, 151, 238, 238, 134, 177, 186, 195, 227, 198, 232, 175, 155, 189, 
  138, 177, 248, 251, 206, 195, 160,                                                                                            //224 random
  255, 247, 239, 231, 223, 215, 207, 199, 191, 183, 175, 167, 159, 151, 143, 135,
  135, 143, 151, 159, 167, 175, 183, 191, 199, 207, 215, 223, 231, 239, 247, 255};                                              //256

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