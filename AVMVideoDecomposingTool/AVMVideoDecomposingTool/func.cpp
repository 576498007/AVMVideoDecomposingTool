#include "stdafx.h"
#include "func.h"
#include "OVS_Cali_Types.h"
#include "Mtx_and_Coord_Operation.h"
#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>
#include <math.h>
#include <stdio.h>


#define SIMILAR_ZERO        (double)(1.0e-16)
#define WHITE_BALANCE_AREA_OFFSET_X		5
#define WHITE_BALANCE_AREA_OFFSET_Y		5
#define WHITE_BALANCE_AREA_WIDTH		25
#define WHITE_BALANCE_AREA_HEIGHT		35
#define  SMLS_FACTOR_E          		0.0000001
#define WHITE_BALANCE_AREA    8
#define  WB_FACTOR_NUM      12

int init_malloc(OVSBasicInfo * pOVSBasicInfo, AvmTableLead *p_stAvmTableLead, AvmTableSupport *p_stAvmTableSupport)
{
	int k;
	int SupportW, SupportH;
	float fRatioU, fRatioV;

	p_stAvmTableLead->iValidFlag = 1;
	p_stAvmTableLead->iWidth = pOVSBasicInfo->stBirdView.iImgWidth;
	p_stAvmTableLead->iHeight = pOVSBasicInfo->stBirdView.iImgHeight;
	p_stAvmTableLead->iTablePointNum = pOVSBasicInfo->stBirdView.iImgWidth * pOVSBasicInfo->stBirdView.iImgHeight;
	p_stAvmTableLead->puiSrcAddress = (unsigned int *)malloc(p_stAvmTableLead->iTablePointNum * sizeof(int));
	if (p_stAvmTableLead->puiSrcAddress == NULL)
		return -1;
	p_stAvmTableLead->puiInterCoe = (unsigned int *)malloc(p_stAvmTableLead->iTablePointNum * sizeof(int));
	if (p_stAvmTableLead->puiInterCoe == NULL)
		return -1;

	// support
	p_stAvmTableSupport->iValidFlag = 1;
	p_stAvmTableSupport->iAreaPointNum = 0;
	for (k = 0; k < 8; k++)
	{
		p_stAvmTableSupport->iaAreaPointNumEach[k] = 0;
	}

	fRatioU = (float)pOVSBasicInfo->stBirdView.iaTVSArea[8] / pOVSBasicInfo->stBirdView.iImgHeight;
	fRatioV = (float)pOVSBasicInfo->stBirdView.iaTVSArea[7] / pOVSBasicInfo->stBirdView.iImgWidth;

	SupportW = (int)((pOVSBasicInfo->stBirdView.iaTVSArea[7] - pOVSBasicInfo->stBirdView.iaTVSArea[0]) / fRatioV + 4);  // add 4 for margin
	SupportH = (int)((pOVSBasicInfo->stBirdView.iaTVSArea[8] - pOVSBasicInfo->stBirdView.iaTVSArea[1]) / fRatioU + 4);
	p_stAvmTableSupport->iTablePointNum = SupportW * SupportH;
	p_stAvmTableSupport->puiDstAddress = (unsigned int *)malloc(p_stAvmTableSupport->iTablePointNum * sizeof(int));
	p_stAvmTableSupport->puiSrcAddress = (unsigned int *)malloc(2 * p_stAvmTableSupport->iTablePointNum * sizeof(int));
	p_stAvmTableSupport->puiInterCoe = (unsigned int *)malloc(2 * p_stAvmTableSupport->iTablePointNum * sizeof(int));

	return 0;
}

void LDWBirdview_CalcVerAndTex(OVSBasicInfo * pOVSBasicInfo, AvmTableLead *p_stAvmTableLead, AvmTableSupport *p_stAvmTableSupport)
{
	int k, imgCoord[2], count;
	char   i_view_1 = 0, i_view_2 = 0;
	char   i_wb_idx1 = -1, i_wb_idx2 = -1;
	float u0_1 = 0, v0_1 = 0;//distorted image 1
	float u0_2 = 0, v0_2 = 0;//distorted image 2
	float factorTmp1, factorTmp2, factor_1 = 1, factor_2 = 1;//position factor
	double pWorld1[3] = { 0, 0, 1 }, pWorld2[3] = { 0, 0, 1 };
	double pImgInput[2], pCam[3];
	float slope[4][2];
	float lineParam_b[4][2];
	unsigned int uiAddress1, uiCoe1, uiAddress2, uiCoe2, uiDstAddress;
	unsigned int uiAddressLead, uiAddressSupport, uiCoeLead, uiCoeSupport;
	unsigned int uiUCoord, uiVCoord, uiFactor1, uiFactor2, uu, vv;
	unsigned int PixWeight[4];
	unsigned int *pAddressLead = p_stAvmTableLead->puiSrcAddress;
	unsigned int *pCoeLead = p_stAvmTableLead->puiInterCoe;
	unsigned int *pAddressSupport = p_stAvmTableSupport->puiSrcAddress;
	unsigned int *pCoeSupport = p_stAvmTableSupport->puiInterCoe;
	unsigned int *pDstAddress = p_stAvmTableSupport->puiDstAddress;
	AvmAndCarSizeInfo * pstAvmAndCarSizeInfo;

	pstAvmAndCarSizeInfo = (AvmAndCarSizeInfo *)malloc(sizeof(AvmAndCarSizeInfo));

	pstAvmAndCarSizeInfo->iAvmImageWidth = pOVSBasicInfo->stBirdView.iImgWidth;
	pstAvmAndCarSizeInfo->iAvmImageHeight = pOVSBasicInfo->stBirdView.iImgHeight;
	pstAvmAndCarSizeInfo->fRatioU = (float)pOVSBasicInfo->stBirdView.iaTVSArea[8] / pOVSBasicInfo->stBirdView.iImgHeight;
	pstAvmAndCarSizeInfo->fRatioV = (float)pOVSBasicInfo->stBirdView.iaTVSArea[7] / pOVSBasicInfo->stBirdView.iImgWidth;
	pstAvmAndCarSizeInfo->iLeftOffset = (int)(pOVSBasicInfo->stBirdView.iaTVSArea[2] / pstAvmAndCarSizeInfo->fRatioV + 0.5);
	pstAvmAndCarSizeInfo->iTopOffset = (int)((pOVSBasicInfo->stBirdView.iaTVSArea[3] + pOVSBasicInfo->stBirdView.iaTVSArea[4]) / pstAvmAndCarSizeInfo->fRatioU + 0.5);
	pstAvmAndCarSizeInfo->iCarImageWidth = (int)(pOVSBasicInfo->stBirdView.iaTVSArea[0] / pstAvmAndCarSizeInfo->fRatioV + 0.5);
	pstAvmAndCarSizeInfo->iCarImageHeight = (int)(pOVSBasicInfo->stBirdView.iaTVSArea[1] / pstAvmAndCarSizeInfo->fRatioU + 0.5);

	pstAvmAndCarSizeInfo->fSlopeFL = (float)(pOVSBasicInfo->stBirdView.iaTVSArea[4] / pstAvmAndCarSizeInfo->fRatioU) / pstAvmAndCarSizeInfo->iLeftOffset;
	pstAvmAndCarSizeInfo->fSlopeFR = pstAvmAndCarSizeInfo->fSlopeFL;
	pstAvmAndCarSizeInfo->fSlopeLB = (float)(pOVSBasicInfo->stBirdView.iaTVSArea[5] / pstAvmAndCarSizeInfo->fRatioU) / pstAvmAndCarSizeInfo->iLeftOffset;
	pstAvmAndCarSizeInfo->fSlopeRB = pstAvmAndCarSizeInfo->fSlopeLB;

	slope[0][0] = (float)tan(atan(pstAvmAndCarSizeInfo->fSlopeFL) + SMLS_OFFSET);
	slope[0][1] = (float)tan(atan(pstAvmAndCarSizeInfo->fSlopeFL) - SMLS_OFFSET);
	slope[1][0] = (float)tan(atan(-pstAvmAndCarSizeInfo->fSlopeFR) - SMLS_OFFSET);
	slope[1][1] = (float)tan(atan(-pstAvmAndCarSizeInfo->fSlopeFR) + SMLS_OFFSET);
	slope[2][0] = (float)tan(atan(-pstAvmAndCarSizeInfo->fSlopeLB) + SMLS_OFFSET);
	slope[2][1] = (float)tan(atan(-pstAvmAndCarSizeInfo->fSlopeLB) - SMLS_OFFSET);
	slope[3][0] = (float)tan(atan(pstAvmAndCarSizeInfo->fSlopeRB) - SMLS_OFFSET);
	slope[3][1] = (float)tan(atan(pstAvmAndCarSizeInfo->fSlopeRB) + SMLS_OFFSET);

	if (1 == GEN_BIRDVIE_WITH_WHOLE_OVERLAP_AREA)
	{
		slope[0][0] = 200.0;
		slope[0][1] = 0.0;
		slope[1][0] = -200.0;
		slope[1][1] = -0.0;
		slope[2][0] = -0.0;
		slope[2][1] = -200.0;
		slope[3][0] = 0.0;
		slope[3][1] = 200.0;
	}

	lineParam_b[0][0] = pstAvmAndCarSizeInfo->iTopOffset - slope[0][0] * pstAvmAndCarSizeInfo->iLeftOffset;
	lineParam_b[0][1] = pstAvmAndCarSizeInfo->iTopOffset - slope[0][1] * pstAvmAndCarSizeInfo->iLeftOffset;
	lineParam_b[1][0] = pstAvmAndCarSizeInfo->iTopOffset - slope[1][0] * (pstAvmAndCarSizeInfo->iLeftOffset + pstAvmAndCarSizeInfo->iCarImageWidth);
	lineParam_b[1][1] = pstAvmAndCarSizeInfo->iTopOffset - slope[1][1] * (pstAvmAndCarSizeInfo->iLeftOffset + pstAvmAndCarSizeInfo->iCarImageWidth);
	lineParam_b[2][0] = pstAvmAndCarSizeInfo->iTopOffset + pstAvmAndCarSizeInfo->iCarImageHeight - slope[2][0] * pstAvmAndCarSizeInfo->iLeftOffset;
	lineParam_b[2][1] = pstAvmAndCarSizeInfo->iTopOffset + pstAvmAndCarSizeInfo->iCarImageHeight - slope[2][1] * pstAvmAndCarSizeInfo->iLeftOffset;
	lineParam_b[3][0] = pstAvmAndCarSizeInfo->iTopOffset + pstAvmAndCarSizeInfo->iCarImageHeight - slope[3][0] * (pstAvmAndCarSizeInfo->iLeftOffset + pstAvmAndCarSizeInfo->iCarImageWidth);
	lineParam_b[3][1] = pstAvmAndCarSizeInfo->iTopOffset + pstAvmAndCarSizeInfo->iCarImageHeight - slope[3][1] * (pstAvmAndCarSizeInfo->iLeftOffset + pstAvmAndCarSizeInfo->iCarImageWidth);

	for (k = 0; k<4; k++)
	{
		GenTradExt(&pOVSBasicInfo->staCameraParamEXT[k]);
	}

	count = 0;
	for (imgCoord[0] = 0; imgCoord[0] < pstAvmAndCarSizeInfo->iAvmImageHeight; imgCoord[0]++)
	{
		for (imgCoord[1] = 0; imgCoord[1] < pstAvmAndCarSizeInfo->iAvmImageWidth; imgCoord[1]++)
		{
			if (imgCoord[0] > slope[0][0] * imgCoord[1] + lineParam_b[0][0] + SMLS_GAP &&
				imgCoord[0] <= slope[0][1] * imgCoord[1] + lineParam_b[0][1] - SMLS_GAP)
			{//left front---------------------
				i_view_1 = 1;
				i_view_2 = 3;

				if (imgCoord[1] > pstAvmAndCarSizeInfo->iLeftOffset - WHITE_BALANCE_AREA_OFFSET_X - WHITE_BALANCE_AREA_WIDTH &&
					imgCoord[1] < pstAvmAndCarSizeInfo->iLeftOffset - WHITE_BALANCE_AREA_OFFSET_X &&
					imgCoord[0] > pstAvmAndCarSizeInfo->iTopOffset - WHITE_BALANCE_AREA_OFFSET_Y - WHITE_BALANCE_AREA_HEIGHT &&
					imgCoord[0] < pstAvmAndCarSizeInfo->iTopOffset - WHITE_BALANCE_AREA_OFFSET_Y)
				{
					i_wb_idx1 = 0;
					i_wb_idx2 = 1;
				}
				else
				{
					i_wb_idx1 = -1;
					i_wb_idx2 = -1;
				}

				factorTmp1 = LEFT_CAMERA_WEIGHT_BIRDVIEW * abs(slope[0][0] * imgCoord[1] - imgCoord[0] + lineParam_b[0][0]) / sqrt(slope[0][0] * slope[0][0] + 1);
				factorTmp2 = FRONT_CAMERA_WEIGHT_BIRDVIEW * abs(slope[0][1] * imgCoord[1] - imgCoord[0] + lineParam_b[0][1]) / sqrt(slope[0][1] * slope[0][1] + 1);
				factor_1 = factorTmp2 / (factorTmp1 + factorTmp2);
				factor_2 = factorTmp1 / (factorTmp1 + factorTmp2);
				BirdImg2Vehicle(imgCoord, pWorld1, &pOVSBasicInfo->stBirdView);
				BirdImg2Vehicle(imgCoord, pWorld2, &pOVSBasicInfo->stBirdView);

			}
			else if (imgCoord[0] <= pstAvmAndCarSizeInfo->iTopOffset &&
				imgCoord[0] <= slope[0][0] * imgCoord[1] + lineParam_b[0][0] &&
				imgCoord[0] <= slope[1][0] * imgCoord[1] + lineParam_b[1][0])
			{//front--------------------------
				i_view_1 = 1;
				i_view_2 = 0;
				i_wb_idx1 = -1;
				i_wb_idx2 = -1;
				factor_1 = 1;
				factor_2 = 0;
				BirdImg2Vehicle(imgCoord, pWorld1, &pOVSBasicInfo->stBirdView);
				u0_2 = 1;
				v0_2 = 1;

			}
			else if (imgCoord[0] > slope[1][0] * imgCoord[1] + lineParam_b[1][0] + SMLS_GAP&&
				imgCoord[0] <= slope[1][1] * imgCoord[1] + lineParam_b[1][1] - SMLS_GAP)
			{//right front--------------------
				i_view_1 = 1;
				i_view_2 = 4;

				if (imgCoord[1] > pstAvmAndCarSizeInfo->iLeftOffset + pstAvmAndCarSizeInfo->iCarImageWidth + WHITE_BALANCE_AREA_OFFSET_X &&
					imgCoord[1] < pstAvmAndCarSizeInfo->iLeftOffset + pstAvmAndCarSizeInfo->iCarImageWidth + WHITE_BALANCE_AREA_OFFSET_X + WHITE_BALANCE_AREA_WIDTH &&
					imgCoord[0] > pstAvmAndCarSizeInfo->iTopOffset - WHITE_BALANCE_AREA_OFFSET_Y - WHITE_BALANCE_AREA_HEIGHT &&
					imgCoord[0] < pstAvmAndCarSizeInfo->iTopOffset - WHITE_BALANCE_AREA_OFFSET_Y)
				{
					i_wb_idx1 = 2;
					i_wb_idx2 = 3;
				}
				else
				{
					i_wb_idx1 = -1;
					i_wb_idx2 = -1;
				}

				factorTmp1 = RIGHT_CAMERA_WEIGHT_BIRDVIEW * abs(slope[1][0] * imgCoord[1] - imgCoord[0] + lineParam_b[1][0]) / sqrt(slope[1][0] * slope[1][0] + 1);
				factorTmp2 = FRONT_CAMERA_WEIGHT_BIRDVIEW * abs(slope[1][1] * imgCoord[1] - imgCoord[0] + lineParam_b[1][1]) / sqrt(slope[1][1] * slope[1][1] + 1);
				factor_1 = factorTmp2 / (factorTmp1 + factorTmp2);
				factor_2 = factorTmp1 / (factorTmp1 + factorTmp2);
				BirdImg2Vehicle(imgCoord, pWorld1, &pOVSBasicInfo->stBirdView);
				BirdImg2Vehicle(imgCoord, pWorld2, &pOVSBasicInfo->stBirdView);

			}
			else if (imgCoord[0] > slope[0][1] * imgCoord[1] + lineParam_b[0][1] &&
				imgCoord[0] <= slope[2][0] * imgCoord[1] + lineParam_b[2][0] &&
				imgCoord[1] < pstAvmAndCarSizeInfo->iLeftOffset)
			{//left---------------------------
				i_view_1 = 3;
				i_view_2 = 0;
				i_wb_idx1 = -1;
				i_wb_idx2 = -1;
				factor_1 = 1;
				factor_2 = 0;
				BirdImg2Vehicle(imgCoord, pWorld1, &pOVSBasicInfo->stBirdView);
				u0_2 = 1;
				v0_2 = 1;

			}
			else if (imgCoord[0] > slope[1][1] * imgCoord[1] + lineParam_b[1][1] &&
				imgCoord[0] <= slope[3][0] * imgCoord[1] + lineParam_b[3][0] &&
				imgCoord[1] >= pstAvmAndCarSizeInfo->iLeftOffset + pstAvmAndCarSizeInfo->iCarImageWidth)
			{//right--------------------------
				i_view_1 = 4;
				i_view_2 = 0;
				i_wb_idx1 = -1;
				i_wb_idx2 = -1;
				factor_1 = 1;
				factor_2 = 0;
				BirdImg2Vehicle(imgCoord, pWorld1, &pOVSBasicInfo->stBirdView);
				u0_2 = 1;
				v0_2 = 1;

			}
			else if (imgCoord[0] > slope[2][0] * imgCoord[1] + lineParam_b[2][0] + SMLS_GAP&&
				imgCoord[0] <= slope[2][1] * imgCoord[1] + lineParam_b[2][1] - SMLS_GAP)
			{//left back----------------------
				i_view_1 = 3;
				i_view_2 = 2;

				if (imgCoord[1] > pstAvmAndCarSizeInfo->iLeftOffset - WHITE_BALANCE_AREA_OFFSET_X - WHITE_BALANCE_AREA_WIDTH &&
					imgCoord[1] < pstAvmAndCarSizeInfo->iLeftOffset - WHITE_BALANCE_AREA_OFFSET_X &&
					imgCoord[0] > pstAvmAndCarSizeInfo->iTopOffset + pstAvmAndCarSizeInfo->iCarImageHeight + WHITE_BALANCE_AREA_OFFSET_Y &&
					imgCoord[0] < pstAvmAndCarSizeInfo->iTopOffset + pstAvmAndCarSizeInfo->iCarImageHeight + WHITE_BALANCE_AREA_OFFSET_Y + WHITE_BALANCE_AREA_HEIGHT)
				{
					i_wb_idx1 = 4;
					i_wb_idx2 = 5;
				}
				else
				{
					i_wb_idx1 = -1;
					i_wb_idx2 = -1;
				}

				factorTmp1 = REAR_CAMERA_WEIGHT_BIRDVIEW * abs(slope[2][0] * imgCoord[1] - imgCoord[0] + lineParam_b[2][0]) / sqrt(slope[2][0] * slope[2][0] + 1);
				factorTmp2 = LEFT_CAMERA_WEIGHT_BIRDVIEW * abs(slope[2][1] * imgCoord[1] - imgCoord[0] + lineParam_b[2][1]) / sqrt(slope[2][1] * slope[2][1] + 1);
				factor_1 = factorTmp2 / (factorTmp1 + factorTmp2);
				factor_2 = factorTmp1 / (factorTmp1 + factorTmp2);
				BirdImg2Vehicle(imgCoord, pWorld1, &pOVSBasicInfo->stBirdView);
				BirdImg2Vehicle(imgCoord, pWorld2, &pOVSBasicInfo->stBirdView);

			}
			else if (imgCoord[0] > pstAvmAndCarSizeInfo->iCarImageHeight + pstAvmAndCarSizeInfo->iTopOffset &&
				imgCoord[0] > slope[2][1] * imgCoord[1] + lineParam_b[2][1] &&
				imgCoord[0] > slope[3][1] * imgCoord[1] + lineParam_b[3][1])
			{//back---------------------------
				i_view_1 = 2;
				i_view_2 = 0;
				i_wb_idx1 = -1;
				i_wb_idx2 = -1;
				factor_1 = 1;
				factor_2 = 0;
				BirdImg2Vehicle(imgCoord, pWorld1, &pOVSBasicInfo->stBirdView);
				u0_2 = 1;
				v0_2 = 1;

			}
			else if (imgCoord[0] > slope[3][0] * imgCoord[1] + lineParam_b[3][0] + SMLS_GAP&&
				imgCoord[0] <= slope[3][1] * imgCoord[1] + lineParam_b[3][1] - SMLS_GAP)
			{//right back---------------------
				i_view_1 = 4;
				i_view_2 = 2;

				if (imgCoord[1] > pstAvmAndCarSizeInfo->iLeftOffset + pstAvmAndCarSizeInfo->iCarImageWidth + WHITE_BALANCE_AREA_OFFSET_X &&
					imgCoord[1] < pstAvmAndCarSizeInfo->iLeftOffset + pstAvmAndCarSizeInfo->iCarImageWidth + WHITE_BALANCE_AREA_OFFSET_X + WHITE_BALANCE_AREA_WIDTH &&
					imgCoord[0] > pstAvmAndCarSizeInfo->iTopOffset + pstAvmAndCarSizeInfo->iCarImageHeight + WHITE_BALANCE_AREA_OFFSET_Y &&
					imgCoord[0] < pstAvmAndCarSizeInfo->iTopOffset + pstAvmAndCarSizeInfo->iCarImageHeight + WHITE_BALANCE_AREA_OFFSET_Y + WHITE_BALANCE_AREA_HEIGHT)
				{
					i_wb_idx1 = 6;
					i_wb_idx2 = 7;
				}
				else
				{
					i_wb_idx1 = -1;
					i_wb_idx2 = -1;
				}

				factorTmp1 = REAR_CAMERA_WEIGHT_BIRDVIEW * abs(slope[3][0] * imgCoord[1] - imgCoord[0] + lineParam_b[3][0]) / sqrt(slope[3][0] * slope[3][0] + 1);
				factorTmp2 = RIGHT_CAMERA_WEIGHT_BIRDVIEW * abs(slope[3][1] * imgCoord[1] - imgCoord[0] + lineParam_b[3][1]) / sqrt(slope[3][1] * slope[3][1] + 1);
				factor_1 = factorTmp2 / (factorTmp1 + factorTmp2);
				factor_2 = factorTmp1 / (factorTmp1 + factorTmp2);
				BirdImg2Vehicle(imgCoord, pWorld1, &pOVSBasicInfo->stBirdView);
				BirdImg2Vehicle(imgCoord, pWorld2, &pOVSBasicInfo->stBirdView);

			}
			else
			{//middle--------------------------
				i_view_1 = 0;
				i_view_2 = 0;
				i_wb_idx1 = -1;
				i_wb_idx2 = -1;
				factor_1 = 1;
				factor_2 = 0;
				u0_1 = 1;
				v0_1 = 1;
				u0_2 = 1;
				v0_2 = 1;
				uiAddress1 = 0;
				uiAddress2 = 0;
			}
			// ----------------------------------------------------------------------------------------------------
			if (i_view_1)
			{
				matrixMul(pOVSBasicInfo->staCameraParamEXT[i_view_1 - 1].daExtMtxV2C, pWorld1, pCam, 3, 3, 1);
				Cam2ImgScara(pImgInput, pCam, &pOVSBasicInfo->stCameraParamINT[i_view_1 - 1]);

				v0_1 = (float)(pImgInput[1] >= 1 ? (pImgInput[1] <= (1280 - 2) ? pImgInput[1] : (1280 - 2)) : 1);
				u0_1 = (float)(pImgInput[0] >= 1 ? (pImgInput[0] <= (720 - 2) ? pImgInput[0] : (720 - 2)) : 1);

				// calculate address and intercoe ------
				uiUCoord = (unsigned int)(u0_1);
				uiVCoord = (unsigned int)(v0_1);

				uiFactor1 = (unsigned int)(PRECISION_MULTI_5_BIT * factor_1);
				uiFactor1 = uiFactor1 > 31 ? 31 : (uiFactor1 < 1 ? 1 : uiFactor1);
				uiAddress1 = i_view_1 << 29;
				uiAddress1 += (uiUCoord * 1280 + uiVCoord) << 9;
				uiAddress1 += uiFactor1 << 4;
				uiAddress1 += (i_wb_idx1 & 0x0f);
				uu = ((((unsigned int)(u0_1 * PRECISION_MULTI_5_BIT)) | 8) & 0x7f) >> 3;  // 4 bit for each
				vv = ((((unsigned int)(v0_1 * PRECISION_MULTI_5_BIT)) | 8) & 0x7f) >> 3;
				PixWeight[0] = (16 - vv) * (16 - uu);
				PixWeight[1] = vv * (16 - uu);
				PixWeight[2] = (16 - vv) * uu;
				PixWeight[3] = vv * uu;
				PixWeight[0] = PixWeight[0] > 0xFF ? 0xFF : PixWeight[0];
				PixWeight[1] = PixWeight[1] > 0xFF ? 0xFF : PixWeight[1];
				PixWeight[2] = PixWeight[2] > 0xFF ? 0xFF : PixWeight[2];
				PixWeight[3] = PixWeight[3] > 0xFF ? 0xFF : PixWeight[3];

				uiCoe1 = (PixWeight[0] << 24) | (PixWeight[1] << 16) | (PixWeight[2] << 8) | PixWeight[3];
			}

			if (i_view_2)
			{
				matrixMul(pOVSBasicInfo->staCameraParamEXT[i_view_2 - 1].daExtMtxV2C, pWorld2, pCam, 3, 3, 1);
				Cam2ImgScara(pImgInput, pCam, &pOVSBasicInfo->stCameraParamINT[i_view_2 - 1]);

				v0_2 = (float)(pImgInput[1] >= 1 ? (pImgInput[1] <= (1280 - 2) ? pImgInput[1] : (1280 - 2)) : 1);
				u0_2 = (float)(pImgInput[0] >= 1 ? (pImgInput[0] <= (720 - 2) ? pImgInput[0] : (720 - 2)) : 1);

				// calculate address and intercoe ------
				uiUCoord = (unsigned int)(u0_2);
				uiVCoord = (unsigned int)(v0_2);
				uiFactor2 = 32 - uiFactor1;
				uiAddress2 = i_view_2 << 29;
				uiAddress2 += (uiUCoord * 1280 + uiVCoord) << 9;
				uiAddress2 += uiFactor2 << 4;
				uiAddress2 += (i_wb_idx2 & 0x0F);
				uu = ((((unsigned int)(u0_2 * PRECISION_MULTI_5_BIT))) & 0x7f) >> 3;  // 4 bit for each
				vv = ((((unsigned int)(v0_2 * PRECISION_MULTI_5_BIT))) & 0x7f) >> 3;
				PixWeight[0] = (16 - vv) * (16 - uu);
				PixWeight[1] = vv * (16 - uu);
				PixWeight[2] = (16 - vv) * uu;
				PixWeight[3] = vv * uu;
				PixWeight[0] = PixWeight[0] > 0xFF ? 0xFF : PixWeight[0];
				PixWeight[1] = PixWeight[1] > 0xFF ? 0xFF : PixWeight[1];
				PixWeight[2] = PixWeight[2] > 0xFF ? 0xFF : PixWeight[2];
				PixWeight[3] = PixWeight[3] > 0xFF ? 0xFF : PixWeight[3];

				uiCoe2 = (PixWeight[0] << 24) | (PixWeight[1] << 16) | (PixWeight[2] << 8) | PixWeight[3];
			}

			//----------------------------------------------------------------------------------------------------
			// AvmTableLead -----
			if ((factor_1 - factor_2) > SMLS_FACTOR_E)
			{// mark the 1st weighted 
				uiAddressLead = uiAddress1;// | 1;
				uiAddressSupport = uiAddress2;
				uiCoeLead = uiCoe1;
				uiCoeSupport = uiCoe2;
			}
			else
			{// else is the 2nd weighted
				uiAddressLead = uiAddress2;// | 1;
				uiAddressSupport = uiAddress1;
				uiCoeLead = uiCoe2;
				uiCoeSupport = uiCoe1;
			}

			*(pAddressLead++) = uiAddressLead;
			*(pCoeLead++) = uiCoeLead;

			if (i_view_2)
			{
				uiDstAddress = (imgCoord[0] * pOVSBasicInfo->stBirdView.iImgWidth + imgCoord[1]) * 2; // dest pixel location, byte
				*(pAddressSupport++) = uiAddressLead;
				*(pAddressSupport++) = uiAddressSupport;
				*(pCoeSupport++) = uiCoeLead;
				*(pCoeSupport++) = uiCoeSupport;

				*(pDstAddress++) = uiDstAddress;

				if (i_wb_idx1 != -1)
				{
					p_stAvmTableSupport->iaAreaPointNumEach[i_wb_idx1] ++;
				}

				if (i_wb_idx2 != -1)
				{
					p_stAvmTableSupport->iaAreaPointNumEach[i_wb_idx2] ++;
				}
				p_stAvmTableSupport->iAreaPointNum++;
			}
			count++;
		}
	}
	free(pstAvmAndCarSizeInfo);
}

static int WhiteBalanceCalcRGB(IplImage **IMGs, AvmTableSupport *pAvmTableSupport, TVS_LIB_WHITE_BALANCE emTvsLibWhiteBalance, int *iWbFactor)
{// table offset are for vertical half d1 images
	// but the input for RGB is CIF
	int iCamIdx1, k, iWbFtrIdx, imgCoord[2];
	int WB_sums[3][WHITE_BALANCE_AREA];
	int WB_average_area[3][WHITE_BALANCE_AREA];
	int WB_average_sum[3], WB_average_all[3];
	double *Mmtx, *Umtx, *Vmtx;
	float fscale;
	unsigned int offset1;
	unsigned int *pAddrSupport = pAvmTableSupport->puiSrcAddress;
	CvScalar s;

	if (emTvsLibWhiteBalance == LIB_WHITE_BALANCE_ON)
	{
		for (k = 0; k < WHITE_BALANCE_AREA; k++)
		{// initial sums
			WB_sums[0][k] = 0;
			WB_sums[1][k] = 0;
			WB_sums[2][k] = 0;
		}
		// summary
		for (k = 0; k < pAvmTableSupport->iAreaPointNum * 2; k++)
		{
			iCamIdx1 = (*pAddrSupport) >> 29;
			offset1 = ((*pAddrSupport) & 0x1FFFFE00) >> 9;  // byte location in vertical half d1 images
			imgCoord[0] = offset1 / (W_SRC_IMG);    // coord in vertical half image
			imgCoord[1] = (offset1) % W_SRC_IMG;
			iWbFtrIdx = ((*pAddrSupport++) & 0x0F);

			if (iWbFtrIdx < WHITE_BALANCE_AREA)
			{
				s = cvGet2D(IMGs[iCamIdx1 - 1], imgCoord[0] / 2, imgCoord[1]);    // coord in CIF image

				WB_sums[0][iWbFtrIdx] += (int)s.val[0];  //B
				WB_sums[1][iWbFtrIdx] += (int)s.val[1];  //G
				WB_sums[2][iWbFtrIdx] += (int)s.val[2];  //R
			}

		}
		// calculation --------------------------------------------------------------------------------
		WB_average_sum[0] = 0;
		WB_average_sum[1] = 0;
		WB_average_sum[2] = 0;

		for (k = 0; k < WHITE_BALANCE_AREA; k++)
		{// average of each area
			if (pAvmTableSupport->iaAreaPointNumEach[k] != 0)
			{
				WB_average_area[0][k] = WB_sums[0][k] / pAvmTableSupport->iaAreaPointNumEach[k];
				WB_average_area[1][k] = WB_sums[1][k] / pAvmTableSupport->iaAreaPointNumEach[k];
				WB_average_area[2][k] = WB_sums[2][k] / pAvmTableSupport->iaAreaPointNumEach[k];
			}
			else
			{
				WB_average_area[0][k] = 128;
				WB_average_area[1][k] = 128;
				WB_average_area[2][k] = 128;
			}
			WB_average_sum[0] += WB_average_area[0][k];
			WB_average_sum[1] += WB_average_area[1][k];
			WB_average_sum[2] += WB_average_area[2][k];
		}

		// dest anchor wb value
		WB_average_all[0] = WB_average_sum[0] / WHITE_BALANCE_AREA;
		WB_average_all[1] = WB_average_sum[1] / WHITE_BALANCE_AREA;
		WB_average_all[2] = WB_average_sum[2] / WHITE_BALANCE_AREA;

		Mmtx = (double*)malloc(4 * 4 * sizeof(double));
		Umtx = (double*)malloc(4 * 4 * sizeof(double));
		Vmtx = (double*)malloc(4 * 4 * sizeof(double));
		for (k = 0; k < 3; k++)
		{
			Mmtx[0] = WB_average_area[k][0] * WB_average_area[k][0] + WB_average_area[k][2] * WB_average_area[k][2];
			Mmtx[1] = -WB_average_area[k][0] * WB_average_area[k][1];
			Mmtx[2] = -WB_average_area[k][2] * WB_average_area[k][3];
			Mmtx[3] = 0;

			Mmtx[4] = -WB_average_area[k][0] * WB_average_area[k][1];
			Mmtx[5] = WB_average_area[k][1] * WB_average_area[k][1] + WB_average_area[k][4] * WB_average_area[k][4];
			Mmtx[6] = 0;
			Mmtx[7] = -WB_average_area[k][4] * WB_average_area[k][5];

			Mmtx[8] = -WB_average_area[k][2] * WB_average_area[k][3];
			Mmtx[9] = 0;
			Mmtx[10] = WB_average_area[k][3] * WB_average_area[k][3] + WB_average_area[k][6] * WB_average_area[k][6];
			Mmtx[11] = -WB_average_area[k][6] * WB_average_area[k][7];

			Mmtx[12] = 0;
			Mmtx[13] = -WB_average_area[k][4] * WB_average_area[k][5];
			Mmtx[14] = -WB_average_area[k][6] * WB_average_area[k][7];
			Mmtx[15] = WB_average_area[k][5] * WB_average_area[k][5] + WB_average_area[k][7] * WB_average_area[k][7];
			if (SplitUV(Mmtx, Umtx, Vmtx, 4, 4))
			{
				fscale = (float)(4 / (Vmtx[12] + Vmtx[13] + Vmtx[14] + Vmtx[15]));
				iWbFactor[k * 4 + 0] = (int)(Vmtx[12] * 128 * fscale);
				iWbFactor[k * 4 + 1] = (int)(Vmtx[13] * 128 * fscale);
				iWbFactor[k * 4 + 2] = (int)(Vmtx[14] * 128 * fscale);
				iWbFactor[k * 4 + 3] = (int)(Vmtx[15] * 128 * fscale);
				if (iWbFactor[k * 4 + 0] < 0)
				{
					iWbFactor[k * 4 + 0] = -iWbFactor[k * 4 + 0];
					iWbFactor[k * 4 + 1] = -iWbFactor[k * 4 + 1];
					iWbFactor[k * 4 + 2] = -iWbFactor[k * 4 + 2];
					iWbFactor[k * 4 + 3] = -iWbFactor[k * 4 + 3];
				}
			}
			else
			{
				iWbFactor[k * 4 + 0] = 128;
				iWbFactor[k * 4 + 1] = 128;
				iWbFactor[k * 4 + 2] = 128;
				iWbFactor[k * 4 + 3] = 128;
			}
		}

		free(Mmtx);
		free(Umtx);
		free(Vmtx);
	}
	else    // white balance not required ----------------------------------------------------------------
	{
		for (k = 0; k < WB_FACTOR_NUM; k++)
		{// in order of y1y2y3y4 u1u2u3u4 v1v2v3v4
			iWbFactor[k] = 128;
		}
	}
	return 1;
}

int MapBirdImgRGB(IplImage **IMGs, IplImage *dst_IMG, int iSeam, AvmTableLead *pAvmTableLead, AvmTableSupport *pAvmTableSupport, TVSLIB_INTERPOLATION emTvsLibInterpolation, TVS_LIB_WHITE_BALANCE emTvsLibWhiteBalance)
{
	int img_w, imgCoord[2], imgCoord_s1[2], imgCoord_s2[2];
	int u, v, j, iCount, iDstIndex, c = 0;
	int iaWBFactors[WB_FACTOR_NUM]; // in order of y1y2y3y4 u1u2u3u4 v1v2v3v4
	unsigned int *pAddrLead = pAvmTableLead->puiSrcAddress;
	unsigned int *pCoesLead = pAvmTableLead->puiInterCoe;

	unsigned int *pAddrSupport = pAvmTableSupport->puiSrcAddress;
	unsigned int *pCoesSupport = pAvmTableSupport->puiInterCoe;
	unsigned int *pDstAddress = pAvmTableSupport->puiDstAddress;
	unsigned char *pByteLocationLead1 = NULL;
	unsigned char *pByteLocationLead2 = NULL;

	unsigned int offset1, offset2, factor1, factor2;
	unsigned int coe1, coe1_1, coe1_2, coe1_3, coe1_4;
	unsigned int coe2, coe2_1, coe2_2, coe2_3, coe2_4;
	unsigned int iCamIdx1, iCamIdx2;
	CvScalar s, s1, s2, s3, s4, s_zero, s_a, s_b;

	s_zero.val[0] = 0;
	s_zero.val[1] = 0;
	s_zero.val[2] = 0;

	img_w = W_SRC_IMG;  // pixels

	if (emTvsLibInterpolation == LIB_INTERPOLATE_ON)// interpolated  -----------------------------------------
	{
		WhiteBalanceCalcRGB(IMGs, pAvmTableSupport, emTvsLibWhiteBalance, iaWBFactors);
		//----------------------------------------------------------------
		// first pick points from lead avm table ;
		for (u = 0; u < pAvmTableLead->iHeight; u++)
		{
			for (v = 0; v < pAvmTableLead->iWidth; v++)
			{
				iCamIdx1 = (*pAddrLead) >> 29;
				offset1 = ((*pAddrLead++) & 0x1FFFFE00) >> 9;   // byte location in vertical half d1 image
				imgCoord[0] = offset1 / (1280);    // coord in vertical half d1 image
				imgCoord[1] = (offset1) % 1280;

				coe1 = *pCoesLead++;
				coe1_1 = coe1 >> 24;
				coe1_2 = (coe1 >> 16) & 0xff;
				coe1_3 = (coe1 >> 8) & 0xff;
				coe1_4 = coe1 & 0xff;

				if (iCamIdx1)
				{
					s1 = cvGet2D(IMGs[iCamIdx1 - 1], imgCoord[0], imgCoord[1]);
					s2 = cvGet2D(IMGs[iCamIdx1 - 1], imgCoord[0], imgCoord[1] + 1);
					s3 = cvGet2D(IMGs[iCamIdx1 - 1], imgCoord[0] + 1, imgCoord[1]);
					s4 = cvGet2D(IMGs[iCamIdx1 - 1], imgCoord[0] + 1, imgCoord[1] + 1);

					for (j = 0; j < 3; j++)
					{
						s.val[j] = s1.val[j] * coe1_1 + s2.val[j] * coe1_2 + s3.val[j] * coe1_3 + s4.val[j] * coe1_4;
						s.val[j] = s.val[j] * iaWBFactors[j * 4 + iCamIdx1 - 1] / 32768;    // >> 15
					}
				}
				else
				{
					s = s_zero;
				}

				cvSet2D(dst_IMG, u, v, s);
			}
		}
		//// then seamless 
		if (1 != iSeam)
		{// seamless -----------------------------------------------------------------------
			// secondly, use avm table support
			for (u = 0; u < pAvmTableSupport->iAreaPointNum; u++)
			{
				iDstIndex = (*pDstAddress++);   // byte location
				imgCoord[0] = iDstIndex / (pAvmTableLead->iWidth * 2);  // coord in dest image
				imgCoord[1] = (iDstIndex / 2) % pAvmTableLead->iWidth;

				// 1st weight
				iCamIdx1 = (*pAddrSupport) >> 29;
				offset1 = ((*pAddrSupport) & 0x1FFFFE00) >> 9;  // byte location
				factor1 = ((*pAddrSupport++) & 0x1F0) >> 4;

				imgCoord_s1[0] = offset1 / (1280);         //coord in vertical half d1 image
				imgCoord_s1[1] = (offset1) % 1280;

				//2nd weight
				iCamIdx2 = (*pAddrSupport) >> 29;
				offset2 = ((*pAddrSupport) & 0x1FFFFE00) >> 9;
				factor2 = ((*pAddrSupport++) & 0x1F0) >> 4;

				imgCoord_s2[0] = offset2 / (1280);         //coord in vertical half d1 image
				imgCoord_s2[1] = (offset2) % 1280;

				coe1 = *pCoesSupport++;
				coe2 = *pCoesSupport++;
				coe1_1 = coe1 >> 24;
				coe1_2 = (coe1 >> 16) & 0xff;
				coe1_3 = (coe1 >> 8) & 0xff;
				coe1_4 = coe1 & 0xff;

				coe2_1 = coe2 >> 24;
				coe2_2 = (coe2 >> 16) & 0xff;
				coe2_3 = (coe2 >> 8) & 0xff;
				coe2_4 = coe2 & 0xff;

				s1 = cvGet2D(IMGs[iCamIdx1 - 1], imgCoord_s1[0], imgCoord_s1[1]);
				s2 = cvGet2D(IMGs[iCamIdx1 - 1], imgCoord_s1[0], imgCoord_s1[1] + 1);
				s3 = cvGet2D(IMGs[iCamIdx1 - 1], imgCoord_s1[0] + 1, imgCoord_s1[1]);
				s4 = cvGet2D(IMGs[iCamIdx1 - 1], imgCoord_s1[0] + 1, imgCoord_s1[1] + 1);

				for (j = 0; j < 3; j++)
				{
					s_a.val[j] = s1.val[j] * coe1_1 + s2.val[j] * coe1_2 + s3.val[j] * coe1_3 + s4.val[j] * coe1_4;
					s_a.val[j] = s_a.val[j] * iaWBFactors[j * 4 + iCamIdx1 - 1] / 32768;    // >> 15
				}

				s1 = cvGet2D(IMGs[iCamIdx2 - 1], imgCoord_s2[0], imgCoord_s2[1]);
				s2 = cvGet2D(IMGs[iCamIdx2 - 1], imgCoord_s2[0], imgCoord_s2[1] + 1);
				s3 = cvGet2D(IMGs[iCamIdx2 - 1], imgCoord_s2[0] + 1, imgCoord_s2[1]);
				s4 = cvGet2D(IMGs[iCamIdx2 - 1], imgCoord_s2[0] + 1, imgCoord_s2[1] + 1);

				for (j = 0; j < 3; j++)
				{
					s_b.val[j] = s1.val[j] * coe2_1 + s2.val[j] * coe2_2 + s3.val[j] * coe2_3 + s4.val[j] * coe2_4;
					s_b.val[j] = s_b.val[j] * iaWBFactors[j * 4 + iCamIdx1 - 1] / 32768;    // >> 15
				}

				//mix together
				s.val[0] = (s_a.val[0] * factor1 + s_b.val[0] * factor2) / PRECISION_MULTI_5_BIT;
				s.val[1] = (s_a.val[1] * factor1 + s_b.val[1] * factor2) / PRECISION_MULTI_5_BIT;
				s.val[2] = (s_a.val[2] * factor1 + s_b.val[2] * factor2) / PRECISION_MULTI_5_BIT;

				cvSet2D(dst_IMG, imgCoord[0], imgCoord[1], s);
			}
		}
	}
	else// not interpolated - - - - - - - - - - - - - - - 
	{
		iCount = 0;
		WhiteBalanceCalcRGB(IMGs, pAvmTableSupport, emTvsLibWhiteBalance, iaWBFactors);
		// ---------------------------------------------------------
		for (u = 0; u < pAvmTableLead->iHeight; u++)
		{
			for (v = 0; v < pAvmTableLead->iWidth; v++)
			{
				iCamIdx1 = (*pAddrLead) >> 29;
				offset1 = ((*pAddrLead++) & 0x1FFFFE00) >> 9;   // byte location in vertical half d1 image
				imgCoord[0] = offset1 / (1280);    // coord in vertical half d1 image
				imgCoord[1] = (offset1) % 1280;

				if (iCamIdx1)
				{
					s = cvGet2D(IMGs[iCamIdx1 - 1], imgCoord[0], imgCoord[1]);
					for (j = 0; j < 3; j++)
					{
						s.val[j] = s.val[j] * iaWBFactors[j * 4 + iCamIdx1 - 1] / 128;    // >> 7
					}
				}
				else
				{
					s = s_zero;
				}
				cvSet2D(dst_IMG, u, v, s);
			}
		}

		if (1 != iSeam)
		{// seamless
			// use avm table support
			for (u = 0; u < pAvmTableSupport->iAreaPointNum; u++)
			{
				iDstIndex = (*pDstAddress++);   // byte location
				imgCoord[0] = iDstIndex / (pAvmTableLead->iWidth * 2);  // coord in dest image
				imgCoord[1] = (iDstIndex / 2) % pAvmTableLead->iWidth;

				// 1st weight
				iCamIdx1 = (*pAddrSupport) >> 29;
				offset1 = ((*pAddrSupport) & 0x1FFFFE00) >> 9;  // byte location
				factor1 = ((*pAddrSupport++) & 0x1F0) >> 4;
				imgCoord_s1[0] = offset1 / (1280);         //coord in vertical half d1 image
				imgCoord_s1[1] = (offset1) % 1280;

				//2nd weight
				iCamIdx2 = (*pAddrSupport) >> 29;
				offset2 = ((*pAddrSupport) & 0x1FFFFE00) >> 9;
				factor2 = ((*pAddrSupport++) & 0x1F0) >> 4;
				imgCoord_s2[0] = offset2 / (1280);         //coord in vertical half d1 image
				imgCoord_s2[1] = (offset2) % 1280;

				s_a = cvGet2D(IMGs[iCamIdx1 - 1], imgCoord_s1[0], imgCoord_s1[1]);
				for (j = 0; j < 3; j++)
				{
					s_a.val[j] = s_a.val[j] * iaWBFactors[j * 4 + iCamIdx1 - 1] / 128;    // >> 7
				}

				s_b = cvGet2D(IMGs[iCamIdx2 - 1], imgCoord_s2[0], imgCoord_s2[1]);
				for (j = 0; j < 3; j++)
				{
					s_b.val[j] = s_b.val[j] * iaWBFactors[j * 4 + iCamIdx1 - 1] / 128;    // >> 7
				}
				//mix together
				s.val[0] = (s_a.val[0] * factor1 + s_b.val[0] * factor2) / PRECISION_MULTI_5_BIT;
				s.val[1] = (s_a.val[1] * factor1 + s_b.val[1] * factor2) / PRECISION_MULTI_5_BIT;
				s.val[2] = (s_a.val[2] * factor1 + s_b.val[2] * factor2) / PRECISION_MULTI_5_BIT;

				cvSet2D(dst_IMG, imgCoord[0], imgCoord[1], s);
			}
		}
		// if seamless image is required
	}
	return 1;
}



