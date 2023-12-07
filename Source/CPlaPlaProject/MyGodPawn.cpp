// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGodPawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyGodPawn::AMyGodPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InputSpeed = 100.0f;
	MoveSpeed.X = 0.0f;
	MoveSpeed.Y = 0.0f;
	MoveSpeed.Z = 200.0f;
	RotSpeed.Roll = 0.0f;
	RotSpeed.Pitch = 0.0f;
	RotSpeed.Yaw = 100.0f;

	// Player0 (�ŏ��l0�Ԗڂ̃v���C���[)�Ƃ����ݒ���s��
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// �l�b�g���[�N�Ȃǂŕ����̃v���C���[������ꍇ�ɁA�ǂ̃v���C���[�����f����̂Ɏg�p

	// ���b�V���̍쐬
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	// �A�Z�b�g�̐ݒ�
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	// �e�q�t���\�ȃ_�~�[�̃��[�g�R���|�[�l���g���쐬
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// �J�����I�u�W�F�N�g���쐬
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

	// �̎��I�u�W�F�N�g(���b�V��)���쐬
	OurVisibleConponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// RootComponent�ɃJ������e�q�t��
	OurCamera->SetupAttachment(RootComponent);

	// �J�������ڂ��Ώۂ̈ʒu�Ɉˑ�����悤�ɔz�u
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	// RootComponent�ɉ̎��I�u�W�F�N�g(���b�V��)��e�q�t��
	OurVisibleConponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyGodPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyGodPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = VisualMesh->GetRelativeLocation();
	FRotator Rotation = VisualMesh->GetRelativeRotation();
	float fDelta = GetGameTimeSinceCreation();

	Location += (FMath::Sin(fDelta + DeltaTime) - FMath::Sin(fDelta)) * MoveSpeed;
	Rotation += (FMath::Sin(DeltaTime)) * RotSpeed;

	VisualMesh->SetRelativeLocation(Location);
	VisualMesh->SetRelativeRotation(Rotation);

	if (!CurrentVelocity.IsZero()) {
		CurrentVelocity.Normalize();
		CurrentVelocity = CurrentVelocity * InputSpeed;

		SetActorLocation((CurrentVelocity * DeltaTime) + GetActorLocation());
	}

	GEngine->AddOnScreenDebugMessage(
		(uint64)-1,
		2.0f,
		FLinearColor::Red.ToFColor(true),
		FString::Printf(TEXT("Velocity[ %f, %f, %f]\n"), CurrentVelocity.X, CurrentVelocity.Y, CurrentVelocity.Z)
	);

	float CurrentScale = OurVisibleConponent->GetComponentScale().X;

	if (IsGrowing) {	// �c��ނ�
		CurrentScale += ScaleSpeed * DeltaTime;
	}
	else {	// �k�ނ�
		CurrentScale -= ScaleSpeed * (DeltaTime * 0.5f);
	}

	// �X�P�[���l��1.0�`2.0 �̊ԂŐ���
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);

	// ���f
	OurVisibleConponent->SetWorldScale3D(FVector(CurrentScale));
}

// Called to bind functionality to input
void AMyGodPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// MoveY�̓��͒l��GodMove_YAxis�֐��փo�C���h����
	InputComponent->BindAxis("MOVEY", this, &AMyGodPawn::GodMove_YAxis);

	// MoveY�̓��͒l��GodMove_YAxis�֐��փo�C���h����
	InputComponent->BindAxis("MOVEX", this, &AMyGodPawn::GodMove_XAxis);

	// Grow�̓��͒l���o�C���h
	InputComponent->BindAction("Grow", EInputEvent::IE_Pressed, this, &AMyGodPawn::StartGrowing);

	InputComponent->BindAction("Grow", EInputEvent::IE_Released, this, &AMyGodPawn::StopGrowing);
}

//Y�����̈ړ��ʂ𐧌�
void AMyGodPawn::GodMove_YAxis(float GodValue)
{
	// (1�b�Ԃɍ��E�� 100�P�ʈړ�)
	CurrentVelocity.Y = FMath::Clamp(GodValue, -1.0f, 1.0f);
}

//X�����̈ړ��ʂ𐧌�
void AMyGodPawn::GodMove_XAxis(float GodValue)
{
	// (1�b�Ԃɍ��E�� 100�P�ʈړ�)
	CurrentVelocity.X = FMath::Clamp(GodValue, -1.0f, 1.0f);
}

// �����J�n�t���O
void AMyGodPawn::StartGrowing()
{
	IsGrowing = true;
}

// ������~�t���O
void AMyGodPawn::StopGrowing()
{
	IsGrowing = false;
}

