// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpt_OSIMng.h"
#include "Kismet/GameplayStatics.h"
#include "GameFrameWork/Character.h"
#include "Engine.h"
#include "Actor/Characters/GameCharacter.h"
#include "Components/Image.h"
#include "Widget_OSIPin.h"

UCpt_OSIMng::UCpt_OSIMng()
{
	PrimaryComponentTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UClass> Const_Widget(TEXT("/Game/1_Project_Main/1_Blueprints/UI/GameHUD/OSI/BP_Widget_OSIPin.BP_Widget_OSIPin_C"));
	if (Const_Widget.Succeeded())
	{
		m_pInst_Widget = Const_Widget.Object;
	}
}

void UCpt_OSIMng::BeginPlay()
{
	Super::BeginPlay();

}

void UCpt_OSIMng::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	for (int i = 0; i < m_pPinList.Num(); i++)
	{
		m_pPinList[i]->RemoveFromParent();
	}

	m_pPinList.Empty();
}

void UCpt_OSIMng::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool bLoop = false;
	do
	{
		bLoop = false;
		UWidget_OSIPin* pRemoveObj = nullptr;
		for (int i = 0; i < m_pPinList.Num(); i++)
		{
			AGameCharacter* pSrc = m_pPinList[i]->GetTargetActor();

			if (pSrc != nullptr)
			{
				if (pSrc->GetLife() == false)
				{
					pRemoveObj = m_pPinList[i];
					bLoop = true;
					break;
				}
			}
			else
			{
				pRemoveObj = m_pPinList[i];
				bLoop = true;
				break;
			}
		}
		if (pRemoveObj != nullptr)
		{
			pRemoveObj->RemoveFromParent();
			m_pPinList.Remove(pRemoveObj);
		}
	} while (bLoop);


	for (int i = 0; i < m_pPinList.Num(); i++)
	{
		FVector2D vScreenLoc = FVector2D::ZeroVector;
		float fRotation = 0.0f;
		float fRot = 0.0f;
		bool bIsOnScreen = false;

		AGameCharacter* pSrc = m_pPinList[i]->GetTargetActor();
		if (pSrc != nullptr)
		{
			//ULOG(TEXT("%s"), *vScreenLoc.ToString());
			FindScreenEdgeLocationForWorldLocation(pSrc->GetActorLocation(), 0.9f, vScreenLoc, fRotation, bIsOnScreen, fRot);
			if (bIsOnScreen == false)
			{
				m_pPinList[i]->SetShow(true);

				const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
				const FVector2D  ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);

				if (vScreenLoc.X > ViewportCenter.X)		//! Right
				{	
					vScreenLoc.X -= 5.0f;
				}
				else
				{
					vScreenLoc.X -= 50.0f;		//! Left
				}

				if (vScreenLoc.Y > ViewportCenter.Y)	//! Bot
				{
					vScreenLoc.Y -= 36.0f;
				}
				else
				{
					vScreenLoc.Y -= 30.0f;			//! Top
				}
				
				m_pPinList[i]->SetPositionInViewport(vScreenLoc);
				m_pPinList[i]->SetRenderAngle(fRotation);
				//m_pPinList[i]->GetIconImage()->SetRenderAngle(fRot);
			}
			else
			{
				m_pPinList[i]->SetShow(false);
			//	m_pPinList[i]->SetPositionInViewport(vScreenLoc);
			}
			
		}
		
	}

	
	
}

void  UCpt_OSIMng::AddPin(class AGameCharacter* pActor, int32 nIconState)
{
	if (m_pInst_Widget == nullptr) return;
	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidget_OSIPin* pObj = CreateWidget<UWidget_OSIPin>(pPlayerController, m_pInst_Widget);

	pObj->SetTargetActor(pActor);
	pObj->AddToViewport();
	pObj->SetChangeImage(nIconState);
	m_pPinList.Add(pObj);
}

void UCpt_OSIMng::DestroyPin()
{
	for (int32 i = 0; i < m_pPinList.Num(); i++)
	{
		m_pPinList[i]->SetShow(false);		
	}

	m_pPinList.Empty();
	DestroyComponent();
}

void UCpt_OSIMng::FindScreenEdgeLocationForWorldLocation(FVector InLocation,  float EdgePercent, 
														FVector2D& OutScreenPosition, float& OutRotationAngleDegrees, bool &bIsOnScreen, float& fRot)
{
	UObject* WorldContextObject = GetWorld();

	bIsOnScreen = false;
	OutRotationAngleDegrees = 0.f;
	fRot = 0.f;
	FVector2D *ScreenPosition = new FVector2D();
	
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D  ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);

	if (!World) return;

	APlayerController* PlayerController = (WorldContextObject ? UGameplayStatics::GetPlayerController(WorldContextObject, 0) : NULL);
	ACharacter *PlayerCharacter = static_cast<ACharacter *> (PlayerController->GetPawn());

	if (!PlayerCharacter) return;


	FVector Forward = PlayerCharacter->GetActorForwardVector();
	FVector Offset = (InLocation - PlayerCharacter->GetActorLocation()).GetSafeNormal();

	float DotProduct = FVector::DotProduct(Forward, Offset);
	bool bLocationIsBehindCamera = (DotProduct < 0);

	if (bLocationIsBehindCamera)
	{
		// For behind the camera situation, we cheat a little to put the
		// marker at the bottom of the screen so that it moves smoothly
		// as you turn around. Could stand some refinement, but results
		// are decent enough for most purposes.

		FVector DiffVector = InLocation - PlayerCharacter->GetActorLocation();
		FVector Inverted = DiffVector * -1.f;
		FVector NewInLocation = PlayerCharacter->GetActorLocation() * Inverted;

		NewInLocation.Z -= 5000;

		PlayerController->ProjectWorldLocationToScreen(NewInLocation, *ScreenPosition);
		ScreenPosition->Y = (EdgePercent * ViewportCenter.X) * 2.f;
		ScreenPosition->X = -ViewportCenter.X - ScreenPosition->X;
	}

	PlayerController->ProjectWorldLocationToScreen(InLocation, *ScreenPosition);

	// Check to see if it's on screen. If it is, ProjectWorldLocationToScreen is all we need, return it.
	if (ScreenPosition->X >= 0.f && ScreenPosition->X <= ViewportSize.X
		&& ScreenPosition->Y >= 0.f && ScreenPosition->Y <= ViewportSize.Y)
	{
		OutScreenPosition = *ScreenPosition;
		bIsOnScreen = true;
		return;
	}

	*ScreenPosition -= ViewportCenter;

	float AngleRadians = FMath::Atan2(ScreenPosition->Y, ScreenPosition->X);
	AngleRadians -= FMath::DegreesToRadians(90.f);
	fRot = AngleRadians;

	OutRotationAngleDegrees = FMath::RadiansToDegrees(AngleRadians) + 180.f;

	float Cos = cosf(AngleRadians);
	float Sin = -sinf(AngleRadians);

	ScreenPosition = new FVector2D(ViewportCenter.X + (Sin * 150.f), ViewportCenter.Y + Cos * 150.f);

	float m = Cos / Sin;

	FVector2D ScreenBounds = ViewportCenter * EdgePercent;

	if (Cos > 0)
	{
		ScreenPosition = new FVector2D(ScreenBounds.Y / m, ScreenBounds.Y);
	}
	else
	{
		ScreenPosition = new FVector2D(-ScreenBounds.Y / m, -ScreenBounds.Y);
	}

	if (ScreenPosition->X > ScreenBounds.X)
	{
		ScreenPosition = new FVector2D(ScreenBounds.X, ScreenBounds.X*m);
	}
	else if (ScreenPosition->X < -ScreenBounds.X)
	{
		ScreenPosition = new FVector2D(-ScreenBounds.X, -ScreenBounds.X*m);
	}

	*ScreenPosition += ViewportCenter;


	OutScreenPosition = *ScreenPosition;

}