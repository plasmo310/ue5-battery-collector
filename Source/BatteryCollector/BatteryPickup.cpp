// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryPickup.h"

ABatteryPickup::ABatteryPickup()
{
	// enable physics.
	auto mesh = GetMesh();
	mesh->SetSimulatePhysics(true);
}

