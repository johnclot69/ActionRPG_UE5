// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ----------------------------------------------------------------------------------------------------------------
// 该头文件被项目中的所有头文件包含，因此是声明公共包含文件的好地方
// 我们包含 EngineMinimal 和我们大多数类使用的引擎头文件子集
// 我们不想包含 "Engine.h"，因为这会引入太多我们不需要的类并减慢编译时间
// ----------------------------------------------------------------------------------------------------------------

#include "EngineMinimal.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"
#include "RPGTypes.h"

ACTIONRPG_API DECLARE_LOG_CATEGORY_EXTERN(LogActionRPG, Log, All);
