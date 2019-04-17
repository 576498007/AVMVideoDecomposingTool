/***************************************************************
----------- COMN_TYPES.h  -----------
Defines all parameters needed to be used during calibration,
including Camera, Vehicle and View Parameters.
These parameters should have default values or be modified during calibration.

NOTICE: all data of 4 cameras, are storage in the order of FRONT \ BACK \ LEFT \ RIGHT !
**************************************************************

Author:     Mu Junzhou
Date:       2014-5-4

************************************************************** */
#ifndef _OVS_CALI_TYPES_H
#define _OVS_CALI_TYPES_H

#define W_SRC_IMG 1280
#define H_SRC_IMG 720
#define INVALID_HIGH 20

#define PI ((double)(3.1415926535897932384626433832795))
#define WID_GAP 2				// unit: pixel
#define OFFSET 0.25
#define  SMLS_OFFSET 0.245
#define  SMLS_GAP 0

#define PRECISION_MULTI 32

#define PIXEL_SIZE 1 // pixel size unit: mm 1, um 1000;
//camera parameters related
#define POLY_DEGREE					4	//Taylor('s) series
#define INVERSE_MAPPING_PARAM_MAX	30
#define INTRINSIC_PARAM_COUNT		5	//intrinsic parameters count
#define EXTRINSIC_PARAM_COUNT		9	//extrinsic parameters count

typedef enum
{
	LIB_WHITE_BALANCE_ON,   // for bird image
	LIB_WHITE_BALANCE_OFF
}TVS_LIB_WHITE_BALANCE;

typedef enum
{
	LIB_INTERPOLATE_OFF,
	LIB_INTERPOLATE_ON
} TVSLIB_INTERPOLATION;     // interpolation

// camera parameters
typedef struct _CameraParamINT
{
	int iHeight;                                        // image height  [240]
	int iWidth;                                         // image width,not the width of the original 360*240 image [320]
	int iDirectMappingCount;                            // length of polynomial
	int iInverseMappingCount;                           // length of inverse polynomial
	double daDirectMapping[POLY_DEGREE + 1];               // the polynomial coefficients: pol[0] + x"pol[1] + x^2*pol[2] + ... + x^(N-1)*pol[N-1]
	double daInverseMapping[INVERSE_MAPPING_PARAM_MAX];  // the coefficients of the inverse polynomial
	double daIntParam[INTRINSIC_PARAM_COUNT];             // order:  c, d, e, xc, yc
	double daValidRange[4];			//valid columns, valid rows, start column, start row [360 240 0 0]
}CameraParamINT;

typedef struct _CameraParamEXT
{// 2014-5-4 ! IMPORTANT ! consider all extrinsic parameters are defined as VEHICLE COORDINATE vs CAMERA COORDINATE system, 
	// notice the direction of the 2 system's axis 
	int iCamPosition;       // camera position on the vehicle.0,1,2,3
	double daExtParam[6];   // order: x, y, z, pan, rot, tilt.
	double daExtMtxV2C[9];  // traditional extrinsic parameter matrix. vehicle against camera, r1 r2 t.
	double daExtMtxC2V[9];  // contrary matrix of above.
}CameraParamEXT;

typedef struct _UndistViewParam
{
	int iRangeWidth[2];     // Undistorted range width
	int iRangeHeight[2];    // Undistorted range height
	int iImgWidth;     // output Undistorted image width
	int iImgHeight;    // output Undistorted image height
	int iaViewAngle[4]; //unit: degree, 150 as default
	float faRangeOffsetRatio[4];	//0.20,0.00 front and rear undistorted image, vertical and horizontal range offset ratio
	// 0.20 0.00
	float faVirCamFOVandDIR[4][4];    // the FOV angle of the front right wheel image
	// the orientation of the virtual camera ( rotating degree around x,y,z axis ) 
	// TOTAL 3 virtual cameras: front right wheel, front left wheel, front large view , and rear large view
	double daVirtCamExtParam[4][9]; //virtual ext parameter for the 3 virtual cameras

}UndistViewParam;

//vehicle parameters, need to be set only when tracks are required.
typedef struct _VechicleParam
{
	int iVehicleWidth;		// actual width of the vehicle
	int iVehicleLength;		// unit: mm
	int iaTread[2];			// width of the wheel distance, left to right
	int iWheelBase;			// wheel base
	int iFrontOverhang;		// distance between the front axis and the front end of the vehicle area
	int iRearOverhang;		// distance between the rear axis and the rear end of the vehicle area
	int iWheelWidth;

	float fAckermanCoe;		// Ackerman Coefficient
	float fMaxLeftAngle;	// the maximum counter-clockwise degree which the steering wheel can get , deg -
	float fMaxRightAngle;	// the maximum clockwise degree which the steering wheel can get , deg +

}VehicleParam;

typedef struct _TracksAndAssist
{
	int iDynaTrackLen;				// length of the dynamic reverse tracks, unit: mm
	int iaDynaTrackStartDist[2];	// the distance from the starting point of the reverse track to the end of vehicle (area) in the longitudinal and lateral direction
	int iStartToFrontWheel;
	int iStartToRearWheel;
}TracksAndAssist;

// bird view image parameters
typedef struct _BirdViewParam
{
	int iImgWidth;               // output image width, pixel
	int iImgHeight;              // output image height, pixel
	int iaTVSArea[9];		//	params about the TVS view area: car_width, car_length, side_area_width, 
	// H0,H1,H2,H3(4 params which determine the slopes)
	// tvs_area_width, tvs_area_length, 
	// the unit for all above is mm.
	int iVehicleImgIdx;
}BirdViewParam;

// common struct ================================================
typedef struct _OVSBasicInfo
{
	CameraParamINT  stCameraParamINT[4];
	CameraParamEXT  staCameraParamEXT[4];
	BirdViewParam   stBirdView;
	UndistViewParam stUndistView;
	VehicleParam    stVehicle;
	TracksAndAssist stTracksAndAssist;
}OVSBasicInfo;  // default params are storaged in this struct, and won't be changed during any calibration.

typedef struct _AvmAndCarSizeInfo
{// bird view table related
	int iAvmImageWidth;	//topview image
	int iAvmImageHeight;
	int iCarImageWidth;		//car image in the center of the topview image
	int iCarImageHeight;
	int iTopOffset;				//offset of the car image in the topview image
	int iLeftOffset;
	float fRatioU;				//ratio between the topview image(unit:pixel) and the range of the view area in world (unit:mm), in image U direction
	float fRatioV;				//same as above,in image V direction
	float fSlopeFL;
	float fSlopeFR;
	float fSlopeLB;
	float fSlopeRB;
}AvmAndCarSizeInfo;

typedef struct _OvsCameraExtParam
{//×¢ÊÍ
	double x;
	double y;
	double z;
	double pan;
	double rot;
	double tilt;
}OvsCameraExtParam;

#endif
