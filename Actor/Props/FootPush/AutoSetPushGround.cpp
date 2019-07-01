// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoSetPushGround.h"
#include "Engine/Public/EngineUtils.h"
#include "Cpt_FootPushGround.h"

// Sets default values
AAutoSetPushGround::AAutoSetPushGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FClassFinder<UCpt_FootPushGround> Asset_Effect(TEXT("/Game/1_Project_Main/1_Blueprints/Actor/Props/FootPush/BP_Cpt_FootPushGround.BP_Cpt_FootPushGround_C"));

	if (Asset_Effect.Succeeded())
	{
		m_pBP = Asset_Effect.Class;
	}
	
}


// Called when the game starts or when spawned
void AAutoSetPushGround::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (*ActorItr != nullptr)
		{
			if (ActorItr->ActorHasTag("PushGround") == true)
			{
				//ULOG(TEXT("%s"), *ActorItr->GetName());
				UActorComponent* pActorCpt = ActorItr->GetComponentByClass(UCpt_FootPushGround::StaticClass());
				if (pActorCpt != nullptr) continue;
				//ActorItr->CreateDefaultSubobject< UCpt_FootPushGround>(TEXT("FootGround"));

				UCpt_FootPushGround* newSpline = nullptr;
				newSpline = NewObject<UCpt_FootPushGround>(*ActorItr, m_pBP, "FootGround");
				if (newSpline != nullptr)
				{

					newSpline->RegisterComponent();
				}
			}
		}
	}

}

// Called every frame
void AAutoSetPushGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

