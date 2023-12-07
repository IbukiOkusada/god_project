// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyGodPawn.generated.h"

UCLASS()
class CPLAPLAPROJECT_API AMyGodPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyGodPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// �\������I�u�W�F�N�g���Ǘ�����R���|�[�l���g
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleConponent;

	// StaticMesh�R���|�[�l���g��錾
	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* VisualMesh;

	FRotator RotSpeed;
	FVector MoveSpeed;

	//Y�����̈ړ��ʂ𐧌�
	void GodMove_YAxis(float GodValue);
	void GodMove_XAxis(float GodValue);

	// ���݂̑��x
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere, // �G�f�B�^��Ƀv���p�e�B��������A�ҏW�\�ɂ���
		BlueprintReadWrite,		// �u���[�v�����g�ł̓ǂݍ��݂Ə������݂��\�ɂ���
		Category = "default")	// �G�f�B�^��Ɍ�����ꂽ�v���p�e�B���J�e�S��(�l�X�e�B���O)��������
		float InputSpeed;

	// �����X�C�b�`����
	void StartGrowing();
	void StopGrowing();

	// �����t���O
	bool IsGrowing;

	// ����
	UPROPERTY(EditAnywhere, // �G�f�B�^��Ƀv���p�e�B��������A�ҏW�\�ɂ���
		BlueprintReadWrite,		// �u���[�v�����g�ł̓ǂݍ��݂Ə������݂��\�ɂ���
		Category = "default")	// �G�f�B�^��Ɍ�����ꂽ�v���p�e�B���J�e�S��(�l�X�e�B���O)��������
	float ScaleSpeed;
};
