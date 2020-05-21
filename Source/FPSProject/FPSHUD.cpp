// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSHUD.h"

void AFPSHUD::DrawHUD()
{
    Super::DrawHUD();

    if (CrosshairTexture)
    {
        // Find the center of our canvas. (�L�����o�X�̒��S�������܂�)
        FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
        // Offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas. (�e�N�X�`���̒������L�����o�X�̒����ƈ�v�����邽�߂Ƀe�N�X�`���̔����̃f�B�����V�����ŃI�t�Z�b�g)
        FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

        // Draw the crosshair at the centerpoint. (���S�_�ɃN���X�w�A��`��)
        FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
    }
}