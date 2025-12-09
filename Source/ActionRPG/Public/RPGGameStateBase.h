// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "GameFramework/GameStateBase.h"
#include "RPGGameStateBase.generated.h"

/** GameState 基类，应进行蓝图化 */
UCLASS()
class ACTIONRPG_API ARPGGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	ARPGGameStateBase() {}
};

