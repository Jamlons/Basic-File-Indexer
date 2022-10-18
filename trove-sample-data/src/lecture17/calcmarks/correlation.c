#include  "calcmarks.h"    // local header file provides declarations

#include  <math.h>

void correlation(int nmarks)
{
    double   sumx   = 0.0;
    double   sumy   = 0.0;
    double   sumxx  = 0.0;
    double   sumyy  = 0.0;
    double   sumxy  = 0.0;

    double   ssxx, ssyy, ssxy;
    double   r, m, b;

    for(int n=0 ; n < nmarks ; ++n) {
        sumx    += projmarks[n];
        sumy    += exammarks[n];

        sumxx   += (projmarks[n] * projmarks[n]);
        sumyy   += (exammarks[n] * exammarks[n]);
        sumxy   += (projmarks[n] * exammarks[n]);
    }

    ssxx    = sumxx - (sumx*sumx) / nmarks;
    ssyy    = sumyy - (sumy*sumy) / nmarks;
    ssxy    = sumxy - (sumx*sumy) / nmarks;

    if((ssxx * ssyy) == 0.0)
    {
        r   = 1.0;
    }
    else
    {
        r   = ssxy / sqrt(ssxx * ssyy);
    }
    printf("correlation is %.4f\n", r);

    if(ssxx != 0.0) {
        m   = ssxy / ssxx;
        b   = (sumy / nmarks) - (m*(sumx / nmarks));
        printf("line of best fit is y = %.4fx + %.4f\n", m, b);
    }
}
