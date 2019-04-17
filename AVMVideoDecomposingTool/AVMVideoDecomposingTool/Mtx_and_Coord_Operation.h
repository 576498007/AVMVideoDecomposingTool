#ifndef _MTX_AND_COORD_OPERATION_H
#define _MTX_AND_COORD_OPERATION_H

#include "OVS_Cali_Types.h"
#include <float.h>
#include <math.h>

#define MAX_CORNER_COUNT 24
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define SIG(a,b) ((b) > 0 ? fabs(a) : -fabs(a))
#define SIGN(x) ((x)<0?-1:((x)>0?1:0))

#define MAX_ITERA 60
#define MIN_DOUBLE (1e-30)

#include "stdlib.h"
#include "math.h"

#ifdef __cplusplus
extern "C" {
#endif

	void TvsLibSetDefaultParam(OVSBasicInfo * pOVSBasicInfo);

	void matrixMul(double * A, double * B, double * C, int PointNum, int two, int two_B);
	int ContraryMatrix1(double * pMatrix, double * _pMatrix, int dim);
	void Cam2ImgScara(double *point2D, double *point3D, CameraParamINT * pstCameraParamINT);
	void Cam2Vehicle(double srcCam3D[3], double dstVehicle3D[3], double daExtC2V[9]);
	void Vehicle2Cam(double srcVehicle3D[3], double dstCam3D[3], double daExtV2C[9]);
	void GenTradExt(CameraParamEXT *pCameraExt);
	void BirdImg2Vehicle(int srcBirdImg2D[2], double dstVehicle3D[3], BirdViewParam *pBirdViewParam);
	int SplitUV(double *m_pData, double* mtxU, double* mtxV, int row, int col);


#ifdef __cplusplus
}
#endif
#endif
