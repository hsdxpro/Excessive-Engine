#pragma once

#include <mymath/mm_common.h>
#include <mymath/mymath.h>
#include "ICamera.h"

class Camera : public ICamera 
{
public:
	Camera();
	Camera(rProjOrtho proj, float nearPlane, float farPlane);
	Camera(rProjPersp proj, float nearPlane, float farPlane);

	void SetFOV(float rad) override;
	void SetNearPlane(float nP) override;
	void SetFarPlane(float fP) override;

	void SetPos(const mm::vec3& p) override;
	void SetTarget(const mm::vec3& p) override;
	void SetDirNormed(const mm::vec3& p) override;
	void SetRot(const mm::quat& q) override;

	float GetFOVRad() const override;
	float GetNearPlane() const override;
	float GetFarPlane() const override;

	mm::mat4 GetViewMatrix() const override;
	mm::mat4 GetProjMatrix(float aspectRatio) const override;

	mm::vec3 GetFrontDir() const override;
	mm::vec3 GetBackDir() const override;
	mm::vec3 GetUpDir() const override;
	mm::vec3 GetDownDir() const override;
	mm::vec3 GetRightDir() const override;
	mm::vec3 GetLeftDir() const override;

	const mm::vec3& GetPos() const override;
	const mm::quat& GetRot() const override;
	const mm::vec3 GetTargetPos() const override;

//protected:
//	void calcProjMatrix();

protected:
	// Pos, Target ( World space )
	mm::vec3 pos;
	mm::quat rot;

	// View params
	float nearPlane;
	float farPlane;

	// Projection params ( TODO: little bit stupid to prepare camera class for every projection )
	eProjType projType;
	rProjOrtho projOrtho;
	rProjPersp projPersp;
	mm::mat4 proj;
};