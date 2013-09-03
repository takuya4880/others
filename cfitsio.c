#include <stdio.h>
#include <fitsio.h>

int main(void){
    
    char fn[20] = "03.fits";

    fitsfile *fptr;
    int status = 0;
    int anynull;
    static int img[4096][4096];
    char dtype;

    fits_open_file(&fptr, fn, READONLY, &status);
    
    fits_read_2d_int(fptr, 0, 0, 4096, 4096, 4096, *img, &anynull, &status);

    printf("%d\n",img[1500][1507]);

    fits_close_file(fptr, &status);

    return(status);
}
