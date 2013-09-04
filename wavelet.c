#include <stdio.h>
#include <fitsio.h>
#include <math.h>
#include <gsl/gsl_wavelet.h>

int main(void){
    
    char fn[20] = "03.fits";

    fitsfile *fptr;
    int status = 0;
    int anynull;
    static int img[4096][4096];
    static double wl[1024][1024];
    char dtype;
    int i,j;
    int ave;
    int N=1024;
    double val;
    double rad;

    fits_open_file(&fptr, fn, READONLY, &status);
    fits_read_2d_int(fptr, 0, 0, 4096, 4096, 4096, *img, &anynull, &status);
    fits_close_file(fptr, &status);

    for(i=0 ; i<4096 ; i++){
        for(j=0 ; j<4096 ; j++){
            rad = sqrt((double)((i-2048)*(i-2048) + (j-2048)*(j-2048)));
            //if(rad>1500.) img[i][j]=0;
        }
    }
    
    for(i=0 ; i<1024 ; i++){
        for(j=0 ; j<1024 ; j++){
            ave = img[i*4][j*4]+img[i*4+1][j*4]+img[i*4+2][j*4]+img[i*4+3][j*4];
            ave = ave + img[i*4][j*4+1]+img[i*4+1][j*4+1]+img[i*4+2][j*4+1]+img[i*4+3][j*4+1];
            ave = ave + img[i*4][j*4+2]+img[i*4+1][j*4+2]+img[i*4+2][j*4+2]+img[i*4+3][j*4+2];
            ave = ave + img[i*4][j*4+3]+img[i*4+1][j*4+3]+img[i*4+2][j*4+3]+img[i*4+3][j*4+3];
            wl[i][j] = ave/16.;
        }
    }

	gsl_wavelet *wavelet = gsl_wavelet_alloc(gsl_wavelet_haar, 2);
	gsl_wavelet_workspace *w = gsl_wavelet_workspace_alloc(N);
	gsl_wavelet2d_transform_forward(wavelet, wl, N, N, N, w);
	gsl_wavelet_free(wavelet);
	gsl_wavelet_workspace_free(w);

    for(i=0 ; i<1024 ; i++){
        for(j=0 ; j<1024 ; j++){
            val = wl[i][j];
            if(val>20.) val = 20.;
            if(val<-20.) val = -20.;
            
            printf("%d %d %lf\n", j, i, val);
        }
        printf("\n");
    }



    /*
    for(i=0 ; i<1024 ; i++){
        for(j=0 ; j<1024 ; j++){
            ave = img[i*4][j*4]+img[i*4+1][j*4]+img[i*4+2][j*4]+img[i*4+3][j*4];
            ave = ave + img[i*4][j*4+1]+img[i*4+1][j*4+1]+img[i*4+2][j*4+1]+img[i*4+3][j*4+1];
            ave = ave + img[i*4][j*4+2]+img[i*4+1][j*4+2]+img[i*4+2][j*4+2]+img[i*4+3][j*4+2];
            ave = ave + img[i*4][j*4+3]+img[i*4+1][j*4+3]+img[i*4+2][j*4+3]+img[i*4+3][j*4+3];
            printf("%d %d %f\n", j, i, ave/16.);
        }
        printf("\n");
    }
    */

    return(status);
}
