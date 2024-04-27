// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryPickup.h"

ABatteryPickup::ABatteryPickup()
{
	// enable physics.
	const auto mesh = GetMesh();
	mesh->SetSimulatePhysics(true);
}

void ABatteryPickup::WasCollected_Implementation()
{
	// destroy when colelcted.
	Super::WasCollected_Implementation();
	Destroy();
}

float ABatteryPickup::GetPower() const
{
	return BatteryPower;
}
