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

	// 表示するオブジェクトを管理するコンポーネント
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleConponent;

	// StaticMeshコンポーネントを宣言
	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* VisualMesh;

	FRotator RotSpeed;
	FVector MoveSpeed;

	//Y方向の移動量を制御
	void GodMove_YAxis(float GodValue);
	void GodMove_XAxis(float GodValue);

	// 現在の速度
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere, // エディタ上にプロパティを後悔し、編集可能にする
		BlueprintReadWrite,		// ブループリントでの読み込みと書き込みを可能にする
		Category = "default")	// エディタ上に後悔されたプロパティをカテゴリ(ネスティング)分けする
		float InputSpeed;

	// 成長スイッチ制御
	void StartGrowing();
	void StopGrowing();

	// 成長フラグ
	bool IsGrowing;

	// 成長
	UPROPERTY(EditAnywhere, // エディタ上にプロパティを後悔し、編集可能にする
		BlueprintReadWrite,		// ブループリントでの読み込みと書き込みを可能にする
		Category = "default")	// エディタ上に後悔されたプロパティをカテゴリ(ネスティング)分けする
	float ScaleSpeed;
};
