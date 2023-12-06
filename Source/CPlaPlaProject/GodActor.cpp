// Fill out your copyright notice in the Description page of Project Settings.


#include "GodActor.h"

// Sets default values
AGodActor::AGodActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGodActor::BeginPlay()
{
	Super::BeginPlay();
	
	GEngine->AddOnScreenDebugMessage(
		(uint64)-1,
		2.0f,
		FLinearColor::Red.ToFColor(true),
		TEXT("GOD")
	);
}

// Called every frame
void AGodActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 生成時にコールされる関数(コーディング用のコンストラクタ的な感じ)
void AGodActor::OnConstruction(const FTransform& transform)
{
	GEngine->AddOnScreenDebugMessage(
		(uint64)-1,
		2.0f,
		FLinearColor::Blue.ToFColor(true),
		TEXT("Ohhowwwwwwwww")
	);
}