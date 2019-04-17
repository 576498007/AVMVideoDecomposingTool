#ifndef _FUNC_H
#define _FUNC_H
#include "OVS_Cali_Types.h"
#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LARGE_TRACK_SEGMENT	200
#define GEN_BIRDVIE_WITH_WHOLE_OVERLAP_AREA 0 
#define FRONT_CAMERA_WEIGHT_BIRDVIEW	5
#define LEFT_CAMERA_WEIGHT_BIRDVIEW		5
#define RIGHT_CAMERA_WEIGHT_BIRDVIEW	5
#define REAR_CAMERA_WEIGHT_BIRDVIEW		5
#define PRECISION_MULTI_5_BIT 32

	typedef struct _AvmTableLead
	{// main avm table, with this only seam table can be generated
		int             iValidFlag;
		int             iWidth;
		int             iHeight;
		int             iTablePointNum;
		unsigned int    *puiSrcAddress;    // camera idx, pixel offset in half D1 image, and mixture factor for seamless, 4,20,8 bits for each
		unsigned int    *puiInterCoe;   // 4 interpolation coefficients around this pixel, each one has only 1 byte length
	}AvmTableLead;

	typedef struct _AvmTableSupport
	{// supporting table, with this can generate seamless image,
		// also needed by white balance 
		int             iValidFlag;
		int             iAreaPointNum;
		int             iaAreaPointNumEach[8];
		int             iTablePointNum;
		unsigned int    *puiDstAddress; // pixle offset in dest image, #iTablePointNum data
		unsigned int    *puiSrcAddress; // weight idx, camera idx, pixel offset in half D1 image, and 2nd mixture factor, 1,3,20,8 bits for each, 2*iTablePointNum data
		unsigned int    *puiInterCoe;   // 4 interpolation coefficients around this pixel, each one has only 1 byte length, 2*iTablePointNum data
	}AvmTableSupport;

	int init_malloc(OVSBasicInfo * pOVSBasicInfo, AvmTableLead *p_stAvmTableLead, AvmTableSupport *p_stAvmTableSupport);

	void LDWBirdview_CalcVerAndTex(OVSBasicInfo * pOVSBasicInfo, AvmTableLead *p_stAvmTableLead, AvmTableSupport *p_stAvmTableSupport);

	int MapBirdImgRGB(IplImage **IMGs, IplImage *dst_IMG, int iSeam, AvmTableLead *pAvmTableLead, AvmTableSupport *pAvmTableSupport, TVSLIB_INTERPOLATION emTvsLibInterpolation, TVS_LIB_WHITE_BALANCE emTvsLibWhiteBalance);

#ifdef __cplusplus
}
#endif

#endif
