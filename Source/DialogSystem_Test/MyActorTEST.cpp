// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorTEST.h"

// Sets default values
AMyActorTEST::AMyActorTEST()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActorTEST::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActorTEST::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

 
  

//void AMyActorTEST::Execute_NativEv()
//{
//	UE_LOG(LogTemp, Warning, TEXT("->->->->->->->    nativEv_implementable"));
//	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, "->->->->->->->    nativEv_implementable");
//}
void AMyActorTEST::NativEv_Implementation() const
{
	UE_LOG(LogTemp, Warning, TEXT("->->->->->->->    nativEv_implementable"));
	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, "->->->->->->->    nativEv_implementable");
}
/*
void AMyActorTEST::NativEv()
{
	UE_LOG(LogTemp, Warning, TEXT("->->->->->->->    nativEv_implementable"));
	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, "->->->->->->->    nativEv_implementable");
}
*/