#pragma once
#include "BaseLibrary\Types.h"
#include "mymath\mymath.h"

// namespace
//namespace graphics {

////////////////////////////////////////////////////////////////////////////////
///	Texture is a resource representing an image/bitmap.
///
////////////////////////////////////////////////////////////////////////////////

enum class eProjType : u32 
{
	ORTHO,
	PERSP,
};

struct rProjOrtho 
{
	rProjOrtho(){}
	rProjOrtho(float left, float right, float bottom, float top) :left(left), right(right), top(top), bottom(bottom){}

	float left, right, top, bottom;
};

struct rProjPersp
{
	rProjPersp():fovRad(3.14159265358979f * 0.5f){}
	rProjPersp(float fovRad) :fovRad(fovRad){}

	float fovRad;
};

class ICamera
{
public:
	virtual void SetFOV(float rad) = 0;
	virtual void SetNearPlane(float nP) = 0;
	virtual void SetFarPlane(float fP) = 0;
	
	virtual void SetPos(const mm::vec3& p) = 0;
	virtual void SetTarget(const mm::vec3& p) = 0;
	virtual void SetDirNormed(const mm::vec3& p) = 0;
	virtual void SetRot(const mm::quat& q) = 0;
	
	virtual float GetFOVRad() const = 0;
	virtual float GetNearPlane() const = 0;
	virtual float GetFarPlane() const = 0;
	
	virtual mm::mat4 GetViewMatrix() const = 0;
	virtual mm::mat4 GetProjMatrix(float aspectRatio) const = 0;
	
	virtual mm::vec3 GetFrontDir() const = 0;
	virtual mm::vec3 GetBackDir() const = 0;
	virtual mm::vec3 GetUpDir() const = 0;
	virtual mm::vec3 GetDownDir() const = 0;
	virtual mm::vec3 GetRightDir() const = 0;
	virtual mm::vec3 GetLeftDir() const = 0;
	
	virtual const mm::vec3& GetPos() const = 0;
	virtual const mm::quat& GetRot() const = 0;
	virtual const mm::vec3 GetTargetPos() const = 0;
};



//} // namespace