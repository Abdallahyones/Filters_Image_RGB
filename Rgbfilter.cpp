// FCAI - OOP Programming - 2023 - Assignment 1
// Program Name : CS213-2023-20220204-20220177-20220509-A1-Part1.cpp
// Last Modification Date : 9/10/2023
// Author1 : Abdullah Mohamed Abdullah Mohamed  ID : 20220204
// Author2 : Abdelrahman Fathy Mohamed Hammad   ID : 20220177
// Author3 : Omar Khaled Elsayed Hussien        ID : 20220509


#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"




using namespace std;
unsigned char image_Rgb[SIZE][SIZE][RGB] ;
unsigned char new_image[SIZE][SIZE][RGB] ;


int dx[] = {1, 0, -1, 0, -1, -1, 1, 1 , 2 , 0 , -2 , 0 , -2 , -2 , 2 , 2 , -2 , -2, -1 , -1 ,2 , 2, 1 , 1 };
int dy[] = {0, -1, 0, 1, -1, 1, -1, 1 , 0 , -2 , 0 , 2 , -2 , 2 , -2 , 2 , -1 , 1 ,-2 , 2 ,-1 , 1 ,-2 , 2 };


bool valid(int x , int y){
    return x >= 0 && y >= 0 && x < SIZE && y < SIZE ;
}   // check if the point(in pixle ) valid



// new_image --> The new picture
// image --> Current picture (input user)

void loadImage ();
void saveImage ();

void Black_White(){

    // filter for conversion imageRGB to  black and white
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0 ; j < SIZE ; j++) {
            int sm = 0 ;
            for (int g = 0 ; g < RGB ; g++){
                sm += image_Rgb[i][j][g];
            }
            sm /= 3;
            for (int g = 0 ; g < RGB ; g++){
                new_image[i][j][g] = image_Rgb[i][j][g] = sm ;
            }
        }
    }
}
void Invert_Image() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for(int g=0;g<RGB;k++){
                new_image[i][j][g]=255-image_Rgb[i][j][g];
                image_Rgb[i][j][g] = new_image[i][j][g];
            }
        }
    }
}

void Flip_Image() {
    int num  ;
    cout <<"1-\tFlip horizontally \n 2-\tFlip vertically\n" ;
    cin >> num ;
    switch (num) {
        case 1: // Flip horizontally
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for (int g = 0 ; g < RGB ; g++){
                        new_image[i][j][g] = image_Rgb[255- i][j][g];
                    }
                }
            }
            break;
        case 2: // Flip vertically
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for (int g = 0 ; g < RGB ; g++){
                        new_image[i][j][g] = image_Rgb[i][255 - j][g];
                    }
                }
            }
            break;
    }
    // Current image equal new_image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int g = 0 ; g < RGB ; g++){
                image_Rgb[i][j][g] = new_image[i][j][g];
            }
        }
    }
}

void Detect_Image(){
    bool chek[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0 ; j < SIZE ; j++) {
            int sm = 0 ;
            for (int g = 0 ; g < RGB ; g++){
                sm += image_Rgb[i][j][g];
            }
            sm /= 3;
            for (int g = 0 ; g < RGB ; g++){
                if (sm < 64 ){
                    new_image [i][j][g] = image_Rgb[i][j][g] = 0 ;
                }
                else if (sm < 128){
                    new_image [i][j][g] = image_Rgb[i][j][g] = 64;
                }
                else if (sm < 192){
                    new_image[i][j][g] = image_Rgb[i][j][g] = 192 ;
                }
                else {
                    new_image[i][j][g] = image_Rgb[i][j][g] = 255 ;
                }
            }
        }
    }

    for (int i = 0 ; i < SIZE ; i++){
        for (int j = 0 ; j < SIZE ; j++ ){
            chek[i][j] = false;
            for (int r = 0; r < 4 ; r++){
                int nx = i+dx[r] , ny = j + dy[r];
                if (valid(nx , ny) && image_Rgb[i][j][0] < image_Rgb[nx][ny][0]){
                    chek[i][j] = true;
                }
            }
        }
    }
    for (int i = 0 ; i < SIZE ; i++){
        for (int j = 0 ; j < SIZE ; j++ ){
            for (int g = 0 ; g < RGB ; g++){
                if (!chek[i][j]) new_image[i][j][g] = 255;
                image_Rgb[i][j][g] = new_image[i][j][g];  // Current image equal new_image
            }
        }
    }
}
void filter8_4() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int g = 0; g < RGB; k++) {
            new_image[i][j][g] = image_Rgb[(i / 2) + 128][(j / 2) + 128][g];
        }
    }}
}
void filter8_3() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int g = 0; g < RGB; k++) {
                new_image[i][j][g] = image_Rgb[(i / 2) + 128][(j / 2)][g];
            }
        }
    }
}
void filter8_2() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int g = 0; g < RGB; k++) {
            new_image[i][j][g] = image_Rgb[i/2][(j/2)+128][g];

        }}
    }
}
void filter8_1() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int g = 0; g < RGB; k++) {
                new_image[i][j][g] = image_Rgb[i / 2][j / 2][g];
            }
        }
    }
}
void Enlarge_Image(){
    //This filter allows the user to enlarge one of the four quarters of the image into a separate new image
    cout << "Which quarter to enlarge 1, 2, 3 or 4? ";
    int num ;
    cin >> num ;
    switch (num) {
        case 1:
            filter8_1();
            break;
        case 2:
            filter8_2();
            break;
        case 3:
            filter8_3();
            break;
        case 4:
            filter8_4();
            break;
    }
      // Current image equal new_image
    for (int i = 0; i < SIZE ; i++){
        for (int j  = 0 ; j < SIZE ; j++){
            for (int g = 0 ; g < RGB ; g++){
                image_Rgb[i][j-cnt][g] = new_image[i][j][g] ;
            }
        }
    }            
}
void Rotate_90() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {
        for (int g = 0; g < RGB; k++) {
            new_image[i][255-j][g]=image_Rgb[j][i][g];

        }
    }
  }
}
void Rotate_180() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int g = 0; g < RGB; k++) {
                new_image[i][j][g]=image_Rgb[255-i][255-j][g];

            }
        }
    }
}
void Rotate_270() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int g = 0; g < RGB; k++) {
                new_image[j][255-i][g]=image_Rgb[255-i][255-j][g];

            }
        }
    }
}
void Rotate_Image(){
    // This filter allows the user to input degree rotate
    int degree ;
    cout << "Rotate (90), (180) or (270) degrees? " ;
    cin >> degree;
    switch (degree) {
        case 90:
            Rotate_90();
            break;
        case 180:
            Rotate_180();
            break;
        case 270:
            Rotate_270();
    }
       // Current image equal new_image
    for (int i = 0; i < SIZE ; i++){
        for (int j  = 0 ; j < SIZE ; j++){
            for (int g = 0 ; g < RGB ; g++){
                image_Rgb[i][j][g] = new_image[i][j][g] ;
            }
        }
    }
}
void Shuffle_Image() {
    cout << "Please enter new order of quarters ? ";
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int g = 0; g < RGB; k++) {
                if (a == 4)new_image[i / 2][j / 2][g] = image_Rgb[(i / 2) + 128][(j / 2) + 128][g];
                if (a == 3)new_image[i / 2][j / 2][g] = image_Rgb[(i / 2) + 128][(j / 2)][g];
                if (a == 2)new_image[i / 2][j / 2][g] = image_Rgb[(i / 2)][(j / 2) + 128][g];
                if (a == 1) new_image[i / 2][j / 2][g] = image_Rgb[(i / 2)][(j / 2)][g];
                if (b == 4)new_image[i / 2][(j / 2) + 128][g] = image_Rgb[(i / 2) + 128][(j / 2) + 128][g];
                if (b == 3)new_image[i / 2][(j / 2) + 128][g] = image_Rgb[(i / 2) + 128][(j / 2)][g];
                if (b == 2)new_image[i / 2][(j / 2) + 128][g] = image_Rgb[(i / 2)][(j / 2) + 128][g];
                if (b == 1)new_image[i / 2][(j / 2) + 128][g] = image_Rgb[(i / 2)][(j / 2)][g];
                if (c == 4)new_image[(i / 2) + 128][j / 2][g] = image_Rgb[(i / 2) + 128][(j / 2) + 128][g];
                if (c == 3)new_image[(i / 2) + 128][j / 2][g] = image_Rgb[(i / 2) + 128][(j / 2)][g];
                if (c == 2)new_image[(i / 2) + 128][j / 2][g] = image_Rgb[(i / 2)][(j / 2) + 128][g];
                if (c == 1)new_image[(i / 2) + 128][j / 2][g] = image_Rgb[(i / 2)][(j / 2)][g];
                if (d == 4)new_image[(i / 2) + 128][(j / 2) + 128][g] = image_Rgb[(i / 2) + 128][(j / 2) + 128][g];
                if (d == 3)new_image[(i / 2) + 128][(j / 2) + 128][g] = image_Rgb[(i / 2) + 128][(j / 2)][g];
                if (d == 2)new_image[(i / 2) + 128][(j / 2) + 128][g] = image_Rgb[(i / 2)][(j / 2) + 128][g];
                if (d == 1)new_image[(i / 2) + 128][(j / 2) + 128][g] = image_Rgb[(i / 2)][(j / 2)][g];
            }
        }
    }
    // Current image equal new_image
    for (int i = 0; i < SIZE ; i++){
        for (int j  = 0 ; j < SIZE ; j++){
            for (int g = 0 ; g < RGB ; g++){
                image_Rgb[i][j][g] = new_image[i][j][g] ;
            }
        }
    }
}


void Mirror_Image (){
    // This filter mirrors 1/2 of the image as seen here in order: Left 1/2, Right 1/2, Upper 1/2 and Lower 1/2.
    int num , cnt = 0 ;
    // input case
    cout<<"Mirror left, right, upper, down side?\n" ;
    cout << "1-\tLeft\n"
         << "2-\tRight\n"
         << "3-\tUpper\n"
         << "4-\tDown\n";
    cin >> num ;
    switch (num) {
        case 1:
            // This filter mirrors 1/2 of the image of Left 1/2
            for (int i = 0 ; i < SIZE ; i++){
                cnt = 0 ;
                for (int j = 0 ; j < SIZE ; j++){
                    if (j >= SIZE/2) {
                        cnt++;
                        (j > SIZE/2) && cnt++;
                    }
                    for (int g = 0 ; g < RGB ; g++){
                        new_image[i][j][g] = image_Rgb[i][j-cnt][g];
                    }
                }
            }
            break;
        case 2:
            // This filter mirrors 1/2 of the image of Right 1/2
            for (int i = 0 ; i < SIZE ; i++){
                cnt = 0 ;
                for (int j = 0 ; j < SIZE ; j++){
                    if (j < SIZE/2) {
                        cnt++;
                        (j < SIZE/2 -1) && cnt++;
                    }
                    for (int g = 0 ; g < RGB ; g++){
                        new_image[i][j][g] = image_Rgb[i][j-cnt][g];
                    }
                }
            }
            break;
        case 3:
            // This filter mirrors 1/2 of the image of upper 1/2
            for (int i = 0; i < SIZE ; i++){
                if (i >= SIZE/2){
                    cnt++;
                    (i > SIZE/2) && cnt++;
                }
                for (int j = 0 ; j < SIZE ; j++){
                    for (int g = 0 ; g < RGB ; g++){
                        new_image[i][j][g] = image_Rgb[i-cnt][j][g];
                    }
                }
            }
            break;
        case 4 :
            // This filter mirrors 1/2 of the image of down 1/2
            for (int i = SIZE-1 ; ~i ; i--){
                if (i < SIZE/2){
                    cnt++;
                    i < (SIZE/2 -1) && cnt++;
                }
                for (int j = 0 ; j < SIZE ; j++){
                    for (int g = 0 ; g < RGB ; g++){
                        new_image[i][j][g] = image_Rgb[i+cnt][j][g];
                    }
                }
            }
            break;
    }
    // Current image equal new_image
    for (int i = 0; i < SIZE ; i++){
        for (int j  = 0 ; j < SIZE ; j++){
            for (int g = 0 ; g < RGB ; g++){
                image_Rgb[i][j-cnt][g] = new_image[i][j][g] ;
            }
        }
    }
}


char input_program (){
    // interface of program
    char num ;
    cout << "Please select a filter to apply or 0 to exit: \n" ;
    cout << "1-\tBlack & White Filter\n"
         << "2-\tInvert Filter\n"
         << "3-\tMerge Filter\n"
         << "4-\tFlip Image\n"
         << "5-\tDarken and Lighten Image\n"
         << "6-\tRotate Image\n"
         << "7-\tDetect Image Edges\n"
         << "8-\tEnlarge Image#\n"  
         << "9-\tShrink Image# \n"  // omar
         <<"a-\tMirror 1/2 Image\n"
         <<"b-\tShuffle Image#\n" 
         <<"c-\tBlur Image#\n"  // omar
         <<"d-\tCrop Image\n"
         <<"e-\tSkew Image Right#\n" // abdo
         <<"f-\tSkew Image Up#\n"   // omar
         <<"s-\tSave the image to a file\n"
         <<"0-\tExit \n";
    cin >> num ;
    return num;
}
int main() {
    char num = input_program();
    while (num){
        switch (num) {
            case '1':
                Black_White();
                break;
            case '2':
                Invert_Image();
                break;
            case '3' :
//                Merge_filter();
                break;
            case '4':
                Flip_Image();
                break;
            case '5':
//                Darken_lighten_filter();
                break;
            case '6':
                Rotate_Image();
                break;
            case '7':
                Detect_Image();
                break;
            case '8':
                Enlarge_Image();
                break;
            case '9':
                // omar funtion
                break;
            case 'a':
                Mirror_Image();
                break;
            case 'b':
               Shuffle_Image();
                break;
            case 'c':
                // omar funtion
                break;
            case 'd':
//                Crop_Image();
                break;
            case 'e':
                // abdo  function
                break;
            case 'f':
                // omar  function
                break;
            case 's':
                saveImage();
                break;
            case '0':
                return 0 ;
        }
        num = input_program();
    }
}


void loadImage () {
    char imageFileName[100];

    // get gray scale image file name

    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image

    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image_Rgb);
}

void saveImage () {
    char imageFileName[100];

    // get gray scale image target file name

    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image

    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, new_image);
}

