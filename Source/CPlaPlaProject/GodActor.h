// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GodActor.generated.h"

UCLASS()
class CPLAPLAPROJECT_API AGodActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGodActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// �������ɃR�[�������֐�(�R�[�f�B���O�p�̃R���X�g���N�^�I�Ȋ���)
	virtual void OnConstruction(const FTransform& Transform) override;

};
