// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalConst.h"

const FVector4 UGlobalConst::RedColor = FVector4(1.f, 0.2f, 0.2f, 1.f);
const FVector4 UGlobalConst::GreenColor = FVector4(.2f, 1.f, 0.2f, 1.f);
const FVector4 UGlobalConst::BlueColor = FVector4(.2f, 0.2f, 1.f, 1.f);
const FVector4 UGlobalConst::WhiteColor = FVector4(.7f, 0.7f, 0.7f, 1.f);
const FVector4 UGlobalConst::BlackColor = FVector4(.1f, 0.1f, 0.1f, 1.f);
const FVector4 UGlobalConst::PearlColor = FVector4(.7f, 0.2f, 0.6f, 1.f);

const FVector4 UGlobalConst::StrongRedColor = FVector4(1.f, 0.05f, 0.05f, 1.f);
const FVector4 UGlobalConst::StrongGreenColor = FVector4(0.05f, 1.f, 0.05f, 1.f);
const FVector4 UGlobalConst::StrongBlueColor = FVector4(0.05f, 0.05f, 1.f, 1.f);
const FVector4 UGlobalConst::StrongWhiteColor = FVector4(.9f, 0.9f, 0.9f, 1.f);
const FVector4 UGlobalConst::StrongBlackColor = FVector4(.05f, 0.05f, 0.05f, 1.f);
const FVector4 UGlobalConst::StrongPearlColor = FVector4(.8f, 0.3f, 0.7f, 1.f);

//!----------------Msg-------------------
const FString UGlobalConst::MsgNotTurn = FString::Printf(TEXT("당신의 차례가 아닙니다."));
const FString UGlobalConst::MsgThreeToken = FString::Printf(TEXT("토큰은 3개까지 선택할 수 있습니다."));
const FString UGlobalConst::MsgUnableGold = FString::Printf(TEXT("황금 토큰을 선택할 수 없습니다."));
const FString UGlobalConst::MsgOneGold = FString::Printf(TEXT("이미 황금 토큰을 선택하였습니다."));
const FString UGlobalConst::MsgNotContiue = FString::Printf(TEXT("연속하지 않은 토큰입니다."));
