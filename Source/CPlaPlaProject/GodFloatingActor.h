// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GodFloatingActor.generated.h"

UCLASS()
class CPLAPLAPROJECT_API AGodFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGodFloatingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// StaticMeshコンポーネントを宣言
	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere, // エディタ上にプロパティを後悔し、編集可能にする
		BlueprintReadWrite,		// ブループリントでの読み込みと書き込みを可能にする
		Category="default")	// エディタ上に後悔されたプロパティをカテゴリ(ネスティング)分けする
		FVector MoveSpeed;

	UPROPERTY(EditAnywhere, // エディタ上にプロパティを後悔し、編集可能にする
		BlueprintReadWrite,		// ブループリントでの読み込みと書き込みを可能にする
		Category = "default")	// エディタ上に後悔されたプロパティをカテゴリ(ネスティング)分けする
		FRotator RotSpeed;

	UPROPERTY(EditAnywhere, // エディタ上にプロパティを後悔し、編集可能にする
		BlueprintReadWrite,		// ブループリントでの読み込みと書き込みを可能にする
		Category = "default")	// エディタ上に後悔されたプロパティをカテゴリ(ネスティング)分けする
		bool IsFloating;

private:
};
