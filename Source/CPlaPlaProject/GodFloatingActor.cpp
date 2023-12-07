// Fill out your copyright notice in the Description page of Project Settings.


#include "GodFloatingActor.h"

// Sets default values
AGodFloatingActor::AGodFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed.X = 0.0f;
	MoveSpeed.Y = 0.0f;
	MoveSpeed.Z = 50.0f;
	RotSpeed.Roll = 0.0f;
	RotSpeed.Pitch = 0.0f;
	RotSpeed.Yaw = 20.0f;
	IsFloating = true;

	// メッシュの作成
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	// アセットの設定
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	// 作成に成功したか判定
	if (CubeVisualAsset.Succeeded())
	{
		// パラメータ設定
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

// Called when the game starts or when spawned
void AGodFloatingActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGodFloatingActor::Tick(float DeltaTime)
{
	if (!IsFloating) {
		return;
	}

	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();
	float fDelta = GetGameTimeSinceCreation();

	Super::Tick(DeltaTime);
	
	Location += (FMath::Sin(fDelta + DeltaTime) - FMath::Sin(fDelta)) * MoveSpeed;
	Rotation += (FMath::Sin(DeltaTime)) * RotSpeed;

	SetActorLocation(Location);
	SetActorRotation(Rotation);
}

