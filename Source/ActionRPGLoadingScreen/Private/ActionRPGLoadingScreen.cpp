// Copyright Epic Games, Inc. All Rights Reserved.

#include "ActionRPGLoadingScreen.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"
#include "Widgets/Images/SThrobber.h"



// 此模块必须在 .uproject 文件中“PreLoadingScreen”加载，否则无法及时挂接！
struct FRPGLoadingScreenBrush : public FSlateDynamicImageBrush//, public FGCObject
{
	FRPGLoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		: FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		SetResourceObject(LoadObject<UObject>(NULL, *InTextureName.ToString()));
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (TObjectPtr<UObject> CachedResourceObject = GetResourceObject())
		{
			Collector.AddReferencedObject(CachedResourceObject);
		}
	}
};

class SRPGLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRPGLoadingScreen) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		// 加载带有文本的 Logo 版本，路径是硬编码的，因为这在启动的非常早期加载
		static const FName LoadingScreenName(TEXT("/Game/UI/T_ActionRPG_TransparentLogo.T_ActionRPG_TransparentLogo"));

		LoadingScreenBrush = MakeShareable(new FRPGLoadingScreenBrush(LoadingScreenName, FVector2D(1024, 256)));
		
		FSlateBrush *BGBrush = new FSlateBrush();
		BGBrush->TintColor = FLinearColor(0.034f, 0.034f, 0.034f, 1.0f);

		ChildSlot
			[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)	
				.BorderImage(BGBrush)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(LoadingScreenBrush.Get())
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(FMargin(10.0f))
				[
					SNew(SThrobber)
					.Visibility(this, &SRPGLoadingScreen::GetLoadIndicatorVisibility)
				]
			]
		];
	}

private:
	/** 是否显示 ... 指示器 */
	EVisibility GetLoadIndicatorVisibility() const
	{
		bool Vis =  GetMoviePlayer()->IsLoadingFinished();
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}
	
	/** 加载屏幕图像画笔 */
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};

class FActionRPGLoadingScreenModule : public IActionRPGLoadingScreenModule
{
public:
	virtual void StartupModule() override
	{
		// 强制加载 Cooker 引用
		LoadObject<UObject>(nullptr, TEXT("/Game/UI/T_ActionRPG_TransparentLogo.T_ActionRPG_TransparentLogo") );

		if (IsMoviePlayerEnabled())
		{
			CreateScreen();
		}
	}
	
	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) override
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = !bPlayUntilStopped;
		LoadingScreen.bWaitForManualStop = bPlayUntilStopped;
		LoadingScreen.bAllowEngineTick = bPlayUntilStopped;
		LoadingScreen.MinimumLoadingScreenDisplayTime = PlayTime;
		LoadingScreen.WidgetLoadingScreen = SNew(SRPGLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

	virtual void StopInGameLoadingScreen() override
	{
		GetMoviePlayer()->StopMovie();
	}

	virtual void CreateScreen()
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 3.f;
		LoadingScreen.WidgetLoadingScreen = SNew(SRPGLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

};

IMPLEMENT_GAME_MODULE(FActionRPGLoadingScreenModule, ActionRPGLoadingScreen);
