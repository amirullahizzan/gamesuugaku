#include "Main.h"
#include "Base.h"

void Base::ScaleModel(float _scaleFactor)
{
	VECTOR currentScale = MV1GetScale(m_model);
	MV1SetScale(m_model, VScale(currentScale, _scaleFactor));
}

void Base::ShrinkModel(float _scaleFactor)
{
	VECTOR currentScale = MV1GetScale(m_model);
	VECTOR reductionAmount = VScale(currentScale, _scaleFactor);
	VECTOR reducedScale = VSub(currentScale, reductionAmount);
	MV1SetScale(m_model, reducedScale);
}

Float3 Base::GetModelSize()
{
	VECTOR modelSizeVEC = MV1GetScale(m_model);
	Float3 modelSizeFloat3 = Float3(modelSizeVEC.x, modelSizeVEC.y, modelSizeVEC.z);
	return modelSizeFloat3;
}