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

	// Player0 (最小値0番目のプレイヤー)という設定を行う
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// ネットワークなどで複数のプレイヤーがいる場合に、どのプレイヤーか判断するのに使用

	// メッシュの作成
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	// アセットの設定
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	// 親子付け可能なダミーのルートコンポーネントを作成
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// カメラオブジェクトを作成
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

	// 歌詞オブジェクト(メッシュ)を作成
	OurVisibleConponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// RootComponentにカメラを親子付け
	OurCamera->SetupAttachment(RootComponent);

	// カメラが移す対象の位置に依存するように配置
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	// RootComponentに歌詞オブジェクト(メッシュ)を親子付け
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

	if (IsGrowing) {	// 膨らむよ
		CurrentScale += ScaleSpeed * DeltaTime;
	}
	else {	// 縮むよ
		CurrentScale -= ScaleSpeed * (DeltaTime * 0.5f);
	}

	// スケール値を1.0～2.0 の間で制御
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);

	// 反映
	OurVisibleConponent->SetWorldScale3D(FVector(CurrentScale));
}

// Called to bind functionality to input
void AMyGodPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// MoveYの入力値をGodMove_YAxis関数へバインドする
	InputComponent->BindAxis("MOVEY", this, &AMyGodPawn::GodMove_YAxis);

	// MoveYの入力値をGodMove_YAxis関数へバインドする
	InputComponent->BindAxis("MOVEX", this, &AMyGodPawn::GodMove_XAxis);

	// Growの入力値をバインド
	InputComponent->BindAction("Grow", EInputEvent::IE_Pressed, this, &AMyGodPawn::StartGrowing);

	InputComponent->BindAction("Grow", EInputEvent::IE_Released, this, &AMyGodPawn::StopGrowing);
}

//Y方向の移動量を制御
void AMyGodPawn::GodMove_YAxis(float GodValue)
{
	// (1秒間に左右へ 100単位移動)
	CurrentVelocity.Y = FMath::Clamp(GodValue, -1.0f, 1.0f);
}

//X方向の移動量を制御
void AMyGodPawn::GodMove_XAxis(float GodValue)
{
	// (1秒間に左右へ 100単位移動)
	CurrentVelocity.X = FMath::Clamp(GodValue, -1.0f, 1.0f);
}

// 成長開始フラグ
void AMyGodPawn::StartGrowing()
{
	IsGrowing = true;
}

// 成長停止フラグ
void AMyGodPawn::StopGrowing()
{
	IsGrowing = false;
}

