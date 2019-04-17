#include "stdafx.h"
#include "Mtx_and_Coord_Operation.h"

#define LAB_SCALE 1

void TvsLibSetDefaultParam(OVSBasicInfo * pOVSBasicInfo)
{
	int i;
	int k;
	for (k = 0; k<4; k++)
	{
		pOVSBasicInfo->stCameraParamINT[k].iWidth = 1280;
		pOVSBasicInfo->stCameraParamINT[k].iHeight = 720;
		pOVSBasicInfo->stCameraParamINT[k].iDirectMappingCount = 5;
		pOVSBasicInfo->stCameraParamINT[k].daDirectMapping[0] = -341.7126363462;
		pOVSBasicInfo->stCameraParamINT[k].daDirectMapping[1] = 0.0000000000;
		pOVSBasicInfo->stCameraParamINT[k].daDirectMapping[2] = 0.0007684678;
		pOVSBasicInfo->stCameraParamINT[k].daDirectMapping[3] = -0.0000002661;
		pOVSBasicInfo->stCameraParamINT[k].daDirectMapping[4] = 0.0000000006;
		pOVSBasicInfo->stCameraParamINT[k].iInverseMappingCount = 9;
		pOVSBasicInfo->stCameraParamINT[k].daInverseMapping[0] = 640.6412457045;
		pOVSBasicInfo->stCameraParamINT[k].daInverseMapping[1] = 509.1525491144;
		pOVSBasicInfo->stCameraParamINT[k].daInverseMapping[2] = 61.2965144805;
		pOVSBasicInfo->stCameraParamINT[k].daInverseMapping[3] = 10.7887547597;
		pOVSBasicInfo->stCameraParamINT[k].daInverseMapping[4] = 60.3102715601;
		pOVSBasicInfo->stCameraParamINT[k].daInverseMapping[5] = 59.2976199022;
		pOVSBasicInfo->stCameraParamINT[k].daInverseMapping[6] = 17.0524971165;
		pOVSBasicInfo->stCameraParamINT[k].daInverseMapping[7] = -1.3699310356;
		pOVSBasicInfo->stCameraParamINT[k].daInverseMapping[8] = -1.0491373923;
		pOVSBasicInfo->stCameraParamINT[k].daIntParam[0] = 0.9996316191;
		pOVSBasicInfo->stCameraParamINT[k].daIntParam[1] = 0.0000295379;
		pOVSBasicInfo->stCameraParamINT[k].daIntParam[2] = -0.0000254068;
		pOVSBasicInfo->stCameraParamINT[k].daValidRange[0] = 1280;
		pOVSBasicInfo->stCameraParamINT[k].daValidRange[1] = 720;
		pOVSBasicInfo->stCameraParamINT[k].daValidRange[2] = 0;
		pOVSBasicInfo->stCameraParamINT[k].daValidRange[3] = 0;
	}
	
#if 0
	//GE3
	pOVSBasicInfo->stCameraParamINT[0].daIntParam[3] = 358.685129;//354.755558;
	pOVSBasicInfo->stCameraParamINT[0].daIntParam[4] = 648.483883;// 650.000000;

	pOVSBasicInfo->stCameraParamINT[1].daIntParam[3] = 362.972319;// 355.173730;
	pOVSBasicInfo->stCameraParamINT[1].daIntParam[4] = 622.305402;// 645.847107;

	pOVSBasicInfo->stCameraParamINT[2].daIntParam[3] = 356.745047;// 349.666198;
	pOVSBasicInfo->stCameraParamINT[2].daIntParam[4] = 626.489609;// 613.727571;

	pOVSBasicInfo->stCameraParamINT[3].daIntParam[3] = 363.638339;// 350.425625;
	pOVSBasicInfo->stCameraParamINT[3].daIntParam[4] = 640.677600;// 650.000000;

	pOVSBasicInfo->staCameraParamEXT[0].daExtParam[0] = 13.164833;// 5.848126;
	pOVSBasicInfo->staCameraParamEXT[0].daExtParam[1] = 2171.638490;// 2283.817508;
	pOVSBasicInfo->staCameraParamEXT[0].daExtParam[2] = 544.769104;// 722.626110;
	pOVSBasicInfo->staCameraParamEXT[0].daExtParam[3] = 0.053289;// -0.051029;
	pOVSBasicInfo->staCameraParamEXT[0].daExtParam[4] = -0.283880;// 0.382477;
	pOVSBasicInfo->staCameraParamEXT[0].daExtParam[5] = 16.160826;// 27.584711;

	pOVSBasicInfo->staCameraParamEXT[1].daExtParam[0] = -41.674401;// -56.159738;
	pOVSBasicInfo->staCameraParamEXT[1].daExtParam[1] = -2145.486092;// -2195.503668;
	pOVSBasicInfo->staCameraParamEXT[1].daExtParam[2] = 663.506062;// 1065.358880;
	pOVSBasicInfo->staCameraParamEXT[1].daExtParam[3] = 181.680283;// 178.833866;
	pOVSBasicInfo->staCameraParamEXT[1].daExtParam[4] = -0.857723;// 1.143762;
	pOVSBasicInfo->staCameraParamEXT[1].daExtParam[5] = 48.865259;// 37.222573;

	pOVSBasicInfo->staCameraParamEXT[2].daExtParam[0] = -1060.286326;// -1022.282501;
	pOVSBasicInfo->staCameraParamEXT[2].daExtParam[1] = 521.873555;// 543.694419;
	pOVSBasicInfo->staCameraParamEXT[2].daExtParam[2] = 1100.486471;// 1180.937556;
	pOVSBasicInfo->staCameraParamEXT[2].daExtParam[3] = 88.796098;// 95.864254;
	pOVSBasicInfo->staCameraParamEXT[2].daExtParam[4] = 1.025409;// -5.357566;
	pOVSBasicInfo->staCameraParamEXT[2].daExtParam[5] = 43.058464;// 47.481158;

	pOVSBasicInfo->staCameraParamEXT[3].daExtParam[0] = 1033.642779;// 997.705697;
	pOVSBasicInfo->staCameraParamEXT[3].daExtParam[1] = 547.947249;// 518.657933;
	pOVSBasicInfo->staCameraParamEXT[3].daExtParam[2] = 1065.046059;// 1179.089943;
	pOVSBasicInfo->staCameraParamEXT[3].daExtParam[3] = -86.502302;// -90.981328;
	pOVSBasicInfo->staCameraParamEXT[3].daExtParam[4] = -2.394637;// 2.010307;
	pOVSBasicInfo->staCameraParamEXT[3].daExtParam[5] = 43.973220;// 48.134660;
#endif
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//pOVSBasicInfo->stBirdView.iaTVSArea[0] = 2000;      // 长安。车辆含盲区的宽度：2000mm/20 = 100 pixel
	//pOVSBasicInfo->stBirdView.iaTVSArea[1] = 5000;      // 车辆含盲区的长度：5000mm/20 = 250 pixel
	//pOVSBasicInfo->stBirdView.iaTVSArea[2] = 4120;      // 全景左/右侧图像宽度：3000mm/20 = 150 pixel
	//pOVSBasicInfo->stBirdView.iaTVSArea[3] = 700;//4000;		 // Org :1016-1000
	//pOVSBasicInfo->stBirdView.iaTVSArea[4] = 4000;//700;      // 全景前方图像距离：4700mm/20 = 235 pixel
	//pOVSBasicInfo->stBirdView.iaTVSArea[5] = 4000;//700;		 // Org: 500-1957
	//pOVSBasicInfo->stBirdView.iaTVSArea[6] = 700;//4000;      // 全景后方图像距离：4700mm/20 = 235 pixel
	//pOVSBasicInfo->stBirdView.iaTVSArea[7] = 10240;      // 8000(2000+3000+3000)mm/20 = 400(100+150+150) pixel
	//pOVSBasicInfo->stBirdView.iaTVSArea[8] = 14400;      // 14400(5000+4700+4700)mm/20 = 720(250+235+235) pixel

	//pOVSBasicInfo->stBirdView.iImgHeight = 360;
	//pOVSBasicInfo->stBirdView.iImgWidth = 256;
	//pOVSBasicInfo->stBirdView.iVehicleImgIdx = 0;
	pOVSBasicInfo->stBirdView.iaTVSArea[0] = 2000;      // 车辆含盲区的宽度：2000mm/40 = 50 pixel
	pOVSBasicInfo->stBirdView.iaTVSArea[1] = 4400;      // 车辆含盲区的长度：4400mm/40 = 110 pixel
	pOVSBasicInfo->stBirdView.iaTVSArea[2] = 6200;     // 全景左/右侧图像宽度：6200mm/40 = 155 pixel
	pOVSBasicInfo->stBirdView.iaTVSArea[3] = 1000;
	pOVSBasicInfo->stBirdView.iaTVSArea[4] = 4000;     // 全景前方图像距离：5000mm/40 = 125 pixel
	pOVSBasicInfo->stBirdView.iaTVSArea[5] = 4000;
	pOVSBasicInfo->stBirdView.iaTVSArea[6] = 1000;      // 全景后方图像距离：5000mm/40 = 125 pixel
	pOVSBasicInfo->stBirdView.iaTVSArea[7] = 14400;     // 14400(2000+6200+6200)mm/40 = 360(50+155+155) pixel
	pOVSBasicInfo->stBirdView.iaTVSArea[8] = 14400;      // 14400(4400+5000+5000)mm/40 = 360(110+125+125) pixel
	pOVSBasicInfo->stBirdView.iImgHeight = 360;
	pOVSBasicInfo->stBirdView.iImgWidth = 360;

	pOVSBasicInfo->stVehicle.fAckermanCoe = 0.07496;
	pOVSBasicInfo->stVehicle.fMaxLeftAngle = -516;
	pOVSBasicInfo->stVehicle.fMaxRightAngle = 516;
	pOVSBasicInfo->stVehicle.iaTread[0] = 1557 / LAB_SCALE;
	pOVSBasicInfo->stVehicle.iaTread[1] = 1558 / LAB_SCALE;
	pOVSBasicInfo->stVehicle.iFrontOverhang = 960 / LAB_SCALE;
	pOVSBasicInfo->stVehicle.iRearOverhang = 980 / LAB_SCALE;
	pOVSBasicInfo->stVehicle.iVehicleLength = 4640 / LAB_SCALE;
	pOVSBasicInfo->stVehicle.iVehicleWidth = 1850 / LAB_SCALE;
	pOVSBasicInfo->stVehicle.iWheelBase = 2700 / LAB_SCALE;
	pOVSBasicInfo->stVehicle.iWheelWidth = 228;

	pOVSBasicInfo->stUndistView.iRangeWidth[0] = 300;
	pOVSBasicInfo->stUndistView.iRangeHeight[0] = 264;
	pOVSBasicInfo->stUndistView.iRangeWidth[1] = 310;
	pOVSBasicInfo->stUndistView.iRangeHeight[1] = 264;
	pOVSBasicInfo->stUndistView.iImgWidth = 1080;
	pOVSBasicInfo->stUndistView.iImgHeight = 720;
	pOVSBasicInfo->stUndistView.faRangeOffsetRatio[0] = 0;
	pOVSBasicInfo->stUndistView.faRangeOffsetRatio[1] = 0;
	pOVSBasicInfo->stUndistView.faRangeOffsetRatio[2] = 0;
	pOVSBasicInfo->stUndistView.faRangeOffsetRatio[3] = 0;
	pOVSBasicInfo->stUndistView.iaViewAngle[0] = 120;
	pOVSBasicInfo->stUndistView.iaViewAngle[1] = 105;
	pOVSBasicInfo->stUndistView.iaViewAngle[2] = 120;
	pOVSBasicInfo->stUndistView.iaViewAngle[3] = 105;

	pOVSBasicInfo->stTracksAndAssist.iaDynaTrackStartDist[0] = 100;
	pOVSBasicInfo->stTracksAndAssist.iaDynaTrackStartDist[1] = 200 / LAB_SCALE;
	pOVSBasicInfo->stTracksAndAssist.iDynaTrackLen = 5000;
	pOVSBasicInfo->stTracksAndAssist.iStartToFrontWheel = pOVSBasicInfo->stVehicle.iFrontOverhang + 300;
	pOVSBasicInfo->stTracksAndAssist.iStartToRearWheel = pOVSBasicInfo->stVehicle.iRearOverhang + 300;
}

void matrixMul(double * A, double * B, double * C, int PointNum, int two, int two_B)
{
	double sub = 0.0;
	int i, j, k;
	for (i = 0; i < PointNum; i++)
	{
		for (j = 0; j < two_B; j++)
		{
			sub = 0.0;
			for (k = 0; k < two; k++)
			{
				sub += A[i*two + k] * B[k*two_B + j];
			}
			C[i*two_B + j] = sub;
		}
	}
}

#define SIMILAR_ZERO        (double)(1.0e-16)
int ContraryMatrix1(double * pMatrix, double * _pMatrix, int dim)
{
	int bState = 1;
	int i, j, k;
	//double *tMatrix;
	double base, pTemp, times;
	//CvMat *tMat = cvCreateMat(dim, dim*2, CV_64F);
	double tMatrix[18];
	for (i = 0; i < dim; i++)
	{
		for (j = 0; j < dim; j++)
		{
			tMatrix[i*dim * 2 + j] = pMatrix[i*dim + j];
		}
	}
	for (i = 0; i < dim; i++)
	{
		for (j = dim; j < dim * 2; j++)
		{
			tMatrix[i*dim * 2 + j] = 0.0;
		}
		tMatrix[i*dim * 2 + dim + i] = 1.0;
	}
	//Initialization over!
	for (i = 0; i < dim; i++)//Process Cols
	{
		int RowTemp = i;
		do
		{
			if (SIMILAR_ZERO < fabs(tMatrix[RowTemp*dim * 2 + i]))
			{
				base = tMatrix[RowTemp*dim * 2 + i];
				break;
			}
			else
			{
				RowTemp++;
			}
		} while (RowTemp < dim);
		if (SIMILAR_ZERO < fabs(base))
		{
			if (RowTemp != i)
			{
				for (k = i; k < 2 * dim; k++)
				{
					pTemp = tMatrix[RowTemp*dim * 2 + k];
					tMatrix[RowTemp*dim * 2 + k] = tMatrix[i*dim * 2 + k];
					tMatrix[i*dim * 2 + k] = pTemp;
				}
			}

			for (j = 0; j < dim; j++)//row
			{
				if (j == i)
					continue;
				times = tMatrix[j*dim * 2 + i] / base;
				for (k = i; k < dim * 2; k++)//col
				{
					tMatrix[j*dim * 2 + k] = tMatrix[j*dim * 2 + k] - times*tMatrix[i*dim * 2 + k];
				}
			}
			for (k = i; k < dim * 2; k++)
			{
				tMatrix[i*dim * 2 + k] /= base;
			}
		}
		else
		{
			bState = 0;
			break;
		}
	}
	if (bState)
	{
		for (i = 0; i < dim; i++)
		{
			for (j = 0; j < dim; j++)
			{
				_pMatrix[i*dim + j] = tMatrix[i*dim * 2 + j + dim];
			}
		}
	}

	//cvReleaseMat(&tMat);
	return bState;
}

int SetCamExtByRT(double *pdRotMtx, double *pdDist, double *dstExt)
{// this function set a ext matrix based on 3 angles and 3 displacements
	double pR[9], T[3];
	int i;

	ContraryMatrix1(pdRotMtx, pR, 3);     // pR: chessboard rotation against camera

	matrixMul(pR, pdDist, T, 3, 3, 1);   // T: chessboard displacement from camera(minus)
	for (i = 0; i < 3; i++)
	{
		dstExt[3 * i + 0] = pR[3 * i];
		dstExt[3 * i + 1] = pR[3 * i + 1];
		dstExt[3 * i + 2] = -T[i];
	}

	return 1;
}

void Cam2ImgScara(double *point2D, double *point3D, CameraParamINT * pstCameraParamINT)
{
	double *invpol = pstCameraParamINT->daInverseMapping;
	double xc = pstCameraParamINT->daIntParam[3];
	double yc = pstCameraParamINT->daIntParam[4];
	double c = pstCameraParamINT->daIntParam[0];
	double d = pstCameraParamINT->daIntParam[1];
	double e = pstCameraParamINT->daIntParam[2];
	int    width = pstCameraParamINT->iWidth;
	int    height = pstCameraParamINT->iHeight;
	int length_invpol = pstCameraParamINT->iInverseMappingCount;
	double norm = sqrt(point3D[0] * point3D[0] + point3D[1] * point3D[1]);
	double theta = atan(point3D[2] / norm);
	double t = 0, t_i = 0;
	double rho = 0, x = 0, y = 0;
	double invnorm = 0;
	int i = 0;

	if (norm != 0)
	{
		invnorm = 1 / norm;
		t = theta;
		rho = invpol[0];
		t_i = 1;

		for (i = 1; i < length_invpol; i++)
		{
			t_i *= t;
			rho += t_i*invpol[i];
		}

		x = point3D[0] * invnorm*rho;
		y = point3D[1] * invnorm*rho;

		point2D[0] = x*c + y*d + xc;
		point2D[1] = x*e + y + yc;
	}
	else
	{
		point2D[0] = xc;
		point2D[1] = yc;
	}
}

void Cam2Vehicle(double srcCam3D[3], double dstVehicle3D[3], double daExtC2V[9])
{
	matrixMul(daExtC2V, srcCam3D, dstVehicle3D, 3, 3, 1);
}

void Vehicle2Cam(double srcVehicle3D[3], double dstCam3D[3], double daExtV2C[9])
{// using design table
	matrixMul(daExtV2C, srcVehicle3D, dstCam3D, 3, 3, 1);
}

void BirdImg2Vehicle(int srcBirdImg2D[2], double dstVehicle3D[3], BirdViewParam *pBirdViewParam)
{// notice, vehicle coordinate system differs from TVS system
	dstVehicle3D[1] = -((double)srcBirdImg2D[0] * pBirdViewParam->iaTVSArea[8] / pBirdViewParam->iImgHeight - (pBirdViewParam->iaTVSArea[3] + pBirdViewParam->iaTVSArea[4] + pBirdViewParam->iaTVSArea[1] / 2));
	dstVehicle3D[0] = (double)srcBirdImg2D[1] * pBirdViewParam->iaTVSArea[7] / pBirdViewParam->iImgWidth - (pBirdViewParam->iaTVSArea[2] + pBirdViewParam->iaTVSArea[0] / 2);
}

void GenTradExt(CameraParamEXT *pCameraExt)
{// using design table
	int k, m;
	double daRotaionAngles[5];  // rad
	double daRotationMtx[5][9];
	double daRotMtxCam2Veh[9];
	double daMtxTmp[9];
	//double daTradExt[9];    // cam 2 vehicle

	daRotaionAngles[0] = -(double)(3.1415926535897932384626433832795) / 2.0f;                             // around Z axis
	daRotaionAngles[1] = (double)(3.1415926535897932384626433832795) / 2.0f;                              // Y axis
	daRotaionAngles[2] = -pCameraExt->daExtParam[3] * PI / 180;  // pan, X axis
	daRotaionAngles[3] = -pCameraExt->daExtParam[5] * PI / 180;  // tilt, Y axis
	daRotaionAngles[4] = pCameraExt->daExtParam[4] * PI / 180;  // rot, Z axis

	for (k = 0; k < 5; k++)
	{
		if (k == 2) // X axis
		{
			daRotationMtx[k][0] = 1;
			daRotationMtx[k][1] = 0;
			daRotationMtx[k][2] = 0;
			daRotationMtx[k][3] = 0;
			daRotationMtx[k][4] = cos(daRotaionAngles[k]);
			daRotationMtx[k][5] = -sin(daRotaionAngles[k]);
			daRotationMtx[k][6] = 0;
			daRotationMtx[k][7] = sin(daRotaionAngles[k]);
			daRotationMtx[k][8] = cos(daRotaionAngles[k]);
		}
		if (k == 0 || k == 4)   // Z axis
		{
			daRotationMtx[k][0] = cos(daRotaionAngles[k]);
			daRotationMtx[k][1] = -sin(daRotaionAngles[k]);
			daRotationMtx[k][2] = 0;
			daRotationMtx[k][3] = sin(daRotaionAngles[k]);
			daRotationMtx[k][4] = cos(daRotaionAngles[k]);
			daRotationMtx[k][5] = 0;
			daRotationMtx[k][6] = 0;
			daRotationMtx[k][7] = 0;
			daRotationMtx[k][8] = 1;
		}
		if (k == 1 || k == 3)   // Y axis
		{
			daRotationMtx[k][0] = cos(daRotaionAngles[k]);
			daRotationMtx[k][1] = 0;
			daRotationMtx[k][2] = sin(daRotaionAngles[k]);
			daRotationMtx[k][3] = 0;
			daRotationMtx[k][4] = 1;
			daRotationMtx[k][5] = 0;
			daRotationMtx[k][6] = -sin(daRotaionAngles[k]);
			daRotationMtx[k][7] = 0;
			daRotationMtx[k][8] = cos(daRotaionAngles[k]);
		}

	}

	if (0)
	{
		for (m = 0; m < 9; m++)
		{
			daMtxTmp[m] = daRotationMtx[0][m];
		}
		for (k = 0; k < 4; k++)
		{
			matrixMul(daMtxTmp, daRotationMtx[k + 1], daRotMtxCam2Veh, 3, 3, 3);
			for (m = 0; m < 9; m++)
			{
				daMtxTmp[m] = daRotMtxCam2Veh[m];
			}
		}
	}
	else
	{
		for (m = 0; m < 9; m++)
		{
			daMtxTmp[m] = daRotationMtx[4][m];
		}
		for (k = 3; k >= 0; k--)
		{
			matrixMul(daRotationMtx[k], daMtxTmp, daRotMtxCam2Veh, 3, 3, 3);
			for (m = 0; m < 9; m++)
			{
				daMtxTmp[m] = daRotMtxCam2Veh[m];
			}
		}
	}

	SetCamExtByRT(daRotMtxCam2Veh, pCameraExt->daExtParam, pCameraExt->daExtMtxV2C);
	ContraryMatrix1(pCameraExt->daExtMtxV2C, pCameraExt->daExtMtxC2V, 3);
}


static void ppp(double a[], double e[], double s[], double v[], int m, int n)
{
	int i, j, p, q;
	double d;
	if (m >= n)
		i = n;
	else
		i = m;
	for (j = 1; j <= i - 1; j++)
	{
		a[(j - 1)*n + j - 1] = s[j - 1];
		a[(j - 1)*n + j] = e[j - 1];
	}
	a[(i - 1)*n + i - 1] = s[i - 1];
	if (m<n)
		a[(i - 1)*n + i] = e[i - 1];
	for (i = 1; i <= n - 1; i++)
	for (j = i + 1; j <= n; j++)
	{
		p = (i - 1)*n + j - 1;
		q = (j - 1)*n + i - 1;
		d = v[p]; v[p] = v[q]; v[q] = d;
	}
	return;
}
static void sss(double fg[2], double cs[2])
{
	double r, d;
	//if((fabs(fg[0])+fabs(fg[1]))==0.0)
	if ((fabs(fg[0]) + fabs(fg[1]))<MIN_DOUBLE)
	{
		cs[0] = 1.0; cs[1] = 0.0; d = 0.0;
	}
	else
	{
		d = sqrt(fg[0] * fg[0] + fg[1] * fg[1]);
		if (fabs(fg[0])>fabs(fg[1]))
		{
			d = fabs(d);
			if (fg[0]<0.0)
				d = -d;
		}
		if (fabs(fg[1]) >= fabs(fg[0]))
		{
			d = fabs(d);
			if (fg[1]<0.0)
				d = -d;
		}
		cs[0] = fg[0] / d;
		cs[1] = fg[1] / d;
	}
	r = 1.0;
	if (fabs(fg[0])>fabs(fg[1]))
		r = cs[1];
	else
		//if(cs[0]!=0.0)
	if (fabs(cs[0])>MIN_DOUBLE)
		r = 1.0 / cs[0];
	fg[0] = d;
	fg[1] = r;
	return;
}

int SplitUV(double *m_pData, double* mtxU, double* mtxV, int row, int col)
{
	int i, j, k, l, it, ll, kk, ix, iy, mm, nn, iz, m1, ks;
	double d, dd, t, sm, sm1, em1, sk, ek, b, c, shh, fg[2], cs[2];
	double *s, *e, *w;
	double eps = 0.000001;
	double pp;

	int m = row;
	int n = col;
	int ka = (m>n ? m : n) + 1;
	s = (double*)calloc(ka, sizeof(double));
	e = (double*)calloc(ka, sizeof(double));
	w = (double*)calloc(ka, sizeof(double));
	k = n;
	if (m - 1<n)
		k = m - 1;//U进行K次迭代，V进行l次迭代
	l = m;
	if (n - 2<m)
		l = n - 2;
	if (l<0)
		l = 0;
	// 循环迭代计算
	ll = k;
	if (l>k)
		ll = l;
	if (ll >= 1)
	{
		for (kk = 1; kk <= ll; kk++)
		{
			if (kk <= k)
			{
				d = 0.0;
				for (i = kk; i <= m; i++)
				{
					ix = (i - 1)*n + kk - 1;
					d = d + m_pData[ix] * m_pData[ix];
				}

				s[kk - 1] = sqrt(d);
				if (s[kk - 1] != 0.0)
				{
					ix = (kk - 1)*n + kk - 1;
					if (m_pData[ix] != 0.0)
					{
						s[kk - 1] = fabs(s[kk - 1]);
						if (m_pData[ix]<0.0)
							s[kk - 1] = -s[kk - 1];
					}

					for (i = kk; i <= m; i++)
					{
						iy = (i - 1)*n + kk - 1;
						m_pData[iy] = m_pData[iy] / s[kk - 1];
					}

					m_pData[ix] = 1.0 + m_pData[ix];
				}

				s[kk - 1] = -s[kk - 1];
			}

			if (n >= kk + 1)
			{
				for (j = kk + 1; j <= n; j++)
				{
					if ((kk <= k) && (s[kk - 1] != 0.0))
					{
						d = 0.0;
						for (i = kk; i <= m; i++)
						{
							ix = (i - 1)*n + kk - 1;
							iy = (i - 1)*n + j - 1;
							d = d + m_pData[ix] * m_pData[iy];
						}

						d = -d / m_pData[(kk - 1)*n + kk - 1];
						for (i = kk; i <= m; i++)
						{
							ix = (i - 1)*n + j - 1;
							iy = (i - 1)*n + kk - 1;
							m_pData[ix] = m_pData[ix] + d*m_pData[iy];
						}
					}

					e[j - 1] = m_pData[(kk - 1)*n + j - 1];
				}
			}
			if (kk <= k)
			{
				for (i = kk; i <= m; i++)
				{
					ix = (i - 1)*m + kk - 1;
					iy = (i - 1)*n + kk - 1;
					pp = m_pData[iy];
					pp = mtxU[ix];
					mtxU[ix] = m_pData[iy];
				}
			}

			if (kk <= l)
			{
				d = 0.0;
				for (i = kk + 1; i <= n; i++)
					d = d + e[i - 1] * e[i - 1];

				e[kk - 1] = sqrt(d);
				if (e[kk - 1] != 0.0)
				{
					if (e[kk] != 0.0)
					{
						e[kk - 1] = fabs(e[kk - 1]);
						if (e[kk]<0.0)
							e[kk - 1] = -e[kk - 1];
					}

					for (i = kk + 1; i <= n; i++)
						e[i - 1] = e[i - 1] / e[kk - 1];

					e[kk] = 1.0 + e[kk];
				}

				e[kk - 1] = -e[kk - 1];
				if ((kk + 1 <= m) && (e[kk - 1] != 0.0))
				{
					for (i = kk + 1; i <= m; i++)
						w[i - 1] = 0.0;

					for (j = kk + 1; j <= n; j++)
					for (i = kk + 1; i <= m; i++)
						w[i - 1] = w[i - 1] + e[j - 1] * m_pData[(i - 1)*n + j - 1];

					for (j = kk + 1; j <= n; j++)
					{
						for (i = kk + 1; i <= m; i++)
						{
							ix = (i - 1)*n + j - 1;
							m_pData[ix] = m_pData[ix] - w[i - 1] * e[j - 1] / e[kk];
						}
					}
				}

				for (i = kk + 1; i <= n; i++)
					mtxV[(i - 1)*n + kk - 1] = e[i - 1];
			}

		}
	}

	mm = n;
	if (m + 1<n)
		mm = m + 1;
	if (k<n)
		s[k] = m_pData[k*n + k];
	if (m<mm)
		s[mm - 1] = 0.0;
	if (l + 1<mm)
		e[l] = m_pData[l*n + mm - 1];

	e[mm - 1] = 0.0;
	nn = m;
	if (m>n)
		nn = n;
	if (nn >= k + 1)
	{
		for (j = k + 1; j <= nn; j++)
		{
			for (i = 1; i <= m; i++)
				mtxU[(i - 1)*m + j - 1] = 0.0;
			mtxU[(j - 1)*m + j - 1] = 1.0;
		}
	}

	if (k >= 1)
	{
		for (ll = 1; ll <= k; ll++)
		{
			kk = k - ll + 1;
			iz = (kk - 1)*m + kk - 1;
			if (s[kk - 1] != 0.0)
			{
				if (nn >= kk + 1)
				{
					for (j = kk + 1; j <= nn; j++)
					{
						d = 0.0;
						for (i = kk; i <= m; i++)
						{
							ix = (i - 1)*m + kk - 1;
							iy = (i - 1)*m + j - 1;
							d = d + mtxU[ix] * mtxU[iy] / mtxU[iz];
						}

						d = -d;
						for (i = kk; i <= m; i++)
						{
							ix = (i - 1)*m + j - 1;
							iy = (i - 1)*m + kk - 1;
							mtxU[ix] = mtxU[ix] + d*mtxU[iy];
						}
					}
				}

				for (i = kk; i <= m; i++)
				{
					ix = (i - 1)*m + kk - 1;
					mtxU[ix] = -mtxU[ix];
				}

				mtxU[iz] = 1.0 + mtxU[iz];
				if (kk - 1 >= 1)
				{
					for (i = 1; i <= kk - 1; i++)
						mtxU[(i - 1)*m + kk - 1] = 0.0;
				}
			}
			else
			{
				for (i = 1; i <= m; i++)
					mtxU[(i - 1)*m + kk - 1] = 0.0;
				mtxU[(kk - 1)*m + kk - 1] = 1.0;
			}
		}
	}

	for (ll = 1; ll <= n; ll++)
	{
		kk = n - ll + 1;
		iz = kk*n + kk - 1;

		if ((kk <= l) && (e[kk - 1] != 0.0))
		{
			for (j = kk + 1; j <= n; j++)
			{
				d = 0.0;
				for (i = kk + 1; i <= n; i++)
				{
					ix = (i - 1)*n + kk - 1;
					iy = (i - 1)*n + j - 1;
					d = d + mtxV[ix] * mtxV[iy] / mtxV[iz];
				}

				d = -d;
				for (i = kk + 1; i <= n; i++)
				{
					ix = (i - 1)*n + j - 1;
					iy = (i - 1)*n + kk - 1;
					mtxV[ix] = mtxV[ix] + d*mtxV[iy];
				}
			}
		}

		for (i = 1; i <= n; i++)
			mtxV[(i - 1)*n + kk - 1] = 0.0;

		mtxV[iz - n] = 1.0;
	}

	for (i = 1; i <= m; i++)
	for (j = 1; j <= n; j++)
		m_pData[(i - 1)*n + j - 1] = 0.0;

	m1 = mm;
	it = 60;
	while (1)
	{
		if (mm == 0)
		{
			ppp(m_pData, e, s, mtxV, m, n);
			free(s);
			free(e);
			free(w);
			return 1;
		}
		if (it == 0)
		{
			ppp(m_pData, e, s, mtxV, m, n);
			free(s);
			free(e);
			free(w);
			return 0;
		}

		kk = mm - 1;
		while ((kk != 0) && (fabs(e[kk - 1]) != 0.0))
		{
			d = fabs(s[kk - 1]) + fabs(s[kk]);
			dd = fabs(e[kk - 1]);
			if (dd>eps*d)
				kk = kk - 1;
			else
				e[kk - 1] = 0.0;
		}

		if (kk == mm - 1)
		{
			kk = kk + 1;
			if (s[kk - 1]<0.0)
			{
				s[kk - 1] = -s[kk - 1];
				for (i = 1; i <= n; i++)
				{
					ix = (i - 1)*n + kk - 1;
					mtxV[ix] = -mtxV[ix];
				}
			}

			while ((kk != m1) && (s[kk - 1]<s[kk]))
			{
				d = s[kk - 1];
				s[kk - 1] = s[kk];
				s[kk] = d;
				if (kk<n)
				{
					for (i = 1; i <= n; i++)
					{
						ix = (i - 1)*n + kk - 1;
						iy = (i - 1)*n + kk;
						d = mtxV[ix];
						mtxV[ix] = mtxV[iy];
						mtxV[iy] = d;
					}
				}

				if (kk<m)
				{
					for (i = 1; i <= m; i++)
					{
						ix = (i - 1)*m + kk - 1;
						iy = (i - 1)*m + kk;
						d = mtxU[ix];
						mtxU[ix] = mtxU[iy];
						mtxU[iy] = d;
					}
				}

				kk = kk + 1;
			}

			it = 60;
			mm = mm - 1;
		}
		else
		{
			ks = mm;
			while ((ks>kk) && (fabs(s[ks - 1]) != 0.0))
			{
				d = 0.0;
				if (ks != mm)
					d = d + fabs(e[ks - 1]);
				if (ks != kk + 1)
					d = d + fabs(e[ks - 2]);

				dd = fabs(s[ks - 1]);
				if (dd>eps*d)
					ks = ks - 1;
				else
					s[ks - 1] = 0.0;
			}

			if (ks == kk)
			{
				kk = kk + 1;
				d = fabs(s[mm - 1]);
				t = fabs(s[mm - 2]);
				if (t>d)
					d = t;

				t = fabs(e[mm - 2]);
				if (t>d)
					d = t;

				t = fabs(s[kk - 1]);
				if (t>d)
					d = t;

				t = fabs(e[kk - 1]);
				if (t>d)
					d = t;

				sm = s[mm - 1] / d;
				sm1 = s[mm - 2] / d;
				em1 = e[mm - 2] / d;
				sk = s[kk - 1] / d;
				ek = e[kk - 1] / d;
				b = ((sm1 + sm)*(sm1 - sm) + em1*em1) / 2.0;
				c = sm*em1;
				c = c*c;
				shh = 0.0;

				if ((b != 0.0) || (c != 0.0))
				{
					shh = sqrt(b*b + c);
					if (b<0.0)
						shh = -shh;

					shh = c / (b + shh);
				}

				fg[0] = (sk + sm)*(sk - sm) - shh;
				fg[1] = sk*ek;
				for (i = kk; i <= mm - 1; i++)
				{
					sss(fg, cs);
					if (i != kk)
						e[i - 2] = fg[0];

					fg[0] = cs[0] * s[i - 1] + cs[1] * e[i - 1];
					e[i - 1] = cs[0] * e[i - 1] - cs[1] * s[i - 1];
					fg[1] = cs[1] * s[i];
					s[i] = cs[0] * s[i];

					if ((cs[0] != 1.0) || (cs[1] != 0.0))
					{
						for (j = 1; j <= n; j++)
						{
							ix = (j - 1)*n + i - 1;
							iy = (j - 1)*n + i;
							d = cs[0] * mtxV[ix] + cs[1] * mtxV[iy];
							mtxV[iy] = -cs[1] * mtxV[ix] + cs[0] * mtxV[iy];
							mtxV[ix] = d;
						}
					}

					sss(fg, cs);
					s[i - 1] = fg[0];
					fg[0] = cs[0] * e[i - 1] + cs[1] * s[i];
					s[i] = -cs[1] * e[i - 1] + cs[0] * s[i];
					fg[1] = cs[1] * e[i];
					e[i] = cs[0] * e[i];

					if (i<m)
					{
						if ((cs[0] != 1.0) || (cs[1] != 0.0))
						{
							for (j = 1; j <= m; j++)
							{
								ix = (j - 1)*m + i - 1;
								iy = (j - 1)*m + i;
								d = cs[0] * mtxU[ix] + cs[1] * mtxU[iy];
								mtxU[iy] = -cs[1] * mtxU[ix] + cs[0] * mtxU[iy];
								mtxU[ix] = d;
							}
						}
					}
				}

				e[mm - 2] = fg[0];
				it = it - 1;
			}
			else
			{
				if (ks == mm)
				{
					kk = kk + 1;
					fg[1] = e[mm - 2];
					e[mm - 2] = 0.0;
					for (ll = kk; ll <= mm - 1; ll++)
					{
						i = mm + kk - ll - 1;
						fg[0] = s[i - 1];
						sss(fg, cs);
						s[i - 1] = fg[0];
						if (i != kk)
						{
							fg[1] = -cs[1] * e[i - 2];
							e[i - 2] = cs[0] * e[i - 2];
						}

						if ((cs[0] != 1.0) || (cs[1] != 0.0))
						{
							for (j = 1; j <= n; j++)
							{
								ix = (j - 1)*n + i - 1;
								iy = (j - 1)*n + mm - 1;
								d = cs[0] * mtxV[ix] + cs[1] * mtxV[iy];
								mtxV[iy] = -cs[1] * mtxV[ix] + cs[0] * mtxV[iy];
								mtxV[ix] = d;
							}
						}
					}
				}
				else
				{
					kk = ks + 1;
					fg[1] = e[kk - 2];
					e[kk - 2] = 0.0;
					for (i = kk; i <= mm; i++)
					{
						fg[0] = s[i - 1];
						sss(fg, cs);
						s[i - 1] = fg[0];
						fg[1] = -cs[1] * e[i - 1];
						e[i - 1] = cs[0] * e[i - 1];
						if ((cs[0] != 1.0) || (cs[1] != 0.0))
						{
							for (j = 1; j <= m; j++)
							{
								ix = (j - 1)*m + i - 1;
								iy = (j - 1)*m + kk - 2;
								d = cs[0] * mtxU[ix] + cs[1] * mtxU[iy];
								mtxU[iy] = -cs[1] * mtxU[ix] + cs[0] * mtxU[iy];
								mtxU[ix] = d;
							}
						}
					}
				}
			}
		}
	}
	free(s);
	free(e);
	free(w);
	return 1;
}


