// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSHUD.h"

void AFPSHUD::DrawHUD()
{
    Super::DrawHUD();

    if (CrosshairTexture)
    {
        // Find the center of our canvas. (キャンバスの中心を見つけます)
        FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
        // Offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas. (テクスチャの中央をキャンバスの中央と一致させるためにテクスチャの半分のディメンションでオフセット)
        FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

        // Draw the crosshair at the centerpoint. (中心点にクロスヘアを描画)
        FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
    }
}