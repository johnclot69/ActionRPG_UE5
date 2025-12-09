// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ActionRPG.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameModeBase.generated.h"

/** GameMode 基类，应进行蓝图化 */
UCLASS()
class ACTIONRPG_API ARPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** 构造函数 */
	ARPGGameModeBase();

	/** 
	 * 重写此函数对于本示例并非必不可少，因为在正常情况下不会调用此函数。
	 * 添加它只是为了简化开发时的活动（如自动化测试）。
	 * 默认的 ResetLevel 实现与 ActionRPG 的设置不太兼容
	 * （这没关系，这正是我们要重写函数的原因！）。
	 */
	virtual void ResetLevel() override;

	/** 如果已调用 GameOver() 则返回 true，否则返回 false */
	virtual bool HasMatchEnded() const override;

	/** 游戏结束时调用，即玩家死亡、时间耗尽或游戏完成 */
	UFUNCTION(BlueprintCallable, Category=Game)
	virtual void GameOver();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category=Game, meta=(DisplayName="DoRestart", ScriptName="DoRestart"))
	void K2_DoRestart();

	UFUNCTION(BlueprintImplementableEvent, Category=Game, meta=(DisplayName="OnGameOver", ScriptName="OnGameOver"))
	void K2_OnGameOver();

	UPROPERTY(BlueprintReadOnly, Category=Game)
	uint32 bGameOver : 1;
};

