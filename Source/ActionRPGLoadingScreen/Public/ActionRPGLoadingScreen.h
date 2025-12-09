// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

/** 此游戏加载屏幕的模块接口 */
class IActionRPGLoadingScreenModule : public IModuleInterface
{
public:
	/** 加载模块以便可以将其打开 */
	static inline IActionRPGLoadingScreenModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IActionRPGLoadingScreenModule>("ActionRPGLoadingScreen");
	}

	/** 启动游戏内加载屏幕（非启动时） */
	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) = 0;

	/** 停止加载屏幕 */
	virtual void StopInGameLoadingScreen() = 0;
};
