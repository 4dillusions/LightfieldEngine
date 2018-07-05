#pragma once

#include "SMCore.h"
#include "SMString.h"
#include "../IO/SMLogger.h"

using namespace SMEngine::IO;

namespace SMEngine { namespace Core
{
	/*
	Compositor pattern.
	Minden játék objektum, ami a GameComponent listán szerepel.
	isAlive-ot inicializálni kell a konstrukorban!
	*/
	abstract class SMGameComponent
	{
	protected:
		bool isAlive, isVisible;
		SMString name;

	public:
		SMGameComponent(const SMString &name) : isAlive(true), isVisible(true), name(name)
		{ }

		virtual ~SMGameComponent()
		{ }

		SMString &Name() { return name; }
		virtual void Update(double deltaTime) = 0;
		bool IsAlive() { return isAlive; };
		virtual void IsAlive(bool isAlive) { this->isAlive = isAlive; }
		bool IsVisible() { return isVisible; };
		virtual void IsVisible(bool isVisible) { this->isVisible = isVisible; }
		virtual void WriteReport() { };
	};
};};
