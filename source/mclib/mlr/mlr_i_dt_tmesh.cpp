//===========================================================================//
// Copyright (C) Microsoft Corporation. All rights reserved.                 //
//===========================================================================//

#include "stdafx.h"

#include <mlr/mlr_i_dt_tmesh.hpp>

using namespace MidLevelRenderer;

//#############################################################################

#if defined(TRACE_ENABLED) && defined(MLR_TRACE)
BitTrace* MLR_I_DT_TMesh_Clip;
#endif

//#############################################################################
//###### MLRIndexedPolyMesh with no color no lighting two texture layer  ######
//#############################################################################

MLR_I_DT_TMesh::ClassData*
MLR_I_DT_TMesh::DefaultData = nullptr;

DynamicArrayOf<Stuff::Vector2DScalar>
* MLR_I_DT_TMesh::clipExtraTexCoords2;
DynamicArrayOf<Stuff::Vector2DScalar>
* MLR_I_DT_TMesh::texCoords2;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void
MLR_I_DT_TMesh::InitializeClass()
{
	Verify(!DefaultData);
	// Verify(gos_GetCurrentHeap() == StaticHeap);
	DefaultData =
		new ClassData(
		MLR_I_DT_TMeshClassID,
		"MidLevelRenderer::MLR_I_DT_TMesh",
		MLR_I_TMesh::DefaultData,
		(MLRPrimitiveBase::Factory)&Make
	);
	Register_Object(DefaultData);
	clipExtraTexCoords2 = new DynamicArrayOf<Stuff::Vector2DScalar>;
	Register_Object(clipExtraTexCoords2);
	clipExtraTexCoords2->SetLength(Limits::Max_Number_Vertices_Per_Mesh);
	texCoords2 = new DynamicArrayOf<Stuff::Vector2DScalar>;
	Register_Object(texCoords2);
	texCoords2->SetLength(Limits::Max_Number_Vertices_Per_Mesh);
#if defined(TRACE_ENABLED) && defined(MLR_TRACE)
	MLR_I_DT_TMesh_Clip = new BitTrace("MLR_I_DT_TMesh_Clip");
	Register_Object(MLR_I_DT_TMesh_Clip);
#endif
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void
MLR_I_DT_TMesh::TerminateClass()
{
	Unregister_Object(clipExtraTexCoords2);
	delete clipExtraTexCoords2;
	Unregister_Object(texCoords2);
	delete texCoords2;
	Unregister_Object(DefaultData);
	delete DefaultData;
	DefaultData = nullptr;
#if defined(TRACE_ENABLED) && defined(MLR_TRACE)
	Unregister_Object(MLR_I_DT_PMesh_Clip);
	delete MLR_I_DT_PMesh_Clip;
#endif
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
MLR_I_DT_TMesh::MLR_I_DT_TMesh(
	ClassData* class_data,
	MemoryStream* stream,
	uint32_t version
):
	MLR_I_TMesh(class_data, stream, version)
{
	Check_Pointer(this);
	Check_Pointer(stream);
	//Verify(gos_GetCurrentHeap() == Heap);
	referenceState2.Load(stream, version);
	referenceState2.SetZBufferWriteOff();
	referenceState.SetPriority(MLRState::DefaultPriority);
	referenceState2.SetPriority(MLRState::DefaultPriority);
#if 0
	referenceState.SetPriority(MLRState::DefaultPriority + 1);
	referenceState2.SetAlphaMode(MLRState::OneZeroMode);
	referenceState.SetAlphaMode(MLRState::AlphaInvAlphaMode);
#endif
	passes = 2;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
MLR_I_DT_TMesh::MLR_I_DT_TMesh(ClassData* class_data):
	MLR_I_TMesh(class_data)
{
	Check_Pointer(this);
	//Verify(gos_GetCurrentHeap() == Heap);
	passes = 2;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
MLR_I_DT_TMesh::~MLR_I_DT_TMesh()
{
	Check_Object(this);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
MLR_I_DT_TMesh*
MLR_I_DT_TMesh::Make(
	MemoryStream* stream,
	uint32_t version
)
{
	Check_Object(stream);
	gos_PushCurrentHeap(Heap);
	MLR_I_DT_TMesh* mesh = new MLR_I_DT_TMesh(DefaultData, stream, version);
	gos_PopCurrentHeap();
	return mesh;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void
MLR_I_DT_TMesh::Save(MemoryStream* stream)
{
	Check_Object(this);
	Check_Object(stream);
	MLR_I_TMesh::Save(stream);
	referenceState2.Save(stream);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
bool
MLR_I_DT_TMesh::Copy(MLR_I_DT_PMesh* pmesh)
{
	Check_Object(pmesh);
	MLR_I_TMesh::Copy(pmesh);
	referenceState2 = pmesh->GetReferenceState(1);
	return true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void
MLR_I_DT_TMesh::TestInstance(void) const
{
	Verify(IsDerivedFrom(DefaultData));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void
MLR_I_DT_TMesh::SetTexCoordData(
	const Stuff::Vector2DScalar* data,
	size_t dataSize
)
{
	Check_Object(this);
	Check_Pointer(data);
	Verify(coords.GetLength() == 0 || dataSize == 2 * coords.GetLength());
	texCoords.AssignData((Vector2DScalar*)data, dataSize);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
int32_t
MLR_I_DT_TMesh::GetNumPasses()
{
	Check_Object(this);
	if(MLRState::GetMultitextureLightMap() == true && state.GetMultiTextureMode() != MLRState::MultiTextureOffMode)
	{
		return 1;
	}
	return 2;
}

#define I_SAY_YES_TO_DUAL_TEXTURES
#undef I_SAY_YES_TO_COLOR
#undef I_SAY_YES_TO_LIGHTING

#define CLASSNAME MLR_I_DT_TMesh

#if defined(TRACE_ENABLED) && defined(MLR_TRACE)
#define SET_MLR_TMESH_CLIP() MLR_I_DT_TMesh_Clip->Set()
#define CLEAR_MLR_TMESH_CLIP() MLR_I_DT_TMesh_Clip->Clear()
#else
#define SET_MLR_TMESH_CLIP()
#define CLEAR_MLR_TMESH_CLIP()
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	This include contains follwing functions:
//	void MLR_I_DT_TMesh::TransformNoClip(Matrix4D*, GOSVertexPool*);
//	int32_t MLR_I_DT_TMesh::Clip(MLRClippingState, GOSVertexPool*);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <mlr/mlrtriangleclipping.inl>

#undef I_SAY_YES_TO_DUAL_TEXTURES
#undef CLASSNAME

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
MLR_I_DT_TMesh*
MidLevelRenderer::CreateIndexedTriCube_NoColor_NoLit_2Tex(
	float half,
	MLRState* state,
	MLRState* state2
)
{
#if 0
	gos_PushCurrentHeap(Heap);
	MLR_I_DT_TMesh* ret = new MLR_I_DT_TMesh();
	Register_Object(ret);
	Point3D* coords = new Point3D [8];
	Register_Object(coords);
	coords[0] = Point3D(half, -half,  half);
	coords[1] = Point3D(-half, -half,  half);
	coords[2] = Point3D(half, -half, -half);
	coords[3] = Point3D(-half, -half, -half);
	coords[4] = Point3D(-half,  half,  half);
	coords[5] = Point3D(half,  half,  half);
	coords[6] = Point3D(half,  half, -half);
	coords[7] = Point3D(-half,  half, -half);
	puint8_t lengths = new uint8_t [6];
	Register_Pointer(lengths);
	int32_t i;
	for(i = 0; i < 6; i++)
	{
		lengths[i] = 4;
	}
	ret->SetSubprimitiveLengths(lengths, 6);
	ret->SetCoordData(coords, 8);
	puint16_t index = new uint16_t [6 * 4];
	Register_Pointer(index);
	index[0] = 0;
	index[1] = 2;
	index[2] = 6;
	index[3] = 5;
	index[4] = 0;
	index[5] = 5;
	index[6] = 4;
	index[7] = 1;
	index[8] = 5;
	index[9] = 6;
	index[10] = 7;
	index[11] = 4;
	index[12] = 2;
	index[13] = 3;
	index[14] = 7;
	index[15] = 6;
	index[16] = 1;
	index[17] = 4;
	index[18] = 7;
	index[19] = 3;
	index[20] = 0;
	index[21] = 1;
	index[22] = 3;
	index[23] = 2;
	ret->SetIndexData(index, 6 * 4);
	ret->FindFacePlanes();
	Stuff::Vector2DScalar* texCoords = new Stuff::Vector2DScalar[16];
	Register_Pointer(texCoords);
	texCoords[0] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[1] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[2] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[3] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[4] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[5] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[6] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[7] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[8] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[9] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[10] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[12] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[13] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[14] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[15] = Stuff::Vector2DScalar(0.0f, 0.0f);
	texCoords[16] = Stuff::Vector2DScalar(0.0f, 0.0f);
	if(state != nullptr)
	{
		ret->SetReferenceState(*state);
		if(state->GetTextureHandle() > 0)
		{
			texCoords[0] = Stuff::Vector2DScalar(0.0f, 0.0f);
			texCoords[1] = Stuff::Vector2DScalar(1.0f, 0.0f);
			texCoords[2] = Stuff::Vector2DScalar(0.25f, 0.25f);
			texCoords[3] = Stuff::Vector2DScalar(0.75f, 0.25f);
			texCoords[4] = Stuff::Vector2DScalar(1.0f, 1.0f);
			texCoords[5] = Stuff::Vector2DScalar(0.0f, 1.0f);
			texCoords[6] = Stuff::Vector2DScalar(0.25f, 0.75f);
			texCoords[7] = Stuff::Vector2DScalar(0.75f, 0.75f);
		}
	}
	if(state2 != nullptr)
	{
		ret->SetReferenceState(*state, 1);
		if(state2->GetTextureHandle() > 0)
		{
			texCoords[8] = Stuff::Vector2DScalar(0.0f, 0.0f);
			texCoords[9] = Stuff::Vector2DScalar(1.0f, 0.0f);
			texCoords[10] = Stuff::Vector2DScalar(0.25f, 0.25f);
			texCoords[11] = Stuff::Vector2DScalar(0.75f, 0.25f);
			texCoords[12] = Stuff::Vector2DScalar(1.0f, 1.0f);
			texCoords[13] = Stuff::Vector2DScalar(0.0f, 1.0f);
			texCoords[14] = Stuff::Vector2DScalar(0.25f, 0.75f);
			texCoords[15] = Stuff::Vector2DScalar(0.75f, 0.75f);
		}
	}
	ret->SetTexCoordData(texCoords, 16);
	Unregister_Object(texCoords);
	delete [] texCoords;
	Unregister_Pointer(index);
	delete [] index;
	Unregister_Pointer(lengths);
	delete [] lengths;
	Unregister_Object(coords);
	delete [] coords;
	gos_PopCurrentHeap();
	return ret;
#else
	return nullptr;
#endif
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
MLRShape*
MidLevelRenderer::CreateIndexedTriIcosahedron_NoColor_NoLit_2Tex(
	IcoInfo& icoInfo,
	MLRState* state,
	MLRState* state2
)
{
	gos_PushCurrentHeap(Heap);
	MLRShape* ret = new MLRShape(20);
	Register_Object(ret);
	int32_t i, j, k;
	uint32_t nrTri = static_cast<uint32_t>(ceil(icoInfo.all * pow(4.0f, icoInfo.depth)));
	Point3D v[3];
	if(3 * nrTri >= Limits::Max_Number_Vertices_Per_Mesh)
	{
		nrTri = Limits::Max_Number_Vertices_Per_Mesh / 3;
	}
	Point3D* coords = new Point3D [nrTri * 3];
	Register_Pointer(coords);
	Point3D* collapsedCoords = nullptr;
	if(icoInfo.indexed == true)
	{
		collapsedCoords = new Point3D [nrTri * 3];
		Register_Pointer(collapsedCoords);
	}
	puint16_t index = new uint16_t [nrTri * 3];
	Register_Pointer(index);
	Stuff::Vector2DScalar* texCoords = new Stuff::Vector2DScalar[2 * nrTri * 3];
	Register_Pointer(texCoords);
	int32_t uniquePoints = 0;
	for(k = 0; k < 20; k++)
	{
		triDrawn = 0;
		MLR_I_DT_TMesh* mesh = new MLR_I_DT_TMesh();
		Register_Object(mesh);
// setup vertex position information
		for(j = 0; j < 3; j++)
		{
			v[j].x = vdata[tindices[k][j]][0];
			v[j].y = vdata[tindices[k][j]][1];
			v[j].z = vdata[tindices[k][j]][2];
		}
		subdivide(coords, v[0], v[1], v[2], icoInfo.depth, nrTri, icoInfo.radius);
		mesh->SetSubprimitiveLengths(nullptr, nrTri);
		if(icoInfo.indexed == true)
		{
			uniquePoints = 1;
			collapsedCoords[0] = coords[0];
			index[0] = 0;
			for(i = 1; i < nrTri * 3; i++)
			{
				for(j = 0; j < uniquePoints; j++)
				{
					if(coords[i] == collapsedCoords[j])
					{
						break;
					}
				}
				if(j == uniquePoints)
				{
					collapsedCoords[uniquePoints++] = coords[i];
				}
				index[i] = static_cast<uint16_t>(j);
			}
			mesh->SetCoordData(collapsedCoords, uniquePoints);
		}
		else
		{
			uniquePoints = nrTri * 3;
			for(i = 0; i < nrTri * 3; i++)
			{
				index[i] = static_cast<uint16_t>(i);
			}
			mesh->SetCoordData(coords, nrTri * 3);
		}
		mesh->SetIndexData(index, nrTri * 3);
		mesh->FindFacePlanes();
		if(state == nullptr)
		{
			for(i = 0; i < 2 * uniquePoints; i++)
			{
				texCoords[i] = Stuff::Vector2DScalar(0.0f, 0.0f);
			}
		}
		else
		{
			state->SetMultiTextureMode(MLRState::MultiTextureLightmapMode);
			mesh->SetReferenceState(*state);
			state->SetMultiTextureMode(MLRState::MultiTextureOffMode);
			if(state->GetTextureHandle() > 0)
			{
				if(icoInfo.indexed == true)
				{
					for(i = 0; i < uniquePoints; i++)
					{
						texCoords[i] =
							Stuff::Vector2DScalar(
								(1.0f + collapsedCoords[i].x) / 2.0f,
								(1.0f + collapsedCoords[i].y) / 2.0f
							);
						texCoords[i + uniquePoints] =
							Stuff::Vector2DScalar(
								(1.0f + collapsedCoords[i].x) / 2.0f,
								(1.0f + collapsedCoords[i].z) / 2.0f
							);
					}
				}
				else
				{
					for(i = 0; i < nrTri; i++)
					{
						texCoords[3 * i] =
							Stuff::Vector2DScalar(
								(1.0f + coords[3 * i].x) / 2.0f,
								(1.0f + coords[3 * i].y) / 2.0f
							);
						texCoords[3 * i + 1] =
							Stuff::Vector2DScalar(
								(1.0f + coords[3 * i + 1].x) / 2.0f,
								(1.0f + coords[3 * i + 1].y) / 2.0f
							);
						texCoords[3 * i + 2] =
							Stuff::Vector2DScalar(
								(1.0f + coords[3 * i + 2].x) / 2.0f,
								(1.0f + coords[3 * i + 2].y) / 2.0f
							);
						texCoords[3 * i + nrTri] =
							Stuff::Vector2DScalar(
								(1.0f + coords[3 * i].x) / 2.0f,
								(1.0f + coords[3 * i].z) / 2.0f
							);
						texCoords[3 * i + 1 + nrTri] =
							Stuff::Vector2DScalar(
								(1.0f + coords[3 * i + 1].x) / 2.0f,
								(1.0f + coords[3 * i + 1].z) / 2.0f
							);
						texCoords[3 * i + 2 + nrTri] =
							Stuff::Vector2DScalar(
								(1.0f + coords[3 * i + 2].x) / 2.0f,
								(1.0f + coords[3 * i + 2].z) / 2.0f
							);
					}
				}
			}
			else
			{
				for(i = 0; i < 2 * uniquePoints; i++)
				{
					texCoords[i] = Stuff::Vector2DScalar(0.0f, 0.0f);
				}
			}
		}
		mesh->SetTexCoordData(texCoords, 2 * uniquePoints);
		mesh->SetReferenceState(*state2, 1);
		ret->Add(mesh);
		mesh->DetachReference();
	}
	Unregister_Pointer(texCoords);
	delete [] texCoords;
	Unregister_Pointer(index);
	delete [] index;
	if(icoInfo.indexed == true)
	{
		Unregister_Pointer(collapsedCoords);
		delete [] collapsedCoords;
	}
	Unregister_Pointer(coords);
	delete [] coords;
	gos_PopCurrentHeap();
	return ret;
}
