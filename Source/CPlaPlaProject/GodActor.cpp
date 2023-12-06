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

// �������ɃR�[�������֐�(�R�[�f�B���O�p�̃R���X�g���N�^�I�Ȋ���)
void AGodActor::OnConstruction(const FTransform& transform)
{
	GEngine->AddOnScreenDebugMessage(
		(uint64)-1,
		2.0f,
		FLinearColor::Blue.ToFColor(true),
		TEXT("Ohhowwwwwwwww")
	);
}